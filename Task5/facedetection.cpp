#include "facedetection.h"


Mat FaceDetection::detectFaces(const std::string& imagePath, Mat& ROI)
{
    // Load the pre-trained face cascade
    CascadeClassifier faceCascade;
    faceCascade.load("F:\\SBME\\Third_Year\\Second Term\\Computer Vision\\Tasks\\Task5\\haarcascade_frontalface_default.xml");

    // Read the image
    Mat image = imread(imagePath);

    // Convert the image to grayscale
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // Perform face detection
    std::vector<Rect> faces;
    faceCascade.detectMultiScale(grayImage, faces);

    // Draw rectangles around the detected faces
    for (const auto& face : faces)
    {
        rectangle(image, face, Scalar(0, 255, 0), 2);
    }

    Mat toReturn;
    grayImage.copyTo(toReturn);

    ROI = toReturn(faces[0]);

    resize(ROI, ROI, Size(100,100));

    return image;
}

