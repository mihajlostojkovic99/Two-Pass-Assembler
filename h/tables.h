#ifndef tables
#define tables
#include <stdio.h>
#include <string>
#include <fstream>
#include <list>

using namespace std;

// extern list<Table> symbolTable;
// extern list<SectionTable> sectionTable;

struct Table {
    static int nextNum;
    int num;
    string symbol;
    string section;
    int value;
    bool global;

    Table(string sym, bool glob = false, string sec = "UND", int val = 0){
        num = nextNum++;
        symbol = sym;
        section = sec;
        value = val;
        global = glob;
    }
};

struct SectionTable {
    static int nextNum;
    int num;
    int offset;
    string symbol;
    int value;

    SectionTable(string sym, int val, int off = 0){
        num = nextNum++;
        symbol = sym;
        value = val;
        offset = off;
    }
};

struct RelocationTable {
    static int nextNum;
    int num;
    int offset;
    bool absolute;
    int symNum;

    RelocationTable(int off, bool abs, int symbolNumber){
        num = nextNum++;
        offset = off;
        absolute = abs;
        symNum = symbolNumber;
    }
};

#endif
