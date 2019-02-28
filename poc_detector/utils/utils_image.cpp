#include utils_image.h

namespace NSImageUtils{


ImageLoader::ImageLoader(const std::string & filename):kernel((Mat_<float>(3,3) <<
            1,  1, 1,
            1, -8, 1,
            1,  1, 1)) 
{}

bool is_valid_image() const noexcept
{
  return image.data != nullptr;
}

void ImageLoader::get_image_from_filename(const std::string & filename)
{
	image =std::move(cv::imread(filename.c_str()));
}


void ImageLoader::transform_background_color()
{
	const cv::Vec3b BlackColor(255,255,255);
	for( int x = 0; x < image.rows; x++ ) {
      for( int y = 0; y < image.cols; y++ ) {
      	  auto & current_pixel = image.at<Vec3b>(x, y);
          if ( current_pixel == BlackColor ) {
            current_pixel[0] = 0;
            current_pixel[1] = 0;
            current_pixel[2] = 0;
          }
        }
}
}