#ifndef __PIPELINE_FEATURE_EXTRACTION_CONFIG_H__
#define __PIPELINE_FEATURE_EXTRACTION_CONFIG_H__
#include <string>
namespace NSConfig {
    struct FeatureExtracionConfig {
        FeatureExtracionConfig(int max_features, float match_percent_aceptable,
                               const std::string &descriptor_name)
            : max_features_(std::move(max_features)),
              match_percent_aceptable_(std::move(match_percent_aceptable)),
              descriptor_name_(descriptor_name) {}

        FeatureExtracionConfig()
            : max_features_(100), match_percent_aceptable_(0.75), descriptor_name_("FlannBased") {}

        FeatureExtracionConfig operator=(const FeatureExtracionConfig &other) {
            return {other.max_features_, other.match_percent_aceptable_, other.descriptor_name_};
        }
        ~FeatureExtracionConfig() = default;
        const int max_features_;
        const float match_percent_aceptable_;
        const std::string descriptor_name_;
    };
} // namespace NSConfig
#endif