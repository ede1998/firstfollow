//
// Created by erik on 24.10.17.
//

#pragma once


#include <vector>
#include <string>

class Node;
using VecNode = std::vector<Node *>;
class Node{
public:
    VecNode children;
    std::string value;
    virtual std::string print() = 0;
    std::string recursivePrint();
    void add(Node *n);
    void add(VecNode n);
    ~Node();
};

class Grammar : public Node {
public:
    virtual std::string print() {
        return "Grammatik";
    }
};
class Rule : public Node {
public:
    Rule(const std::string &str);
    virtual std::string print() {
        return "Regel";
    }
};
class ID : public Node {
public:
    ID(const std::string &str);
    virtual std::string print() {
        return "ID";
    }
};

