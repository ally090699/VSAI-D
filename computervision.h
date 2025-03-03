#ifndef COMPUTERVISION_H
#define COMPUTERVISION_H

#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <string>

class ComputerVision {
public:
    ComputerVision();
    ~ComputerVision();

    std::string extractTextFromImage(const cv::Mat& image);
    void clearOCR();

private:
    tesseract::TessBaseAPI* tessApi;
};

#endif // COMPUTERVISION_H
