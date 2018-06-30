#include "translit.h"
#include "ui_translit.h"
#include "ciphers.h"
#include "mainwindow.h"
#include <QMessageBox>

Translit::Translit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Translit)
{
    ui->setupUi(this);
    this->setWindowTitle("Translit");
    this->setWindowIcon(QIcon(":/res/img/key.png"));
}

Translit::~Translit()
{
    delete ui;
}

void Translit::on_eng_to_rus_clicked()
{
    ui->string->setEnabled(true);
    ui->string->clear();
    QRegExp let( "^[A-Za-z ]*$" );
    QValidator *valid_str = new QRegExpValidator(let, this);
    ui->string->setValidator( valid_str );
}

void Translit::on_rus_to_eng_clicked()
{
    ui->string->setEnabled(true);
    ui->string->clear();
    QRegExp let( "^[А-Яа-я ]*$" );
    QValidator *valid_str = new QRegExpValidator(let, this);
    ui->string->setValidator( valid_str );
}

void Translit::on_algorithm_clicked()
{
    QString str = ui->string->text();
    QString result = "result";

    if (ui->eng_to_rus->isChecked())
        result = transl_engrus(str);
    else if (ui->rus_to_eng->isChecked())
        result = transl_ruseng(str);

    ui->label_result->setText(result);
    ui->label_result->setTextInteractionFlags(Qt::TextSelectableByMouse);   // чтобы можно бб выделить текст
}

void Translit::on_to_menu_clicked()
{
    hide();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}

void Translit::on_about_translit_clicked()
{
    QMessageBox info(QMessageBox::NoIcon, "About translit",
                     "This algorithm change russian(english) letters to english(russian) letters with positions of it on keyboard.\n\n"\
                     "For using, enter your message and choose action (rus_to_eng or eng_to_rus).",
                     QMessageBox::Ok, this);
    info.setTextInteractionFlags(Qt::TextSelectableByMouse);
    info.exec();
}

void Translit::on_example_clicked()
{
    QMessageBox exam;
    exam.setIconPixmap(QPixmap(":/res/img/translit.png"));
    exam.setWindowTitle("Keyboard — image");
    exam.show();
    exam.exec();
}
