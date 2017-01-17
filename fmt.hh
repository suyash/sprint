#pragma once

#ifdef __clang__

// _fmt is a macro that will give the format for a variable
// based on its type
#define _fmt(T) \
	_Generic((T), \
		int: "%d", \
		long int: "%ld", \
		long long int: "%lld", \
		\
		unsigned int: "%u", \
		unsigned long int: "%lu", \
		unsigned long long int: "%llu", \
		\
		float: "%f", \
		double: "%lf", \
		\
		char: "%c", \
		\
		char*: "%s", \
		const char*: "%s", \
		\
		default: "%p" \
)

#else

#include <typeinfo>

template <typename T>
const char* _fmt(T val) {
	// switch won't work as switched value cannot be a custom type

	if (typeid(val) == typeid(int)) return "%d";
	if (typeid(val) == typeid(long int)) return "%ld";
	if (typeid(val) == typeid(long long int)) return "%lld";

	if (typeid(val) == typeid(unsigned int)) return "%u";
	if (typeid(val) == typeid(unsigned long int)) return "%lu";
	if (typeid(val) == typeid(unsigned long long int)) return "%llu";

	if (typeid(val) == typeid(char*)) return "%s";
	if (typeid(val) == typeid(const char*)) return "%s";

	if (typeid(val) == typeid(float)) return "%f";
	if (typeid(val) == typeid(double)) return "%lf";

	if (typeid(val) == typeid(char)) return "%c";

	return "%p";
}

#endif  // __clang__
