#include <benchmark/benchmark_api.h>

#include <iostream>
#include <fstream>

#include "sprint.hh"

static void PrintIntFprintf(benchmark::State& state) {
	while (state.KeepRunning()) {
		fprintf(stderr, "%ld, %ld, %ld", 4294967295, 4294967295,
		        4294967295);
	}
}

BENCHMARK(PrintIntFprintf);

static void PrintIntFprint(benchmark::State& state) {
	while (state.KeepRunning()) {
		fprint(stderr, 4294967295, 4294967295, 4294967295);
	}
}

BENCHMARK(PrintIntFprint);

static void PrintIntFprintln(benchmark::State& state) {
	while (state.KeepRunning()) {
		fprintln(stderr, 4294967295, 4294967295, 4294967295);
	}
}

BENCHMARK(PrintIntFprintln);

static void PrintIntCerrWithoutFlush(benchmark::State& state) {
	while (state.KeepRunning()) {
		std::cerr << 4294967295 << 4294967295 << 4294967295 << '\n';
	}
}

BENCHMARK(PrintIntCerrWithoutFlush);

static void PrintIntCerrWithFlush(benchmark::State& state) {
	while (state.KeepRunning()) {
		std::cerr << 4294967295 << 4294967295 << 4294967295 << std::endl;
	}
}

BENCHMARK(PrintIntCerrWithFlush);

const char* str =
    "Far far away, behind the word mountains, far from the countries Vokalia "
    "and Consonantia, there live the blind texts. Separated they live in "
    "Bookmarksgrove right at the coast of the Semantics, a large language "
    "ocean. A small river named Duden flows by their place and supplies it "
    "with the necessary regelialia. It is a paradisematic country, in which "
    "roasted parts of sentences fly into your mouth. Even the all-powerful "
    "Pointing has no control about the blind texts it is an almost "
    "unorthographic life One day however a small line of blind text by the "
    "name of Lorem Ipsum decided to";

static void PrintStringFprintf(benchmark::State& state) {
	while (state.KeepRunning()) {
		fprintf(stderr, "%s", str);
	}
}

BENCHMARK(PrintStringFprintf);

static void PrintStringFprint(benchmark::State& state) {
	while (state.KeepRunning()) {
		fprint(stderr, str);
	}
}

BENCHMARK(PrintStringFprint);

static void PrintStringFprintln(benchmark::State& state) {
	while (state.KeepRunning()) {
		fprintln(stderr, str);
	}
}

BENCHMARK(PrintStringFprintln);

static void PrintStringCerrWithoutFlush(benchmark::State& state) {
	while (state.KeepRunning()) {
		std::cerr << str << '\n';
	}
}

BENCHMARK(PrintStringCerrWithoutFlush);

static void PrintStringCerrWithFlush(benchmark::State& state) {
	while (state.KeepRunning()) {
		std::cerr << str << std::endl;
	}
}

BENCHMARK(PrintStringCerrWithFlush);

static void ScanIntFscanf(benchmark::State& state) {
	int64_t a = 0, b = 0, c = 0;
	FILE* file = fopen("fixtures/int.in", "r");
	while (state.KeepRunning()) {
		fscanf(file, "%ld %ld %ld", &a, &b, &c);
	}
}

BENCHMARK(ScanIntFscanf);

static void ScanIntFscan(benchmark::State& state) {
	int64_t a = 0, b = 0, c = 0;
	FILE* file = fopen("fixtures/int.in", "r");
	while (state.KeepRunning()) {
		fscan(file, &a, &b, &c);
	}
}

BENCHMARK(ScanIntFscan);

static void ScanIntFscanln(benchmark::State& state) {
	int64_t a = 0, b = 0, c = 0;
	FILE* file = fopen("fixtures/int.in", "r");
	while (state.KeepRunning()) {
		fscanln(file, &a, &b, &c);
	}
}

BENCHMARK(ScanIntFscanln);

static void ScanIntIfstream(benchmark::State& state) {
	int64_t a = 0, b = 0, c = 0;
	std::ifstream stream("fixtures/int.in");
	while (state.KeepRunning()) {
		stream >> a >> b >> c;
		stream.sync();
	}
}

BENCHMARK(ScanIntIfstream);

BENCHMARK_MAIN();
