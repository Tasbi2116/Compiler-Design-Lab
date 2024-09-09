#include<iostream>
#include<fstream>
using namespace std;

bool multiple_comment = false;

string Remove_comment(string string_line)
{
    bool single_comment = false;
    int string_size = string_line.length();
    string result_string = "";
    // for traverse the whole string i need to use for loop
    for(int i = 0; i<string_size; i++)
    {
        if(string_line[i] == '/' && string_line[i+1] == '/')
        {
            // means there is a single comment and so i need to make the single_comment flag true and the multile_comment flag = flase
            single_comment = true;
            multiple_comment = false;
            break; // hence there is a single line commnet so i dont need to check that line anymore.
        }
        else if(string_line[i] == '/' && string_line[i+1] == '*' && multiple_comment == false)
        {
            // when there is a multiple comment then there is first two character / and * so i have already read two character of the strig line so i can increase the i.
            multiple_comment = true;
            i++;
        }
        else if(string_line[i] == '*' && string_line[i+1] == '/') // when a multiple line comment ends.
        {
            multiple_comment = false;
            single_comment = false;
            i++;
        }
        else if(single_comment == false && multiple_comment == false)
        {
            // no comment so i have to save the exact code into the output.txt file by the result string return.
            result_string+= string_line[i];

        }
    }
    return result_string;
}
int main()
{
    fstream fin, fout;
    fin.open("input.txt");
    fout.open("output.txt");

    string string_line;
    while (getline(fin, string_line))
    {
        string string_temp = Remove_comment(string_line);
        fout<<string_temp<<endl;
    }
    
    fin.close();
    fout.close();
    return 0;
}