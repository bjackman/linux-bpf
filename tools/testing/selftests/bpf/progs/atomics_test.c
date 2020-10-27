// SPDX-License-Identifier: GPL-2.0
#include <stdatomic.h>

#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

__u64 add64_value = 1;
__u64 add64_result;
__u32 add32_value = 1;
__u32 add32_result;
__u64 add_stack_value_copy;
__u64 add_stack_result;
SEC("fentry/bpf_fentry_test1")
int BPF_PROG(add, int a)
{
	__u64 add_stack_value = 1;

	add64_result = __sync_fetch_and_add(&add64_value, 1);
	add32_result = __sync_fetch_and_add(&add32_value, 1);
	add_stack_result = __sync_fetch_and_add(&add_stack_value, 1);
	add_stack_value_copy = add_stack_value;

	return 0;
}

__u64 cmpxchg64_value = 1;
__u64 cmpxchg64_result_fail;
__u64 cmpxchg64_result_succeed;
SEC("fentry/bpf_fentry_test1")
int BPF_PROG(cmpxchg, int a)
{
	cmpxchg64_result_fail = __sync_val_compare_and_swap(
		&cmpxchg64_result_fail, 0, 3);
	cmpxchg64_result_succeed = __sync_val_compare_and_swap(
		&cmpxchg64_result_fail, 1, 2);
}

/* TODO: xchg, other binary ops */
