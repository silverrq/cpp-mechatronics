#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>
#include <conio.h>
#include <windows.h>
#include <map>
#include <cctype>
#include <cstdio>

HANDLE hConsole;

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27
#define UNKNOWN 0

using namespace std;

// Ekran temizleme fonksiyonu
void clr() {

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);

    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
    DWORD count;

    FillConsoleOutputCharacter(hOut, ' ', cellCount, {0,0}, &count);
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount, {0,0}, &count);

    SetConsoleCursorPosition(hOut, {0,0});
}


// renkler
inline void black()    { SetConsoleTextAttribute(hConsole, 0);}

inline void white()    { SetConsoleTextAttribute(hConsole,
                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
inline void gray()     { SetConsoleTextAttribute(hConsole,
                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); }
inline void red()      { SetConsoleTextAttribute(hConsole,
                        FOREGROUND_RED | FOREGROUND_INTENSITY); }
inline void green()    { SetConsoleTextAttribute(hConsole,
                        FOREGROUND_GREEN | FOREGROUND_INTENSITY); }
inline void blue()     { SetConsoleTextAttribute(hConsole,
                        FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
inline void magenta()  { SetConsoleTextAttribute(hConsole,
                        FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
inline void yellow()   {SetConsoleTextAttribute(hConsole,
                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); }
inline void brown()    { SetConsoleTextAttribute(hConsole,
                        BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN); }
inline void silver()   { SetConsoleTextAttribute(hConsole, 
                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
inline void gold()     { SetConsoleTextAttribute(hConsole, 
                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED); }
inline void purple()   { SetConsoleTextAttribute(hConsole, 
                        FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
inline void orange()   { SetConsoleTextAttribute(hConsole,
                        FOREGROUND_RED | FOREGROUND_GREEN); }
inline void reset()    { SetConsoleTextAttribute(hConsole, 0); }

// yavaş yazma efekti
void ws(const string& text, int delay_ms = 5) {
    for (char karakter : text) {

        if (_kbhit()) {
            _getch();
        }

        cout << karakter << flush;
        this_thread::sleep_for(chrono::milliseconds(delay_ms));
    }
}

// enter girdisi bekleme
void waitForEnter() {
    while (_kbhit()) {
        _getch();
    }
    cin.clear();
    while (true) {
        int key = _getch();
        if (key == ENTER) break;
        while (_kbhit()) _getch();
    }
}

// bekle
void wait(int ms = 1000) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}


// gelen girdiyi okuyup tuş tespiti yapma
int readKey() {
    int key = _getch();
    if (key == 224) {
        int second = _getch();
        if (second == UP) return UP;
        if (second == DOWN) return DOWN;
    }
    if (key == ENTER) return ENTER;
    if (key == ESC) return ESC;
    return UNKNOWN;
}

// Girilen girdi ESC ise true değilse false döndür
bool escapeCheck() {
    if (_kbhit()) {
        int key = _getch();
        if (key == ESC) return true;
        else _ungetch(key);
    }
    return false;
}

// Menü
void menu(int selected) {
    clr();
    gray();
    cout << "\nWelcome to the Resistor Calculator!\n\n";
    cout << "\n────────────────────────────────────────\n\n";
    reset();
    const char* arrow[4] = { "  ", "  ", "  ", "  " };
    arrow[selected] = "► ";

    if(selected == 0) {
        green();
    }else white();
    cout << arrow[0] << "1. 4 Band Resistor Calculation\n";
    cout << "   ╭──|██|██|██|██|──╮\n\n";

    if(selected == 1) {
        green();
    }else white();
    cout << arrow[1] << "2. 5 Band Resistor Calculation\n";
    cout << "   ╭──|██|██|██|██|██|──╮\n\n";

    if(selected == 2) {
        green();
    }else white();
    cout << arrow[2] << "3. 6 Band Resistor Calculation\n";
    cout << "   ╭──|██|██|██|██|██|██|──╮\n\n";

    if(selected == 3) {
        red();
    }else white();
    cout << arrow[3] << "4. Exit\n\n";

    gray();
    cout << "────────────────────────────────────────\n";
    cout << "Up/Down arrow keys: Select | Enter: Confirm | ESC: Exit\n";
    reset();
}

// Menü fonksiyonu
int arrowKeyMenu() {
    int selected = 0;
    int max = 4;
    while (true) {
        menu(selected);
        int key = readKey();
        if (key == UP) selected = (selected - 1 + max) % max;
        else if (key == DOWN) selected = (selected + 1) % max;
        else if (key == ENTER) return selected + 1;
        else if (key == ESC) return 4;
    }
}

// Rehber
void information(int bandcount) {
    gray();
    cout << "\n" << bandcount << " Band Resistor Calculator\n" << endl;
    cout << "────────────────────────────────────────" << endl << endl;
    reset();
    yellow();
    cout << "●Enter colors using their English name." << endl;
    cout << "●Press ESC to return to the menu while entering colors." << endl;
    cout << "●Colors: black, brown, red, orange, yellow, green, blue, purple & violet, gray, white" << endl;
    cout << "●Multiplier Colors: black, brown, red, orange, yellow, green, blue, violet & purple, gray, white, gold & golden, silver" << endl;
    cout << "●Tolerance Colors: gold & golden, silver, violet & purple, brown, red, green, blue, gray" << endl;
    if(bandcount == 6) {
        cout << "●Temperature Coefficient Colors: black, brown, red, orange, yellow, green, blue, violet & purple, gray, white" << endl;
    }
    reset();
    orange();
    cout << "\n\n────────── Band Descriptions ──────────\n\n" << endl;
    reset();
    gray();
    cout << "● First band is the leftmost band." << endl;
    cout << "● Second band is the one next to the first band." << endl;

    if (bandcount == 4) {
        cout << "● Third band is the multiplier band." << endl;
        cout << "● Fourth band is the tolerance band." << endl;
    }else {
        cout << "● Third band is the third significant digit band." << endl;
        cout << "● Fourth band is the multiplier band." << endl;
        cout << "● Fifth band is the tolerance band." << endl;
        if (bandcount == 6) {
            cout << "● Sixth band is the temperature coefficient band." << endl;
        }
    }
    reset();
    gray();
    cout << "\n────────────────────────────────────────" << endl;
    reset();
    green();
    ws("\nPress Enter to continue...");
    reset();
    waitForEnter();
}

// MAPLER
map<string, int> digitMap = {
    {"black", 0},{"brown", 1},{"red", 2},{"orange", 3},{"yellow", 4},
    {"green", 5},{"blue", 6},{"purple", 7}, {"violet", 7}, {"gray", 8},{"white", 9},
};

map<string, int> multiplierMap = {
    {"black", 0},{"brown", 1},{"red", 2},{"orange", 3},{"yellow", 4},
    {"green", 5},{"blue", 6},{"purple", 7}, {"violet", 7}, {"gray", 8},{"white", 9},
    {"gold", -1}, {"silver", -2}, {"golden", -1}
};

map<string, double> tolmap = {
    {"gold", 5},{"golden", 5},
    {"silver", 10}, {"brown", 1},
    {"red", 2},{"green", 0.5},{"blue", 0.25},
    {"purple", 0.1},{"violet", 0.1},{"gray", 0.05}
};

map<string, int> tempmap = {
    {"black", 250},{"brown", 100},{"red", 50},{"orange", 15},{"yellow", 25},
    {"green", 20},{"blue", 10},{"purple", 5}, {"violet", 5},{"gray", 1},{"white", 0}
};


// Program sonu
bool end() {
    green(); ws("\nPress Enter to return main menu |"); reset(); red(); ws(" ESC to Exit..."); reset();
    while (true) {
        int key = _getch();
        if (key == ENTER) {
            clr();
            purple();
            ws("\nReturning to the main menu..."); reset();
            wait(1500);
            clr();
            return true;
        }
        if (key == ESC) return false;
    }
}

// Renk girdisi sırasında her bir harfi kontrol eden,
// Hatalı girdide tekrar girdiren ve girilen harfleri küçülten fonksiyon
template<typename T>
bool getBandInput(string& input, const map<string, T>& mp) {
    input.clear();
    green();
    cout << "> ";
    reset();
    white();
    while (true) {
        int key = _getch();

        if (key == ESC) {
            clr();
            purple();
            ws("\nReturning to the main menu...");
            reset();
            wait(1500);
            return false; // Menüye dön
        }
        else if (key == ENTER) {
            if (!input.empty() && mp.find(input) != mp.end()) {
                cout << endl;
                return true;
            }
            red();
            ws("\nInvalid input! Enter a valid color name > ");
            reset();
            white();
            input.clear();
        }
        else if (key == 8) { // BACKSPACE
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b";
            }
        }
        else {
            input.push_back(tolower(key)); // Küçük Harfe Çevirme
            cout << (char)tolower(key);
        }
    }
}

// Büyüklükler
const double GIGA = 1000000000.0;
const double MEGA = 1000000.0;
const double KILO = 1000.0;

string format(double value) {

    double absValue = fabs(value);
    double displayValue = value;
    string unit = " Ω";

    if(absValue >= GIGA) {
        displayValue = value / GIGA;
        unit = " GΩ";
    }
    else if(absValue >= MEGA) {
        displayValue = value / MEGA;
        unit = " MΩ";
    }
    else if(absValue >= KILO) {
        displayValue = value / KILO;
        unit = " kΩ";
    }

    double rounded = round(displayValue * 1000.0) / 1000.0; // Yuvarlama
    string s = to_string(rounded);
    s.erase(s.find_last_not_of('0') + 1, string::npos);
    if (!s.empty() && s.back() == '.') s.pop_back();
    return s + unit;
}

// Direncin bant rengini sembolize etmek için gerekli kontroller ve çıktılar
void printBand(string color) {
    if(color == "black") black();
    else if(color == "brown") brown();
    else if(color == "red") red();
    else if(color == "orange") orange();
    else if(color == "yellow") yellow();
    else if(color == "green") green();
    else if(color == "blue") blue();
    else if(color == "purple") purple();
    else if(color == "violet") purple();
    else if(color == "gray") gray();
    else if(color == "white") white();
    else if(color == "gold" || color == "golden") {
        yellow();
    }else if(color == "silver") {
        gray();
    }

    cout << "██";
    reset();
}

// Ayırıcı
void inputHeader(int bandCount) {
    blue(); cout << "\n   "; cout << bandCount; reset(); white(); cout << " Band Resistor\n"; reset();
    white(); cout << "────────────────────────────────────────\n"; reset();
}

int main() {

    // Renk isimli fonksiyonlar textleri boyamak için kullanılıyor

    SetConsoleOutputCP(65001); // UTF-8
    SetConsoleCP(65001);

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Font değiştirme, UI renklendirme vs.
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 20;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Cascadia Mono");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);


    string b1, b2, b3, b4, b5, b6; // Bant değişkenleri

    clr();
    blue();
    ws("\nWelcome to the Resistor Calculator!\n");
    reset();
    wait(1000);
    green();
    ws("\nPress Enter to continue...");
    reset();
    waitForEnter();

    clr();
    purple();
    ws("\nLogging into the system...");
    reset();
    wait(1500);

    while (true) {
        clr();
        int secim = arrowKeyMenu();
        clr();

        bool backToMenu = false; // Bayrak

        if (secim == 4) break;

        int bandCount;

        if (secim == 1) bandCount = 4;
        else if (secim == 2) bandCount = 5;
        else if (secim == 3) bandCount = 6;
        else bandCount = 0;

        information(bandCount);
        clr();

        inputHeader(bandCount);
        white(); ws("\nEnter the "); reset(); yellow();  ws("color"); reset(); white();  ws(" of the "); reset();
        orange();  ws("FIRST"); reset(); white();  ws(" band "); reset();

        if (!getBandInput(b1, digitMap)) continue;
        clr();

        inputHeader(bandCount);
        white(); ws("\nEnter the "); reset(); yellow();  ws("color"); reset(); white();  ws(" of the "); reset();
        orange(); ws("SECOND"); reset(); white(); ws(" band "); reset();

        if (!getBandInput(b2, digitMap)) continue;
        clr();

        double value = 0;
        double tolerance = 0;

        if (bandCount == 4) {

            inputHeader(bandCount);
            white(); ws("\nEnter the "); reset(); yellow();  ws("color"); reset(); white();  ws(" of the "); reset();
            orange();  ws("THIRD"); reset(); white();  ws(" band"); reset(); purple(); ws(" (Multiplier) "); reset();

            if (!getBandInput(b3, multiplierMap)) continue;
            clr();

            inputHeader(bandCount);
            white(); ws("\nEnter the "); reset(); yellow(); ws("color"); reset(); white(); ws(" of the "); reset();
            orange(); ws("FOURTH"); reset(); white(); ws(" band"); reset(); purple(); ws(" (Tolerance) "); reset();

            if (!getBandInput(b5, tolmap)) continue;
            clr();

            value = (digitMap[b1] * 10 + digitMap[b2]) * pow(10, multiplierMap[b3]);
            tolerance = tolmap[b5];
        }
        else {

            inputHeader(bandCount);
            white(); ws("\nEnter the "); reset(); yellow();  ws("color"); reset(); white();  ws(" of the "); reset();
            orange();  ws("THIRD"); reset(); white();  ws(" band "); reset();

            if (!getBandInput(b3, digitMap)) continue;
            clr();

            inputHeader(bandCount);
            white(); ws("\nEnter the "); reset(); yellow();  ws("color"); reset(); white();  ws(" of the "); reset();
            orange();  ws("FOURTH"); reset(); white();  ws(" band"); reset(); purple(); ws(" (Multiplier) "); reset();

            if (!getBandInput(b4, multiplierMap)) continue;
            clr();

            inputHeader(bandCount);
            white(); ws("\nEnter the "); reset(); yellow();  ws("color"); reset(); white();  ws(" of the "); reset();
            orange();  ws("FIFTH"); reset(); white();  ws(" band"); reset(); purple(); ws(" (Tolerance) "); reset();

            if (!getBandInput(b5, tolmap)) continue;
            clr();

            value = (digitMap[b1] * 100 + digitMap[b2] * 10 + digitMap[b3]) * pow(10, multiplierMap[b4]);
            tolerance = tolmap[b5];

            if (bandCount == 6) {

                inputHeader(bandCount);
                white(); ws("\nEnter the "); reset(); yellow();  ws("color"); reset(); white();  ws(" of the "); reset();
                orange();  ws("SIXTH"); reset(); white();  ws(" band"); reset(); purple(); ws(" (Temp Coefficient) "); reset();

                if (!getBandInput(b6, tempmap)) continue;
                reset();
                clr();
            }
        }

        clr();
        purple();
        ws("\nCalculating the resistance...");
        wait(1000);
        reset();
        clr();

        double minv = value - (value * tolerance / 100);
        double maxv = value + (value * tolerance / 100);
        
        green(); cout << "\nValues of Your Resistor:\n"; reset();
        white(); cout << "────────────────────────────────────────\n\n"; reset();
        white(); ws("This is what is your Resistor looks like:\n\n"); reset();

        if(bandCount == 4) {
            white(); cout << "╭──|"; reset(); printBand(b1); white(); cout << "|"; reset();
            white(); cout << "|"; reset(); printBand(b2); white(); cout << "|"; reset();
            white(); cout << "|"; reset(); printBand(b3); white(); cout << "|"; reset();
            white(); cout << "|"; reset(); printBand(b5); white(); cout << "|──╮\n\n"; reset();
        }else if(bandCount == 5) {
            white(); cout << "╭──|"; reset(); printBand(b1); white(); cout << "|"; reset();
            white(); cout << "|"; reset(); printBand(b2); white(); cout << "|"; reset();
            white(); cout << "|"; reset(); printBand(b3); white(); cout << "|"; reset();
            white(); cout << "|"; reset(); printBand(b4); white(); cout << "|"; reset();
            white(); cout << "|"; reset(); printBand(b5); white(); cout << "|──╮\n\n"; reset();
        }else {
            white(); cout << "╭──|"; reset(); printBand(b1); white(); cout << "|"; reset();
            white(); cout << "|"; reset(); printBand(b2); white(); cout << "|"; reset();
            white(); cout << "|"; reset(); printBand(b3); white(); cout << "|"; reset();
            white(); cout << "|"; reset(); printBand(b4); white(); cout << "|"; reset();
            white(); cout << "|"; reset(); printBand(b5); white(); cout << "|"; reset();
            white(); cout << "|"; reset(); printBand(b6); white(); cout << "|──╮\n\n"; reset();
        }
        white(); cout << "────────────────────────────────────────\n\n"; reset();
        orange(); ws("Resistance value of the Resistor: "); reset(); white(); ws(format(value)); ws(" ±%"); ws(to_string((int)tolerance)); ws("\n"); reset();
        purple(); ws("Range Value of Resistance: "); reset(); white(); ws(format(minv)); ws(" - "); ws(format(maxv)); ws("\n"); reset();

        if (bandCount == 6) {
            yellow(); ws("\nTemperature Coefficient of the Resistor: "); reset(); white(); ws(to_string(tempmap[b6])); ws(" ppm/°C\n"); reset();
        }

        if (!end()) break;
    }

    clr();
    red();
    ws("\nShutting down...");
    reset();
    wait(1500);
    clr();
    return 0;
}
