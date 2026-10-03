#include "nitro/types.h"

typedef struct BgGraphicsData {
    void *screen;
    void *character;
    void *palette;
} BgGraphicsData;

typedef struct OverlayWork {
    u32 unk_00;
    u32 messageHandle;
    void *archive;
    BgGraphicsData background;
} OverlayWork;

#define REG_DISPCNT (*(vu32 *)0x04000000)

extern OverlayWork *data_ov036_020c3844;
extern const char data_ov036_020c38c4[];
extern u32 Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void *func_0202c478(u32 fileId, u32 mode);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);

void LoadTextWindowBackground_020bea80(void)
{
    data_ov036_020c3844->messageHandle = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov036_020c38c4, 0xe, FALSE);
    data_ov036_020c3844->archive =
        func_0202c478((((data_ov036_020c3844->messageHandle + 0x8000) & 0xfffffc) << 7) | 0x80000000, 0xe);
    GetBgDataFromArchive_0202b554(&data_ov036_020c3844->background, data_ov036_020c3844->archive, 0, 0, 0);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1f00;
}
