#include "HashTable.h"
#include <cstring>
#include <random>

size_t pearson_hash(const std::string s, const int* table) {
	size_t hash = 0;
	for (char c : s) {
		hash = table[(hash ^ c)%256];
	}
	return hash;
}

bool compare_pearson_hashes(const std::string s1, const std::string s2, const int* table) {
	return pearson_hash(s1, table) == pearson_hash(s2, table);
}

int main() {
	HashTable<int, int> map(10);
	map.insert(353, 11);
	map.insert(3, 11);
	map.insert(3, 12);
	map.insert(35, 11);
	map.insert(53, 11);
	map.insert_or_assign(35, 34);
	std::cout << "Map Search of 2" << std::endl;
	std::cout << map.search(2) << std::endl;
	std::cout << "Map Search of 3" << std::endl;
	std::cout << *map.search(3) << std::endl;
	std::cout << "___________________" << std::endl;
	std::cout << "Map print" << std::endl;
	map.print();
	std::cout << "___________________" << std::endl;
	std::cout << "Map erase" << std::endl;
	std::cout << map.erase(35) << std::endl;
	std::cout << "___________________" << std::endl;
	std::cout << "Map print" << std::endl;
	map.print();
	std::cout << "___________________" << std::endl;
	std::cout << "Map size" << std::endl;
	std::cout << map.get_size() << std::endl;
	std::cout << "___________________" << std::endl;
	map.insert(7, 5);
	map.insert(5, 5);
	map.insert(5, 5);
	std::cout << "Map print" << std::endl;
	map.print();
	std::cout << "___________________" << std::endl;
	HashTable<int, int> map1(10, 1, 5);
	std::cout << "Map1: " << std::endl;
	map1.print();
	std::cout << "___________________" << std::endl;
	HashTable<char, char> mapchar(15, 1, 100);
	mapchar.print();
	std::cout << "___________________" << std::endl;
	HashTable<int, std::string> mapstring(15);
	mapstring.insert(412, "One");
	mapstring.print();
	std::cout << "___________________\n___________________\n___________________" << std::endl;
	std::string s1 = "Twenty percent skill";
	std::string s2 = "Twenty percent skill";
	std::string s3 = "Fifty percent concentrated power of will";
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> dis(1, 255);
	int table[256];
	for (size_t i = 0; i < 256; ++i) {
		table[i] = (int)dis(gen);
	}
	std::cout << "Pearson hash comparison(s1==s2):" << std::endl;
	std::cout << "s1 -- s2:" << std::endl;
	std::cout << compare_pearson_hashes(s1, s2, table) << std::endl;
	std::cout << "s2 -- s3:" << std::endl;
	std::cout << compare_pearson_hashes(s2, s3, table) << std::endl;
	
	return 0;
}