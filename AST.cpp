//
// Created by erik on 24.10.17.
//

#include "AST.h"

std::string Node::recursivePrint() {
    std::string res;
    res = this->print() + "\t" + this->value + "\n";
    for (auto n: children) {
        res += n->recursivePrint() + "\n";
    }
    return res;
}

void Node::add(Node *n) {
    children.push_back(n);
}

void Node::add(VecNode n) {
    for (Node *m: n) {
        children.push_back(m);
    }
}

Node::~Node() {
    for (auto i = std::begin(children); i != std::end(children);) {
        i = children.erase(i);
    }
}

ID::ID(const std::string &str)
{
    value = str;
}

Rule::Rule(const std::string &str) {
    value = str;
}
