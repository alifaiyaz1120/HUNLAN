#include <iostream>
#include <vector>
#include <cmath>

#include "HUNLAN.h"


int main(int argc, char *argv[]) 
{
    Interpreter engine;
    engine.Run(argv[1]);
    return 0;
}

// Command to Run on Terminal 
// g++  -std=c++17  *.cpp  -o hunlan
// ./hunlan  mycode.hun








