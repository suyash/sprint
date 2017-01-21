# Based on the Makefile in googletest/make

# Points to the root of Google Test
GTEST_DIR = vendor/googletest

BENCHMARK_BUILD_DIR = vendor/benchmark_build

# Flags passed to the preprocessor.
CPPFLAGS += -isystem $(GTEST_DIR)/include -std=c++11

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++11

# All tests produced by this Makefile.
TESTS = sprint_test

# All benchmarks produced by this Makefile.
BENCHS = sprint_bench

# All Google Test headers.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# DO NOT TWEAK
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# General Tasks

all : test bench

clean :
	rm -f $(TESTS).out $(BENCHS).out gtest.a gtest_main.a *.o *.out

test: $(TESTS)

bench: $(BENCHS)

# Tasks for gtest

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Tasks to build benchmark

$(BENCHMARK_BUILD_DIR) : vendor/benchmark
	cd $< \
	&& cmake -DCMAKE_INSTALL_PREFIX=../../$@ -DCMAKE_BUILD_TYPE=Release . \
	&& make \
	&& make install

# Tasks for sprint_test

sprint_test.o : sprint_test.cc $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c sprint_test.cc

sprint_test.out : gtest_main.a sprint_test.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

sprint_test : sprint_test.out
	./$<

# Tasks for sprint_uint128_bench

sprint_bench.o : sprint_bench.cc $(BENCHMARK_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(BENCHMARK_BUILD_DIR)/include -c sprint_bench.cc

sprint_bench.out : sprint_bench.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -lpthread -L$(BENCHMARK_BUILD_DIR)/lib -lbenchmark -o $@

sprint_bench : sprint_bench.out
	./$< --benchmark_out_format=console 2> /dev/null < fixtures/int.in
