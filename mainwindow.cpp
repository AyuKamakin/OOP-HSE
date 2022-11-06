#include "mainwindow.h"
#include "ui_mainwindow.h"
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


void MainWindow::on_pushButton_add_clicked()
{
    if(ui->radioButton_package->isChecked()||ui->radioButton_packOfCoins->isChecked()){
        Package* pack;
        if(ui->radioButton_package->isChecked()){
          pack=new Package();
        }
        else{
          pack=new PackOfCoins();
        }
        int8_t a=pack->setInfo(ui->line_name->text().toLocal8Bit().data(),ui->spinBox_size->value() ,ui->spinBox_price->value());
        if(a==0){
            list.add(pack);
            ui->addingStatus->setText("Успешно!");
        }
        else if(a==3){
            ui->addingStatus->setText("Неверный размер, измените значение");
            ui->spinBox_size->setValue(0);
        }
        else if(a==1){
            ui->addingStatus->setText("Неверное имя, измените значение");
            ui->line_name->setText("");
        }
        else if(a==2){
            ui->addingStatus->setText("Неверная цена, измените значение");
            ui->spinBox_price->setValue(0);
        }
        delete pack;
    }
    else{
        ui->addingStatus->setText("Выберите тип багажа");
    };
}


void MainWindow::on_pushButton_add_wSort_clicked()
{

}


void MainWindow::on_pushButton_sort_clicked()
{

}


void MainWindow::on_pushButton_delition_clicked()
{

}


void MainWindow::on_pushButton_del_clicked()
{

}


void MainWindow::on_pushButton_toFile_clicked()
{

}


void MainWindow::on_pushButton_fromFile_clicked()
{

}



