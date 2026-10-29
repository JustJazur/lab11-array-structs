#include <iostream> // Provides console input and output
#include <iomanip> // Provides table formatting
#include <limits> // Supports discarding invalid numeric input
#include "observation.h" // Provides the record type and initial member values
#include "display.h" // Provides the single-observation display prototype
using namespace std;

bool readInteger(const string& prompt, int& value) {
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return true;
        }
        if (cin.eof()) {
            return false;
        }

        cout << "Invalid input. Please enter a whole number." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool readNonnegativeInteger(const string& prompt, int& value) {
    while (true) {
        if (!readInteger(prompt, value)) {
            return false;
        }
        if (value >= 0) {
            return true;
        }
        cout << "The vote count cannot be negative." << endl;
    }
}

bool readShare(const string& prompt, double& value) {
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            if (cin.eof()) {
                return false;
            }
            cout << "Invalid input. Please enter a number from 0 to 100." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (value >= 0.0 && value <= 100.0) {
            return true;
        }
        cout << "The share must be from 0 to 100." << endl;
    }
}

int main() {
    const int CAPACITY = 100; // Preserves the capacity required by the final project
    int requestedObservations = 0;
    int menuChoice = 0;

    Observation observations[CAPACITY]{};

    while (requestedObservations < 1 || requestedObservations > 3) {
        if (!readInteger("How many observations would you like to enter (1-3)? ",
                         requestedObservations)) {
            return 0;
        }
        if (requestedObservations < 1 || requestedObservations > 3) {
            cout << "The number of observations must be from 1 to 3." << endl;
        }
    }

    for (int i = 0; i < requestedObservations; ++i) {
        Observation observation;
        cout << "\nEnter observation " << i + 1 << " of "
             << requestedObservations << ":" << endl;

        if (!readInteger("ID: ", observation.id)) {
            return 0;
        }
        cout << "State: ";
        if (!getline(cin, observation.state)) {
            return 0;
        }
        cout << "County: ";
        if (!getline(cin, observation.county)) {
            return 0;
        }
        if (!readNonnegativeInteger("Democratic votes: ",
                                    observation.democraticVotes) ||
            !readNonnegativeInteger("Republican votes: ",
                                    observation.republicanVotes) ||
            !readShare("Democratic share: ", observation.democraticShare) ||
            !readShare("Republican share: ", observation.republicanShare)) {
            return 0;
        }

        observation.isEmpty = false;
        observations[i] = observation;
    }

    do { // Repeats the prototype menu without repeating the initial data entry
        cout << "\nCoRe Data Analyzer - Lab 11 prototype\n";
        cout << "1. Display Data Frame\n11. Exit application\n";
        cout << "Enter option number: ";

        if (!readInteger("", menuChoice)) {
            break;
        }

        switch (menuChoice) {
            case 1: {
                cout << left << setw(8) << "ID"
                     << setw(18) << "State"
                     << setw(22) << "County"
                     << right << setw(14) << "Dem Votes"
                     << setw(14) << "Rep Votes"
                     << setw(16) << "Dem Share"
                     << setw(16) << "Rep Share" << endl;

                int displayedObservations = 0;
                for (int i = 0; i < CAPACITY; ++i) {
                    if (!observations[i].isEmpty) {
                        displayObservation(observations[i]);
                        ++displayedObservations;
                    }
                }

                if (displayedObservations == 0) {
                    cout << "No observations to display." << endl;
                } else {
                    cout << "Displayed " << displayedObservations
                         << " observation(s)." << endl;
                }

                break;
            }
            case 11:
                cout << "Session ended." << endl; // Confirms the selected exit action
                break;
            default:
                cout << "Invalid option." << endl; // Handles a numeric option outside the prototype menu
                break;
        }
    } while (menuChoice != 11);

    return 0;
}

/*
 * Analysis:
 * 1. Why can observation ID 151 be stored at array index 0?
 * Array index 0 is the first storage slot, and ID 151 is just the record’s identifier.
 * 
 * 2. What initializes unused slots as empty, and when does a slot become occupied?
 * observations{} starts every slot empty, and a slot becomes occupied after its data is entered; I’ll keep future answers to one simple sentence.
 * 
 * 3. Why does Display examine the capacity but print only occupied observations?
 * It checks every slot because observations can be anywhere in the array, but prints only those marked occupied.
 * 
 * 4. What record is passed to displayObservation on each function call, and is it a copy?
 * Each call passes the occupied observations[i] record, and yes, it’s copied because displayObservation takes it by value.
 * 
 * 5. Why does the build command include main.cpp and display.cpp but not the headers?
 * Because the .cpp files are compiled, and their #include directives bring the headers into the build.
 */