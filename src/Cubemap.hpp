#ifndef Cubemap_hpp
#define Cubemap_hpp

#include <opencv2/opencv.hpp>
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include <cmath>
#include <stdexcept>

#include "CubemapPlane.hpp"

class Cubemap{

public:


	Cubemap(std::shared_ptr<cv::Mat> top, std::shared_ptr<cv::Mat> extrinsicTop,
	std::shared_ptr<cv::Mat> bottom, std::shared_ptr<cv::Mat> extrinsicBottom,
	std::shared_ptr<cv::Mat> front, std::shared_ptr<cv::Mat> extrinsicFront,
	std::shared_ptr<cv::Mat> back, std::shared_ptr<cv::Mat> extrinsicBack,
	std::shared_ptr<cv::Mat> right, std::shared_ptr<cv::Mat> extrinsicRight,
	std::shared_ptr<cv::Mat> left, std::shared_ptr<cv::Mat> extrinsicLeft);

	std::shared_ptr<CubemapPlane> GetPlane(std::string indice);

	std::shared_ptr<cv::Mat> ToEquirectangular(int width);

private:

	std::unordered_map<std::string, std::shared_ptr<CubemapPlane> > planes;



};

#endif /* Cubemap_hpp */