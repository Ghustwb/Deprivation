#include "detect.h"
#include "opencv2/opencv.hpp"
#include "QDebug"
#include "QImage"
#include "QTime"

Detector::Detector(std::string Model)
{
    model_path = Model;

    model_init_done = true;
}

Detector::~Detector()
{
    delete yoloXDetector;
}


void Detector::setCamOption(int index,int blur_option)
{
    this->video_index = index;
    this->blur_option = blur_option;
}

//Draw Rect
void Detector::draw_objects(const cv::Mat& bgr, const std::vector<Detect::Object>& objects)
{
    static const char* class_names[] = {
        "Face", "Plate"
    };

    cv::Mat image = bgr.clone();

    for (size_t i = 0; i < objects.size(); i++)
    {
        const Detect::Object& obj = objects[i];

        // fprintf(stderr, "%d = %.5f at %.2f %.2f %.2f x %.2f\n", obj.label, obj.prob,
        //         obj.rect.x, obj.rect.y, obj.rect.width, obj.rect.height);

        cv::Scalar color = cv::Scalar(Detect::color_list[obj.label][0], Detect::color_list[obj.label][1], Detect::color_list[obj.label][2]);
        float c_mean = cv::mean(color)[0];
        cv::Scalar txt_color;
        if (c_mean > 0.5){
            txt_color = cv::Scalar(0, 0, 0);
        }else{
            txt_color = cv::Scalar(255, 255, 255);
        }

        cv::rectangle(image, obj.rect, color * 255, 2);

        char text[256];
        sprintf(text, "%s %.1f%%", class_names[obj.label], obj.prob * 100);

        int baseLine = 0;
        cv::Size label_size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.4, 1, &baseLine);

        cv::Scalar txt_bk_color = color * 0.7 * 255;

        int x = obj.rect.x;
        int y = obj.rect.y + 1;
        //int y = obj.rect.y - label_size.height - baseLine;
        if (y > image.rows)
            y = image.rows;
        //if (x + label_size.width > image.cols)
        //x = image.cols - label_size.width;

        cv::rectangle(image, cv::Rect(cv::Point(x, y), cv::Size(label_size.width, label_size.height + baseLine)),
                      txt_bk_color, -1);

        cv::putText(image, text, cv::Point(x, y + label_size.height),
                    cv::FONT_HERSHEY_SIMPLEX, 0.4, txt_color, 1);
    }
//    std::string window_name = "Camera" + std::to_string(video_index);
//    cv::namedWindow(window_name, 0);
//    cv::imshow(window_name, image);
    //cv::waitKey(1);
    QImage qimg;
    mat2Qimg.Mat_2_Qimage_f(image,qimg);
    emit sig_video_src(qimg);
}

//Put Mosic on image
void Detector::generate_mosaic(cv::Mat& bgr, const std::vector<Detect::Object>& objects)
{
    int step = 30;
    for (int t = 0; t < objects.size(); t++)
    {
        int x = objects.at(t).rect.x;
        int y = objects.at(t).rect.y;
        int width = objects.at(t).rect.width;
        int height = objects.at(t).rect.height;
        for (int i = y; i < (y + height); i += step)
        {
            for (int j = x; j < (x + width); j += step)
            {
                for (int k = i; k < (step + i); k++)
                {
                    for (int m = j; m < (step + j); m++)
                    {
                        for (int c = 0; c < 3; c++)
                        {
                            bgr.at<cv::Vec3b>(k, m)[c] = bgr.at<cv::Vec3b>(i, j)[c];
                        }
                    }
                }
            }
        }
    }
//    std::string window_name = "Mosaic Camera" + std::to_string(video_index);
//    cv::namedWindow(window_name, 0);
//    cv::imshow(window_name,bgr);
    QImage qimg;
    mat2Qimg.Mat_2_Qimage_f(bgr,qimg);
    emit sig_video_out(qimg);
}


//Put gray pixle on image
void Detector::generate_gray_pixle(cv::Mat& bgr, const std::vector<Detect::Object>& objects)
{
    int pix = 105;
    for (int t = 0; t < objects.size(); t++)
    {
        int x = objects.at(t).rect.x;
        int y = objects.at(t).rect.y;
        int width = objects.at(t).rect.width;
        int height = objects.at(t).rect.height;
        for (int i = y; i < (y + height); i += 1)
        {
            for (int k = x; k < (x + width); k++)
            {
                for (int m = 0; m < 3; m++)
                {
                    bgr.at<cv::Vec3b>(i, k)[m] = pix;
                }
            }
        }
    }
//    std::string window_name = "Gray Pixel Camera" + std::to_string(video_index);
//    cv::namedWindow(window_name, 0);
//    cv::imshow(window_name,bgr);
    QImage qimg;
    mat2Qimg.Mat_2_Qimage_f(bgr,qimg);
    emit sig_video_out(qimg);
}

//Put Gaussian Blur
void Detector::generate_Gaussian(cv::Mat &bgr, const std::vector<Detect::Object> &objects)
{
    cv::Mat image = bgr.clone();
    for (int t = 0; t < objects.size(); t++)
    {
        cv::Rect roi = objects.at(t).rect;
        cv::GaussianBlur(image(roi), bgr(roi), cv::Size(35, 35), 15, 0, 4);
    }
//    std::string window_name = "Gaussian Blur Camera" + std::to_string(video_index);
//    cv::namedWindow(window_name, 0);
//    cv::imshow(window_name,bgr);
    QImage qimg;
    mat2Qimg.Mat_2_Qimage_f(bgr,qimg);
    emit sig_video_out(qimg);
}

void Detector::run()
{
    qDebug()<< "start run ...";
    if(this->video_index == -1)
    {
        qDebug()<< "Please Set Cam Index";
        return ;
    }
    yoloXDetector = new Detect::YOLOX(model_path);
    cap.open(video_index);
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
        if(image.empty())
        {
            qDebug() << "img empty";
            break;
        }
        QTime timer;
        timer.start();
        std::vector<Detect::Object> objects = yoloXDetector->detect(image);
        qDebug()<< "Detect time: " << timer.elapsed();
        timer.start();
        draw_objects(image,objects);
        qDebug()<< "Draw Obj time: " << timer.elapsed();
        if(this->blur_option == 0)
        {
            this->generate_mosaic(image,objects);
        }
        else if(this->blur_option == 1)
        {
            this->generate_Gaussian(image,objects);
        }
        else if(this->blur_option == 2)
        {
            this->generate_gray_pixle(image,objects);
        }
    }
}
