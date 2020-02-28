#ifndef CVIMAGEPROCESS_H
#define CVIMAGEPROCESS_H

#include <opencv2/opencv.hpp>

using namespace std;

class cvimageprocess
{
public:
  cvimageprocess(void);
  ~cvimageprocess(void);

  /// image process routine
  static void imreconstruct(cv::Mat marker, cv::Mat mask, cv::Mat &dst, int conn);
  static void imclearBorder(cv::Mat src, cv::Mat &dst, int conn=8);
  static void bwremoveparticles(cv::Mat src, cv::Mat &dst, int ksize);

  //def convertGray2ColorLUT(imgSrc, colLUT)

//  static int transferImageHistLUT( Mat &imgSrc,  TVectorU8 &usrLUT, OUT Mat &imgDst);
//  static void imconvertgrayscaledynamic( Mat &imgsrc, OUT Mat &imgdst);
//  static Mat imcropcircle( Mat &imgsrc,  PupilCorneaPos &pupil);
//  static Scalar imcirclemean( Mat &imgsrc,  PupilCorneaPos &circle);
//  static bool imremovecircle( const Mat &imgu8,   const PupilCorneaPos &circle, OUT Mat &dst);
//  static Mat bwfillhole( Mat &thresh,  Mat &mask);
//  static int imcorrectsys( string calibpath,  CameraSetting camsetting, OUT TVectorMat &imgarray,
};

#endif // CVIMAGEPROCESS_H
