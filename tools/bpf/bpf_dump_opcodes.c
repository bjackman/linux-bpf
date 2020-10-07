// SPDX-License-Identifier: GPL-2.0-only

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <linux/bpf.h>
#include <linux/stringify.h>

/* Peeking at an internal header in  kernel/bpf/ */
#include "insn_map.h"

/* unused opcode to mark special call to bpf_tail_call() helper */
#define BPF_TAIL_CALL	0xf0

/* unused opcode to mark special load instruction. Same as BPF_ABS */
#define BPF_PROBE_MEM	0x20

/* unused opcode to mark call to interpreter with arguments */
#define BPF_CALL_ARGS	0xe0

int main(int argc, char **argv)
{
#define BPF_INSN_2_TBL(x, y)    [BPF_##x | BPF_##y] = __stringify(x##_##y)
#define BPF_INSN_3_TBL(x, y, z) [BPF_##x | BPF_##y | BPF_##z] = __stringify(x##_##y##_##z)
	static const char public_insntable[256][16] = {
		[0 ... 255] = "",
		/* Now overwrite non-defaults ... */
		BPF_INSN_MAP(BPF_INSN_2_TBL, BPF_INSN_3_TBL),
		/* UAPI exposed, but rewritten opcodes. cBPF carry-over. */
		BPF_INSN_3_TBL(LD, ABS, B)"*",
		BPF_INSN_3_TBL(LD, ABS, H)"*",
		BPF_INSN_3_TBL(LD, ABS, W)"*",
		BPF_INSN_3_TBL(LD, IND, B)"*",
		BPF_INSN_3_TBL(LD, IND, H)"*",
		BPF_INSN_3_TBL(LD, IND, W)"*",
		/* Non-UAPI available opcodes. */
		BPF_INSN_2_TBL(JMP, CALL_ARGS)"*",
		BPF_INSN_2_TBL(JMP, TAIL_CALL)"*",
		BPF_INSN_3_TBL(LDX, PROBE_MEM, B)"*",
		BPF_INSN_3_TBL(LDX, PROBE_MEM, H)"*",
		BPF_INSN_3_TBL(LDX, PROBE_MEM, W)"*",
		BPF_INSN_3_TBL(LDX, PROBE_MEM, DW) /* * skipped because it doesn't fit lol */,
	};

	/* Print column headers */
	for (int j = 0; j < 8; j++)
		printf("|  0x%02x%11s", j, "");
	printf("|\n");
	/* Underline column headers */
	for (int j = 0; j < 150; j++)
		printf("-");
	printf("\n");

	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 8; j++) {
			printf("| %-16s", public_insntable[i * 8 + j]);
		}
		printf("| 0x%02x\n", i * 8);
	}
}
