#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    int size;
    int source;
} TileResource;

typedef struct {
    u8 pad_00[0x10];
    TileResource *alternate;
    TileResource *normal;
} MenuResources;

extern struct { int reserved; MenuResources *menu; } contextData_020c0068;
extern void UploadGroupPaletteSegment_020bb8d4(int alternate);
extern int GFXi_EnqueueCommand_02014090(void *a, int b, int c, int d);

void UploadGroupMenuTiles_020bbba8(int alternate)
{
    MenuResources *menu = contextData_020c0068.menu;
    TileResource *resource;
    if (alternate == 0) {
        resource = menu->normal;
        UploadGroupPaletteSegment_020bb8d4(FALSE);
    } else {
        resource = menu->alternate;
        UploadGroupPaletteSegment_020bb8d4(TRUE);
    }
    GFXi_EnqueueCommand_02014090((void *)7, 0x5000, resource->source, resource->size);
}
