{
	"atomic exchange smoketest - 64bit",
	.insns = {
	/* val = 3; */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 3),
	/* old = atomic_cmpxchg(&val, 2, 4); */
	BPF_MOV64_IMM(BPF_REG_1, 4),
	BPF_MOV64_IMM(BPF_REG_0, 2),
	BPF_ATOMIC_CMPXCHG(BPF_DW, BPF_REG_10, BPF_REG_1, -8),
	/* if (old != 3) exit(2); */
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
	BPF_MOV64_IMM(BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	/* if (val != 3) exit(3); */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -8),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
	BPF_MOV64_IMM(BPF_REG_0, 3),
	BPF_EXIT_INSN(),
	/* old = atomic_cmpxchg(&val, 3, 4); */
	BPF_MOV64_IMM(BPF_REG_1, 4),
	BPF_MOV64_IMM(BPF_REG_0, 3),
	BPF_ATOMIC_CMPXCHG(BPF_DW, BPF_REG_10, BPF_REG_1, -8),
	/* if (old != 3) exit(4); */
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
	BPF_MOV64_IMM(BPF_REG_0, 4),
	BPF_EXIT_INSN(),
	/* if (val != 4) exit(5); */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -8),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 4, 2),
	BPF_MOV64_IMM(BPF_REG_0, 5),
	BPF_EXIT_INSN(),
	/* exit(0); */
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
},
{
	"atomic exchange smoketest - 32bit",
	.insns = {
	/* val = 3; */
	BPF_ST_MEM(BPF_W, BPF_REG_10, -4, 3),
	/* old = atomic_cmpxchg(&val, 2, 4); */
	BPF_MOV32_IMM(BPF_REG_1, 4),
	BPF_MOV32_IMM(BPF_REG_0, 2),
	BPF_ATOMIC_CMPXCHG(BPF_W, BPF_REG_10, BPF_REG_1, -4),
	/* if (old != 3) exit(2); */
	BPF_JMP32_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
	BPF_MOV32_IMM(BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	/* if (val != 3) exit(3); */
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_10, -4),
	BPF_JMP32_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
	BPF_MOV32_IMM(BPF_REG_0, 3),
	BPF_EXIT_INSN(),
	/* old = atomic_cmpxchg(&val, 3, 4); */
	BPF_MOV32_IMM(BPF_REG_1, 4),
	BPF_MOV32_IMM(BPF_REG_0, 3),
	BPF_ATOMIC_CMPXCHG(BPF_W, BPF_REG_10, BPF_REG_1, -4),
	/* if (old != 3) exit(4); */
	BPF_JMP32_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
	BPF_MOV32_IMM(BPF_REG_0, 4),
	BPF_EXIT_INSN(),
	/* if (val != 4) exit(5); */
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_10, -4),
	BPF_JMP32_IMM(BPF_JEQ, BPF_REG_0, 4, 2),
	BPF_MOV32_IMM(BPF_REG_0, 5),
	BPF_EXIT_INSN(),
	/* exit(0); */
	BPF_MOV32_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
},
{
	"atomic compare-and-set smoketest - 64bit",
	.insns = {
	/* val = 3; */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 3),
	/* atomic_cmpxchg(&val, 2, 4); */
	BPF_MOV64_IMM(BPF_REG_1, 4),
	BPF_MOV64_IMM(BPF_REG_0, 2),
	BPF_ATOMIC_CMPSET(BPF_DW, BPF_REG_10, BPF_REG_1, -8),
	/* r0 should not be clobbered (BPF_FETCH flag not set) */
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 2, 2),
	BPF_MOV64_IMM(BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	/* if (val != 3) exit(3); */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -8),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
	BPF_MOV64_IMM(BPF_REG_0, 3),
	BPF_EXIT_INSN(),
	/* old = atomic_cmpxchg(&val, 3, 4); */
	BPF_MOV64_IMM(BPF_REG_1, 4),
	BPF_MOV64_IMM(BPF_REG_0, 3),
	BPF_ATOMIC_CMPXCHG(BPF_DW, BPF_REG_10, BPF_REG_1, -8),
	/* if (old != 3) exit(4); */
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
	BPF_MOV64_IMM(BPF_REG_0, 4),
	BPF_EXIT_INSN(),
	/* if (val != 4) exit(5); */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -8),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 4, 2),
	BPF_MOV64_IMM(BPF_REG_0, 5),
	BPF_EXIT_INSN(),
	/* exit(0); */
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
},
{
	"atomic compare-and-set smoketest - 32bit",
	.insns = {
	/* val = 3; */
	BPF_ST_MEM(BPF_W, BPF_REG_10, -4, 3),
	/* atomic_cmpxchg(&val, 2, 4); */
	BPF_MOV32_IMM(BPF_REG_1, 4),
	BPF_MOV32_IMM(BPF_REG_0, 2),
	BPF_ATOMIC_CMPSET(BPF_W, BPF_REG_10, BPF_REG_1, -4),
	/* r0 should not be clobbered (BPF_FETCH flag not set) */
	BPF_JMP32_IMM(BPF_JEQ, BPF_REG_0, 2, 2),
	BPF_MOV32_IMM(BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	/* if (val != 3) exit(3); */
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_10, -4),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
	BPF_MOV32_IMM(BPF_REG_0, 3),
	BPF_EXIT_INSN(),
	/* old = atomic_cmpxchg(&val, 3, 4); */
	BPF_MOV32_IMM(BPF_REG_1, 4),
	BPF_MOV32_IMM(BPF_REG_0, 3),
	BPF_ATOMIC_CMPXCHG(BPF_W, BPF_REG_10, BPF_REG_1, -4),
	/* if (old != 3) exit(4); */
	BPF_JMP32_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
	BPF_MOV32_IMM(BPF_REG_0, 4),
	BPF_EXIT_INSN(),
	/* if (val != 4) exit(5); */
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_10, -4),
	BPF_JMP32_IMM(BPF_JEQ, BPF_REG_0, 4, 2),
	BPF_MOV32_IMM(BPF_REG_0, 5),
	BPF_EXIT_INSN(),
	/* exit(0); */
	BPF_MOV32_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
},
{
	"Can't use cmpxchg on uninit src reg",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 3),
	BPF_MOV64_IMM(BPF_REG_0, 3),
	BPF_ATOMIC_CMPXCHG(BPF_DW, BPF_REG_10, BPF_REG_2, -8),
	BPF_EXIT_INSN(),
	},
	.result = REJECT,
	.errstr = "!read_ok",
},
{
	"Can't use cmpxchg on uninit memory",
	.insns = {
	BPF_MOV64_IMM(BPF_REG_0, 3),
	BPF_MOV64_IMM(BPF_REG_2, 4),
	BPF_ATOMIC_CMPXCHG(BPF_DW, BPF_REG_10, BPF_REG_2, -8),
	BPF_EXIT_INSN(),
	},
	.result = REJECT,
	.errstr = "invalid read from stack",
},
{
	"Can't use compare-and-set on kernel memory",
	.insns = {
	/* This is an fentry prog, context is array of the args of the
	 * kernel function being called. Load first arg into R2.
	 */
	BPF_LDX_MEM(BPF_DW, BPF_REG_2, BPF_REG_1, 0),
	/* First arg of bpf_fentry_test7 is a pointer to a struct.
	 * Attempt to modify that struct. Verifier shouldn't let us
	 * because it's kernel memory.
	 */
	BPF_MOV64_IMM(BPF_REG_3, 1),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_ATOMIC_CMPSET(BPF_DW, BPF_REG_2, BPF_REG_3, 0),
	BPF_EXIT_INSN(),
	},
	.prog_type = BPF_PROG_TYPE_TRACING,
	.expected_attach_type = BPF_TRACE_FENTRY,
	.kfunc = "bpf_fentry_test7",
	.result = REJECT,
	.errstr = "only read is supported",
},
