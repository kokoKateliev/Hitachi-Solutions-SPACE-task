#include "ShuttleSchedule.h"

void input() {
    cout << "Welcome\n Hitachi Solutions Task\n Weather Conditions for SPACE shuttle launch!\n";
    cout << "Please, Enter file name: ";
    string fileName;
    cin >> fileName;
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        throw exception("Error while opening file.");
    }
    ShuttleSchedule test;
    test.gatherInformationFromFile(inputFile);
    test.writeInformationToFile();
}


int main() {
    input();
}
