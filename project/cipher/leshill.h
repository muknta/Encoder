#ifndef LESHILL_H
#define LESHILL_H

#include <QMainWindow>

namespace Ui {
class LesHill;
}

class LesHill : public QMainWindow
{
    Q_OBJECT

public:
    explicit LesHill(QWidget *parent = 0);
    ~LesHill();

private slots:
    void on_algorithm_clicked();

    void on_to_menu_clicked();

    void on_about_hill_clicked();

    void on_example_clicked();

private:
    Ui::LesHill *ui;
};

#endif // LESHILL_H
