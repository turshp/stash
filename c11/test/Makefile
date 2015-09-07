CXX=clang++-3.6

INCLUDE=../
bins = optest lztest tctest eitest anytest fttest rgtest rftest rttest

all:$(bins)

optest:test_optional.cc ../optional.hh
	$(CXX) -std=c++11 -I$(INCLUDE) -o optest test_optional.cc

lztest:test_lazy.cc ../lazy.hh
	$(CXX) -std=c++11 -I$(INCLUDE) -o lztest test_lazy.cc

tctest:test_task_chain.cc ../task_chain.hh
	$(CXX) --std=c++11 -I$(INCLUDE) -o tctest test_task_chain.cc

eitest:test_enable_if.cc
	$(CXX) --std=c++11 -I$(INCLUDE) -o eitest test_enable_if.cc

anytest: test_any.cc ../any.hh
	$(CXX) --std=c++11 -I$(INCLUDE) -o anytest test_any.cc

fttest:test_function_traits.cc ../function_traits.hh
	$(CXX) --std=c++11 -I$(INCLUDE) -o fttest test_function_traits.cc

rgtest: test_range.cc ../range.hh
	$(CXX) --std=c++11 -I$(INCLUDE) -o rgtest test_range.cc

rftest:test_reference.cc ../type_name.hh
	$(CXX) --std=c++11 -I$(INCLUDE) -o rftest test_reference.cc

rttest:test_return_tuple.cc ../lenminmax.hh
	$(CXX) --std=c++11 -I$(INCLUDE) -o rttest test_return_tuple.cc

clean:
	-rm $(bins)

.PHONY: all clean

