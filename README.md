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

## Benchmarks

From: https://travis-ci.org/suyash/sprint/jobs/193965648

```
Benchmark                            Time           CPU Iterations
------------------------------------------------------------------
PrintIntFprintf                    662 ns        651 ns    1120266
PrintIntFprint                     726 ns        726 ns     986147
PrintIntFprintln                   813 ns        803 ns     860802
PrintIntCerrWithoutFlush          1781 ns       1760 ns     396888
PrintIntCerrWithFlush             1619 ns       1608 ns     403087
PrintStringFprintf                1087 ns       1068 ns     663231
PrintStringFprint                 1005 ns        998 ns     608755
PrintStringFprintln               1094 ns       1088 ns     688807
PrintStringCerrWithoutFlush        792 ns        782 ns     891838
PrintStringCerrWithFlush           756 ns        743 ns     889423
ScanIntFscanf                      664 ns        660 ns    1179087
ScanIntFscan                       733 ns        729 ns     880432
ScanIntFscanln                     734 ns        717 ns     935005
ScanIntIfstream                    614 ns        607 ns    1173745
```

## TODO

- minified builds for quick embedding

- google/benchmark for benchmarks

- support for `std::string`

- support for printing collections supporting `std::begin` and `std::end`
