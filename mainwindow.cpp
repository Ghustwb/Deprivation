#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"
#include "QDebug"
#include "QFile"
#include "QImage"
#include "QPainter"

//MainWindows 1920*1080
//divied to 4 paarts =>
//640*2 = 1280
//480*2 = 960
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_modelPath->setText("./model_trt_2070.engine");
    ui->comboBox->setCurrentIndex(1);

    //    bool OK1 = connect(detector1,SIGNAL(sig_video_src1(QImage)),this,SLOT(slot_src1_video_display(QImage)));
    //    bool OK2 = connect(detector1,SIGNAL(sig_video_out1(QImage)),this,SLOT(slot_output1_video_display(QImage)));
    //    bool OK3 = connect(detector2,SIGNAL(sig_video_src2(QImage)),this,SLOT(slot_src2_video_display(QImage)));
    //    bool OK4 = connect(detector2,SIGNAL(sig_video_out2(QImage)),this,SLOT(slot_output2_video_display(QImage)));
    //    qDebug() << OK1 <<OK2 <<OK3 <<OK4;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_src1_video_display( QImage img)
{
    QPainter painter( &img );
    QRect rect;
    uint i;
    painter.setPen( QPen( Qt::red, 4) );
    //painter.setBrush( Qt::green );
    QString font_type("Ubuntu");
    QFont font( font_type, 30 );
    painter.setFont( font );
    QPoint p( 30 , 30 );
    painter.drawText( p, "src video1" );
    //bool ok = painter.begin( &img );

    //painter.end();
    //ui->labelABViewer->setPixmap( QPixmap::fromImage( img ).scaled( ui->labelABViewer->size(), Qt::KeepAspectRatio ) );
    ui->label_vdieo_src1->setPixmap( QPixmap::fromImage( img ).scaled( ui->label_vdieo_src1->size(), Qt::KeepAspectRatio ));

}

void MainWindow::slot_src2_video_display( QImage img)
{
    QPainter painter( &img );
    QRect rect;
    uint i;
    painter.setPen( QPen( Qt::red, 4) );
    //painter.setBrush( Qt::green );
    QString font_type("Ubuntu");
    QFont font( font_type, 30 );
    painter.setFont( font );
    QPoint p( 30 , 30 );
    painter.drawText( p, "src video1" );
    //bool ok = painter.begin( &img );

    //painter.end();
    //ui->labelABViewer->setPixmap( QPixmap::fromImage( img ).scaled( ui->labelABViewer->size(), Qt::KeepAspectRatio ) );
    ui->label_vdieo_src2->setPixmap( QPixmap::fromImage( img ).scaled( ui->label_vdieo_src2->size(), Qt::KeepAspectRatio ));

}

void MainWindow::slot_output1_video_display( QImage img)
{
    QPainter painter( &img );
    QRect rect;
    uint i;
    painter.setPen( QPen( Qt::red, 4) );
    //painter.setBrush( Qt::green );
    QString font_type("Ubuntu");
    QFont font( font_type, 30 );
    painter.setFont( font );
    QPoint p( 30 , 30 );
    painter.drawText( p, "src Output1" );
    //bool ok = painter.begin( &img );

    //painter.end();
    //ui->labelABViewer->setPixmap( QPixmap::fromImage( img ).scaled( ui->labelABViewer->size(), Qt::KeepAspectRatio ) );
    ui->label_vdieo_output1->setPixmap( QPixmap::fromImage( img ).scaled( ui->label_vdieo_output1->size(), Qt::KeepAspectRatio ));
}

void MainWindow::slot_output2_video_display( QImage img)
{
    QPainter painter( &img );
    QRect rect;
    uint i;
    painter.setPen( QPen( Qt::red, 4) );
    //painter.setBrush( Qt::green );
    QString font_type("Ubuntu");
    QFont font( font_type, 30 );
    painter.setFont( font );
    QPoint p( 30 , 30 );
    painter.drawText( p, "src Output1" );
    //bool ok = painter.begin( &img );

    //painter.end();
    //ui->labelABViewer->setPixmap( QPixmap::fromImage( img ).scaled( ui->labelABViewer->size(), Qt::KeepAspectRatio ) );
    ui->label_vdieo_output2->setPixmap( QPixmap::fromImage( img ).scaled( ui->label_vdieo_output2->size(), Qt::KeepAspectRatio ));
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
        bool OK1 = connect(detector1,SIGNAL(sig_video_src(QImage)),this,SLOT(slot_src1_video_display(QImage)));
        bool OK2 = connect(detector1,SIGNAL(sig_video_out(QImage)),this,SLOT(slot_output1_video_display(QImage)));
        qDebug() << OK1 << OK2;
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
        bool OK3 = connect(detector2,SIGNAL(sig_video_src(QImage)),this,SLOT(slot_src2_video_display(QImage)));
        bool OK4 = connect(detector2,SIGNAL(sig_video_out(QImage)),this,SLOT(slot_output2_video_display(QImage)));
        qDebug() << OK3 << OK4;
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

