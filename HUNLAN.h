#ifndef HUNLAN
#define HUNLAN

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cassert>
#include <fstream>
#include <cstring>
#include <unordered_map>

class MyParser
{
    public:
        std::vector<std::string> operator()(const std::string& user_input); // const reference
        int quoteChecker(std::string counter);
        int operationChecker(std::string counter);
        int spaceChecker(std::string counter);

};

class Interpreter
{
    public:
        bool Run(const std::string& fileName);

};

class MyManager
{
    public:
        void ProcessCommand(std::vector<std::string> command);
        void String(std::vector<std::string> words);
        void Number(std::vector<std::string> values);
        void Print(std::vector<std::string> statement);
        void ProcessAssignment(std::vector<std::string> assignment);
        void AssignmentStrings(std::vector<std::string> assignment);
        void AssignmentNumber(std::vector<std::string> assignment);
        void Arithmetic(std::vector<std::string> assignment);
        std::string ErrorCheck(std::vector<std::string> caution);
        

    private:
       std:: unordered_map< std::string, std::string> strings;
       std:: unordered_map< std::string, long long int> numbers;
};

/*
#include "Parser.cpp"
#include "Interpreter.cpp"
#include "MyManager.cpp"
*/

#endif


