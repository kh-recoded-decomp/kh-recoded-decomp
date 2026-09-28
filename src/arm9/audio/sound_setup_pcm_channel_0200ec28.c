extern void PushCommand_impl(int commandId, int packedWord0, int packedWord1, int packedWord2, int packedWord3);

void sound_setup_pcm_channel_0200ec28(int nChannel, int nFormat, const void *pData,
                          int nLoop, int nLoopStart, int nLoopLength,
                          int nVolume, int nShift, int nTimer, int nPan)
{
    int startFormatLoopPan = nLoopStart | (((nLoop << 26) | (nFormat << 24)) | (nPan << 16));
    int lengthVolumeShift = nLoopLength | ((nVolume << 24) | (nShift << 22));
    int channelTimer = nChannel | (nTimer << 16);
    PushCommand_impl(0xe, channelTimer, (int)pData, lengthVolumeShift, startFormatLoopPan);
}
