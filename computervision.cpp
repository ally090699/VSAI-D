#include "computervision.h"
#include <QDebug>

ComputerVision::ComputerVision() {
    tessApi = new tesseract::TessBaseAPI();
    if (tessApi->Init(NULL, "eng")) { // "eng" for English
        std::cerr << "Could not initialize tesseract." << std::endl;
    }
}

ComputerVision::~ComputerVision() {
    if (tessApi) {
        tessApi->Clear();
        tessApi->End();
        delete tessApi;
        tessApi = nullptr;
    }
}

std::string ComputerVision::extractTextFromImage(const cv::Mat& image) {
    tessApi->SetImage(image.data, image.cols, image.rows, image.channels(), image.step);
    char* outText = tessApi->GetUTF8Text();
    std::string text(outText);
    delete[] outText;
    return text;
}

void ComputerVision::clearOCR(){
    tessApi->Clear();
}
