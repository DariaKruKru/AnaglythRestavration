
/* 
 * File:   base.h
 * Author: Kru
 *
 * Created on January 10, 2018, 9:19 PM
 */

#ifndef BASE_H
#define BASE_H

#include <opencv2/core.hpp>

namespace ap {
    
class base {
    protected:
        int commandType; //type of wanted filtering or anaglyth method

    public:

        base(int _filteringType = 0);
        ~base(void);

        void setProcess(int _filteringType); 
        virtual const std::string getProcessName(void) const = 0;
        virtual void process(const cv::Mat_<cv::Vec3b>& src) = 0;
        virtual operator const cv::Mat_<cv::Vec3b>& (void) const = 0;

        virtual const cv::Vec3b& operator()(int i, int j) const = 0;
        virtual cv::Vec3b& operator()(int i, int j) = 0;

    };

}
#endif /* BASE_H */

