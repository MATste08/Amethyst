#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <string.h>
#include <windows.h>

int main()
{
    bool abc;
    int i, n, x, y;
    char c, c1;
    std::string filename;
    char command[100], command2[100], command3[100], command4[100];
    std::cin >> filename;
    std::map <std::string, int> ints;
    std::map <std::string, char> chars;
    std::map <std::string, std::string> strings;
    std::ifstream fi(filename);
    while (true)
    {
        fi >> command;
        if (!strcmp(command, "int"))fi >> command2 >> c >> ints[command2];
        if (!strcmp(command, "int"))fi >> command2 >> c >> ints[command2];
        if (!strcmp(command, "char")) fi >> command2 >> c >> chars[command2];
        if (!strcmp(command, "string")) fi >> command2 >> c >> strings[command2];
        if (!strcmp(command, "nextline")) std::cout << '\n';
        if (!strcmp(command, "wait"))
        {
            std::cin >> x;
            Sleep(x);
        }
        if (!strcmp(command, "beep"))
        {
            fi >> x >> y;
            Beep(x, y);
        }
        if (!strcmp(command, "cls")) system("cls");
        if (!strcmp(command, "ctoi"))
        {
            fi >> command2 >> command3;
            ints[command2] = chars[command3];
        }
        if (!strcmp(command, "itoc"))
        {
            fi >> command2 >> command3;
            chars[command2] = char(ints[command3]);
        }
        if (!strcmp(command, "cc"))
        {
            fi >> n;
            std::cout << char(n);
        }
        if (!strcmp(command, "add"))
        {
            fi >> command2 >> command3;
            ints[command2] += ints[command3];
        }
        if (!strcmp(command, "decrease"))
        {
            fi >> command2 >> command3;
            ints[command2] -= ints[command3];
        }
        if (!strcmp(command, "multiply"))
        {
            fi >> command2 >> command3;
            ints[command2] *= ints[command3];
        }
        if (!strcmp(command, "divide"))
        {
            fi >> command2 >> command3;
            ints[command2] /= ints[command3];
        }
        if (!strcmp(command, "write_int"))
        {
            fi >> command2;
            std::cout << ints[command2];
        }
        if (!strcmp(command, "write_char"))
        {
            fi >> command2;
            std::cout << chars[command2];
        }
        if (!strcmp(command, "write_string"))
        {
            fi >> command2;
            std::cout << strings[command2];
        }
        if (!strcmp(command, "read_int"))
        {
            fi >> command2;
            std::cin >> ints[command2];
        }
        if (!strcmp(command, "read_char"))
        {
            fi >> command2;
            std::cin >> chars[command2];
        }
        if (!strcmp(command, "read_string"))
        {
            fi >> command2;
            std::cin >> strings[command2];
        }
        if (!strcmp(command, "while"))
        {
            fi >> command2 >> c >> command3;
            abc = 0;
            if (c == '<' && ints[command2] < ints[command3]) abc = 1;
            if (c == '>' && ints[command2] > ints[command3]) abc = 1;
            if (c == '=' && ints[command2] == ints[command3]) abc = 1;
            if (c == '!' && ints[command2] != ints[command3]) abc = 1;
            while (true)
            {
                fi >> command4;
                if (abc)
                {
                    //copy here
                }
                if (!strcmp(command4, "endwhile")) break;
            }
        }
        if (!strcmp(command, "if"))
        {
            fi >> command2 >> c >> command3;
            abc = 0;
            if (c == '<' && ints[command2] < ints[command3]) abc = 1;
            if (c == '>' && ints[command2] > ints[command3]) abc = 1;
            if (c == '=' && ints[command2] == ints[command3]) abc = 1;
            if (c == '!' && ints[command2] != ints[command3]) abc = 1;
            fi >> command4;
            //copy here
        }
    }
}
