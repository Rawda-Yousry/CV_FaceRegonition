#include "pca.h"


Mat DoPCA::getEigenVector(Mat cov, Mat subFaces, int imgRows){
    Mat allEigenValues, allEigenVectors, eigenVector;
    eigen(cov, allEigenValues, allEigenVectors);
    eigenVector = allEigenVectors * (subFaces.t());     //project each face image onto the eigenvectors to obtain the corresponding coefficients
        //each row represents the coefficients for a single face image.
        //These coefficients represent the contribution of each eigenvector to the corresponding face image.

    //Normalize eigenvectors
    for(int i = 0; i < eigenVector.rows; i++ )
    {
        Mat tempVec = eigenVector.row(i);
        normalize(tempVec, tempVec);
    }

    // This commented Part is for visualizuation, We can remove it and remove imgRows parameter
    /*
    //Display eigen face
    Mat eigenFaces, allEigenFaces;
    for (int i = 0; i < eigenVector.rows; i++) {
        eigenVector.row(i).reshape(0, imgRows).copyTo(eigenFaces);
        normalize(eigenFaces, eigenFaces, 0, 1, cv::NORM_MINMAX);
        if(i == 0){
            allEigenFaces = eigenFaces;
        }else{
            hconcat(allEigenFaces, eigenFaces, allEigenFaces);  //This function concatenate all the matrices horizontally (That's why the image (allEigenFaces) contain all the photos
        }
    }

    namedWindow("EigenFaces", WINDOW_NORMAL);
    imshow("EigenFaces", allEigenFaces);
    waitKey();
    */

    return eigenVector;

}

void DoPCA::prePCA(){
    vector<Mat> images;
    FaceDetection face;
    Mat ROI, temp;
    for(int i = 1; i <= 20; i++){
        string path = PATH + "Gehad+Rawda\\" + to_string(i) + ".jpg";
        Mat img = imread(path, IMREAD_GRAYSCALE);
        temp = face.detectFaces(path, ROI);
        string savePath = PATH + "Training\\" + to_string(i) + ".png";
        imwrite(savePath, ROI);
        images.push_back(ROI);
    }

    //get image size
    imgSize = images[0].rows * images[0].cols;
    imgRows = images[0].rows;

    // Create features matrix
    features.create(imgSize, col, CV_32FC1);
    for(int i = 0; i < col; i++){
        Mat temp = features.col(i);                //temp is a reference to the current column of features
        Mat tempImg;
        images[i].convertTo(tempImg, CV_32FC1);    //Convert the input image to a matrix tempImg

        tempImg.reshape(1, imgSize).copyTo(temp); //Reshapes the tempImg matrix to a single row of imgSize elements, Copies the reshaped tempImg matrix to the current column of features.
    }


    reduce(features, avgFace, 1, REDUCE_AVG);

    features.copyTo(subFaces);
    for(int i = 0; i < subFaces.cols; i++){
        subtract(subFaces.col(i), avgFace, subFaces.col(i));
    }
}

Mat DoPCA::applyPCA(){
    // Calculate covariance matrix
    Mat cov;
    cov = (1.0 / col) * (subFaces.t()) * subFaces ;

    Mat eigenVector = getEigenVector(cov, subFaces, imgRows);

    return eigenVector;
}



















