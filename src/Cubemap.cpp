#include "Cubemap.hpp"

Cubemap::Cubemap(
	std::shared_ptr<cv::Mat> top, std::shared_ptr<cv::Mat> extrinsicTop,
	std::shared_ptr<cv::Mat> bottom, std::shared_ptr<cv::Mat> extrinsicBottom,
	std::shared_ptr<cv::Mat> front, std::shared_ptr<cv::Mat> extrinsicFront,
	std::shared_ptr<cv::Mat> back, std::shared_ptr<cv::Mat> extrinsicBack,
	std::shared_ptr<cv::Mat> right, std::shared_ptr<cv::Mat> extrinsicRight,
	std::shared_ptr<cv::Mat> left, std::shared_ptr<cv::Mat> extrinsicLeft)
{
	planes["top"] = std::shared_ptr<CubemapPlane>(new CubemapPlane(top, extrinsicTop));
	planes["bottom"] = std::shared_ptr<CubemapPlane>(new CubemapPlane(bottom, extrinsicBottom));
	planes["front"] = std::shared_ptr<CubemapPlane>(new CubemapPlane(front, extrinsicFront));
	planes["back"] = std::shared_ptr<CubemapPlane>(new CubemapPlane(back, extrinsicBack));
	planes["right"] = std::shared_ptr<CubemapPlane>(new CubemapPlane(right, extrinsicRight));
	planes["left"] = std::shared_ptr<CubemapPlane>(new CubemapPlane(left, extrinsicLeft));
}

std::shared_ptr<CubemapPlane> Cubemap::GetPlane(std::string indice)
{
	return planes[indice];
}

std::shared_ptr<cv::Mat> Cubemap::ToEquirectangular(int height)
{
	cv::Mat equirectangular = cv::Mat::zeros(height, height*2, CV_8UC3);

	for (int i=0; i < equirectangular.rows; i++){
		for (int j=0; j < equirectangular.cols; j++){

			float theta = ((2.0f * (float)j / (float)equirectangular.cols) - 1.0f ) * M_PI;
			float phi = ((2.0f * (float)i / (float)equirectangular.rows) - 1.0f ) * M_PI / 2.0f;

			float worldCoordX = std::cos(phi) * std::cos(theta);
			float worldCoordY = std::sin(phi);
			float worldCoordZ = std::cos(phi) * std::sin(theta);

			for (auto plane : planes){
				try{
					equirectangular.at<cv::Vec3b>(i, j) = (plane.second)->GetPixel(worldCoordX, worldCoordY, worldCoordZ);
				}
				catch(std::out_of_range &e){
					continue;
				}
			}

		}
	}

	return std::make_shared<cv::Mat>(equirectangular);
}