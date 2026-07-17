CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion -Wno-sign-compare -Wfloat-equal -fsanitize=undefined -I .

.PHONY: clean clear di p%
.SECONDARY:

%.out: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

_%: %.out
	./$*.out

+%: %.out
	./$*.out < $*.in > z_actual.txt
	cat z_actual.txt

di: 
	@diff -yw z_actual.txt z_expected.txt

clean: 
	echo "cleaning"
	rm -f *.out 

clear:
	echo "clearing"
	rm -f *.out *.in

p%: 
	cp ~/cpp/template/setup.cpp $*.cpp
	echo "" > $*.in

