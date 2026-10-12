#include "nitro/types.h"

typedef struct BgControlHandlers {
    void (*setExtended)(int size, int colorMode, int screenBase, int charBase, int extPal);
    void (*setBasic)(int size, int colorMode, int screenBase, int charBase);
} BgControlHandlers;

extern void SetMainBg0Control(int size, int colorMode, int screenBase, int charBase, int extPal);

/* The remaining four transfer callbacks follow this pair in the ROM. */
const BgControlHandlers gBg0ControlHandlers = {
    SetMainBg0Control,
    NULL
};
