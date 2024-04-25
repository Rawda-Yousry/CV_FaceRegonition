#ifndef TRAINDATA_H
#define TRAINDATA_H

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "pca.h"

using namespace std;
using namespace cv;


class TrainData
{
public:
    void WriteData();
    Mat readFaces(int facesNumber, vector<string>& loadedFaceID);
    Mat readMean();
    Mat readEigen(int facesNumber);
    string PATH = "F:\\SBME\\Third_Year\\Second Term\\Computer Vision\\Tasks\\Task5\\";

    Mat trainFaceseign;
};

#endif // TRAINDATA_H
