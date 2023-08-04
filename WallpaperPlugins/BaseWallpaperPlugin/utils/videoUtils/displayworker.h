#ifndef DISPLAYWORKER_H
#define DISPLAYWORKER_H

#include <QImage>
#include "../threadbase.h"
#include "AvFrameQueue.h"
#include "../AVConfig.h"
#include "../audioUtils/audioutils.h"
extern "C"{
#include "libavcodec/codec.h"
#include "libswresample/swresample.h"
#include "libswscale/swscale.h"
#include "libavutil/time.h"
}
class DisplayWorker :public ThreadBase
{
    Q_OBJECT
private:
    AVCodecContext* aduioCodecContext;
    AVCodecContext* videoCodecContext;
    AVFrameQueue*   videoFrames;
    AVFrameQueue*   audioFrames;
    SwrContext*     swrContext;
    SwsContext*     swsContext;
    AudioUtils*     audioUtils;
    struct Clock{
        double pts;           /* clock base 时间基准*/
        double pts_drift;     /* clock base minus time at which we updated the clock 时间基减去更新时钟的时间 */
        double last_updated;
    } clock;
protected:
    void run() override;


public:
    DisplayWorker();
    DisplayWorker(AVCodecContext* _audioCodecContext,AVCodecContext* _videoCodecContext,AVFrameQueue*  _videoFrames,AVFrameQueue*  _audioFrames,AudioUtils* audio);



    void setVideoFrames(AVFrameQueue *value);
    void setAudioFrames(AVFrameQueue *value);
    void setAudioUtils(AudioUtils *value);

    void setAduioCodecContext(AVCodecContext *value);

    void setVideoCodecContext(AVCodecContext *value);


};

#endif // DISPLAYWORKER_H
