#include "caesar.h"
#include "ui_caesar.h"
#include "ciphers.h"
#include "mainwindow.h"
#include <QMessageBox>

Caesar::Caesar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Caesar)
{
    ui->setupUi(this);
    this->setWindowTitle("Caesar algorithm");
    this->setWindowIcon(QIcon(":/res/img/key.png"));

    QRegExp let( "^[A-Za-z ]*$" );
    QValidator *valid_str = new QRegExpValidator(let, this);
    ui->string->setValidator( valid_str );

    QRegExp dig( "^[0-9-]{1}[0-9]*$" );
    QValidator *valid_int = new QRegExpValidator(dig, this);
    ui->step->setValidator( valid_int );
}

Caesar::~Caesar()
{
    delete ui;
}

void Caesar::on_algorithm_clicked()
{
    QString str = ui->string->text();
    QString step = ui->step->text();

    QString result = caesar(str, step);
    ui->label_result->setText(result);
    ui->label_result->setTextInteractionFlags(Qt::TextSelectableByMouse);
}

void Caesar::on_to_menu_clicked()
{
    hide();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}

void Caesar::on_about_caesar_clicked()
{
    QMessageBox info(QMessageBox::NoIcon, "About Caesar cipher",
                     "Caesar cipher is one of the simplest and most widely known encryption techniques. "\
                     "It is a type of substitution cipher in which each letter in the plaintext is replaced by a letter some fixed number of positions down the alphabet. "\
                     "For example, with a left shift of 3, D would be replaced by A, E would become B, and so on.\n"\
                     "The method is named after Julius Caesar, who used it in his private correspondence.\n\n"\
                     "For using, enter your message, step and confirm.",
                     QMessageBox::Ok, this);
    info.setTextInteractionFlags(Qt::TextSelectableByMouse);
    info.exec();
}

void Caesar::on_example_clicked()
{
    QMessageBox exam;
    exam.setIconPixmap(QPixmap(":/res/img/caesar.png"));
    exam.setWindowTitle("Example of Caesar cipher");
    exam.show();
    exam.exec();
}
