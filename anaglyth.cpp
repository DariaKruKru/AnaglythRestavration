/* 
 * File:   anaglyth.cpp
 * Author: Kru
 * 
 * Created on January 7, 2018, 9:29 PM
 */
#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "anaglyth.h"
#include "base.h"

using namespace cv;
using namespace std;

namespace ap {

    Anaglyth::Anaglyth(void) {
    }; //empty constructor

    Anaglyth::Anaglyth(const cv::Mat_<cv::Vec3b>& src) {
        this->process(src);
    }; //constructor


    void Anaglyth::getLRimages(const cv::Mat_<cv::Vec3b>& src) {
        //define cropping areas for images from left and right sides automatically
        Rect leftCropRectamgle = Rect(20, 30, 825, 718);
        Rect rightCropRectamgle = Rect(1060, 30, 825, 718);

        //cropping image
        leftImage = src(leftCropRectamgle);
        rightImage = src(rightCropRectamgle);
    };

    void Anaglyth::makeAnaglyth(void) {

        // assign a different mixing for matrix for different kind of algorithms
        if (commandType == 6) {
            double trueMix[2][9] = {
                {0.299, 0.587, 0.114, 0, 0, 0, 0, 0, 0},
                { 0, 0, 0, 0, 0, 0, 0.299, 0.587, 0.114}
            };
            memcpy(mix, trueMix, 18 * sizeof (double));

        } else if (commandType == 7) {
            double mono[2][9] = {
                { 0.299, 0.587, 0.114, 0, 0, 0, 0, 0, 0},
                { 0, 0, 0, 0.299, 0.587, 0.114, 0.299, 0.587, 0.114}
            };
            memcpy(mix, mono, 18 * sizeof (double));
        } else if (commandType == 8) {
            double color[2][9] = {
                { 1, 0, 0, 0, 0, 0, 0, 0, 0},
                { 0, 0, 0, 0, 1, 0, 0, 0, 1}
            };
            memcpy(mix, color, 18 * sizeof (double));
        } else if (commandType == 9) {
            double halfcolored [2][9] = {
                {0.299, 0.587, 0.114, 0, 0, 0, 0, 0, 0},
                { 0, 0, 0, 0, 1, 0, 0, 0, 1}
            };
            memcpy(mix, halfcolored, 18 * sizeof (double));

        } else if (commandType == 10) {
            double optimized[2][9] = {
                {0, 0.7, 0.3, 0, 0, 0, 0, 0, 0},
                { 0, 0, 0, 0, 1, 0, 0, 0, 1}
            };
            memcpy(mix, optimized, 18 * sizeof (double));
        } else {
            std::cout << "Impossible to process this image" << std::endl;
        }

        //separate color channels
        cv::Mat_<cv::Vec3b> bgrLeft[3];
        cv::Mat_<cv::Vec3b> bgrRight[3];
        std::vector<Mat> VectorImageR;
        std::vector<Mat> VectorImageL;
        cv::Mat_<cv::Vec3b> resultImageR, resultImageL;

        cv::split(this->leftImage, bgrLeft);
        cv::split(this->rightImage, bgrRight);

        bgrLeft[0] = bgrLeft[0] * mix[0][6] + bgrLeft[0] * mix[0][7] + bgrLeft[0] * mix[0][8];
        bgrLeft[1] = bgrLeft[1] * mix[0][3] + bgrLeft[1] * mix[0][4] + bgrLeft[1] * mix[0][5];
        bgrLeft[2] = bgrLeft[2] * mix[0][0] + bgrLeft[1] * mix[0][7] + bgrLeft[2] * mix[0][2];

        bgrRight[0] = bgrRight[0] * mix[1][6] + bgrRight[0] * mix[1][7] + bgrRight[0] * mix[1][8];
        bgrRight[1] = bgrRight[1] * mix[1][3] + bgrRight[1] * mix[1][4] + bgrRight[1] * mix[1][5];
        bgrRight[2] = bgrRight[2] * mix[1][0] + bgrRight[2] * mix[1][1] + bgrRight[2] * mix[1][2];

        VectorImageR.push_back(bgrRight[0]);
        VectorImageR.push_back(bgrRight[1]);
        VectorImageR.push_back(bgrRight[2]);

        VectorImageL.push_back(bgrLeft[0]);
        VectorImageL.push_back(bgrLeft[1]);
        VectorImageL.push_back(bgrLeft[2]);

        //merge color channels
        cv::merge(VectorImageR, resultImageR);
        cv::merge(VectorImageL, resultImageL);

        cv::addWeighted(resultImageR, 0.5, resultImageL, 0.5, 0, this->resultImage);

    };

    void Anaglyth::process(const cv::Mat_<cv::Vec3b>& src) {

        getLRimages(src);
        
        makeAnaglyth();

    };

    const std::string Anaglyth::getProcessName(void) const {
        switch (this->base::commandType) {
            case TRUE: return std::string("True Anaglyth");
                break;
            case MONO: return std::string("Mono Anaglyth");
                break;
            case COLOR: return std::string("Color Anaglyth");
                break;
            case HALFCOLORED: return std::string("Halfcolored Anaglyth");
                break;
            case OPTIMIZED: return std::string("Optimized Anaglyth");
                break;
            default: return std::string("Unknown");
                break;
        }
    }

    const cv::Vec3b& Anaglyth::operator()(int i, int j) const {
        return this->cv::Mat_<cv::Vec3b>::operator()(i, j);
    }

    cv::Vec3b& Anaglyth::operator()(int i, int j) {
        return this->cv::Mat_<cv::Vec3b>::operator()(i, j);
    }

    Anaglyth::operator const cv::Mat_<cv::Vec3b>& (void) const {
        return *(dynamic_cast<const cv::Mat_<cv::Vec3b>*> (this));
    }
};


