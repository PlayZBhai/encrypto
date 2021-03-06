#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_browse_btn_clicked();

    void on_encrypt_btn_clicked();

    void on_browse_btn_2_clicked();

    void on_decrypt_btn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
