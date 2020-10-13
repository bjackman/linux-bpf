{
	"XFADD smoketest",
	.insns = {
	BPF_MOV64_IMM(BPF_REG_0, 0),
	/* Write 3 to stack */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 3),
	/* Put a 1 in R1, add it to the 3 on the stack, and load the value back into R1 */
	BPF_MOV64_IMM(BPF_REG_1, 1),
	BPF_ATM_XFADD_REG(BPF_REG_10, -8, BPF_REG_1),
	/* Check the value we loaded back was 3 */
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 3, 2),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	/* Load value from stack */
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -8),
	/* Check value loaded from stack was 4 */
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 4, 1),
	BPF_MOV64_IMM(BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
},
{
	"Can't use XFADD on frame pointer",
	.insns = {
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 3),
		BPF_ATM_XFADD_REG(BPF_REG_10, -8, BPF_REG_10),
		BPF_EXIT_INSN(),
	},
	.result = REJECT,
	/* It happens that the address leak check is first, but it would also be
	 * complain about the fact that we're trying to modify R10.
	 */
	.errstr = "R10 leaks addr into mem",
},
{
	"Can't use XFADD on uninit src reg",
	.insns = {
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 3),
		BPF_ATM_XFADD_REG(BPF_REG_10, -8, BPF_REG_2),
		BPF_EXIT_INSN(),
	},
	.result = REJECT,
	/* It happens that the address leak check is first, but it would also be
	 * complain about the fact that we're trying to modify R10.
	 */
	.errstr = "!read_ok",
},
{
	"Can't use XFADD on uninit dst reg",
	.insns = {
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_ATM_XFADD_REG(BPF_REG_2, -8, BPF_REG_0),
		BPF_EXIT_INSN(),
	},
	.result = REJECT,
	/* It happens that the address leak check is first, but it would also be
	 * complain about the fact that we're trying to modify R10.
	 */
	.errstr = "!read_ok",
},
{
	"Can't use XFADD on kernel memory",
	.insns = {
		BPF_EMIT_CALL(BPF_FUNC_ktime_get_ns),
		BPF_MOV64_IMM(BPF_REG_1, 1),
		BPF_ATM_XFADD_REG(BPF_REG_0, 0, BPF_REG_1),
		BPF_EXIT_INSN(),
	},
	.result = REJECT,
	/* It happens that the address leak check is first, but it would also be
	 * complain about the fact that we're trying to modify R10.
	 */
	.errstr = "!read_ok",
},
/*
 * TODO:
 * ensure you can't pass uninitialised registers
 * ensure reserved fields must be 0
 */
