CXX=g++
CXXFLAGS=-std=c++98 -pedantic -Wall -Werror -g `pkg-config pugixml --cflags`
LDFLAGS= `pkg-config pugixml --libs-only-l`
LDLIBS= `pkg-config pugixml --libs-only-L`
RM=rm -fv
.PHONY: all clean
edp.out: edp.cpp address.o company.o envelope.o envelope-c4.o envelope-dl.o str2i-error.o str2l-error.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)
str2l-error.o: str2l-error.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
str2i-error.o: str2i-error.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
envelope-dl.o: envelope-dl.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
envelope-c4.o: envelope-c4.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
envelope.o: envelope.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
company.o: company.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
address.o: address.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
clean:
	$(RM) *.o *.out