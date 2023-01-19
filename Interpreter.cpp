#include "HUNLAN.h"
#include <sstream>
#include <fstream>
#include <cstring>

bool Interpreter::Run(const std::string& fileName)
{
    std::string line;
    std::ifstream myfile(fileName);
    char sign = '#';
    MyManager engine;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            // read the lines that are empty
            if (line.size() == 0)
            {
                continue;
            }
            // if the lines has a "#", go to the next line
            if (line[0] == '#')
            {
                continue;
            }
            // loop through the string and check for a "#", if there a "#", erase everything after the "#"
            if (line.find(sign) != std::string::npos)
            {
               line.erase(line.find(sign), line.size());
            }

            std::vector<std::string> words;
            MyParser parser;
            words = parser(line); 
            std::string checker = engine.ErrorCheck(words);
            if (checker == "Perfect")
            {
                engine.ProcessCommand(words);
            }
            else
            {
                std:: cout << checker << std::endl;
                break;
            }
        }
        myfile.close();

    }
    else
    {
        std::cout << "Unable to open file";
    }
    return true;
}

