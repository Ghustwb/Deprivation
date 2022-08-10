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
    void setCamIndex(int index);
public:
    bool model_init_done = false;
    std::string model_path ;
    int video_index = -1;

private:
    Detect::YOLOX *yoloXDetector;

protected:
    void run();
};

#endif // DETECT_H
