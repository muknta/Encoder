#include "leshill.h"
#include "ui_leshill.h"
#include "ciphers.h"
#include "mainwindow.h"
#include <QMessageBox>

LesHill::LesHill(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LesHill)
{
    ui->setupUi(this);
    this->setWindowTitle("Hill cipher");
    this->setWindowIcon(QIcon(":/res/img/key.png"));

    QRegExp let( "^[?A-Za-z, ]*$" );
    QValidator *valid_int = new QRegExpValidator(let, this);
    ui->key->setValidator( valid_int );
    ui->word->setValidator( valid_int );
}

LesHill::~LesHill()
{
    delete ui;
}

void LesHill::on_algorithm_clicked()
{
    QString key = ui->key->text();
    int key_len = key.length();
    QString word = ui->word->text();
    QString result = "result";

    if (((ui->encrypt->isChecked()) || (ui->descrypt->isChecked())) && (word != "") && (key != "")) {

        if ((key_len == 4) || (key_len == 9)) {

            if ((ui->encrypt->isChecked()) && (word != "") && (key != ""))
                result = hill_encrypt(key, word);
            else if ((ui->descrypt->isChecked()) && (word != "") && (key != ""))
                result = hill_descrypt(key, word);

            if (result == "error: det=0")
                QMessageBox::warning(this, "Some Error", "Determinant of key matrix = 0.");
            else
                ui->label_result->setText(result);
            ui->label_result->setTextInteractionFlags(Qt::TextSelectableByMouse);
        }
        else QMessageBox::warning(this, "Some Error", "Length of key must be equal to 4 or 9.");
    }
    else QMessageBox::warning(this, "Some Error", "All fields must be filled.");

}

void LesHill::on_to_menu_clicked()
{
    hide();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}

void LesHill::on_about_hill_clicked()
{
    QMessageBox info(QMessageBox::NoIcon, "About Hill cipher",
                     "Hill cipher is a polygraphic substitution cipher based on linear algebra. "\
                     "Invented by Lester S. Hill in 1929, it was the first polygraphic cipher in which it was practical (though barely) to operate on more than three symbols at once. "\
                     "The following discussion assumes an elementary knowledge of matrices.\n\n"\
                     "You can write key and message with letters of English alphabet + ' ' + ',' + '?'. This is done in order to get prime number (29) — length of new alphabet. "\
                     "Prime number is more difficult to decipher. Key and word is transformed to matrix of letter positions in alphabet.\n"\
                     "For encryption blocks(rows) of matrix_word multiplicates to key_matrix.\n"\
                     "For descryption blocks(rows) of matrix_word multiplicates to inverse_key_matrix.\n\n"\
                     "For using enter key and your message to encrypt/descrypt.",
                     QMessageBox::Ok, this);
    info.setTextInteractionFlags(Qt::TextSelectableByMouse);
    info.exec();
}

void LesHill::on_example_clicked()
{
    QMessageBox exam;
    exam.setIconPixmap(QPixmap(":/res/img/hill.jpg"));
    exam.setWindowTitle("Hill cipher — image");
    exam.show();
    exam.exec();
}
