#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include <iostream>
#include <stdio.h>

#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

class Drawing {
public:
    cv::Mat_<cv::Vec3b > image;
    Scalar currentColor;
    int currentThickness;
    int currentLineType;
    
    Drawing (void);
    Drawing (Scalar _color, int _thickness, int _lineType);        
    void SetCurrentColor(Scalar _color);
    Scalar GetCurrentColor(void);
    void DrawTexts(const string &text, Point org, int fontFace, double fontScale);
    void DrawRectangles(Point pt1, Point pt2);
    void DrawInterface(const char* ui);
};

#endif	// USERINTERFACE_H

