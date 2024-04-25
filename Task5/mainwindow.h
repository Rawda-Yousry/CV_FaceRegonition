
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include <QString>
#include <opencv2/opencv.hpp>
#include "facedetection.h"
#include "traindata.h"
#include "recognize.h"

using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readImage(QLabel *img_lbl);
    void displayImage(QLabel *img_lbl, Mat img);
    Mat image;
    Mat imageRGB;
    int w = 500;
    int h = 400;
    QString file_name;

    QPixmap pixmap;
    QPainter *painter;


    int facesNumber;

private slots:
    void on_Browse_clicked();

    void on_recognize_clicked();

    void on_train_clicked();

    void on_rocCurve_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
