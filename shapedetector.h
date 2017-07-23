#ifndef SHAPEDETECTOR_H
#define SHAPEDETECTOR_H

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#include <QObject>
#include <QProcess>

class ShapeDetector : public QObject
{
    Q_OBJECT
public:
    explicit ShapeDetector(QObject *parent = 0);
    ~ShapeDetector();
    void setup (cv::String fname);

public slots:
    void rightMessage();
    void wrongMessage();

private:
    QProcess *proc;
};

#endif // SHAPEDETECTOR_H
