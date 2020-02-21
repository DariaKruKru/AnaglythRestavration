#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/photo.hpp"

#include <iostream>
#include <math.h>
#include <string.h>

#include "userInterface.h"
#include "base.h"
#include "anaglyth.h"
#include "filtering.h"

using namespace cv;
using namespace std;

const char* wndname = "Anaglyph Project";
const char* wndAnaglyth = "Anaglyph Result";
const char* interfaceWnd = "User Interface";
int commandNumber = 0;

void mouseEvent(int evt, int x, int y, int flags, void* param) {
    ;

    switch (evt) {
        case CV_EVENT_LBUTTONDOWN:
        {

            if (x >= 40 and x <= 160) {

                if (y >= 40 and y <= 70) {
                    commandNumber = 1;
                }
                else if (y >= 85 and y <= 115) {
                    commandNumber = 2;
                }
                else if (y >= 130 and y <= 160) {
                    commandNumber = 3;
                }
                else if (y >= 175 and y <= 205) {
                    commandNumber = 4;
                }
                else if (y >= 220 and y <= 250) {
                    commandNumber = 5;
                }
            }

            if (x >= 200 and x <= 370) {

                if (y >= 40 and y <= 70) {
                    commandNumber = 6;
                }
                else if (y >= 85 and y <= 115) {
                    commandNumber = 7;
                }
                else if (y >= 130 and y <= 160) {
                    commandNumber = 8;
                }
                else if (y >= 175 and y <= 205) {
                    commandNumber = 9;
                }
                else if (y >= 220 and y <= 250) {
                    commandNumber = 10;
                }

            }

            cout << "Left Button at position (" << x << "," << y << ") : " << endl;
        }
            break;

    }
}

int main(int argc, char** argv) {
    static const char* names[] = {"test2.jpg", 0};

    if (argc > 1) {
        names[0] = argv[1];
        names[1] = "0";
    }

    namedWindow(wndname, 1); //create new window

    //read all the images
    for (int i = 0; names[i] != 0; i++) {
        cv::Mat_<cv::Vec3b> image = imread(names[i], 1);
        cv::Mat_<cv::Vec3b> image_res;
        ap::Filtering Filtering;

        if (image.empty()) {
            cout << "Couldn't load " << names[i] << endl;
            continue;
        }

        //make image smaller
        resize(image, image_res, Size(), 0.35, 0.35);

        //create new window for interface
        Drawing ui;
        ui.DrawInterface(interfaceWnd);

        //set the callback function for any mouse event
        setMouseCallback(interfaceWnd, mouseEvent);

        int x; //variable tor exit button code
        bool flag = true;

        while (flag) {
            x = waitKey(20);

            cv::imshow(wndname, image_res);

            if (commandNumber > 0) {  //if any button was pushed

                //filtering of the image
                if (commandNumber < 6) {   

                    ap::Filtering filter;  //create filtering object
                    filter.setProcess(commandNumber);
                    cout << filter.getProcessName() << endl;  //print the name of filtering process
                    filter.process(image_res);
                    image_res = filter;
                }
                
                //create stereo image from filtered image
                else if (commandNumber > 5) {
                    ap::Anaglyth an;   //create anaglyth object
                    an.setProcess(commandNumber);
                    cout << an.getProcessName() << endl;   //print the name of anaglyth method
                    an.process(image_res);
                    image_res = an.resultImage;
                    cv::imwrite("anaglyph_sample.png", image_res); //save result           
                }

                commandNumber = 0;
            }

            if (x == 27) { //if Esc pushed
                flag = false;
            }

        }

        waitKey(0);
        break;
    }

    return 0;
}