#pragma once

#include <cstdio>
#include <cstring>
#include <typeinfo>

#include "fmt.hh"

// _sfmt fills the passed buffer with the expected format
// _sfmt (base specialization) for a single argument
template <typename T>
int _sfmt(char* buffer, int start, bool ln, T x) {
	auto fmt = _fmt(x);
	std::strcpy(buffer + start, fmt);
	start += strlen(fmt);

	if (ln) {
		std::strcpy(buffer + start, "\n");
		start++;
	}

	return start;
}

// _sfmt fills the passed buffer with the expected format
// _sfmt (variadic specialization) for multiple arguments
// it returns the number of characters written to the passed buffer
template <typename First, typename... Args>
int _sfmt(char* buffer, int start, bool ln, First x, Args... rest) {
	auto fmt = _fmt(x);
	std::strcpy(buffer + start, fmt);
	start += strlen(fmt);

	std::strcpy(buffer + start, " ");
	start++;

	return _sfmt(buffer, start, ln, rest...);
}

///////////////////////////////////////////////////////////////////////////////

// _print creates a new buffer for the passed arguments and calls printf
// the first parameter checks whether newline has to be printed at the end or
// not
template <typename... T>
int _print(FILE* stream, bool ln, T... args) {
	int nargs = sizeof...(args);
	int size = nargs * 5 - 1;
	if (ln) size++;
	char buf[size];
	memset(buf, 0, size);

	_sfmt(buf, 0, ln, args...);
	return fprintf(stream, buf, args...);
}

// fprint (empty argument specialization), simply returns 0
int fprint(FILE* stream) { return 0; }

// fprint (variadic arguments specialization) prints without newline at the end
// to the passed stream
template <typename... T>
int fprint(FILE* stream, T... args) {
	return _print(stream, false, args...);
}

// fprintln (empty argument specialization), simply prints a newline
// to the passed stream
int fprintln(FILE* stream) { return fprintf(stream, "\n"); }

// fprintln (variadic arguments specialization) prints with newline at the end
// to the passed stream
template <typename... T>
int fprintln(FILE* stream, T... args) {
	return _print(stream, true, args...);
}

// print (empty argument specialization), simply returns 0
int print() { return 0; }

// print (variadic arguments specialization) prints without newline at the end
template <typename... T>
int print(T... args) {
	return _print(stdout, false, args...);
}

// println (empty argument specialization), simply prints a newline
int println() { return printf("\n"); }

// println (variadic arguments specialization) prints with newline at the end
template <typename... T>
int println(T... args) {
	return _print(stdout, true, args...);
}

///////////////////////////////////////////////////////////////////////////////

// scan (empty argument specialization), simply returns 0
int fscan(FILE* stream) { return 0; }

// scan (variadic arguments specialization) creates a format string and then
// scans
// arguments, returning the result of the scanf call
template <typename... T>
int fscan(FILE* stream, T... args) {
	int nargs = sizeof...(args);
	int size = 5 * nargs - 1;

	char buf[size];
	memset(buf, 0, size);

	_sfmt(buf, 0, false, args...);
	return fscanf(stream, buf, args...);
}

void fscanskipln(FILE* stream) {
	while (true) {
		char ch = getc(stream);
		if (ch == EOF || ch == '\n') break;
		// TODO: check if we need
		// https://sourcegraph.com/github.com/golang/go@838eaa738f2bc07c3706b96f9e702cb80877dfe1/-/blob/src/fmt/scan.go#L1058:8
	}
}

// fscanln (empty argument specialization), scans until a newline and returns 0
int fscanln(FILE* stream) {
	fscanskipln(stream);
	return 0;
}

// scanln is scan but will read until a newline or EOF
template <typename... T>
int fscanln(FILE* stream, T... args) {
	int v = fscan(stream, args...);
	fscanskipln(stream);
	return v;
}

int scan() { return 0; }

template <typename... T>
int scan(T... args) {
	return fscan(stdin, args...);
}

int scanln() { return fscanln(stdin); }

template <typename... T>
int scanln(T... args) {
	return fscanln(stdin, args...);
}
