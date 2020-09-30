// SPDX-License-Identifier: GPL-2.0

#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

__u64 value_in = 0;
 long value_out = 0;

SEC("tp/syscalls/sys_enter_getpgid")
int test_atomic_fetch_add(void *ctx)
{
	__u64 old = value_in;

	value_out = bpf_atomic64_inc_return(&value_in);

	const char fmt[] = "value_in=%lld->%lld, value_out=%ld\n";
	bpf_trace_printk(fmt, sizeof(fmt), old, value_in, value_out);

	return value_out;
}

char _license[] SEC("license") = "GPL";
