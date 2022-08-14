#ifndef DETECT_H
#define DETECT_H

#include <QObject>
#include <QThread>
#include "yolox.h"

class Detector: public QThread
{
    Q_OBJECT
public:
    Detector(std::string Model);
    ~Detector();
    void setCamOption(int index,int blur_option = 1);
public:
    bool model_init_done = false;
    std::string model_path ;
    int video_index = -1;
    int blur_option = 0;

private:
    Detect::YOLOX *yoloXDetector;
    cv::VideoCapture cap;
    void draw_objects(const cv::Mat& bgr, const std::vector<Detect::Object>& objects);
    void generate_mosaic(cv::Mat& bgr, const std::vector<Detect::Object>& objects);
    void generate_gray_pixle(cv::Mat& bgr, const std::vector<Detect::Object>& objects);
    void generate_Gaussian(cv::Mat& bgr, const std::vector<Detect::Object>& objects);

protected:
    void run();
};

#endif // DETECT_H
