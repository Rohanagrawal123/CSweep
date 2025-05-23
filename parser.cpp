#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

string removeComments(const string& line) {
    string cleaned = line;
    size_t pos = cleaned.find("//");
    if (pos != string::npos)
        cleaned = cleaned.substr(0, pos);
    regex inlineBlockComment(R"(/\.?\*/)");
    cleaned = regex_replace(cleaned, inlineBlockComment, "");
    return cleaned;
}

string trim(const string& str) {
    const string whitespace = " \t\n\r";
    size_t start = str.find_first_not_of(whitespace);
    if (start == string::npos) return "";
    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}

int main() {
    ifstream file("testData/test_2.c");
    if (!file.is_open()) {
        cerr << "Failed to open test_2.c\n";
        return 1;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(removeComments(line));
    }

     // Match pointer assignment using malloc/calloc/realloc, including cases inside loops
    regex dmaRegex(R"((int|float|double|char)\s*\b([a-zA-Z_]\w*)\b\s*=\s*\([^)]+\)\s*(malloc|calloc|realloc)\s*\()");

    unordered_map<string, int> lastOccurrence;
    vector<string> dmaVars;

    for (int i = 0; i < lines.size(); ++i) {
        smatch match;
        string currentLine = trim(lines[i]);

        
         // Check if the line is inside a loop
        if (currentLine.find("for") != string::npos || currentLine.find("while") != string::npos) {
            // Handle loop-specific logic

        if (regex_search(currentLine, match, dmaRegex)) {
            string varName = match[2];
                dmaVars.push_back(varName);
                lastOccurrence[varName] = i + 1;
            }
        } else if (regex_search(currentLine, match, dmaRegex)) {
             if (regex_search(currentLine, match, dmaRegex)) {
                string varName = match[2];
                dmaVars.push_back(varName);
                lastOccurrence[varName] = i + 1;
            }
        } else if (regex_search(currentLine, match, dmaRegex)) {
            string varName = match[2];
            dmaVars.push_back(varName);
            lastOccurrence[varName] = i + 1;
        }
    }

    // Also capture variables that are declared earlier but assigned later
    regex pointerAssignRegex(R"(\b([a-zA-Z_]\w*)\s*=\s*\([^)]+\)\s*(malloc|calloc|realloc)\s*\()");

    for (int i = 0; i < lines.size(); ++i) {
        smatch match;
        string currentLine = trim(lines[i]);
        // Check if the line is inside a loop
        if (currentLine.find("for") != string::npos || currentLine.find("while") != string::npos) {
            // Handle loop-specific logic
        if (regex_search(currentLine, match, pointerAssignRegex)) {
             string varName = match[1];
                if (lastOccurrence.find(varName) == lastOccurrence.end()) {
                    dmaVars.push_back(varName);
                }
                lastOccurrence[varName] = i + 1;
            }
        } else if (regex_search(currentLine, match, pointerAssignRegex)) {
            string varName = match[1];
            if (lastOccurrence.find(varName) == lastOccurrence.end()) {
                dmaVars.push_back(varName);
            }
            lastOccurrence[varName] = i + 1;
        }
    }

    // Track last usage
    for (const string& var : dmaVars) {
        regex usageRegex("\\b" + var + "\\b");
        for (int i = 0; i < lines.size(); ++i) {
            if (regex_search(lines[i], usageRegex)) {
                lastOccurrence[var] = i + 1;
            }
        }
    }

    // Sort and output
    vector<pair<string, int>> sorted(lastOccurrence.begin(), lastOccurrence.end());
    sort(sorted.begin(), sorted.end());

    ofstream outFile("output.txt");
    //outFile << "DMA Variable\t\tLast Occurrence\n";
    for (const auto& entry : sorted) {
        outFile << entry.first << " : " << entry.second << "\n";
    }

    cout << "Output written to output.txt\n";
    return 0;
}
