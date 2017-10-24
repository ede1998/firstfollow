//
// Created by erik on 24.10.17.
//

#pragma once

#include <iostream>
#include "AST.h"
#include "Lexer.h"

void error(const std::string &name);

Node *parseGrammar();

VecNode parseRules();

VecNode parseIDs();

Node *parseRule();

void error(const std::string &name) {
#ifndef SILENT
    std::cout << "Error " << name << std::endl;
#endif
}

void found(const std::string &name) {
#ifndef SILENT
    std::cout << "Found " << name << std::endl;
#endif
}

Node *parseGrammar() {
    found("Grammar");
    t = next();
    if ((t.type == ttID) || (t.type == ttEOG)) {
        Grammar *g = new Grammar();
        g->add(parseRules());
        return g;
    }
    error("Grammar");
}

VecNode parseRules() {
    VecNode v;
    found("Rules");
    if (t.type == ttID) {
        v.push_back(parseRule());
        t = next();
        VecNode vn = parseRules();
        v.insert(v.end(), vn.begin(), vn.end());
        return v;
    } else if (t.type == ttEOG)
        return v;
    error("Rules");
}

Node *parseRule() {
    found("Rule");
    if (t.type == ttID) {
        Rule *r = new Rule(t.content);
        t = next();
        if (t.type == ttARROW) {
            t = next();

            if ((t.type == ttID)) {
                r->add(parseIDs());
            }
            else {
                r->add(new ID("epsilon"));
            }
            if (t.type == ttDOT) {
                return r;
            }
        }
    }
    error("Rule");
}

VecNode parseIDs() {
    found("IDs");
    VecNode v;
    if (t.type == ttID) {
        v.push_back(new ID(t.content));
        t = next();
        if (t.type == ttID) {
            VecNode vn = parseIDs();
            v.insert(v.end(), vn.begin(), vn.end());
        }
        return v;
    }
    error("IDs");
}
