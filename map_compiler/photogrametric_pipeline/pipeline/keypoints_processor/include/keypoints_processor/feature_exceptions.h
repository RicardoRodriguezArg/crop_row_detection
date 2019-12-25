#ifndef __FEATURE_EXTRACTION_EXCEPTIONS_H__
#define __FEATURE_EXTRACTION_EXCEPTIONS_H__
#include <exception>
#include <string>
namespace NSFeatureExtraction {
    struct FeatureException : public std::exception {
        FeatureException(const std::string &exception_message)
            : exception_message_(exception_message) {}
        const char *what() const throw() { return exception_message_.c_str(); }

        private:
        const std::string &exception_message_;
    };
} // namespace NSFeatureExtraction
#endif