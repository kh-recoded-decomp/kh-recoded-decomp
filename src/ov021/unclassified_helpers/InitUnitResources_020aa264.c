#include "nitro/types.h"

typedef struct {
    u32 state;
    u8 selection;
    u8 pad_05[3];
    u8 *record;
    u8 pad_0c[0x48];
    u32 field_54;
    u32 field_58;
    u32 field_5c;
} UnitResources;

extern const char *data_0205615c[];
extern const char data_ov021_020b5238[];
extern const char data_ov021_020b5248[];
extern void *GetOverlaySelectionRecord(u32 selectionIndex);
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void *func_0202c48c(const char *path, u32 flags);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void func_ov021_020a9d68(UnitResources *unit, void *data, int kind);
extern void func_ov021_020a9ecc(UnitResources *unit, void *arg, int kind, void *data);

void InitUnitResources_020aa264(UnitResources *unit, void *arg, int kind, u32 selection)
{
    void *data;
    void *file;
    char motionPath[0x81];
    char modelPath[0x7f];

    unit->state = 0;
    unit->field_54 = 0;
    unit->field_5c = 0;
    unit->field_58 = 0;
    unit->selection = selection;
    unit->record = (u8 *)GetOverlaySelectionRecord(selection) + 0x10;
    OS_SPrintf_02002428(motionPath, data_ov021_020b5238, data_0205615c[kind]);
    data = func_0202c48c(motionPath, 0x11);
    func_ov021_020a9d68(unit, data, kind);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(data);
    OS_SPrintf_02002428(modelPath, data_ov021_020b5248, data_0205615c[kind]);
    file = func_0202c48c(modelPath, 0x11);
    func_ov021_020a9ecc(unit, arg, kind, file);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
}
