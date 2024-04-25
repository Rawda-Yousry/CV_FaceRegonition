#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readImage(QLabel *img_lbl){
    image = imread(file_name.toStdString(), IMREAD_COLOR);
    displayImage(img_lbl, image);
}

void MainWindow::displayImage(QLabel *img_lbl, Mat img){
    cvtColor(img, imageRGB, COLOR_BGR2RGB);
    img_lbl->setPixmap(QPixmap::fromImage(QImage(imageRGB.data, imageRGB.cols, imageRGB.rows, imageRGB.step,
                                                 QImage::Format_RGB888)).scaled(w,h,Qt::KeepAspectRatio));
    img_lbl->repaint();
}

void MainWindow::on_Browse_clicked()
{
    file_name = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Images (*.png *.xpm *.jpg)"));
    if (!file_name.isEmpty()){
        readImage(ui->input);
    }
}


void MainWindow::on_recognize_clicked()
{
    FaceDetection face;
    Mat ROI;
    Mat processed;
    Mat img = face.detectFaces(file_name.toStdString(), ROI);
    displayImage(ui->input, img);

    TrainData read;
    vector<string> loadedFaceID;
    Mat faces = read.readFaces(20, loadedFaceID);

//    cout<<faces<<endl;

    Mat avg = read.readMean();
    Mat eigens = read.readEigen(20);

    Recognize recognize;
    ROI.convertTo(ROI, CV_32FC1);
    string FaceID = recognize.getID(ROI, avg, eigens, faces, loadedFaceID);
    ui->faceName->setText(QString::fromStdString(FaceID));
}


void MainWindow::on_train_clicked()
{
    TrainData train;
    train.WriteData();
}

void MainWindow::on_rocCurve_clicked()
{

//    QString folderPath = "F:\\SBME\\Third_Year\\Second Term\\Computer Vision\\Tasks\\Task5\\TestData";
//    QDir directory(folderPath);
//    QStringList fileNames = directory.entryList(QStringList() << "*.jpg" << "*.png", QDir::Files | QDir::NoDotAndDotDot);
//    QStringList predictedFaceIDs;
//    QString folderPathGround = "F:\\SBME\\Third_Year\\Second Term\\Computer Vision\\Tasks\\Task5\\TestData"; // Replace with the actual folder path
//    QDir directoryGround(folderPathGround);
//    QStringList fileNamesGround = directoryGround.entryList(QStringList() << "*.jpg" << "*.png", QDir::Files | QDir::NoDotAndDotDot);
//    for (const QString& fileName : fileNames) {
//        QString filePath = directory.filePath(fileName);
//        qDebug() << "Predicted FaceID: " << filePath;
//        FaceDetection face;
//        Mat ROI;
//        Mat processed;
//        Mat img = face.detectFaces(filePath.toStdString(), ROI);

//        TrainData read;
//        vector<string> loadedFaceID;
//        Mat faces = read.readFaces(20, loadedFaceID);

//        Mat avg = read.readMean();
//        Mat eigens = read.readEigen(20);
//        Recognize recognize;
//        ROI.convertTo(ROI, CV_32FC1);
//        string FaceID = recognize.getID(ROI, avg, eigens, faces, loadedFaceID);

//        ROI.convertTo(ROI, CV_32FC1);

//        // Print the predicted FaceID for each image
//        predictedFaceIDs.append(QString::fromStdString(FaceID));

//    }
////    for (const QString& predictedFaceID : predictedFaceIDs) {
////        qDebug() << "Predicted FaceID: " << predictedFaceID;

////    }
//    QString outputFilePath = "F:\\SBME\\Third_Year\\Second Term\\Computer Vision\\Tasks\\Task5\\file.txt"; // Replace with the desired output file path
//    QFile outputFile(outputFilePath);
//    QString outputFilePathGround = "F:\\SBME\\Third_Year\\Second Term\\Computer Vision\\Tasks\\Task5\\ground.txt";
//    QFile outputFileGround(outputFilePathGround);
//    if (outputFileGround.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        QTextStream stream(&outputFileGround);
//        for (const QString& fileName : fileNamesGround) {
//            if (fileName.startsWith("g", Qt::CaseInsensitive)) {
//                stream << "gehad" << "\n";
//            } else if (fileName.startsWith("r", Qt::CaseInsensitive)) {
//                stream << "rawda" << "\n";
//            } else {
//                stream << "unknown" << "\n";
//            }
//        }

//        outputFile.close();
//    }
//    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        QTextStream stream(&outputFile);
//        for (const QString& predictedFaceID : predictedFaceIDs) {
//            if (predictedFaceID == "None") {
//                stream << "Unknown" << "\n";
//            } else if (predictedFaceID.toInt() <= 10) {
//                stream << "gehad" << "\n";
//            } else {
//                stream << "rawda" << "\n";
//            }
//        }
//        outputFile.close();
//    }
//    TrainData read;
//    vector<string> loadedFaceID;
//    Mat faces = read.readFaces(20, loadedFaceID);

    Recognize roc;
    string folderTrained = "F:\\SBME\\Third_Year\\Second Term\\Computer Vision\\Tasks\\Task5\\Training";
 //   string folderTest = "F:\\SBME\\Third_Year\\Second Term\\Computer Vision\\Tasks\\Task5\\TestData";
    double maxDistance = roc.findMaxDist(folderTrained);
//    String folderPatternTrained = folderTrained + "/*.png";
//    String folderPatternTest = folderTest + "/*.png";
    cout << "Maximum Distance: " << maxDistance << endl;
////    double probability = 1.0 - (euclideanDistance / maxDistance);
//    vector<string> testFileNames;
//    vector<string> trainedFileNames;
//    vector<Mat> testSamples;
//    vector<Mat> trainedData;
//    cv::glob(folderPatternTest, testFileNames);
//    for (const string& testFileName : testFileNames) {
//        Mat testSample = imread(testFileName);
//        cv::resize(testSample, testSample, Size(100, 100));
//        testSamples.push_back(testSample);
//    }
//    cv::glob(folderPatternTrained, trainedFileNames);
//    for (const string& trainedFileName : trainedFileNames) {
//        Mat trainedSample = imread(trainedFileName);
//        trainedData.push_back(trainedSample);
//    }
//    Mat distanceMatrix(testSamples.size(), trainedData.size(), CV_64F);
//    for (int i = 0; i < testSamples.size(); ++i) {
//        for (int j = 0; j < trainedData.size(); ++j) {
//            double distance = norm(testSamples[i], trainedData[j], NORM_L2);
//            distanceMatrix.at<double>(i, j) = distance;
//        }
//    }
//    for (int i = 0; i < distanceMatrix.rows; ++i) {
//        for (int j = 0; j < distanceMatrix.cols; ++j) {
//            if (distanceMatrix.at<double>(i, j) > maxDistance) {
//                distanceMatrix.at<double>(i, j) = (distanceMatrix.at<double>(i, j) - maxDistance) / (maxDistance);
//            } else {
//                distanceMatrix.at<double>(i, j) = 1- (distanceMatrix.at<double>(i, j) / maxDistance);
//            }
//            cout << distanceMatrix.at<double>(i, j) << " ";
//        }
//        cout << endl;  // Add a new line after each row
//    }

}
