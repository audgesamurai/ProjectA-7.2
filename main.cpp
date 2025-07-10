#include <iostream>
#include <cctype>
using namespace std;

const int NUM_USERS = 100;
const int NUM_PROJECTS = 10;

enum AccountType { NONE, MASTER, PROJECT };

struct UserAccount {
    AccountType type = NONE;
    int projectID = -1;
};

int main() {
    UserAccount users[NUM_USERS];
    int masterCopies = 0;
    int projectCopies[NUM_PROJECTS] = {0};

    char choice;

    while (true) {
        cout << "U)ser A)dministrator Q)uit" << endl;
        cin >> choice;
        choice = toupper(choice);

        if (choice == 'Q') break;

        if (choice == 'U') {
            int userID, copies;
            cout << "What's your user ID (0–99)? ";
            cin >> userID;

            if (userID < 0 || userID >= NUM_USERS) {
                cout << "That ID does not exist." << endl;
                continue;
            }

            cout << "How many copies do you need? ";
            cin >> copies;

            if (copies < 0) {
                cout << "That’s not a valid number." << endl;
                continue;
            }

            if (users[userID].type == MASTER) {
                masterCopies += copies;
            } else if (users[userID].type == PROJECT && users[userID].projectID >= 0 && users[userID].projectID < NUM_PROJECTS) {
                projectCopies[users[userID].projectID] += copies;
            } else {
                cout << "You’re not set up to use the copier. Ask an admin." << endl;
            }
        }

        else if (choice == 'A') {
            char adminChoice;
            cout << "B)alance M)aster P)roject" << endl;
            cin >> adminChoice;
            adminChoice = toupper(adminChoice);

            if (adminChoice == 'B') {
                cout << "Master account: " << masterCopies << " copies" << endl;
                for (int i = 0; i < NUM_PROJECTS; ++i) {
                    cout << "Project " << i << ": " << projectCopies[i] << " copies" << endl;
                }
            }

            else if (adminChoice == 'M') {
                int userID;
                cout << "User ID to connect to master (0–99)? ";
                cin >> userID;

                if (userID >= 0 && userID < NUM_USERS) {
                    users[userID].type = MASTER;
                    users[userID].projectID = -1;
                    cout << "User " << userID << " now using the master account." << endl;
                } else {
                    cout << "That’s not a valid user." << endl;
                }
            }

            else if (adminChoice == 'P') {
                int userID, projectID;
                cout << "User ID to connect to a project (0–99)? ";
                cin >> userID;
                cout << "Project ID (0–9)? ";
                cin >> projectID;

                if (userID >= 0 && userID < NUM_USERS && projectID >= 0 && projectID < NUM_PROJECTS) {
                    users[userID].type = PROJECT;
                    users[userID].projectID = projectID;
                    cout << "User " << userID << " now using project " << projectID << "." << endl;
                } else {
                    cout << "Bad user or project ID." << endl;
                }
            }

            else {
                cout << "Not a valid admin option." << endl;
            }
        }

        else {
            cout << "Not a real menu option." << endl;
        }
    }

    cout << "See ya." << endl;
    return 0;
}

