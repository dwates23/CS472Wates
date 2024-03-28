#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

// Function to decode the encoded string
string decode(string encodedString, map<string, char>& codes) {
    string decodedString;
    string code;
    for (char bit : encodedString) {
        code += bit;
        if (codes.find(code) != codes.end()) {
            decodedString += codes[code];
            code = ""; // Reset code
        }
    }
    return decodedString;
}

int main() {
    // Read encoded data from file
    ifstream encodedFile("encoded.txt");
    if (!encodedFile.is_open()) {
        cerr << "Error: Unable to open encoded file." << endl;
        return 1;
    }

    // Read Huffman codes and encoded string
    map<string, char> codes;
    string encodedString;

    string line;
    while (getline(encodedFile, line)) {
        if (line.empty()) // Skip empty lines
            continue;
        if (line.find(": ") != string::npos) { // Huffman code line
            char character = line[0];
            string code = line.substr(line.find(": ") + 2);
            codes[code] = character;
        } else { // Encoded string
            encodedString = line;
        }
    }
    encodedFile.close();

    // Decode the encoded string
    string decodedString = decode(encodedString, codes);

    // Output decoded string to a file
    ofstream outputFile("decoded.txt");
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }

    outputFile << decodedString;
    outputFile.close();

    cout << "Decompression successful. Output written to decoded.txt" << endl;

    return 0;
}
