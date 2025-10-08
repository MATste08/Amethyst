#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <cmath>

// GUI control IDs
#define ID_COMPILE 1
#define ID_EDITOR  2
#define ID_OUTPUT  3

HWND hEditor, hOutput;

// Helper for getting input from user via dialog
std::string GetInputDialog(const std::string& prompt) {
    char buf[512] = {0};
    MessageBoxA(NULL, prompt.c_str(), "Input Required", MB_OK);
    // A real input box would be better, but as a placeholder, just return "0"
    return "0";
}

// Levenshtein Distance
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

// Interpret code from string as input, return output as string
std::string RunAmethystInterpreter(const std::string& code) {
    std::istringstream fi(code);
    std::ostringstream out;
    bool abc;
    int radius, i, n, x, y;
    char c, c1;
    char command[100], command2[100], command3[100], command4[100], color[9] = "color ";
    std::map <std::string, int> ints;
    std::map <std::string, char> chars;
    std::map <std::string, std::string> strings;

    std::vector<std::string> fileWords;
    while (fi >> command) {
        fileWords.push_back(command);
    }
    // Rewind stream
    fi.clear();
    fi.seekg(0);

    // Now interpret
    fi.clear();
    fi.seekg(0);
    fi.str(code);

    while (fi >> command)
    {
        std::string scmd(command);
        if (!isValidCommand(scmd)) {
            std::string suggestion = findClosestCommand(scmd);
            if (!suggestion.empty()) out << "Unknown command '" << scmd << "'. Did you mean '" << suggestion << "'?\r\n";
            else out << "Unknown command '" << scmd << "'. No suggestion found.\r\n";
            continue;
        }

        if (!strcmp(command, "nextline")) out << "\r\n";
        if (!strcmp(command, "printspace")) out << " ";
        if (!strcmp(command, "setcolor"))
        {
            fi >> c >> c1;
            color[6] = c;
            color[7] = c1;
            // system(color); // No color in GUI
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
            // std::cin >> x;
            x = 0;
            Sleep(x);
        }
        if (!strcmp(command, "beep"))
        {
            fi >> x >> y;
            Beep(x, y);
        }
        if (!strcmp(command, "cls")) ; // no-op in GUI
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
            out << char(n);
        }
        if (!strcmp(command, "clear")) ; // no-op in GUI
        if (!strcmp(command, "rect"))
        {
            fi >> x >> y;
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++) out << char(219) << char(219);
                out << "\r\n";
            }
        }
        if (!strcmp(command, "cir"))
        {
            fi >> radius;
            for (int i = -radius; i <= radius; i++)
            {
                for (int j = -radius; j <= radius; j++)
                    if (j * j + i * i <= radius * radius + radius) out << char(219) << char(219);
                    else out << "  ";
                out << "\r\n";
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
            out << ints[command2];
        }
        if (!strcmp(command, "write_char"))
        {
            fi >> command2;
            out << chars[command2];
        }
        if (!strcmp(command, "write_string"))
        {
            fi >> command2;
            out << strings[command2];
        }
        if (!strcmp(command, "read_int"))
        {
            fi >> command2;
            // GUI input dialog for int
            std::string inp = GetInputDialog("read_int " + std::string(command2));
            ints[command2] = std::stoi(inp);
        }
        if (!strcmp(command, "read_char"))
        {
            fi >> command2;
            std::string inp = GetInputDialog("read_char " + std::string(command2));
            chars[command2] = inp.empty() ? ' ' : inp[0];
        }
        if (!strcmp(command, "read_string"))
        {
            fi >> command2;
            std::string inp = GetInputDialog("read_string " + std::string(command2));
            strings[command2] = inp;
        }
        if (!strcmp(command, "while"))
        {
            fi >> command2 >> c >> command3;
            abc = 0;
            if (c == '<' && ints[command2] < ints[command3]) abc = 1;
            if (c == '>' && ints[command2] > ints[command3]) abc = 1;
            if (c == '=' && ints[command2] == ints[command3]) abc = 1;
            if (c == '!' && ints[command2] != ints[command3]) abc = 1;
            std::streampos loopStart = fi.tellg();
            while (true) {
                fi >> command4;
                std::string scmd4(command4);
                if (!isValidCommand(scmd4)) {
                    std::string suggestion = findClosestCommand(scmd4);
                    if (!suggestion.empty()) out << "Unknown command '" << scmd4 << "' (in while). Did you mean '" << suggestion << "'?\r\n";
                    else out << "Unknown command '" << scmd4 << "' (in while). No suggestion found.\r\n";
                    if (!strcmp(command4, "endwhile")) break;
                    continue;
                }
                if (abc) {
                    if (!strcmp(command4, "nextline")) out << "\r\n";
                    if (!strcmp(command4, "printspace")) out << " ";
                    if (!strcmp(command4, "setcolor")) fi >> c >> c1;
                    if (!strcmp(command4, "int")) { fi >> command2 >> c >> n; ints[command2] = n; }
                    if (!strcmp(command4, "char")) { fi >> command2 >> c >> c1; chars[command2] = c1; }
                    if (!strcmp(command4, "string")) { fi >> command2 >> c >> command3; strings[command2] = command3; }
                    if (!strcmp(command4, "wait")) x = 0;
                    if (!strcmp(command4, "beep")) fi >> x >> y;
                    if (!strcmp(command4, "cls")) ;
                    if (!strcmp(command4, "ctoi")) { fi >> command2 >> command3; ints[command2] = chars[command3]; }
                    if (!strcmp(command4, "itoc")) { fi >> command2 >> command3; chars[command2] = char(ints[command3]); }
                    if (!strcmp(command4, "cc")) { fi >> n; out << char(n); }
                    if (!strcmp(command4, "clear")) ;
                    if (!strcmp(command4, "rect")) { fi >> x >> y; for (int i = 0; i < x; i++) { for (int j = 0; j < y; j++) out << char(219) << char(219); out << "\r\n"; } }
                    if (!strcmp(command4, "cir")) { fi >> radius; for (int i = -radius; i <= radius; i++) { for (int j = -radius; j <= radius; j++) if (j * j + i * i <= radius * radius + radius) out << char(219) << char(219); else out << "  "; out << "\r\n"; } }
                    if (!strcmp(command4, "add")) { fi >> command2 >> command3; ints[command2] += ints[command3]; }
                    if (!strcmp(command4, "decrease")) { fi >> command2 >> command3; ints[command2] -= ints[command3]; }
                    if (!strcmp(command4, "multiply")) { fi >> command2 >> command3; ints[command2] *= ints[command3]; }
                    if (!strcmp(command4, "divide")) { fi >> command2 >> command3; ints[command2] /= ints[command3]; }
                    if (!strcmp(command4, "mod")) { fi >> command2 >> command3; ints[command2] %= ints[command3]; }
                    if (!strcmp(command4, "equal")) { fi >> command2 >> command3; ints[command2] = ints[command3]; }
                    if (!strcmp(command4, "pow")) { fi >> command2 >> command3; ints[command2] = pow(ints[command2], ints[command3]); }
                    if (!strcmp(command4, "sqrt")) { fi >> command2; ints[command2] = sqrt(ints[command2]); }
                    if (!strcmp(command4, "write_int")) { fi >> command2; out << ints[command2]; }
                    if (!strcmp(command4, "write_char")) { fi >> command2; out << chars[command2]; }
                    if (!strcmp(command4, "write_string")) { fi >> command2; out << strings[command2]; }
                    if (!strcmp(command4, "read_int")) { fi >> command2; ints[command2] = 0; }
                    if (!strcmp(command4, "read_char")) { fi >> command2; chars[command2] = ' '; }
                    if (!strcmp(command4, "read_string")) { fi >> command2; strings[command2] = ""; }
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

            std::string scmd4(command4);
            if (!isValidCommand(scmd4)) {
                std::string suggestion = findClosestCommand(scmd4);
                if (!suggestion.empty()) out << "Unknown command '" << scmd4 << "' (in if). Did you mean '" << suggestion << "'?\r\n";
                else out << "Unknown command '" << scmd4 << "' (in if). No suggestion found.\r\n";
            } else {
                if (!strcmp(command4, "nextline")) out << "\r\n";
                if (!strcmp(command4, "printspace")) out << " ";
                if (!strcmp(command4, "setcolor")) fi >> c >> c1;
                if (!strcmp(command4, "int")) { fi >> command2 >> c >> n; ints[command2] = n; }
                if (!strcmp(command4, "char")) { fi >> command2 >> c >> c1; chars[command2] = c1; }
                if (!strcmp(command4, "string")) { fi >> command2 >> c >> command3; strings[command2] = command3; }
                if (!strcmp(command4, "wait")) x = 0;
                if (!strcmp(command4, "beep")) fi >> x >> y;
                if (!strcmp(command4, "cls")) ;
                if (!strcmp(command4, "ctoi")) { fi >> command2 >> command3; ints[command2] = chars[command3]; }
                if (!strcmp(command4, "itoc")) { fi >> command2 >> command3; chars[command2] = char(ints[command3]); }
                if (!strcmp(command4, "cc")) { fi >> n; out << char(n); }
                if (!strcmp(command4, "cir")) { fi >> radius; for (int i = -radius; i <= radius; i++) { for (int j = -radius; j <= radius; j++) if (j * j + i * i <= radius * radius + radius) out << char(219) << char(219); else out << "  "; out << "\r\n"; } }
                if (!strcmp(command4, "clear")) ;
                if (!strcmp(command4, "rect")) { fi >> x >> y; for (int i = 0; i < x; i++) { for (int j = 0; j < y; j++) out << char(219) << char(219); out << "\r\n"; } }
                if (!strcmp(command4, "add")) { fi >> command2 >> command3; ints[command2] += ints[command3]; }
                if (!strcmp(command4, "decrease")) { fi >> command2 >> command3; ints[command2] -= ints[command3]; }
                if (!strcmp(command4, "multiply")) { fi >> command2 >> command3; ints[command2] *= ints[command3]; }
                if (!strcmp(command4, "divide")) { fi >> command2 >> command3; ints[command2] /= ints[command3]; }
                if (!strcmp(command4, "mod")) { fi >> command2 >> command3; ints[command2] %= ints[command3]; }
                if (!strcmp(command4, "equal")) { fi >> command2 >> command3; ints[command2] = ints[command3]; }
                if (!strcmp(command4, "pow")) { fi >> command2 >> command3; ints[command2] = pow(ints[command2], ints[command3]); }
                if (!strcmp(command4, "sqrt")) { fi >> command2; ints[command2] = sqrt(ints[command2]); }
                if (!strcmp(command4, "write_int")) { fi >> command2; out << ints[command2]; }
                if (!strcmp(command4, "write_char")) { fi >> command2; out << chars[command2]; }
                if (!strcmp(command4, "write_string")) { fi >> command2; out << strings[command2]; }
                if (!strcmp(command4, "read_int")) { fi >> command2; ints[command2] = 0; }
                if (!strcmp(command4, "read_char")) { fi >> command2; chars[command2] = ' '; }
                if (!strcmp(command4, "read_string")) { fi >> command2; strings[command2] = ""; }
            }
        }
    }
    return out.str();
}

// Win32 WindowProc
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HBRUSH hBrushBackground = CreateSolidBrush(RGB(128, 0, 128)); // Purple

    switch (uMsg) {
        case WM_CREATE: {
            CreateWindow("BUTTON", "Run Code", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                         50, 30, 150, 30, hwnd, (HMENU)ID_COMPILE, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

            hEditor = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,
                                   50, 70, 800, 300, hwnd, (HMENU)ID_EDITOR, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

            hOutput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
                                   50, 390, 800, 250, hwnd, (HMENU)ID_OUTPUT, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == ID_COMPILE) {
                int length = GetWindowTextLength(hEditor);
                char* buffer = new char[length + 1];
                GetWindowText(hEditor, buffer, length + 1);

                std::string code(buffer);
                delete[] buffer;

                std::string output = RunAmethystInterpreter(code);
                SetWindowText(hOutput, output.c_str());
            }
            break;
        }
        case WM_CTLCOLOREDIT: {
            HDC hdc = (HDC)wParam;
            SetTextColor(hdc, RGB(255, 105, 180)); // Hot pink text
            SetBkColor(hdc, RGB(173, 216, 230));   // Light blue background
            return (INT_PTR)CreateSolidBrush(RGB(173, 216, 230));
        }
        case WM_ERASEBKGND: {
            RECT rect;
            GetClientRect(hwnd, &rect);
            FillRect((HDC)wParam, &rect, hBrushBackground);
            return 1;
        }
        case WM_DESTROY:
            DeleteObject(hBrushBackground);
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "AmethystCompilerWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "AMETHYST IDE",
                               WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                               CW_USEDEFAULT, CW_USEDEFAULT, 920, 700,
                               NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
