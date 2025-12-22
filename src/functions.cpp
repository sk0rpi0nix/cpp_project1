#include <iostream>
#include <string>
// #include <optional>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdio>
// #include <json/json.h>
#include <fstream>
#include <session.h>
// #include </src/auth.cpp>
#include <functions.h>
#include <tools.h>
#include <array>



using namespace std;
// struct User {
//     int ID;
//     string Name;
//     string Sername;
//     string Lastname;
//     int Course;
//     vector<int> Marks;
// };

// // inner functions

// void add(string);
// void update(int, string);
// void get(int);
// void remove(int);
// void list();
// void task(int);
// void read();
// void write();


// // void sortUsers();
// bool sortString(string, string, bool);
// bool sortInt(int, int, bool);


// // utility functions

// vector<string> splitBySpace(string);


// // database functions

// int addUser(User);
// User getUser(int);
// vector<User> getAllUsers();
// int updateUser(int, User);
// int removeUser(int);



const char separator    = ' ';
const int idWidth     = 5;
const int nameWidth     = 30;
const int sernameWidth      = 30;
const int lastnameWidth = 30;
const int courseWidth = 10;
const int marksWidth = 20;
// void updateUser();







// vector<User> users;
// int id_buff = 0;



int average(array<int,4> marks) {
    int sum = 0;
    for (int num : marks) {
        sum += num;
    };
    return sum;
}
                        
void cmd_add(string data) {
    // cout << "stage 1";
    // vector<string> data = splitBySpace(line);
    SplittedData lines = checkArguments(data, 8);
    if (!lines.Valid) {
        cout << lines.Data[0] << endl;
        return;
    }
    User new_user = User{
        ID: id_buff,
        Name: lines.Data[0],
        Sername: lines.Data[1],
        Lastname: lines.Data[2],
        Course: stoi(lines.Data[3]),
        Marks: array<int,4>{}
    };
    for (int i = 4; i < 8;i++) {
        new_user.Marks[i-4] = (stoi(lines.Data[i]));
    }
    int i = addUser(new_user);
    id_buff++;
    // cout << "added user " << "'" + new_user.Name + "'" << endl;
    
    
    // cout << "stage 4";
    // users.push_back(new_user);
    return;
}

// "Name Sername Lastname Course Mark1 Mark2 Mark3 Mark4"
void cmd_update(string data) {
    SplittedData lines = checkArguments(data, 9);
    if (!lines.Valid) {
        cout << lines.Data[0] << endl;
        return;
    }

    int id = stoi(lines.Data[0]);
    int index = -1;
    for (int i = 0;i < users.size(); i++) {
        if (users[i].ID == id) {
            index = i;
            break;
        }
        cout << "No such user." << endl;
        return;
    }

    int user_id = stoi(lines.Data[0]);
    User new_user = User{
        // ID: lines.Data[0] == "_" ? : stoi(lines.Data[0]),
        ID: stoi(lines.Data[0]),
        Name: lines.Data[1] != "_" ? lines.Data[1] : users[index].Name,
        Sername: lines.Data[2] != "_" ? lines.Data[2] : users[index].Sername,
        Lastname: lines.Data[3] != "_" ? lines.Data[3] : users[index].Lastname,
        Course: lines.Data[4] != "_" ? stoi(lines.Data[4]) : users[index].Course,
        Marks: array<int,4>{}
    };
    for (int i = 5; i < 9;i++) {
        new_user.Marks[i-5] = lines.Data[i] != "_" ? stoi(lines.Data[i]) : users[index].Marks[i-5];
    }
    int i = updateUser(stoi(lines.Data[0]), new_user);
    cout << "updated user " << "'" + new_user.Name + "'" << endl;
    return;
}

void cmd_remove(string data) {
    SplittedData lines = checkArguments(data, 1); 
    if (!lines.Valid) {
        cout << lines.Data[0] << endl;
        return;
    }
    int id = stoi(lines.Data[0]);
    int i = removeUser(id);
    // cout << "added user " << "'" + new_user.Name + "'" << endl;
    return;
}

void cmd_get(string data) {
    SplittedData lines = checkArguments(data, 1); 
    if (!lines.Valid) {
        cout << lines.Data[0] << endl;
        return;
    }

    int id = stoi(lines.Data[0]);
    User user = getUser(id);
    if (user.ID == -1) {
        cout << "User not found" << endl;
        return;
    };

    string marks = 
        to_string(user.Marks[0])+", " + 
        to_string(user.Marks[1])+", " + 
        to_string(user.Marks[2])+", " + 
        to_string(user.Marks[3]);
    
    const vector<string> header = {
        "ID","Name","Sername","Last name", "Course", "Marks"
    };

    const vector<size_t> cellSizes = {
        idWidth, nameWidth, sernameWidth, lastnameWidth, courseWidth, marksWidth
    };

    const string headerDivider =
        string(idWidth, '-') + "+" +
        string(nameWidth,'-') + "+" + 
        string(sernameWidth, '-') + "+" + 
        string(lastnameWidth, '-') + "+" + 
        string(courseWidth, '-') + "+" + 
        string(marksWidth, '-') + string(10,'-');

    const vector<string> userData = {
        to_string(user.ID), user.Name, user.Sername, user.Lastname, to_string(user.Course), marks
    };

    printTableRow(header, cellSizes);
    cout << headerDivider << endl;
    printTableRow(userData, cellSizes);
    
    // cout << left
    //     << setw(idWidth) << "ID" << '|'
    //     << setw(nameWidth) << "Name" << '|'
    //     << setw(sernameWidth) << "Sername" << '|'
    //     << setw(lastnameWidth) << "Last name" << '|'
    //     << setw(courseWidth) << "Course" << '|'
    //     << setw(marksWidth) << "Marks"
    //     << endl;

    // cout << left 
    // << string(idWidth, '-') + "+" + 
    // string(nameWidth,'-') + "+" + 
    // string(sernameWidth, '-') + "+" + 
    // string(lastnameWidth, '-') + "+" + 
    // string(courseWidth, '-') + "+" + 
    // string(marksWidth, '-') + string(10,'-');
    // << endl;
    
    // cout << left
    //     << setw(idWidth) << user.ID << '|'
    //     << setw(nameWidth) << user.Name << '|'
    //     << setw(sernameWidth) << user.Sername << '|'
    //     << setw(lastnameWidth) << user.Lastname << '|'
    //     << setw(courseWidth) << user.Course << '|'
    //     << setw(marksWidth) << marks
    //     << endl;

    // cout << (user.ID + user.Name + user.Sername, user.Lastname + user.Course + user.Marks);
    return;
}

void cmd_list(string data) {
    SplittedData lines = checkArguments(data, 0); 
    if (!lines.Valid) {
        cout << lines.Data[0] << endl;
        return;
    }

    vector<User> users = getAllUsers();
    // printUser(user)
    
    // HEADER
    // ---------
    const vector<string> header = {
        "ID","Name","Sername","Last name", "Course", "Marks"
    };

    const vector<size_t> cellSizes = {
        idWidth, nameWidth, sernameWidth, lastnameWidth, courseWidth, marksWidth
    };

    const string headerDivider =
        string(idWidth, '-') + "+" +
        string(nameWidth,'-') + "+" + 
        string(sernameWidth, '-') + "+" + 
        string(lastnameWidth, '-') + "+" + 
        string(courseWidth, '-') + "+" + 
        string(marksWidth, '-') + string(10,'-');


    printTableRow(header, cellSizes);
    cout << headerDivider << endl;
    // ----------


    
    
    
    // cout << left
    //     << setw(idWidth) << "ID" << '|'
    //     << setw(nameWidth) << "Name" << '|'
    //     << setw(sernameWidth) << "Sername" << '|'
    //     << setw(lastnameWidth) << "Last name" << '|'
    //     << setw(courseWidth) << "Course" << '|'
    //     << setw(marksWidth) << "Marks"
    //     << endl;
    // cout << left 
    // << string(idWidth, '-') + "+" + 
    // string(nameWidth,'-') + "+" + 
    // string(sernameWidth, '-') + "+" + 
    // string(lastnameWidth, '-') + "+" + 
    // string(courseWidth, '-') + "+" + 
    // string(marksWidth, '-') + string(10,'-')
    // // << string(idWidth + nameWidth + sernameWidth + lastnameWidth + courseWidth + marksWidth + 10, '-')
    // << endl;

    for (User user : users) {
        string marks = 
            to_string(user.Marks[0])+", " + 
            to_string(user.Marks[1])+", " + 
            to_string(user.Marks[2])+", " + 
            to_string(user.Marks[3]);
        
        const vector<string> userData = {
            to_string(user.ID), user.Name, user.Sername, user.Lastname, to_string(user.Course), marks
        };


        printTableRow(userData, cellSizes);
        // cout << left << string(nameWidth + sernameWidth + lastnameWidth + courseWidth + marksWidth + 20, '-') << "\n";
        // string marks = to_string(user.Marks[0])+", "+ to_string(user.Marks[1])+", "+ to_string(user.Marks[2])+", "+ to_string(user.Marks[3]);
        // cout << left << string(nameWidth + sernameWidth + lastnameWidth + courseWidth + marksWidth + 20, '-') << "\n";

        // cout << left
        //     << setw(idWidth) << user.ID << '|'
        //     << setw(nameWidth) << user.Name << '|'
        //     << setw(sernameWidth) << user.Sername << '|'
        //     << setw(lastnameWidth) << user.Lastname << '|'
        //     << setw(courseWidth) << user.Course << '|'
        //     << setw(marksWidth) << marks
        //     << endl;
    }
    return;
}

void cmd_task(string data) {
    SplittedData lines = checkArguments(data, 1); 
    if (!lines.Valid) {
        cout << lines.Data[0] << endl;
        return;
    }
    int course = stoi(lines.Data[0]);
    float output;
    int sum = 0;
    int num = 0;
    for (User user : users) {
        if (user.Course == course) {
            sum += average(user.Marks);
            num++;
        }
    };
    output = float(sum) / float((num*4));
    cout << to_string(output) << "\n";
    return;
    // return output;
}

void cmd_sort(string data) {
    bool res = sortUsers(data);
    if (res) {
        cmd_list("");
    }
    return;
}

void cmd_reg(string data) {
    SplittedData lines = checkArguments(data, 2);
    if (!lines.Valid) {
        cout << lines.Data[0] << endl;
        return;
    }
    addUserToFile(lines.Data[0], lines.Data[1]);
    addUserCred(data);

}

void cmd_login(string data) {
    string username = tryLogin(data);
    if (username != "") {
        db_path = "files/dbs/" + username + ".txt";
        SessionCycle(username);
        users.clear();
    } else {
        cout << "Invalid username or password" << endl;
    }
}


void cmd_file(string data) {
    const string type = data.substr(0, data.find(' '));
    const string operation = data.substr(data.find(' ') + 1);
    
    if (type == "text") {
        textFileManagment(operation);
        return;
    } else if (type == "binary") {
        binaryFileManagment(operation);
        return;
    };
    cout << "Unknown file type. Type 'help' for help" << endl;
    // cin.ignore();
    return;
}



void textFileManagment(string data) {
    SplittedData lines = checkArguments(data, 2); // not 3 because text/bin parses before 
    if (!lines.Valid) {
        cout << lines.Data[0] << endl;
        return;
    }
    if (lines.Data[0] == "read") {
        read("files/inbox/"+lines.Data[1]);
        cout << "reading complete" << endl;
        return;
    } else if (lines.Data[0] == "write") {
        write("files/inbox/"+lines.Data[1]);
        cout << "writing complete" << endl;
        return;
    }
    cout << "Unknown operation command. Type 'help' for help" << endl;
    return;
}
void binaryFileManagment(string data) {
    SplittedData lines = checkArguments(data, 2); // not 3 because text/bin parses before 
    if (!lines.Valid) {
        cout << lines.Data[0] << endl;
        return;
    }
    if (lines.Data[0] == "read") {
        binaryRead("files/inbox/" + lines.Data[1]);
        cout << "reading complete" << endl;
        return;
    } else if (lines.Data[0] == "write") {
        binaryWrite("files/inbox/" + lines.Data[1]);
        cout << "writing complete" << endl;
        return;
    }
    cout << "Unknown operation command. Type 'help' for help" << endl;
    return;
}

void read(string path) {
    string line{};

    // Надо научиться брать путь к файлу базы из переменной db_path в auth.h
    // cout << "db_path is: " << db_path << endl;
    // string db_location = "dbs/" + ""; 
    ifstream file(path);
    while (getline(file,line)) {
        // cout << "line: " << line << endl;
        cmd_add(line);
    };
    // cout << "reading complete" << endl;
}

void write(string path) {
    ofstream new_file(path);
    for (User user: users) {
        string line = 
            user.Name + " " +
            user.Sername + " " +
            user.Lastname + " " +
            to_string(user.Course) + " " + 
            to_string(user.Marks[0])+" "+
            to_string(user.Marks[1])+" "+
            to_string(user.Marks[2])+" "+
            to_string(user.Marks[3]) + "\r\n";
        new_file << line;
    };

    // remove(db_path.c_str());
    // rename("/files/tmp.txt", db_path.c_str());
    new_file.close();
    return;
}




void sessionHelp(string data) {
    SplittedData lines = checkArguments(data, 0); // not 3 because text/bin parses before 
    if (!lines.Valid) {
        cout << lines.Data[0] << endl;
        return;
    }

    string line{};

    // Надо научиться брать путь к файлу базы из переменной db_path в auth.h
    // cout << "db_path is: " << db_path << endl;
    // string db_location = "dbs/" + ""; 
    ifstream file("files/help/sessionHelp_en.txt");
    while (getline(file,line)) {
        cout << line << endl;
        
    };
    
    // cout << "list of all available commands:\n\n";
    // cout << 
    //     "add -> Add user\n"
    //     "   8 arguments: NAME SERNAME LASTNAME COURSE MARK1 MARK2 MARK3 MARK4\n\n"
    //     <<
    //     "update -> Update user by id\n"
    //     "   9 arguments: ID NAME SERNAME LASTNAME COURSE MARK1 MARK2 MARK3 MARK4\n\n"
    //     <<
    //     "get -> Get user by id\n"
    //     "   1 argument: ID\n\n"
    //     <<
    //     "delete -> Delete user by id\n"
    //     "   1 argument: ID\n\n"
    //     <<
    //     "list -> List all users\n\n"
    //     <<
    //     "marks -> Get average course marks\n"
    //     "   1 argument: COURSE\n\n"
    //     <<
    //     "sort -> Sort users by FIELD_ID\n"
    //     "   2 arguments: FIELD_ID {acs|desc}\n"
    //     "   FIELD_ID - (ID - 1 | Name - 2 | Sername - 3 | LastName - 4 | Course 5)\n\n"
    //     <<
    //     "files -> Work with files\n"
    //     "   3 agruments: {bin|text} {read|write} FILE_PATH\n\n"
    //     <<
    //     "exit -> Save users to file and exit program"
    //     << endl;
    return;
}

void loginHelp(string data) {
    SplittedData lines = checkArguments(data, 0); // not 3 because text/bin parses before 
    if (!lines.Valid) {
        cout << lines.Data[0] << endl;
        return;
    }

    string line{};

    // Надо научиться брать путь к файлу базы из переменной db_path в auth.h
    // cout << "db_path is: " << db_path << endl;
    // string db_location = "dbs/" + ""; 
    ifstream file("files/help/loginHelp_en.txt");
    while (getline(file,line)) {
        cout << line << endl;
        
    };
}



// DATABASE FUNCTIONS
  

// Add user
int addUser(User user) {
    users.push_back(user);
    // cout << "user ", user.ID, user.Name, user.Sername, user.Lastname, user.Course, user.Marks, "'n";
    return 0;
}

// Update user by id
int updateUser(int id, User user) {
    for (int i = 0; i <= users.size() - 1; i++) {
        if (users[i].ID == id) {
            users.at(i) = user;
            return 0;
        }
    }
    cout << "no such user";
    return -1;
};

// Delete user by id
int removeUser(int id) {
    for (int i = 0; i < users.size(); i++) {
        // cout << "index:" <<i << " "<< users[i].ID << " looking for "<< id<< (users[i].ID == id) << endl;
        if (users[i].ID == id) {
            
            users.erase(users.begin() + i);
            return 0;
            // cout << "added user " << "'" + users.Name + "'" << endl;
        }
    }
    cout << "couldn't remove user\n";
    return -1;
}

// Get user by id
User getUser(int id) {
    for (User user : users) {
        if (user.ID == id) {
            return user;
        }
    }
    return User{ID:-1};
};

// Get all users;
vector<User> getAllUsers() {
    return users;
};

// typedef bool(*compareFunc)(int,int);

void mySort(compareFunc func, bool asc) {
    // 1 // int ID;
    // 2 // string Name;
    // 3 // string Sername;
    // 4 // string Lastname;
    // 5 // int Course;
    const int n = users.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (func(j, j+1) == asc) {
                swap(users[j], users[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
};

void sortMarks(bool asc, int mark) {
    const int n = users.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (_sortMarks(j,j+1,mark) == asc) {
                swap(users[j], users[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// asc isGreater result
// 0    0       1  
// 0    1       0
// 1    0       0
// 1    1       1
bool compareInt(int a, int b) {
    return (a > b);
}

bool compareString(string a, string b) {
    // cout << a << " " << b;
    int ai{0};

    int bi{0};
    if (a == b) return 0;
    while (tolower(a[ai]) == tolower(b[bi])) {
        ai++;
        bi++;
    };
    // cout << a[ai] << a[bi] << (ai > bi) << endl;
    return tolower(a[ai]) > tolower(b[bi]);
}


bool sortUsers(string data) {
    SplittedData lines = checkArguments(data, 2);
    if (!lines.Valid) {
        cout << lines.Data[0] << endl;
        return false;
    }

    size_t tmp = lines.Data[0].find(".");
    if (tmp != string::npos) {
        const string mark_i = data.substr(data.find('.') + 1);
        sortMarks(lines.Data[1] == "asc", stoi(mark_i));
        return true;
    }

    // mySort(filter, 1);
    const int filter = stoi(lines.Data[0]);
    const bool direction = lines.Data[1] == "asc"; // asc or desc
    switch (filter)

    {
    case 1: // ID    
        mySort(_sortIDs ,direction);
        return true;
        break;
    case 2: // Name
        mySort(_sortNames,direction);
        return true;
        break;
    case 3: // Sername
        mySort(_sortSernames ,direction);
        return true;
        break;
    case 4: // Lastname
        mySort(_sortLastnames,direction);
        break;
    case 5: // Course
        mySort(_sortCourses, direction);
        return true;
        break;
    default:
        return false;
        break;
    }
    return false;


    // switch ()
    // {
    // case 1:
    //     sort(users.begin(), users.end(),[asc](const User& a, const User& b){
    //         return compareInt(a.ID, b.ID, asc);
    //     });
    //     break;
    // case 2:
    //     sort(users.begin(), users.end(),[asc](const User& a, const User& b){
    //         return compareString(a.Name, b.Name, asc);
    //     });
    //     break;
    // case 3:
    //     sort(users.begin(), users.end(),[asc](const User& a, const User& b){
    //         return compareString(a.Sername, b.Sername, asc);
    //     });
    //     break;
    // case 4:
    //     sort(users.begin(), users.end(),[asc](const User& a, const User& b){
    //         return compareString(a.Lastname, b.Lastname, asc);
    //     });
    //     break;
    // case 5:
    //     sort(users.begin(), users.end(),[asc](const User& a, const User& b){
    //         return compareInt(a.Course, b.Course, asc);
    //     });
    // default:

    //     break;
    // }
    // return;
};

bool _sortIDs(int i1, int i2) {
    return compareInt(users[i1].ID, users[i2].ID);
}
bool _sortMarks(int i1, int i2, int mark) {
    return compareInt(users[i1].Marks[mark-1], users[i2].Marks[mark-1]);
}
bool _sortNames(int i1, int i2) {
    return compareString(users[i1].Name, users[i2].Name);
}
bool _sortSernames(int i1, int i2) {
    return compareString(users[i1].Sername, users[i2].Sername);
}
bool _sortLastnames(int i1, int i2) {
    return compareString(users[i1].Lastname, users[i2].Lastname);
}
bool _sortCourses(int i1, int i2) {
    return compareInt(users[i1].Course, users[i2].Course);
}




void addUserToFile(string username, string password) {
    ofstream new_file("files/auth/user_creds.txt", ios::app);

    string userLine = username + " " + password;
    new_file << userLine << endl;

    // rename("/files/tmp.txt", db_path.c_str());
    new_file.close();
    return;

}

string tryLogin(string data) {
    SplittedData lines = checkArguments(data, 2);
    if (!lines.Valid) {
        cout << lines.Data[0] << endl;
        return "";
    }

    // vector<string> creds = splitBySpace(data);
    for (UserCred userCred : userCreds) {
        if (userCred.Username == lines.Data[0]) {
            if (userCred.Password == lines.Data[1]) {
                return lines.Data[0];
            } else {
                return "";
            }
        }
    };
    return ""; 
}