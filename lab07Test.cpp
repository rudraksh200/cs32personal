#include <iostream>
#include <string>
#include <sstream>
#include "WordCount.h"
#include "tddFuncs.h"
using namespace std;

int main(){
    WordCount table = WordCount();
    std::ostringstream oss;
    std::ostream& out = oss;
    cout << "getTotalWords() initial: " << table.getTotalWords() << endl
    << "getNumUniqueWords() initial: " << table.getNumUniqueWords() << endl
    <<"getWordCount(\"hi\") initial: " << table.getWordCount("hi") << endl
    << "decrWordCount(\"hi\") initial: " << table.decrWordCount("hi") << endl
    << "incrWordCount(\"hi\"): " << table.incrWordCount("hi") << endl
    << "getTotalWords(): " << table.getTotalWords() << endl
    << "getNumUniqueWords(): " << table.getNumUniqueWords() << endl
    << "getWordCount(\"hi\"): " << table.getWordCount("hi") << endl
    << "decrWordCount(\"hi\"): " << table.decrWordCount("hi") << endl
    << "getTotalWords(): " << table.getTotalWords() << endl
    << "getNumUniqueWords(): " << table.getNumUniqueWords() << endl
    << "getWordCount(\"hi\"): " << table.getWordCount("hi") << endl
    << "incrWordCount test: " << table.incrWordCount("\'\'----w_O-r#d----") << endl
    << "getWordCount(\"wo-rd\"): " << table.getWordCount("wo-rd")<<endl
    << "reset: " << table.decrWordCount("wo-rd")<< endl
    << "addAllWords test: ";
    table.addAllWords("Hello hello! C++ isn't fun... but fun? Yes, FUN.");
    cout << "dumpWordsSortedByWord(): ";
    table.dumpWordsSortedByWord(out);
    cout << oss.str();
    oss.str("");
    oss.clear();
    table.dumpWordsSortedByOccurence(out);
    cout << "dumpWordsSortedByOccurence(): " << oss.str();
    WordCount wc = WordCount();
    wc.addAllWords("-start 'end' middle-");
    oss.str("");
    oss.clear();
    wc.dumpWordsSortedByOccurence(out);
    cout << "dumpWordsSortedByOccurence(): " <<oss.str();
    WordCount wc1 = WordCount();
    wc1.addAllWords("$$$1234 !!! ");
    oss.str("");
    oss.clear();
    cout << "Another makeValidWord test: " << wc1.getTotalWords() << endl;
    return 0;
}