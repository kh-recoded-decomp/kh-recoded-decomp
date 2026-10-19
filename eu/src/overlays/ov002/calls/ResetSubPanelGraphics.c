#pragma opt_propagation off
#pragma opt_common_subs off
#include "src/overlays/ov002/Ov002PanelState.h"

extern void *G2S_GetBG0ScrPtr(void);
extern void *G2S_GetBG1ScrPtr(void);
extern void *G2S_GetBG2ScrPtr(void);
extern void *G2S_GetBG3ScrPtr(void);
extern void *G2S_GetBG0CharPtr(void);
extern void *G2S_GetBG1CharPtr(void);
extern void *G2S_GetBG2CharPtr(void);
extern void *G2S_GetBG3CharPtr(void);
extern void MIi_CpuClearFast(u32 value, void *destination, u32 byteCount);
extern void CreatePanelTextLayer6(NNSG2dFont *font);
extern void CreatePanelTextLayer(NNSG2dFont *font);

static inline void SetBg0Priority(u32 priority)
{
    volatile u16 *control = (volatile u16 *)0x04001008;
    u32 value = *control;
    value &= ~3;
    value |= priority;
    *control = value;
}

static inline void SetBg1Priority(u32 priority)
{
    volatile u16 *control = (volatile u16 *)0x0400100a;
    u32 value = *control;
    value &= ~3;
    value |= priority;
    *control = value;
}

static inline void SetBg2Priority(u32 priority)
{
    volatile u16 *control = (volatile u16 *)0x0400100c;
    u32 value = *control;
    value &= ~3;
    value |= priority;
    *control = value;
}

static inline void SetBg3Priority(u32 priority)
{
    volatile u16 *control = (volatile u16 *)0x0400100e;
    u32 value = *control;
    value &= ~3;
    value |= priority;
    *control = value;
}

void ResetSubPanelGraphics(void)
{
    MIi_CpuClearFast(0, G2S_GetBG0ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG3ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG0CharPtr(), 0x40);
    MIi_CpuClearFast(0, G2S_GetBG1CharPtr(), 0x40);
    MIi_CpuClearFast(0, G2S_GetBG2CharPtr(), 0x40);
    MIi_CpuClearFast(0, G2S_GetBG3CharPtr(), 0x40);
    MIi_CpuClearFast(0xc0, (void *)0x07000400, 0x400);
    *(volatile u32 *)0x04001010 = 0;
    *(volatile u32 *)0x04001014 = 0;
    *(volatile u32 *)0x04001018 = 0;
    *(volatile u32 *)0x0400101c = 0;
    SetBg0Priority(1);
    SetBg1Priority(3);
    SetBg2Priority(2);
    SetBg3Priority(0);
    CreatePanelTextLayer6(&gOv002PanelState->fonts[0].font);
    CreatePanelTextLayer(&gOv002PanelState->fonts[0].font);
    *(volatile u32 *)0x04001000 &= ~0xe000;
}
