#ifndef FILTERING_H
#define FILTERING_H

#include <string>
#include <iostream>
#include <stdio.h>

#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

#include "base.h"
   
using namespace cv;
using namespace std;


namespace ap {
#define MEDIANBLUR 1
#define BLUR 2
#define GAUSSIAN 3
#define DENOISING 4
#define SHARPENING 5
    

    class Filtering : public base, public cv::Mat_<cv::Vec3b> {
    public:

        Filtering(void);

        Filtering(const cv::Mat_<cv::Vec3b>& src, int _filteringType = 0);

        Filtering(const Filtering& src);

        const cv::Vec3b& operator()(int i, int j) const;

        cv::Vec3b& operator()(int i, int j);

        const std::string getProcessName(void) const;

        void process(const cv::Mat_<cv::Vec3b>& src);

        operator const cv::Mat_<cv::Vec3b>& (void) const;

        const Filtering& operator=(const Filtering& src);

    };
    
}
#endif	//FILTERING_H

