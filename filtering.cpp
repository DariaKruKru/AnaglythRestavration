#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/photo.hpp"

#include <iostream>
#include <math.h>
#include <string.h>

#include "filtering.h"
#include "base.h"


namespace ap {
    

    Filtering::Filtering(void) : base(), cv::Mat_<cv::Vec3b>() {
    }    //empty constructor

    Filtering::Filtering(const cv::Mat_<cv::Vec3b>& src, int _filteringType) : base(_filteringType),
    cv::Mat_<cv::Vec3b>() {
        this->process(src);
    }   //constructor

    Filtering::Filtering(const Filtering& src) : base(src.commandType),
    cv::Mat_<cv::Vec3b>(src) {
    } //copy constructor

    const cv::Vec3b& Filtering::operator()(int i, int j) const {
        return this->cv::Mat_<cv::Vec3b>::operator()(i, j);
    }

    cv::Vec3b& Filtering::operator()(int i, int j) {
        return this->cv::Mat_<cv::Vec3b>::operator()(i, j);
    }

    const std::string Filtering::getProcessName(void) const {
        switch (this->base::commandType) {
            case BLUR: return std::string("Blur");
                break;
            case GAUSSIAN: return std::string("Gaussian");
                break;
            case MEDIANBLUR: return std::string("Median");
                break;
            case DENOISING: return std::string("Denoising");
                break;
            case SHARPENING: return std::string("Sharpening");
                break;
            default: return std::string("Unknown");
                break;
        }
    }

    void Filtering::process(const cv::Mat_<cv::Vec3b>& src) {
        
        switch (this->base::commandType) {
            case BLUR:
            {
                blur(src, *this, cv::Size(8, 8));
            }
                break;
            case GAUSSIAN:
            {
                GaussianBlur(src, *this, cv::Size(5, 5), 0, 0);
            }
                break;
            case MEDIANBLUR:
            {
                cv::medianBlur(src, *this, 5);
            }
                break;
            case DENOISING:
            {
                fastNlMeansDenoising(src, *this, 10);
            }
                break;
            case SHARPENING:
            {
                // sharpen image using "unsharp mask" algorithm
                Mat blurred;
                double sigma = 10, threshold = 5, amount = 1;
                GaussianBlur(src, blurred, Size(), sigma, sigma);
                Mat lowContrastMask = abs(src - blurred) < threshold;
                Mat sharpened = src * (1 + amount) + blurred * (-amount);
                this->cv::Mat_<cv::Vec3b>::operator=(sharpened);

            }
                break;
            default:
                std::cout << "Impossible to process this image" << std::endl;
        }
    }

    
    Filtering::operator const cv::Mat_<cv::Vec3b>& (void) const {
        return *(dynamic_cast<const cv::Mat_<cv::Vec3b>*> (this));
    }

    const Filtering& Filtering::operator=(const Filtering& src) {
        this->cv::Mat_<cv::Vec3b>::operator=(src);
        this->base::commandType = src.commandType;
        return *this;
    }

    const cv::Mat_<cv::Vec3b>& operator>>(const cv::Mat& imageToProcess, base& imageProcessing) {
        imageProcessing.process(imageToProcess);
        return imageProcessing;
    }

    void globalProcess(base& imageProcessing, const cv::Mat& imageToProcess) {
        imageProcessing.process(imageToProcess);

    }
};

