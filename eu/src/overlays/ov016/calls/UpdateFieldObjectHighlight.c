#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    s16 linkId;
} FieldLink;

typedef struct {
    u8 pad_00[0x30];
    u16 attributes;
    u8 pad_32[0x76 - 0x32];
    s8 forceShow;
    u8 mode;
    u8 pad_78[0xbd - 0x78];
    u8 unk_BD_low : 4;
    u8 phase : 4;
    u8 pad_be[0xec - 0xbe];
    FieldLink *link;
} FieldObject;

void UpdateFieldObjectHighlight(FieldObject *obj, BOOL visible)
{
    BOOL highlight;

    if (visible) {
        highlight = FALSE;
        obj->attributes |= 0x10;
        if (obj->phase < 5 || obj->link->linkId != -1) {
            if (obj->forceShow != 0) {
                highlight = TRUE;
            } else {
                switch (obj->mode) {
                case 9:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    highlight = TRUE;
                    break;
                }
            }
        }
        if (highlight) {
            obj->attributes |= 8;
        } else {
            obj->attributes &= ~8;
        }
    } else {
        obj->attributes &= ~0x10;
        obj->attributes &= ~8;
    }
}
