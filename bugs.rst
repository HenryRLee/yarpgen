====================================
LLVM:
====================================
Version #2
---------------
| `46525 <https://bugs.llvm.org/show_bug.cgi?id=46525>`_ - ICE: Assertion \`!verifyFunction(\*L->getHeader()->getParent())' failed
| `46471 <https://bugs.llvm.org/show_bug.cgi?id=46471>`_ - [CodeGenPrepare] Assertion \`materialized_use_empty() && "Uses remain when a value is destroyed!"' failed
| `46178 <https://bugs.llvm.org/show_bug.cgi?id=46178>`_ - Assertion \`idx < size()' failed in combineX86ShufflesRecursively with -O3 -march=skx

Loop-targeting prototype
-------------------------
| `42833 <https://bugs.llvm.org/show_bug.cgi?id=42833>`_ - Incorrect result with -O3 -march=skx
| `42819 <https://bugs.llvm.org/show_bug.cgi?id=42819>`_ - ICE: "Cannot select: X86ISD::SUBV_BROADCAST" with -O3 -march=skx

Version #1
---------------
| `35583 <https://bugs.llvm.org/show_bug.cgi?id=35583>`_ - NewGVN indeterministic crash
| `35272 <https://bugs.llvm.org/show_bug.cgi?id=35272>`_ - [AVX512] Assertion "Invalid sext node, dst < src!" in llvm::SelectionDAG::getNode()
| `34959 <https://bugs.llvm.org/show_bug.cgi?id=34959>`_ - Incorrect predication in SKX, opt-bisect blames SLP Vectorizer
| `34947 <https://bugs.llvm.org/show_bug.cgi?id=34947>`_ - -O0 crash: assertion "Cannot BITCAST between types of different sizes!"
| `34934 <https://bugs.llvm.org/show_bug.cgi?id=34934>`_ - UNREACHABLE at LegalizeDAG.cpp: "Unexpected request for libcall!" (x86_64, SKX)
| `34856 <https://bugs.llvm.org/show_bug.cgi?id=34856>`_ - Assertion on vector code: "Invalid constantexpr cast!"
| `34855 <https://bugs.llvm.org/show_bug.cgi?id=34855>`_ - Cannot select shl and srl for v2i64
| `34841 <https://bugs.llvm.org/show_bug.cgi?id=34841>`_ - InstCombine - Assertion "Cannot convert from scalar to/from vector"
| `34838 <https://bugs.llvm.org/show_bug.cgi?id=34838>`_ - InstCombine - Assertion "Compare known true or false was not folded"
| `34837 <https://bugs.llvm.org/show_bug.cgi?id=34837>`_ - UNREACHABLE in DAGTypeLegalizer::PromoteIntegerResult
| `34830 <https://bugs.llvm.org/show_bug.cgi?id=34830>`_ - Clang failing with "Cannot emit physreg copy instruction"
| `34828 <https://bugs.llvm.org/show_bug.cgi?id=34828>`_ - Assertion in VirtRegRewriter: \`toIndex_(n) < storage\_.size() && "index out of bounds!"'
| `34787 <https://bugs.llvm.org/show_bug.cgi?id=34787>`_ - Assertion \`TN->getNumChildren() == 0 && "Not a tree leaf"'
| `34782 <https://bugs.llvm.org/show_bug.cgi?id=34782>`_ - Assertion "Deleted edge still exists in the CFG!"
| `34381 <https://bugs.llvm.org/show_bug.cgi?id=34381>`_ - Clang produces incorrect code at -O0
| `34377 <https://bugs.llvm.org/show_bug.cgi?id=34377>`_ - Clang produces incorrect code with -O1 and higher
| `34137 <https://bugs.llvm.org/show_bug.cgi?id=34137>`_ - clang crash in llvm::SelectionDAG::Combine on -O0
| `33844 <https://bugs.llvm.org/show_bug.cgi?id=33844>`_ - Assertion \`loBit <= BitWidth && "loBit out of range"' failed with -O1
| `33828 <https://bugs.llvm.org/show_bug.cgi?id=33828>`_ - Crash in X86DAGToDAGISel::RunSDNodeXForm: "getConstant with a uint64_t value that doesn't fit in the type!"
| `33765 <https://bugs.llvm.org/show_bug.cgi?id=33765>`_ - Replacing instructions in instcombine violates dominance relation
| `33695 <https://bugs.llvm.org/show_bug.cgi?id=33695>`_ - Bit-Tracking Dead Code Elimination (BDCE) fails to invalidate nsw/nuw after transforms
| `33560 <https://bugs.llvm.org/show_bug.cgi?id=33560>`_ - "Cannot emit physreg copy instruction" at lib/Target/X86/X86InstrInfo.cpp:6707
| `33442 <https://bugs.llvm.org/show_bug.cgi?id=33442>`_ - UBSAN: right shift by negative value is not caught for some values
| `33133 <https://bugs.llvm.org/show_bug.cgi?id=33133>`_ - UBSan misses check for "negative_value << 0"
| `32894 <https://bugs.llvm.org/show_bug.cgi?id=32894>`_ - ICE: "Cannot replace uses of with self" in llvm::SelectionDAG::ReplaceAllUsesWith
| `32830 <https://bugs.llvm.org/show_bug.cgi?id=32830>`_ - Clang produces incorrect code with -O2 and higher
| `32525 <https://bugs.llvm.org/show_bug.cgi?id=32525>`_ - Assertion is hit: "The number of nodes scheduled doesn't match the expected number!"
| `32515 <https://bugs.llvm.org/show_bug.cgi?id=32515>`_ - Assertion "DELETED_NODE in CSEMap!" fires a lot with -march=skx
| `32345 <https://bugs.llvm.org/show_bug.cgi?id=32345>`_ - Assertion \`Op.getScalarValueSizeInBits() == BitWidth && "Mask size mismatches value type size!"' failed with -O0.
| `32340 <https://bugs.llvm.org/show_bug.cgi?id=32340>`_ - Assertion \`N->getOpcode() != ISD::DELETED_NODE && "Deleted Node added to Worklist"' failed with -O0
| `32329 <https://bugs.llvm.org/show_bug.cgi?id=32329>`_ - Silent failure in X86 DAG->DAG Instruction Selection with -march=skx -O3
| `32316 <https://bugs.llvm.org/show_bug.cgi?id=32316>`_ - Assertion \`N1.getValueType() == N2.getValueType() && N1.getValueType() == VT && "Binary operator types must match!"' failed with -O1 -march=skx
| `32284 <https://bugs.llvm.org/show_bug.cgi?id=32284>`_ - Assertion \`Num < NumOperands && "Invalid child # of SDNode!"' failed with -O0 -march=skx.
| `32256 <https://bugs.llvm.org/show_bug.cgi?id=32256>`_ - Assertion \`!isHReg(DestReg) && "Cannot move between mask and h-reg"' failed with -m32 -O0 -march=skx.
| `32241 <https://bugs.llvm.org/show_bug.cgi?id=32241>`_ - Incorrect result with -march=skx -O0 -m32.
| `31306 <https://bugs.llvm.org/show_bug.cgi?id=31306>`_ - [AVX-512] Compiler crash: Cannot select: t41: v8i64 = X86ISD::SUBV_BROADCAST
| `31045 <https://bugs.llvm.org/show_bug.cgi?id=31045>`_ - Clang fails in insertDAGNode
| `31044 <https://bugs.llvm.org/show_bug.cgi?id=31044>`_ - Assertion \`Index.getValueType() == MVT::i32 && "Expect to be extending 32-bit registers for use in LEA"' failed
| `30813 <https://bugs.llvm.org/show_bug.cgi?id=30813>`_ - Assertion \`ShiftBits != 0 && MaskBits <= Size' failed.
| `30783 <https://bugs.llvm.org/show_bug.cgi?id=30783>`_ - Assertion \`New->getType() == getType() && "replaceAllUses of value with new value of different type!"' failed
| `30777 <https://bugs.llvm.org/show_bug.cgi?id=30777>`_ - Assertion \`DestBits == SrcBits && "Illegal cast to vector (wrong type or size)"' failed
| `30775 <https://bugs.llvm.org/show_bug.cgi?id=30775>`_ - Assertion \`NodeToMatch->getOpcode() != ISD::DELETED_NODE && "NodeToMatch was removed partway through selection"' failed.
| `30693 <https://bugs.llvm.org/show_bug.cgi?id=30693>`_ - AVX512 Segfault: alignment incorrect for relative addressing
| `30286 <https://bugs.llvm.org/show_bug.cgi?id=30286>`_ - [AVX-512] KNL bug at -O0
| `30256 <https://bugs.llvm.org/show_bug.cgi?id=30256>`_ - Assert in llvm::ReassociatePass::OptimizeAdd
| `29058 <https://bugs.llvm.org/show_bug.cgi?id=29058>`_ - Assert in llvm::SelectionDAG::Legalize()
| `28845 <https://bugs.llvm.org/show_bug.cgi?id=28845>`_ - Incorrect codegen for "store <2 x i48>" triggered by -fslp-vectorize-aggressive
| `28661 <https://bugs.llvm.org/show_bug.cgi?id=28661>`_ - [AVX512] incorrect code for boolean expression at -O0.
| `28313 <https://bugs.llvm.org/show_bug.cgi?id=28313>`_ - LLVM trunk crash with knl target (Assertion \`isSCEVable(V->getType()))
| `28312 <https://bugs.llvm.org/show_bug.cgi?id=28312>`_ - LLVM trunk crash with knl target (Assertion \`Res.getValueType() == N->getValueType(0))
| `28301 <https://bugs.llvm.org/show_bug.cgi?id=28301>`_ - Clang trunk ICE (Assertion \`Removed && "Register is not used by this instruction!)
| `28291 <https://bugs.llvm.org/show_bug.cgi?id=28291>`_ - LLVM trunk crash with knl target (Assertion \`C1->getType() == C2->getType())
| `28119 <https://bugs.llvm.org/show_bug.cgi?id=28119>`_ - [AVX-512] llc crash with UNREACHABLE executed at lib/IR/ValueTypes.cpp:128
| `27997 <https://bugs.llvm.org/show_bug.cgi?id=27997>`_ - ICE on trunk Clang, knl target, Assertion \`L.isLCSSAForm(DT)' failed
| `27879 <https://bugs.llvm.org/show_bug.cgi?id=27879>`_ - ICE on trunk llvm (Invalid operands for select instruction)
| `27873 <https://bugs.llvm.org/show_bug.cgi?id=27873>`_ - ICE in llvm::TargetLowering::SimplifyDemandedBits on knl
| `27789 <https://bugs.llvm.org/show_bug.cgi?id=27789>`_ - Clang trunk crashes on knl target
| `27638 <https://bugs.llvm.org/show_bug.cgi?id=27638>`_ - ICE in llvm::SDValue llvm::X86TargetLowering::LowerSETCC
| `27591 <https://bugs.llvm.org/show_bug.cgi?id=27591>`_ - Clang crash with KNL target, Assertion \`Emitted && "Failed to emit a zext!"' failed
| `27584 <https://bugs.llvm.org/show_bug.cgi?id=27584>`_ - LLVM trunk crash with knl target
| `25519 <https://bugs.llvm.org/show_bug.cgi?id=25519>`_ - [AVX-512] llc generates incorrect code
| `25518 <https://bugs.llvm.org/show_bug.cgi?id=25518>`_ - [AVX-512] llc generates incorrect code
| `25517 <https://bugs.llvm.org/show_bug.cgi?id=25517>`_ - [AVX-512] llc generates incorrect code

====================================
GCC:
====================================

Version #2
---------------
| `95916 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95916>`_ - [11 Regression] ICE during GIMPLE pass: slp : verify_ssa failed
| `95717 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95717>`_ - [9/10 Regression] ICE during GIMPLE pass: vect: verify_ssa failed since r9-5325-gf25507d041de4df6
| `95649 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95649>`_ - [11 Regression] ICE during GIMPLE pass: cunroll since r11-1146-g1396fa5b91cfa0b3
| `95487 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95487>`_ - [10 Regression] ICE: verify_gimple failed (error: invalid vector types in nop conversion) with -O3 -march=skylake-avx512 since r10-1052-gc29c92c789d93848
| `95401 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95401>`_ - [10/11 Regression] GCC produces incorrect instruction with -O3 for AVX2 since r10-2257-g868363d4f52df19d
| `95396 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95396>`_ - [8/9/10/11 Regression] GCC produces incorrect code with -O3 for loops since r8-6511-g3ae129323d150621
| `95308 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95308>`_ - [10 Regression] ICE: in maybe_canonicalize_mem_ref_addr with -O3 -march=skylake-avx512 since r10-4203-g97c146036750e7cb
| `95297 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95297>`_ - ICE: Segmentation fault
| `95295 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95295>`_ - g++ produces incorrect code with -O3 for loops
| `95284 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95284>`_ - ICE: verify_gimple failed
| `95268 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95268>`_ - ICE: invalid ‘PHI’ argument
| `95248 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95248>`_ - [11 Regression] GCC produces incorrect code with -O3 for loops since r11-272-gb6ff3ddecfa93d53
| `94727 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=94727>`_ - [10 Regression] GCC produces incorrect code with -O3 since r10-5071-g02d895504cc59be0

Loop-targeting prototype
-------------------------
| `91403 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=91403>`_ - GCC fails with ICE.
| `91293 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=91293>`_ - [8 Regression] Wrong code with -O3 -mavx2
| `91240 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=91240>`_ - [8/9/10 Regression] Wrong code with -O3 due to unroll and jam pass
| `91207 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=91207>`_ - [10 Regression] Wrong code with -O3
| `91204 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=91204>`_ - [10 Regression] ICE in expand_expr_real_2, at expr.c:9215 with -O3
| `91178 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=91178>`_ - [9 Regression] Infinite recursion in split_constant_offset in slp after r260289
| `91145 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=91145>`_ - [9 Regression] ICE: in vect_build_slp_tree_2, at tree-vect-slp.c:1143 with -march=skylake-avx512 -O3
| `91137 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=91137>`_ - [7 Regression] Wrong code with -O3

Version #1
---------------
| `83383 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=83383>`_ - Wrong code with a bunch of type conversion and ternary operators
| `83382 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=83382>`_ - UBSAN tiggers false-positive warning [-Werror=uninitialized]
| `83252 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=83252>`_ - [8 Regression] Wrong code with "-march=skylake-avx512 -O3"
| `83221 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=83221>`_ - [8 Regression] qsort comparator not anti-commutative: -2147483648, -2147483648
| `82778 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82778>`_ - crash: insn does not satisfy its constraints
| `82576 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82576>`_ - sbitmap_vector_alloc() not ready for 64 bits
| `82413 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82413>`_ - [8 Regression] -O0 crash (ICE in decompose, at tree.h:5179)
| `82381 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82381>`_ - [8 Regression] internal compiler error: qsort checking failed
| `82353 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82353>`_ - [8 Regression] runtime ubsan crash
| `82192 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82192>`_ - [5/6/7/8 Regression] gcc produces incorrect code with -O2 and bit-field
| `82073 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82073>`_ - internal compiler error: in pop_to_marker, at tree-ssa-scopedtables.c
| `81987 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81987>`_ - [8 Regression] ICE in verify_ssa with -O3 -march=skylake-avx512
| `81814 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81814>`_ - [5/6/7 Regression] Incorrect behaviour at -O0 (conditional operator)
| `81705 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81705>`_ - [8 Regression] UBSAN: yet another false positive
| `81607 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81607>`_ - [6 Regression] Conditional operator: "type mismatch in shift expression" error
| `81588 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81588>`_ - [7/8 Regression] Wrong code at -O2
| `81556 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81556>`_ - [7/8 Regression] Wrong code at -O2
| `81555 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81555>`_ - [5/6/7/8 Regression] Wrong code at -O1
| `81553 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81553>`_ - [7/8 Regression] ICE in immed_wide_int_const, at emit-rtl.c:607
| `81546 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81546>`_ - [8 Regression] ICE at -O3 during GIMPLE pass dom
| `81503 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81503>`_ - [8 Regression] Wrong code at -O2
| `81488 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81488>`_ - [8 Regression] gcc goes off the limits allocating memory in gimple-ssa-strength-reduction.c
| `81423 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81423>`_ - [6/7/8 Regression] Wrong code at -O2
| `81403 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81403>`_ - [8 Regression] wrong code at -O3
| `81387 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81387>`_ - UBSAN consumes too much memory at -O2
| `81281 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81281>`_ - [6/7/8 Regression] UBSAN: false positive, dropped promotion to long type.
| `81162 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81162>`_ - [8 Regression] UBSAN switch triggers incorrect optimization in SLSR
| `81148 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81148>`_ - UBSAN: two more false positives
| `81097 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81097>`_ - UBSAN: false positive for not existing negation operator and a bogus message
| `81088 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81088>`_ - UBSAN: false positive as a result of reassosiation
| `81065 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81065>`_ - UBSAN: false positive as a result of distribution involving different types
| `80932 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80932>`_ - UBSAN: false positive as a result of distribution: c1*(c2*v1-c3*v2)=>c1*c2*v1-c1*c3*v2
| `80875 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80875>`_ - [7 Regression] UBSAN: compile time crash in fold_binary_loc at fold-const.c:9817
| `80800 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80800>`_ - UBSAN: yet another false positive
| `80620 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80620>`_ - [8 Regression] gcc produces wrong code with -O3
| `80597 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80597>`_ - [8 Regression] internal compiler error: in compute_inline_parameters, at ipa-inline-analysis.c:3126
| `80536 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80536>`_ - [6/7/8 Regression] UBSAN: compile time segfault
| `80403 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80403>`_ - UBSAN: compile time crash with "type mismatch in binary expression" message in / and % expr
| `80386 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80386>`_ - UBSAN: false positive - constant folding and reassosiation before instrumentation
| `80362 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80362>`_ - [5/6 Regression] gcc miscompiles arithmetic with signed char
| `80350 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80350>`_ - UBSAN changes code semantics when -fno-sanitize-recover=undefined is used
| `80349 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80349>`_ - [6/7 Regression] UBSAN: compile time crash with "type mismatch in binary expression" message
| `80348 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80348>`_ - [6 Regression] UBSAN: compile time crash in ubsan_instrument_division
| `80341 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80341>`_ - [5/6 Regression] gcc miscompiles division of signed char
| `80297 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80297>`_ - [6 Regression] Compiler time crash: type mismatch in binary expression
| `80072 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80072>`_ - [7 Regression] ICE in gimple_build_assign_1 with -O3 -march=broadwell/skylake-avx512
| `80067 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80067>`_ - [6/7 Regression] ICE in fold_comparison with -fsanitize=undefined
| `80054 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80054>`_ - [7 Regression] ICE in verify_ssa with -O3 -march=broadwell/skylake-avx512
| `79399 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=79399>`_ - GCC fails to compile big source at -O0
| `78726 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=78726>`_ - [5/6 Regression] Incorrect unsigned arithmetic optimization
| `78720 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=78720>`_ - [7 Regression] Illegal instruction in generated code
| `78438 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=78438>`_ - [7 Regression] incorrect comparison optimization
| `78436 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=78436>`_ - [7 Regression] incorrect write to larger-than-type bitfield (signed char x:9)
| `78132 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=78132>`_ - [7 Regression] GCC produces invalid instruction (kmovd and kmovq) for KNL.
| `77544 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=77544>`_ - [6 Regression] segfault at -O0 - infinite loop in simplification
| `77476 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=77476>`_ - [7 Regression] [AVX-512] illegal kmovb instruction on KNL
| `73714 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=73714>`_ - [Regression 7] Incorrect unsigned long long arithmetic optimization
| `72835 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=72835>`_ - [7 Regression] Incorrect arithmetic optimization involving bitfield arguments
| `71657 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=71657>`_ - Wrong code on trunk gcc (std::out_of_range), westmere
| `71655 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=71655>`_ - [7 Regression] GCC trunk ICE on westmere target
| `71488 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=71488>`_ - [6 Regression] Wrong code for vector comparisons with ivybridge and westmere targets
| `71470 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=71470>`_ - Wrong code on trunk gcc with westmere target
| `71389 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=71389>`_ - [7 Regression] ICE on trunk gcc on ivybridge target (df_refs_verify)
| `71281 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=71281>`_ - [7 Regression] ICE on gcc trunk on knl, wsm, ivb and bdw targets (tree-ssa-reassoc)
| `71279 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=71279>`_ - [6/7 Regression] ICE on trunk gcc with knl target
| `71261 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=71261>`_ - [7 Regression] Trunk GCC hangs on knl and broadwell targets
| `71259 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=71259>`_ - [6/7 Regression] GCC trunk emits wrong code
| `70941 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70941>`_ - [5 Regression] Test miscompiled with -O2.
| `70902 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70902>`_ - [7 Regression] GCC freezes while compiling for 'skylake-avx512' target
| `70728 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70728>`_ - GCC trunk emits invalid assembly for knl target
| `70726 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70726>`_ - [6/7 Regression] Internal compiler error (ICE) on valid code
| `70725 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70725>`_ - Internal compiler error (ICE) on valid code
| `70542 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70542>`_ - [6 Regression] Wrong code with -O3 -mavx2.
| `70450 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70450>`_ - [6 Regression] Wrong code with -O0 and -O1.
| `70429 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70429>`_ - Wrong code with -O1.
| `70354 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70354>`_ - [6 Regression] Wrong code with -O3 -march=broadwell and -march=skylake-avx512.
| `70333 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70333>`_ - [5 Regression] Test miscompiled with -O0.
| `70252 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70252>`_ - ICE in vect_get_vec_def_for_stmt_copy with -O3 -march=skylake-avx512.
| `70251 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70251>`_ - Wrong code with -O3 -march=skylake-avx512.
| `70222 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70222>`_ - Test miscompiled with -O1
| `70153 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70153>`_ - [6 Regression] ICE on valid C++ code
| `70026 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70026>`_ - [6 Regression] ICE in expand_expr_real_2 with -O1 -ftree-vectorize
| `70021 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70021>`_ - [6 Regression] Test miscompiled with -O3 option for -march=core-avx2.
| `69820 <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=69820>`_ - [6 Regression] Test miscompiled with -O3 option

====================================
ISPC:
====================================
Full list of ISPC bugs can be found `here <https://github.com/ispc/ispc/issues?q=is%3Aissue+label%3Ayarpgen+>`_

| `1806	<https://github.com/ispc/ispc/issues/1806>`_ - ISPC produces wrong code with bool type iterator
| `1793 <https://github.com/ispc/ispc/issues/1793>`_ - Wrong code for avx2-i32x16.
| `1788 <https://github.com/ispc/ispc/issues/1788>`_ - ICE: LLVM ERROR: Instruction Combining seems stuck in an infinite loop after 1000 iterations.
| `1771 <https://github.com/ispc/ispc/issues/1771>`_ - Wrong code for avx2-i64x4
| `1768 <https://github.com/ispc/ispc/issues/1768>`_ - Uniform and varying types have different rounding rules.
| `1767 <https://github.com/ispc/ispc/issues/1767>`_ - Assertion \`V.getNode() && \"Getting TableId on SDValue()"' failed.
| `1763 <https://github.com/ispc/ispc/issues/1763>`_ - Wrong code for avx2-i64x4
| `1762 <https://github.com/ispc/ispc/issues/1762>`_ - ICE: "scatterFunc != NULL".
| `1729 <https://github.com/ispc/ispc/issues/1729>`_ - Assertion failed: "ci != NULL".
| `1719 <https://github.com/ispc/ispc/issues/1719>`_ - Division by zero leads to ICE
