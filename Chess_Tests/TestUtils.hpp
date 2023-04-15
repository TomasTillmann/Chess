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

template <class c1, class c2>
static void assert_container_equal(c1 expected, c2 actual) {
	EXPECT_TRUE(similiar(expected.begin(), expected.end(), actual.begin(), actual.end())) << "Expected: " << range_toString(expected.begin(), expected.end()) << std::endl << "Actual: " << range_toString(actual.begin(), actual.end());
}

#define ASSERT_CONTAINER_EQ(expected_container, actual_container) \
	assert_container_equal(expected_container, actual_container);
