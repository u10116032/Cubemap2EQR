#ifndef CubemapPlane_hpp
#define CubemapPlane_hpp

#include <opencv2/opencv.hpp>
#include <memory>
#include <cmath>
#include <stdexcept>

class CubemapPlane{

public:
	CubemapPlane(std::shared_ptr<cv::Mat> data, std::shared_ptr<cv::Mat> extrinsicMatrix);

	std::shared_ptr<cv::Mat> GetData();

	cv::Vec3b GetPixel(float rigCoordX, float rigCoordY, float rigCoordZ);

private:
	std::shared_ptr<cv::Mat> data;
	std::shared_ptr<cv::Mat> extrinsicMatrix;
	std::shared_ptr<cv::Mat> instrinsicMatrix;

	const float FOV_X = 90.0f;
	const float FOV_Y = 90.0f;

};

#endif /* CubemapPlane_hpp */