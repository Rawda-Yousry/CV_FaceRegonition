#ifndef RECOGNIZE_H
#define RECOGNIZE_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;



class Recognize
{
public:
    void prepareFace(Mat test);
    void projectFace(Mat testVec, Mat avgVec, Mat eigenVec);
    void recognizeTestimg(Mat test, Mat faces, vector<string>& loadedFacesID);
    double findMaxDist(const std::string& folderPath);
    string getID(Mat& img, Mat avgVec, Mat eigenVec, Mat faces, vector<string>& loadedFacesID);
    void plot_Roc(const std::vector<int>& true_labels, const std::vector<double>& predicted_scores);

    Mat testVec;
    Mat testPrjFace;
    string closetFaceID = "None";
    double closetFaceDist = 3500;
};

#endif // RECOGNIZE_H
