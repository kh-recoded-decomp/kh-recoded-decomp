#include "nitro/types.h"

typedef struct {
    s32 status : 8;
    u32 statusHigh : 24;
    u8 pad_04[0x382c];
} SaveSlot;

typedef struct {
    u8 pad_00[0x28c4];
    u32 saveStamp;
} SaveFields;

typedef struct {
    u8 bytes[0x20];
} FadeRecord;

typedef struct {
    u8 slotIndex;
    u8 pad_01;
    u8 needsRedraw;
    u8 pad_03;
    s32 step : 8;
    u32 stepHigh : 24;
    u8 promptOpen;
    u8 pad_09[2];
    u8 overwriting;
    u8 pad_0C[4];
    int saving;
    int returnMode;
    int busy;
    int unk_1C;
    u32 latestStamp;
    u8 pad_24[0x10];
    FadeRecord fade;
    void *panel;
    u8 pad_58[0x20];
    SaveSlot slots[2];
} SaveSelectScreen;

extern SaveFields *data_0205fe0c;
extern int func_ov039_020bc914(void);
extern void func_ov039_020bbf78(int a, int b, int c);
extern void DecrementBusyCounterIfPositive_02025494(void);
extern void IncrementBusyCounter_020254a8(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern u32 func_0202a9d0(u32 range);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void func_02052514(FadeRecord *record, int value0, int value1, int value2, int value3);
extern void func_0205255c(FadeRecord *record);
extern void *FindWidgetById_020b90a4(void *root, int id);
extern void SetEntrySlotsVisible_020b9580(void *panel, void *element, BOOL visible);
extern void SetPrimaryElementEnabled_020bc054(BOOL enabled);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern BOOL PrepareAndStartStream_0204dd4c(int streamIndex, int streamId);
extern void StopSoundStreamAtIndex_0204deb0(int handleIndex, int fadeFrame);

void ConfirmSaveSelectStep_020c5a0c(SaveSelectScreen *screen)
{
    switch (screen->step) {
    case 0:
        if (func_ov039_020bc914() != 3) {
            screen->step = 1;
            screen->promptOpen = 1;
            PlaySoundEffect_0204d924(0, 1);
        } else {
            switch (screen->slots[screen->slotIndex].status) {
            case 0:
                PlaySoundEffect_0204d924(0, 4);
                break;
            case 1:
                screen->step = 1;
                screen->overwriting = 1;
                screen->promptOpen = 1;
                PlaySoundEffect_0204d924(0, 1);
                break;
            default:
                screen->step = 1;
                screen->promptOpen = 1;
                PlaySoundEffect_0204d924(0, 1);
                break;
            }
        }
        break;
    case 1:
        if (screen->promptOpen == 0) {
            if (screen->overwriting != 0) {
                screen->step = 5;
                screen->saving = 1;
                func_02052514(&screen->fade, 0, 0, 0x1000, 2000);
                func_0205255c(&screen->fade);
            } else if (func_ov039_020bc914() != 3) {
                screen->step = 3;
                screen->latestStamp = (screen->latestStamp & 0xf0000000) | ((screen->latestStamp + 1) & 0x0fffffff);
                data_0205fe0c->saveStamp = ((screen->slotIndex << 28) & 0x30000000) | (screen->latestStamp & 0x0fffffff) | ((func_0202a9d0(4) << 30) & 0xc0000000);
                screen->saving = 1;
                if (screen->returnMode != 0) {
                    SetGlobalPackedBit_02027320(0xbea);
                }
            } else {
                screen->step = 7;
                func_02052514(&screen->fade, 0, 0, 0x10, 0x42a);
                func_0205255c(&screen->fade);
            }
            if (screen->step != 7) {
                SetSecondaryElementEnabled_020bc084(FALSE);
                SetEntrySlotsVisible_020b9580(screen->panel, FindWidgetById_020b90a4(screen->panel, 8), TRUE);
                PlaySoundEffect_0204d924(0, 1);
                IncrementBusyCounter_020254a8();
            } else {
                SetPrimaryElementEnabled_020bc054(FALSE);
                SetSecondaryElementEnabled_020bc084(FALSE);
                PrepareAndStartStream_0204dd4c(1, 3);
                StopSoundStreamAtIndex_0204deb0(0, 0x1e);
            }
        } else {
            screen->step = 0;
            screen->overwriting = 0;
            PlaySoundEffect_0204d924(0, 1);
        }
        break;
    case 2:
        if (screen->promptOpen == 0) {
            func_ov039_020bbf78(-1, -1, 1);
        } else {
            screen->step = 0;
            screen->overwriting = 0;
        }
        PlaySoundEffect_0204d924(0, 1);
        break;
    case 4:
    case 6:
        if (screen->busy != 0) {
            screen->busy = 0;
            DecrementBusyCounterIfPositive_02025494();
        }
        if (screen->returnMode != 0) {
            func_ov039_020bbf78(-1, -1, 1);
        } else {
            screen->step = 0;
            screen->overwriting = 0;
        }
        PlaySoundEffect_0204d924(0, 1);
        break;
    }
    screen->needsRedraw = 1;
}
