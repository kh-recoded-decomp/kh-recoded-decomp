extern unsigned int func_020a9380(int chan);
extern void func_020a9398(int chan, int buf);
extern void DC_StoreRange(void *addr, unsigned int len);

void flushPendingStereoAudioBlocks_020a809c(int *audioRing) {
    int blockIndex;
    unsigned long long pendingBlockCount;

    pendingBlockCount = func_020a9380(audioRing[0]);
    for (blockIndex = 0; blockIndex < pendingBlockCount; blockIndex++) {
        func_020a9398(audioRing[0], audioRing[1] + (audioRing[7] << 1));
        func_020a9398(audioRing[0], audioRing[2] + (audioRing[7] << 1));
        DC_StoreRange((void *)(audioRing[1] + (audioRing[7] << 1)), audioRing[6] << 1);
        DC_StoreRange((void *)(audioRing[2] + (audioRing[7] << 1)), audioRing[6] << 1);
        audioRing[7] = audioRing[7] + audioRing[6];
        if (audioRing[7] == audioRing[8] * audioRing[6]) {
            audioRing[7] = 0;
        }
    }
}
