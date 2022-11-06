#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox_2->setVisible(false);
    ui->pushButton_toFile->setVisible(false);
    msg=new QMessageBox(0);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_add_clicked()
{
    addingBase(true);
}
void MainWindow::on_pushButton_add_wSort_clicked()
{
    addingBase(false);
}
void MainWindow::on_pushButton_sort_clicked()
{
    list.sort();
    textRenew();
}
void MainWindow::on_pushButton_delition_clicked()
{
    list.destruction();
    textRenew();
}


void MainWindow::on_pushButton_del_clicked()
{
    if(!list.del(ui->spinBox_size->value())){
        msg->setWindowTitle("Ошибка при удалении элемента");
        msg->setText("Недопустимый номер!");
        msg->exec();
        ui->spinBox_size->setValue(1);
    }
    else{
        textRenew();
    }
}

void MainWindow::on_pushButton_toFile_clicked() const
{
    if(strcmp(ui->lineEdit_fileName->text().toLocal8Bit().data(),"")!=0){
        string fname=strcat(ui->lineEdit_fileName->text().toLocal8Bit().data(),".txt");
        list.toFile(fname);
        ui->lineEdit_fileName->setText("");
    }
    else {
        msg->setWindowTitle("Ошибка операции");
        msg->setText("введите имя файла!");
        msg->exec();
    }
}


void MainWindow::on_pushButton_fromFile_clicked()
{
    if(strcmp(ui->lineEdit_fileName->text().toLocal8Bit().data(),"")!=0){
        string fname=strcat(ui->lineEdit_fileName->text().toLocal8Bit().data(),".txt");
        bool a= list.fromFile(fname);
        if(!a){
            msg->setWindowTitle("Ошибка операции");
            msg->setText("Файл не существует!");
            msg->exec();
        }
        ui->lineEdit_fileName->setText("");
        if(list.getLen()>0){
            if(!ui->groupBox_2->isVisible()){
                ui->groupBox_2->setVisible(true);
                ui->pushButton_toFile->setVisible(true);
            }
            textRenew();
        }
    }
    else {
        msg->setWindowTitle("Ошибка операции");
        msg->setText("Введите имя файла!");
        msg->exec();
    }
}
void MainWindow::on_radioButton_package_clicked() const
{
    ui->label_2->setVisible(true);
    ui->spinBox_size->setVisible(true);
}

void MainWindow::on_radioButton_packOfCoins_clicked() const
{
    ui->label_2->setVisible(false);
    ui->spinBox_size->setVisible(false);
}
void MainWindow::addingBase(bool how){
    if(ui->radioButton_package->isChecked()||ui->radioButton_packOfCoins->isChecked()){
        Package* pack;
        if(ui->radioButton_package->isChecked()){
          pack=new Package();
        }
        else{
          pack=new PackOfCoins();
        }
        int8_t a=pack->setInfo(ui->line_name->text().toLocal8Bit().data(),ui->spinBox_size->value(), ui->spinBox_price->value());
        if(a==0&&pack->getPrice()>0&&pack->getSize()>0){
            if(how) list.add(pack);
            else list.insertWSort(pack);
            if(!ui->groupBox_2->isVisible()){
                ui->groupBox_2->setVisible(true);
                ui->pushButton_toFile->setVisible(true);
            }
           ui->spinBox_price->setValue(0);
           ui->spinBox_size->setValue(0);
           ui->line_name->setText("");
           if(how) addToTail();
           else textRenew();
        }
        else if(a==3){
            msg->setWindowTitle("Ошибка при добавлении элемента");
            msg->setText("Недопустимый размер!");
            msg->exec();
            ui->spinBox_size->setValue(1);
        }
        else if(a==1){
            msg->setWindowTitle("Ошибка при добавлении элемента");
            msg->setText("Недопустимое имя!");
            msg->exec();
            ui->line_name->setText("");
        }
        else if(a==2){
            msg->setWindowTitle("Ошибка при добавлении элемента");
            msg->setText("Недопустимая цена!");
            msg->exec();
            ui->spinBox_price->setValue(1);
        }
        delete pack;
    }
    else{
        msg->setWindowTitle("Ошибка при добавлении элемента");
        msg->setText("Не выбран тип багажа!");
        msg->exec();
    };
}
void MainWindow::textRenew()const{
    if(list.getLen()>0){
        ui->spinBox_del->setMaximum(list.getLen());
        QString a="Длина списка багажа - "+QString::number(list.getLen());
        ui->groupBox_2->setTitle(a);
    }
    else{
        ui->groupBox_2->setVisible(false);
        ui->pushButton_toFile->setVisible(false);
    };
    QString fulltext;
    List::Iterator start;
        if (list.getLen() == 1){
            fulltext="num " + QString::number(1) + "; name: " + list.head()->getName() + "; size: " + QString::number(list.head()->getSize())
                 + "; price: " + QString::number(list.head()->getPrice()) + ", value " + QString::number(list.head()->getValue())+"\n";
            ui->textBrowser_list->setText(fulltext);
        }
        else if(list.getLen()>1){
            start = list.head();
            if (!start.ifPrev()) {
                if (*start) {
                    List::Iterator temp = start;
                    for (int i = 1; i <= list.getLen(); i++) {
                        fulltext+="num " + QString::number(i) + "; name: " + temp.getName() + "; size: " + QString::number(temp.getSize())+ "; price: " + QString::number(temp.getPrice()) + ", value " + QString::number(temp.getValue());
                        fulltext+="; type - ";
                        if(temp.getType()) fulltext+="packOfCoins\n";
                        else fulltext= fulltext+"package\n";
                         ++temp;
                    }
                }
            }
            ui->textBrowser_list->setText(fulltext);
        }
        else{
            msg->setWindowTitle("");
            msg->setText("Список багажа пуст, добавьте в него что-либо!");
            msg->exec();
            ui->groupBox_2->setVisible(false);
            ui->pushButton_toFile->setVisible(false);
        }
}
void MainWindow::addToTail() const{
    QString fulltext=ui->textBrowser_list->toPlainText();
    fulltext+="num " + QString::number(list.getLen()) + "; name: " + list.tail()->getName() + "; size: " + QString::number(list.tail()->getSize())+ "; price: " + QString::number(list.tail()->getPrice()) + ", value " + QString::number(list.tail()->getValue());
    fulltext+="; type - ";
    if(list.tail()->getType()) fulltext+="packOfCoins\n";
    else fulltext= fulltext+"package\n";
    ui->textBrowser_list->setText(fulltext);
}
