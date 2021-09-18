#include "../h/firstPass.h"
#include "../h/tidyUp.h"
#include "../h/directives.h"
#include "../h/instructions.h"
#include "../h/labels.h"
#include <regex>
#include <fstream>
#include <string>
#include <iostream>

int secondPass(fstream &input) {
    cnt = 0;
    string line;
    regex label(".+:");
    while (getline(input, line)) {
        tidyUp(line);
        if (line != "") {
            if (line.front() == ' ') line = line.substr(1);

            if (line.front() == '.') {
                int tmp = directiveToHex(line);
                if (tmp == -1) return -1;
                if (tmp == 1) return 0;
            } else if (regex_search(line, label)) {
                line = line.substr(line.find_first_of(':') + 1);
                if (line.front() == ' ') line = line.substr(1);
                if (line.length() > 1) {
                    if (line.front() == '.') {
                        int tmp = directiveToHex(line);
                        if (tmp == -1) return -1;
                        if (tmp == 1) return 0;
                    } else instructionToHex(line);
                }
            } else {
                if (instructionToHex(line) == -1) return -1;
            }
        }
    }
    return 0;
}