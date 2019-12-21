#pragma once
#include <opencv2/opencv.hpp>
namespace NSFeatureExtraction
{
	struct Utils
	{
	 static cv::Mat convertToGreyScale(const cv::Mat & image);
	};
}