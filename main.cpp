#include<iostream>
#include<windows.h>
#include<iomanip>
#include<stdlib.h>
#include<fstream>
#include<conio.h>
#include<string.h>
using namespace std;

int setWidth(string respective, string actual, int margin){
    return actual.length() - respective.length() + margin;
}

int getSize(string content, char searcher){
    int size = 1;
    for(int i = 0; i < content.length(); i++){
        if(content[i] == searcher){
            size++;
        }
    }
    return size;
}

void split(string content, char searcher, string *arr){
    int counter = 0;
    string buff = "";
    for(int i = 0; i < content.length(); i++){
        if(content[i] == searcher){
            *(arr + counter) = buff;
            counter++;
            buff = "";
        }
        else{
            buff += content[i];
        }
    }
}

class User;
class File;

class File{
    fstream file;
    public:
        void open(string name, bool append = false){
            if(append){
                file.open(name, ios::app);
            }
            else{
                file.open(name);
            }
        }
        string read(){
            string content = "";
            while(file.good()){
                content += file.get();
            }
            return content;
        }
        void close(){
            file.close();
        }
        void append(string content){
            content = "\n" + content;
            file << content;
        }
};

class User{
    string Username, Password, Name, Email;
    public:
        User(){
            Username = "";
            Password = "";
            Name = "";
        }
        void returnCredentials(string *ptr){
            *(ptr) = Username;
            *(ptr + 1) = Password;
            *(ptr + 2) = Name;
        }
        bool validateCredentials(string username, string password){
            File credFile;
            credFile.open("user-details.txt");
            string content = credFile.read();
            string lines[getSize(content, '\n')];
            split(content, '\n', lines);
            for(int i = 0; i < getSize(content, '\n'); i++){
                string details[getSize(content, '-')];
                split(lines[i], '-', details);
                if(details[0].compare(username) == 0 && details[1].compare(password) == 0){
                    Username = details[0];
                    Password = details[1];
                    Name = details[2];
                    Email = details[3];
                    return true;
                    break;
                }
            }
            credFile.close();
            return false;
        }
}user;

void showStartScreen(bool input);
void showLoginScreen(bool input);
void showRegisterScreen(bool input);

void showStartScreen(bool input){
    cout << endl << setw(75) << "Welcome to User Registration System!!!" << endl;
    cout << "\n\n\n\n" << setw(79) << "Please login or Register to continue..." << endl;
    cout << "\n\n" << setw(setWidth("1.Login", "1. Login", 50)) << "1. Login" << endl;
    cout << setw(setWidth("1.Login", "2. Register", 50)) << "2. Register" << endl;
    cout << setw(setWidth("1.Login", "3. Exit", 50)) << "3. Exit" << "\n\n\n";
    int choice;
    if(!input){
        cout << setw(setWidth("Enter your choice : ", "Wrong Input! Please enter valid choice...", 40)) << "Wrong Input! Please enter valid choice..." << endl;
    }
    cout << setw(40) << "Enter your choice : ";
    cin >> choice;

    switch(choice){
        case 1: system("cls"); showLoginScreen(true);
        case 2: system("cls"); showRegisterScreen(true); break;
        case 3: exit(0);
        default: system("cls"); showStartScreen(false);
    }
}

void showLoginScreen(bool input){
    string wish = "Do you wish to continue? (y/n) : ";
    cout << "\n\n" << setw(77) << "Login to your existing account..." << endl;
    cout << "\n\n\n\n" << setw(50) << wish;
    char choice;
    cin >> choice;
    if(choice == 'y' || choice == 'Y'){
        goto Continue;
    }
    else{
        system("cls");
        showStartScreen(true);
    }
    Continue:
        string username, password;
        cout << "\n\n\n\n" << setw(setWidth(wish, "Enter your username : ", 50)) << "Enter your  username : ";
        cin >> username;
        cout << "\n\n" << setw(setWidth(wish, "Enter you password : ", 50)) << "Enter your password : ";
        cin >> password;
        bool isValid = user.validateCredentials(username, password);
        if(password == "admin" && username == "admin"){
            ShellExecute(NULL, "open", "hotel_management\\HOTEL.exe", NULL, NULL, SW_SHOWDEFAULT);
            exit(0);
        }
        else if(isValid){
            string detailsArray[5];
            system("cls");
            user.returnCredentials(detailsArray);
            string wish = "Do you wish to continue? (y/n) : ";
            cout << "\n\n" << setw(65) << "Your Profile" << endl;
            cout << "\n\n\n\n" << setw(setWidth("Username : ", "Username : ", 50)) << "Username : ";
            cout << detailsArray[0];
            cout << "\n\n" << setw(setWidth("Username : ", "Password : ", 50)) << "Password : ";
            cout << detailsArray[1];
            cout << "\n\n" << setw(setWidth("Username : ", "Name : ", 50)) << "Name : ";
            cout << detailsArray[2];
            cout << "\n\n\n\n";
            getch();
            exit(0);
        }
        else{
            cout << "\n\n\n" << setw(setWidth(wish, "Incorrect Credentials!!!", 50)) << "Incorrect  Credentials!!!" << endl;
            cout << endl << setw(setWidth(wish, "Do you wish to continue ? (y/n) : ", 50)) << "Do you wish to continue ?  (y/n) : ";
            char cont;
            cin >> cont;
            if(cont == 'y' || cont == 'Y'){
                system("cls");
                showLoginScreen(true);
            }
            else{
                system("cls");
                showStartScreen(true);
            }
        }
}

void showRegisterScreen(bool input){
    string wish = "Do you wish to continue? (y/n) : ";
    cout << "\n\n" << setw(77) << "Register to a new account..." << endl;
    cout << "\n\n\n\n" << setw(50) << wish;
    char choice;
    cin >> choice;
    if(choice == 'y' || choice == 'Y'){
        goto Continue;
    }
    else{
        system("cls");
        showStartScreen(true);
    }
    Continue:
        string username, password, passwordConfirm, email, name;
        cout << "\n\n\n\n" << setw(setWidth(wish, "Enter your username : ", 50)) << "Enter your username : ";
        cin >> username;
        cout << "\n\n" << setw(setWidth(wish, "Enter your password : ", 50)) << "Enter your password : ";
        cin >> password;
        cout << "\n\n" << setw(setWidth(wish, "Confirm your password : ", 50)) << "Confirm your password : ";
        cin >> passwordConfirm;
        if(password != passwordConfirm){
            cout << "\n\n" << setw(setWidth(wish, "The passwords don't match... Restart process!!!", 50)) << "The passwords don't match... Restart process!!!" << endl;
            cout << setw(setWidth(wish, "Do you wish to continue ? (y/n) : ", 50)) << "Do you wish to continue ? (y/n) : ";
            char choice;
            cin >> choice;
            if(choice == 'Y' || choice == 'y'){
                system("cls");
                showRegisterScreen(true);
            }
            else{
                system("cls");
                showStartScreen(true);
            }
        }
        cout << "\n\n" << setw(setWidth(wish, "Enter your name : ", 50)) << "Enter your name : ";
        fflush(stdin); getline(cin, name);
        cout << "\n\n" << setw(setWidth(wish, "Enter your email : ", 50)) << "Enter your email : ";
        cin >> email;
        fflush(stdin);

        File credFile;
        credFile.open("user-details.txt", true);
        string details = username + "-" + password + "-" + name + "-" + email;
        credFile.append(details);
        credFile.append("\n");
        credFile.close();

        cout << "\n\n\n" << setw(setWidth(wish, "User created successfully!!!", 50)) << "User created successfully!!!" << endl;
        cout << setw(setWidth(wish, "Do you wish to login now ? (y/n) : ", 50)) << "Do you wish to login now ? (y/n) : ";
        char cont;
        cin >> cont;
        if(cont == 'Y' || cont == 'y'){
            system("cls");
            showLoginScreen(true);
        }
        else{
            system("cls");
            showStartScreen(true);
        }
}

int main(){
    showStartScreen(true);
    getch();
    return 0;
}
