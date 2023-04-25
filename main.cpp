/* Login / Registration system using C++ and cryptography
 * Author : Pramod kumar Chinthala
*/
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> // for crypt() function

using namespace std;

class User 
{
    private:
        string username;
        string password;

    public:
        User() {} // Default constructor
        User(string username, string password) : username(username), password(password) {} // Parameterized constructor

        // Getter and Setter methods for username and password
        string getUsername() const { return username; }
        void setUsername(const string& username) { this->username = username; }

        string getPassword() const { return password; }
        void setPassword(const string& password) { this->password = password; }

        // Function to register new user
        static void registerNewUser()
        {
            User user;
            cout<<"Enter the username: ";
            cin>>user.username;
            cout<<"Enter the password: ";
            cin>>user.password;

            // encrypt the password
            // SHA-512 Algorithm
            const char* salt = "$6$abcdefg$"; // the salt should be a random string of characters
            char* hashed_password = crypt(user.getPassword().c_str(), salt);
            ofstream database;
            database.open("details.txt", ios::app); // append the details to the file
            database<<user.username<<" "<<hashed_password<<endl;
            database.close();
            cout<<"User registered successfully!"<<endl;
        }

        // Function to login existing user
        static void loginUser()
        {
            User user;
            cout<<"Enter the username: ";
            cin>>user.username;
            cout<<"Enter the password: ";
            cin>>user.password;

            bool found = false;
            User read_user;

            ifstream read_database("details.txt");
            while(read_database >> read_user.username >> read_user.password) 
            {
                cout<<read_user.username<<" "<<read_user.password<<endl;
                if(user.username == read_user.username && user.password == read_user.password) 
                {
                    // Hash the password entered by the user using the same salt used during registration
                    const char* salt = "$6$abcdefg$"; // the salt should be a random string of characters
                    char* hashed_password = crypt(user.getPassword().c_str(), salt);

                    // Compare the hashed password entered by the user with the hashed password in the database
                    if (strcmp(hashed_password, read_user.password.c_str()) == 0) 
                    {
                        found = true;
                        break;
                    }
                }
            }
            read_database.close();

            // print status message of login
            cout<<(found ? "User logged in successfully!" : "Invalid username or password!")<<endl;
        }
};

int main() 
{

    int option;
    cout<<"Registration / Login details"<<endl;
    cout<<"1. Register new user"<<endl;
    cout<<"2. Login existing user"<<endl;
    cout<<"Select an option (1 or 2) : "<<endl;
    cin>>option;
    switch(option) 
    {
        case 1:
            User::registerNewUser();
            break;
        case 2:
            User::loginUser();
            break;
        case 0:
            cout<<"Exit the page...."<<endl;
            return 0;
        default:
            cout<<"Please select a valid option!"<<endl;
    }
    return 0;
}
