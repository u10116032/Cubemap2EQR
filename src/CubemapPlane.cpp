#include "CubemapPlane.hpp"

CubemapPlane::CubemapPlane(std::shared_ptr<cv::Mat> data, std::shared_ptr<cv::Mat> extrinsicMatrix)
{
	this->data = data;
	this->extrinsicMatrix = extrinsicMatrix;

	instrinsicMatrix = std::make_shared<cv::Mat>(
		cv::Mat::zeros(3,3,CV_32F)
	);

	float fx = (float)data->cols * (1.0f / (std::tan(FOV_X * M_PI * 0.5f / 180.0f) * 2.0f));
	float fy = (float)data->rows * (1.0f / (std::tan(FOV_Y * M_PI * 0.5f / 180.0f) * 2.0f));

	instrinsicMatrix->at<float>(0,0) = fx; 
	instrinsicMatrix->at<float>(1,1) = fy;
	instrinsicMatrix->at<float>(0,2) = (0.5f) * (float)data->cols; 
	instrinsicMatrix->at<float>(1,2) = (0.5f) * (float)data->rows;
	instrinsicMatrix->at<float>(2,2) = 1.0f;

	// std::cout << *instrinsicMatrix << std::endl;
}

std::shared_ptr<cv::Mat> CubemapPlane::GetData()
{
	return data;
}

cv::Vec3b CubemapPlane::GetPixel(float rigCoordX, float rigCoordY, float rigCoordZ)
{
	cv::Mat rigCoord = cv::Mat::zeros(3,1, CV_32F);
	rigCoord.at<float>(0,0) = rigCoordX;
	rigCoord.at<float>(1,0) = rigCoordY;
	rigCoord.at<float>(2,0) = rigCoordZ;

	cv::Mat camCoord = (*extrinsicMatrix * rigCoord);

	if (camCoord.at<float>(2,0) < 0)
		throw (std::out_of_range("Z Value < 0"));

	cv::Mat screenCoord = (*instrinsicMatrix) * camCoord;
	int screenCoordW = (int)(screenCoord.at<float>(0,0) / screenCoord.at<float>(2,0));
	int screenCoordH = (int)(screenCoord.at<float>(1,0) / screenCoord.at<float>(2,0));

	if (screenCoordW > (data->cols - 1) || screenCoordH > (data->rows - 1) 
		|| screenCoordW < 0 || screenCoordH < 0)
		throw (std::out_of_range("Pixel Out Of Range"));

	return data->at<cv::Vec3b>((int)screenCoordH, (int)screenCoordW);
}