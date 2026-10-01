#include "nitro/types.h"

typedef struct NoticeScreen {
    u8 pad_000[0x1C];
    u8 records[0x3F0];
    u64 shownTick;
    u8 pad_414[0x44];
    void *tilemap;
} NoticeScreen;

extern u64 OS_GetTick_02003fd4(void);
extern void *FindActiveRecordById_020b8184(void *records, int id);
extern void InvokeCallback40_020b8268(void *records, void *record);
extern void func_ov027_020b9d54(NoticeScreen *screen, int layer, int x, int y, int width, int height);
extern void ClearTilemapRegion_0206ea94(void *dest, int column, int row, int width, int height);

void ExpireNoticeWindow_0207023c(NoticeScreen *screen)
{
    u64 now = OS_GetTick_02003fd4();

    if (screen->shownTick != 0 && now >= screen->shownTick + 0x17F898) {
        if (screen->tilemap == NULL) {
            InvokeCallback40_020b8268(screen->records, FindActiveRecordById_020b8184(screen->records, 0x34));
            func_ov027_020b9d54(screen, 11, 1, 7, 8, 1);
        } else {
            ClearTilemapRegion_0206ea94(screen->tilemap, 0, 5, 13, 4);
        }
        screen->shownTick = 0;
    }
}
