#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class OS {
private:
    const int memorySize;    // Total memory size
    const int kernelSize;    // Size reserved for the kernel
    char* memory;            // Dynamically allocated memory array
    string username;         // To store the username
    string password;         // To store the password

public:
    // Initializes memory to 1 kilobyte
    // Initializes kernel size to 200
    OS(int memSize = 1024, int kernSize = 200) 
        : memorySize(memSize), kernelSize(kernSize) {
        memory = new char[memorySize]();  // Initialize allocated memory array to zero
        loadCredentials();  // Load credentials from file
    }

    // The BootStrapProgram function loads the kernel into the memory
    void BootStrapProgram() {
        for (int i = 0; i < kernelSize; i += 2) {
            memory[i] = '0';  // Place '0' if even
            if (i + 1 < kernelSize) {
                memory[i + 1] = '1';  // Place '1' if odd 
            }
        }
        cout << "Kernel loaded into memory." << std::endl;
        logIn();  // After the kernel is loaded into memory, run the OS
    }

    // Function to load credentials from file
    void loadCredentials() {
        ifstream file("password.txt");
        if (file) {
            getline(file, username);
            getline(file, password);
            file.close();
        }
    }

    // Login authentication 
    void logIn() {
        string inputUsername, inputPassword;

        if (username.empty() || password.empty()) {
            // No credentials found, prompt user to create a new account
            cout << "No existing account found. Please create a new account." << endl;
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            // Save user input to file
            ofstream file("password.txt");
            file << username << endl;
            file << password << endl;
            file.close();

            cout << "Account created!" << endl;
        } else {
            // Prompt for login with existing credentials
            cout << "Please log in." << endl;
            cout << "Enter username: ";
            getline(cin, inputUsername);
            cout << "Enter password: ";
            getline(cin, inputPassword);

            // Check credentials
            if (inputUsername == username && inputPassword == password) {
                cout << "Login successful!" << endl;
            } else {
                cout << "Login failed. Incorrect username or password." << endl;
                logIn(); // Retry login
            }
        }
        
        menu();
    }
    
    // Main menu function
    void menu(){
        cout << "Main Menu | Quit\n";
    }
};

int main() {
    OS os;  // Create an instance of the OS class

    string option;
    bool bootSystem = false;

    do {
        cout << "Type 'yes' to boot the system: ";
        cin >> option;
        cin.ignore(); // Clear the input buffer

        if (option == "yes") {
            bootSystem = true;  
        }

    } while (!bootSystem); 
    
    os.BootStrapProgram();

    return 0;
}
