#include "nitro/types.h"

typedef struct {
    u8 data[0x30];
} SpriteSlot;

typedef struct {
    u32 ids[7];
} SpriteFileIds;

typedef struct {
    u8 pad_000[0xfc];
    SpriteSlot *slots;
} SlotManager;

extern SlotManager *data_ov001_020a049c;
extern const SpriteFileIds data_ov001_0209db04;
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern u32 MakePrimaryVramKey_020711ec(u32 slot);
extern BOOL InitSlotFromFile_0206a8f0(SpriteSlot *slot, u32 fileId);

void LoadManagerSpriteSlots_0206dbb4(void)
{
    SlotManager *manager = data_ov001_020a049c;
    SpriteFileIds fileIds;
    int i;

    if (manager != NULL && manager->slots == NULL) {
        manager->slots = NNSi_FndAllocFromDefaultHeap_0202a178(7 * sizeof(SpriteSlot));
        fileIds = data_ov001_0209db04;
        for (i = 0; i < 7; i++) {
            InitSlotFromFile_0206a8f0(&manager->slots[i], MakePrimaryVramKey_020711ec(fileIds.ids[i]));
        }
    }
}
