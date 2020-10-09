{
	"atomic add smoketest - immediate",
	.insns = {
	BPF_MOV64_IMM(BPF_REG_0, 0),
	/* Write 3 to stack */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 3),
	/* Fetch the 0 from the stack back into R0 then increment it. */
	BPF_ATM_XFADD_IMM(BPF_REG_10, -8, BPF_REG_1, 1),
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
	"atomic add smoketest - register",
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
/*
 * TODO:
 * ensure you can't pass uninitialised registers
 * ensure reserved fields must be 0
 */
