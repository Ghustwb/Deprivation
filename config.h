#ifndef CONFIG_H
#define CONFIG_H


#define CHECK(status) \
    do\
    {\
        auto ret = (status);\
        if (ret != 0)\
        {\
            std::cerr << "Cuda failure: " << ret << std::endl;\
            abort();\
        }\
    } while (0)


#define DEVICE 0  // GPU id
#define NMS_THRESH 0.45
#define BBOX_CONF_THRESH 0.3


// stuff we know about the network and the input/output blobs
static const int INPUT_W = 640;
static const int INPUT_H = 640;
static const int NUM_CLASSES = 2;
static const char* INPUT_BLOB_NAME = "input_0";
static const char* OUTPUT_BLOB_NAME = "output_0";
static Logger gLogger;


#endif // CONFIG_H
