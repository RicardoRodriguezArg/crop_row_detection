#ifndef __IMAGE_SEGMETATOR_H
#define __IMAGE_SEGMETATOR_H
#include "utils_definitions.h"
namespace NSImageUtils{
	template<SegmentationType>
	struct Segmentator;

	
	template<>
	struct Segmentator<SegmentationType::OTSU_CLASSIC>
	{

	};
	
	using OtsuClassicSegmentator = Segmentator<SegmentationType::OTSU_CLASSIC>;

	template<>
	struct Segmentator<SegmentationType::OTSU_HLS>
	{
		Segmentator()
	};
	using OtsuLigthSegmentator = Segmentator<SegmentationType::OTSU_HLS>;
	
}
#endif