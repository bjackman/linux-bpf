#include <linux/gfp.h>
#include <linux/memory.h>

#include <kunit/test.h>

static void test_alloc(struct kunit *test)
{
	struct page *page = __alloc_pages_zonelist(
		GFP_KERNEL, 0, node_zonelist(0, GFP_KERNEL), NULL);
	struct pglist_data *node0 = NODE_DATA(0);
	struct zone *zone = &NODE_DATA(0)->node_zones[ZONE_MOVABLE];
	unsigned long pfn;

	// Carve out a fake micro-node whose zones are not on any real
	// zonelists. We can then allocate from and free to this node for
	// testing, without the rest of the system interfering.

	// Figure out which memory blocks will go into our fake node. We
	// arbitrarily pick node 0 and grab half of ZONE_MOVABLE since we can
	// get that for ourselves.
	pfn = zone->zone_start_pfn + (zone->spanned_pages / 2);
	struct memory_block *block_start = find_memory_block(
		pfn_to_section_nr(zone->zone_start_pfn));

	KUNIT_ASSERT_NOT_NULL(test, block_start);
	printk("Found block, node %d\n", block_start->nid);


	// TODO:
	// Figure out a range of addrresses to carve out for the separated
	// allocator. I guess we cannot carve this range from the middle of an
	// existing zone?.
	// find  corresponding memory blocks with
	// find_memory_block(pfn_to_section_nr(something)), then call
	// memory_block_offline to remove it Then I tihnk we might want
	// add_hotplug_memory_block (assuming the previous step removed the
	// memory_block device) then memory_block_add_nid to associate with a
	// fake NID?

}

static struct kunit_case test_cases[] = {
        KUNIT_CASE(test_alloc),
        {}
};

static struct kunit_suite test_suite = {
        .name = "page_alloc",
        .test_cases = test_cases,
};
kunit_test_suite(test_suite);

MODULE_LICENSE("GPL");