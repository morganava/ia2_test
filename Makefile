.DEFAULT_GOAL := ia2_test

ia2_test: *.cpp *.hpp
	i686-w64-mingw32-g++ -std=c++17 -Wall -Wfatal-errors -O3 -g accessible_test.cpp dumper.cpp  -IIAccessible2 -luuid -loleacc -loleaut32 -lole32 -static-libgcc -static-libstdc++ -o ia2_test.exe

clean:
	rm -f ia2_test.exe
