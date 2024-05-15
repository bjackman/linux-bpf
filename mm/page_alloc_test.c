#include <kunit/test.h>

static void test_nop(struct kunit *test)
{
}

static struct kunit_case test_cases[] = {
        KUNIT_CASE(test_nop),
        {}
};

static struct kunit_suite test_suite = {
        .name = "page_alloc",
        .test_cases = test_cases,
};
kunit_test_suite(test_suite);

MODULE_LICENSE("GPL");