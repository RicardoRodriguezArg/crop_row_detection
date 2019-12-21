#ifndef __PIPELINE_ORTO_UTILS__
#define __PIPELINE_ORTO_UTILS__
namespace NSPipelineUtils {
    namespace Factory {
        struct FactoryBase {
            virtual ~FactoryBase() {}
            virtual int getID() { return 1; }
        };
    } // namespace Factory
} // namespace NSPipelineUtils
#endif