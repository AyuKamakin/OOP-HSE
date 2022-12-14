#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMessageBox>
#include "list.h"
#include "package.h"
#include "packofcoins.h"
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
    void on_pushButton_add_clicked();

    void on_pushButton_add_wSort_clicked();

    void on_pushButton_sort_clicked();

    void on_pushButton_delition_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_toFile_clicked() const;

    void on_pushButton_fromFile_clicked();

    void on_radioButton_package_clicked() const;

    void on_radioButton_packOfCoins_clicked()  const;

private:
    Ui::MainWindow *ui;
    List list;
    QMessageBox *msg;
    void addingBase(bool how);
    void textRenew() const;
    void addToTail() const;
};
#endif // MAINWINDOW_H
