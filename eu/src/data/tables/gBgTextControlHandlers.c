#include "nitro/types.h"

extern void Bg_SetMainBg0Control(int value, int flag, int screenBase, int charBase);
extern void Bg_SetMainBg1Control(int value, int flag, int screenBase, int charBase);
extern void Bg_SetMainBg2TextControl(int value, int flag, int screenBase, int charBase);
extern void Bg_SetMainBg3TextControl(int value, int flag, int screenBase, int charBase);
extern void Bg_SetSubBg0Control(int value, int flag, int screenBase, int charBase);
extern void Bg_SetSubBg1Control(int value, int flag, int screenBase, int charBase);
extern void Bg_SetSubBg2TextControl(int value, int flag, int screenBase, int charBase);
extern void Bg_SetSubBg3TextControl(int value, int flag, int screenBase, int charBase);

void (*const gBgTextControlHandlers[8])(int, int, int, int) = {
    Bg_SetMainBg0Control,
    Bg_SetMainBg1Control,
    Bg_SetMainBg2TextControl,
    Bg_SetMainBg3TextControl,
    Bg_SetSubBg0Control,
    Bg_SetSubBg1Control,
    Bg_SetSubBg2TextControl,
    Bg_SetSubBg3TextControl
};
