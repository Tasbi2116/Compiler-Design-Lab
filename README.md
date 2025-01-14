# 🌟 Compiler Design Laboratory Project (0.75 credit) 🌟

This repository contains the project for the **CSE-3206: Compiler Design Laboratory** course. The project demonstrates various compiler-related tasks implemented in **C++**, including comment removal, keyword and special character identification, and symbol table creation.

## 🚀 Project Description

The project processes a given C++ code file to perform the following tasks:

1. **Remove Comments**  
   Reads the code file (`input.txt`), removes all single-line (`//`) and multi-line (`/* */`) comments, and outputs the cleaned code to an output file.

2. **List Keywords**  
   Identifies and lists all keywords used in the code.

3. **List Special Characters**  
   Extracts and lists all special characters used in the code.

4. **Create a Symbol Table**  
   Generates a symbol table containing variable names and their respective types.

All the outputs, including the cleaned code, tokenized output, and symbol table, are written to a single output file (`output.txt`).

## 📂 Files in the Repository

- **`input.txt`**: Contains the input C++ code to be processed.
- **`output.txt`**: Contains the processed results, including the cleaned code, tokenized output, and symbol table.
- **Executable File (`exe`)**: A precompiled executable of the program for quick testing.

## 📜 Features

- **Comment Removal**: Removes both single-line and multi-line comments.
- **Keyword Detection**: Recognizes common C++ keywords such as `if`, `else`, `while`, `for`, and `return`.
- **Special Character Identification**: Identifies symbols like `#`, `{`, `}`, `;`, and operators like `&&` and `||`.
- **Symbol Table Generation**: Extracts variable names and types from the cleaned code.

## 🛠️ How to Use

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/Tasbi2116/Compiler-Design-Lab

2. Place the C++ code to be processed in the `input.txt` file.
3. Run the executable file:
   - For Windows:
     ```cmd
     RemoveCommentsFromCode.exe
     ```
   - For Unix-based systems, compile the source code (if not using the executable):
     ```bash
     g++ -o compiler_project RemoveCommentsFromCode.cpp
     ./compiler_project
     ```
4. View the results in the `output.txt` file.

## 📜 Output Format

The output file contains three main sections:

1. **Cleaned Code**  
   Displays the input code with all comments removed.

2. **Tokenized Output**  
   Lists the tokens in the code with their lexemes, token types, and attribute values.

3. **Symbol Table**  
   Displays the variables and their types found in the code.

### 📜 Example Output

#### 🔹 Cleaned Code:
```cpp
#include <stdio.h>
int main() {
    int a, b;
    printf("Hello, World!");
    return 0;
}
```

#### 🔹 Tokenized Output:
```
Lexemes              Token Name           Attribute Value
#include             Special symbol      Preprocessor
<                   Special symbol      Angle Bracket
...
```

#### 🔹 Symbol Table:
```
| Variable: a , Type: int |
| Variable: b , Type: int |
```

## 🏆 Acknowledgments

This project was completed as part of the **CSE-3206: Compiler Design Laboratory** course. The tasks implemented help in understanding the foundational concepts of compiler design and its practical applications.

## 📧 Contact

Have questions? Feel free to reach out via:

- **GitHub Issues**: [Submit an issue](../../issues)
- **Email**: [tasbi2116@cseku.ac.bd](mailto:tasbi2116@cseku.ac.bd)

## License

This repository is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
```

This `README.md` provides a comprehensive overview of your project, detailing its functionality, usage, and output, making it user-friendly for anyone viewing your GitHub repository.
