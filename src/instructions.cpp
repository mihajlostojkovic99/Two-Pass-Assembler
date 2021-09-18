#include "instructions.h"
#include "directives.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <regex>
#include <iomanip>

using namespace std;



int instruction(string &line) {
    string str = line.substr(0, line.find_first_of(' '));
    Instruction ins;
    if (str == "halt") ins = HALT;
    else if (str == "int") ins = INT;
    else if (str == "iret") ins = IRET;
    else if (str == "call") ins = CALL;
    else if (str == "ret") ins = RET;
    else if (str == "jmp") ins = JMP;
    else if (str == "jeq") ins = JEQ;
    else if (str == "jne") ins = JNE;
    else if (str == "jgt") ins = JGT;
    else if (str == "push") ins = PUSH;
    else if (str == "pop") ins = POP;
    else if (str == "xchg") ins = XCHG;
    else if (str == "add") ins = ADD;
    else if (str == "sub") ins = SUB;
    else if (str == "mul") ins = MUL;
    else if (str == "div") ins = DIV;
    else if (str == "cmp") ins = CMP;
    else if (str == "not") ins = NOT;
    else if (str == "and") ins = AND;
    else if (str == "or") ins = OR;
    else if (str == "xor") ins = XOR;
    else if (str == "test") ins = TEST;
    else if (str == "shl") ins = SHL;
    else if (str == "shr") ins = SHR;
    else if (str == "ldr") ins = LDR;
    else if (str == "str") ins = STR;

    regex threeByteJumps("\\*\\[r\\d{1}]|\\*r\\d{1}");
    regex threeByteData(", \\[r\\d{1}]|, r\\d{1}");

    switch (ins)
    {
    case HALT:
        cnt++;
        break;
    case INT:
        cnt+=2;
        break;
    case IRET:
        cnt++;
        break;
    case CALL:
    case JMP:
    case JEQ:
    case JNE:
    case JGT:
        if (regex_search(line, threeByteJumps)) cnt+=3;
        else cnt+=5;
        break;
    case RET:
        cnt++;
        break;
    case XCHG:
        cnt+=2;
        break;
    case ADD:
    case SUB:
    case MUL:
    case DIV:
        cnt+=2;
        break;
    case CMP:
    case AND:
    case NOT:
    case OR:
    case XOR:
    case TEST:
        cnt+=2;
        break;
    case SHR:
    case SHL:
        cnt+=2;
        break;
    case LDR:
    case STR:
        if (regex_search(line, threeByteData)) cnt+=3;
        else cnt+=5;
        break;
    case PUSH:
    case POP:
        cnt+=3;
        break;
    default:
        break;
    }

    return 0;
}

int instructionToHex(string line) {
    string str = line.substr(0, line.find_first_of(' '));
    Instruction ins;
    vector<string> symbols;
    if (str == "halt") ins = HALT;
    else if (str == "int") ins = INT;
    else if (str == "iret") ins = IRET;
    else if (str == "call") ins = CALL;
    else if (str == "ret") ins = RET;
    else if (str == "jmp") ins = JMP;
    else if (str == "jeq") ins = JEQ;
    else if (str == "jne") ins = JNE;
    else if (str == "jgt") ins = JGT;
    else if (str == "push") ins = PUSH;
    else if (str == "pop") ins = POP;
    else if (str == "xchg") ins = XCHG;
    else if (str == "add") ins = ADD;
    else if (str == "sub") ins = SUB;
    else if (str == "mul") ins = MUL;
    else if (str == "div") ins = DIV;
    else if (str == "cmp") ins = CMP;
    else if (str == "not") ins = NOT;
    else if (str == "and") ins = AND;
    else if (str == "or") ins = OR;
    else if (str == "xor") ins = XOR;
    else if (str == "test") ins = TEST;
    else if (str == "shl") ins = SHL;
    else if (str == "shr") ins = SHR;
    else if (str == "ldr") ins = LDR;
    else if (str == "str") ins = STR;

    regex threeByteJumps("\\*\\[r\\d{1}]|\\*r\\d{1}");
    regex threeByteData(", \\[r\\d{1}]|, r\\d{1}");

    switch (ins)
    {
    case HALT:
        cnt++;
        sectionIterator->push_back("00");
        break;
    case INT:
        cnt+=2;
        str = line.substr(line.find_first_of(' ') + 1);
        str = str.substr(1);
        if (str.length() > 1) {
            cout << "ERROR(5): INT instruction register out of range!" << endl;
            return -1;
        }
        else sectionIterator->push_back("10" + str + "f");
        break;
    case IRET:
        cnt++;
        sectionIterator->push_back("20");
        break;
    case CALL:
        //NE ZNAMMMM
    case JMP:
    case JEQ:
    case JNE:
    case JGT:
        if (regex_search(line, threeByteJumps)) cnt+=3;
        else cnt+=5;
        str = line.substr(line.find_first_of(' ') + 1);
        sectionIterator->push_back(jumpIns(ins, str));
        
        break;
    case RET:
        cnt++;
        sectionIterator->push_back("40");
        break;
    case XCHG:
        cnt+=2;
        str = line.substr(line.find_first_of(' ') + 1);
        splitString(str, ',', symbols);
        if (symbols.size() != 2) {
            cout << "ERROR(6): XCHG instruction missing arguments!" << endl;
            return -1;
        }
        str = "60";
        str += symbols[0].back();
        str += symbols[1].back();
        sectionIterator->push_back(str);
        break;
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case CMP:
        cnt+=2;
        str = line.substr(line.find_first_of(' ') + 1);
        splitString(str, ',', symbols);
        if (symbols.size() != 2) {
            cout << "ERROR(7): Arithmetic instruction missing arguments!" << endl;
            return -1;
        }
        str = arithmeticIns(ins, symbols);
        sectionIterator->push_back(str);
        break;
    case AND:
    case NOT:
    case OR:
    case XOR:
    case TEST:
        cnt+=2;
        str = line.substr(line.find_first_of(' ') + 1);
        splitString(str, ',', symbols);
        if (symbols.size() != 2 && ins != NOT) {
            cout << "ERROR(8): Logic instruction missing arguments!" << endl;
            return -1;
        }
        str = logicIns(ins, symbols);
        sectionIterator->push_back(str);
        break;
    case SHR:
    case SHL:
        cnt+=2;
        str = line.substr(line.find_first_of(' ') + 1);
        splitString(str, ',', symbols);
        if (symbols.size() != 2) {
            cout << "ERROR(9): Shift instruction missing arguments!" << endl;
            return -1;
        }
        str = (ins == SHL)? "90":"91";
        str += symbols[0].back();
        str += symbols[1].back();
        sectionIterator->push_back(str);
        break;
    case LDR:
    case STR:
        if (regex_search(line, threeByteData)) cnt+=3;
        else cnt+=5;
        str = line.substr(line.find_first_of(' ') + 1);
        splitString(str, ',', symbols);
        if (symbols.size() != 2 && ins != NOT) {
            cout << "ERROR(10): Load/Store instruction missing arguments!" << endl;
            return -1;
        }
        str = loadStoreIns(ins, symbols);
        sectionIterator->push_back(str);
        break;
    case PUSH:
    case POP:
        cnt+=3;
        str = line.substr(line.find_first_of(' ') + 1);
        symbols.push_back(str);
        if (symbols.size() != 1) {
            cout << "ERROR(11): Push/Pop instruction has wrong arguments!" << endl;
            return -1;
        }
        if (ins == PUSH) str = "b0"; else str = "a0";
        str += symbols[0].back();
        if (ins == POP) str+="642"; else str+="612";
        sectionIterator->push_back(str);
        break;
    default:
        break;
    }

    return 0;
}

string jumpIns(Instruction &ins, string str) {
    string ret = "";
    string arg1;
    string arg2;
    regex hexa("0x");
    switch (ins)
    {
    case CALL:
        ret = "20f";
        break;
    case JMP:
        ret = "50f";
        break;
    case JEQ:
        ret = "51f";
        break;
    case JNE:
        ret = "52f";
        break;
    case JGT:
        ret = "53f";
        break;
    default:
        break;
    }
    if (str.find_first_of('[') != string::npos) {
        if (str.find_first_of('+') != string::npos) {
            arg1 = str.substr(str.find_first_of('[')+1, str.find_first_of('+') - 2);
            if (arg1.find_first_of(' ') != string::npos) arg1.pop_back();
            arg2 = str.substr(str.find_first_of('+') + 2, str.find_first_of(']'));
            arg2.pop_back();
            ret+=arg1.back();
            ret+="03";
            if (regex_search(arg2, hexa)) ret+=shortToHexString(stos(arg2));
            else if (!isdigit(arg2[0])){
                //SIMBOL
                for (list<Table>::iterator it = symbolTable.begin(); it != symbolTable.end(); ++it) {
                    if (it->symbol == arg2) {
                        if (it->global) {
                            ret += "0000";
                        } else {
                            ret += shortToHexString(it->value);
                        }
                        if (it->section != "ABS") updateRelocationTable(it);
                        break;
                    }
                }
            } else {
                //DECIMAL
                ret += shortToHexString(stoi(arg2));
            }
            
        }
        else {
            str = str.substr(str.find_first_of('[') + 1);
            str = str.substr(0, str.find_last_of(']'));
            ret+=str.back();
            ret+="02";  
            
        }
    } else if (str.find_first_of('*') != string::npos){
        str = str.substr(1);
        if (regex_search(str, regex("r\\d"))) {
            ret += str.back();
            ret += "01"; 
        } else if (regex_search(str, hexa)) {
            ret += "004";
            ret += shortToHexString(stos(str));
        } else if (!isdigit(str[0])) { 
            //SIMBOL
            ret += "004";
            for (list<Table>::iterator it = symbolTable.begin(); it != symbolTable.end(); ++it) {
                if (it->symbol == str) {
                    if (it->global) {
                        ret += "0000";
                    } else {
                        ret += shortToHexString(it->value);
                    }
                    if (it->section != "ABS") updateRelocationTable(it);
                    break;
                }
            }
        } else {
            //DECIMAL
            ret += "004";
            ret += shortToHexString(stoi(str));
        }
        
    } else if (str.find_first_of('%') != string::npos) {
        str = str.substr(1);
        //SIMBOL PC REL
        ret += "705";
        for (list<Table>::iterator it = symbolTable.begin(); it != symbolTable.end(); ++it) {
                if (it->symbol == str) {
                    if (it->global) {
                        ret += shortToHexString(-2);
                    } else {
                        ret += shortToHexString(it->value - 2);
                    }
                    updateRelocationTable(it, 2, false);
                    break;
                }
            }
    } else {
        //SAMO SIMBOL ILI LITERAL
        if (regex_search(str, hexa)) {
            ret += "000";
            ret += shortToHexString(stos(str));
        } else if (!isdigit(str[0])) {
            //SIMBOL
            ret += "000";
            for (list<Table>::iterator it = symbolTable.begin(); it != symbolTable.end(); ++it) {
                if (it->symbol == str) {
                    if (it->global) {
                        ret += "0000";
                    } else {
                        ret += shortToHexString(it->value);
                    }
                    if (it->section != "ABS") updateRelocationTable(it);
                    break;
                }
            }
        } else {
            //LITERAL
            ret += "000";
            ret += shortToHexString(stoi(str));
        }
    }
    return ret;
}

string arithmeticIns(Instruction &ins, vector<string> str) {
    string ret = "";
    switch (ins)
    {
    case ADD:
        ret = "70";
        break;
    case SUB:
        ret = "71";
        break;
    case MUL:
        ret = "72";
        break;
    case DIV:
        ret = "73";
        break;
    case CMP:
        ret = "74";
        break;
    default:
        break;
    }
    ret += str[0].back();
    ret += str[1].back();
    return ret;
}

string logicIns(Instruction &ins, vector<string> str) {
    string ret = "";
    switch (ins)
    {
    case NOT:
        ret = "80";
        break;
    case AND:
        ret = "81";
        break;
    case OR:
        ret = "82";
        break;
    case XOR:
        ret = "83";
        break;
    case TEST:
        ret = "84";
        break;
    default:
        break;
    }
    ret += str[0].back();
    if (ins != NOT) ret += str[1].back(); else ret += str[0].back();
    return ret;
}

string loadStoreIns(Instruction &ins, vector<string> args) {
    string ret = "";
    regex hexa("0x");
    switch (ins)
    {
    case LDR:
        ret = "a0";
        break;
    case STR:
        ret = "b0";
        break;
    default:
        break;
    }

    string reg = args[0];
    ret+= reg.back();
    string str = args[1];
    if (str.front() == ' ') str = str.substr(1);
    string arg1;
    string arg2;

    if (str.find_first_of('[') != string::npos) {
        if (str.find_first_of('+') != string::npos) {
            arg1 = str.substr(str.find_first_of('[')+1, str.find_first_of('+') - 2);
            if (arg1.find_first_of(' ') != string::npos) arg1.pop_back();
            arg2 = str.substr(str.find_first_of('+') + 2, str.find_first_of(']'));
            arg2.pop_back();
            ret+=arg1.back();
            ret+="03";  
            if (regex_search(arg2, hexa)) ret+=shortToHexString(stos(arg2));
            else if (!isdigit(arg2[0])){
                //SIMBOL
                for (list<Table>::iterator it = symbolTable.begin(); it != symbolTable.end(); ++it) {
                    if (it->symbol == arg2) {
                        if (it->global) {
                            ret += "0000";
                        } else {
                            ret += shortToHexString(it->value);
                        }
                        if (it->section != "ABS") updateRelocationTable(it);
                        break;
                    }
            }
            } else {
                //DECIMAL
                ret += shortToHexString(stoi(arg2));
            }
        } else {
            str = str.substr(str.find_first_of('[') + 1);
            str = str.substr(0, str.find_last_of(']'));
            ret+=str.back();
            ret+="02";  
        }
    } else if (str.find_first_of('%') != string::npos) {
        str = str.substr(1);
        //SIMBOL PC REL 
        ret += "703";
        for (list<Table>::iterator it = symbolTable.begin(); it != symbolTable.end(); ++it) {
            if (it->symbol == str) {
                if (it->global) {
                    ret += "0000";
                } else {
                    ret += shortToHexString(it->value);
                }
                updateRelocationTable(it, 2, false);
                break;
            }
        }
    } else if (str.find_first_of('$') != string::npos) {
        str = str.substr(1);
        if (regex_search(str, hexa)) {
            ret += "000";
            
            ret += shortToHexString(stos(str));
        } else if (!isdigit(str[0])) {
            //SIMBOL
            ret += "000";
            for (list<Table>::iterator it = symbolTable.begin(); it != symbolTable.end(); ++it) {
                if (it->symbol == str) {
                    if (it->global) {
                        ret += "0000";
                    } else {
                        ret += shortToHexString(it->value);
                    }
                    if (it->section != "ABS") updateRelocationTable(it);
                    break;
                }
            }
        } else {
            //DECIMAL
            ret += "000";
            ret += shortToHexString(stoi(str));
        }
    } else {
        //SIMBOL ILI LITERAL SU ADRESA U MEMORIJI SA KOJE SE HVATA PODATAK ILI REGISTAR DIREKTNO
        if (regex_search(str, regex("r\\d"))) {
            ret += str.back();
            ret += "01";
        } else if (regex_search(str, hexa)) {
            ret += "004";
            ret += shortToHexString(stos(str));
        } else { 
            //SIMBOL
            ret += "004";
            for (list<Table>::iterator it = symbolTable.begin(); it != symbolTable.end(); ++it) {
                if (it->symbol == str) {
                    if (it->global) {
                        ret += "0000";
                    } else {
                        ret += shortToHexString(it->value);
                    }
                    if (it->section != "ABS") updateRelocationTable(it);
                    break;
                }
            }
        }
    }

    return ret;
}