#include "mat_2_qimage.h"

Mat_2_Qimage::Mat_2_Qimage()
{
    image_w = 0;
    image_h = 0;
    image_c = 0;
    image_data = nullptr;
}

void Mat_2_Qimage::Mat_2_Qimage_f( const cv::Mat &input_image, QImage &out_image )
{
    const unsigned char *line_ptr = nullptr;
    if( input_image.cols != image_w || image_h != input_image.rows || image_c != input_image.channels() )
    {
        if( nullptr != image_data )
        {
            delete image_data;
            image_data = nullptr;
        }
        image_w = input_image.cols;
        image_h = input_image.rows;
        image_c = input_image.channels();
        image_data = new unsigned char[ image_w * image_h * image_c ];
    }
    int i;
    int j;
    int curline_data_size = 0;
    for( i = 0; i < image_h; ++i )
    {
        line_ptr = input_image.ptr< unsigned char >( i );
        curline_data_size = image_w * image_c * i;
        for( j = 0; j < image_w; ++j )
        {
            if( 3 == image_c )
            {
               image_data[ curline_data_size + image_c * j ] = line_ptr[ image_c * j + 2 ];
               image_data[ curline_data_size + image_c * j + 1 ] = line_ptr[ image_c * j + 1 ];
               image_data[ curline_data_size + image_c * j + 2 ] = line_ptr[ image_c * j ];
            }
            else if( 1 == image_c )
            {
                image_data[ curline_data_size + image_c * j ] = line_ptr[ image_c * j ];
                image_data[ curline_data_size + image_c * j + 1 ] = line_ptr[ image_c * j ];
                image_data[ curline_data_size + image_c * j + 2 ] = line_ptr[ image_c * j ];
            }
        }
    }
    out_image = QImage( image_data, image_w, image_h, QImage::Format_RGB888 ).copy();
}
