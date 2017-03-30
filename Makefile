all:
	g++ -Wall -std=c++11 -c Trie.cpp -o trie.o
	g++ -Wall -std=c++11 trie.o main.cpp
