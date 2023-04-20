#include "pch.h"
#include "gtest/gtest.h"
#include "../Chess/Chess.hpp";

template <class Begin, class End>
static std::string range_toString(Begin begin, End end) {
	std::string str = "";
	for (Begin item = begin; item != end; ++item) {
		str += item->to_string() + " ";
	}

	return str;
}

template <class first, class second>
static bool similiar(first beg1, first end1, second beg2, second end2) {
	int first_len = 0;
	for (first i = beg1; i != end1; ++i) {
		++first_len;
	}

	int second_len = 0;
	for (second j = beg2; j != end2; ++j) {
		++second_len;
	}

	if (first_len != second_len) {
		return false;
	}

	for (first i = beg1; i != end1; ++i) {
		bool present = false;

		for (second j = beg2; j != end2; ++j) {
			if ((*i) == (*j)) {
				present = true;
				break;
			}
		}

		if (!present) {
			return false;
		}
		
		present = false;
	}


	return true;
}

//template <class first, class second>
//static bool subset(first beg1, first end1, second beg2, second end2) {
//	int first_len = 0;
//	for (first i = beg1; i != end1; ++i) {
//		++first_len;
//	}
//
//	int second_len = 0;
//	for (second j = beg2; j != end2; ++j) {
//		++second_len;
//	}
//
//	if (first_len < second_len) {
//		return false;
//	}
//
//	for (first i = beg2; i != end2; ++i) {
//		bool present = false;
//
//		for (second j = beg1; j != end1; ++j) {
//			if ((*i) == (*j)) {
//				present = true;
//				break;
//			}
//		}
//
//		if (!present) {
//			return false;
//		}
//		
//		present = false;
//	}
//
//
//	return true;
//}

template <class c1, class c2>
static void assert_container_equal(const c1& expected, const c2& actual) {
	EXPECT_TRUE(similiar(expected.begin(), expected.end(), actual.begin(), actual.end())) << "Expected: " << range_toString(expected.begin(), expected.end()) << std::endl << "Actual: " << range_toString(actual.begin(), actual.end());
}

//template <class c1, class c2>
//static void assert_container_subset(const c1& superset, const c2& subset) {
//	EXPECT_TRUE(subset(superset.begin(), superset.end(), subset.begin(), subset.end())) << "Superset: " << range_toString(superset.begin(), superset.end()) << std::endl << "Subset: " << range_toString(subset.begin(), subset.end());
//}

#define ASSERT_CONTAINER_EQ(expected_container, actual_container) \
	assert_container_equal(expected_container, actual_container);

//#define ASSERT_CONTAINER_SUBSET(superset_container, subset_container) \
//	assert_container_subset(superset_container, subset_container);
