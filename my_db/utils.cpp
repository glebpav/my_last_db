#include "utils.h"

Utils::Utils()
{

}

string Utils::removeSpaces(string inputStr){
    string outputStr = "";

    for(int i=0;i<inputStr.size();i++){
        char currentChar = inputStr[i];
        if (currentChar != ' ') outputStr += currentChar;
    }
    return outputStr;
}

