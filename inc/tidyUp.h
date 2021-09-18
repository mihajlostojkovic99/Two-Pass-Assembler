#ifndef tidyUp
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

int tidyUp(string &line);
int removeComments(string &line);
int checkMultipleDirectives(string &line);
int removeWhitespaces(string &line);
int checkLabels(string &line);


#endif