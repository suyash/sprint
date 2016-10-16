# sprint

[![Build Status](https://travis-ci.org/suyash/sprint.svg?branch=master)](https://travis-ci.org/suyash/sprint)

golang like scan, scanln, print and println functions for C++

Just include `sprint.hh` to use.

```cpp
print(1, 2, 3) // prints `1 2 3`
println(1, 2, 3) // prints `1 2 3` followed by a newline

int a = 0, b = 0, c = 0;
char s[256] = {0};
scanln(&a, &b, &c); // will scan 3 variables and terminate only after finding a newline
scan(s); // will scan a string after the newline
```

## Art

### Format Detection

A function `_fmt` is defined in `fmt.hh` that has 2 implementations

The first is using the `_Generic` macro in C11, used to create a type switch to detect format.

The second uses the C++11 `typeid` to compare types and detect formats.

The `_Generic` version only builds on clang.

Currently keeping both as some naive benchmarks show that the `_Generic` version is faster on clang.

### Format String Generation

The backing construct is the **variadic template functions/parameter packs** syntax introduced in C++11.

```cpp
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
