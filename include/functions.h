#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// #include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;

struct User {
    int ID;
    string Name;
    string Sername;
    string Lastname;
    int Course;
    array<int,4> Marks;
};


struct SplittedData {
    bool Valid;
    vector<string> Data;
};

typedef bool(*compareFunc)(int,int);


// Command line functions
void cmd_add(string data);
void cmd_update(string data);
void cmd_get(string data);
void cmd_remove(string data);
void cmd_list(string data);
void cmd_task(string data);
void cmd_sort(string data);
void cmd_file(string data);

// File managment functions

void textFileManagment(string data);
void binaryFileManagment(string data);

void read(string path);
void write(string path);
void appendFile(string path);

// Sorting functions

void mySort(compareFunc func, bool asc);

void sortMarks(bool asc, int mark);
bool sortUsers(string data);
bool compareString(string a, string b, bool asc);
bool compareInt(int a, int b, bool asc);

bool _sortIDs(int i1, int i2);
bool _sortMarks(int i1, int i2, int mark);
bool _sortNames(int i1, int i2);
bool _sortSernames(int i1, int i2);
bool _sortLastnames(int i1, int i2);
bool _sortCourses(int i1, int i2);

// Help functions

void loginHelp(string data);
void sessionHelp(string data);

// Login functions

void cmd_reg(string data);
void cmd_login(string data);


void addUserToFile(string username, string password);
string tryLogin(string data);

// utility functions




// database functions

int addUser(User);
User getUser(int);
vector<User> getAllUsers();
int updateUser(int, User);
int removeUser(int);



#endif