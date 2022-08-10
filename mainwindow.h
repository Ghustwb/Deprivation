#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    Detector *detector;

private slots:
    void on_pushButton_start1_clicked();

    void on_pushButton_start2_clicked();

    void on_pushButton_start3_clicked();

    void on_pushButton_start4_clicked();

    void on_pushButton_chooseModel_clicked();

    void on_pushButton_loadModel_clicked();

private:
    Ui::MainWindow *ui;
    bool model_loaded_done = false;
};
#endif // MAINWINDOW_H
