#ifndef AVCONFIG_H
#define AVCONFIG_H
extern "C"{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswresample/swresample.h"
}
// ffmpeg 宏
#define SAMPLE_FMT AV_SAMPLE_FMT_S32
#define SAMPLE_SIZE 16 // audioUtils 使用的
#define SAMPLE_RATE 48000
#define AUDIO_CHANNEL 2
#define AUDIO_BUFF_SIZE 10000
#endif // AVCONFIG_H
