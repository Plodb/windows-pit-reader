CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

all: build

build:
	mkdir -p build
	$(CXX) -shared -DPIT_LIB_EXPORTS $(CXXFLAGS) pit_reader.cpp -o build/pit.dll
	$(CXX) $(CXXFLAGS) example.cpp -Lbuild -lpit -o build/example.exe

clean:
	rm -rf build

.PHONY: all build clean