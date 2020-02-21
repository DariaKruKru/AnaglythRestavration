#include <string>
#include <iostream>
#include <stdio.h>

#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "userInterface.h"


void Drawing::DrawRectangles(Point pt1, Point pt2) {

    cv::rectangle(image, pt1, pt2, currentColor, currentThickness, currentLineType);
}

void Drawing::SetCurrentColor(Scalar _color) {
    currentColor = _color;
}

Scalar Drawing::GetCurrentColor(void) {
    return currentColor;
}

void Drawing::DrawTexts(const string &text, Point org, int fontFace, double fontScale) {

    cv::putText(image, text, org, fontFace, fontScale, currentColor);
}

Drawing::Drawing(void) {
    currentColor = Scalar(100, 100, 100);
    currentThickness = -3;
    currentLineType = 8;
}

Drawing::Drawing(Scalar _color, int _thickness, int _lineType) {
    currentColor = _color;
    currentThickness = _thickness;
    currentLineType = _lineType;
}

void Drawing::DrawInterface(const char* ui) {

    Drawing obj;
    Mat Interface = Mat(400, 500, CV_8UC3, Scalar(235, 235, 235));
    obj.image = Interface;
    Scalar buttonColor = Scalar(210, 200, 200);
    Scalar textColor = Scalar(90, 90, 90);

    obj.SetCurrentColor(buttonColor);
    int buttonWidth = 30;
    int buttonSpace = 15;
    int step;
    step = buttonWidth + buttonSpace;

    //draw rectangles for buttons
    for (int i = 0; i < (step * 5); i = i + step) {
        obj.DrawRectangles(Point(40, 40 + i), Point(160, 70 + i));
    }
    
    for (int i = 0; i < (step * 5); i = i + step) {
        obj.DrawRectangles(Point(200, 40 + i), Point(370, 70 + i));
    }

    //place names for these buttons
    obj.SetCurrentColor(textColor);
    double fontSize = 0.45;
    int fontFace = 0;
    obj.DrawTexts("Median", Point(60, 60), fontFace, fontSize);
    obj.DrawTexts("Blur", Point(60, 60 + step), fontFace, fontSize);
    obj.DrawTexts("Gaussian", Point(60, 60 + step * 2), fontFace, fontSize);
    obj.DrawTexts("Denoising", Point(60, 60 + step * 3), fontFace, fontSize);
    obj.DrawTexts("Sharpening", Point(60, 60 + step * 4), fontFace, fontSize);
    
    obj.DrawTexts("True Anaglyth", Point(220, 60), fontFace, fontSize);
    obj.DrawTexts("Mono Anaglyth", Point(220, 60 + step), fontFace, fontSize);
    obj.DrawTexts("Color Anaglyth", Point(220, 60 + step * 2), fontFace, fontSize);
    obj.DrawTexts("Halfcolored Anaglyth", Point(220, 60 + step * 3), fontFace, fontSize);
    obj.DrawTexts("Optimised Anaglyth", Point(220, 60 + step * 4), fontFace, fontSize);

    namedWindow(ui, 1); //create new window for interface
    cv::imshow(ui, Interface); 

};
