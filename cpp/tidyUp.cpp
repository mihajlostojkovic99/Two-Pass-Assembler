#include "../h/tidyUp.h"
#include <regex>
#include <stdio.h>
#include <iostream>

using namespace std;

int tidyUp(string &line) {
    removeComments(line);
    removeWhitespaces(line);
    if (checkMultipleDirectives(line) == -1) return -1; 
    if (checkLabels(line) == -2) return -2; 
    return 0;
}

int removeComments(string &line) {
    regex comment("# .*| # .*");
    line = regex_replace(line, comment, "");
    return 0;
}

int checkMultipleDirectives(string &line) {
    regex multiple("\\..+\\.");
    if (regex_search(line, multiple)) return -1;
    else return 0;
}

int removeWhitespaces(string &line) {
    regex whitespaces("\\s{2,}");
    line = regex_replace(line, whitespaces, " ");
    return 0;
}

int checkLabels(string &line) {
    regex wrongLabelPosition(".+ .+:");
    if (regex_search(line, wrongLabelPosition)) return -2;
    return 0;
}