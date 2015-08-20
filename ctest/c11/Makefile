CXX=clang++-3.5

all:optest lztest tctest

optest:test_optional.cc optional.hh
	$(CXX) -std=c++11 -o optest test_optional.cc

lztest:test_lazy.cc lazy.hh
	$(CXX) -std=c++11 -o lztest test_lazy.cc

tctest:test_task_chain.cc task_chain.hh
	$(CXX) --std=c++11 -o tctest test_task_chain.cc

clean:
	-rm optest lztest tctest

.PHONY: all clean

