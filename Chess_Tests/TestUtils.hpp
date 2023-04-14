#include "pch.h"
#include "gtest/gtest.h"
#include "../Chess/Chess.hpp";

template<typename T = square_t>
static std::string set_toString(std::set<T> s) {
	std::string str = "";
	for (auto&& item : s) {
		str += item.to_string() + " ";
	}

	return str;
}

template<typename T = square_t>
static void assert_set_equal(std::set<T> expected, std::set<T> actual) {
	ASSERT_EQ(expected.size(), actual.size()) << "Expected: " << set_toString(expected) << std::endl << "Actual: " << set_toString(actual);

	for (auto&& exp : expected) {
		ASSERT_TRUE(actual.contains(exp)) << "Expected: " << set_toString(expected) << std::endl << "Actual: " << set_toString(actual);
	}
}

#define ASSERT_SET_EQ(expected_set, actual_set) \
		assert_set_equal(expected_set, actual_set);
