#include "nitro/types.h"

typedef struct OverlaySelectionRecord {
    unsigned char overlaySet;
    unsigned char unknown_001[0x144 - 1];
} OverlaySelectionRecord;

typedef struct OverlayObject {
    int variant;
    unsigned char unknown_004[0x1d4 - 0x004];
    OverlaySelectionRecord *selectionState;
    unsigned char selectionIndex;
    unsigned char unknown_1d9[0x1f4 - 0x1d9];
    void *updateCallback;
    unsigned char unknown_1f8[0x230 - 0x1f8];
} OverlayObject;

typedef OverlayObject *(*OverlayObjectFactory)(void);
typedef int OverlayIdTable[3][3];
typedef void (*OverlayInitializer)(void);
typedef OverlayInitializer OverlayInitializerTable[3][3];
typedef int OverlayTrackedIds[3];
extern unsigned int func_01ff8830();
extern unsigned int func_arm9_0204f768();

void func_ov021_020a75a4(OverlayObject *object,int variant,int selectionIndex) {
  OverlaySelectionRecord *selection;

  func_01ff8830(object,0,0x230);
  object->updateCallback = (void *)0x20a7a41;
  object->variant = variant;
  object->selectionIndex = (u8)selectionIndex;
  selection = func_arm9_0204f768(selectionIndex);
  object->selectionState = selection;
}
