#include <iostream> // Provides cout and endl
#include <iomanip> // Provides aligned fields and decimal formatting
#include "display.h" // Checks the definition against its declared prototype
using namespace std;

void displayObservation(Observation observation) {
    cout << left << setw(8) << observation.id
         << setw(18) << observation.state
         << setw(22) << observation.county
         << right << setw(14) << observation.democraticVotes
         << setw(14) << observation.republicanVotes
         << setw(16) << fixed << setprecision(2) << observation.democraticShare
         << setw(16) << observation.republicanShare;
    cout << endl; // Ends the row after all its fields have been displayed
}