#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ciphers.h"
#include "generator.h"
#include "caesar.h"
#include "morse.h"
#include "translit.h"
#include "leshill.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Text Encryption");
    this->setWindowIcon(QIcon(":/res/img/key.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generator_clicked()
{
    hide();
    Generator *mainWindow = new Generator();
    mainWindow->show();
}

void MainWindow::on_caesar_clicked()
{
    hide();
    Caesar *mainWindow = new Caesar();
    mainWindow->show();
}

void MainWindow::on_leshill_clicked()
{
    hide();
    LesHill *mainWindow = new LesHill();
    mainWindow->show();
}

void MainWindow::on_morse_clicked()
{
    hide();
    Morse *mainWindow = new Morse();
    mainWindow->show();
}

void MainWindow::on_translit_clicked()
{
    hide();
    Translit *mainWindow = new Translit();
    mainWindow->show();
}

void MainWindow::on_about_program_clicked()
{
    QMessageBox::information(this, "About program", "The program is designed to work with text. "\
                             "It contains some algorithms for text encryption.\n\n\n"\
                             "© Nikita Sadchenko, 2018");
}

void MainWindow::on_exit_clicked()
{
    close();
}
