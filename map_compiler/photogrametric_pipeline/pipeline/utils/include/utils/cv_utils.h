#ifndef __PIPELINE_UTILS_H__
#define __PIPELINE_UTILS_H__

#include <iterator>
#include <opencv2/opencv.hpp>
#include <string>
namespace NSFeatureExtraction {
    struct Utils {
        static cv::Mat convertToGreyScale(const cv::Mat &image);
        static cv::Mat loadImageFromFileName(const std::string &image_filename);
        static std::tuple<double, double> getImageDimension(const std::string &image_filename);
    };
    namespace Generics {
        template <typename Iterator, typename Functor>
        void iterate_over_all_in_pairs_(Iterator first, Iterator last, Functor functor,
                                        std::forward_iterator_tag) {
            if (first != last) {
                Iterator previous = first;
                ++first;
                for (; first != last; ++first, ++previous) {
                    for (Iterator iterator = first; iterator != last; ++iterator) {
                        functor(*previous, *first);
                    }
                }
            }
        }

        template <typename Iterator, typename Functor>
        void iterate_over_all_in_pairs(Iterator first, Iterator last, Functor functor) {
            using iterator_type = typename std::iterator_traits<Iterator>::iterator_category;
            iterator_type t;
            iterate_over_all_in_pairs_(first, last, functor, t);
        }

    } // namespace Generics
} // namespace NSFeatureExtraction
#endif