#include "nitro/types.h"

typedef struct {
    u8 pad00[2];
    s8 selection;
    u8 pad03[5];
    s32 state;
    u8 pad0c[0x69dc];
    u8 menu[1];
} SaveMenu;

extern SaveMenu *data_ov002_0206c464;
extern u8 *data_0205fe0c;

extern BOOL IsButtonBPressed_020632c8(void);
extern BOOL IsGlobalBit0Set_020632ac(void);
extern void PlaySoundEffect_0204d924(int bank, int id);
extern void ChangeMenuState(int result);
extern u16 *func_ov002_02062000(void);
extern void func_ov027_020b8ca8(void *menu, u16 entry);
extern int func_ov027_020b90a4(void *menu, int index);
extern void func_ov027_020b96e4(void *menu, int handle);
extern void SetEntrySlotsVisible_020b9580(void *menu, int handle, int visible);
extern void func_ov027_020b9098(void *menu, int flag);
extern void func_ov002_02064584(int mode);
extern int func_020271e8(u32 slot);
extern void IncrementBusyCounter_020254a8(void);
extern void DecrementBusyCounterIfPositive_02025494(void);
extern int PollCardThreadState_020271f8(void);
extern void SetCardThreadStartTick_02027258(void);
extern void func_ov002_02066c44(void);
extern void func_ov002_0206671c(void);
extern int GetMenuTouchPressed_02066b84(int arg);
extern void func_ov002_020620fc(int arg);

void UpdateSaveMenuState(void)
{
    u8 *menu;

    switch (data_ov002_0206c464->state) {
    case 0:
        if (IsButtonBPressed_020632c8()) {
            PlaySoundEffect_0204d924(2, 2);
            ChangeMenuState(1);
            return;
        }
        switch (data_ov002_0206c464->selection) {
        case 0:
            func_ov027_020b8ca8(data_ov002_0206c464->menu, *func_ov002_02062000());
            break;
        case 1:
            PlaySoundEffect_0204d924(2, 1);
            func_ov027_020b96e4(data_ov002_0206c464->menu, func_ov027_020b90a4(data_ov002_0206c464->menu, 0xc));
            data_ov002_0206c464->state = 1;
            break;
        case 2:
            PlaySoundEffect_0204d924(2, 1);
            func_ov027_020b96e4(data_ov002_0206c464->menu, func_ov027_020b90a4(data_ov002_0206c464->menu, 0xb));
            data_ov002_0206c464->state = 1;
            break;
        }
        break;
    case 1:
        data_ov002_0206c464->state = 3;
        break;
    case 3:
        switch (data_ov002_0206c464->selection) {
        case 1:
            ChangeMenuState(1);
            break;
        case 2:
            data_ov002_0206c464->state = 5;
            break;
        }
        break;
    case 5:
        func_ov002_02064584(0);
        menu = data_ov002_0206c464->menu;
        SetEntrySlotsVisible_020b9580(menu, func_ov027_020b90a4(menu, 0xb), 0);
        menu = data_ov002_0206c464->menu;
        SetEntrySlotsVisible_020b9580(menu, func_ov027_020b90a4(menu, 0xc), 0);
        func_ov027_020b9098(data_ov002_0206c464->menu, 0);
        if (func_020271e8((*(u32 *)(data_0205fe0c + 0x28c4) & 0x30000000) >> 28) == 0) {
            data_ov002_0206c464->state = 20;
            return;
        }
        IncrementBusyCounter_020254a8();
        data_ov002_0206c464->state = 10;
        break;
    case 10:
        switch (PollCardThreadState_020271f8()) {
        case 0:
            DecrementBusyCounterIfPositive_02025494();
            SetCardThreadStartTick_02027258();
            func_ov002_02066c44();
            func_ov002_02064584(4);
            PlaySoundEffect_0204d924(2, 1);
            data_ov002_0206c464->state = 50;
            break;
        case 1:
            break;
        default:
            data_ov002_0206c464->state = 20;
            break;
        }
        break;
    case 20:
        func_ov002_02064584(2);
        DecrementBusyCounterIfPositive_02025494();
        data_ov002_0206c464->state = 100;
        break;
    case 100:
        break;
    case 50:
        func_ov002_0206671c();
        if (IsGlobalBit0Set_020632ac() || IsButtonBPressed_020632c8() || GetMenuTouchPressed_02066b84(0)) {
            func_ov002_020620fc(0);
            PlaySoundEffect_0204d924(2, 2);
            ChangeMenuState(1);
        }
        break;
    }
}
