#include "nitro/types.h"

typedef struct HeaderGraphic {
    u8 pad_00[0x24];
    int vramOffset;
} HeaderGraphic;

typedef struct FieldHeader {
    u8 pad_00[0x34];
    void *textLayer;
    u8 pad_38[0x1c];
    HeaderGraphic *graphic;
} FieldHeader;

typedef struct FieldManager {
    u8 pad_000[0x550];
    FieldHeader header;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;
extern void CallVirtualHandlerSlot1_02001574(void **context, int arg);
extern void DrawTextAnchored_020015a0(void **layer, int x, int y, int color, u32 flags, const u16 *text);
extern BOOL func_ov001_0207b3cc(void);
extern int GFXi_EnqueueCommand_02014090(int command, int value, int address, int size);

void DrawFieldHeaderText_02071df0(const u16 *text)
{
    FieldHeader *header = &data_ov001_020a04a4.manager->header;

    CallVirtualHandlerSlot1_02001574(&header->textLayer, 1);
    DrawTextAnchored_020015a0(&header->textLayer, 4, 3, 2, 0x209, text);
    if (!func_ov001_0207b3cc()) {
        GFXi_EnqueueCommand_02014090(0x15, 0x1000, header->graphic->vramOffset, 0x780);
    }
}
