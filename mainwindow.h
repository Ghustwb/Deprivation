#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>

#include "detect.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Detector *detector1;
    Detector *detector2;
    Detector *detector3;
    Detector *detector4;

private slots:
    void on_pushButton_start1_clicked();

    void on_pushButton_start2_clicked();

    void on_pushButton_start3_clicked();

    void on_pushButton_start4_clicked();

    void on_pushButton_chooseModel_clicked();

    void slot_src1_video_display( QImage img);
    void slot_src2_video_display( QImage img);
    void slot_output1_video_display( QImage img);
    void slot_output2_video_display( QImage img);
private:
    Ui::MainWindow *ui;
    std::string model_file;
    bool model_loaded_done = false;
};
#endif // MAINWINDOW_H
