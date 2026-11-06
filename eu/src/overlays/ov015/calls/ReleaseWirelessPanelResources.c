#include "nitro/types.h"

extern void DestroyOwnedObjectList(void *ptr);
extern void DestroyObjectsAndRelease(void *ptr);
extern void FreePointerIfSet(void *ptr);
extern u8 *gWirelessBoardGlobals;

void ReleaseWirelessPanelResources(void) {
    DestroyObjectsAndRelease(gWirelessBoardGlobals + 0x160);
    FreePointerIfSet(gWirelessBoardGlobals + 0x65e0);
    DestroyOwnedObjectList(gWirelessBoardGlobals + 0x65ec);
    DestroyOwnedObjectList(gWirelessBoardGlobals + 0x65f0);
    DestroyOwnedObjectList(gWirelessBoardGlobals + 0x65f4);
}
