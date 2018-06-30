#ifndef TRANSLIT_H
#define TRANSLIT_H

#include <QMainWindow>

namespace Ui {
class Translit;
}

class Translit : public QMainWindow
{
    Q_OBJECT

public:
    explicit Translit(QWidget *parent = 0);
    ~Translit();

private slots:
    void on_eng_to_rus_clicked();

    void on_rus_to_eng_clicked();

    void on_algorithm_clicked();

    void on_to_menu_clicked();

    void on_about_translit_clicked();

    void on_example_clicked();

private:
    Ui::Translit *ui;
};

#endif // TRANSLIT_H
