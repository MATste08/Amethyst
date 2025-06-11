#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <string.h>
#include <windows.h>
#include <math.h>
int main()
{
    bool abc;
    int radius, i, n, x, y;
    char c, c1;
    std::string filename;
    char command[100], command2[100], command3[100], command4[100], color[9] = "color ";
    std::cin >> filename;
    std::map <std::string, int> ints;
    std::map <std::string, char> chars;
    std::map <std::string, std::string> strings;
    std::ifstream fi(filename);
    system("cls");
    while (fi >> command)
    {
        if (!strcmp(command, "nextline")) std::cout << '\n';
        if (!strcmp(command, "printspace")) std::cout << ' ';
        if (!strcmp(command, "setcolor"))
        {
            fi >> c >> c1;
            color[6] = c;
            color[7] = c1;
            system(color);
        }
        if (!strcmp(command, "int"))
        {
            fi >> command2 >> c >> n;
            ints[command2] = n;
        }
        if (!strcmp(command, "char"))
        {
            fi >> command2 >> c >> c1;
            chars[command2] = c1;
        }
        if (!strcmp(command, "string"))
        {
            fi >> command2 >> c >> command3;
            strings[command2] = command3;
        }
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
        if (!strcmp(command, "clear")) system("CLS");
        if (!strcmp(command, "rect"))
        {
            fi >> x >>y;
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++) std::cout << char(219) << char(219);
                std::cout << std::endl;
            }
        }
        if(!strcmp(command, "cir"))
        {
            fi >> radius;
            for (int i = -radius; i <= radius; i++)
            {
                for (int j = -radius; j <= radius; j++)
                    if (j * j + i * i <= radius * radius + radius) std::cout << char(219)<<char(219);
                    else std::cout << "  ";
                std::cout << std::endl;
            }
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
        if (!strcmp(command, "mod"))
        {
            fi >> command2 >> command3;
            ints[command2] %= ints[command3];
        }
        if (!strcmp(command, "equal"))
        {
            fi >> command2 >> command3;
            ints[command2] = ints[command3];
        }
        if (!strcmp(command, "pow"))
        {
            fi >> command2 >> command3;
            ints[command2] = pow(ints[command2], ints[command3]);
        }
        if (!strcmp(command, "sqrt"))
        {
            fi >> command2;
            ints[command2] = sqrt(ints[command2]);
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
                    if (!strcmp(command, "nextline")) std::cout << '\n';
                    if (!strcmp(command, "printspace")) std::cout << ' ';
                    if (!strcmp(command, "setcolor"))
                    {
                        fi >> c >> c1;
                        color[6] = c;
                        color[7] = c1;
                        system(color);
                    }
                    if (!strcmp(command, "int"))
                    {
                        fi >> command2 >> c >> n;
                        ints[command2] = n;
                    }
                    if (!strcmp(command, "char"))
                    {
                        fi >> command2 >> c >> c1;
                        chars[command2] = c1;
                    }
                    if (!strcmp(command, "string"))
                    {
                        fi >> command2 >> c >> command3;
                        strings[command2] = command3;
                    }
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
                    if(!strcmp(command, "clear")) system("CLS");
                    if(!strcmp(command, "rect"))
                    {
                        fi >> x  >>y;
                        for (int i = 0; i < x; i++)
                        {
                            for (int j = 0; j < y; j++) std::cout << char(219) << char(219);
                            std::cout << std::endl;
                        }
                    }
                    if(!strcmp(command, "cir"))
                    {
                        fi >> radius;
                        for (int i = -radius; i <= radius; i++)
                        {
                            for (int j = -radius; j <= radius; j++)
                                if (j * j + i * i <= radius * radius + radius) std::cout << char(219)<<char(219);
                                else std::cout << "  ";
                            std::cout << std::endl;
                        }
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
                    if (!strcmp(command, "mod"))
                    {
                        fi >> command2 >> command3;
                        ints[command2] %= ints[command3];
                    }
                    if (!strcmp(command, "equal"))
                    {
                        fi >> command2 >> command3;
                        ints[command2] = ints[command3];
                    }
                    if (!strcmp(command, "pow"))
                    {
                        fi >> command2 >> command3;
                        ints[command2] = pow(ints[command2], ints[command3]);
                    }
                    if (!strcmp(command, "sqrt"))
                    {
                        fi >> command2;
                        ints[command2] = sqrt(ints[command2]);
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
            if (!strcmp(command, "nextline")) std::cout << '\n';
            if (!strcmp(command, "printspace")) std::cout << ' ';
            if (!strcmp(command, "setcolor"))
            {
                fi >> c >> c1;
                color[6] = c;
                color[7] = c1;
                system(color);
            }
            if (!strcmp(command, "int"))
            {
                fi >> command2 >> c >> n;
                ints[command2] = n;
            }
            if (!strcmp(command, "char"))
            {
                fi >> command2 >> c >> c1;
                chars[command2] = c1;
            }
            if (!strcmp(command, "string"))
            {
                fi >> command2 >> c >> command3;
                strings[command2] = command3;
            }
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
            if(!strcmp(command, "cir"))
            {
                fi >> radius;
                for (int i = -radius; i <= radius; i++)
                {
                    for (int j = -radius; j <= radius; j++)
                        if (j * j + i * i <= radius * radius + radius) std::cout << char(219)<<char(219);
                        else std::cout << "  ";
                    std::cout << std::endl;
                }
            }
            if(!strcmp(command, "clear")) system("CLS");
            if(!strcmp(command, "rect"))
            {
                fi >> x >>y;
                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < y; j++) std::cout << char(219) << char(219);
                    std::cout << std::endl;
                }
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
            if (!strcmp(command, "mod"))
            {
                fi >> command2 >> command3;
                ints[command2] %= ints[command3];
            }
            if (!strcmp(command, "equal"))
            {
                fi >> command2 >> command3;
                ints[command2] = ints[command3];
            }
            if (!strcmp(command, "pow"))
            {
                fi >> command2 >> command3;
                ints[command2] = pow(ints[command2], ints[command3]);
            }
            if (!strcmp(command, "sqrt"))
            {
                fi >> command2;
                ints[command2] = sqrt(ints[command2]);
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
        }
    Sleep(1000);
}
