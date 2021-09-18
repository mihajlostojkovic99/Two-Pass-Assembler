#include "labels.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <regex>

int labelLine(string &line) {
    string label = line.substr(0, line.find_first_of(':'));
    cout << "Found label " << label << " Value is " << cnt << "\n";
    Table newEntry(label, false, currSection, cnt);
    symbolTable.push_back(newEntry);
    return 0;
}