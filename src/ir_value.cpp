/*
Copyright (c) 2019, Intel Corporation

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

//////////////////////////////////////////////////////////////////////////////

#include "ir_value.h"
#include "type.h"

using namespace yarpgen;

IRValue::IRValue()
    : type_id(IntTypeID::MAX_INT_TYPE_ID), undefined(true),
      ub_code(UBKind::NoUB) {
    value.ullong_val = 0;
}

IRValue::IRValue(IntTypeID _type_id)
    : type_id(_type_id), undefined(true), ub_code(UBKind::NoUB) {
    value.ullong_val = 0;
}

template <> bool &IRValue::getValueRef() { return value.bool_val; }
template <> int8_t &IRValue::getValueRef() { return value.schar_val; }
template <> uint8_t &IRValue::getValueRef() { return value.uchar_val; }
template <> int16_t &IRValue::getValueRef() { return value.shrt_val; }
template <> uint16_t &IRValue::getValueRef() { return value.ushrt_val; }
template <> int32_t &IRValue::getValueRef() { return value.int_val; }
template <> uint32_t &IRValue::getValueRef() { return value.uint_val; }
template <> int64_t &IRValue::getValueRef() { return value.llong_val; }
template <> uint64_t &IRValue::getValueRef() { return value.ullong_val; }

//////////////////////////////////////////////////////////////////////////////

// The idea here is to have a template functions to do all the real work and
// overloaded operators as a proxy-functions. In order to improve code reuse
// we usually implement them with define.

IRValue IRValue::operator+() { return {*this}; }

//////////////////////////////////////////////////////////////////////////////
template <typename T> static IRValue minusOperator(IRValue &operand) {
    IRValue ret(operand.getIntTypeID());
    if (std::is_signed<T>::value &&
        operand.getValueRef<T>() == std::numeric_limits<T>::min())
        ret.setUBCode(UBKind::SignOvf);
    else
        ret.getValueRef<T>() = -operand.getValueRef<T>();
    return ret;
}

IRValue IRValue::operator-() { UnaryOperatorImpl(minusOperator); }

//////////////////////////////////////////////////////////////////////////////

static IRValue logicalNegationOperator(IRValue &operand) {
    assert(operand.getIntTypeID() == IntTypeID::BOOL &&
           "Logical negation is defined only for boolean type!");
    IRValue ret(operand.getIntTypeID());
    ret.getValueRef<bool>() = !operand.getValueRef<bool>();
    return ret;
}

IRValue IRValue::operator!() { return logicalNegationOperator(*this); }

//////////////////////////////////////////////////////////////////////////////

template <typename T> static IRValue bitwiseNegationOperator(IRValue &operand) {
    IRValue ret(operand.getIntTypeID());
    ret.getValueRef<T>() = ~operand.getValueRef<T>();
    return ret;
}

IRValue IRValue::operator~() { UnaryOperatorImpl(bitwiseNegationOperator); }

//////////////////////////////////////////////////////////////////////////////

template <typename T>
static typename std::enable_if<std::is_unsigned<T>::value, IRValue>::type
addOperator(IRValue &lhs, IRValue &rhs) {
    if (rhs.getIntTypeID() != lhs.getIntTypeID())
        ERROR("Can perform operation only on IRValues with the same IntTypeID");

    IRValue ret(rhs.getIntTypeID());
    ret.getValueRef<T>() = lhs.getValueRef<T>() + rhs.getValueRef<T>();
    assert(ret.getUBCode() == UBKind::NoUB &&
           "Addition of two unsigned values can't cause UB");
    return ret;
}

template <typename T>
static typename std::enable_if<!std::is_unsigned<T>::value, IRValue>::type
addOperator(IRValue &lhs, IRValue &rhs) {
    if (rhs.getIntTypeID() != lhs.getIntTypeID())
        ERROR("Can perform operation only on IRValues with the same IntTypeID");

    IRValue ret(rhs.getIntTypeID());
    using unsigned_T = typename std::make_unsigned<T>::type;
    auto ua = static_cast<unsigned_T>(lhs.getValueRef<T>());
    auto ub = static_cast<unsigned_T>(rhs.getValueRef<T>());
    unsigned_T u_tmp = ua + ub;
    ua = (ua >> std::numeric_limits<T>::digits) + std::numeric_limits<T>::max();
    if (static_cast<T>((ua ^ ub) | ~(ub ^ u_tmp)) >= 0)
        ret.setUBCode(UBKind::SignOvf);
    else
        ret.getValueRef<T>() = lhs.getValueRef<T>() + rhs.getValueRef<T>();
    return ret;
}

IRValue IRValue::operator+(IRValue &rhs) { BinaryOperatorImpl(addOperator); }

//////////////////////////////////////////////////////////////////////////////

template <typename T>
static typename std::enable_if<std::is_unsigned<T>::value, IRValue>::type
subOperator(IRValue &lhs, IRValue &rhs) {
    if (rhs.getIntTypeID() != lhs.getIntTypeID())
        ERROR("Can perform operation only on IRValues with the same IntTypeID");

    IRValue ret(rhs.getIntTypeID());
    ret.getValueRef<T>() = lhs.getValueRef<T>() - rhs.getValueRef<T>();
    assert(ret.getUBCode() == UBKind::NoUB &&
           "Subtraction of two unsigned values can't cause UB");
    return ret;
}

template <typename T>
static typename std::enable_if<!std::is_unsigned<T>::value, IRValue>::type
subOperator(IRValue &lhs, IRValue &rhs) {
    if (rhs.getIntTypeID() != lhs.getIntTypeID())
        ERROR("Can perform operation only on IRValues with the same IntTypeID");

    IRValue ret(rhs.getIntTypeID());
    using unsigned_T = typename std::make_unsigned<T>::type;
    auto ua = static_cast<unsigned_T>(lhs.getValueRef<T>());
    auto ub = static_cast<unsigned_T>(rhs.getValueRef<T>());
    unsigned_T u_tmp = ua - ub;
    ua = (ua >> std::numeric_limits<T>::digits) + std::numeric_limits<T>::max();
    if (static_cast<T>((ua ^ ub) & (ua ^ u_tmp)) < 0)
        ret.setUBCode(UBKind::SignOvf);
    else
        ret.getValueRef<T>() = static_cast<T>(u_tmp);
    return ret;
}

IRValue IRValue::operator-(IRValue &rhs) { BinaryOperatorImpl(subOperator); }

//////////////////////////////////////////////////////////////////////////////

template <typename T> static bool checkMulIsOk(T a, T b, IRValue &res) {
    // Special thanks to http://www.fefe.de/intof.html

    using unsigned_T = typename std::make_unsigned<T>::type;
    unsigned_T ret = 0;

    T sign = (((a > 0) && (b > 0)) || ((a < 0) && (b < 0))) ? 1 : -1;
    unsigned_T a_abs = std::abs(a);
    unsigned_T b_abs = std::abs(b);

    using unsigned_half_T =
        std::conditional_t<std::is_same<T, int32_t>::value, uint16_t, uint32_t>;
    unsigned_half_T half_all_one =
        (std::is_same<unsigned_half_T, uint32_t>::value) ? 0xFFFFFFFF : 0xFFFF;
    int32_t half_bit_size = sizeof(unsigned_half_T) * CHAR_BIT;
    unsigned_half_T a_low = a_abs & half_all_one;
    unsigned_half_T b_low = b_abs & half_all_one;
    unsigned_half_T a_high = a_abs >> half_bit_size;
    unsigned_half_T b_high = b_abs >> half_bit_size;

    if ((a_high != 0) && (b_high != 0))
        return false;

    unsigned_T tmp = (static_cast<unsigned_T>(a_high) * b_low) +
                     (static_cast<unsigned_T>(b_high) * a_low);
    if (tmp > half_all_one)
        return false;

    ret = (tmp << half_bit_size) + (static_cast<unsigned_T>(a_low) * b_low);
    if (ret < (tmp << half_bit_size))
        return false;

    if ((sign < 0) && (ret > static_cast<unsigned_T>(
                                 std::abs(std::numeric_limits<T>::min()))))
        return false;
    else if ((sign > 0) && (ret > std::numeric_limits<T>::max()))
        return false;
    else
        res.getValueRef<T>() = ret * sign;

    return true;
}

template <typename T>
static typename std::enable_if<std::is_unsigned<T>::value, IRValue>::type
mulOperator(IRValue &lhs, IRValue &rhs) {
    if (rhs.getIntTypeID() != lhs.getIntTypeID())
        ERROR("Can perform operation only on IRValues with the same IntTypeID");

    IRValue ret(rhs.getIntTypeID());
    // GCC doesn't like bool * bool. This function should be never called with T
    // = bool, so we need this kludge to suppress warning
    auto foo = std::multiplies<T>();
    ret.getValueRef<T>() = foo(lhs.getValueRef<T>(), rhs.getValueRef<T>());
    assert(ret.getUBCode() == UBKind::NoUB &&
           "Multiplication of two unsigned values can't cause UB");
    return ret;
}

template <typename T>
static typename std::enable_if<!std::is_unsigned<T>::value, IRValue>::type
mulOperator(IRValue &lhs, IRValue &rhs) {
    if (rhs.getIntTypeID() != lhs.getIntTypeID())
        ERROR("Can perform operation only on IRValues with the same IntTypeID");

    IRValue ret(rhs.getIntTypeID());

    auto special_check = [](IRValue &a, IRValue &b) -> bool {
        return (a.getValueRef<T>() == std::numeric_limits<T>::min() &&
                b.getValueRef<T>() == -1) ||
               (b.getValueRef<T>() == std::numeric_limits<T>::min() &&
                a.getValueRef<T>() == -1);
    };

    if (special_check(lhs, rhs) || special_check(rhs, lhs))
        ret.setUBCode(UBKind::SignOvfMin);
    else if (!checkMulIsOk<T>(lhs.getValueRef<T>(), rhs.getValueRef<T>(), ret))
        ret.setUBCode(UBKind::SignOvf);
    return ret;
}

IRValue IRValue::operator*(IRValue &rhs) { BinaryOperatorImpl(mulOperator); }

//////////////////////////////////////////////////////////////////////////////

template <typename T>
static typename std::enable_if<std::is_unsigned<T>::value, IRValue>::type
divModImpl(IRValue &lhs, IRValue &rhs, std::function<T(T &, T &)> op) {
    if (rhs.getIntTypeID() != lhs.getIntTypeID())
        ERROR("Can perform operation only on IRValues with the same IntTypeID");

    IRValue ret(rhs.getIntTypeID());
    if (rhs.getValueRef<T>() == 0)
        ret.setUBCode(UBKind::ZeroDiv);
    else
        ret.getValueRef<T>() = op(lhs.getValueRef<T>(), rhs.getValueRef<T>());
    return ret;
}

template <typename T>
static typename std::enable_if<!std::is_unsigned<T>::value, IRValue>::type
divModImpl(IRValue &lhs, IRValue &rhs, std::function<T(T &, T &)> op) {
    if (rhs.getIntTypeID() != lhs.getIntTypeID())
        ERROR("Can perform operation only on IRValues with the same IntTypeID");

    IRValue ret(rhs.getIntTypeID());

    auto special_check = [](IRValue &a, IRValue &b) -> bool {
        return (a.getValueRef<T>() == std::numeric_limits<T>::min() &&
                b.getValueRef<T>() == -1) ||
               (b.getValueRef<T>() == std::numeric_limits<T>::min() &&
                a.getValueRef<T>() == -1);
    };

    if (rhs.getValueRef<T>() == 0)
        ret.setUBCode(UBKind::ZeroDiv);
    else if (special_check(lhs, rhs) || special_check(rhs, lhs))
        ret.setUBCode(UBKind::SignOvf);
    else
        ret.getValueRef<T>() = op(lhs.getValueRef<T>(), rhs.getValueRef<T>());
    return ret;
}

template <typename T> static IRValue divOperator(IRValue &lhs, IRValue &rhs) {
    return divModImpl<T>(lhs, rhs, std::divides<T>());
}

IRValue IRValue::operator/(IRValue &rhs) { BinaryOperatorImpl(divOperator); }

template <typename T> static IRValue modOperator(IRValue &lhs, IRValue &rhs) {
    return divModImpl<T>(lhs, rhs, std::modulus<T>());
}

IRValue IRValue::operator%(IRValue &rhs) { BinaryOperatorImpl(modOperator); }

//////////////////////////////////////////////////////////////////////////////

template <typename T>
static IRValue cmpEqImpl(IRValue &lhs, IRValue &rhs,
                         std::function<T(T &, T &)> op) {
    if (rhs.getIntTypeID() != lhs.getIntTypeID())
        ERROR("Can perform operation only on IRValues with the same IntTypeID");

    IRValue ret(IntTypeID::BOOL);
    ret.getValueRef<bool>() = op(lhs.getValueRef<T>(), rhs.getValueRef<T>());
    return ret;
}

template <typename T> static IRValue lessOperator(IRValue &lhs, IRValue &rhs) {
    return cmpEqImpl<T>(lhs, rhs, std::less<T>());
}

IRValue IRValue::operator<(IRValue &rhs) { BinaryOperatorImpl(lessOperator); }

template <typename T>
static IRValue greaterOperator(IRValue &lhs, IRValue &rhs) {
    return cmpEqImpl<T>(lhs, rhs, std::greater<T>());
}

IRValue IRValue::operator>(IRValue &rhs) {
    BinaryOperatorImpl(greaterOperator);
}

template <typename T>
static IRValue lessEqualOperator(IRValue &lhs, IRValue &rhs) {
    return cmpEqImpl<T>(lhs, rhs, std::less_equal<T>());
}

IRValue IRValue::operator<=(IRValue &rhs) {
    BinaryOperatorImpl(lessEqualOperator);
}

template <typename T>
static IRValue greaterEqualOperator(IRValue &lhs, IRValue &rhs) {
    return cmpEqImpl<T>(lhs, rhs, std::greater_equal<T>());
}

IRValue IRValue::operator>=(IRValue &rhs) {
    BinaryOperatorImpl(greaterEqualOperator);
}

template <typename T> static IRValue equalOperator(IRValue &lhs, IRValue &rhs) {
    return cmpEqImpl<T>(lhs, rhs, std::equal_to<T>());
}

IRValue IRValue::operator==(IRValue &rhs) { BinaryOperatorImpl(equalOperator); }

template <typename T>
static IRValue notEqualOperator(IRValue &lhs, IRValue &rhs) {
    return cmpEqImpl<T>(lhs, rhs, std::not_equal_to<T>());
}

IRValue IRValue::operator!=(IRValue &rhs) {
    BinaryOperatorImpl(notEqualOperator);
}

//////////////////////////////////////////////////////////////////////////////

static IRValue logicalAndOrImpl(IRValue &lhs, IRValue &rhs,
                                std::function<bool(bool &, bool &)> op) {
    if (rhs.getIntTypeID() != lhs.getIntTypeID())
        ERROR("Can perform operation only on IRValues with the same IntTypeID");
    if (lhs.getIntTypeID() != IntTypeID::BOOL)
        ERROR("Logical And/Or expressions are defined only for bool values");

    IRValue ret(IntTypeID::BOOL);
    ret.getValueRef<bool>() =
        op(lhs.getValueRef<bool>(), rhs.getValueRef<bool>());
    return ret;
}

IRValue logicalAndOperator(IRValue &lhs, IRValue &rhs) {
    return logicalAndOrImpl(lhs, rhs, std::logical_and<>());
}

IRValue logicalOrOperator(IRValue &lhs, IRValue &rhs) {
    return logicalAndOrImpl(lhs, rhs, std::logical_or<>());
}

IRValue IRValue::operator&&(IRValue &rhs) {
    return {logicalAndOperator(*this, rhs)};
}

IRValue IRValue::operator||(IRValue &rhs) {
    return {logicalOrOperator(*this, rhs)};
}

//////////////////////////////////////////////////////////////////////////////

template <typename T>
static IRValue bitwiseAndOrXorImpl(IRValue &lhs, IRValue &rhs,
                                   std::function<T(T &, T &)> op) {
    if (rhs.getIntTypeID() != lhs.getIntTypeID())
        ERROR("Can perform operation only on IRValues with the same IntTypeID");

    IRValue ret(rhs.getIntTypeID());
    ret.getValueRef<T>() = op(lhs.getValueRef<T>(), rhs.getValueRef<T>());
    return ret;
}

template <typename T>
static IRValue bitwiseAndOperator(IRValue &lhs, IRValue &rhs) {
    return bitwiseAndOrXorImpl<T>(lhs, rhs, std::bit_and<T>());
}

IRValue IRValue::operator&(IRValue &rhs) {
    BinaryOperatorImpl(bitwiseAndOperator);
}

template <typename T>
static IRValue bitwiseOrOperator(IRValue &lhs, IRValue &rhs) {
    return bitwiseAndOrXorImpl<T>(lhs, rhs, std::bit_or<T>());
}

IRValue IRValue::operator|(IRValue &rhs) {
    BinaryOperatorImpl(bitwiseOrOperator);
}

template <typename T>
static IRValue bitwiseXorOperator(IRValue &lhs, IRValue &rhs) {
    return bitwiseAndOrXorImpl<T>(lhs, rhs, std::bit_xor<T>());
}

IRValue IRValue::operator^(IRValue &rhs) {
    BinaryOperatorImpl(bitwiseXorOperator);
}

//////////////////////////////////////////////////////////////////////////////

template <typename T, typename U>
static IRValue shiftOperatorCommonChecks(IRValue &lhs, IRValue &rhs) {
    IRValue ret(lhs.getIntTypeID());

    if (std::is_signed<U>::value && rhs.getValueRef<U>() < 0) {
        ret.setUBCode(UBKind::ShiftRhsNeg);
        return ret;
    }

    size_t lhs_bit_size = sizeof(T) * CHAR_BIT;
    if (rhs.getValueRef<U>() >= static_cast<U>(lhs_bit_size)) {
        ret.setUBCode(UBKind::ShiftRhsLarge);
        return ret;
    }

    return ret;
}

template <typename T, typename U>
static IRValue leftShiftOperator(IRValue &lhs, IRValue &rhs) {
    IRValue ret = shiftOperatorCommonChecks<T, U>(lhs, rhs);

    if (ret.getUBCode() != UBKind::NoUB)
        return ret;

    if (std::is_signed<T>::value && lhs.getValueRef<T>() < 0) {
        ret.setUBCode(UBKind::NegShift);
        return ret;
    }

    size_t lhs_bit_size = sizeof(T) * CHAR_BIT;
    if (std::is_signed<T>::value) {
        size_t max_avail_shift = lhs_bit_size - findMSB(lhs.getValueRef<T>());
        if (rhs.getValueRef<U>() > static_cast<U>(max_avail_shift)) {
            ret.setUBCode(UBKind::ShiftRhsLarge);
            return ret;
        }
    }

    assert(ret.getUBCode() == UBKind::NoUB &&
           "Ret can't has an UB. All of the cases should be handled earlier.");
    ret.getValueRef<T>() = lhs.getValueRef<T>() << rhs.getValueRef<U>();
    return ret;
}

IRValue IRValue::operator<<(IRValue &rhs) {
    ShiftOperatorImpl(leftShiftOperator);
}

template <typename T, typename U>
static IRValue rightShiftOperator(IRValue &lhs, IRValue &rhs) {
    IRValue ret = shiftOperatorCommonChecks<T, U>(lhs, rhs);

    if (ret.getUBCode() != UBKind::NoUB)
        return ret;

    if (std::is_signed<T>::value && lhs.getValueRef<T>() < 0) {
        // TODO: it is implementation-defined!
        ret.setUBCode(UBKind::NegShift);
        return ret;
    }

    assert(ret.getUBCode() == UBKind::NoUB &&
           "Ret can't has an UB. All of the cases should be handled earlier.");
    ret.getValueRef<T>() = lhs.getValueRef<T>() >> rhs.getValueRef<U>();
    return ret;
}

IRValue IRValue::operator>>(IRValue &rhs) {
    ShiftOperatorImpl(rightShiftOperator);
}