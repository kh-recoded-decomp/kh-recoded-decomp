#include "nitro/types.h"

typedef struct MenuEntry {
    s32 id;
    s32 extra;
} MenuEntry;

typedef struct Ov037Context {
    u16 selected;
    u16 entryCount;
    s32 freeSlots;
    u8 list[0x4c];
    u8 tileTable[0x1c];
    u8 model[0x128];
    u8 camera[0x38];
    s32 enabled;
    MenuEntry entries[4];
    u8 text[0x34];
    u64 startTick;
    s32 textUploaded;
} Ov037Context;

extern Ov037Context *g_ov037Context_020bb764;
extern u16 data_02060500;
extern u64 OS_GetTick_02003fd4(void);
extern void Text_UploadTileBuffer_02001520(void *text);
extern void RefreshMenuListLayout_020bad64(void);
extern void PlaySoundEffect_0204d924(int player, int sound);
extern void func_ov027_020b7dd4(void *list);
extern void func_ov027_020b9e60(void *tileTable);
extern void camera_commit_projection_0202a814(void *camera);
extern void AdvanceAnimationTracks_0202ef24(void *model, int step);
extern void SceneNode_Draw_01ffb12c(void *model);

s32 UpdateMenuSelection_020bb4bc(void)
{
    s32 result = -1;
    Ov037Context *ctx = g_ov037Context_020bb764;

    if (ctx == NULL) {
        return result;
    }
    if (ctx->textUploaded == 0 && OS_GetTick_02003fd4() >= ctx->startTick + 0xffb10) {
        Text_UploadTileBuffer_02001520(ctx->text);
        g_ov037Context_020bb764->textUploaded = 1;
    }
    ctx = g_ov037Context_020bb764;
    if (ctx->enabled) {
        if (data_02060500 & 0x40) {
            ctx->selected = (ctx->selected + ctx->entryCount - 1) % ctx->entryCount;
            RefreshMenuListLayout_020bad64();
            if (g_ov037Context_020bb764->entryCount > 1) {
                PlaySoundEffect_0204d924(0, 0);
            }
        } else if (data_02060500 & 0x80) {
            ctx->selected = (ctx->selected + 1) % ctx->entryCount;
            RefreshMenuListLayout_020bad64();
            if (g_ov037Context_020bb764->entryCount > 1) {
                PlaySoundEffect_0204d924(0, 0);
            }
        } else if (data_02060500 & 1) {
            result = ctx->entries[ctx->selected].id;
            ctx->enabled = 0;
            PlaySoundEffect_0204d924(0, 1);
        }
    }
    func_ov027_020b7dd4(g_ov037Context_020bb764->list);
    func_ov027_020b9e60(g_ov037Context_020bb764->tileTable);
    camera_commit_projection_0202a814(g_ov037Context_020bb764->camera);
    AdvanceAnimationTracks_0202ef24(g_ov037Context_020bb764->model, 0x1000);
    SceneNode_Draw_01ffb12c(g_ov037Context_020bb764->model);
    return result;
}
