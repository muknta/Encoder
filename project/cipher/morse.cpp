#include "morse.h"
#include "ui_morse.h"
#include "ciphers.h"
#include "mainwindow.h"
#include <QMessageBox>

Morse::Morse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Morse)
{
    ui->setupUi(this);
    this->setWindowTitle("Morse code");
    this->setWindowIcon(QIcon(":/res/img/key.png"));
}

Morse::~Morse()
{
    delete ui;
}

void Morse::on_eng_to_mor_clicked()
{
    ui->string->setEnabled(true);
    ui->string->clear();
    QRegExp let( "^[A-Za-z ]*$" );
    QValidator *valid_str = new QRegExpValidator(let, this);
    ui->string->setValidator( valid_str );
}

void Morse::on_mor_to_eng_clicked()
{
    ui->string->setEnabled(true);
    ui->string->clear();
    QRegExp let( "^[-.& ]*$" );
    QValidator *valid_str = new QRegExpValidator(let, this);
    ui->string->setValidator( valid_str );
}

void Morse::on_algorithm_clicked()
{
    QString str = ui->string->text();
    QString result = "result";

    if (ui->eng_to_mor->isChecked())
        result = eng_to_morse(str);
    else if (ui->mor_to_eng->isChecked())
        result = morse_to_eng(str);

    ui->label_result->setText(result);
    ui->label_result->setTextInteractionFlags(Qt::TextSelectableByMouse);
}

void Morse::on_to_menu_clicked()
{
    hide();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}

void Morse::on_about_morse_clicked()
{
    QMessageBox info(QMessageBox::NoIcon, "About Morse code",
                     "Morse code is a method of transmitting text information as a series of on-off tones, lights, or clicks that can be directly understood by a skilled listener or observer without special equipment. "\
                     "It is named for Samuel F. B. Morse, an inventor of the telegraph.\n"\
                     "Each Morse code symbol represents either a text character (letter or numeral) or a prosign and is represented by a unique sequence of dots and dashes. "\
                     "The dot duration is the basic unit of time measurement in code transmission. The duration of a dash is three times the duration of a dot. Each dot or dash is followed by a short silence, equal to the dot duration. "\
                     "The letters of a word are separated by a space equal to three dots (one dash), and the words are separated by a space equal to seven dots.\n\n"\
                     "For using, enter message in English(Morse code) for encryption to Morse code(English).\n"\
                     "Morse code:  ' ' — letter separator; '&' — word separator.\n"\
                     "English: ' ' — word separator.\n\n"\
                     "Example:  [..  & -.  .  .  -..  & ....  .  .-..  .--.]  —  [I NEED HELP]",
                     QMessageBox::Ok, this);
    info.setTextInteractionFlags(Qt::TextSelectableByMouse);
    info.exec();
}

void Morse::on_example_clicked()
{
    QMessageBox exam;
    exam.setIconPixmap(QPixmap(":/res/img/morse.jpg"));
    exam.setWindowTitle("Morse code — image");
    exam.show();
    exam.exec();
}
