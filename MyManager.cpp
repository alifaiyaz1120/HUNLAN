#include "HUNLAN.h"
#include <sstream>
#include <fstream>
#include <cstring>


void MyManager::ProcessCommand(std::vector<std::string> command)
{
    if (command[0] == "STRING")
    {
        // go to the string function
        String(command);
    }
    else if (command[0] == "NUMBER")
    {
        // go to the number function
        Number(command);
    }
    else if (command[0] == "PRINT")
    {
        // go to the print function
        Print(command);
    }
    else 
    {
        ProcessAssignment(command);
    }
}

void MyManager::String(std::vector<std::string> words)
{
   strings[words[1]] = ""; 
}
void MyManager::Number(std::vector<std::string> values)
{
    numbers[values[1]] = 0;
}
void MyManager::Print(std::vector<std::string> statement)
{
    if (strings.find(statement[1]) != strings.end())
    {
        if ((strings[statement[1]][0] == '\\' && strings[statement[1]][1] == 'n') && 
        (strings[statement[1]][strings[statement[1]].size()-2] == 'n' && strings[statement[1]][strings[statement[1]].size()-3] == '\\'))
        {
           // remove the \n in the beginning and the end of the string
            strings[statement[1]] = strings[statement[1]].substr(2);
            strings[statement[1]] = strings[statement[1]].substr(0, strings[statement[1]].size() - 3);
            std::cout << std::endl << strings[statement[1]] << std::endl;
        }
        else if (strings[statement[1]][0] == '\\' && strings[statement[1]][1] == 'n') 
        {
            strings[statement[1]] = strings[statement[1]].substr(2);
            std::cout << std::endl << strings[statement[1]];
        }
        else if (strings[statement[1]][strings[statement[1]].size()-2] == 'n' && strings[statement[1]][strings[statement[1]].size()-3] == '\\') 
        {
            // remove the /n from the end of the string and go to the next line
            strings[statement[1]] = strings[statement[1]].substr(0, strings[statement[1]].size() - 3);
            std::cout << strings[statement[1]] << std::endl;
        }
        else
        {
            std::cout << strings[statement[1]];
        }
    }
    else if (numbers.find(statement[1]) != numbers.end())
    {
        std::cout << numbers[statement[1]];
    }
    // if the number is already in the map, and declared more than once, print an error message
    else
    {   
        if ((statement[1][0] == '\\' && statement[1][1] == 'n') && 
        (statement[1][statement[1].size()-1] == 'n' && statement[1][statement[1].size()-2] == '\\'))
        {
           statement[1] = statement[1].substr(2);
           statement[1] = statement[1].substr(0, statement[1].size() - 3);
           std::cout << std::endl << statement[1] << std::endl;
        }
        else if (statement[1][0] == '\\' && statement[1][1] == 'n')
        {
           statement[1] = statement[1].substr(2);
           std::cout << std::endl << statement[1];
        }
        else if (statement[1][statement[1].size()-2] == 'n' && statement[1][statement[1].size()-3] == '\\')
        {
              statement[1] = statement[1].substr(0, statement[1].size() - 3);
              std::cout << statement[1] << std::endl;
        }
        else 
        {
            std::cout << statement[1];
        }
    }
    
}

void MyManager::ProcessAssignment(std::vector<std::string> assignment)
{
   
    if (strings.find(assignment[0]) != strings.end())
    {
        AssignmentStrings(assignment);
    }

    if (numbers.find(assignment[0]) != numbers.end())
    {
        AssignmentNumber(assignment);
    }
}

void MyManager::AssignmentStrings(std::vector<std::string> assignment)
{
    
    if (strings.find(assignment[2]) != strings.end())
    {
        strings[assignment[0]] = strings[assignment[2]];
    }
    else 
    {
        strings[assignment[0]] = assignment[2];
    }

}
void MyManager::AssignmentNumber(std::vector<std::string> assignment)
{
    if (assignment.size() == 3)
    {
        if(numbers.find(assignment[2]) != numbers.end())
        {
            numbers[assignment[0]] = numbers[assignment[2]];
        }
        else if(isdigit(assignment[2][0]))
        {
             numbers[assignment[0]] = std::stoi(assignment[2]);    
        }
        else
        {
            std::cout << "You can't assign strings to numeric variables. ";
            exit(0);
        }
        
    }
    else if (assignment.size() > 3)
    {
        Arithmetic(assignment);
    }
}

void MyManager::Arithmetic(std::vector<std::string> assignment)
{
    // replace values 
    for (int i = 2 ; i < assignment.size(); i++)
    {
        if (numbers.find(assignment[i]) != numbers.end())
        {
             assignment[i] = std::to_string(numbers[assignment[i]]);
        }
        else if (strings.find(assignment[i]) != strings.end())
        {
            std:: cout << "Strings cannot be a part of arithmetic expression. ";
            exit(0);
        }     
    }
    // counts multiply signs 
    int multiply_counter = 0;
    for (int i = 0 ; i < assignment.size(); i++)
    {
        if (assignment[i][0] == '*')
        {
            multiply_counter++;
        }
    }
    // multiply simplify
    long long int multiplication_holder = 0;
    while (multiply_counter != 0)
    {
        for (int i = 2; i < assignment.size(); i++)
        {
            if (assignment[i][0] == '*')
            {
                multiplication_holder = stoi(assignment[i-1]) * stoi(assignment[i+1]);
                assignment.insert(assignment.begin() + (i -1), std::to_string(multiplication_holder));
                assignment.erase(assignment.begin() + i, assignment.begin() + (i + 3));       
            }
        }
        multiply_counter--;
    }

    // addition and subtraction simplify
    std::string holder = "";
    for (int i = 2; i < assignment.size(); i++)
    {
        holder = holder + " " + assignment[i];
    }
    std:: stringstream stream(holder);
    long long int answer = 0;
    std:: string op;
    std:: string number;

    stream >> number;
    answer += stoi(number);

    while (stream >> op >> number)
    {
        if (op == "+")
        {
            answer += stoi(number);
        }
        else if (op == "-")
        {
            answer -= stoi(number);
        }
    }
    numbers[assignment[0]] = answer;
}
std::string MyManager::ErrorCheck(std::vector<std::string> caution)
{
    if (caution[0] == "string")
    {
        return "\"string\" isn't \"STRING\"";
    }
    else if (caution[0] == "number")
    {
        return "\"number\" isn't \"NUMBER\"";
    }
    else if (caution[0] == "print")
    {
        return "\"print\" isn't \"PRINT\"";
    }
    // if caution[0] == NUMBER and caution[1] first letter is a number 
    else if (caution[0] == "NUMBER")
    {
        if (isdigit(caution[1][0]))
        {
            return "Variable name cannot start with a number";
        }
    }
    // if the left side of the equal sign is a number, print out left part of an assignment must be a variable
    else if (isdigit(caution[0][0]))
    {
        return "Left side of an assignment must be a variable";
    } 
    // check if there is more than two tokens for STRING, NUMBER, and PRINT
    else if (caution[0] == "STRING" || caution[0] == "NUMBER" || caution[0] == "PRINT")
    {
        if (caution.size() > 2)
        {
            return "You can't have more than one variable declared";
        }
    } 
    // if a variable is not declared in the map, print out that variable is not declared
    else if (strings.find(caution[0]) == strings.end() && numbers.find(caution[0]) == numbers.end())
    {
        return "Variable is not declared";
    }
    else
    {
        // check if there is two operators in a row
        for (int i = 0; i < caution.size(); i++)
        {
            if (caution[i] == "+" || caution[i] == "-" || caution[i] == "*" || caution[i] == "=")
            {
                if (caution[i+1] == "+" || caution[i+1] == "-" || caution[i+1] == "*")
                {
                    return "Incorrect Arithmetic Expression";
                }
            }
            // check if there two numbers in a row
            if (isdigit(caution[i][0]))
            {
                if (isdigit(caution[i+1][0]))
                {
                    return "Incorrect Arithmetic Expression";
                }
            }
        }
    }
    // loop through the entire vector and check if there a "/", if there is print out error
    for (int i = 1; i < caution.size(); i++)
    {
        if (caution[i][0] == '/')
        {
            return "Incorrect Arithmetic Expression. HUNLAN doesn't have division.";
        }
    }
    return "Perfect";
}


