

// #include "mainwindow.h"
// #include <QApplication>
// #include "ui_mainwindow.h"
#include "ciphers.h"

// #define ENG_ALPH 26
// #define ASCII_A (int)'A'    // 65
// #define ASCII_Z (int)'Z'    // 90
// #define ASCII_a (int)'a'    // 97
// #define ASCII_z (int)'z'    // 122

void caesar() {
    std::string str = "abcdef";
    int step = 2;
    int int_str;
    int differ1, differ2;
//  char array[] = "abcdefghijklmnopqrstuvwxyz";

//    cout << "Enter your string: ";
//    getline(cin, str);
//    cout << "Enter length of the step: ";
//    cin >> step;

    int str_len = str.length();
    std::cout << "\n*** Modified string ***\n";
    for (int i = 0; i < str_len; ++i) {
        if (str[i] == ' ') std::cout << ' ';
        else {
            int_str = (int)str[i];
            if ((int_str >= ASCII_A) && (int_str <= ASCII_Z)) {     // UPPER case

                differ1 = ASCII_Z - int_str;
                differ2 = int_str - ASCII_A;
                if (step > differ1) {
                    std::cout << (char)(ASCII_A-1 + ((step - differ1) % ENG_ALPH));
                }
                else if (-step > differ2) {
                    std::cout << (char)(ASCII_Z+1 + ((step + differ2) % ENG_ALPH));
                }
                else std::cout << (char)(int_str + step);
            }
            else if ((int_str >= ASCII_a) && (int_str <= ASCII_z)) {    // LOWER case

                differ1 = ASCII_z - int_str;
                differ2 = int_str - ASCII_a;
                if (step > differ1) {
                    std::cout << (char)(ASCII_a-1 + ((step - differ1) % ENG_ALPH));
                }
                else if (-step > differ2) {
                    std::cout << (char)(ASCII_z+1 + ((step + differ2) % ENG_ALPH));
                }
                else std::cout << (char)(int_str + step);
            }
        }
    }
    std::cout << std::endl;
}

void eng_to_morse() {
    char alpha[ENG_ALPH] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    std::string morse[ENG_ALPH] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

    std::string str;
    std::cout << "Enter your string: ";
    getline(std::cin, str);

    int str_len = str.length();
    for (int i = 0; i < str_len; ++i) {
        if ((str[i] == ' ') && str[i+1] && (str[i+1] != ' ')) std::cout << "& ";
        else if (str[i] != ' ') {
            for (int j = 0; j < ENG_ALPH; ++j) {
                if (toupper(str[i]) == alpha[j]) std::cout << morse[j] << ' ';
            }
        }
    }
    std::cout << std::endl;
}

void morse_to_eng() {
    std::vector <std::string> morse = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    char alpha[ENG_ALPH] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    std::vector <std::string> morse2 = {""};

    std::string str;
    std::cout << "Enter your string: ";
    getline(std::cin, str);

    int str_len = str.length();
    for (int i = 0; i < str_len; ++i) {
        if ((str[i] == ' ') || !str[i+1]) {
            if (!str[i+1]) morse2[0] = morse2[0] + str[i];
            for (int j = 0; j < ENG_ALPH; ++j) {
                if (morse2[0] == morse[j]) std::cout << alpha[j];
            }
            morse2[0] = "";
        }
        else if (str[i] == '&') {
            std::cout << ' ';
            morse2[0] = "";
        }
        else morse2[0] = morse2[0] + str[i];
    }
}

/* russian to english */
void translit() {
    // setlocale(LC_ALL,"Russian");
    // std::system("chcp 1251");

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char eng[ENG_ALPH] = {'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'};
    int rus[ENG_ALPH] = {233,246,243,234,229,237,227,248,249,231,244,251,226,224,239,240,238,235,228,255,247,241,236,232,242,252};
//  char rus[ENG_ALPH] = {'й','ц','у','к','е','н','г','ш','щ','з','ф','ы','в','а','п','р','о','л','д','я','ч','с','м','и','т','ь'};

    std::string str;
    std::cout << "Enter your string: ";
    getline(std::cin, str);
    int str_len = str.length();
    for (int i = 0; i < str_len; ++i) {
        if ((str[i] == ' ') && (str[i-1] != ' ')) std::cout << ' ';
        else {
            for (int j = 0; j < ENG_ALPH; ++j) {
                if ((char)(tolower(str[i])) == (char)rus[j]) {
                    if ((char)(tolower(str[i])) == str[i]) std::cout << eng[j];
                    else std::cout << (char)(toupper(eng[j]));
                }
            }
        }
    }
}
