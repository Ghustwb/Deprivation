#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"
#include "QDebug"
#include "QFile"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_modelPath->setText("./model_trt_2070.engine");
    ui->comboBox->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_start1_clicked()
{
    qDebug() << "Click button 1";
    QFile file(ui->lineEdit_modelPath->text());
    if(!file.exists())
    {
        qDebug() << "Error,model is null";
        QMessageBox::information(this,
            tr("Error"),
            tr("AI Model Not Found, Please Select Correct Model Path"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
        return;
    }
    else
    {
        model_file = ui->lineEdit_modelPath->text().toStdString();
        detector1 = new Detector(model_file) ;
        int blur_option = ui->comboBox->currentIndex();
        detector1->setCamOption(0,blur_option);
        detector1->start();
    }
}

void MainWindow::on_pushButton_start2_clicked()
{
    qDebug() << "Click button 2";
    QFile file(ui->lineEdit_modelPath->text());
    if(!file.exists())
    {
        qDebug() << "Error,model is null";
        QMessageBox::information(this,
            tr("Error"),
            tr("AI Model Not Found, Please Select Correct Model Path"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
        return;
    }
    else
    {
        model_file = ui->lineEdit_modelPath->text().toStdString();
        detector2 = new Detector(model_file) ;
        detector2->setCamOption(1);
        detector2->start();
    }
}

void MainWindow::on_pushButton_start3_clicked()
{
    qDebug() << "Click button 3";
    QFile file(ui->lineEdit_modelPath->text());
    if(!file.exists())
    {
        qDebug() << "Error,model is null";
        QMessageBox::information(this,
            tr("Error"),
            tr("AI Model Not Found, Please Select Correct Model Path"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
        return;
    }
    else
    {
        model_file = ui->lineEdit_modelPath->text().toStdString();
        detector3 = new Detector(model_file) ;
        detector3->setCamOption(2);
        detector3->start();
    }
}

void MainWindow::on_pushButton_start4_clicked()
{
    qDebug() << "Click button 4";
    QFile file(ui->lineEdit_modelPath->text());
    if(!file.exists())
    {
        qDebug() << "Error,model is null";
        QMessageBox::information(this,
            tr("Error"),
            tr("AI Model Not Found, Please Select Correct Model Path"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
        return;
    }
    else
    {
        model_file = ui->lineEdit_modelPath->text().toStdString();
        detector4 = new Detector(model_file) ;
        detector4->setCamOption(3);
        detector4->start();
    }
}

void MainWindow::on_pushButton_chooseModel_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                "选择文件",
                "../",
                "All files(*.*)");
    if (fileName.isEmpty()) {
        //qDebug() << "this is the file name " << fileName;
        return;
    }
    ui->lineEdit_modelPath->setText(fileName);
}

