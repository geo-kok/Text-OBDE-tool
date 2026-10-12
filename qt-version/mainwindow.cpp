#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ENCRYPTpushButton_clicked()
{
    int profile = ui->PROTOCOLcomboBox->currentIndex();

    QString qtext = ui->INPUTtextEdit->toPlainText(); //Qstring Text OBJECT!
    string text = qtext.toStdString(); //string text! (not Qstring obj)

    if(profile == 0){
        int key = ui->KEYspinBox->value();

        bool ignoreSpaces = ui->IGSPACEScheckBox->isChecked();
        bool ignoreUppercase = ui->IGUPcheckBox->isChecked();

        string encrypted = encryptCS(text, key, ignoreSpaces, ignoreUppercase);

        ui->OUTPUTtextEdit->setPlainText(
            QString::fromStdString(encrypted)
            );
    }
    else if (profile == 1){
        //bool ignoreSpaces = ui->IGSPACEScheckBox->isChecked(); //future implementation

        string encrypted = encryptBinary(text);

        ui->OUTPUTtextEdit->setPlainText(
            QString::fromStdString(encrypted)
            );
    }

}


void MainWindow::on_DECRYPTpushButton_clicked()
{
    int profile = ui->PROTOCOLcomboBox->currentIndex();

    QString qtext = ui->INPUTtextEdit->toPlainText(); //Qstring Text OBJECT!
    string text = qtext.toStdString(); //string text! (not Qstring obj)

    if(profile == 0){ //CEASARS CIPHER
        int key = ui->KEYspinBox->value();

        bool ignoreSpaces = ui->IGSPACEScheckBox->isChecked();
        bool ignoreUppercase = ui->IGUPcheckBox->isChecked();

        string decrypted = decryptCS(text, key, ignoreSpaces, ignoreUppercase);

        ui->OUTPUTtextEdit->setPlainText(
            QString::fromStdString(decrypted)
            );
    }
    else if(profile == 1){ // BINARY
        //bool ignoreSpaces = ui->IGSPACEScheckBox->isChecked(); //future implementation

        string decrypted = decryptBinary(text);

        ui->OUTPUTtextEdit->setPlainText(
            QString::fromStdString(decrypted)
            );
    }



}


void MainWindow::on_PROTOCOLcomboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        // Default profile Ceasar's cipher
        ui->KEYspinBox->show();
        ui->IGUPcheckBox->show();
        ui->KEYlabel->show();
        ui->IGSPACEScheckBox->show();
    }
    else if (index == 1)
    {
        // Profile 2 - Binary
        ui->KEYspinBox->hide();
        ui->IGUPcheckBox->hide();
        ui->KEYlabel->hide();
        ui->IGSPACEScheckBox->hide();
    }
}

