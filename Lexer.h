//
// Created by erik on 24.10.17.
//

#pragma once

#include <string>

enum TokenType {
    ttARROW, ttID, ttEOG, ttDOT, ttERR
};
struct Token {
    TokenType type = ttERR;
    std::string content = "";
};

unsigned int position = 0;
std::string input;
Token t;

bool isEmpty(char c) {
    switch (c) {
        case '\n':
        case '\r':
        case '\t':
        case ' ':
            return true;
        default:
            return false;
    }
}

Token next() {
    Token t = {};

    //Delete empty characters
    while (position < input.length()) {
        if (isEmpty(input[position]))
            ++position;
        else
            break;
    }

    //find Tokens
    if (position >= input.length()) {
        t.type = ttEOG;
    } else if (input[position] == '.') {
        t.type = ttDOT;
        t.content = '.';
    } else if (input[position] == '-') {
        ++position;
        if (position < input.length())
            if (input[position] == '>') {
                t.type = ttARROW;
                t.content = "->";
            }
    } else {
        bool done = false;
        unsigned int i;
        //add characters to ID until invalid character is found
        for (i = position; i <= input.length(); ++i) {
            switch (input[i]) {
                case '.':
                case '-':
                case '>':
                case ' ':
                case '\n':
                case '\r':
                case '\t':
                    done = true;
                    break;
                default:
                    t.content += input[i];
            }
            if (done) {
                position = i - 1;
                if (t.content.length() != 0)
                    t.type = ttID;
                break;
            }
        }
    }
    ++position;
    return t;
}