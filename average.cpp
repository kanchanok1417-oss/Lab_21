#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        cout << "Please input numbers to find average." << endl;
        return 0;
    }

    double sum = 0;
    int count = argc - 1;
    
    for (int i = 1; i < argc; i++) {
        try {
            sum += stod(argv[i]); 
        }
        catch (...) {
            cout << "Error: Invalid input detected." << endl;
            return 1;
        }
    }

    double average = sum / count;
    cout << "---------------------------------" << endl;
    cout << "Average of " << count << " numbers = " << average << endl;
    cout << "---------------------------------" << endl;

    return 0;
}
