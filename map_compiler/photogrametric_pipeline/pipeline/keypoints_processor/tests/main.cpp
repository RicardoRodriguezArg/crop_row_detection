#include "keypoints_processor/feature_exceptions.h"
#include "keypoints_processor/feature_extraction_config.h"
#include "keypoints_processor/feature_extraction_task.h"
#include "keypoints_processor/feature_keypoints.h"
#include "keypoints_processor/feature_processing_task_based.h"
#include "utils/cv_utils.h"
//#include "keypoints_processor/keypoints_repository.h"
#include <glog/logging.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Pipeline_keypoints_processor {
    TEST(KEYPOINT_EXTRACTION_CLASSIC_APPROACH, KEYPOINT_PROCESSOR_EXCEPTION) {
        constexpr int max_features{};
        const float match_percent_aceptable{};
        const std::string &descriptor_name{""};
        NSFeatureExtraction::FeatureExtraction feature_extraction{
            max_features, match_percent_aceptable, descriptor_name};
        try {
            feature_extraction.detectFeatures();
            FAIL() << "detectFeatures() should throw an exception\n";
        } catch (std::runtime_error &exception) {
            EXPECT_EQ(exception.what(), std::string("Error: Empty Raw Image Mat"));
        } catch (NSFeatureExtraction::FeatureException &exception) {
            EXPECT_EQ(exception.what(), std::string("Error: Matcher not Init or not define"));
        } catch (...) {
            FAIL() << "ERROR: Unexpected exception thrown: " << std::current_exception << std::endl;
        }
    }

    TEST(KEYPOINT_EXTRACTION_CLASSIC_APPROACH, EXTRACT_FEATURE_OK) {
        constexpr int max_features{500};
        const float match_percent_aceptable{0.15f};
        const std::string &descriptor_name{"FlannBased"};
        NSFeatureExtraction::FeatureExtraction feature_extraction{
            max_features, match_percent_aceptable, descriptor_name};
        // load image mat from file
        const std::string image_filename{"resources/image_a.png"};
        // TODO:encapsulate and test
        auto image_raw_color = NSFeatureExtraction::Utils::loadImageFromFileName(image_filename);
        EXPECT_EQ(false, image_raw_color.empty());
        feature_extraction.setRawImage(image_raw_color);
        EXPECT_NO_THROW(feature_extraction.detectFeatures());
        // add
        const auto keypoint_container = feature_extraction.getKeyPointContainer();
        const auto keypoint_descriptor = feature_extraction.getKeyPointDescriptor();
        ASSERT_EQ(216, keypoint_container.size())
            << "detected keypoints for test image is " << keypoint_container.size();
        cv::Size expected_size{32, 216};
        ASSERT_EQ(expected_size, keypoint_descriptor.size())
            << "keypoints descriptor for test image is " << keypoint_descriptor.size();
    }

    TEST(KEYPOINT_EXTRACTION_CLASSIC_APPROACH, EXTRACT_FEATURE_CHECKER_OK) {
        constexpr int max_features{500};
        const float match_percent_aceptable{0.15f};
        const std::string &descriptor_name{"FlannBased"};
        NSFeatureExtraction::FeatureExtraction feature_extraction{
            max_features, match_percent_aceptable, descriptor_name};
        // load image mat from file
        const std::string image_filename{"resources/chess_board_test.png"};
        // TODO:encapsulate and test
        auto image_raw_color = NSFeatureExtraction::Utils::loadImageFromFileName(image_filename);
        EXPECT_EQ(false, image_raw_color.empty());
        feature_extraction.setRawImage(image_raw_color);
        EXPECT_NO_THROW(feature_extraction.detectFeatures());
        // add
        const std::vector<cv::KeyPoint> keypoint_container =
            feature_extraction.getKeyPointContainer();
        const cv::Mat keypoint_descriptor = feature_extraction.getKeyPointDescriptor();
        ASSERT_EQ(116, keypoint_container.size())
            << "detected keypoints for test image is " << keypoint_container.size();
        cv::Size expected_size{32, 116};
        ASSERT_EQ(expected_size, keypoint_descriptor.size())
            << "keypoints descriptor for test image is " << keypoint_descriptor.size();
    }

    TEST(KEYPOINT_EXTRACTION_MULTITHREAD_APPROACH, EXTRACT_FEATURE_MULTIPLE_IMAGES_OK) {
        // parameters for Multithread processing
        const int max_thread_count{4};
        NSFeatureExtraction::MultiThreadFeatureProcessing feature_processing{"./resources",
                                                                             max_thread_count};
        feature_processing.extractKeypointFeature();
        ASSERT_EQ(feature_processing.getImagesProcessingCount(),
                  feature_processing.getFeatureExtractionContainer().size());
        // load image mat from file
    }

    TEST(KEYPOINT_EXTRACTION_MULTITHREAD_APPROACH,
         EXTRACT_FEATURE_MULTIPLE_IMAGES_PARAMETER_CHECK_TUNNING_OK) {
        // parameters for Multithread processing
        const int max_thread_count{10};
        NSFeatureExtraction::MultiThreadFeatureProcessing feature_processing{"./resources",
                                                                             max_thread_count};
        feature_processing.extractKeypointFeature();
        ASSERT_EQ(feature_processing.getImagesProcessingCount(),
                  feature_processing.getFeatureExtractionContainer().size());
    }

} // namespace Pipeline_keypoints_processor

int main(int argc, char **argv) {
    // Initialize Google's logging library.
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}