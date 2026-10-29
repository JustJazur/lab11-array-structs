#include <iostream> // Provides console input and output
#include <string> // Provides string and getline
using namespace std;

struct DispatchRecord {
    string destination; // Stores the shipment destination
    int boxCount = 0; // Initializes the number of boxes
};

void displayDispatch(DispatchRecord record); // Declares a function that receives one record

int main() {
    DispatchRecord shipment = {}; // Creates one initialized record
    cout << "Enter shipment destination: ";
    getline(cin, shipment.destination); // Reads a destination that may include spaces
    cout << "Enter number of boxes: ";
    cin >> shipment.boxCount;
    while (shipment.boxCount < 1) {
        cout << "Enter a positive number of boxes: ";
        cin >> shipment.boxCount; // Validates the count before displaying the record
    }
    cout << "Destination recorded: " << shipment.destination << endl;

    displayDispatch(shipment); // Sends a copy of the complete record to the function
    

    return 0;
}

void displayDispatch(DispatchRecord record) {
    cout << "Dispatch summary" << endl;
    cout << "Destination: " << record.destination << endl;
    cout << "Boxes: " << record.boxCount << endl; // Displays a member from the local record copy
}

/*
 * Analysis:
 * 1. What is the difference between DispatchRecord and shipment?
 * dispatch tell you what it has while shipment is a variable that holds the destination and box count.
 * 
 * 2. Which members are copied when displayDispatch(shipment) is called?
 * destination and box count are both copied.
 * 
 * 3. Why would changing record.boxCount inside the function leave shipment.boxCount unchanged?
 * Changing record.boxCount changes only that local copy, shipment.boxCount remains unchanged.
 */
