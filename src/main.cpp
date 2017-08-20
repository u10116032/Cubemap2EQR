#include <iostream>

#include <memory>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>

#include "Cubemap.hpp"

const int PANORAMA_Height = 200;

int main(int argc, char const *argv[])
{
	cv::Mat extrinsicTop = cv::Mat::zeros(3,3,CV_32F);
	cv::Mat extrinsicBottom = cv::Mat::zeros(3,3,CV_32F);
	cv::Mat extrinsicFront = cv::Mat::zeros(3,3,CV_32F);
	cv::Mat extrinsicBack = cv::Mat::zeros(3,3,CV_32F);
	cv::Mat extrinsicRight = cv::Mat::zeros(3,3,CV_32F);
	cv::Mat extrinsicLeft = cv::Mat::zeros(3,3,CV_32F);

	// rotate x : clockwise +90
	extrinsicTop.at<float>(0,0) = 1.0f; 
	extrinsicTop.at<float>(0,1) = 0.0f; 
	extrinsicTop.at<float>(0,2) = 0.0f;

	extrinsicTop.at<float>(1,0) = 0.0f; 
	extrinsicTop.at<float>(1,1) = std::cos(M_PI*(-0.5f));  
	extrinsicTop.at<float>(1,2) = -std::sin(M_PI*(-0.5f));

	extrinsicTop.at<float>(2,0) = 0.0f;
	extrinsicTop.at<float>(2,1) = std::sin(M_PI*(-0.5f));  
	extrinsicTop.at<float>(2,2) = std::cos(M_PI*(-0.5f));

	// rotate x : clockwise -90
	extrinsicBottom.at<float>(0,0) = 1.0f; 
	extrinsicBottom.at<float>(0,1) = 0.0f; 
	extrinsicBottom.at<float>(0,2) = 0.0f;

	extrinsicBottom.at<float>(1,0) = 0.0f; 
	extrinsicBottom.at<float>(1,1) = std::cos(M_PI*0.5f);  
	extrinsicBottom.at<float>(1,2) = -std::sin(M_PI*0.5f);

	extrinsicBottom.at<float>(2,0) = 0.0f;
	extrinsicBottom.at<float>(2,1) = std::sin(M_PI*0.5f);  
	extrinsicBottom.at<float>(2,2) = std::cos(M_PI*0.5f);

	// reference frame
	extrinsicFront.at<float>(0,0) = 1.0f; 
	extrinsicFront.at<float>(0,1) = 0.0f; 
	extrinsicFront.at<float>(0,2) = 0.0f;

	extrinsicFront.at<float>(1,0) = 0.0f; 
	extrinsicFront.at<float>(1,1) = 1.0f; 
	extrinsicFront.at<float>(1,2) = 0.0f;

	extrinsicFront.at<float>(2,0) = 0.0f; 
	extrinsicFront.at<float>(2,1) = 0.0f; 
	extrinsicFront.at<float>(2,2) = 1.0f;

	// rotate y : clockwise +180
	extrinsicBack.at<float>(0,0) = std::cos(M_PI);  
	extrinsicBack.at<float>(0,1) = 0.0f; 
	extrinsicBack.at<float>(0,2) = std::sin(M_PI);

	extrinsicBack.at<float>(1,0) = 0.0f;   		       
	extrinsicBack.at<float>(1,1) = 1.0f; 
	extrinsicBack.at<float>(1,2) = 0.0f;

	extrinsicBack.at<float>(2,0) = -std::sin(M_PI); 
	extrinsicBack.at<float>(2,1) = 0.0f; 
	extrinsicBack.at<float>(2,2) = std::cos(M_PI);

	// rotate y : clockwise -90
	extrinsicRight.at<float>(0,0) = std::cos(M_PI*(-0.5f));  
	extrinsicRight.at<float>(0,1) = 0.0f; 
	extrinsicRight.at<float>(0,2) = std::sin(M_PI*(-0.5f));

	extrinsicRight.at<float>(1,0) = 0.0f;       		   
	extrinsicRight.at<float>(1,1) = 1.0f; 
	extrinsicRight.at<float>(1,2) = 0.0f;

	extrinsicRight.at<float>(2,0) = -std::sin(M_PI*(-0.5f)); 
	extrinsicRight.at<float>(2,1) = 0.0f; 
	extrinsicRight.at<float>(2,2) = std::cos(M_PI*(-0.5f));

	// rotate y : clockwise +90
	extrinsicLeft.at<float>(0,0) = std::cos(M_PI*0.5f);  
	extrinsicLeft.at<float>(0,1) = 0.0f; 
	extrinsicLeft.at<float>(0,2) = std::sin(M_PI*0.5f);

	extrinsicLeft.at<float>(1,0) = 0.0f;       		   
	extrinsicLeft.at<float>(1,1) = 1.0f; 
	extrinsicLeft.at<float>(1,2) = 0.0f;

	extrinsicLeft.at<float>(2,0) = -std::sin(M_PI*0.5f); 
	extrinsicLeft.at<float>(2,1) = 0.0f; 
	extrinsicLeft.at<float>(2,2) = std::cos(M_PI*0.5f);

	Cubemap* cubemap = new Cubemap(
		std::make_shared<cv::Mat>(cv::imread("./input/top.png")), std::make_shared<cv::Mat>(extrinsicTop), 
		std::make_shared<cv::Mat>(cv::imread("./input/bottom.png")), std::make_shared<cv::Mat>(extrinsicBottom), 
		std::make_shared<cv::Mat>(cv::imread("./input/front.png")), std::make_shared<cv::Mat>(extrinsicFront), 
		std::make_shared<cv::Mat>(cv::imread("./input/back.png")), std::make_shared<cv::Mat>(extrinsicBack), 
		std::make_shared<cv::Mat>(cv::imread("./input/right.png")), std::make_shared<cv::Mat>(extrinsicRight), 
		std::make_shared<cv::Mat>(cv::imread("./input/left.png")), std::make_shared<cv::Mat>(extrinsicLeft) 
	);

	// 2K height
	cv::imshow("test", *(cubemap->ToEquirectangular(PANORAMA_Height)));
	cv::waitKey(0);


	/* code */
	return 0;
}