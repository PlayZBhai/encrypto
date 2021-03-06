#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QGraphicsDropShadowEffect>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("N/A");

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(70);
    shadow->setColor(QColor(0, 0, 0, 255));
    shadow->setOffset(0);
    ui->frame_2->setGraphicsEffect(shadow);
}

char get_operating_system()
{
    #ifdef Q_OS_WIN
        return 'w';
    #elif defined(Q_OS_LINUX)
        return 'l';
    #elif defined(Q_OS_MAC)
        return 'm';
    #else
        return 'o';
    #endif
}

void MainWindow::on_browse_btn_clicked()
{

    QString default_file_location = "N/A";


    char os = get_operating_system();
    if(os == 'w') {
        default_file_location = "C://";
    } else if (os == 'l') {
        default_file_location = "/home/";
    } else if (os == 'm') {
        default_file_location = "/Users/";
    } else {
        default_file_location = "/";
    }

    QString file_name = QFileDialog::getOpenFileName(this, "Choose a file", QDir::homePath());

    if(file_name.isEmpty()) {
        QMessageBox::information(this, "Error", "No file selected");
        return;
    }

    if(file_name.isNull()) {
        QMessageBox::information(this, "Error", "No file selected");
        return;
    }

    if(file_name == "") {
        QMessageBox::information(this, "Error", "No file selected");
        return;
    }

    ui->label->setText(file_name);
    QFile selectedFile("selectedFile.enloc");
    if(!selectedFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::information(this, "Error", "We had trouble reading and writing data. Please run the program as administrator");
        return;
    }

    QTextStream out(&selectedFile);
    out << file_name;
    selectedFile.flush();
    selectedFile.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    return;
}


void MainWindow::on_encrypt_btn_clicked()
{

    if(ui->label->text() == "N/A"){
        QMessageBox::information(this, "Error", "Please given a file to encrypt");
        return;
    }

    QString givenKeyName = ui->keyEdit->text();

    if(ui->keyEdit->text() == "") {
        QMessageBox::warning(this, "Error", "Please enter a key name!");
    }

    QFile selectedKey("selectedKey.enloc");
    if(!selectedKey.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::information(this, "Error", "We had trouble reading and writing data. Please run the program as administrator");
        return;
    }

    QTextStream out(&selectedKey);
    out << givenKeyName;
    selectedKey.flush();
    selectedKey.close();
    QProcess *process = new QProcess(this);
    process->startDetached("encrypt.exe");
    process->waitForFinished();
    QMessageBox::information(this, "Success", "Encryption successful");
}


void MainWindow::on_browse_btn_2_clicked()
{
    QString key_name = QFileDialog::getOpenFileName(this, "Choose a file", QDir::homePath());

    if(key_name.isEmpty()) {
        QMessageBox::information(this, "Error", "No file selected");
        return;
    }

    if(key_name.isNull()) {
        QMessageBox::information(this, "Error", "No file selected");
        return;
    }

    if(key_name == "") {
        QMessageBox::information(this, "Error", "No file selected");
        return;
    }

    ui->label_3->setText(key_name);
    QFile selectedKey("selectedGivenKey.enloc");
    if(!selectedKey.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::information(this, "Error", "We had trouble reading and writing data. Please run the program as administrator");
        return;
    }

    QTextStream out(&selectedKey);
    out << key_name;
    selectedKey.flush();
    selectedKey.close();
}


void MainWindow::on_decrypt_btn_clicked()
{

    if(ui->label->text() == "N/A"){
        QMessageBox::information(this, "Error", "Please given a file to decrypt");
        return;
    }

    QProcess *process = new QProcess(this);
    process->startDetached("decrypt.exe");
    process->waitForFinished();
    QMessageBox::information(this, "Success", "Decryption successful");
}

