#include "nitro/types.h"

extern void LoadPanelPaletteBase_02074240(void);
extern void ScrollPanelSlotsDown_0207436c(void);
extern void ScrollPanelSlotsUp_020742a4(void);
extern void func_ov013_02074238(void);
extern void func_ov013_0207423c(void);
extern void func_ov013_02074348(void);
extern void func_ov013_0207434c(void);
extern void func_ov013_0207441c(void);

void (*data_ov013_02074b3c[7])(void) = {
    func_ov013_0207423c,
    LoadPanelPaletteBase_02074240,
    ScrollPanelSlotsUp_020742a4,
    func_ov013_02074348,
    func_ov013_0207434c,
    ScrollPanelSlotsDown_0207436c,
    func_ov013_0207441c,
};

void (*data_ov013_02074b38[1])(void) = {
    func_ov013_02074238,
};
