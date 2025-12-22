#ifndef AUTH_H
#define AUTH_H

// #include <iostream>
#include <string>
#include <vector>
#include <functions.h>
using namespace std;

struct UserCred {
    string Username;
    string Password;
};

extern vector<User> users;
extern int id_buff;
extern string db_path;
extern vector<UserCred> userCreds;

typedef void(*cmdFunc)(string);

struct Command {
    string Name;
    cmdFunc functionCallback;
};

// struct User {
//     int ID;
//     string Name;
//     string Sername;
//     string Lastname;
//     int Course;
//     vector<int> Marks;
// };


int handleCommand(string cmd, string data);

void loadUserCreds();
void addUserCred(string data);

int LoginCycle();
int SessionCycle(string user);

int callSessionCmdFunc(string input_cmd, string data);
int callLoginCmdFunc(string input_cmd, string data);




#endif