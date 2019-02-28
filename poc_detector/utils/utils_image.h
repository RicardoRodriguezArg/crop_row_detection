#ifndef __UTILS__FILES_
#define __UTILS__FILES_

#include <opencv2/opencv.hpp>
#include <string>
#include "utils_definitions.h"
namespace NSImageUtils{
	class ImageWrapper
	{
	public:
		explicit ImageLoader(const std::string & filename) ;
		bool is_valid_image() const noexcept;
		void transform_background_color() ;
		void segment_image(const SegmentationType & type) noexcept;
	private:
		void get_image_from_filename(const std::string & filename);
		cv::Mat image;
		const cv::Mat kernel;
	};
}
#endif