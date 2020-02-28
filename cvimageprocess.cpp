#include "cvimageprocess.h"

cvimageprocess::cvimageprocess()
{

}

cvimageprocess::~cvimageprocess()
{

}


/// OpenCV python implementation of MATLAB imreconstruct
/// ref: <<Digital Image Processing Using MATLAB>>
void cvimageprocess::imreconstruct(cv::Mat marker, cv::Mat mask, cv::Mat &dst, int conn=8)
{
  // connectivity default = 8
  int morph_elem = 0;
  if (conn == 4)
    morph_elem = cv::MORPH_CROSS;
  else
    morph_elem = cv::MORPH_RECT;

  cv::Mat kernel = cv::getStructuringElement(morph_elem, cv::Size(3,3));

  cv::Mat h = marker.clone();

  cv::Mat dilated;
  cv::dilate(h, dilated, kernel);

  cv::Mat h1;
  cv::bitwise_and(dilated, mask, h1);

  cv::Mat cmp_dst;
  cv::compare(h1, h, cmp_dst, cv::CMP_NE);

  // repeat until h not change any more
  // CMP_NE compare not equal: 1; equal: 0, -> total countNonZero: 0
  while (cv::countNonZero(cmp_dst)) {
//    h = h1.clone();
//    cv::dilate(h, dilated, kernel);
//    cv::bitwise_and(dilated, mask, h1);
//    cv::compare(h1, h, cmp_dst, cv::CMP_NE);

    h = h1;
    cv::dilate(h, dilated, kernel);
    cv::Mat tmp;
    cv::bitwise_and(dilated, mask, tmp);
    h1 = tmp;
    cv::compare(h1, h, cmp_dst, cv::CMP_NE);
  }

  dst = h1;
}

/// OpenCV python implementation of Clearing Border Objects
/// ref: <<Digital Image Processing Using MATLAB>>
void cvimageprocess::imclearBorder(cv::Mat src, cv::Mat &dst, int conn)
{
  // get border elements
  cv::Mat border_elm = cv::Mat::zeros(src.size(), CV_8UC1);
  int nrows = src.rows;
  int ncols = src.cols;

  src.row(0).copyTo(border_elm.row(0));
  src.row(nrows-1).copyTo(border_elm.row(nrows-1));
  src.col(0).copyTo(border_elm.col(0));
  src.col(ncols-1).copyTo(border_elm.col(ncols-1));

  // reconstruct marker=border, with mask=src
  cv::Mat border_obj;

//  int t0 = cv::getTickCount();
  imreconstruct(border_elm, src, border_obj, conn);
//  int t1 = cv::getTickCount();
//  cout << (t1-t0)/cv::getTickFrequency() << endl;

  // remove border object
//  dst = src.clone();
//  for (int i = 0; i < nrows; ++i) {
//    uchar* p_border = border_obj.ptr<uchar>(i);
//    uchar* p_dst = dst.ptr<uchar>(i);
//    for (int j = 0; j < ncols; ++j) {
//      if (p_border[j] != 0)
//        p_dst[j] = 0;
//    }
//  }

  // for binary
  src.copyTo(dst, (1-border_obj));

}

/// OpenCV python implementation of opening-by-reconstuction
/// ref: <<Digital Image Processing Using MATLAB>>
void cvimageprocess::bwremoveparticles(cv::Mat src, cv::Mat &dst, int ksize)
{
  cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(ksize,ksize));

  cv::Mat fe;
  cv::erode(src,fe,kernel);

  imreconstruct(fe, src, dst, 8);
}

