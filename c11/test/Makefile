CXX=clang++-3.5

INCLUDE=../
bins = optest lztest tctest eitest anytest fttest

all:$(bins)

optest:test_optional.cc
	$(CXX) -std=c++11 -I$(INCLUDE) -o optest test_optional.cc

lztest:test_lazy.cc
	$(CXX) -std=c++11 -I$(INCLUDE) -o lztest test_lazy.cc

tctest:test_task_chain.cc
	$(CXX) --std=c++11 -I$(INCLUDE) -o tctest test_task_chain.cc

eitest:test_enable_if.cc
	$(CXX) --std=c++11 -I$(INCLUDE) -o eitest test_enable_if.cc

anytest: test_any.cc
	$(CXX) --std=c++11 -I$(INCLUDE) -o anytest test_any.cc

fttest:test_function_traits.cc
	$(CXX) --std=c++11 -I$(INCLUDE) -o fttest test_function_traits.cc

clean:
	-rm $(bins)

.PHONY: all clean

