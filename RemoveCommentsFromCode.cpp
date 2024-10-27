#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <set>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

bool multiple_comment = false;

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

string keyword_list(const string &token) {
    const string keywords[] = {"if", "else", "while", "for", "return"};
    for (const string &keyword : keywords) {
        if (token == keyword) {
            return "Keyword";
        }
    }
    return "";
}

string symbol_name(const string &symbol) {
    if (symbol == "#") return "Preprocessor";
    if (symbol == "<" || symbol == ">") return "Angle Bracket";
    if (symbol == ".") return "Dot Operator";
    if (symbol == "(") return "Left Parenthesis";
    if (symbol == ")") return "Right Parenthesis";
    if (symbol == "{") return "Left Brace";
    if (symbol == "}") return "Right Brace";
    if (symbol == ",") return "Comma";
    if (symbol == ";") return "Semicolon";
    if (symbol == "_") return "Underscore";
    if (symbol == "/") return "Slash (Divide)";
    if (symbol == "@") return "At Symbol";
    if (symbol == "&") return "Bitwise AND";
    if (symbol == "&&") return "AND operator";
    if (symbol == "||") return "OR operator";
    return "Unknown Symbol";
}

void process_line(const string &line, string tokenizer[], int &tokenCount) {
    string word = "";
    for (size_t i = 0; i < line.size(); ++i) {
        char ch = line[i];

        if (isalnum(ch)) {
            word += ch;
        } else if (!isalnum(ch) && !isdigit(ch) && ch != ' ' && ch != '\n') {
            if (!word.empty()) {
                tokenizer[tokenCount++] = word;
                word = "";
            }

            if (ch == '&' && i + 1 < line.size() && line[i + 1] == '&') {
                tokenizer[tokenCount++] = "&&";
                i++;
            } else if (ch == '|' && i + 1 < line.size() && line[i + 1] == '|') {
                tokenizer[tokenCount++] = "||";
                i++;
            } else {
                tokenizer[tokenCount++] = string(1, ch);
            }
        } else {
            if (!word.empty()) {
                tokenizer[tokenCount++] = word;
                word = "";
            }
        }
    }
    if (!word.empty()) {
        tokenizer[tokenCount++] = word;
    }
}

void write_tokens(ofstream &output, string tokenizer[], int tokenCount) {
    output << "Lexemes              Token Name           Attribute Value\n";
    for (int i = 0; i < tokenCount; ++i) {
        const string &token = tokenizer[i];

        if (!isalnum(token[0]) && token[0] != '+' && token[0] != '-' && token[0] != '*' && token[0] != '/' && token[0] != '=') {
            string symbolName = symbol_name(token);
            output << token << string(20 - token.length(), ' ') << "Special symbol      " << symbolName << '\n';
        } else if (!isalnum(token[0])) {
            string symbolName = symbol_name(token);
            output << token << string(20 - token.length(), ' ') << "Operator            " << symbolName << '\n';
        } else if (isdigit(token[0])) {
            output << token << string(20 - token.length(), ' ') << "Number              Constant\n";
        } else {
            string found_token = keyword_list(token);
            if (!found_token.empty()) {
                output << token << string(20 - token.length(), ' ') << found_token << "              ---\n";
            } else {
                output << token << string(20 - token.length(), ' ') << "id                 Pointer to symbol table\n";
            }
        }
    }
}

void findVariables(const string& cleanedCode, vector<string>& variableNames, vector<string>& variableTypes) {
    int startOfCodeBlock = 0;

    while (cleanedCode[startOfCodeBlock] != '{' && startOfCodeBlock < cleanedCode.length()) {
        startOfCodeBlock++;
    }

    int lengthOfContent = cleanedCode.length();
    int currentIndex = startOfCodeBlock + 1;

    while (currentIndex < lengthOfContent) {
        if (cleanedCode[currentIndex] == ' ' && cleanedCode.substr(currentIndex + 1, 3) == "int") {
            currentIndex += 5; // Skip "int "
            string currentVariableName = "";

            while (cleanedCode[currentIndex] != ';' && currentIndex < lengthOfContent) {
                if (cleanedCode[currentIndex] == ',') {
                    if (!currentVariableName.empty()) {
                        variableNames.push_back(currentVariableName);
                        variableTypes.push_back("int");
                        currentVariableName = "";
                    }
                    currentIndex++;
                    continue;
                }

                if (isalnum(cleanedCode[currentIndex]) || cleanedCode[currentIndex] == '_') {
                    currentVariableName += cleanedCode[currentIndex];
                }

                if (cleanedCode[currentIndex + 1] == ' ' || cleanedCode[currentIndex + 1] == ';') {
                    if (!currentVariableName.empty()) {
                        variableNames.push_back(currentVariableName);
                        variableTypes.push_back("int");
                        currentVariableName = "";
                    }
                }
                currentIndex++;
            }
            if (!currentVariableName.empty()) {
                variableNames.push_back(currentVariableName);
                variableTypes.push_back("int");
            }
        } else {
            currentIndex++;
        }
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    const int maxTokens = 1000;
    string tokenizer[maxTokens];
    int tokenCount = 0;

    string cleanedCode = "";
    string string_line;

    while (getline(fin, string_line)) {
        string cleaned_line = Remove_comment(string_line);
        cleanedCode += cleaned_line + "\n";
    }
    fin.close();

    // Write cleaned code to output file
    fout << "--------------Cleaned Code--------------\n";
    fout << cleanedCode << "\n";
    
    process_line(cleanedCode, tokenizer, tokenCount);
    
    // Write tokenized output
    fout << "--------------Tokenized Output--------------\n";
    write_tokens(fout, tokenizer, tokenCount);

    // Find and write the symbol table
    vector<string> variableNames;
    vector<string> variableTypes;
    findVariables(cleanedCode, variableNames, variableTypes);

    fout << "\n--------------Symbol Table--------------\n";
    if (!variableNames.empty()) {
        for (size_t i = 0; i < variableNames.size(); i++) {
            fout << "| Variable: " << variableNames[i] << " , Type: " << variableTypes[i] <<"|\n";
        }
    } else {
        fout << "No variables detected.\n";
    }
    fout.close();

    return 0;
}