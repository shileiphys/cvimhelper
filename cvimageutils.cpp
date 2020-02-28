#include "cvimageutils.h"
#include "base64.h"

#include <iostream>
#include <string>

CVImageUtils::CVImageUtils()
{

}

std::string CVImageUtils::imencodeToBase64(cv::Mat mat, int quality)
{
  std::vector<uchar> buff;//buffer for coding
  std::vector<int> param(2);

  //QByteArray byte_img((char*)(mat.data), mat.total() * mat.elemSize());

  // encode to JPEG
  param[0] = cv::IMWRITE_JPEG_QUALITY;
  param[1] = quality; //default(95) 0-100
  cv::imencode(".jpg", mat, buff, param);

  // base64
  std::string base64Image = base64_encode(buff.data(), buff.size());

  return base64Image;
}

cv::Mat CVImageUtils::imdecodeFromBase64(std::string base64_imstr, int flag)
{
  // decode base64 image
  std::string base64_image = base64_decode(base64_imstr);
  std::vector<uchar> v( base64_image.begin(), base64_image.end() );
  cv::Mat mat = cv::imdecode(v, flag);

  return mat;
}
