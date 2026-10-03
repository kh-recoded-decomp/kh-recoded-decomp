#include "nitro/types.h"

typedef struct Ov037Context {
    u16 selected;
    u16 entryCount;
    s32 baseY;
    u8 list[0x68];
} Ov037Context;

extern Ov037Context *g_ov037Context_020bb764;
extern void *FindLoadedElementById_020b8390(void *list, u32 id);
extern void PositionListRecords_020b8498(void *list, void *element, s16 position);
extern void SetTagRecordArmed_020b83e8(void *list, void *element, BOOL arm);
extern void *FindActiveRecordById_020b8184(void *list, u32 id);
extern void func_ov027_020b822c(void *list, void *record, int mode, s16 position);

void RefreshMenuListLayout_020bad64(void)
{
    void *list;
    int index;
    Ov037Context *ctx;

    ctx = g_ov037Context_020bb764;
    list = ctx->list;

    for (index = 0; index < ctx->entryCount; index++) {
        if (index == ctx->selected) {
            PositionListRecords_020b8498(list, FindLoadedElementById_020b8390(list, 0), (s16)(ctx->baseY + index * 2));
            SetTagRecordArmed_020b83e8(list, FindLoadedElementById_020b8390(list, 0), TRUE);
        } else {
            func_ov027_020b822c(list, FindActiveRecordById_020b8184(list, 0), 8, (s16)(ctx->baseY + index * 2));
        }
        ctx = g_ov037Context_020bb764;
    }
}
