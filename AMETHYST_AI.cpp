#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <limits>

// Levenshtein Distance function
int levenshtein(const std::string& s1, const std::string& s2) {
    const size_t m = s1.size(), n = s2.size();
    std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1));
    for (size_t i = 0; i <= m; ++i) dp[i][0] = i;
    for (size_t j = 0; j <= n; ++j) dp[0][j] = j;
    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            if (s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + std::min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }
    return dp[m][n];
}

const std::vector<std::string> AMETHYST_COMMANDS = {
    "nextline", "printspace", "setcolor", "int", "char", "string", "wait", "beep",
    "cls", "ctoi", "itoc", "cc", "clear", "rect", "cir", "add", "decrease", "multiply",
    "divide", "mod", "equal", "pow", "sqrt", "write_int", "write_char", "write_string",
    "read_int", "read_char", "read_string", "while", "endwhile", "if"
};

bool isValidCommand(const std::string& cmd) {
    for (const auto& valid : AMETHYST_COMMANDS) {
        if (cmd == valid) return true;
    }
    return false;
}

std::string findClosestCommand(const std::string& scmd) {
    int minDist = std::numeric_limits<int>::max();
    std::string closest;
    for (const std::string& valid : AMETHYST_COMMANDS) {
        int dist = levenshtein(scmd, valid);
        if (dist < minDist) {
            minDist = dist;
            closest = valid;
        }
    }
    if (minDist <= 2) return closest; // Threshold for autocorrection
    return "";
}

// Returns true if word has more than 2 consecutive identical characters
bool hasConsecutiveRepeats(const std::string& word) {
    if (word.size() < 3) return false;
    int count = 1;
    for (size_t i = 1; i < word.size(); ++i) {
        if (word[i] == word[i-1]) {
            ++count;
            if (count > 2) return true;
        } else {
            count = 1;
        }
    }
    return false;
}

// In-place autocorrect the file, prompting user for each change
void autocorrectFile(const std::string& filename) {
    std::ifstream fi(filename);
    if (!fi) {
        std::cerr << "Cannot open input file: " << filename << std::endl;
        exit(1);
    }

    std::vector<std::string> corrected;
    std::string word;
    while (fi >> word) {
        bool changed = false;
        std::string replacement = word;

        if (hasConsecutiveRepeats(word)) {
            std::cout << "Word '" << word << "' will be replaced by declaration: int " << word << "; Proceed? (Y/N): ";
            char c;
            std::cin >> c;
            if (c == 'Y' || c == 'y') {
                replacement = "int " + word + ";";
                changed = true;
            }
        } else if (!isValidCommand(word)) {
            std::string suggestion = findClosestCommand(word);
            if (!suggestion.empty()) {
                std::cout << "Word '" << word << "' will be replaced with '" << suggestion << "'. Proceed? (Y/N): ";
                char c;
                std::cin >> c;
                if (c == 'Y' || c == 'y') {
                    replacement = suggestion;
                    changed = true;
                }
            }
        }
        corrected.push_back(replacement);
    }
    fi.close();

    std::ofstream fo(filename, std::ios::trunc);
    if (!fo) {
        std::cerr << "Cannot write to output file: " << filename << std::endl;
        exit(1);
    }
    for (const std::string& w : corrected) {
        fo << w << std::endl;
    }
    fo.close();
    std::cout << "Correction finished. File overwritten: " << filename << std::endl;
}

// Interpreter logic
int main()
{
    bool abc;
    int radius, i, n, x, y;
    char c, c1;
    std::string filename;
    char command[100], command2[100], command3[100], command4[100], color[9] = "color ";
    std::cout << "Enter your Amethyst source filename: ";
    std::cin >> filename;

    std::cout << "Autocorrect will check each change and ask for confirmation before overwriting the source file.\n";
    autocorrectFile(filename);

    std::map <std::string, int> ints;
    std::map <std::string, char> chars;
    std::map <std::string, std::string> strings;
    std::ifstream fi(filename);
    system("cls");
    while (fi >> command)
    {
        if (!isValidCommand(command)) {
            std::string suggestion = findClosestCommand(command);
            if (!suggestion.empty()) {
                std::cout << "Unknown command '" << command << "'. Did you mean '" << suggestion << "'?\n";
            } else {
                std::cout << "Unknown command '" << command << "'. No suggestion found.\n";
            }
            continue;
        }

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
            fi >> x >> y;
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++) std::cout << char(219) << char(219);
                std::cout << std::endl;
            }
        }
        if (!strcmp(command, "cir"))
        {
            fi >> radius;
            for (int i = -radius; i <= radius; i++)
            {
                for (int j = -radius; j <= radius; j++)
                    if (j * j + i * i <= radius * radius + radius) std::cout << char(219) << char(219);
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
                if (!isValidCommand(command4)) {
                    std::string suggestion = findClosestCommand(command4);
                    if (!suggestion.empty()) {
                        std::cout << "Unknown command '" << command4 << "' (in while). Did you mean '" << suggestion << "'?\n";
                    } else {
                        std::cout << "Unknown command '" << command4 << "' (in while). No suggestion found.\n";
                    }
                    if (!strcmp(command4, "endwhile")) break;
                    continue;
                }
                if (abc)
                {
                    if (!strcmp(command4, "nextline")) std::cout << '\n';
                    if (!strcmp(command4, "printspace")) std::cout << ' ';
                    if (!strcmp(command4, "setcolor"))
                    {
                        fi >> c >> c1;
                        color[6] = c;
                        color[7] = c1;
                        system(color);
                    }
                    if (!strcmp(command4, "int"))
                    {
                        fi >> command2 >> c >> n;
                        ints[command2] = n;
                    }
                    if (!strcmp(command4, "char"))
                    {
                        fi >> command2 >> c >> c1;
                        chars[command2] = c1;
                    }
                    if (!strcmp(command4, "string"))
                    {
                        fi >> command2 >> c >> command3;
                        strings[command2] = command3;
                    }
                    if (!strcmp(command4, "wait"))
                    {
                        std::cin >> x;
                        Sleep(x);
                    }
                    if (!strcmp(command4, "beep"))
                    {
                        fi >> x >> y;
                        Beep(x, y);
                    }
                    if (!strcmp(command4, "cls")) system("cls");
                    if (!strcmp(command4, "ctoi"))
                    {
                        fi >> command2 >> command3;
                        ints[command2] = chars[command3];
                    }
                    if (!strcmp(command4, "itoc"))
                    {
                        fi >> command2 >> command3;
                        chars[command2] = char(ints[command3]);
                    }
                    if (!strcmp(command4, "cc"))
                    {
                        fi >> n;
                        std::cout << char(n);
                    }
                    if (!strcmp(command4, "clear")) system("CLS");
                    if (!strcmp(command4, "rect"))
                    {
                        fi >> x >> y;
                        for (int i = 0; i < x; i++)
                        {
                            for (int j = 0; j < y; j++) std::cout << char(219) << char(219);
                            std::cout << std::endl;
                        }
                    }
                    if (!strcmp(command4, "cir"))
                    {
                        fi >> radius;
                        for (int i = -radius; i <= radius; i++)
                        {
                            for (int j = -radius; j <= radius; j++)
                                if (j * j + i * i <= radius * radius + radius) std::cout << char(219) << char(219);
                                else std::cout << "  ";
                            std::cout << std::endl;
                        }
                    }
                    if (!strcmp(command4, "add"))
                    {
                        fi >> command2 >> command3;
                        ints[command2] += ints[command3];
                    }
                    if (!strcmp(command4, "decrease"))
                    {
                        fi >> command2 >> command3;
                        ints[command2] -= ints[command3];
                    }
                    if (!strcmp(command4, "multiply"))
                    {
                        fi >> command2 >> command3;
                        ints[command2] *= ints[command3];
                    }
                    if (!strcmp(command4, "divide"))
                    {
                        fi >> command2 >> command3;
                        ints[command2] /= ints[command3];
                    }
                    if (!strcmp(command4, "mod"))
                    {
                        fi >> command2 >> command3;
                        ints[command2] %= ints[command3];
                    }
                    if (!strcmp(command4, "equal"))
                    {
                        fi >> command2 >> command3;
                        ints[command2] = ints[command3];
                    }
                    if (!strcmp(command4, "pow"))
                    {
                        fi >> command2 >> command3;
                        ints[command2] = pow(ints[command2], ints[command3]);
                    }
                    if (!strcmp(command4, "sqrt"))
                    {
                        fi >> command2;
                        ints[command2] = sqrt(ints[command2]);
                    }
                    if (!strcmp(command4, "write_int"))
                    {
                        fi >> command2;
                        std::cout << ints[command2];
                    }
                    if (!strcmp(command4, "write_char"))
                    {
                        fi >> command2;
                        std::cout << chars[command2];
                    }
                    if (!strcmp(command4, "write_string"))
                    {
                        fi >> command2;
                        std::cout << strings[command2];
                    }
                    if (!strcmp(command4, "read_int"))
                    {
                        fi >> command2;
                        std::cin >> ints[command2];
                    }
                    if (!strcmp(command4, "read_char"))
                    {
                        fi >> command2;
                        std::cin >> chars[command2];
                    }
                    if (!strcmp(command4, "read_string"))
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

            if (!isValidCommand(command4)) {
                std::string suggestion = findClosestCommand(command4);
                if (!suggestion.empty()) {
                    std::cout << "Unknown command '" << command4 << "' (in if). Did you mean '" << suggestion << "'?\n";
                } else {
                    std::cout << "Unknown command '" << command4 << "' (in if). No suggestion found.\n";
                }
            } else {
                if (!strcmp(command4, "nextline")) std::cout << '\n';
                if (!strcmp(command4, "printspace")) std::cout << ' ';
                if (!strcmp(command4, "setcolor"))
                {
                    fi >> c >> c1;
                    color[6] = c;
                    color[7] = c1;
                    system(color);
                }
                if (!strcmp(command4, "int"))
                {
                    fi >> command2 >> c >> n;
                    ints[command2] = n;
                }
                if (!strcmp(command4, "char"))
                {
                    fi >> command2 >> c >> c1;
                    chars[command2] = c1;
                }
                if (!strcmp(command4, "string"))
                {
                    fi >> command2 >> c >> command3;
                    strings[command2] = command3;
                }
                if (!strcmp(command4, "wait"))
                {
                    std::cin >> x;
                    Sleep(x);
                }
                if (!strcmp(command4, "beep"))
                {
                    fi >> x >> y;
                    Beep(x, y);
                }
                if (!strcmp(command4, "cls")) system("cls");
                if (!strcmp(command4, "ctoi"))
                {
                    fi >> command2 >> command3;
                    ints[command2] = chars[command3];
                }
                if (!strcmp(command4, "itoc"))
                {
                    fi >> command2 >> command3;
                    chars[command2] = char(ints[command3]);
                }
                if (!strcmp(command4, "cc"))
                {
                    fi >> n;
                    std::cout << char(n);
                }
                if (!strcmp(command4, "cir"))
                {
                    fi >> radius;
                    for (int i = -radius; i <= radius; i++)
                    {
                        for (int j = -radius; j <= radius; j++)
                            if (j * j + i * i <= radius * radius + radius) std::cout << char(219) << char(219);
                            else std::cout << "  ";
                        std::cout << std::endl;
                    }
                }
                if (!strcmp(command4, "clear")) system("CLS");
                if (!strcmp(command4, "rect"))
                {
                    fi >> x >> y;
                    for (int i = 0; i < x; i++)
                    {
                        for (int j = 0; j < y; j++) std::cout << char(219) << char(219);
                        std::cout << std::endl;
                    }
                }
                if (!strcmp(command4, "add"))
                {
                    fi >> command2 >> command3;
                    ints[command2] += ints[command3];
                }
                if (!strcmp(command4, "decrease"))
                {
                    fi >> command2 >> command3;
                    ints[command2] -= ints[command3];
                }
                if (!strcmp(command4, "multiply"))
                {
                    fi >> command2 >> command3;
                    ints[command2] *= ints[command3];
                }
                if (!strcmp(command4, "divide"))
                {
                    fi >> command2 >> command3;
                    ints[command2] /= ints[command3];
                }
                if (!strcmp(command4, "mod"))
                {
                    fi >> command2 >> command3;
                    ints[command2] %= ints[command3];
                }
                if (!strcmp(command4, "equal"))
                {
                    fi >> command2 >> command3;
                    ints[command2] = ints[command3];
                }
                if (!strcmp(command4, "pow"))
                {
                    fi >> command2 >> command3;
                    ints[command2] = pow(ints[command2], ints[command3]);
                }
                if (!strcmp(command4, "sqrt"))
                {
                    fi >> command2;
                    ints[command2] = sqrt(ints[command2]);
                }
                if (!strcmp(command4, "write_int"))
                {
                    fi >> command2;
                    std::cout << ints[command2];
                }
                if (!strcmp(command4, "write_char"))
                {
                    fi >> command2;
                    std::cout << chars[command2];
                }
                if (!strcmp(command4, "write_string"))
                {
                    fi >> command2;
                    std::cout << strings[command2];
                }
                if (!strcmp(command4, "read_int"))
                {
                    fi >> command2;
                    std::cin >> ints[command2];
                }
                if (!strcmp(command4, "read_char"))
                {
                    fi >> command2;
                    std::cin >> chars[command2];
                }
                if (!strcmp(command4, "read_string"))
                {
                    fi >> command2;
                    std::cin >> strings[command2];
                }
            }
        }
    }
    Sleep(1000);
}
