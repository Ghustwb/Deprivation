#include "detect.h"
#include "opencv2/opencv.hpp"
#include "QDebug"

Detector::Detector(std::string Model)
{
    model_path = Model;
    yoloXDetector = new Detect::YOLOX(model_path);
    model_init_done = true;
}

Detector::~Detector()
{
    delete yoloXDetector;
}

void Detector::setCamIndex(int index)
{
    this->video_index = index;
}


void Detector::run()
{
    qDebug()<< "start run ...";
    if(this->video_index == -1)
    {
        qDebug()<< "Please Set Cam Index";
        return ;
    }
    cv::VideoCapture cap(video_index);
    cv::Mat image ;
    if (!cap.isOpened())
    {
        qDebug()<< "Open failed: " << video_index;
        return;
    }
    else
        qDebug()<< "Open Camera: " << video_index;
    while(1)
    {
        cap >> image;
        std::string window_name = "video" + std::to_string(video_index);
        //cv::imshow(window_name,image);
        std::vector<Detect::Object> objects = yoloXDetector->detect(image);
        //std::cout << "Detection Num: " << objects.size() << std::endl;
    }
}
