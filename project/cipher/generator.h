#ifndef GENERATOR_H
#define GENERATOR_H

#include <QMainWindow>

namespace Ui {
class Generator;
}

class Generator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Generator(QWidget *parent = 0);
    ~Generator();

private slots:
    void on_algorithm_clicked();

    void on_to_menu_clicked();

    void on_saving_clicked();

    void on_about_generator_clicked();

private:
    Ui::Generator *ui;
};

#endif // GENERATOR_H
