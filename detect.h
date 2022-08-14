#ifndef DETECT_H
#define DETECT_H

#include <QObject>
#include <QThread>
#include <QImage>
#include "yolox.h"
#include "mat_2_qimage.h"

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
    Mat_2_Qimage mat2Qimg;
    void draw_objects(const cv::Mat& bgr, const std::vector<Detect::Object>& objects);
    void generate_mosaic(cv::Mat& bgr, const std::vector<Detect::Object>& objects);
    void generate_gray_pixle(cv::Mat& bgr, const std::vector<Detect::Object>& objects);
    void generate_Gaussian(cv::Mat& bgr, const std::vector<Detect::Object>& objects);

protected:
    void run();

signals:
    void sig_video_src( QImage img );
    void sig_video_out( QImage img );
//    void sig_video_src2( QImage img );
//    void sig_video_out2( QImage img );
};

#endif // DETECT_H
