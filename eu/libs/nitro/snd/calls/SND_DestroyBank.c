#include "nitro/types.h"

#define SND_BANK_TO_WAVEARC_MAX 4

typedef struct SNDBinaryFileHeader {
    char signature[4];
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} SNDBinaryFileHeader;

typedef struct SNDBinaryBlockHeader {
    u32 kind;
    u32 size;
} SNDBinaryBlockHeader;

typedef struct SNDWaveArcLink {
    struct SNDWaveArc *waveArc;
    struct SNDWaveArcLink *next;
} SNDWaveArcLink;

typedef struct SNDWaveArc {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    SNDWaveArcLink *topLink;
    u32 reserved[7];
    u32 waveCount;
} SNDWaveArc;

typedef struct SNDBankData {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    SNDWaveArcLink waveArcLink[SND_BANK_TO_WAVEARC_MAX];
    u32 instCount;
} SNDBankData;

extern void func_0200eddc(void);
extern void SNDi_UnlockMutex(void);
extern void DC_StoreRange(const void *addr, u32 size);

void SND_DestroyBank(SNDBankData *bank)
{
    SNDWaveArc *waveArc;
    int i;

    func_0200eddc();

    for (i = 0; i < SND_BANK_TO_WAVEARC_MAX; i++) {
        waveArc = bank->waveArcLink[i].waveArc;

        if (waveArc == NULL) {
            continue;
        }

        if (&bank->waveArcLink[i] == waveArc->topLink) {
            waveArc->topLink = bank->waveArcLink[i].next;
            DC_StoreRange(waveArc, sizeof(SNDWaveArc));
        } else {
            SNDWaveArcLink *prev;
            for (prev = waveArc->topLink; prev != NULL; prev = prev->next) {
                if (&bank->waveArcLink[i] == prev->next) {
                    break;
                }
            }
            prev->next = bank->waveArcLink[i].next;
            DC_StoreRange(prev, sizeof(SNDWaveArcLink));
        }
    }

    SNDi_UnlockMutex();
}
