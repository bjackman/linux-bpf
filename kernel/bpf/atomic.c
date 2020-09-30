// SPDX-License-Identifier: GPL-2.0-or-later

#include <linux/filter.h>
#include <linux/atomic.h>

BPF_CALL_1(bpf_atomic64_inc_return, u64*, v)
{
	u64 old = *v;
	u64 new = atomic64_inc_return((atomic64_t *)v);

	printk("%s called! v=%p old=%lld new=%lld\n", __func__, v, old, new);

	return new;
}

const struct bpf_func_proto bpf_atomic64_inc_return_proto = {
	.func		= bpf_atomic64_inc_return,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_INT,
};
