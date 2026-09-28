#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x8fc];
    s32 unk_8FC;
} Ov089Menu;

extern void *func_ov039_020bc1bc(void);
extern void func_ov027_020b9360(void *panel, int elementId, fx32 *position, int mode);
extern void *func_ov027_020b90a4(void *panel, int elementId);
extern void func_ov027_020b91c8(void *panel, void *element, const fx32 *position, int mode);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void MoveCursorToElement_020bef34(Ov089Menu *menu, int elementId, BOOL playSound)
{
    void *panel = func_ov039_020bc1bc();
    fx32 position[2];
    fx32 offset;

    func_ov027_020b9360(panel, elementId, position, 0);
    offset = 0x30000;
    if (menu->unk_8FC == 0) {
        offset = 0x40000;
    }
    position[0] -= offset;
    func_ov027_020b91c8(panel, func_ov027_020b90a4(panel, 0), position, 0);
    if (playSound) {
        PlaySoundEffect_0204d924(0, 0);
    }
}
