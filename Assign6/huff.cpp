#include <iostream>
#include <queue>
#include <map>
#include <string>

using namespace std;

// Node structure for Huffman tree
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode *left, *right;

    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Comparison function for priority queue
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

// Function to build Huffman tree
HuffmanNode* buildHuffmanTree(map<char, int>& frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    // Create leaf nodes and push them into priority queue
    for (auto pair : frequencies) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // Build Huffman tree
    while (pq.size() != 1) {
        HuffmanNode* left = pq.top();
        pq.pop();

        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

// Function to generate Huffman codes
void generateCodes(HuffmanNode* root, string code, map<char, string>& codes) {
    if (root == nullptr)
        return;

    if (root->data != '$')
        codes[root->data] = code;

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

// Function to encode the input string
string encode(string input, map<char, string>& codes) {
    string encodedString;
    for (char c : input) {
        encodedString += codes[c];
    }
    return encodedString;
}

int main() {
    string input = "this is an example for huffman encoding";
    
    // Calculate frequencies of characters in the input string
    map<char, int> frequencies;
    for (char c : input) {
        frequencies[c]++;
    }

    // Build Huffman tree
    HuffmanNode* root = buildHuffmanTree(frequencies);

    // Generate Huffman codes
    map<char, string> codes;
    generateCodes(root, "", codes);

    // Encode the input string
    string encodedString = encode(input, codes);

    // Output Huffman codes
    cout << "Huffman Codes:\n";
    for (auto pair : codes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Output encoded string
    cout << "\nEncoded String: " << encodedString << endl;

    return 0;
}
