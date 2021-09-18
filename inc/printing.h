#ifndef printing
#define printing
#include <stdio.h>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include "tables.h"

using namespace std;

extern list<Table> symbolTable;
extern list<SectionTable> sectionTable;
extern vector<vector<string>> sections;
extern vector<vector<string>>::iterator sectionIterator;
extern vector<list<RelocationTable>> relocationTable;
extern vector<list<RelocationTable>>::iterator relocationIterator;

int printSectionTable(fstream &output);
int printSymbolTable(fstream &output);
int printHex(fstream &output);
int printRelocationTables(fstream &output);

#endif