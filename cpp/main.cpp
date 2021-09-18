#include <stdio.h>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include "../h/firstPass.h"
#include "../h/secondPass.h"
#include "../h/tables.h"
#include "../h/printing.h"
using namespace std;

string currSection = "";
int sectionCnt = 1;
int cnt = 0;

list<Table> symbolTable;
list<SectionTable> sectionTable;
vector<vector<string>> sections;
vector<vector<string>>::iterator sectionIterator;
vector<list<RelocationTable>> relocationTable;
vector<list<RelocationTable>>::iterator relocationIterator;

int main(int argc, char* argv[]) {
    regex inputFormat(".+\\.s");
    regex outputFormat(".+\\.o");
    if (argc < 4) {
        printf("Arguments are missing!");
        return 1;
    } else if (strcmp(argv[1], "-o")) {
        printf("Wrong call format!");
        return 1;
    }
    string outputName = argv[2];
    string inputName = argv[3];

    if (!regex_search(outputName, outputFormat)) outputName += ".o";
    if (!regex_search(inputName, inputFormat)) inputName += ".s";

    fstream input, output;
    input.open(inputName, ios::in);
    output.open(outputName, ios::out);

    if (firstPass(input) == 0) {
        input.clear();
        input.seekg(0);
        if (secondPass(input) == 0) {
            if (sections.size() > 0) {
                for (vector<string> v : sections) {
                    if (v.empty()) break;
                    for (string s : v) {
                        cout << s << endl;
                    }
                    cout << endl << endl;
                }  
            }
            printSectionTable(output);
            printSymbolTable(output);
            printHex(output);
            printRelocationTables(output);
        }
    }

    input.close();
    output.close();
    return 0;
}