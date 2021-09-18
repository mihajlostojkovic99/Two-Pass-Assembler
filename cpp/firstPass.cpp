#include "../h/firstPass.h"
#include "../h/tidyUp.h"
#include "../h/directives.h"
#include "../h/instructions.h"
#include "../h/labels.h"
#include <regex>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int firstPass(fstream &input) {
    string line;
    regex label(".+:");
    symbolTable.push_back(Table(""));
    while (getline(input, line)) {
        switch (tidyUp(line))
        {
        case -1:
            cout << "ERROR(" << -1 << "): Multiple directives in a line!" << "\n";
            return -1;
        
        case -2:
            cout << "ERROR(" << -2 << "): Wrog label format!" << "\n";
            return -1;

        default:
            break;
        }
        if (line != "") {
            if (line.front() == ' ') line = line.substr(1);

            if (line.front() == '.') {
                if (directiveInstruction(line) == 1) return 0;
            } else if (regex_search(line, label)) {
                labelLine(line);
                //Kod za proveru instrukcije u istoj liniji sa labelom
                line = line.substr(line.find_first_of(':'));
                if (line.front() == ' ') line = line.substr(1);
                if (line.length() > 1) {
                    if (line.front() == '.') {
                        if (directiveInstruction(line) == 1) return 0;
                    } else instruction(line);
                }
            } else {
                instruction(line);
            }
        }
    }
    return 0;
}