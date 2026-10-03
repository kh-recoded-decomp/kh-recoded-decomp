#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x14 - 4];
    s32 column;
    u8 pad_00018[0x24 - 0x18];
    u8 touchInput[4];
    BOOL columnLocked;
    u8 pad_0002C[0x11ee6 - 0x2c];
    s16 slotIndex;
} SlotMenu;

typedef BOOL (*SlotMenuCheck)(SlotMenu *menu);
typedef void (*SlotMenuAction)(SlotMenu *menu);

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    u16 slotHandles[16];
} SaveData;

extern SaveData *data_0205fe0c;
extern char data_ov076_020cd260[];

extern void *GetActiveRecordEntryOrNull_02029548(int index);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void SlotMenu_UnequipSlotEntry_020c89e0(SlotMenu *menu, int slot, int column);
extern void SlotMenu_ReloadSlot_020c6f60(SlotMenu *menu, int slot, int mode);
extern void SlotMenu_CheckPointLimit_020c544c(SlotMenu *menu, int mode);
extern void SlotMenu_ShowSlotHint_020c827c(SlotMenu *menu);
extern void SlotMenu_SelectGuideStep_020c439c(SlotMenu *menu);
extern BOOL func_ov076_020cbba0(void *touch, SlotMenu *menu, SlotMenuCheck check, SlotMenuAction action, void *region, int arg5);
extern BOOL SlotMenu_OpenEmptySlot_020c4f7c(SlotMenu *menu);
extern void SlotMenu_BeginSlotSelection_020c4edc(SlotMenu *menu);
extern void *func_ov039_020bc1bc(void);
extern void SetNavigationElementsVisible_020ccd30(void *container, BOOL visible);

void SlotMenu_UnequipCursorSlot_020c8d70(SlotMenu *menu)
{
    int column = menu->column;
    int slot = menu->slotIndex;
    u16 handle;

    if (menu->columnLocked == FALSE && menu->state == 1 && column != 2) {
        handle = data_0205fe0c->slotHandles[slot * 2 + column];
        if (handle != 0xffff) {
            if (handle < 0x200) {
                PlaySoundEffect_0204d924(1, 6);
                SlotMenu_UnequipSlotEntry_020c89e0(menu, slot, column);
                SlotMenu_ReloadSlot_020c6f60(menu, slot, 0);
                SlotMenu_CheckPointLimit_020c544c(menu, 0);
                SlotMenu_ShowSlotHint_020c827c(menu);
                return;
            }
            GetActiveRecordEntryOrNull_02029548((u16)(handle - 0x200));
            PlaySoundEffect_0204d924(1, 6);
            if (column == 0) {
                SlotMenu_UnequipSlotEntry_020c89e0(menu, slot, 1);
            }
            SlotMenu_UnequipSlotEntry_020c89e0(menu, slot, column);
            SlotMenu_ReloadSlot_020c6f60(menu, slot, 0);
            SlotMenu_CheckPointLimit_020c544c(menu, 0);
            SlotMenu_ShowSlotHint_020c827c(menu);
            SlotMenu_SelectGuideStep_020c439c(menu);
            if (func_ov076_020cbba0(menu->touchInput, menu, SlotMenu_OpenEmptySlot_020c4f7c, SlotMenu_BeginSlotSelection_020c4edc, data_ov076_020cd260, 1)) {
                menu->state = 2;
                SetNavigationElementsVisible_020ccd30(func_ov039_020bc1bc(), FALSE);
            }
        }
    }
}
