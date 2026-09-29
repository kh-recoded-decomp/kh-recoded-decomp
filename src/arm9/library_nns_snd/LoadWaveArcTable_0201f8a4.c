#include "nitro/types.h"
#include "nnsys/snd.h"

typedef struct WaveArcHeader {
    u8 pad_00[0x38];
    u32 waveCount;
    u32 waveOffset[1];
} WaveArcHeader;

extern u8 g_waveArcHeaderBuffer_0205e2e8[0x3c];
extern WaveArcHeader g_waveArcHeader_0205e2e8;

extern void *NNS_SndArcGetFileAddress_0201ee28(u32 fileId);
extern s32 NNS_SndArcReadFile_0201ed3c(u32 fileId, void *buffer, s32 size, s32 offset);
extern void *NNS_SndArcGetCurrentSndArc_0201e9f0(void);
extern void *NNS_SndHeapAlloc_0201f0ec(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);
extern void WaveArcTableDisposeCallback_0201faac(void *mem, u32 size, u32 data1, u32 data2);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dest, u32 size);
extern void MI_CpuFill8_01ff8830(void *dest, u8 data, u32 size);
extern void DC_StoreRange_02003430(const void *startAddr, u32 nBytes);
extern void NNS_SndArcSetFileAddress_0201ee50(u32 fileId, void *address);

WaveArcHeader *LoadWaveArcTable_0201f8a4(u32 fileId, NNSSndHeapHandle heap, BOOL setAddr)
{
    u32 fileSize;
    WaveArcHeader *waveArc;
    u32 waveCount;
    u32 tableSize;
    s32 result;

    waveArc = NNS_SndArcGetFileAddress_0201ee28(fileId);
    if (waveArc == NULL) {
        if (NNS_SndArcReadFile_0201ed3c(fileId, g_waveArcHeaderBuffer_0205e2e8, 0x3c, 0) != 0x3c) {
            return NULL;
        }
        waveCount = g_waveArcHeader_0205e2e8.waveCount;
        tableSize = waveCount * sizeof(u32);
        fileSize = tableSize * 2;
        if (heap == NULL) {
            return NULL;
        }
        waveArc = NNS_SndHeapAlloc_0201f0ec(heap, fileSize + 0x5c, WaveArcTableDisposeCallback_0201faac,
                                            setAddr ? (u32)NNS_SndArcGetCurrentSndArc_0201e9f0() : 0, fileId);
        if (waveArc == NULL) {
            return NULL;
        }
        result = NNS_SndArcReadFile_0201ed3c(fileId, waveArc, (s32)(tableSize + 0x3c), 0);
        if (result != tableSize + 0x3c) {
            return NULL;
        }
        MI_CpuCopy8_01ff89a8(waveArc->waveOffset, &waveArc->waveOffset[waveArc->waveCount], tableSize);
        MI_CpuFill8_01ff8830(waveArc->waveOffset, 0, tableSize);
        DC_StoreRange_02003430(waveArc, fileSize + 0x3c);
        if (setAddr) {
            NNS_SndArcSetFileAddress_0201ee50(fileId, waveArc);
        }
    }
    return waveArc;
}
