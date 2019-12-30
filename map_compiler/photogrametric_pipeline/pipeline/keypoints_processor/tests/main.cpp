#include "keypoints_processor/feature_exceptions.h"
#include "keypoints_processor/feature_extraction.h"
#include "keypoints_processor/feature_extraction_config.h"
#include "keypoints_processor/feature_extraction_task.h"
#include "keypoints_processor/feature_processing.h"
#include "utils/cv_utils.h"
//#include "keypoints_processor/keypoints_repository.h"
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
        ASSERT_EQ(keypoint_container.size(), keypoint_container.size())
            << "detected keypoints for image a is " << keypoint_container.size();
    }
} // namespace Pipeline_keypoints_processor

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}