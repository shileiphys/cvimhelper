#ifndef CVIMAGEUTILS_H
#define CVIMAGEUTILS_H

#include <opencv2/opencv.hpp>

class CVImageUtils
{
public:
    CVImageUtils();

    // image encoding base64 string
    static std::string imencodeToBase64(cv::Mat mat, int quality=95);
    static cv::Mat imdecodeFromBase64(std::string base64_imstr, int flag=cv::IMREAD_COLOR);

};

#endif // CVIMAGEUTILS_H
