#ifndef CAESAR_H
#define CAESAR_H

#include <QMainWindow>

namespace Ui {
class Caesar;
}

class Caesar : public QMainWindow
{
    Q_OBJECT

public:
    explicit Caesar(QWidget *parent = 0);
    ~Caesar();

private slots:
    void on_algorithm_clicked();

    void on_to_menu_clicked();

    void on_about_caesar_clicked();

    void on_example_clicked();

private:
    Ui::Caesar *ui;
};

#endif // CAESAR_H
