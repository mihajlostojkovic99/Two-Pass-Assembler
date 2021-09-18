#ifndef directives
#define directives
#include <stdio.h>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include "tables.h"

using namespace std;

extern string currSection;
extern int cnt;
extern list<Table> symbolTable;
extern list<SectionTable> sectionTable;
extern int sectionCnt;
extern vector<vector<string>> sections;
extern vector<vector<string>>::iterator sectionIterator;
extern vector<list<RelocationTable>> relocationTable;
extern vector<list<RelocationTable>>::iterator relocationIterator;

int directiveInstruction(string &line);
int directiveToHex(string &line);
int splitString(string &str, char delimiter, vector<string> &vect);
int stos(string s);
int insertSection(string str);
string shortToHexString(int a);
int updateRelocationTable(list<Table>::iterator i, int shiftCnt = 2, bool absolute = true);

#endif