#include "generator.h"
#include "ui_generator.h"
#include "mainwindow.h"
#include "ciphers.h"

#include <iostream>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>  // choosing directory

Generator::Generator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Generator)
{
    ui->setupUi(this);
    this->setWindowTitle("Password generation");
    this->setWindowIcon(QIcon(":/res/img/key.png"));

    QRegExp dig( "^[0-9]*$" );
    QValidator *valid_int = new QRegExpValidator(dig, this);
    ui->length->setValidator( valid_int );
}

Generator::~Generator()
{
    delete ui;
}

void Generator::on_algorithm_clicked()
{
    QString pass_length = ui->length->text();

//    if (pass_length < "1000") {
        QString result = pass_generator(pass_length);
        ui->label_result->setText(result);
        ui->label_result->setTextInteractionFlags(Qt::TextSelectableByMouse);
//    } else {
//        QMessageBox::warning(this, "Some Error", "Length must be < 1000");
//    }
}

void Generator::on_to_menu_clicked()
{
    hide();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}

void Generator::on_saving_clicked()
{
    QString dir = QFileDialog::getOpenFileName(this,
                                               tr("Open Directory"),
                                               "D:/",
                                               "All files (*.*);;Text files (*.txt);;Doc files (*.doc);;Docx files (*.docx);;Fb2 files(*.fb2)");

    QFile file(dir);
    QByteArray buff = "";
    int num = 1;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while(!file.atEnd()) {
            buff = file.readLine();
//            if (!buff.isNull())
                num++;
        }
        file.close();
    }

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        file.write(buff + "\r\n");
        QString pass = ui->label_result->text();
        QString service = ui->service->text();
        if (pass != "<center>result</center>") {
            if (service != "") {
//                if (buff.isNull()){
                    file.write((QString::number(num) + ". " + service + " — " + pass + "\r\n").toUtf8());
//                } else {
//                    file.write(("\r\n" + QString::number(num) + ". " + service + " — " + pass + "\r\n").toUtf8());
//                }
            } else {
//                if (buff.isNull()) {
                    file.write((QString::number(num) + ". " + pass + "\r\n").toUtf8());  // QString to const char* (toUtf8)
//                } else {
//                    file.write(("\r\n" + QString::number(num) + ". " + pass + "\r\n").toUtf8());
//                }
            }
        }
        file.close();
    }
    else QMessageBox::warning(this, "Some Error", "File didn't opened...");
}

void Generator::on_about_generator_clicked()
{
    QMessageBox info(QMessageBox::NoIcon, "About password generator",
                     "Algorithm generates a password (with English letters and digits) due to pseudo-random numbers.\n"\
                     "For using, enter length of a password and confirm.",
                     QMessageBox::Ok, this);
    info.setTextInteractionFlags(Qt::TextSelectableByMouse);
    info.exec();
}
