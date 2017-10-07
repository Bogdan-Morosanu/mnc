main: tokeniser.* main.cpp
	g++ -O3 -Wall -Werror -std=c++17 main.cpp tokeniser.cpp -o mnc
