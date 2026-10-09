#include "nitro/types.h"

extern unsigned int gMovieContextState;
extern unsigned int DrawVisibleSceneSlots(void);
extern unsigned int RunFlaggedEventCallbacks(void);
extern unsigned int func_ov001_020876d4(void);
extern unsigned int UpdateActorSlotsAndBillboards(void);
extern unsigned int func_020bd2a4(void);
extern unsigned int func_ov001_0206dc38(void);
extern unsigned int func_ov021_020af528(int);
extern unsigned int func_ov035_020bae94(void);
extern unsigned int DrawMovieSceneIfVisible(void);
extern unsigned int func_ov040_020bdb70(void);

void DispatchSceneDrawCallbacks(void)
{
    int work;
    u32 active;
    int blocked;

    work = gMovieContextState;
    if ((*(u16 *)(gMovieContextState + 0x24) & 0x80) != 0) {
        func_ov021_020af528(1);
    }
    if ((*(u16 *)(work + 0x22) & 1) != 0) {
        DrawVisibleSceneSlots();
    }
    if ((*(u16 *)(work + 0x22) & 4) != 0) {
        DrawMovieSceneIfVisible();
    }
    active = func_ov001_0206dc38();
    if (((0 < (int)active) &&
         (blocked = func_ov035_020bae94(), blocked == 0)) &&
        ((*(u16 *)(work + 0x22) & 8) != 0)) {
        RunFlaggedEventCallbacks();
    }
    if ((*(u16 *)(work + 0x22) & 0x40) != 0) {
        UpdateActorSlotsAndBillboards();
    }
    if ((*(u16 *)(work + 0x22) & 0x10) != 0) {
        func_ov001_020876d4();
    }
    blocked = func_ov035_020bae94();
    if (blocked != 0) {
        func_020bd2a4();
    }
    if ((*(u16 *)(work + 0x22) & 0x100) != 0) {
        func_ov040_020bdb70();
    }
}
