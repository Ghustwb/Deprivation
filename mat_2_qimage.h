#ifndef MAT_2_QIMAGE_H
#define MAT_2_QIMAGE_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <QImage>

class Mat_2_Qimage
{
public:
    Mat_2_Qimage();
    void Mat_2_Qimage_f( const cv::Mat &input_image, QImage &out_image );

private:
    int image_w;
    int image_h;
    int image_c;
    unsigned char *image_data;
};

#endif // MAT_2_QIMAGE_H
