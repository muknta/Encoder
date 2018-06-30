#ifndef MORSE_H
#define MORSE_H

#include <QMainWindow>

namespace Ui {
class Morse;
}

class Morse : public QMainWindow
{
    Q_OBJECT

public:
    explicit Morse(QWidget *parent = 0);
    ~Morse();

private slots:
    void on_eng_to_mor_clicked();

    void on_mor_to_eng_clicked();

    void on_algorithm_clicked();

    void on_to_menu_clicked();

    void on_about_morse_clicked();

    void on_example_clicked();

private:
    Ui::Morse *ui;
};

#endif // MORSE_H
