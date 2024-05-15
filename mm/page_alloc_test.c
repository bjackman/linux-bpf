#include <linux/gfp.h>

#include <kunit/test.h>

static void test_alloc(struct kunit *test)
{
	struct page *page = __alloc_pages_zonelist(
		GFP_KERNEL, 0, node_zonelist(0, GFP_KERNEL), NULL);

	KUNIT_ASSERT_NOT_NULL(test, page);
	__free_pages(page, 0);
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