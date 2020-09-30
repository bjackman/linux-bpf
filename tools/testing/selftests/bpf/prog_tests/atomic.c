// SPDX-License-Identifier: GPL-2.0
#define _GNU_SOURCE

#include <test_progs.h>

#include "test_atomic.skel.h"

static struct test_atomic *skel;

void test_atomic(void)
{
	int duration = 0; // Required by unhygeinic CHECK macro.
	int err;

	skel = test_atomic__open_and_load();
	if (CHECK(!skel, "skel_open_load", "skeleton open&load failed\n"))
		return;

	err = test_atomic__attach(skel);
	if (CHECK(err, "skel_attach", "skeleton attachment failed: %d\n", err))
		goto cleanup;

	CHECK(skel->bss->value_out != 1, "value_out", "value_out = %ld\n",
	      skel->bss->value_out);
	CHECK(skel->bss->value_in != 1, "value_in", "value_in = %lld\n",
	      skel->bss->value_in);

	// The prog is attached to a tracepoint on this syscall - make the
	// syscall to trigger running the prog.
	syscall(__NR_getpgid);
cleanup:
	test_atomic__destroy(skel);
}
