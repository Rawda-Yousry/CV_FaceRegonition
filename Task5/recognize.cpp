#include "recognize.h"
#include <filesystem>
#include <numeric>
#include "traindata.h"
namespace fs = std::filesystem;
void Recognize::prepareFace(Mat test)
{
    test.convertTo(test, CV_32FC1);
    test.reshape(0, test.rows*test.cols).copyTo(testVec);
}

void Recognize::projectFace(Mat testVector, Mat avgVec, Mat eigenVec){
    Mat tmpData;

    subtract(testVector, avgVec, tmpData);
    testPrjFace = eigenVec * tmpData;
}

//Find the closet Euclidean Distance between input and database
void Recognize::recognizeTestimg(Mat test, Mat faces, vector<string>& loadedFacesID)
{
    Mat src2 = test;

    for (int i =0; i < loadedFacesID.size(); i++) {
        Mat src1 = faces.col(i);

//        cout << src1.size() << "\n" << src2.size();

        double dist = norm(src1, src2, NORM_L2);
        cout << "Dist " <<dist <<endl;
        if (dist < closetFaceDist) {
            closetFaceDist = dist;
            closetFaceID = loadedFacesID[i];
        }
    }
}

string Recognize::getID(Mat& img, Mat avgVec, Mat eigenVec, Mat faces, vector<string>& loadedFacesID){
    prepareFace(img);
    projectFace(testVec, avgVec, eigenVec);
    recognizeTestimg(testPrjFace, faces, loadedFacesID);
    return closetFaceID;
}
void Recognize::plot_Roc(const std::vector<int>& true_labels, const std::vector<double>& predicted_scores){
        std::vector<double> fpr;
        std::vector<double> tpr;
        std::vector<int> idx(predicted_scores.size());
        std::iota(idx.begin(), idx.end(), 0);
        std::sort(idx.begin(), idx.end(), [&](int i, int j) { return predicted_scores[i] > predicted_scores[j]; });

        int n_positives = std::count(true_labels.begin(), true_labels.end(), 1);
        int n_negatives = std::count(true_labels.begin(), true_labels.end(), 0);
        int tp = 0, fp = 0, tn = n_negatives, fn = n_positives;

        double prev_score = -1.0;
        for (int i = 0; i < idx.size(); i++) {
            int j = idx[i];
            if (predicted_scores[j] != prev_score) {
                fpr.push_back((double)fp / n_negatives);
                tpr.push_back((double)tp / n_positives);
                prev_score = predicted_scores[j];
            }
            if (true_labels[j] == 1) {
                tp++;
                fn--;
            }
            else {
                fp++;
                tn--;
            }
        }
        fpr.push_back((double)fp / n_negatives);
        tpr.push_back((double)tp / n_positives);



        // Plot ROC curve
        cv::Mat img = cv::Mat::zeros(480, 640, CV_8UC3);

        double x_min = *std::min_element(fpr.begin(), fpr.end());
        double x_max = *std::max_element(fpr.begin(), fpr.end());
        double y_min = *std::min_element(tpr.begin(), tpr.end());
        double y_max = *std::max_element(tpr.begin(), tpr.end());
        double x_range = x_max - x_min;
        double y_range = y_max - y_min;
        double x_scale = img.cols / x_range;
        double y_scale = img.rows / y_range;
        std::vector<cv::Point> pts(fpr.size());

        for (int i = 0; i < fpr.size(); i++) {
            pts[i] = cv::Point((fpr[i] - x_min) * x_scale, img.rows -( (tpr[i] - y_min)* y_scale));
        }

        // Draw the lines between each pair of adjacent points
        for (int i = 0; i < pts.size() - 1; i++) {
            cv::line(img, pts[i], pts[i + 1], cv::Scalar(0, 255, 0), 2);
        }

        // Show result
        imshow("ROC Curve", img);


}


double Recognize::findMaxDist(const std::string& folderPath) {

    string folderTrained = "F:\\SBME\\Third_Year\\Second Term\\Computer Vision\\Tasks\\Task5\\Training";

    String folderPatternTrained = folderTrained + "/*.png";

    vector<string> trainedFileNames;

    cv::glob(folderPatternTrained, trainedFileNames);


    vector<string> loadedFaceID;
    vector<int>Rawda;
    vector<int>Gehad;
    vector<int>Hager;
    vector<int>Rawan;
    vector<int>Sara;

    TrainData read;
    Mat faces = read.readFaces(50, loadedFaceID);
    for(int i = 0 ; i < loadedFaceID.size();i++  ){
        if(loadedFaceID[i] >= "1" && loadedFaceID[i] <= "10"){
            Gehad.push_back(1);
            Rawda.push_back(0);
            Hager.push_back(0);
            Rawan.push_back(0);
            Sara.push_back(0);

        }
        else if(loadedFaceID[i]>= "11" && loadedFaceID[i] <= "20"){
            Gehad.push_back(0);
            Rawda.push_back(1);
            Hager.push_back(0);
            Rawan.push_back(0);
            Sara.push_back(0);
        }
        else if(loadedFaceID[i] >= "21" && loadedFaceID[i] <= "30"){
            Gehad.push_back(0);
            Rawda.push_back(0);
            Hager.push_back(1);
            Rawan.push_back(0);
            Sara.push_back(0);
        }
        else if(loadedFaceID[i] >= "31" && loadedFaceID[i] <= "40"){
            Gehad.push_back(0);
            Rawda.push_back(0);
            Hager.push_back(0);
            Rawan.push_back(0);
            Sara.push_back(1);
        }
        else if(loadedFaceID[i] >= "41" && loadedFaceID[i]<= "50"){
            Gehad.push_back(0);
            Rawda.push_back(0);
            Hager.push_back(0);
            Rawan.push_back(1);
            Sara.push_back(0);
        }

    }



    double maxDistance = 0.0;

    vector<double> scores;

    for (int i = 0; i < loadedFaceID.size() ;i++) {
            std::vector<std::vector<double>> distances;
        for (int j = 0; j <faces.cols; j++) {
            std::vector<double> columnDistances;

            for (int j = 0; j < faces.cols; ++j) {

                    cv::Mat col1 = faces.col(i);
                    cv::Mat col2 = faces.col(j);
                    double distance = norm(col1, col2,NORM_L2);
                    columnDistances.push_back(distance);

            }

            distances.push_back(columnDistances);
        }
        for (const auto& columnDistances : distances) {


//          maxDistance = distance;
            int k = 4;

            // Use partial_sort_copy to find the indices of the k largest elements
            std::vector<int> indices(k);
            std::partial_sort_copy(columnDistances.begin(), columnDistances.end(), indices.begin(), indices.end());

            // Sort the indices to find the k smallest indices
            std::sort(indices.begin(), indices.end());
            double percentage = (Rawda[indices[0]] + Rawda[indices[1]] + Rawda[indices[2]] + Rawda[indices[3]])/4;
            scores.push_back(percentage);

        }

        plot_Roc(Rawda,scores);

     }


    return maxDistance;
}



