#define SILENT

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "Parser.h"

std::map<std::string, std::set<std::string>> calcFirst(const Grammar g) {
    using set = std::set<std::string>;
    using std::string;
    using element = std::pair<string, set>;

    //prepare each set and find nonterminal symbols
    std::map<string, set> allFirstSets;
    set nTerminals;
    for (auto * n: g.children) {
        allFirstSets.insert(element(n->value, {}));
        nTerminals.insert(n->value);
    }

    bool changed = true;
    while (changed) {
        changed = false;
        //each rule has at least one ID (=epsilon)
        for (auto * n: g.children) {  //for each rule
            //if starts with terminal insert into first set
            unsigned long numberOfElements = allFirstSets[n->value].size();
            if (nTerminals.count(n->children[0]->value) == 0) {
                allFirstSets[n->value].insert(n->children[0]->value);
            }
            //starts with a nonterminal
            else {  //combine first sets
                auto &firstset = allFirstSets[n->children[0]->value];
                allFirstSets[n->value].insert(firstset.begin(), firstset.end());
            }
            changed = changed | (numberOfElements != allFirstSets[n->value].size());
        }
    }
    return allFirstSets;
}

int main() {
    std::ifstream f("../rules1.txt");
    input = std::string((std::istreambuf_iterator<char>(f)),
                        std::istreambuf_iterator<char>());
    Node *n = parseGrammar();
    std::cout << n->recursivePrint() << std::endl;
    auto firstSets = calcFirst(*dynamic_cast<Grammar *>(n));
    for (auto tmp: firstSets) {
        std::cout << tmp.first << std::endl;
        for (auto tmp1: tmp.second) {
            std::cout << tmp1 << ',';
        }
        std::cout << std::endl;
    }
    delete n;
    return 0;
}