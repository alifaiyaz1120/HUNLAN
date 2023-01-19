#include "HUNLAN.h"
#include <sstream>
#include <fstream>
#include <cstring>

std::vector<std::string> MyParser::operator()(const std::string& user_input)
{
    std::string word;
    std::vector<std::string> words;

    std::stringstream stream(user_input); // storing the string to stringstream

    while (stream >> word)
    {
        words.push_back(word);
    }

   std::string checkingLength;
   // store everything in words into checkingLength
    for (int i = 0; i < words.size(); i++)
    {
        checkingLength += words[i] + " ";
    }

    int counter_quotes = 0;
   
    for (int i = 0; i < checkingLength.size(); i++)
    {
        if (checkingLength[i] == '\"')
        {
            counter_quotes++;
        }
    }
    if (counter_quotes > 2)
    {
        std::cout << "No double quotes inside HUNLAN strings allowed!" << std::endl;
        exit(1);
    }
    // loop through checkingLength and check for two or more equal signs if there is more than one, print error
    int counter_equal = 0;
    for (int i = 0; i < checkingLength.size(); i++)
    {
        if (checkingLength[i] == '=')
        {
            counter_equal++;
        }
    }
    if (counter_equal > 1)
    {
        std::cout << "No more than one equal sign allowed!" << std::endl;
        exit(1);
    }
    
    if (words.size() == 1 && operationChecker(checkingLength) == 0)
    {
        for (int i = 0; i < words.size(); i++)
        {
            for (int j = 0; j < words[i].size(); j++)
            {
                if (words[i][j] == '=')
                {
                    std::string left = words[i].substr(0, j);
                    std::string right = words[i].substr(j + 1, words[i].size());
                    std::vector<std::string> left_right;

                    left_right.push_back(left);
                    left_right.push_back("=");
                    left_right.push_back(right);
                    return left_right;
                }
            }
        }
    }

    if (operationChecker(checkingLength) == 1 && quoteChecker(checkingLength) == 0)
    {
        // insert a space with any operation sign and store it a string
        std::string holder = "";
        for (int i = 0; i < words.size(); i++)
        {
           // store everything in holder
            holder += words[i] + " ";
        }
        // loop through holder and insert a space left and right of the operation sign
        for (int i = 0; i < holder.size(); i++)
        {
            if (holder[i] == '+' || holder[i] == '-' || holder[i] == '*' || holder[i] == '=')
            {
                holder.insert(i++, " ");
                holder.insert(i + 1, " ");
            }
        }
        std::string word;
        std::vector<std::string> output;
        std::stringstream stream(holder); // storing the string to stringstream

        while (stream >> word)
        {
            output.push_back(word);
        }
        return output;
    }
    
    if (checkingLength.size() > 1 && words[0] != "PRINT" && spaceChecker(checkingLength) == 1 && quoteChecker(checkingLength) == 1) 
    {
        std:: string right = "";
        std:: vector <std::string> output;
        
        // combine everything after words[2]
        for (int i = 2; i < words.size(); i++)
        {
            right += words[i] + " ";
        }
        // remove all the '\"' in string right
        for (int i = 0; i < right.size(); i++)
        {
            if (right[i] == '\"')
            {
                right.erase(i, 1);
            }
        }
        if (right[0] == ' ')
        {
            right.erase(0, 1);
        }
        output.push_back(words[0]);
        output.push_back(words[1]);
        output.push_back(right);
        return output;
    }

    if (checkingLength.size() > 1 && words[0] != "PRINT" && quoteChecker(checkingLength) == 1 && spaceChecker(checkingLength) == 0)  
    { 
       std::string left = "";
       std::string holder2 = "";
       int counter = 0;
       std::vector<std::string> output;
       for (int i = 0; i < words.size(); i++)
        {
            left += words[i] + " ";
        }
        for (int i = 0; i < left.size(); i++)
        {
            if (left[i] == '\"')
            {
                counter++;
                if (counter == 1)
                {
                    holder2 = left.substr(i + 1, left.size());
                }
                if (counter == 2)
                {
                    break;
                }
            }
        }
        // erase the quotes in holder2
        for (int i = 0; i < holder2.size(); i++)
        {
            if (holder2[i] == '\"')
            {
                holder2.erase(i, 1);
            }
        }
        if (holder2[0] == ' ')
        {
            holder2.erase(0, 1);
        }
        for (int i = 0; i < left.size(); i++)
        {
            if (left[i] == '=')
            {
                left.erase(i, left.size());
            }
        }
        output.push_back(left);
        output.push_back("=");
        output.push_back(holder2);
        return output;
    }
    
     if (words[0] == "PRINT" && quoteChecker(checkingLength) == 1)
     {
           if (words[1][0] == '\"' && isalpha(words[1][1]) || words[1][1] == '\\' || words[1][1] == ',' )
            {
                std:: string holder = "";
                int counter = 0;
                for (int i = 1; i < words.size(); i++)
                {   
                    holder = holder + " " + words[i];
                    counter += quoteChecker(words[i]);
                    // remove the quotes from holder
                                
                    if (counter == 2)
                    {
                        break;
                    }
                } 
              
                holder = holder.substr(2, holder.size() - 3);
                std::vector<std::string> right;
                right.push_back(words[0]);
                right.push_back(holder);
                return right; 
            }
            else if (words[1][0] == '\"')
            {
                    std::string holder = "";
                    int counter = 0;
                    for (int i = 1; i < words.size(); i++)
                    {
                        for (int j = 0; j < words[i].size(); j++)
                        {
                            if (words[i][j] == '\"')
                            {
                                counter++;
                            }
                            if (counter == 1)
                            {
                                holder += words[i][j];
                            }
                            if (counter == 2)
                            {
                                break;
                            }
                        }
                        if (counter == 2)
                        {
                            break;
                        }
                        holder += " ";
                    }
                    // after the first quote sign, remove only the spaces before the first letter
                    holder.erase(0, 1);
                    holder += " ";
                    // insert a space at the end of the string
                    holder = holder.substr(1, holder.size() - 2);
                    std::vector<std::string> right;
                    right.push_back(words[0]);
                    right.push_back(holder);
                    return right;
            }
        
     }  
                   
    return words;
}
  

int MyParser::quoteChecker(std::string counter)
{
    //loop through the string checking for quotes and return 1 if there is a quote and return 0 if there is no quote
    for (int i = 0; i < counter.size(); i++)
    {
        if (counter[i] == '\"')
        {
            return 1;
        }
    }
    return 0;
}

int MyParser::operationChecker(std::string counter)
{
    for (int i = 0; i < counter.size(); i++)
    {
        if (counter[i] == '+' || counter[i] == '-' || counter[i] == '*')
        {
            return 1;
        }
    }
    return 0;
}

int MyParser::spaceChecker(std::string counter)
{
    // loop through the string and check for spaces if there a '=' sign left and right of it 
    for (int i = 0; i < counter.size(); i++)
    {
        if (counter[i] == '=')
        {
            if (counter[i - 1] == ' ' && counter[i + 1] == ' ')
            {
                return 1;
            }
            else 
            {
                return 0;
            }
        }
    }
    return 0;
}

