# HUNLAN Interpreter

Welcome to the HUNLAN Interpreter! This repository contains a simple interpreter for the HUNLAN programming language, created in C++. HUNLAN is a primitive but functional language with support for numeric and string variables, mathematical expressions, and basic input/output operations.


## HUNLAN Language Features
- Accepts one instruction per line
- Allows empty lines with no instructions
- Comments denoted by # extend until the end of the line
- Case-sensitive
- Separators include spaces and tabs with support for multiple leading and trailing separators
- Two datatypes: NUMBER (8-Byte integer) and STRING (string)
- Variable declaration: datatype variable_name (follows C++ variable naming rules)
- Numeric literals consist of only digits
- String literals consist of any ASCII characters except double-quotation marks
- Assignment operator: =
- Prohibits assignment of numeric values to string variables, and vice versa
- Mathematical expressions support operators +, –, *
- Prohibits usage of string variables or literals in mathematical expressions
- Allows assigning the value of one string variable to another
- Allows negative values for variables and expressions
- PRINT command prints a single variable or literal of any type
- Prohibits using PRINT with more than one variable or literal
- Prohibits supplying mathematical expressions to PRINT
- Multiple variable declarations cause unspecified behavior

## Compilation

To compile the HUNLAN interpreter, use the following command:

```bash
g++ -std=c++17 *.cpp -o hunlan
 ```

## Usage
- Execute HUNLAN programs by creating plain text files with a .hun extension. Run the code using the following command:

```bash
./hunlan mycode.hun
 ```

## Example Scripts
For reference, example scripts are provided in the repository with the .hun file extension. These are plain text files that can be opened with any text editor. If needed, you can rename them with a .txt extension.




<img width="600" alt="Screenshot 2023-01-18 at 11 05 27 PM" src="https://user-images.githubusercontent.com/119764873/213352683-95905171-cb84-4dee-ae83-0e4b24f345c6.png">

Printed on Terminal:
<img width="900" alt="Screenshot 2023-12-16 at 7 15 49 PM" src="https://github.com/alifaiyaz1120/HUNLAN/assets/119764873/8712f77d-d0e6-4e12-9257-ed8817285bc2">

