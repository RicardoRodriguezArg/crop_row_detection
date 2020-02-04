#ifndef _UTILS_IMAGE_CHECKER_H__
#define _UTILS_IMAGE_CHECKER_H__
namespace NSImageChecker {
    class FileNameUtils {
        enum class ActionToPerform {
            REMOVED_FILE_THAT_NOT_MATCH_CRITERIA,
            CREATE_REPORT_ON_NOT_MATCH_CRITERIA
        };

        public:
        explicit FileNameUtils(const std::string &input_directory);
        void checkImageSize(const std::size_t &witht, const std::size_t &height,
                            const ActionToPerform &action);

        private:
        void remove_file(const std::string &file_to_be_remove) const;
    };
} // namespace NSImageChecker
#endif