/* 
 * File:   anaglyth.h
 * Author: Kru
 *
 * Created on January 7, 2018, 9:29 PM
 */

#ifndef ANAGLYTH_H
#define ANAGLYTH_H

#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp"

#include "base.h"

using namespace cv;
using namespace std;

namespace ap {

#define TRUE 6 
#define MONO 7 
#define COLOR 8
#define HALFCOLORED 9
#define OPTIMIZED 10 

class Anaglyth : public base, public cv::Mat_<cv::Vec3b> {
    public:

        cv::Mat_<cv::Vec3b> leftImage;
        cv::Mat_<cv::Vec3b> rightImage;
        cv::Mat_<cv::Vec3b> resultImage;
        double mix[2][9]; //matrix to describe various color blending algorithms to mix the pixels 
       
        Anaglyth(void);
        Anaglyth(const cv::Mat_<cv::Vec3b>& src);
        
        void getLRimages(const cv::Mat_<cv::Vec3b>& src);
        
        void makeAnaglyth(void);
 
        void process(const cv::Mat_<cv::Vec3b>& src);
        
        const std::string getProcessName(void) const;
        
        const cv::Vec3b& operator()(int i, int j) const;

        cv::Vec3b& operator()(int i, int j);
    
        operator const cv::Mat_<cv::Vec3b>& (void) const;
    };

}
#endif /* ANAGLYTH_H */

