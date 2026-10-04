#include "nitro/types.h"

typedef struct {
    int values[3];
} IdTriple;

typedef struct {
    u8 pad_000[0xb64];
    u8 labelTable[0x54];
    int variant;
} PanelScene;

extern const IdTriple data_ov087_020c7c88;
extern const IdTriple data_ov087_020c7cac;
extern void *func_ov027_020ba2a8(void *table, int index);
extern void func_ov087_020c4860(PanelScene *scene, const u16 *text);
extern void func_ov001_020645dc(int flagId);

void ShowVariantMessageAndSetFlag_020c4990(PanelScene *scene)
{
    IdTriple messageIds = data_ov087_020c7c88;
    IdTriple flagIds = data_ov087_020c7cac;

    func_ov087_020c4860(scene, func_ov027_020ba2a8(scene->labelTable, messageIds.values[scene->variant]));
    func_ov001_020645dc(flagIds.values[scene->variant] + 0xf50);
}
