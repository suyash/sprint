# Based on the Makefile in googletest/make

# Points to the root of Google Test
GTEST_DIR = vendor/googletest

# Flags passed to the preprocessor.
CPPFLAGS += -isystem $(GTEST_DIR)/include -std=c++11

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++11

# All tests produced by this Makefile.
TESTS = sprint_test

# All benchmarks produced by this Makefile.
BENCHS = sprint_bench_test

# All Google Test headers.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# DO NOT TWEAK
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# General Tasks

all : test bench

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o *.out

test: $(TESTS).out
	./$<

bench: $(BENCHS).out
	./$< 2> /dev/null < fixtures/int.in

# Tasks for gtest

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Tasks for sprint_test

sprint_test.o : sprint_test.cc $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c sprint_test.cc

sprint_test.out : gtest_main.a sprint_test.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

# Tasks for sprint_bench_test

sprint_bench_test.o: sprint_bench_test.cc
	$(CXX) $(CXXFLAGS) -c $<

sprint_bench_test.out: sprint_bench_test.o
	$(CXX) $(CXXFLAGS) $^ -o $@
