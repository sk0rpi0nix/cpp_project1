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
#include <sys/stat.h>

using namespace std;


vector<string> splitBySpace(string input) {
    vector<string> output;
    string s;
    stringstream ss(input);

    while (getline(ss, s, ' ')) {

        // store token string in the vector
        output.push_back(s);
    }
    // cout << "stage 2";
    return output;
}

SplittedData checkArguments(string data, int required_args) {
    vector<string> lines = splitBySpace(data);
    if (lines.size() > required_args) {
        string returnLine = "Too many arguments, expected: " + to_string(required_args) + ", got: " + to_string(lines.size());
        return {
            Valid: false,
            Data: vector<string>{returnLine}
        };
    } else if (lines.size() < required_args) {
        string returnLine = "Not enough arguments, expected: " + to_string(required_args) + ", got: " + to_string(lines.size());
        return {
            Valid: false,
            Data: vector<string>{returnLine}
        };
    };
    return {
        Valid: true,
        Data: lines
    };
}


size_t getStringLengthUTF8(string line) {
    size_t width = 0;
    for (unsigned char c : line) {
        // Count only starting bytes of UTF-8 characters
        if ((c & 0xC0) != 0x80) {  // Not a continuation byte
            width++;
        }
    }
    return width;
}

void printTableRow(vector<string> cells, vector<size_t> column_widths) {
    for (size_t i = 0; i < cells.size(); i++) {
        size_t cell_width = getStringLengthUTF8(cells[i]);
        
        if (cell_width < column_widths[i]) {
            size_t padding = column_widths[i] - cell_width;
            cout << cells[i] << string(padding, ' ');
        } else {
            cout << cells[i].substr(0, column_widths[i]);
        }
        
        if (i < cells.size() - 1) {
            cout << "|";  // Column separator
        }
    }
    cout << std::endl;
}

void binaryWrite(string path) {
    //     ofstream outfile(path, ios::binary);
    // if (!outfile) {
    //     cerr << "Ошибка открытия файла для записи" << std::endl;
    //     return;
    // }
    
    // Записываем количество пользователей
    // size_t count = users.size();
    // outfile.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    // Записываем каждого пользователя
    vector<string> lines = {};
    for (const User user : users) {

        string marks = 
            to_string(user.Marks[0])+", " + 
            to_string(user.Marks[1])+", " + 
            to_string(user.Marks[2])+", " + 
            to_string(user.Marks[3]);

        string line =  
            user.Name+" " + 
            user.Sername+" " + 
            user.Lastname+" " + 
            to_string(user.Course)+" " +
            marks;
        lines.push_back(line);
    };

    writeStringsToBinary(lines, path);
    
    // std::cout << "Записано " << count << " пользователей" << std::endl;
    // return;

    // ofstream outfile("files/inbox/"+path, std::ios::binary);
    // if (!outfile) return;
    
    // size_t count = users.size();
    // outfile.write(reinterpret_cast<char*>(&count), sizeof(size_t));
    
    // outfile.write(reinterpret_cast<char*>(users.data()), count * sizeof(User));

    // outfile.close();
}

void binaryRead(string path) {
    // std::vector<User> users;

    vector<string> lines = readStringsFromBinary(path);

    for (string line : lines) {
        cmd_add(line);
    };
    // std::ifstream infile(path, std::ios::binary);
    
    // if (!infile) {
    //     std::cerr << "Ошибка открытия файла для чтения" << std::endl;
    //     // return users;
    // }
    
    // // Читаем количество пользователей
    // size_t count;
    // infile.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    // users.reserve(count);
    
    // // Читаем каждого пользователя
    // for (size_t i = 0; i < count; i++) {
    //     User user;
    //     readUserBinary(infile, user);
    //     users.push_back(user);
        
    //     if (!infile) {
    //         std::cerr << "Ошибка чтения пользователя " << i << std::endl;
    //         users.clear();
    //         break;
    //     }
    // }
    
    // std::cout << "Прочитано " << users.size() << " пользователей" << std::endl;
    // return users;
    return;
    
    // ifstream infile(path, std::ios::binary);
    // if (!infile) return;
    
    // size_t count;
    // infile.read(reinterpret_cast<char*>(&count), sizeof(size_t));
    
    // vector<User> tmp_users(count);
    
    // infile.read(reinterpret_cast<char*>(tmp_users.data()), 
    //             count * sizeof(User));
    // infile.close();

    // for (User user : tmp_users) {
    //     users.push_back(user);
    // }
    // return;
    

}

// void writeUserBinary(std::ofstream& outfile, const User& user) {

//     outfile.write(reinterpret_cast<const char*>(&user.ID), sizeof(user.ID));

//     const size_t name_l = user.Name.size();
//     const size_t sername_l = user.Sername.size();
//     const size_t lastname_l = user.Lastname.size();
//     outfile.write(reinterpret_cast<const char*>(&user.Name), sizeof(name_l));
//     outfile.write(reinterpret_cast<const char*>(&user.Sername), sizeof(sername_l));
//     outfile.write(reinterpret_cast<const char*>(&user.Lastname), sizeof(lastname_l));
    
    
//     outfile.write(reinterpret_cast<const char*>(&user.Course), sizeof(user.Course));

//     outfile.write(reinterpret_cast<const char*>(&user.Marks), sizeof(user.Marks.size()));
    
// }

// void readUserBinary(std::ifstream& infile, User& user) {

//     infile.read(reinterpret_cast<char*>(&user.ID), sizeof(user.ID));

//     size_t name_len = 0;
//     infile.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
//     user.Name.resize(name_len);
//     infile.read(&user.Name[0], name_len);

//     size_t sername_len = 0;
//     infile.read(reinterpret_cast<char*>(&sername_len), sizeof(sername_len));
//     user.Sername.resize(sername_len);
//     infile.read(&user.Sername[0], sername_len);

//     size_t lastname_len = 0;
//     infile.read(reinterpret_cast<char*>(&lastname_len), sizeof(lastname_len));
//     user.Lastname.resize(lastname_len);
//     infile.read(&user.Lastname[0], lastname_len);


//     infile.read(reinterpret_cast<char*>(&user.Course), sizeof(user.Course));


//     // size_t marks_size = 0;
//     // infile.read(reinterpret_cast<char*>(&marks_size), sizeof(marks_size));
    
//     // // 2. Изменяем размер вектора
//     // user.Marks.resize(marks_size);
    
    
//     infile.read(reinterpret_cast<char*>(user.Marks.data()), 4 * sizeof(int));
    
// }



void writeStringsToBinary(vector<string> strings, string path) {
    ofstream file(path, ios::binary);
    
    if (!file) {
        throw runtime_error("Cannot open file: " + path);
    }
    
    // Записываем количество строк
    size_t count = strings.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    // Записываем каждую строку
    for (const auto& str : strings) {
        size_t length = str.size();
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.write(str.data(), length);
    }
    return;
}


vector<string> readStringsFromBinary(string path) {
    ifstream file(path, ios::binary);
    vector<string> result;
    
    if (!file) {
        throw runtime_error("Cannot open file: " + path);
    }
    
    // Читаем количество строк
    size_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    // Читаем каждую строку
    for (size_t i = 0; i < count; ++i) {
        size_t length;
        file.read(reinterpret_cast<char*>(&length), sizeof(length));
        
        string str(length, '\0');
        file.read(&str[0], length);
        
        result.push_back(str);
    }
    
    return result;
}

// void mkDirFunc(const string path, string name) {
//     stat()
//     // mkdir(path)
// };

