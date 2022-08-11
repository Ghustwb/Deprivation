#include "yolox.h"
#include "BYTETracker.h"



int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <trt_model.engine>" \
            << "-image/-video"<< "image or video path"<< std::endl;
        return 1;
    }
    std::string input_image_path;
    std::string input_video_path;

    if(std::string(argv[2]) == "-image")
    {
        input_image_path = argv[3];
        input_video_path = "";
        cv::Mat img = cv::imread(input_image_path);
        if(img.empty())
        {
            std::cerr << "image is empty!" << std::endl;
            return -1;
        }
        Detect::YOLOX detector(argv[1]);
        std::vector<Detect::Object> objects = detector.detect(img);
    }
    else if(std::string(argv[2]) == "-video")
    {
        input_image_path = "";
        //judge camera or video
        input_video_path = argv[3];
        cv::VideoCapture cap;
        if(input_video_path == "0")
        {
            cap.open(0);
        }
        else
        {
            cap.open(input_video_path);
        }
        if(!cap.isOpened())
        {
            std::cerr << "Video Open Failed" << std::endl;
            return -1;
        }
        int img_w = cap.get(cv::CAP_PROP_FRAME_WIDTH);
        int img_h = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
        int fps = cap.get(cv::CAP_PROP_FPS);
        long nFrame = static_cast<long>(cap.get(cv::CAP_PROP_FRAME_COUNT));
        std::cout << "Total frames: " << nFrame << std::endl;

        cv::VideoWriter writer("demo.mp4", cv::VideoWriter::fourcc('m', 'p', '4', 'v'), fps, cv::Size(img_w, img_h));
        Detect::YOLOX detector(argv[1]);
        BYTETracker tracker(fps, 30);
        int num_frames = 0;
        int total_ms = 0;
        while(1)
        {
            cv::Mat frame;
            cap >> frame;
            if(frame.empty())
            {
                std::cerr << "frame is empty!" << std::endl;
                break;
            }
            std::vector<Detect::Object> objects = detector.detect(frame);
            std::cout << "Detection Num: " << objects.size() << std::endl;
            vector<Object> objects_to_track ;
            Object tmp;
            for(auto& obj : objects)
            {
                if(obj.prob > 0.3)
                {
                    tmp.label = obj.label;
                    tmp.prob = obj.prob;
                    tmp.rect = obj.rect;
                    objects_to_track.push_back(tmp);
                }
            }
            std::cout << "Track Update Num: " << objects_to_track.size() << std::endl;
            std::vector<STrack> output_stracks = tracker.update(objects_to_track);

            std::cout << "output_stracks Num: " << output_stracks.size() << std::endl;

            for (int i = 0; i < output_stracks.size(); i++)
            {
                std::vector<float> tlwh = output_stracks[i].tlwh;
                std::cout << "tlwh: " << tlwh[0] << " " << tlwh[1] << " " << tlwh[2] << " " << tlwh[3] << std::endl;
                //bool vertical = tlwh[2] / tlwh[3] > 1.6; // limite width / height ratio less than 1.6
                bool vertical = false;
                if (tlwh[2] * tlwh[3] > 20 && !vertical)
                {
                    cv::Scalar s = tracker.get_color(output_stracks[i].track_id);
                    cv::putText(frame, format("%d", output_stracks[i].track_id), cv::Point(tlwh[0], tlwh[1] - 5), 
                            0, 0.6, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
                    cv::rectangle(frame, cv::Rect(tlwh[0], tlwh[1], tlwh[2], tlwh[3]), s, 2);
                }
            }
            putText(frame, format("frame: %d fps: %d num: %d", num_frames, num_frames * 1000000 / total_ms, output_stracks.size()), 
                Point(0, 30), 0, 0.6, Scalar(0, 0, 255), 2, LINE_AA);
            cv::imshow("frame", frame);
            if(cv::waitKey(1) == 27)
            {
                break;
            }
        }
    }
    else
    {
        std::cerr << "Usage: " << argv[0] << " <trt_model.engine>" \
            << "-image/-video"<< "image or video path"<< std::endl;
        return 1;
    }

    return 0;
}
