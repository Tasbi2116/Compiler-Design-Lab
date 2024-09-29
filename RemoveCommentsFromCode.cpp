#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <map>

using namespace std;

bool multiple_comment = false;

// Function to remove comments from the code
string Remove_comment(string string_line) {
    bool single_comment = false;
    int string_size = string_line.length();
    string result_string = "";

    for (int i = 0; i < string_size; i++) {
        if (string_line[i] == '/' && string_line[i + 1] == '/') {
            single_comment = true;
            multiple_comment = false;
            break; // Ignore rest of the line
        } else if (string_line[i] == '/' && string_line[i + 1] == '*' && multiple_comment == false) {
            multiple_comment = true;
            i++;
        } else if (string_line[i] == '*' && string_line[i + 1] == '/') {
            multiple_comment = false;
            single_comment = false;
            i++;
        } else if (single_comment == false && multiple_comment == false) {
            result_string += string_line[i]; // Add code that is not part of a comment
        }
    }

    return result_string;
}

int main() {
    // Predefined keywords to search for in the code
    set<string> predefinedWords = {"int", "float", "double", "if", "else", "for", "while", "return"};

    // Special characters mapping
    map<char, string> specialCharacters = {
        {'#', "hash"},
        {'<', "less than"},
        {'>', "greater than"},
        {'&', "ampersand"},
        {'@', "at the rate of"},
        {'%', "percent"},
        {'$', "dollar"},
        {'!', "exclamation mark"},
        {'*', "asterisk"},
        {'^', "Exponential character"},
        {'?', "Question mark"},
        {'.', "dot"},
        {',', "comma"}
    };

    // Open input and output files
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    string string_line;
    set<string> matchedWords;      
    set<char> matchedSpecialChars; 

    fout << "Cleaned Code (without comments):\n\n";
    
    while (getline(fin, string_line)) {
        // Remove comments from each line
        string cleaned_line = Remove_comment(string_line);
        
        // Write the cleaned code to the output file
        fout << cleaned_line << endl;
        
        // Process the cleaned line for keywords and special characters
        stringstream ss(cleaned_line);
        string word;

        while (ss >> word) {
            // Check for keywords
            if (predefinedWords.find(word) != predefinedWords.end()) {
                matchedWords.insert(word); 
            }

            // Check for special characters in each word
            for (char ch : word) {
                if (specialCharacters.find(ch) != specialCharacters.end()) {
                    matchedSpecialChars.insert(ch); 
                }
            }
        }
    }

    fin.close();

    // Write keywords to the output file
    fout << "\nPredefined keywords in the code:\n";
    if (!matchedWords.empty()) {
        for (const string &word : matchedWords) {
            fout << word << endl;
        }
    } else {
        fout << "No predefined keywords matched." << endl;
    }

    // Write special characters to the output file
    fout << "\nSpecial characters in the code:\n";
    if (!matchedSpecialChars.empty()) {
        for (const char &ch : matchedSpecialChars) {
            fout << ch << " - " << specialCharacters[ch] << endl;
        }
    } else {
        fout << "No special characters matched." << endl;
    }

    fout.close();

    return 0;
}
