#include <iostream>
#include <fstream>

enum TokenType { ttARROW, ttID, ttEOG, ttDOT, ttERR};
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
    }
    else if (input[position] == '.') {
        t.type = ttDOT;
        t.content = '.';
    }
    else if (input[position] == '-') {
        ++position;
        if (position < input.length())
            if (input[position] == '>') {
                t.type = ttARROW;
                t.content = "->";
            }
    }
    else {
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
            if (done){
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

void error(const std::string &name);
void parseGrammar();
void parseRules();
void parseIDs();
void parseRule();

void error(const std::string &name) {
    std::cout << "Error " << name << std::endl;
}

void found(const std::string &name) {
    std::cout << "Found " << name << std::endl;
}
void parseGrammar() {
    found("Grammar");
    t = next();
    if ((t.type == ttID) || (t.type == ttEOG)) {
        parseRules();
        return;
    }
    error("Grammar");
}

void parseRules() {
    found("Rules");
    if (t.type == ttID) {
        parseRule();
        t = next();
        parseRules();
        return;
    }
    else if (t.type == ttEOG)
        return;
    error("Rules");
}

void parseRule() {
    found("Rule");
    if (t.type == ttID) {
        t = next();
        if (t.type == ttARROW) {
            t = next();
            if ((t.type == ttID)) {
                parseIDs();
            }
            if (t.type == ttDOT) {
                return;
            }
        }
    }
    error("Rule");
}

void parseIDs() {
    found("IDs");
    if (t.type == ttID) {
        t = next();
        if (t.type == ttID)
            parseIDs();
        return;
    }
    error("IDs");
}

int main() {
    std::ifstream f("file.txt");
    input = std::string((std::istreambuf_iterator<char>(f)),
                    std::istreambuf_iterator<char>());
    parseGrammar();
    /*Token t;
    do {
        t = next();
        switch (t.type) {
            case ttERR:
                std::cout << "Err: " << t.content << std::endl;
                break;
            case ttEOG:
                std::cout << "EOG: " << t.content << std::endl;
                break;
            case ttARROW:
                std::cout << "ARROW: " << t.content << std::endl;
                break;
            case ttID:
                std::cout << "ID: " << t.content << std::endl;
                break;
            case ttDOT:
                std::cout << "DOT: " << t.content << std::endl;
                break;
        }
    }
    while ((t.type != ttEOG) && (t.type != ttERR));*/
    return 0;
}