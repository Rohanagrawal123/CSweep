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
    
    //it will find al the declarations
    for (int i = 0; i < lines.size(); ++i) {
        smatch match;
        string currentLine = lines[i];
        if (regex_search(currentLine, match, declRegex)) {
            string varName = match[2];
            variables.push_back(varName);
            lastOccurrence[varName] = i + 1; //store declaration line as default last use
        }
    }

    // Second pass: Find actual last usage
    for (const string& var : variables) {
        regex usageRegex("\\b" + var + "\\b");
        for (int i = 0; i < lines.size(); ++i) {
            if (regex_search(lines[i], usageRegex)) {
                lastOccurrence[var] = i + 1;
            }
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
