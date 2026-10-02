#include "nitro/types.h"

typedef struct GaugeAnim {
    u64 startTick;
    s32 rate;
    s32 elapsed;
    s32 active;
    s32 frame;
} GaugeAnim;

typedef struct GaugeSlot {
    u16 maximum;
    u16 current;
    u16 pad_04;
} GaugeSlot;

typedef struct GaugeScale {
    s32 scale;
    u8 pad_04[8];
} GaugeScale;

typedef struct GaugeMenu {
    void *contexts[10];
    s32 soundPlaying;
    u8 pad_2c[0x6c - 0x2c];
    GaugeAnim anims[3];
    GaugeSlot slots[10];
    u8 pad_f0[2];
    u16 primaryState;
} GaugeMenu;

extern GaugeMenu *data_ov001_020a04ac;
extern GaugeScale data_ov001_0209edd8[];
extern void func_ov001_020737fc(void *context, int index, int mode);
extern void func_ov001_02073870(void *context, int index, int mode);
extern u64 OS_GetTick_02003fd4(void);
extern void func_ov001_0207414c(int index, GaugeAnim *anim);
extern void RunMenuEntryCallbacks_020740d0(void *context, int menu, int count, void (*callback)(void *context, int index, int mode), int mode);
extern void func_ov001_02071770(int index, int mode);
extern BOOL IsFieldPanelHidden_0207187c(void);
extern BOOL IsFirstEntryFlagSet_0206e584(void);
extern u32 func_ov001_02064490(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void StopSeqArcOrDefault_0204d960(int seqArcNo, int index, int fade);

void SetMenuGaugeActive_0207512c(int index, BOOL enable) {
    GaugeMenu *menu = data_ov001_020a04ac;
    GaugeAnim *anim = &menu->anims[index];
    void (*callback)(void *context, int index, int mode);
    u16 state;
    u16 current;

    if (index == 0) {
        callback = func_ov001_020737fc;
        state = menu->primaryState;
        if (state == 0 && menu->slots[0].current != 0) {
            state = 1;
        }
    } else {
        callback = func_ov001_02073870;
        current = menu->slots[index].current;
        state = (current * data_ov001_0209edd8[index].scale) / menu->slots[index].maximum;
        if (state == 0 && current != 0) {
            state = 1;
        }
    }
    if (enable) {
        anim->active = 1;
        anim->frame = 0;
        anim->rate = 0x3fec4;
        anim->elapsed = 0;
        anim->startTick = OS_GetTick_02003fd4();
        func_ov001_0207414c(index, anim);
        func_ov001_02071770(index, 2);
    } else {
        anim->active = 0;
        RunMenuEntryCallbacks_020740d0(menu->contexts[index], index, state, callback, menu->slots[index].current == 0);
        func_ov001_02071770(index, 0);
    }
    if (index == 0) {
        if (enable) {
            if (menu->soundPlaying == 0 && IsFieldPanelHidden_0207187c() && !IsFirstEntryFlagSet_0206e584() && !func_ov001_02064490()) {
                PlaySoundEffect_0204d924(0, 0xe);
                menu->soundPlaying = 1;
            }
        } else if (menu->soundPlaying != 0) {
            StopSeqArcOrDefault_0204d960(0, 0xe, 0);
            menu->soundPlaying = 0;
        }
    }
}
