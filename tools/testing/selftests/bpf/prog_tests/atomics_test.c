// SPDX-License-Identifier: GPL-2.0

#include <test_progs.h>

#include "atomics_test.skel.h"

static void test_add(void)
{
	struct atomics_test *atomics_skel = NULL;
	int err, prog_fd;
	__u32 duration = 0, retval;

	atomics_skel = atomics_test__open_and_load();
	if (CHECK(!atomics_skel, "atomics_skel_load", "atomics skeleton failed\n"))
		goto cleanup;

	err = atomics_test__attach(atomics_skel);
	if (CHECK(err, "atomics_attach", "atomics attach failed: %d\n", err))
		goto cleanup;

	prog_fd = bpf_program__fd(atomics_skel->progs.add);
	err = bpf_prog_test_run(prog_fd, 1, NULL, 0,
				NULL, NULL, &retval, &duration);
	if (CHECK(err || retval, "test_run add",
		  "err %d errno %d retval %d duration %d\n",
		  err, errno, retval, duration))
		goto cleanup;

	if (CHECK(atomics_skel->data->add64_value != 2, "add64_value",
		  "64bit atomic add value was not incremented (got %lld want 2)\n",
		  atomics_skel->data->add64_value))
	if (CHECK(atomics_skel->bss->add64_result != 1, "add64_result",
		  "64bit atomic add bad return value (got %lld want 1)\n",
		  atomics_skel->data->add64_value))

	if (CHECK(atomics_skel->data->add32_value != 2, "add32_value",
		  "32bit atomic add value was not incremented (got %d want 2)\n",
		  atomics_skel->data->add32_value))
	if (CHECK(atomics_skel->bss->add32_result != 1, "add32_result",
		  "32bit atomic add bad return value (got %d want 1)\n",
		  atomics_skel->data->add32_value))

	if (CHECK(atomics_skel->bss->add_stack_value_copy != 2, "add_stack_value",
		  "_stackbit atomic add value was not incremented (got %lld want 2)\n",
		  atomics_skel->bss->add_stack_value_copy))
	if (CHECK(atomics_skel->bss->add_stack_result != 1, "add_stack_result",
		  "_stackbit atomic add bad return value (got %lld want 1)\n",
		  atomics_skel->bss->add_stack_value_copy))

cleanup:
	atomics_test__destroy(atomics_skel);
}

static void test_cmpxchg(void)
{
	struct atomics_test *atomics_skel = NULL;
	int err, prog_fd;
	__u32 duration = 0, retval;

	atomics_skel = atomics_test__open_and_load();
	if (CHECK(!atomics_skel, "atomics_skel_load", "atomics skeleton failed\n"))
		goto cleanup;

	err = atomics_test__attach(atomics_skel);
	if (CHECK(err, "atomics_attach", "atomics attach failed: %d\n", err))
		goto cleanup;

	prog_fd = bpf_program__fd(atomics_skel->progs.add);
	err = bpf_prog_test_run(prog_fd, 1, NULL, 0,
				NULL, NULL, &retval, &duration);
	if (CHECK(err || retval, "test_run add",
		  "err %d errno %d retval %d duration %d\n",
		  err, errno, retval, duration))
		goto cleanup;

	if (CHECK(atomics_skel->data->cmpxchg64_value != 2, "cmpxchg64_value",
		  "64bit cmpxchg left unexpected value (got %lld want 2)\n",
		  atomics_skel->data->cmpxchg64_value))
	if (CHECK(atomics_skel->bss->cmpxchg64_result_fail != 1, "cmpxchg_result_fail",
		  "64bit cmpxchg (comparison should fail) returned bad result (got %lld want 1)\n",
		  atomics_skel->bss->cmpxchg64_result_fail))
	if (CHECK(atomics_skel->bss->cmpxchg64_result_succeed != 1, "cmpxchg_result_succeed",
		  "64bit cmpxchg (comparison should succeed) returned bad result (got %lld want 1)\n",
		  atomics_skel->bss->cmpxchg64_result_succeed))

cleanup:
	atomics_test__destroy(atomics_skel);
}

void test_atomics_test(void)
{
	test_add();
	test_cmpxchg();
}
