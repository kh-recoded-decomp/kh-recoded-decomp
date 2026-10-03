#include "nitro/types.h"

extern void *func_ov039_020bc1bc(void);
extern void func_ov027_020b91c8(void *scene, void *node, int *offset, int flags);

typedef struct {
    u8 pad0[0x24];
    void *cursorNode;
    u8 pad28[0x5d0 - 0x28];
    int cursor;
} MenuState;

void PlaceCursorNode_020c4748(MenuState *menu)
{
    int offset[2];

    offset[0] = (menu->cursor * 0x1c) << 12;
    offset[1] = 0;
    func_ov027_020b91c8(func_ov039_020bc1bc(), menu->cursorNode, offset, 3);
}
