#include "directives.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <regex>
#include <vector>

using namespace std;

enum Directive {GLOBAL, EXTERN, SECTION, WORD, SKIP, EQU, END};

int directiveInstruction(string &line) {
    string str = line.substr(line.find_first_of('.'), line.find_first_of(' ')-line.find_first_of('.'));
    vector<string> symbols;
    Directive directive;
    regex hexa("0x");
    if (str == ".global") directive = GLOBAL;
    else if (str == ".extern") directive = EXTERN;
    else if (str == ".section") directive = SECTION;
    else if (str == ".word") directive = WORD;
    else if (str == ".skip") directive = SKIP;
    else if (str == ".equ") directive = EQU;
    else if (str == ".end") directive = END;

    

    switch (directive)
    {
    case GLOBAL:
        cout << "Current directive: GLOBAL";
        str = line.substr(line.find_first_of(' ') + 1);
        cout << "   Symbols: " << str;
        cout << "   Current section: " << currSection << "\n";
        break;
    case EXTERN:
        cout << "Current directive: EXTERN";
        str = line.substr(line.find_first_of(' ') + 1);
        cout << "   Symbols: " << str;
        cout << "   Current section: " << currSection << "\n";
        splitString(str, ',', symbols);
        for (int i=0; i < symbols.size(); i++) {
            symbolTable.push_back(Table(symbols[i], true));
        }
        break;
    case SECTION:
        cout << "Current directive: SECTION";
        str = line.substr(line.find_first_of(' ') + 1);
        cout << "   Symbols: " << str;
        if (currSection != "") sectionTable.push_back(SectionTable(currSection, cnt));
        insertSection(str);
        currSection = str;
        cnt = 0;
        cout << "   Current section: " << currSection << "\n";
        break;
    case WORD:
        cout << "Current directive: WORD";
        str = line.substr(line.find_first_of(' ') + 1);
        cout << "   Symbols: " << str;
        cout << "   Current section: " << currSection << "\n";
        splitString(str, ',', symbols);
        for (string s : symbols) {
            cnt+=2;
        }
        break;
    case SKIP:
        cout << "Current directive: SKIP";
        str = line.substr(line.find_first_of(' ') + 1);
        cout << "   Symbols: " << str;
        cout << "   Current section: " << currSection << "\n";
        if (regex_search(str, hexa)) cnt += stos(str);
        else cnt += stoi(str);
        break;
    case EQU:
        cout << "Current directive: EQU";
        str = line.substr(line.find_first_of(' ') + 1);
        cout << "   Symbols: " << str;
        cout << "   Current section: " << currSection << "\n";
        line = str.substr(0, str.find_first_of(',')); //line = symbol
        str = str.substr(str.find_first_of(',')+1); //str -> symbol value
        if (regex_search(str, hexa))
            symbolTable.push_back(Table(line, false, "ABS", stos(str)));
        else symbolTable.push_back(Table(line, false, "ABS", stoi(str)));
        break;
    case END:
        cout << "Current directive: END" << "\n";
        sectionTable.push_back(SectionTable(currSection, cnt));
        cnt = 0;
        sectionCnt = 0;
        return 1;
        break;
    
    default:
        break;
    }
    

    return 0;
}

int directiveToHex(string &line) {
    string str = line.substr(line.find_first_of('.'), line.find_first_of(' ')-line.find_first_of('.'));
    vector<string> symbols;
    Directive directive;
    list<Table>::iterator it = symbolTable.begin();
    regex hexa("0x");
    bool symbolNotFound = true;
    string directiveHexString;
    if (str == ".global") directive = GLOBAL;
    else if (str == ".extern") directive = EXTERN;
    else if (str == ".section") directive = SECTION;
    else if (str == ".word") directive = WORD;
    else if (str == ".skip") directive = SKIP;
    else if (str == ".equ") directive = EQU;
    else if (str == ".end") directive = END;

    switch (directive)
    {
    case GLOBAL:
        str = line.substr(line.find_first_of(' ') + 1);
        splitString(str, ',', symbols);
        for (string i : symbols) {
            symbolNotFound = true;
            for (it = symbolTable.begin(); it != symbolTable.end(); ++it) {
                if (it->symbol == i) {
                    it->global = true;
                    symbolNotFound = false;
                    break;
                    
                }
            }
            if (symbolNotFound) {
            cout << "ERROR(-3): Symbol defined as global was not found!" << endl;
            return -1;
            }
        }
        
        break;
    case SECTION:
        cnt = 0;
        sectionCnt++;
        sections.push_back({});
        relocationTable.push_back({});
        sectionIterator = prev(sections.end());
        relocationIterator = prev(relocationTable.end());
        RelocationTable::nextNum = 0;
        break;
    case WORD:
        str = line.substr(line.find_first_of(' ') + 1);
        if (regex_search(str, hexa)) {
            directiveHexString = shortToHexString(stos(str));
            sectionIterator->push_back(directiveHexString);
        } else if (!isdigit(str[0])) {
            splitString(str, ',', symbols);
            for (string s : symbols) {
                cnt += 2;
                symbolNotFound = true;
                for (it = symbolTable.begin(); it != symbolTable.end(); ++it) {
                    if (s == it->symbol) {
                        if (it->global) {
                            sectionIterator->push_back("0000");
                        } else {
                            sectionIterator->push_back(shortToHexString(it->value));
                        }
                        if (it->section != "ABS") updateRelocationTable(it);
                        symbolNotFound = false;
                        break;
                    }
                    
                }
                if (symbolNotFound) {
                    cout << "ERROR(-4): .word symbol was not found!" << endl;
                    return -1;
                }
            }
        } else {
            directiveHexString = shortToHexString(stoi(str));
            sectionIterator->push_back(directiveHexString);
        }
        break;
    case SKIP:
        str = line.substr(line.find_first_of(' ') + 1);
        if (regex_search(str, hexa)) {
            cnt += stos(str);
            directiveHexString.insert(0, stos(str)*2, '0');
        } else {
            cnt += stoi(str);
            directiveHexString.insert(0, stoi(str)*2, '0');
        }
        
        sectionIterator->push_back(directiveHexString);
        break;
    case END:
        return 1;
    default:
        break;
    }
    return 0;
}

string shortToHexString(int x) {
    stringstream ss;
    short y = static_cast<unsigned short>(x);
    string hexString;
    ss << setfill ('0') << setw(4) << hex << y;
    ss >> hexString;
    hexString.append(hexString.substr(0, 2));
    hexString = hexString.substr(2);
    return hexString;
}

int splitString(string &str, char delimiter, vector<string> &vect) {
    stringstream ss(str);
    while (ss.good()) {
        string substring;
        getline(ss, substring, ',');
        if (substring.front() == ' ') substring = substring.substr(1);
        if (substring.back() == ' ') substring = substring.substr(0, substring.length()-1);
        vect.push_back(substring);
    }
    return 0;
}

int stos(string s) {
    unsigned int x;
    stringstream ss;
    ss << hex << s;
    ss >> x;
    return static_cast<short>(x);
}

int insertSection(string str) {
        list<Table>::iterator it = symbolTable.begin();
        advance(it, sectionCnt);
        symbolTable.insert(it, Table(str, false, str));
        int num = 0;
        for (it = symbolTable.begin(); it != symbolTable.end(); ++it) {
            it->num = num;
            num++;
        }
        sectionCnt++;
        return 0;
}

int updateRelocationTable(list<Table>::iterator i, int shiftCnt, bool absolute) {
    int tmp = -1;;
    if (i->global || i->section == "ABS") tmp = i->num; else {
        for (Table t : symbolTable) {
            if (t.symbol == i->section) {
                tmp = t.num;
                break;
            }
        }
    } 
    relocationIterator->push_back(RelocationTable(cnt - shiftCnt, absolute, tmp));
    return 0;
}