#include "nitro/types.h"

typedef void (*InitFunc)(void);

typedef struct {
    u32 id;
    u8 *ramAddress;
    u32 ramSize;
    u32 bssSize;
    InitFunc *sinitInit;
    InitFunc *sinitInitEnd;
    u32 fileId;
    u32 flagsWord;
} OverlayInfo;

extern int FSi_GetOverlayBinarySize_0200b7cc(void *p);
extern u16 GetU16Field_020049f0(void);
extern BOOL CompareGeneratedBlock_0200bab4(int *expected, void *param2, void *param3, int useCallback);
extern void func_01ff8830(void *dst, int value, int size);
extern void RunResetCallbackAndIdle_02004cf0(void);
extern void func_02000950(void *bottom);
extern void func_0200344c(void *addr, u32 size);

extern u8 data_020561ac[];
extern u8 dataEnd_020561ac[];

void StartOverlay_0200bb74(OverlayInfo *overlay) {
    u32 rareSize = FSi_GetOverlayBinarySize_0200b7cc(overlay);

    if (GetU16Field_020049f0() != 1) {
        BOOL matched = FALSE;

        if ((overlay->flagsWord >> 0x18) & 2) {
            u32 odtMax = (dataEnd_020561ac - data_020561ac) / 20;
            if (overlay->id < odtMax) {
                u8 *specDigest = data_020561ac + 20 * overlay->id;
                matched = CompareGeneratedBlock_0200bab4((int *)specDigest, overlay->ramAddress, (void *)rareSize, 0);
            }
        }
        if (!matched) {
            func_01ff8830(overlay->ramAddress, 0, rareSize);
            RunResetCallbackAndIdle_02004cf0();
            return;
        }
    }

    if ((overlay->flagsWord >> 0x18) & 1) {
        func_02000950(overlay->ramAddress + rareSize);
    }
    func_0200344c(overlay->ramAddress, overlay->ramSize);

    {
        InitFunc *p = overlay->sinitInit;
        InitFunc *q = overlay->sinitInitEnd;
        for (; p < q; p++) {
            if (*p) {
                (*p)();
            }
        }
    }
}
