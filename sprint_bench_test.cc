#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>

#include "sprint.hh"

typedef std::function<void()> Worker;

uint64_t bench(uint64_t iter, const Worker& worker) {
	auto start = std::chrono::system_clock::now();

	for (uint64_t i = 0; i < iter; i++) {
		worker();
	}

	auto end = std::chrono::system_clock::now();

	return std::chrono::duration_cast<std::chrono::milliseconds>(end -
	                                                             start)
	    .count();
}

void benchpints() {
	uint64_t runs = 10;
	uint64_t iter = 250000;
	double t_pf = 0, t_p = 0, t_pl = 0, t_c = 0;

	for (uint64_t x = 0; x < runs; x++) {
		t_pf += bench(iter, []() {
			fprintf(stderr, "%ld, %ld, %ld", 4294967295, 4294967295,
			        4294967295);
		});

		t_p += bench(iter, []() {
			fprint(stderr, 4294967295, 4294967295, 4294967295);
		});

		t_pl += bench(iter, []() {
			fprintln(stderr, 4294967295, 4294967295, 4294967295);
		});

		t_c += bench(iter, []() {
			std::cerr << 4294967295 << 4294967295 << 4294967295
			          << '\n'
			          << std::flush;
		});
	}

	println("ints printf:", t_pf / runs, "print:", t_p / runs, "println:",
	        t_pl / runs, "cerr:", t_c / runs);
}

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

void benchpstrings() {
	uint64_t runs = 10;
#ifdef __APPLE__
	uint64_t iter = 25000;
#else
	uint64_t iter = 250000;
#endif
	double t_pf = 0, t_p = 0, t_pl = 0, t_c = 0;

	for (uint64_t x = 0; x < runs; x++) {
		t_pf += bench(iter, []() { fprintf(stderr, "%s", str); });

		t_p += bench(iter, []() { fprint(stderr, str); });

		t_pl += bench(iter, []() { fprintln(stderr, str); });

		t_c += bench(iter, []() {
			std::cerr << str << '\n' << std::flush;
		});
	}

	println("strings printf:", t_pf / runs, "print:", t_p / runs,
	        "println:", t_pl / runs, "cerr:", t_c / runs);
}

void benchsints() {
	uint64_t runs = 10;
	uint64_t iter = 250000;
	double t_sf = 0, t_s = 0, t_sl = 0, t_c = 0;

	for (uint64_t x = 0; x < runs; x++) {
		t_sf += bench(iter, []() {
			int64_t a = 0, b = 0, c = 0;
			scanf("%ld %ld %ld", &a, &b, &c);
		});

		t_s += bench(iter, []() {
			int64_t a = 0, b = 0, c = 0;
			scan(&a, &b, &c);
		});

		t_sl += bench(iter, []() {
			int64_t a = 0, b = 0, c = 0;
			scanln(&a, &b, &c);
		});

		t_c += bench(iter, []() {
			int64_t a = 0, b = 0, c = 0;
			std::cin >> a >> b >> c;
		});
	}

	println("ints scanf:", t_sf / runs, "scan:", t_s / runs, "scanln:",
	        t_sl / runs, "cin:", t_c / runs);
}

int main() {
	benchpints();
	benchpstrings();
	benchsints();
}
