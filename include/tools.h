#ifndef TOOLS_H
#define TOOLS_H

// #include <iostream>
#include <string>
#include <vector>
#include <functions.h>
using namespace std;

// struct User {
//     int ID;
//     string Name;
//     string Sername;
//     string Lastname;
//     int Course;
//     vector<int> Marks;
// };



size_t getStringLengthUTF8(string line);
void printTableRow(vector<string> cells, vector<size_t> column_widths);

// void writeUserBinary(std::ofstream& outfile, const User& user);
// void readUserBinary(std::ifstream& infile, User& user);

void binaryRead(string path);
void binaryWrite(string path);

void writeStringsToBinary(vector<string> strings, string filename);
vector<string> readStringsFromBinary(string filename);

vector<string> splitBySpace(string);
SplittedData checkArguments(string data, int required_args);


#endif