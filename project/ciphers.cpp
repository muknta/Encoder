#include <iostream>
#include <windows.h>    // cyrillic
#include <cstdlib>  // rand()
#include <time.h>   // time_t
#include <cmath>    // pow()
#include <string>   // memset()
#include <QString>
#include <QVector>
#include "ciphers.h"

#define ENG_ALPH 26
#define ASCII_A (int)'A'    // 65
#define ASCII_Z (int)'Z'    // 90
#define ASCII_a (int)'a'    // 97
#define ASCII_z (int)'z'    // 122


QString pass_generator(QString pass_size_str);
QString caesar(QString str, QString step);
QString eng_to_morse(QString str);
QString morse_to_eng(QString str);
QString transl_ruseng(QString str);
QString transl_engrus(QString str);
int ext_euc_alg(int det, const int len);
int** mat_declare(int rows, int cols);
int** filling(QString message, int rows, int cols);
void freeing(int** matrix, int rows);
int determinant(int** matrix, int size);
int** inverse_matrix(int** matrix, int size, const int alpha_length);
QString hill_encrypt(QString key, QString word);
QString hill_descrypt(QString key, QString word);


/* Password Generator */
QString pass_generator(QString pass_size_str) {
    int pass_size = pass_size_str.toInt();
    QString password;
    srand(time(NULL));

    int t;
    for (int i = 0; i < pass_size; ++i) {
        t = rand()%3;
        if (t == 0) {
            password[i] = QChar(char(ASCII_A + rand()%26));
        } else if (t == 1) {
            password[i] = QChar(char(ASCII_a + rand()%26));
        } else {
            password[i] = QChar(char(48 + rand()%10));  // ASCII 'zero'
        }
    }
    return password;
}


/* Caesar Cipher */
QString caesar(QString str, QString step) {
    int step_int = step.toInt();
    int ascii_str;
    int differ1, differ2;
    QString result;
    int counter = 0;
    int str_len = str.length();

    for (int i = 0; i < str_len; ++i) {
        if (str[i] == ' ') {
            result[counter++] = ' ';
        } else {
            ascii_str = str[i].toLatin1();
            if ((ascii_str >= ASCII_A) && (ascii_str <= ASCII_Z)) {     // UPPER case

                differ1 = ASCII_Z - ascii_str;
                differ2 = ascii_str - ASCII_A;
                if (step_int > differ1) {
                    result[counter++] = (char)(ASCII_A + ((step_int - (differ1 + 1)) % ENG_ALPH));
                } else if (-step_int > differ2) {
                    result[counter++] = (char)(ASCII_Z + ((step_int + (differ2 + 1)) % ENG_ALPH));
                } else {
                    result[counter++] = (char)(ascii_str + step_int);
                }
            }
            else if ((ascii_str >= ASCII_a) && (ascii_str <= ASCII_z)) {    // LOWER case

                differ1 = ASCII_z - ascii_str;
                differ2 = ascii_str - ASCII_a;
                if (step_int > differ1) {
                    result[counter++] = (char)(ASCII_a + ((step_int - (differ1 + 1)) % ENG_ALPH));
                } else if (-step_int > differ2) {
                    result[counter++] = (char)(ASCII_z + ((step_int + (differ2 + 1)) % ENG_ALPH));
                } else {
                    result[counter++] = (char)(ascii_str + step_int);
                }
            }
        }
    }
    return result;
}


/* English to Morse */
QString eng_to_morse(QString str) {
    char alpha[ENG_ALPH] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    QString morse[ENG_ALPH] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    QString result = "";

    int str_len = str.length();
    for (int i = 0; i < str_len; ++i) {
        if ((str[i] == ' ') && (str[i+1] != ' ') && (str[i+1] != '\0'))
            result += "& ";
        else if (str[i] != ' ') {
            for (int j = 0; j < ENG_ALPH; ++j) {
                if (str[i].toUpper() == alpha[j]) {
                    result += morse[j] + "  ";
                    break;
                }
            }
        }
    }
    return result;
}


/* Morse to English */
QString morse_to_eng(QString str) {    // added c++11 for syntax of QVector initilization
    QVector <QString> morse = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    char alpha[ENG_ALPH] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    QVector <QString> morse2 = {""};
    QString result;
    int counter = 0;

    int str_len = str.length();
    for (int i = 0; i < str_len; ++i) {
        if ((str[i] == ' ') || (str[i] == '&') || (str[i+1] == '\0')) {
            if ((str[i+1] == '\0') && (str[i] != ' ') && (str[i] != '&'))
                morse2[0] += str[i];
            for (int j = 0; j < ENG_ALPH; j++) {
                if (morse2[0] == morse[j])
                    result[counter++] = alpha[j];
            }
            morse2[0] = "";
            if (str[i] == '&')
                result[counter++] = ' ';
        }
        else morse2[0] += str[i];
    }
    return result;
}


/* russian to english */
QString transl_ruseng(QString str) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    QString eng[ENG_ALPH] = {"q","w","e","r","t","y","u","i","o","p","a","s","d","f","g","h","j","k","l","z","x","c","v","b","n","m"};
    int rus[ENG_ALPH] = {233,246,243,234,229,237,227,248,249,231,244,251,226,224,239,240,238,235,228,255,247,241,236,232,242,252};
//  char rus[ENG_ALPH] = {'й','ц','у','к','е','н','г','ш','щ','з','ф','ы','в','а','п','р','о','л','д','я','ч','с','м','и','т','ь'};
    QString result = "";

    str = str + ".";
    int str_len = str.length();
    for (int i = 0; i < str_len; i++) {

        if ((str[i] == ' ') && (str[i-1] != ' '))
            result += ' ';
        else {

            // cyrillic to ASCII
            QString str_low(str[i].toLower());
            QByteArray byte_str = str_low.toLocal8Bit();
            int ascii_str = static_cast<unsigned char>(byte_str[0]);

            for (int j = 0; j < ENG_ALPH; j++) {
                if (ascii_str == rus[j]) {
                    if (str[i].toLower() == str[i]) {
                        result += eng[j];
                    }
                    else result += eng[j].toUpper();
                    break;
                }
            }
        }
    }
    return result;
}


/* english to russian */
QString transl_engrus(QString str) {

    QString eng[ENG_ALPH] = {"q","w","e","r","t","y","u","i","o","p","a","s","d","f","g","h","j","k","l","z","x","c","v","b","n","m"};
    QString rus[ENG_ALPH] = {"й","ц","у","к","е","н","г","ш","щ","з","ф","ы","в","а","п","р","о","л","д","я","ч","с","м","и","т","ь"};
    QString result = "";

    int str_len = str.length();
    for (int i = 0; i < str_len; i++) {

        if ((str[i] == ' ') && (str[i-1] != ' '))
            result += ' ';
        else {
            for (int j = 0; j < ENG_ALPH; j++) {
                if (static_cast<QString>(str[i]) == eng[j]) {
                    result += rus[j];
                    break;
                }
                else if (static_cast<QString>(str[i]) == static_cast<QString>(eng[j]).toUpper()) {
                    result += static_cast<QString>(rus[j]).toUpper();
                    break;
                }
            }
        }
    }
    return result;
}


/* Extended Euclidean Algorithm */
int ext_euc_alg(int det, const int len) {
    int a = det, b = len;
    int ua = 1, va = 0, ub = 0, vb = 1;
    int q, r, buf;
    // a = ua * det + va * len;
    // b = ub * det + vb * len;

    while (b != 0) {
        q = a/b;
        r = a%b;
        a = b; b = r;
        buf = ub;
        ub = ua - q * ub;
        ua = buf; buf = vb;
        vb = va - q * vb;
        va = buf;
    }
//    int d = a, y = va;
    int x = 0;

    if ((a == -1) && (ua > 0))
        x = len - ua;
    else if ((ua < 0) && (det < 0))
        x = -ua;
    else if ((ua < 0) && (det > 0))
        x = len + ua;
    else if (ua > 0)
        x = ua;

    return x;
}


/* Matrix Declaring */
int** mat_declare(int rows, int cols) {
    int** matrix = new int*[rows];
    for(int i = 0; i < rows; ++i)
        matrix[i] = new int[cols];

    return matrix;
}


/* Matrix Filling with declaring */
int** filling(QString message, int rows, int cols) {
    QString alpha[ENG_ALPH+3] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"," ",",","?"};
    int mess_len = message.length();
    int iter = 0;

    int** matrix = mat_declare(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < ENG_ALPH+3; ++k) {
                if (iter >= mess_len)
                    matrix[i][j] = 26;  // position of ' ' in alpha
                else if (static_cast<QString>(message[iter]).toUpper() == alpha[k])
                    matrix[i][j] = k;
            }
            ++iter;
        }
    }
    return matrix;
}


/* Matrix Freeing */
void freeing(int** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete [] matrix[i];
    }
    delete [] matrix;
}


/* Determinant of Matrix */
int determinant(int** matrix, int size) {
    int det = 0;

    if (size == 1) det = matrix[0][0];
    else if (size == 2)
        det = matrix[0][0]* matrix[1][1] - matrix[1][0]* matrix[0][1];
    else if (size == 3)
        det = matrix[0][0]* matrix[1][1]* matrix[2][2] + matrix[0][1]* matrix[1][2]* matrix[2][0] +
              matrix[1][0]* matrix[2][1]* matrix[0][2] - matrix[0][2]* matrix[1][1]* matrix[2][0] -
              matrix[0][0]* matrix[1][2]* matrix[2][1] - matrix[0][1]* matrix[1][0]* matrix[2][2];
    return det;
}


/* Finding of Inverse Matrix */
int** inverse_matrix(int** matrix, int size, const int alpha_length) {

    int** inv_matrix = mat_declare(size, size);
    int det = determinant(matrix, size);
    if (det != 0) {
        int cof[size][size];
        int adj[size][size];
        int x = ext_euc_alg(det, alpha_length);

        if (size == 2) {
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    cof[i][j] = pow(-1, i+j)* (matrix[1-i][1-j] %(ENG_ALPH+3));
                }

            }
        }
        else if (size == 3) {
            int ia,ib,ja,jb;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (i+1 > 2) ib = 0;
                    else ib = i+1;
                    if (i-1 < 0) ia = 2;
                    else ia = i-1;
                    if (j+1 > 2) jb = 0;
                    else jb = j+1;
                    if (j-1 < 0) ja = 2;
                    else ja = j-1;
                    cof[i][j] = (matrix[ib][jb]* matrix[ia][ja] - matrix[ia][jb]* matrix[ib][ja]) %(ENG_ALPH+3);
                }
            }
        }
        // TRANSPOSE cofactor matrix (result - adjugate matrix)
        for (int i = 0; i < size; ++i) {
            for (int j = i+1; j < size; ++j) {
                adj[i][j] = cof[j][i];
                adj[j][i] = cof[i][j];
            }
            adj[i][i] = cof[i][i];
        }
        // RESULT MATRIX
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (adj[i][j] < 0)
                    inv_matrix[i][j] = (ENG_ALPH+3) + ((adj[i][j] * x) %(ENG_ALPH+3));
                else
                    inv_matrix[i][j] = (adj[i][j] *x) %(ENG_ALPH+3);
            }
        }
    }
    return inv_matrix;
}


/* Hill Cipher (Encryption) */
QString hill_encrypt(QString key, QString word) {
    QString alpha[ENG_ALPH+3] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"," ",",","?"};

    int size = sqrt(key.length());
    int blocks = (word.length())/size;
    if ((word.length())%size != 0)
        ++blocks;

    int** mat_key = filling(key, size, size);
    int** mat_word = filling(word, blocks, size);


    QString result = "";
    int det = determinant(mat_key, size);
    if (det != 0) {
        int mat_mult[blocks][size];
        memset(mat_mult, 0, sizeof(mat_mult));

        // MATRIX MULTIPLICATION + DECODING
        for (int i = 0; i < blocks; ++i) {
            for (int j = 0; j < size; ++j) {
                for (int k = 0; k < size; ++k) {
                    mat_mult[i][j] = (mat_mult[i][j] + (mat_word[i][k] * mat_key[k][j])) %(ENG_ALPH+3);
                }
                result += alpha[ mat_mult[i][j] ];
            }
        }
    } else {
        result = "error: det=0";
    }
    freeing(mat_key, size);
    freeing(mat_word, blocks);

    return result;
}


/* Hill Cipher (Descryption) */
QString hill_descrypt(QString key, QString word) {
    QString alpha[ENG_ALPH+3] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"," ",",","?"};

    int size = sqrt(key.length());
    int blocks = (word.length())/size;
    if ((word.length())%size != 0)
        ++blocks;

    int** mat_key = filling(key, size, size);
    int** mat_word = filling(word, blocks, size);
    int** inv_mat_key = inverse_matrix(mat_key, size, ENG_ALPH+3);

    QString result = "";
    int det = determinant(mat_key, size);
    if (det != 0) {
        int mat_mult[blocks][size];
        memset(mat_mult, 0, sizeof(mat_mult));

        // MATRIX MULTIPLICATION + DECODING
        for (int i = 0; i < blocks; ++i) {
            for (int j = 0; j < size; ++j) {
                for (int k = 0; k < size; ++k) {
                    mat_mult[i][j] = (mat_mult[i][j] + (mat_word[i][k] * inv_mat_key[k][j])) %(ENG_ALPH+3);
                }
                result += alpha[ mat_mult[i][j] ];
            }
        }
    } else {
        result = "error: det=0";
    }
    freeing(mat_key, size);
    freeing(mat_word, blocks);
    freeing(inv_mat_key, size);

    return result;
}
