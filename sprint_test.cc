#include <gtest/gtest.h>

#include "sprint.hh"

TEST(_fmt, int) {
	int a = 2;
	ASSERT_STREQ("%d", _fmt(a));
}

TEST(_fmt, uint64_t) {
	uint64_t a = 4294967295;
	if (typeid(a) == typeid(unsigned long long int)) {
		ASSERT_STREQ("%llu", _fmt(a));
	} else {
		ASSERT_STREQ("%lu", _fmt(a));
	}
}

TEST(_fmt, int64_t) {
	int64_t a = 4294967295;
	if (typeid(a) == typeid(long long int)) {
		ASSERT_STREQ("%lld", _fmt(a));
	} else {
		ASSERT_STREQ("%ld", _fmt(a));
	}
}

TEST(_fmt, uint32_t) {
	uint32_t a = 4294967295;
	if (typeid(a) == typeid(unsigned long int)) {
		ASSERT_STREQ("%lu", _fmt(a));
	} else {
		ASSERT_STREQ("%u", _fmt(a));
	}
}

TEST(_fmt, int32_t) {
	int32_t a = 4294967295;
	if (typeid(a) == typeid(long int)) {
		ASSERT_STREQ("%ld", _fmt(a));
	} else {
		ASSERT_STREQ("%d", _fmt(a));
	}
}

TEST(_fmt, double) {
	double a = 3.14159;
	ASSERT_STREQ("%lf", _fmt(a));
}

TEST(_fmt, float) {
	float a = 3.14159;
	ASSERT_STREQ("%f", _fmt(a));
}

TEST(_fmt, char) {
	char a = '1';
	ASSERT_STREQ("%c", _fmt(a));
}

TEST(_sfmt, single_arg) {
	char buffer[100];
	memset(buffer, 0, 100);
	int t = _sfmt(buffer, 0, false, 2);
	ASSERT_STREQ("%d", buffer);
	ASSERT_EQ(2, t);
}

TEST(_sfmt, three_args) {
	char buffer[100];
	memset(buffer, 0, 100);
	int t = _sfmt(buffer, 0, false, 2, 2.1, 'a');
	ASSERT_STREQ("%d %lf %c", buffer);
	ASSERT_EQ(9, t);
}

TEST(_sfmt, newline) {
	char buffer[100];
	memset(buffer, 0, 100);
	int t = _sfmt(buffer, 0, true, 2, 2.1, 'a');
	ASSERT_STREQ("%d %lf %c\n", buffer);
	ASSERT_EQ(10, t);
}
