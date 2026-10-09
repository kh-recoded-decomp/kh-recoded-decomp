#include "nitro/types.h"

typedef struct {
    u32 cellFileId;
    u32 unk04[3];
} ObjManagerConfig;

extern const ObjManagerConfig data_ov087_020c7cec;
extern void *func_ov039_020bc1bc(void);
extern u32 BuildSlotImageParams_020bc220(int slot, u32 low);
extern void InitObjManagerAndMark_020b9060(void *container, ObjManagerConfig *config);
extern void func_ov027_020b8f98(void *container, u32 fileId, int count);
extern void SetAllElementObjectModes_020b97fc(void *container, int mode);
extern void *FindWidgetById_020b90a4(void *container, int elementId);
extern void SetFocusedWidget_020b96e4(void *container, void *element);
extern void SetWidgetRootDpadEnabled_020b9874(void *root, BOOL enabled);
extern void func_ov027_020b9098(void *container, u32 value);
extern void ResolveEntryStoreWord_020b9088(void *container, int elementId, void (*callback)(void));
extern void HandleSlotInput_020c460c(void);
extern void func_ov087_020c7810(void);
extern void func_ov087_020c7994(void);
extern void HandleConfirmForState_020c7ae4(void);
extern void func_ov087_020c7b64(void);
extern void func_ov087_020c7bf8(void);

void SetupPanelWidgetHandlers_020c69a4(void)
{
    void *container = func_ov039_020bc1bc();
    ObjManagerConfig config = data_ov087_020c7cec;

    config.cellFileId = BuildSlotImageParams_020bc220(2, 0x13);
    InitObjManagerAndMark_020b9060(container, &config);
    func_ov027_020b8f98(container, BuildSlotImageParams_020bc220(2, 0x12), 0xf);
    SetAllElementObjectModes_020b97fc(container, 2);
    SetFocusedWidget_020b96e4(container, FindWidgetById_020b90a4(container, 2));
    SetWidgetRootDpadEnabled_020b9874(container, TRUE);
    func_ov027_020b9098(container, (u32)HandleSlotInput_020c460c);
    ResolveEntryStoreWord_020b9088(container, 2, func_ov087_020c7810);
    ResolveEntryStoreWord_020b9088(container, 3, func_ov087_020c7994);
    ResolveEntryStoreWord_020b9088(container, 4, HandleConfirmForState_020c7ae4);
    ResolveEntryStoreWord_020b9088(container, 7, func_ov087_020c7b64);
    ResolveEntryStoreWord_020b9088(container, 8, func_ov087_020c7bf8);
}

