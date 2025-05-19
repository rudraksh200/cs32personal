// WordCount.cpp

#include "WordCount.h"
#include <cctype>

using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int sum = 0;
	for(size_t i = 0; i < CAPACITY; i++){
		for(size_t j = 0; j < table[i].size(); j++){
			sum += table[i][j].second;
		}
	}
	return sum;
}

int WordCount::getNumUniqueWords() const {
	int count = 0;
	for(size_t i = 0; i < CAPACITY; i++){
		for(size_t j = 0; j < table[i].size(); j++){
				count++;
		}
	}
	return count;
}

int WordCount::getWordCount(std::string word) const {
	std::string vWord = makeValidWord(word);
	size_t wHash = hash(vWord);
	for(size_t j = 0; j < table[wHash].size(); j++){
		if(vWord == table[wHash][j].first){
			return table[wHash][j].second;
		}
	}
	return 0;
}
	
int WordCount::incrWordCount(std::string word) {
	std::string vWord = makeValidWord(word);
	if(word.size() == 0) return 0;
	size_t wHash = hash(vWord);
	for(size_t j = 0; j < table[wHash].size(); j++){
		if(vWord == table[wHash][j].first){
			table[wHash][j].second++;
			return table[wHash][j].second;
		}
	}
	table[wHash].push_back(std::make_pair(vWord, 1));
	return 1;
}

int WordCount::decrWordCount(std::string word) {
	std::string vWord = makeValidWord(word);
	size_t wHash = hash(vWord);
	for(size_t j = 0; j < table[wHash].size(); j++){
		if(vWord == table[wHash][j].first){
			table[wHash][j].second--;
			if(table[wHash][j].second == 0){
				table[wHash].erase(table[wHash].begin() + j);
				return 0;
			}
			return table[wHash][j].second;
		}
	}
	return -1;
}

bool WordCount::isWordChar(char c) {
	if(isalpha(c)){
		return true;
	}
	return false;
}

std::string WordCount::makeValidWord(std::string word) {
	std::string vWord = word;
	for(size_t i = 0; i < vWord.length(); i++){
		if(i == 0 || i == vWord.length()-1){
			if(isWordChar(vWord[i])){
				vWord[i] = tolower(vWord[i]);
			} else{
				vWord.erase(i,1);
				i--;
			}
		} else if(isWordChar(vWord[i]) || vWord[i] == '-' || vWord[i] == '\''){
			vWord[i] = tolower(vWord[i]);
		}
		else{
			vWord.erase(i,1);
			i--;
		}
	}
	return vWord;
}
