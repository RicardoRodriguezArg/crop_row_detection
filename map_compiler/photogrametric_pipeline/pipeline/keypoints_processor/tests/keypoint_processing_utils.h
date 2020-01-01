#ifndef __KEYPOINT_PROCESSING_UNIT_TEST_UTILS_H__
#define __KEYPOINT_PROCESSING_UNIT_TEST_UTILS_H__
#include <opencv2/opencv.hpp>
namespace Pipeline_keypoints_processor {
namespace utils {
const cv::Mat REFERENCE_DESCRIPTOR_MATRIX{32, 116};
/*
[252, 112, 253, 100,  36,  14,  75,  16,  96, 136, 183,   8,  83,  19, 209,  59,
30, 196,  76, 106, 137,  96, 225,   8, 195, 233,  97,  20,  96, 179,  66,  33;
252, 112, 253, 100,  36,  14,  75,  16,  96, 136, 183,   8,  83,  19, 209,  59,
30, 196,  76, 106, 137,  96, 225,   8, 195, 233,  97,  20,  96, 179,  66,  33;
3, 143,  66, 156,  20, 131, 174, 230,  84,   0,  90, 231,  96, 224, 180, 196,
120,  42,   2, 237, 231, 184,   4, 255,  32,  38, 138, 128,  29, 172, 120, 140;
236,  48, 253, 100,  36,  14,  89,  16,  97, 178,  39,  24, 223,  19,  73,  59,
134, 212, 108, 122, 136, 100, 240,   0, 195, 217,  97,  52,  98, 163,  66,  34;
2, 139,   2, 158,  19, 145, 162, 231, 150,   5,  72, 163,  32, 234,  50, 196,
120,  43, 131, 197,   6, 154,   6, 253,  40,  38, 154, 139,  20,  14, 184, 142;
204,  48, 185,  96,  32,  44,  81,  24, 105, 186,  37,  24, 159,  19,  73,  27,
132, 148, 108,  58,   8, 100, 240,   0, 195, 217,  81,  52, 194, 161,  66,  35;
3, 143,  66, 156,  20, 131, 174, 230,  84,   0,  90, 231,  96, 224, 182, 196,
120,  42,   2, 237, 231, 184,   4, 255,  32,  38, 138, 128,  29, 172, 120, 140;
236,  48, 253, 100,  36,  12,  81,  16,  97, 178, 167,  24, 223,  19,  73,  59,
134, 148, 125, 122, 136, 100, 240,   0, 195, 217,  97,  52,  98, 161,  66,  34;
3, 143,   2, 156,  20, 131, 170, 231,  22,   0,  72, 231,  32, 232, 182, 196,
120,  42,   2, 197,   6, 154,   4, 253,  32,  38, 138, 131,  21,  12,  56, 140;
100,  48, 184, 112,  32, 109,  81,  24, 107, 187,  37,  24, 150,  31,  72,  27,
133,  21, 108,  16,  26, 100, 242,   0, 203, 217, 113, 118, 192,   0,  67,   3;
2, 143,   2, 158,  19, 147, 170, 231, 150,   5,  72, 167,  32, 234,  50, 196,
120,  43, 130, 197,   6, 154,   6, 253,  40,  38, 154, 139,  20,  14, 184, 140;
64, 176, 152, 240, 169, 237,  17,   2, 171,  59,  32,  24, 150,  31,  72,  26,
129,  19, 125,  16,  18, 108, 210,  80, 205, 209,  48, 127, 192,  64,   7,  19;
228,  48, 184, 112,  33, 109,  81,  24, 107, 187,  37,  24, 150,  31,  72,  27,
133,  21, 108,  24,  26, 100, 240,   0, 203, 217, 112, 118, 192,   0,  67,   3;
228,  48, 184, 112,  33, 109,  81,  24, 107, 187,  37,  24, 150,  31,  72,  27,
133,  21, 108,  24,  26, 100, 240,   0, 203, 217, 112, 118, 192,   0,  67,   3;
64, 176, 152, 240, 169, 237,  17,   2, 171,  59,  32,  24, 150,  31,  72,  26,
129,  19, 125,  16,  18, 108, 210,  80, 205, 209,  48, 127, 192,  64,   7,  19;
2, 143,   2, 158,  19, 147, 170, 231, 150,   5,  72, 167,  32, 234,  50, 196,
120,  43, 130, 197,   6, 154,   6, 253,  40,  38, 154, 139,  20,  14, 184, 140;
100,  48, 184, 112,  32, 109,  81,  24, 107, 187,  37,  24, 150,  31,  72,  27,
133,  21, 108,  16,  26, 100, 242,   0, 203, 217, 113, 118, 192,   0,  67,   3;
3, 143,   2, 156,  20, 131, 170, 231,  22,   0,  72, 231,  32, 232, 182, 196,
120,  42,   2, 197,   6, 154,   4, 253,  32,  38, 138, 131,  21,  12,  56, 140;
236,  48, 253, 100,  36,  12,  81,  16,  97, 178, 167,  24, 223,  19,  73,  59,
134, 148, 125, 122, 136, 100, 240,   0, 195, 217,  97,  52,  98, 161,  66,  34;
3, 143,  66, 156,  20, 131, 174, 230,  84,   0,  90, 231,  96, 224, 182, 196,
120,  42,   2, 237, 231, 184,   4, 255,  32,  38, 138, 128,  29, 172, 120, 140;
204,  48, 185,  96,  32,  44,  81,  24, 105, 186,  37,  24, 159,  19,  73,  27,
132, 148, 108,  58,   8, 100, 240,   0, 195, 217,  81,  52, 194, 161,  66,  35;
2, 139,   2, 158,  19, 145, 162, 231, 150,   5,  72, 163,  32, 234,  50, 196,
120,  43, 131, 197,   6, 154,   6, 253,  40,  38, 154, 139,  20,  14, 184, 142;
236,  48, 253, 100,  36,  14,  89,  16,  97, 178,  39,  24, 223,  19,  73,  59,
134, 212, 108, 122, 136, 100, 240,   0, 195, 217,  97,  52,  98, 163,  66,  34;
3, 143,  66, 156,  20, 131, 174, 230,  84,   0,  90, 231,  96, 224, 180, 196,
120,  42,   2, 237, 231, 184,   4, 255,  32,  38, 138, 128,  29, 172, 120, 140;
68,  32, 241,  96, 104, 104,  97,   0, 105, 178, 163,  24, 158,  19,  65,  26,
162, 148, 108,  58,   8, 100, 209,  64, 213, 152,  81, 116, 192, 161,  70,  34;
3, 195,   6, 141,  28, 131, 168, 111, 134,   0, 194, 199,  33, 200,  54, 192,
104,  43,  10, 197,  70, 139,   7, 221,  32,  32, 138,   1,  29,  12, 184, 140;
2, 131,  14, 142,  30, 129, 184, 109, 134,   5, 200, 163,  36, 202,  42,  64,
216,  43, 139, 133,  86, 139,   6, 221,  56,  36, 138, 219,  21,  14, 185, 142;
68,  48, 185,  96, 104, 109, 113,   0,  43, 185,  49,  56, 150,  23,  72,  26,
131,  21, 127,  16,  18, 112, 194,  64, 205, 156,  48, 102, 192,  67,   7,  35;
100,  32, 241,  96, 104, 104,  97,   0, 105, 179, 163,  24, 150,  19,  65,  26,
162, 148, 108,  58,   9, 100, 209,  64, 213, 152,  81, 116, 192, 161,  70,  34;
3, 131,   6, 141,  28, 131, 168, 111, 134,   0, 192, 199,  33, 200,  54, 192,
104,  43,  10, 197,  70, 139,   7, 221,  32,  32, 138,   1,  29,  12, 184, 140;
3, 131,   6, 141,  28, 131, 168, 111, 134,   1, 192, 199,  32, 200,  54, 192,
104,  43,  10, 197,  86, 139,   7, 221,  36,  32, 138,   1,  29,  12, 184, 140;
68,  32, 241,  96, 104, 104,  97,   0, 105, 178, 163,  24, 150,  19,  65,  26,
162, 148, 108,  58,   8, 100, 209,  64, 213, 152,  81,  52, 192, 161,  70,  34;
68,  32, 185,  96, 104, 109, 113,   0,  43, 185,  49,  56, 150,  23,  72,  26,
131,  21, 127,  16,  18, 112, 194,  64, 205, 156,  48, 102, 192,  66,   7,  35;
18, 131,  14, 142,  30, 129, 184, 109, 134,   5, 200, 163, 100, 202,  42,  64,
216,  43, 139, 133,  94, 139,   6, 221, 184,  36, 138, 219,  21,  14, 189, 142;
3, 131,   6, 141,  28, 131, 168, 111, 134,   0, 192, 199,  32, 200,  54, 192,
104,  43,  10, 197,  70, 139,   7, 221,  32,  32, 138,   1,  29,  12, 184, 140;
68,  32, 241,  96, 104, 104,  97,   0, 105, 178, 163,  24, 150,  19,  65,  26,
162, 148, 108,  58,   8, 100, 209,  64, 213, 152,  81,  52, 192, 161,  71,  34;
131,  75,  70, 157,  20, 147, 168, 103,  84,   0,  66, 198,  33,   0, 180, 197,
104,  40,   2, 237, 229, 184,   5, 157,  36,  34, 154,   0,  29, 140, 120, 140;
252,  32, 247, 100,   5,  78,  65,  16,  97, 162, 162,  24,  27,  19,  65,  63,
34, 212, 104, 106,   9, 103, 241, 128, 211, 248,  65,  20,  98, 177,  66,  34;
68,  32, 241,  96,  96, 108, 113,  16, 105, 178,  33,  24, 158,  23,  65,  62,
162, 148, 125,  58,   9, 100, 240,  64, 215, 152,  81,  54, 192, 163,  70,  34;
3, 131,   6, 156,  30, 131, 168, 111, 134,   0, 192, 199,  33, 200,  54, 193,
120,  42,  10, 197,  70, 139,   7, 221,  32,  32, 138,   1,  21,  12, 184, 140;
131,  75,  70, 157,  20, 147, 168, 103,  84,   0,  66, 198, 161,   0, 180, 197,
104,  40,   2, 237, 229, 184,   5, 221,  36,  34, 154,   0,  29, 140, 120, 140;
252,  32, 243, 100,   5,  78,  65,  16,  97, 162, 166,  24,  27,  19,  65,  63,
34, 212, 104, 106,   9, 103, 241, 128, 211, 248,  65,  52,  98, 177,  66,  34;
252,  32, 243, 100,   5,  78,  65,  16,  97, 162, 166,  24,  27,  19,  65,  63,
34, 212, 104, 106,   9, 103, 241, 128, 211, 248,  65,  52,  98, 177,  66,  34;
131,  75,  70, 157,  20, 147, 168, 103,  84,   0,  66, 198, 161,   0, 180, 197,
104,  40,   2, 237, 229, 184,   5, 221,  36,  34, 154,   0,  29, 140, 120, 140;
3, 131,   6, 156,  30, 131, 168, 111, 134,   0, 192, 199,  33, 200,  54, 193,
120,  42,  10, 197,  70, 139,   7, 221,  32,  32, 138,   1,  21,  12, 184, 140;
68,  32, 241,  96,  96, 108, 113,  16, 105, 178,  33,  24, 158,  23,  65,  62,
162, 148, 125,  58,   9, 100, 240,  64, 215, 152,  81,  54, 192, 163,  70,  34;
252,  32, 247, 100,   5,  78,  65,  16,  97, 162, 162,  24,  27,  19,  65,  63,
34, 212, 104, 106,   9, 103, 241, 128, 211, 248,  65,  20,  98, 177,  66,  34;
131,  75,  70, 157,  20, 147, 168, 103,  84,   0,  66, 198,  33,   0, 180, 197,
104,  40,   2, 237, 229, 184,   5, 157,  36,  34, 154,   0,  29, 140, 120, 140;
68,  32, 241,  96, 104, 104,  97,   0, 105, 178, 163,  24, 150,  19,  65,  26,
162, 148, 108,  58,   8, 100, 209,  64, 213, 152,  81,  52, 192, 161,  71,  34;
3, 131,   6, 141,  28, 131, 168, 111, 134,   0, 192, 199,  32, 200,  54, 192,
104,  43,  10, 197,  70, 139,   7, 221,  32,  32, 138,   1,  29,  12, 184, 140;
18, 131,  14, 142,  30, 129, 184, 109, 134,   5, 200, 163, 100, 202,  42,  64,
216,  43, 139, 133,  94, 139,   6, 221, 184,  36, 138, 219,  21,  14, 189, 142;
68,  32, 185,  96, 104, 109, 113,   0,  43, 185,  49,  56, 150,  23,  72,  26,
131,  21, 127,  16,  18, 112, 194,  64, 205, 156,  48, 102, 192,  66,   7,  35;
68,  32, 241,  96, 104, 104,  97,   0, 105, 178, 163,  24, 150,  19,  65,  26,
162, 148, 108,  58,   8, 100, 209,  64, 213, 152,  81,  52, 192, 161,  70,  34;
3, 131,   6, 141,  28, 131, 168, 111, 134,   1, 192, 199,  32, 200,  54, 192,
104,  43,  10, 197,  86, 139,   7, 221,  36,  32, 138,   1,  29,  12, 184, 140;
3, 131,   6, 141,  28, 131, 168, 111, 134,   0, 192, 199,  33, 200,  54, 192,
104,  43,  10, 197,  70, 139,   7, 221,  32,  32, 138,   1,  29,  12, 184, 140;
100,  32, 241,  96, 104, 104,  97,   0, 105, 179, 163,  24, 150,  19,  65,  26,
162, 148, 108,  58,   9, 100, 209,  64, 213, 152,  81, 116, 192, 161,  70,  34;
68,  48, 185,  96, 104, 109, 113,   0,  43, 185,  49,  56, 150,  23,  72,  26,
131,  21, 127,  16,  18, 112, 194,  64, 205, 156,  48, 102, 192,  67,   7,  35;
2, 131,  14, 142,  30, 129, 184, 109, 134,   5, 200, 163,  36, 202,  42,  64,
216,  43, 139, 133,  86, 139,   6, 221,  56,  36, 138, 219,  21,  14, 185, 142;
3, 195,   6, 141,  28, 131, 168, 111, 134,   0, 194, 199,  33, 200,  54, 192,
104,  43,  10, 197,  70, 139,   7, 221,  32,  32, 138,   1,  29,  12, 184, 140;
68,  32, 241,  96, 104, 104,  97,   0, 105, 178, 163,  24, 158,  19,  65,  26,
162, 148, 108,  58,   8, 100, 209,  64, 213, 152,  81, 116, 192, 161,  70,  34;
108,  60, 241,  82, 227, 120,  87, 146, 123, 234,  61,  56,  94, 247, 205,  62,
183, 127, 245,  26, 161, 116, 168, 226,  79, 222,  69, 166, 194, 247,  70, 115;
155, 147,  44, 190, 156, 151, 156, 189, 150,  93, 212, 247, 225, 108, 186, 193,
221,  35, 157, 229, 254, 201, 127, 189, 234,  99, 255, 193,  29, 140, 185,  95;
187, 151,  44, 190, 156, 151, 156, 189, 150,  92, 212, 231, 225, 108, 186, 193,
221,  35, 157, 229, 255, 201, 127, 189, 234,  99, 255, 209,  30, 140, 184,  95;
108,  60, 241,  82, 227, 120, 119, 146, 123, 234,  61,  56,  94, 247, 205,  62,
183, 127, 245,  26, 177, 116, 168, 226,  79, 222,  69, 166, 226, 247,  70, 115;
108,  60, 241,  82, 227, 120,  87, 146, 123, 235,  61,  56,  94, 247, 205,  62,
183, 127, 245,  26, 161, 116, 168, 226, 123, 222,  69, 174, 226, 247,  70, 115;
155, 147,  44, 190, 157, 151, 156, 189, 150,  92, 212, 231, 225, 108, 186, 193,
221,  35, 157, 229, 254, 201, 127, 157, 234,  99, 255, 145,  30, 140, 184,  95;
155, 215,  46, 190, 157, 151, 156, 189, 150,  92, 212, 199, 225, 108, 186, 193,
221,  99, 157, 229, 254, 201, 127, 189, 234,  99, 255, 145,  31,  12, 184,  95;
108,  60, 241,  82, 227, 120,  87, 146, 123, 234,  61,  56,  94, 247, 205,  62,
151, 127, 245,  26, 161, 116, 168, 226,  79, 222,  69, 166, 194, 247,  70, 119;
108,  60, 241,  82, 227, 120, 119, 146, 123, 234,  61,  56,  94, 247, 205,  62,
183, 127, 245,  26, 177, 116, 168, 226, 107, 222,  69, 174, 226, 247,  70, 115;
187, 147,  44, 190, 157, 151, 156, 189, 150,  93, 212, 247, 225, 108, 186, 193,
221,   3, 157, 229, 255, 201, 127, 189, 234,  99, 255, 209,  31, 140, 184,  95;
155, 147,  44, 190, 157, 151, 156, 189, 150,  92, 212, 231, 225, 108, 186, 193,
221,  67, 157, 229, 254, 201, 127, 189, 234,  99, 255, 129,  31, 140, 184,  95;
108,  60, 241,  82, 227, 120,  87, 146, 123, 234,  61,  56,  94, 247, 197,  62,
151, 126, 245,  26, 177, 116, 168, 226,  79, 222,  69, 166, 194, 247,  70, 119;
155, 215,  44, 190,  29, 151, 156, 189, 150,  92, 212, 247, 225, 108, 186, 193,
221,   3, 157, 229, 254, 201, 127, 157, 234,  99, 255, 145,  62, 140, 184,  95;
108,  60, 241,  82, 227, 120,  87, 146, 123, 235,  61,  56,  94, 255, 197,  62,
183, 127, 245,  26, 161, 116, 168, 226,  95, 222,  69, 166, 194, 247,  70, 115;
108,  60, 241,  82, 227, 120, 119, 146, 123, 234,  61,  56,  94, 247, 205,  62,
183, 127, 245,  26, 161, 116, 168, 226,  79, 222,  69, 166, 194, 247,  70, 243;
155, 147,  44, 190,  29, 151, 156, 189, 150,  92, 212, 231, 225, 108, 186, 193,
221,   3, 189, 229, 254, 201, 127, 157, 234,  99, 255, 145,  30, 140, 184,  95;
155, 215,  44, 190,  29, 151, 156, 189, 150,  92, 212, 231, 225, 108, 186, 193,
221,  67, 157, 229, 254, 201, 127, 157, 234,  99, 255, 145,  30, 140, 184,  95;
108,  60, 241,  82, 227, 120,  87, 146, 123, 235,  61,  56,  94, 247, 205,  62,
183, 127, 245,  26, 161, 116, 168, 226,  91, 222,  69, 174, 194, 247,  70, 115;
108,  60, 241,  82, 227, 120,  87, 146, 123, 235,  61,  56,  94, 247, 205,  62,
183, 127, 245,  26, 161, 116, 168, 226,  91, 222,  69, 174, 194, 247,  70, 115;
155, 215,  44, 190,  29, 151, 156, 189, 150,  92, 212, 231, 225, 108, 186, 193,
221,  67, 157, 229, 254, 201, 127, 157, 234,  99, 255, 145,  30, 140, 184,  95;
155, 147,  44, 190,  29, 151, 156, 189, 150,  92, 212, 231, 225, 108, 186, 193,
221,   3, 189, 229, 254, 201, 127, 157, 234,  99, 255, 145,  30, 140, 184,  95;
108,  60, 241,  82, 227, 120, 119, 146, 123, 234,  61,  56,  94, 247, 205,  62,
183, 127, 245,  26, 161, 116, 168, 226,  79, 222,  69, 166, 194, 247,  70, 243;
108,  60, 241,  82, 227, 120,  87, 146, 123, 235,  61,  56,  94, 255, 197,  62,
183, 127, 245,  26, 161, 116, 168, 226,  95, 222,  69, 166, 194, 247,  70, 115;
155, 215,  44, 190,  29, 151, 156, 189, 150,  92, 212, 247, 225, 108, 186, 193,
221,   3, 157, 229, 254, 201, 127, 157, 234,  99, 255, 145,  62, 140, 184,  95;
108,  60, 241,  82, 227, 120,  87, 146, 123, 234,  61,  56,  94, 247, 197,  62,
151, 126, 245,  26, 177, 116, 168, 226,  79, 222,  69, 166, 194, 247,  70, 119;
155, 147,  44, 190, 157, 151, 156, 189, 150,  92, 212, 231, 225, 108, 186, 193,
221,  67, 157, 229, 254, 201, 127, 189, 234,  99, 255, 129,  31, 140, 184,  95;
187, 147,  44, 190, 157, 151, 156, 189, 150,  93, 212, 247, 225, 108, 186, 193,
221,   3, 157, 229, 255, 201, 127, 189, 234,  99, 255, 209,  31, 140, 184,  95;
108,  60, 241,  82, 227, 120, 119, 146, 123, 234,  61,  56,  94, 247, 205,  62,
183, 127, 245,  26, 177, 116, 168, 226, 107, 222,  69, 174, 226, 247,  70, 115;
108,  60, 241,  82, 227, 120,  87, 146, 123, 234,  61,  56,  94, 247, 205,  62,
151, 127, 245,  26, 161, 116, 168, 226,  79, 222,  69, 166, 194, 247,  70, 119;
155, 215,  46, 190, 157, 151, 156, 189, 150,  92, 212, 199, 225, 108, 186, 193,
221,  99, 157, 229, 254, 201, 127, 189, 234,  99, 255, 145,  31,  12, 184,  95;
155, 147,  44, 190, 157, 151, 156, 189, 150,  92, 212, 231, 225, 108, 186, 193,
221,  35, 157, 229, 254, 201, 127, 157, 234,  99, 255, 145,  30, 140, 184,  95;
108,  60, 241,  82, 227, 120,  87, 146, 123, 235,  61,  56,  94, 247, 205,  62,
183, 127, 245,  26, 161, 116, 168, 226, 123, 222,  69, 174, 226, 247,  70, 115;
108,  60, 241,  82, 227, 120, 119, 146, 123, 234,  61,  56,  94, 247, 205,  62,
183, 127, 245,  26, 177, 116, 168, 226,  79, 222,  69, 166, 226, 247,  70, 115;
187, 151,  44, 190, 156, 151, 156, 189, 150,  92, 212, 231, 225, 108, 186, 193,
221,  35, 157, 229, 255, 201, 127, 189, 234,  99, 255, 209,  30, 140, 184,  95;
155, 147,  44, 190, 156, 151, 156, 189, 150,  93, 212, 247, 225, 108, 186, 193,
221,  35, 157, 229, 254, 201, 127, 189, 234,  99, 255, 193,  29, 140, 185,  95;
108,  60, 241,  82, 227, 120,  87, 146, 123, 234,  61,  56,  94, 247, 205,  62,
183, 127, 245,  26, 161, 116, 168, 226,  79, 222,  69, 166, 194, 247,  70, 115;
110,  44, 243,  84, 243, 248, 127, 130, 123, 162, 120, 232,  76, 255, 197, 188,
183, 127, 149,  18, 129, 240, 172, 234,  31, 222,   5, 162, 231, 247,  71, 165;
110,  44, 243,  84, 243, 248, 127, 130, 123, 170,  56, 232,  76, 255, 197, 188,
183, 255, 149,  18, 129, 240, 168, 234,  31, 222,   5, 162, 231, 247,  71, 165;
187, 147,  44, 189,  44,  23, 220, 189, 150,  92, 149, 149, 243, 108,  58,  67,
213,   1, 189, 173, 254,  77, 123, 157, 203, 123, 253, 213,  26, 140, 152,  91;
187, 147,  44, 189,  44,  23, 220,  61, 150,  92, 149, 149, 243, 108,  58,  67,
213,   1, 189, 165, 254,  77, 123, 157, 235, 123, 253, 213,  30, 140, 152,  91;
110,  44, 243,  84, 243, 250,  63, 130, 123, 163, 120, 168,  76, 255, 197, 188,
183, 127, 149,  18, 129, 240, 172, 234,  31, 222,   5, 162, 231, 247,  71, 165;
110,  44, 243,  84, 243, 248,  63, 130, 123, 170,  56, 168,  76, 255, 197, 188,
183, 127, 149,  18, 129, 240, 168, 234,  31, 222,   5, 162, 231, 247,  71, 165;
185, 147,  44, 189,  44,  23, 220, 189, 150,  92, 149, 213, 243, 108, 186,  67,
213,   1, 189, 165, 254,  77, 123, 157, 235, 107, 249, 213,  26, 140, 152,  91;
185, 147,  44, 189,  44,  23,  92,  61, 150,  92, 149, 213, 243, 108,  58,  67,
213,   1, 189, 165, 254,  77, 127, 157, 235, 123, 253, 157,  30, 140, 152,  91;
185, 147,  44, 189,  44,  23,  92,  61, 150,  92, 149, 213, 243, 108,  58,  67,
213,   1, 189, 165, 254,  77, 127, 157, 235, 123, 253, 157,  30, 140, 152,  91;
185, 147,  44, 189,  44,  23, 220, 189, 150,  92, 149, 213, 243, 108, 186,  67,
213,   1, 189, 165, 254,  77, 123, 157, 235, 107, 249, 213,  26, 140, 152,  91;
110,  44, 243,  84, 243, 248,  63, 130, 123, 170,  56, 168,  76, 255, 197, 188,
183, 127, 149,  18, 129, 240, 168, 234,  31, 222,   5, 162, 231, 247,  71, 165;
110,  44, 243,  84, 243, 250,  63, 130, 123, 163, 120, 168,  76, 255, 197, 188,
183, 127, 149,  18, 129, 240, 172, 234,  31, 222,   5, 162, 231, 247,  71, 165;
187, 147,  44, 189,  44,  23, 220,  61, 150,  92, 149, 149, 243, 108,  58,  67,
213,   1, 189, 165, 254,  77, 123, 157, 235, 123, 253, 213,  30, 140, 152,  91;
187, 147,  44, 189,  44,  23, 220, 189, 150,  92, 149, 149, 243, 108,  58,  67,
213,   1, 189, 173, 254,  77, 123, 157, 203, 123, 253, 213,  26, 140, 152,  91;
110,  44, 243,  84, 243, 248, 127, 130, 123, 170,  56, 232,  76, 255, 197, 188,
183, 255, 149,  18, 129, 240, 168, 234,  31, 222,   5, 162, 231, 247,  71, 165;
110,  44, 243,  84, 243, 248, 127, 130, 123, 162, 120, 232,  76, 255, 197, 188,
183, 127, 149,  18, 129, 240, 172, 234,  31, 222,   5, 162, 231, 247,  71, 165;
54,  42, 243,  84, 114, 242, 186,  66, 251, 128, 120, 232,  41, 254, 229, 188,
182, 125, 149,  80, 130, 248, 164, 200,  10, 220,   1, 163, 199, 229, 103, 173;
227, 192,  44, 189,  44,   7,  88,  57, 151,  54,   7,  29, 247, 121,  58,  67,
213,   5,  61,  45, 254,  68,  91, 149, 203, 251, 217, 212,  28, 172, 152,  66;
227, 192,  44, 189,  44,   7,  88,  57, 151,  54,   7,  29, 247, 121,  58,  67,
213,   5,  61,  45, 254,  68,  91, 149, 203, 251, 217, 212,  28, 172, 152,  66;
54,  42, 243,  84, 114, 242, 186,  66, 251, 128, 120, 232,  41, 254, 229, 188,
182, 125, 149,  80, 130, 248, 164, 200,  10, 220,   1, 163, 199, 229, 103, 173]
}*/
}  // namespace utils
}  // namespace Pipeline_keypoints_processor
#endif