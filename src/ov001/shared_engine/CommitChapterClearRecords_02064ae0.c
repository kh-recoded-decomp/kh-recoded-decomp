#include "nitro/types.h"

extern s8 GetCtxModeByte_02068084(void);
extern u32 func_02027348(u32 bitOffset, u32 bitCount);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern u32 func_ov001_02064574(int flagIndex, u32 bitCount);
extern void func_ov001_0206459c(int flagIndex, u32 bitCount, u32 value);
extern BOOL func_ov001_020645c8(u32 flagIndex);
extern void func_ov001_020645dc(int flagIndex);
extern void func_ov001_020645e8(int flagIndex);

void CommitChapterClearRecords_02064ae0(void)
{
    int chapter;
    int clearCount;
    int bestCount;
    u32 clearTime;
    u32 bestTime;

    chapter = GetCtxModeByte_02068084();
    if (func_02027348(0x1a00, 2) == 0) {
        if (chapter == 7 && IsGlobalPackedBitSet_02027304(0xbea) != 0) {
            return;
        }
        func_ov001_020645dc(chapter + 0xa0b);
        func_ov001_0206459c(0xf38, 4, chapter + 1);
    }
    if (func_02027348(0x1a00, 2) != 3) {
        if (func_ov001_020645c8(0x35c9) != 0) {
            func_ov001_020645dc(chapter + 0xa23);
        }
        if (func_ov001_020645c8(0x35ca) != 0) {
            func_ov001_020645dc(chapter + 0xa63);
        }
        if (func_ov001_02064574(0x35c7, 2) == 1) {
            func_ov001_020645dc(chapter + 0x12b8);
        }
        if (func_ov001_02064574(0x35c7, 2) == 2) {
            func_ov001_020645dc(chapter + 0xa13);
        }
        if (func_ov001_02064574(0x35c7, 2) == 3) {
            func_ov001_020645dc(chapter + 0xa1b);
        }
        clearCount = func_ov001_02064574(0x35cb, 7);
        bestCount = func_ov001_02064574(chapter * 7 + 0xa2b, 7);
        if (bestCount == 0 || clearCount < bestCount) {
            if (clearCount > 99) {
                clearCount = 99;
            }
            func_ov001_0206459c(chapter * 7 + 0xa2b, 7, clearCount);
        }
        clearTime = func_ov001_02064574(0x35d2, 17);
        bestTime = func_ov001_02064574(chapter * 17 + 0xa6b, 17);
        if (bestTime == 0 || clearTime < bestTime) {
            if (clearTime > 99999) {
                clearTime = 99999;
            }
            func_ov001_0206459c(chapter * 17 + 0xa6b, 17, clearTime);
        }
    }
    if (chapter != 7 || func_02027348(0x1a00, 2) != 0) {
        func_ov001_020645e8(0x3536);
    }
}
