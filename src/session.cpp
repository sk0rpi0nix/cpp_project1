#include <iostream>
#include <string>
// #include <optional>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>
// #include <json/json.h>
#include <fstream>
#include <session.h>
#include <functions.h>
#include <tools.h>

using namespace std;
// using namespace functions;

// namespace db {
vector<User> users{};
// }
int id_buff = 0;
string db_path = "";
vector<UserCred> userCreds = {};
vector<Command> sessionCommands = {
    {"add", cmd_add},
    {"update", cmd_update},
    {"get", cmd_get},
    {"remove", cmd_remove},
    {"list", cmd_list},
    {"task", cmd_task},
    {"help", sessionHelp},
    {"sort", cmd_sort},
    {"file", cmd_file},
};

vector<Command> loginCommands = {
    {"login", cmd_login},
    {"register", cmd_reg},
    {"help", loginHelp},
    // {"remove", cmd_remove},
    // {"list", cmd_list},
    // {"task", cmd_task},
};


int callSessionCmdFunc(string input_cmd, string data) {
    if (input_cmd == "exit") return -1;

    for (Command cmd: sessionCommands) {
        if (input_cmd == cmd.Name) {
            cmd.functionCallback(data);
            return 0;
        }
    };
    cout << "Invalid command. Type \"help\" for help\n";
    return 0;
}

int callLoginCmdFunc(string input_cmd, string data) {
    if (input_cmd == "exit") return -1;

    for (Command cmd: loginCommands) {
        if (input_cmd == cmd.Name) {
            cmd.functionCallback(data);
            return 0;
        }
    };

    cout << "Invalid command. Type \"help\" for help\n";
    return 0;
}

int LoginCycle() {
    const string startLine = "unautorized=> ";
    
    
    string request;

    // cin >> ws;

    while (true) {
        try {
            cout << startLine;
            cin >> ws;
        
            getline(cin, request);
    
            int space = request.find(' ');
            const string command = request.substr(0, space);
            const string data = space != -1 ? request.substr(space + 1) : "";

            int code = callLoginCmdFunc(command, data);
            if (code == -1) {
                return 0;
            }

        } catch (const exception& err) {
            cout << "Error occured but was catched:" << err.what() << endl;
        }
    
    
    }
    return 0;

}



void loadUserCreds() {
    // userCreds = {};
    string line{};

    ifstream file("files/auth/user_creds.txt");
    while (getline(file,line)) {

        // cout << "line: " << line << endl;
        addUserCred(line);
    };
    cout << "loading complete" << endl;
}

void addUserCred(string data) {
    SplittedData lines = checkArguments(data, 2);
    if (!lines.Valid) {
        cout << lines.Data[0] << endl;
        return;
    }
    const UserCred userCred = UserCred{
        Username: lines.Data[0],
        Password: lines.Data[1]
    };
    userCreds.push_back(userCred);
    ofstream file("files/dbs/"+lines.Data[0]+".txt", ios::app);
    file.close();
    return;
}



// NEEDED ARGUMENTS
// C - 8 (name surname lastname course mark1 mark2 mark3 mark4)
// R - 1 (id)
// U - 9 (id name surname lastname course mark1 mark2 mark3 mark4)
// D - 1 (id)
// L - 0
// File - 1 + 2 (bin/text + read/write path)
// Help - 0
// Sort - 2 (field_number asc/desc)
// Task (Middle)



int SessionCycle(string user) {
    read(db_path);
    const string startLine = user + "=> "; 
    // const string middleLine = user + "-> ";

    // const string a = "abcd";
    
    while (true) {
        try {
            cout << startLine;
            // cout << "cmd: \n";
            string request;
            // string data;
            string id;

            // cin.ignore();
            cin >> ws;
            getline(cin, request);
            // cin >> request;

            int space = request.find(' ');
            const string command = request.substr(0, space);
            const string data = space != -1 ? request.substr(space + 1) : "";


            // cout << command << " _ " << data << endl;
            try {
                int code = callSessionCmdFunc(command, data);
                if (code == -1) {
                    write(db_path);
                    return 0;
                }
            } catch (const invalid_argument& err) {
                cout << "error occured:" << " expected number, got text" << endl;
            }

            // switch (command[0]) 
            // {
            // case 'h':
            //     sessionHelp();                    
            //     break;
            // // add
            // case 'a':

            //     cmd_add(data);
            //     break;
            // // update
            // case 'u':
            //     cmd_update(data);
            //     break;
            // // get
            // case 'g':

            //     cmd_get(data);
                
            //     break;
            // // list
            // case 'l':
            //     cmd_list(data);
            //     break;
            // // delete
            // case 'd':

            //     cmd_remove(data);
            //     break;
            // // task
            // case 'm':

            //     cmd_task(data);

            //     break;
            // // file
            // case 'f': {
            //     // cout << "(r)ead or (w)rite?" << endl;

            //     const string type = data.substr(0, data.find(' '));
            //     const string operation = data.substr(data.find(' ') + 1);
                
            //     if (type[0] == 't') {
            //         textFileManagment(operation);
            //     } else {
            //         binaryFileManagment(operation);
            //     };
            //     // cin.ignore();
            //     break;
            // }
            // // sort
            // case 's':
            //     // cout << middleLine;
            //     // cin >> data;
            //     sortUsers(data);
            //     cmd_list(data);
            //     break;
            // // exit
            // case 'e':
            //     write(db_path);
            //     cout << "exiting..." << endl;
            //     return 0;
            // default:
            //     cout << "Invalid command. Type \"help\" for help\n";
            //     break;
            // }
        } catch (const exception& err) {
        
            cout << "error occured outer:" << err.what() << endl;
            // cout << "Error occured :\n" << << endl;
        }
        
        
    }
    return 0;

}