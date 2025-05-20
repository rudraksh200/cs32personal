#include <iostream>
#include <string>
#include "WordCount.h"
#include "tddFuncs.h"
using namespace std;

int main(){
    WordCount table = WordCount();
    cout << "Starting table totalWords(): " << table.getTotalWords() << endl;
    cout << "Starting table numuniquewords(): " << table.getNumUniqueWords() << endl;
    cout << "Starting table wordCount for hi: " << table.getWordCount("hi") << endl;
    cout << "Incrementing word count for hi: " << table.incrWordCount("hi") << endl;
    cout << "Rechecking total words after addition: " << table.getTotalWords() << endl;
    cout << "Rechecking get num unique words: " << table.getNumUniqueWords() << endl;
    cout << "Rechecking wordcount for hi: " << table.getWordCount("hi") << endl;
    cout << "Decrementing word count for hi: " << table.decrWordCount("hi") << endl;
    cout << "Rechecking total words after decrement: " << table.getTotalWords() << endl;
    cout << "Rechecking get num unique words: " << table.getNumUniqueWords() << endl;
    cout << "Rechecking wordcount for hi: " << table.getWordCount("hi") << endl;
    cout << "Checking makeValidWord for ''''''word-main-: " << table.makeValidWord("''''''word-main-") << endl;
    cout << "Checking makeValidWord count for ''''''w--or-d##main------: " << table.makeValidWord("''''''w--or-d##main------") << endl;
    cout << "Checking makeValidWord count for ''-----: " << table.makeValidWord("''-----") << endl;
    cout << table.makeValidWord("can't") << endl << table.makeValidWord("good-hearted") << endl << table.makeValidWord("12mOnkEYs-$") << endl << table.makeValidWord("Pa55ive") << endl;

    return 0;
}