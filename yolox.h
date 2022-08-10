#ifndef YOLOX_H
#define YOLOX_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <numeric>
#include <chrono>
#include <vector>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include "NvInfer.h"
#include "cuda_runtime_api.h"
#include "logging.h"
#include "config.h"


using namespace nvinfer1;

namespace Detect{
struct Object
{
    cv::Rect_<float> rect;
    int label;
    float prob;
};

struct GridAndStride
{
    int grid0;
    int grid1;
    int stride;
};

const float color_list[2][3] =
{
    {0, 255, 100},
    {100, 0, 255},
    
};


class YOLOX
{
public:
    YOLOX(std::string engine_file_path);
    ~YOLOX();
    std::vector<Object> detect(cv::Mat& image);
    void draw_objects(const cv::Mat& bgr, const std::vector<Object>& objects);
    
private:
    IRuntime* runtime = nullptr;
    ICudaEngine* engine = nullptr;
    IExecutionContext* context = nullptr;
    float* prob = nullptr;
    long output_size = 1;


private:
    void doInference(IExecutionContext& context, float* input, float* output, const int output_size, cv::Size input_shape);
    void generate_grids_and_stride(std::vector<int>& strides, std::vector<GridAndStride>& grid_strides);
    inline float intersection_area(const Object& a, const Object& b);
    void qsort_descent_inplace(std::vector<Object>& faceobjects, int left, int right);
    void qsort_descent_inplace(std::vector<Object>& objects);
    void nms_sorted_bboxes(const std::vector<Object>& faceobjects, std::vector<int>& picked, float nms_threshold);
    void generate_yolox_proposals(std::vector<GridAndStride> grid_strides, float* feat_blob, float prob_threshold, std::vector<Object>& objects);
    float* blobFromImage(cv::Mat& img);
    void decode_outputs(float* prob, std::vector<Object>& objects, float scale, const int img_w, const int img_h);
   
};
}

#endif // YOLOX_H