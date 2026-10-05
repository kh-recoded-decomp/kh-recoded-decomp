#include "nitro/types.h"

typedef struct SwapAnimator {
    u8 pad_00[0x20];
    u16 slotIds[2];
    u8 pad_24[2];
    u16 step : 14;
    u16 flags : 2;
    u8 pad_28[4];
    int side;
} SwapAnimator;

extern const int data_ov001_0209dfd8[];
extern const int data_ov001_0209dfe8[];

extern void *GetSceneTagTracker_020711b0(void);
extern int func_ov001_0207123c(void);
extern void func_ov027_020b9d54(int screen, int layer, int x, int y, int width, int height);
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void func_ov027_020b81e0(void *pool, void *record, s16 y);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);

void AnimateSwapSlotLabels_0207db50(SwapAnimator *anim)
{
    void *pool = GetSceneTagTracker_020711b0();
    int screen = func_ov001_0207123c();
    void *record;

    if (anim->step != 0 && anim->step <= 3) {
        func_ov027_020b9d54(screen, 0xb, 0xe, 0xf, 4, 7);
        if (anim->step < 3) {
            record = FindActiveRecordById_020b8184(pool, data_ov001_0209dfd8[anim->slotIds[anim->side]]);
            func_ov027_020b81e0(pool, record, 0x13 - anim->step);
        } else {
            record = FindActiveRecordById_020b8184(pool, data_ov001_0209dfe8[anim->slotIds[anim->side]]);
            func_ov027_020b81e0(pool, record, 0xf);
            TagTracker_InvokeCallback_020b8210(pool, record);
            record = FindActiveRecordById_020b8184(pool, data_ov001_0209dfd8[anim->slotIds[anim->side ^ 1]]);
            func_ov027_020b81e0(pool, record, 0x13);
        }
        TagTracker_InvokeCallback_020b8210(pool, record);
        anim->step++;
    }
}
