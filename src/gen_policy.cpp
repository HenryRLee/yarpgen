/*
Copyright (c) 2015-2020, Intel Corporation
Copyright (c) 2019-2020, University of Utah

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

#include "gen_policy.h"
#include "options.h"

using namespace yarpgen;

size_t GenPolicy::leaves_prob_bump = 30;

template <typename T>
static void shuffleProbProxy(std::vector<Probability<T>> &vec) {
    Options &options = Options::getInstance();
    if (!options.getUseParamShuffle())
        return;
    rand_val_gen->shuffleProb(vec);
}

GenPolicy::GenPolicy() {
    Options &options = Options::getInstance();

    stmt_num_lim = 1000;

    loop_seq_num_lim = 4;
    uniformProbFromMax(loop_seq_num_distr, loop_seq_num_lim, 1);

    loop_nest_depth_lim = 3;
    uniformProbFromMax(loop_nest_depth_distr, loop_nest_depth_lim, 2);

    loop_depth_limit = 5;

    if_else_depth_limit = 5;

    scope_stmt_min_num = 2;
    scope_stmt_max_num = 5;
    uniformProbFromMax(scope_stmt_num_distr, scope_stmt_max_num,
                       scope_stmt_min_num);

    min_iters_num = 1;
    max_iters_num = 1;
    uniformProbFromMax(iters_num_distr, max_iters_num, min_iters_num);

    iters_end_limit_min = 10;
    iter_end_limit_max = 25;
    iters_step_distr.emplace_back(Probability<size_t>{1, 10});
    iters_step_distr.emplace_back(Probability<size_t>{2, 10});
    iters_step_distr.emplace_back(Probability<size_t>{4, 10});

    if (!options.isSYCL()) {
        stmt_kind_struct_distr.emplace_back(
            Probability<IRNodeKind>{IRNodeKind::LOOP_SEQ, 10});
        stmt_kind_struct_distr.emplace_back(
            Probability<IRNodeKind>{IRNodeKind::LOOP_NEST, 10});
    }
    stmt_kind_struct_distr.emplace_back(
        Probability<IRNodeKind>{IRNodeKind::IF_ELSE, 10});
    stmt_kind_struct_distr.emplace_back(
        Probability<IRNodeKind>{IRNodeKind::STUB, 70});
    shuffleProbProxy(stmt_kind_struct_distr);

    else_br_distr.emplace_back(Probability<bool>{true, 20});
    else_br_distr.emplace_back(Probability<bool>{false, 80});
    shuffleProbProxy(else_br_distr);

    int_type_distr.emplace_back(Probability<IntTypeID>(IntTypeID::BOOL, 10));
    int_type_distr.emplace_back(Probability<IntTypeID>(IntTypeID::SCHAR, 10));
    int_type_distr.emplace_back(Probability<IntTypeID>(IntTypeID::UCHAR, 10));
    int_type_distr.emplace_back(Probability<IntTypeID>(IntTypeID::SHORT, 10));
    int_type_distr.emplace_back(Probability<IntTypeID>(IntTypeID::USHORT, 10));
    int_type_distr.emplace_back(Probability<IntTypeID>(IntTypeID::INT, 10));
    int_type_distr.emplace_back(Probability<IntTypeID>(IntTypeID::UINT, 10));
    int_type_distr.emplace_back(Probability<IntTypeID>(IntTypeID::LLONG, 10));
    int_type_distr.emplace_back(Probability<IntTypeID>(IntTypeID::ULLONG, 10));
    shuffleProbProxy(int_type_distr);

    min_inp_vars_num = 10;
    max_inp_vars_num = 20;

    stmt_kind_pop_distr.emplace_back(
        Probability<IRNodeKind>(IRNodeKind::ASSIGN, 20));

    min_new_arr_num = 2;
    max_new_arr_num = 4;
    uniformProbFromMax(new_arr_num_distr, max_new_arr_num, min_new_arr_num);

    out_kind_distr.emplace_back(Probability<DataKind>(DataKind::VAR, 20));
    out_kind_distr.emplace_back(Probability<DataKind>(DataKind::ARR, 20));
    shuffleProbProxy(out_kind_distr);

    max_arith_depth = 3;

    arith_node_distr.emplace_back(
        Probability<IRNodeKind>(IRNodeKind::CONST, 10));
    arith_node_distr.emplace_back(
        Probability<IRNodeKind>(IRNodeKind::SCALAR_VAR_USE, 10));
    arith_node_distr.emplace_back(
        Probability<IRNodeKind>(IRNodeKind::SUBSCRIPT, 10));
    arith_node_distr.emplace_back(
        Probability<IRNodeKind>(IRNodeKind::TYPE_CAST, 20));
    arith_node_distr.emplace_back(
        Probability<IRNodeKind>(IRNodeKind::UNARY, 20));
    arith_node_distr.emplace_back(
        Probability<IRNodeKind>(IRNodeKind::BINARY, 20));
    if (!options.isSYCL())
        arith_node_distr.emplace_back(
            Probability<IRNodeKind>(IRNodeKind::CALL, 20));
    arith_node_distr.emplace_back(
        Probability<IRNodeKind>(IRNodeKind::TERNARY, 20));
    shuffleProbProxy(arith_node_distr);

    unary_op_distr.emplace_back(Probability<UnaryOp>(UnaryOp::PLUS, 25));
    unary_op_distr.emplace_back(Probability<UnaryOp>(UnaryOp::NEGATE, 25));
    unary_op_distr.emplace_back(Probability<UnaryOp>(UnaryOp::LOG_NOT, 25));
    unary_op_distr.emplace_back(Probability<UnaryOp>(UnaryOp::BIT_NOT, 25));
    shuffleProbProxy(unary_op_distr);

    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::ADD, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::SUB, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::MUL, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::DIV, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::MOD, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::LT, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::GT, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::LE, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::GE, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::EQ, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::NE, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::LOG_AND, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::LOG_OR, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::BIT_AND, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::BIT_OR, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::BIT_XOR, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::SHL, 10));
    binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::SHR, 10));
    shuffleProbProxy(binary_op_distr);

    foreach_distr.emplace_back(Probability<bool>(true, 20));
    foreach_distr.emplace_back(Probability<bool>(false, 80));
    shuffleProbProxy(foreach_distr);

    cxx_lib_call_distr.emplace_back(
        Probability<LibCallKind>(LibCallKind::MAX, 20));
    cxx_lib_call_distr.emplace_back(
        Probability<LibCallKind>(LibCallKind::MIN, 20));
    shuffleProbProxy(cxx_lib_call_distr);

    ispc_lib_call_distr.emplace_back(
        Probability<LibCallKind>(LibCallKind::MAX, 20));
    ispc_lib_call_distr.emplace_back(
        Probability<LibCallKind>(LibCallKind::MIN, 20));
    ispc_lib_call_distr.emplace_back(
        Probability<LibCallKind>(LibCallKind::SELECT, 20));
    ispc_lib_call_distr.emplace_back(
        Probability<LibCallKind>(LibCallKind::ANY, 20));
    ispc_lib_call_distr.emplace_back(
        Probability<LibCallKind>(LibCallKind::ALL, 20));
    ispc_lib_call_distr.emplace_back(
        Probability<LibCallKind>(LibCallKind::NONE, 20));
    ispc_lib_call_distr.emplace_back(
        Probability<LibCallKind>(LibCallKind::RED_MIN, 20));
    ispc_lib_call_distr.emplace_back(
        Probability<LibCallKind>(LibCallKind::RED_MAX, 20));
    ispc_lib_call_distr.emplace_back(
        Probability<LibCallKind>(LibCallKind::RED_EQ, 20));
    ispc_lib_call_distr.emplace_back(
        Probability<LibCallKind>(LibCallKind::EXTRACT, 20));
    shuffleProbProxy(ispc_lib_call_distr);

    loop_end_kind_distr.emplace_back(
        Probability<LoopEndKind>(LoopEndKind::CONST, 30));
    loop_end_kind_distr.emplace_back(
        Probability<LoopEndKind>(LoopEndKind::VAR, 30));
    loop_end_kind_distr.emplace_back(
        Probability<LoopEndKind>(LoopEndKind::EXPR, 30));
    shuffleProbProxy(loop_end_kind_distr);

    uniformProbFromMax(pragma_num_distr,
                       static_cast<int>(PragmaKind::MAX_CLANG_PRAGMA_KIND) - 1,
                       static_cast<size_t>(PragmaKind::CLANG_VECTORIZE));

    pragma_kind_distr.emplace_back(
        Probability<PragmaKind>(PragmaKind::CLANG_VECTORIZE, 25));
    pragma_kind_distr.emplace_back(
        Probability<PragmaKind>(PragmaKind::CLANG_INTERLEAVE, 25));
    pragma_kind_distr.emplace_back(
        Probability<PragmaKind>(PragmaKind::CLANG_VEC_PREDICATE, 25));
    pragma_kind_distr.emplace_back(
        Probability<PragmaKind>(PragmaKind::CLANG_UNROLL, 25));
    shuffleProbProxy(pragma_kind_distr);

    active_similar_op = SimilarOperators::MAX_SIMILAR_OP;

    apply_similar_op_distr.emplace_back(Probability<bool>(true, 10));
    apply_similar_op_distr.emplace_back(Probability<bool>(false, 90));
    shuffleProbProxy(apply_similar_op_distr);

    similar_op_distr.emplace_back(
        Probability<SimilarOperators>(SimilarOperators::ADDITIVE, 10));
    similar_op_distr.emplace_back(
        Probability<SimilarOperators>(SimilarOperators::BITWISE, 10));
    similar_op_distr.emplace_back(
        Probability<SimilarOperators>(SimilarOperators::LOGIC, 10));
    similar_op_distr.emplace_back(
        Probability<SimilarOperators>(SimilarOperators::MULTIPLICATIVE, 10));
    similar_op_distr.emplace_back(
        Probability<SimilarOperators>(SimilarOperators::BIT_SH, 10));
    similar_op_distr.emplace_back(
        Probability<SimilarOperators>(SimilarOperators::ADD_MUL, 10));
    shuffleProbProxy(similar_op_distr);

    active_const_use = ConstUse::MAX_CONST_USE;

    apply_const_use_distr.emplace_back(Probability<bool>(true, 10));
    apply_const_use_distr.emplace_back(Probability<bool>(false, 90));
    shuffleProbProxy(apply_const_use_distr);

    const_use_distr.emplace_back(Probability<ConstUse>(ConstUse::HALF, 50));
    const_use_distr.emplace_back(Probability<ConstUse>(ConstUse::ALL, 50));
    shuffleProbProxy(const_use_distr);

    use_special_const_distr.emplace_back(Probability<bool>(true, 30));
    use_special_const_distr.emplace_back(Probability<bool>(false, 70));
    shuffleProbProxy(use_special_const_distr);

    special_const_distr.emplace_back(
        Probability<SpecialConst>(SpecialConst::ZERO, 10));
    special_const_distr.emplace_back(
        Probability<SpecialConst>(SpecialConst::MIN, 10));
    special_const_distr.emplace_back(
        Probability<SpecialConst>(SpecialConst::MAX, 10));
    special_const_distr.emplace_back(
        Probability<SpecialConst>(SpecialConst::BIT_BLOCK, 10));
    special_const_distr.emplace_back(
        Probability<SpecialConst>(SpecialConst::END_BITS, 10));
    shuffleProbProxy(special_const_distr);

    use_lsb_bit_end_distr.emplace_back(Probability<bool>(true, 50));
    use_lsb_bit_end_distr.emplace_back(Probability<bool>(false, 50));
    shuffleProbProxy(use_lsb_bit_end_distr);

    use_const_offset_distr.emplace_back(Probability<bool>(true, 50));
    use_const_offset_distr.emplace_back(Probability<bool>(false, 50));
    shuffleProbProxy(use_const_offset_distr);

    min_offset = 1;
    max_offset = 32;
    uniformProbFromMax(const_offset_distr, max_offset, min_offset);

    pos_const_offset_distr.emplace_back(Probability<bool>(true, 50));
    pos_const_offset_distr.emplace_back(Probability<bool>(false, 50));
    shuffleProbProxy(pos_const_offset_distr);

    replace_in_buf_distr.emplace_back(Probability<bool>(true, 50));
    replace_in_buf_distr.emplace_back(Probability<bool>(false, 50));
    shuffleProbProxy(replace_in_buf_distr);

    reuse_const_prob.emplace_back(Probability<bool>(true, 30));
    reuse_const_prob.emplace_back(Probability<bool>(false, 70));
    shuffleProbProxy(reuse_const_prob);

    use_const_transform_distr.emplace_back(Probability<bool>(true, 50));
    use_const_transform_distr.emplace_back(Probability<bool>(false, 50));
    shuffleProbProxy(use_const_offset_distr);

    const_transform_distr.emplace_back(
        Probability<UnaryOp>(UnaryOp::NEGATE, 30));
    const_transform_distr.emplace_back(
        Probability<UnaryOp>(UnaryOp::BIT_NOT, 30));
    shuffleProbProxy(const_transform_distr);
}

size_t yarpgen::GenPolicy::const_buf_size = 10;

void GenPolicy::chooseAndApplySimilarOp() {
    if (active_similar_op != SimilarOperators::MAX_SIMILAR_OP)
        return;
    active_similar_op = rand_val_gen->getRandId(similar_op_distr);
    binary_op_distr.clear();
    unary_op_distr.clear();
    if (active_similar_op == SimilarOperators::ADDITIVE ||
        active_similar_op == SimilarOperators::ADD_MUL) {
        unary_op_distr.emplace_back(Probability<UnaryOp>(UnaryOp::PLUS, 10));
        unary_op_distr.emplace_back(Probability<UnaryOp>(UnaryOp::NEGATE, 10));
        binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::ADD, 10));
        binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::SUB, 10));
        if (active_similar_op == SimilarOperators::ADD_MUL) {
            binary_op_distr.emplace_back(
                Probability<BinaryOp>(BinaryOp::MUL, 10));
            binary_op_distr.emplace_back(
                Probability<BinaryOp>(BinaryOp::DIV, 10));
        }
    }
    if (active_similar_op == SimilarOperators::MULTIPLICATIVE) {
        unary_op_distr.emplace_back(Probability<UnaryOp>(UnaryOp::PLUS, 10));
        unary_op_distr.emplace_back(Probability<UnaryOp>(UnaryOp::NEGATE, 10));
        binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::MUL, 10));
        binary_op_distr.emplace_back(Probability<BinaryOp>(BinaryOp::DIV, 10));
    }
    if (active_similar_op == SimilarOperators::BITWISE ||
        active_similar_op == SimilarOperators::BIT_SH) {
        unary_op_distr.emplace_back(Probability<UnaryOp>(UnaryOp::BIT_NOT, 10));
        binary_op_distr.emplace_back(
            Probability<BinaryOp>(BinaryOp::BIT_AND, 10));
        binary_op_distr.emplace_back(
            Probability<BinaryOp>(BinaryOp::BIT_OR, 10));
        binary_op_distr.emplace_back(
            Probability<BinaryOp>(BinaryOp::BIT_XOR, 10));
        if (active_similar_op == SimilarOperators::BIT_SH) {
            binary_op_distr.emplace_back(
                Probability<BinaryOp>(BinaryOp::SHL, 10));
            binary_op_distr.emplace_back(
                Probability<BinaryOp>(BinaryOp::SHR, 10));
        }
    }
    if (active_similar_op == SimilarOperators::LOGIC) {
        unary_op_distr.emplace_back(Probability<UnaryOp>(UnaryOp::LOG_NOT, 10));
        binary_op_distr.emplace_back(
            Probability<BinaryOp>(BinaryOp::LOG_AND, 10));
        binary_op_distr.emplace_back(
            Probability<BinaryOp>(BinaryOp::LOG_OR, 10));
    }
}

void GenPolicy::chooseAndApplyConstUse() {
    if (active_const_use != ConstUse::MAX_CONST_USE)
        return;
    active_const_use = rand_val_gen->getRandId(const_use_distr);
    if (active_const_use == ConstUse::ALL) {
        arith_node_distr.clear();
        arith_node_distr.emplace_back(
            Probability<IRNodeKind>(IRNodeKind::CONST, 100));
    }
    else if (active_const_use == ConstUse::HALF) {
        size_t sum = 0;
        auto &vec = arith_node_distr;
        std::for_each(vec.begin(), vec.end(),
                      [&](Probability<IRNodeKind> n) { sum += n.getProb(); });
        auto search_func = [](Probability<IRNodeKind> n) -> bool {
            return n.getId() == IRNodeKind::CONST;
        };
        if (auto find_res = std::find_if(vec.begin(), vec.end(), search_func) !=
                            vec.end()) {
            sum -= vec.at(find_res).getProb();
            vec.erase(vec.begin() + find_res);
        }
        arith_node_distr.emplace_back(
            Probability<IRNodeKind>(IRNodeKind::CONST, sum));
    }
}

template <typename T>
void GenPolicy::uniformProbFromMax(std::vector<Probability<T>> &distr,
                                   size_t max_num, size_t min_num) {
    distr.reserve(max_num - min_num);
    for (size_t i = min_num; i <= max_num; ++i)
        distr.emplace_back(i, (max_num - i + 1) * 10);
}
