// SPDX-License-Identifier: GPL-2.0-only

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <linux/bpf.h>
#include <linux/stringify.h>

/* Peeking at an internal header in  kernel/bpf/ */
#include "insn_map.h"

int main(int argc, char **argv)
{
#define BPF_INSN_2_TBL(x, y)    [BPF_##x | BPF_##y] = __stringify(x##_##y)
#define BPF_INSN_3_TBL(x, y, z) [BPF_##x | BPF_##y | BPF_##z] = __stringify(x##_##y##_##z)
	static const char public_insntable[256][16] = {
		[0 ... 255] = "",
		/* Now overwrite non-defaults ... */
		BPF_INSN_MAP(BPF_INSN_2_TBL, BPF_INSN_3_TBL),
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
