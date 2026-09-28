typedef unsigned int u32;

struct StereoPcmStream {
    int pad0000;
    short *leftSamples;
    short *rightSamples;
    int pad000c;
    int sampleRate;
    int pad0014;
    u32 samplesPerBlock;
    int pad001c;
    u32 blockCount;
};

extern int func_02023fc8(u32 nBase, int sampleRate);
extern void DC_StoreRange(void *pBlock, u32 nSize);
extern void SND_LockChannel(u32 nChannelMask, u32 nLockId);
extern void SND_SetupChannelPcm(int nChannel, int nFormat, const void *pData,
                                int nLoop, int nLoopStart, int nLoopLength,
                                int nVolume, int nShift, int timerPeriod, int nPan);
extern void SND_SetupAlarm(int nId, int nTick, int nPeriod, void *pfn, void *pArg);
extern void SND_StartTimer(u32 nChannelMask, u32 nCaptureMask,
                           u32 nAlarmMask, u32 nFlags);
extern void func_0200f080(int nChannel);
extern void func_020a7d94(void);

void startStereoPcmStream_020a7db4(struct StereoPcmStream *stream)
{
    int timerPeriod;

    timerPeriod = func_02023fc8(0x00ffb0ff, stream->sampleRate);
    DC_StoreRange(stream->leftSamples, (stream->blockCount * stream->samplesPerBlock) << 1);
    DC_StoreRange(stream->rightSamples, (stream->blockCount * stream->samplesPerBlock) << 1);
    SND_LockChannel(3, 0);
    SND_SetupChannelPcm(0, 1, stream->leftSamples, 1, 0,
                        (stream->blockCount * stream->samplesPerBlock) >> 1,
                        0, 0, timerPeriod, 0x20);
    SND_SetupChannelPcm(1, 1, stream->rightSamples, 1, 0,
                        (stream->blockCount * stream->samplesPerBlock) >> 1,
                        0, 0, timerPeriod, 0x5f);
    SND_SetupAlarm(0, timerPeriod * 0x64, 0, (void *)&func_020a7d94, 0);
    SND_StartTimer(3, 0, 1, 0);
    func_0200f080(1);
}
