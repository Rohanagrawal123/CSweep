#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    ifstream file("test_2.c");
    if (!file.is_open()) {
        cerr << "Failed to open test_2.c\n";
        return 1;
    }

    vector<string> lines;
    string line;

    //read the entire file into a vector of lines
    while (getline(file, line)) {
        lines.push_back(line);
    }

    //regex will only matxh single declared variables
    // regex declRegex(R"(\b(int|float|double|char)\s+([a-zA-Z_]\w*)\s*(=\s*[^;]+)?\s*;)");
    // unordered_map<string, int> lastOccurrence;
    // vector<string> variables;
    regex allocRegex(R"(\b([a-zA-Z_]\w*)\s*=\s*(?:\(\s*\w+\s*\*\s*\)\s*)?(malloc|calloc|realloc)\s*\(.*\)\s*;)");
    unordered_map<string, int> lastOccurrence;

    for (int i = 0; i < lines.size(); ++i) {
        smatch match;
        string currentLine = lines[i];
        if (regex_search(currentLine, match, allocRegex)) {
            string varName = match[1];
            lastOccurrence[varName] = i + 1; // line numbers are 1-based
        }
    
    }

    // Write output as a clean table
    ofstream outFile("output.txt");
    // outFile<<"Variable\t\tLast Occurrence\n";
    // outFile<<"--------\t\t----------------\n";
    for (const auto& entry : lastOccurrence) {
        outFile << entry.first << ":" << entry.second << "\n";
    }

    cout << "Output written to output.txt\n";
    return 0;
}
