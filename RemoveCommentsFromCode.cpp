#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <vector>
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

// Function to find variables in the cleaned code
void findVariables(const string& cleanedCode, vector<string>& variableNames, vector<string>& variableTypes) {
    int startOfCodeBlock = 0;

    // Locate the start of the code block
    while (cleanedCode[startOfCodeBlock] != '{' && startOfCodeBlock < cleanedCode.length()) {
        startOfCodeBlock++;
    }

    int lengthOfContent = cleanedCode.length();
    int currentIndex = startOfCodeBlock + 1;

    // Loop through the cleaned code
    while (currentIndex < lengthOfContent) {
        // Detecting variable declarations
        if (cleanedCode[currentIndex] == ' ' && cleanedCode[currentIndex + 1] == 'i' && cleanedCode[currentIndex + 2] == 'n' && cleanedCode[currentIndex + 3] == 't' && cleanedCode[currentIndex + 4] == ' ') {
            currentIndex += 5; // Skip "int "
            string currentVariableName = ""; // Reset variable name

            while (cleanedCode[currentIndex] != ';' && currentIndex < lengthOfContent) {
                if (cleanedCode[currentIndex] == ',') {
                    // On a comma, push the current variable name (if not empty)
                    if (!currentVariableName.empty()) {
                        variableNames.push_back(currentVariableName);
                        variableTypes.push_back("int");
                        currentVariableName = ""; // Reset for the next variable
                    }
                    currentIndex++; // Skip the comma
                    continue; // Continue to the next character
                }

                // Collect variable names (letters, digits, underscore allowed)
                if ((cleanedCode[currentIndex] >= 'a' && cleanedCode[currentIndex] <= 'z') || 
                    (cleanedCode[currentIndex] >= 'A' && cleanedCode[currentIndex] <= 'Z') || 
                    (cleanedCode[currentIndex] >= '0' && cleanedCode[currentIndex] <= '9') || 
                    cleanedCode[currentIndex] == '_') {
                    currentVariableName += cleanedCode[currentIndex];
                }

                // If we reach the end of the variable name (space or semicolon)
                if (cleanedCode[currentIndex + 1] == ' ' || cleanedCode[currentIndex + 1] == ';') {
                    if (!currentVariableName.empty()) {
                        variableNames.push_back(currentVariableName);
                        variableTypes.push_back("int");
                        currentVariableName = ""; // Reset for the next variable
                    }
                }
                currentIndex++;
            }

            // To capture the last variable before the semicolon
            if (!currentVariableName.empty()) {
                variableNames.push_back(currentVariableName);
                variableTypes.push_back("int");
            }
        }

        // Similar logic applies for "float", "char", and "bool" declarations...
        // You would repeat the same logic for these variable types, ensuring commas are handled correctly.
        // For "float":
        else if (cleanedCode[currentIndex] == ' ' && cleanedCode[currentIndex + 1] == 'f' && cleanedCode[currentIndex + 2] == 'l' && cleanedCode[currentIndex + 3] == 'o' && cleanedCode[currentIndex + 4] == 'a' && cleanedCode[currentIndex + 5] == 't' && cleanedCode[currentIndex + 6] == ' ') {
            currentIndex += 7; // Skip "float "
            string currentVariableName = ""; // Reset variable name

            while (cleanedCode[currentIndex] != ';' && currentIndex < lengthOfContent) {
                if (cleanedCode[currentIndex] == ',') {
                    // On a comma, push the current variable name (if not empty)
                    if (!currentVariableName.empty()) {
                        variableNames.push_back(currentVariableName);
                        variableTypes.push_back("float");
                        currentVariableName = ""; // Reset for the next variable
                    }
                    currentIndex++; // Skip the comma
                    continue; // Continue to the next character
                }

                if ((cleanedCode[currentIndex] >= 'a' && cleanedCode[currentIndex] <= 'z') ||
                    (cleanedCode[currentIndex] >= 'A' && cleanedCode[currentIndex] <= 'Z') ||
                    (cleanedCode[currentIndex] >= '0' && cleanedCode[currentIndex] <= '9') ||
                    cleanedCode[currentIndex] == '_') {
                    currentVariableName += cleanedCode[currentIndex];
                }

                // End of variable name (space or semicolon)
                if (cleanedCode[currentIndex + 1] == ' ' || cleanedCode[currentIndex + 1] == ';') {
                    if (!currentVariableName.empty()) {
                        variableNames.push_back(currentVariableName);
                        variableTypes.push_back("float");
                        currentVariableName = ""; // Reset for the next variable
                    }
                }
                currentIndex++;
            }

            // Capture the last variable before the semicolon
            if (!currentVariableName.empty()) {
                variableNames.push_back(currentVariableName);
                variableTypes.push_back("float");
            }
        }

        // Repeat similar logic for "char" and "bool"...

        else {
            currentIndex++; // Move to the next character if no declaration is found
        }
    }
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
    string cleanedCode = ""; // Store cleaned code for variable search
    
    fout << "Cleaned Code (without comments):\n\n";
    
    while (getline(fin, string_line)) {
        // Remove comments from each line
        string cleaned_line = Remove_comment(string_line);
        cleanedCode += cleaned_line + "\n"; // Collect all cleaned code for further processing
        
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

    // Process variables in the cleaned code
    vector<string> variableNames;
    vector<string> variableTypes;
    findVariables(cleanedCode, variableNames, variableTypes);

    // Write keywords to the output file
    fout << "\n--------------Predefined keywords in the code--------------\n";
    if (!matchedWords.empty()) {
        for (const string &word : matchedWords) {
            fout << word << endl;
        }
    } else {
        fout << "No predefined keywords matched." << endl;
    }

    // Write special characters to the output file
    fout << "\n--------------Special characters in the code--------------\n";
    if (!matchedSpecialChars.empty()) {
        for (const char &ch : matchedSpecialChars) {
            fout << ch << " - " << specialCharacters[ch] << endl;
        }
    } else {
        fout << "No special characters matched." << endl;
    }

    // Write variables to the output file
    fout << "\n--------------Symbol Table--------------\n";
    if (!variableNames.empty()) {
        for (size_t i = 0; i < variableNames.size(); i++) {
            fout << "Variable: " << variableNames[i] << ", Type: " << variableTypes[i] << endl;
        }
    } else {
        fout << "No variables detected." << endl;
    }

    fout.close();

    return 0;
}
