# sprint

[![Build Status](https://travis-ci.org/suyash/sprint.svg?branch=master)](https://travis-ci.org/suyash/sprint)

golang like scan, scanln, print and println functions for C++

Just include `sprint.hh` to use.

## Art

### Format Detection

A function `_fmt` is defined that has 2 implementations

The first is using the new `_Generic` macro in C11, used to create a type switch to detect format.

The second uses the new C++11 `typeid` to compare types and detect formats.

The `_Generic` version only builds on clang.

Currently keeping both as some naive benchmarks show that the `_Generic` version is faster on clang.

### Format String Generation

The backing construct is the new **variadic template functions/parameter packs** introduced in C++11.

```
template <typename... T>
ret_type func_name(T... args) {
	// sizeof...(args) gives the number of passed arguments
}
```

## TODO

- minified builds for quick embedding

- google/benchmark for benchmarks

- support for `std::string`

- support for printing collections supporting `std::begin` and `std::end`
