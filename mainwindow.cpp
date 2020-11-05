#include <QDebug>

#include <opencv2/opencv.hpp>

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

void MainWindow::on_pushButton_clicked()
{
    cv::VideoCapture vc(0);
    if (!vc.isOpened())
        return;

    auto frame_width = vc.get(cv::CAP_PROP_FRAME_WIDTH);
    auto frame_height = vc.get(cv::CAP_PROP_FRAME_HEIGHT);
    auto fps = vc.get(cv::CAP_PROP_FPS);

    cv::VideoWriter vw((qApp->applicationDirPath() + "/video.avi").toStdString()
                       , cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(frame_width, frame_height));
    while (true) {
        cv::Mat frame;
        vc >> frame;
        if (frame.empty())
            break;
        cv::imshow("Video", frame);
        vw.write(frame);
        if (cv::waitKey(1) >= 0)
            break;
    }
    vw.release();
    vc.release();
    cv::destroyAllWindows();
}
