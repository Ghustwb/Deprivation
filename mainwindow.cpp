#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_modelPath->setText("./model_trt_2070.engine");
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_start1_clicked()
{
    qDebug() << "Click button 1";
    if(ui->lineEdit_modelPath->text().isEmpty())
    {
        qDebug() << "Error,model is null";
        return;
    }
    else
    {
        model_file = ui->lineEdit_modelPath->text().toStdString();
        Detector *detector = new Detector(model_file) ;
        detector->setCamIndex(0);
        detector->start();
    }
}

void MainWindow::on_pushButton_start2_clicked()
{
    qDebug() << "Click button 2";
    if(ui->lineEdit_modelPath->text().isEmpty())
    {
        qDebug() << "Error,model is null";
        return;
    }
    else
    {
        model_file = ui->lineEdit_modelPath->text().toStdString();
        Detector *detector = new Detector(model_file) ;
        detector->setCamIndex(1);
        detector->start();
    }
}

void MainWindow::on_pushButton_start3_clicked()
{
    qDebug() << "Click button 3";
    if(ui->lineEdit_modelPath->text().isEmpty())
    {
        qDebug() << "Error,model is null";
        return;
    }
    else
    {
        model_file = ui->lineEdit_modelPath->text().toStdString();
        Detector *detector = new Detector(model_file) ;
        detector->setCamIndex(2);
        detector->start();
    }
}

void MainWindow::on_pushButton_start4_clicked()
{
    qDebug() << "Click button 4";
    if(ui->lineEdit_modelPath->text().isEmpty())
    {
        qDebug() << "Error,model is null";
        return;
    }
    else
    {
        model_file = ui->lineEdit_modelPath->text().toStdString();
        Detector *detector = new Detector(model_file) ;
        detector->setCamIndex(3);
        detector->start();
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

void MainWindow::on_pushButton_loadModel_clicked()
{
    //    if(ui->lineEdit_modelPath->text().isEmpty())
    //    {
    //        //        QMessageBox::warning(this, '标题', '我是文本', QMessageBox.Close);
    //        return;
    //    }
    //    std::string model_name = ui->lineEdit_modelPath->text().toStdString();
    //    detector = new Detector(model_name);

    //    ui->pushButton_loadModel->setVisible(false);
    //    model_loaded_done = detector->model_init_done;
}
