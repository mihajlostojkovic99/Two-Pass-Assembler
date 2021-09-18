#ifndef labels
#define labels
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

int labelLine(string &line);

#endif