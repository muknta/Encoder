#ifndef CIPHERS_H
#define CIPHERS_H

#include <QString>

QString caesar(QString str, QString step);
QString pass_generator(QString pass_size_str);
QString eng_to_morse(QString str);
QString morse_to_eng(QString str);
QString transl_ruseng(QString str);
QString transl_engrus(QString str);
QString hill_encrypt(QString key, QString word);
QString hill_descrypt(QString key, QString word);

#endif
