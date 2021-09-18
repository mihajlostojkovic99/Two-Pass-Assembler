#ifndef instructions
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include "tables.h"

using namespace std;

extern string currSection;
extern int cnt;
extern int sectionCnt;
extern vector<vector<string>> sections;
extern vector<vector<string>>::iterator sectionIterator;
extern list<Table> symbolTable;
extern vector<list<RelocationTable>> relocationTable;
extern vector<list<RelocationTable>>::iterator relocationIterator;

enum Instruction {HALT, INT, IRET, CALL, RET, JMP, JEQ, JNE, JGT, PUSH, POP, XCHG, ADD, SUB, MUL, DIV,
CMP, NOT, AND, OR, XOR, TEST, SHL, SHR, LDR, STR};

int instruction(string &line);
int instructionToHex(string line);
string jumpIns(Instruction &ins, string str);
string arithmeticIns(Instruction &ins, vector<string> str);
string logicIns(Instruction &ins, vector<string> str);
string loadStoreIns(Instruction &ins, vector<string> args);

#endif