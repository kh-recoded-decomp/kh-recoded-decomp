#include "nitro/types.h"

#define REG_DB_DISPCNT (*(vu32 *)0x04001000)
#define REG_DB_BG0CNT (*(vu16 *)0x04001008)
#define REG_DB_BG1CNT (*(vu16 *)0x0400100a)
#define REG_DB_BG2CNT (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT (*(vu16 *)0x0400100e)
#define REG_DB_BG2PA (*(vu32 *)0x04001018)
#define REG_DB_BG2PC (*(vu32 *)0x0400101c)

typedef struct StatusScreen {
    u8 pad00[0x28];
    u32 areaId;
    u8 pad2c[0xdc0 - 0x2c];
    u8 layerA[0x34];
    u8 layerB[0x34];
    u8 layerC[0x34];
    u8 pade5c[0x10e0 - 0xe5c];
    void *sprites;
} StatusScreen;

extern void *func_ov039_020bc1cc(void);
extern void *FindWidgetById_020b90a4(void *root, int id);
extern void SetEntrySlotsVisible_020b9580(void *menu, void *widget, int visible);
extern void AlarmCallback_0204f12c(void *sprites);
extern void ReleaseStatusPage_020bece0(StatusScreen *screen, void *page);
extern void *G2S_GetBG1ScrPtr_02006e68(void);
extern void *G2S_GetBG2ScrPtr_02006f0c(void);
extern void *G2S_GetBG3ScrPtr_02007004(void);
extern void func_01ff8740(int value, void *dst, int size);
extern void StartCurrentAreaEvents_020bc55c(int a, int b, int c, u16 area);
extern void FlushBufferAndRunCallback_0200153c(void *layer);
extern u16 *UpdateScreenWidgetLayer_020bc1e4(int layer);
extern void FillBackgroundLayerRect_02001a60(void *layer, u16 *dst, int x, int y, u8 palette);
extern void SetScreenLayerDirty_020bc104(int layer);

void CloseStatusScreen_020c1864(StatusScreen *screen, void *page)
{
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1000;
    SetEntrySlotsVisible_020b9580(func_ov039_020bc1cc(), FindWidgetById_020b90a4(func_ov039_020bc1cc(), 0xe), 0);
    SetEntrySlotsVisible_020b9580(func_ov039_020bc1cc(), FindWidgetById_020b90a4(func_ov039_020bc1cc(), 0x3b), 0);
    AlarmCallback_0204f12c(screen->sprites);
    ReleaseStatusPage_020bece0(screen, page);
    REG_DB_BG0CNT = (REG_DB_BG0CNT & 0x43) | 0x0c00;
    REG_DB_BG1CNT = (REG_DB_BG1CNT & 0x43) | 0x0d00;
    REG_DB_BG2CNT = (REG_DB_BG2CNT & 0x43) | 0x0e00;
    REG_DB_BG3CNT = (REG_DB_BG3CNT & 0x43) | 0x0f00;
    REG_DB_BG0CNT = REG_DB_BG0CNT & ~3;
    REG_DB_BG1CNT = (REG_DB_BG1CNT & ~3) | 1;
    REG_DB_BG2CNT = (REG_DB_BG2CNT & ~3) | 2;
    REG_DB_BG3CNT = (REG_DB_BG3CNT & ~3) | 3;
    func_01ff8740(0, G2S_GetBG1ScrPtr_02006e68(), 0x800);
    func_01ff8740(0, G2S_GetBG2ScrPtr_02006f0c(), 0x800);
    func_01ff8740(0, G2S_GetBG3ScrPtr_02007004(), 0x800);
    StartCurrentAreaEvents_020bc55c(0, 3, 0, screen->areaId);
    FlushBufferAndRunCallback_0200153c(screen->layerA);
    FlushBufferAndRunCallback_0200153c(screen->layerB);
    FlushBufferAndRunCallback_0200153c(screen->layerC);
    FillBackgroundLayerRect_02001a60(screen->layerA, UpdateScreenWidgetLayer_020bc1e4(0x19), 3, 0, 0xf);
    FillBackgroundLayerRect_02001a60(screen->layerB, UpdateScreenWidgetLayer_020bc1e4(0x19), 3, 3, 0xf);
    FillBackgroundLayerRect_02001a60(screen->layerC, UpdateScreenWidgetLayer_020bc1e4(0x19), 0, 0x13, 0xf);
    SetScreenLayerDirty_020bc104(0x19);
    REG_DB_BG2PA = 0;
    REG_DB_BG2PC = 0;
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1e00;
}
