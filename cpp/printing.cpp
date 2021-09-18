#include "../h/printing.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int printSectionTable(fstream &output){
    if (sectionTable.size() > 0 && sections.size() > 0) {
        output << "---------------------------" << endl;
        output << "SECTION TABLE:" << endl;
        output << "---------------------------" << endl;
        output << setw(2) << "NUM" << " " << setw(7) << "SECTION" << " " << setw(6) << "OFFSET" << " " << setw(5) << "SIZE" << endl;
        for (SectionTable t : sectionTable) {
            //cout << t.num << " " << t.symbol << " "<< 0 << " " << t.value << endl;
            output << setw(2) << t.num << " " << setw(7) << t.symbol << " " << setw(6) << 0 << " " << setw(5) << t.value << endl;
        }
    }
    output << endl;
    return 0;
}

int printSymbolTable(fstream &output){
    if (symbolTable.size() > 0 && sections.size() > 0) {
        output << "---------------------------" << endl;
        output << "SYMBOL TABLE:" << endl;
        output << "---------------------------" << endl;
        output << setw(2) << "NUM" << " " << setw(15) << "SYMBOL" << " " << setw(7) << "SECTION" << " " << setw(5) << "VALUE" << " " << setw(6) << "SCOPE" << endl;
        for (Table t : symbolTable) {
            //cout << t.num << " " << t.symbol << " "<< t.section << " " << t.value << endl;
            output << setw(2) << t.num << " " << setw(15) << t.symbol << " " << setw(7) << t.section << " " << setw(5) << t.value << "  " << setw(6) << ((t.global)? " global":" local") << endl;
        }
    }
    return 0;
}

int printHex(fstream &output){
    
    if (sectionTable.size() > 0 && sections.size() > 0) {
        sectionIterator = sections.begin();
        output << endl << "**************************************************************" << endl << endl;
        string tmp;
        int spaceCnt = 0;
        for (SectionTable t : sectionTable) {
            output << "---------------------------" << endl;
            output << t.symbol << endl;
            output << "---------------------------" << endl;
            for (vector<string>::iterator it = sectionIterator->begin(); it != sectionIterator->end(); ++it) {
                tmp = *it;
                spaceCnt = 0;
                for (int i=0; i<tmp.size(); i++) {
                    spaceCnt++;
                    output << tmp[i];
                    if (spaceCnt == 2) {
                        output << " ";
                        spaceCnt = 0;
                    }
                }
                output << endl;
            }
            advance(sectionIterator, 1);
        }
    }
    return 0;
}

int printRelocationTables(fstream &output) {
    
    if (relocationTable.size() > 0 && sectionTable.size() > 0) {
        relocationIterator = relocationTable.begin();
        output << endl << "**************************************************************" << endl << endl;
        for (SectionTable t : sectionTable) {
            output << "---------------------------" << endl;
            output << t.symbol << " RELOCATION TABLE:" << endl;
            output << "---------------------------" << endl;
            output << setw(2) << "NUM" << " " << setw(7) << "OFFSET" << " " << setw(10) << "TYPE  "  << " " << setw(7) << "SYM_NUM" << endl;
            for (RelocationTable t : *relocationIterator) {
                output << setw(2) << t.num << " " << setw(7) << t.offset << " " << setw(10) << (t.absolute? "R_386_16" : "R_386_PC16")  << " " << setw(7) << t.symNum << endl;
            }
            output << endl;
            advance(relocationIterator, 1);
        }
    } 
    return 0;
}