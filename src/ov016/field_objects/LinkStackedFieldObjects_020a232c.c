#include "nitro/types.h"

typedef struct FieldObjectPool FieldObjectPool;

typedef struct FieldObject {
    u8 pad_00[4];
    FieldObjectPool *pool;
    u8 pad_08[0x28];
    u16 drawFlags;
    u8 pad_32;
    u8 slotIndex;
    u8 pad_34[4];
    s32 posX;
    s32 posY;
    s32 posZ;
    u8 pad_44[0x2c];
    u16 statePad : 3;
    u16 linkActive : 1;
    u16 statePadHigh : 12;
    u8 pad_72[4];
    s8 linkLocked;
    u8 linkBit;
    u8 pad_78[0x18];
    s16 linkPrev;
    s16 linkNext;
    u8 pad_94[0x29];
    u8 pad_bd : 4;
    u8 category : 4;
    u8 pad_be : 4;
    u8 mode : 4;
    u8 pad_bf;
    u32 flags;
} FieldObject;

struct FieldObjectPool {
    u8 pad_00[0x3e];
    u16 count;
};

extern BOOL func_ov001_020872b8(FieldObject *object);
extern FieldObject *func_ov001_0208635c(FieldObjectPool *pool, int index);
extern void func_ov016_020a230c(FieldObject *object);

void LinkStackedFieldObjects_020a232c(FieldObject *object)
{
    FieldObjectPool *pool = object->pool;
    FieldObject *other;
    FieldObject *head;
    int index;
    u32 usedBits;
    s32 delta;

    if (func_ov001_020872b8(object) && !(object->flags & 0x10) && object->mode != 6) {
        if (object->category != 1) {
            if (object->linkLocked == 0 && object->linkPrev == -1 && object->linkNext != -1) {
                other = func_ov001_0208635c(pool, object->linkNext);
                while (other != NULL) {
                    func_ov016_020a230c(other);
                    other->linkActive = 0;
                    if (object->linkNext != -1) {
                        other = NULL;
                    } else {
                        other = func_ov001_0208635c(pool, object->linkNext);
                    }
                }
            }
        } else {
            for (index = 0; index < pool->count; index++) {
                other = func_ov001_0208635c(pool, index);
                if (!(other->flags & 0x2000000)) {
                    continue;
                }
                if (other->category != 1 && other->category != 0) {
                    continue;
                }
                if (!func_ov001_020872b8(other) || other->mode == 6 || (other->flags & 0x10)) {
                    continue;
                }
                delta = other->posX - object->posX;
                if (delta >= 0x80 || delta <= -0x80) {
                    continue;
                }
                delta = other->posZ - object->posZ;
                if (delta >= 0x80 || delta <= -0x80) {
                    continue;
                }
                delta = other->posY - (object->posY - 0x1800);
                if (delta < 0x80 && delta > -0x80 && other->linkNext == -1) {
                    other->linkNext = object->slotIndex;
                    object->linkPrev = other->slotIndex;
                } else {
                    delta = other->posY - (object->posY + 0x1800);
                    if (delta < 0x80 && delta > -0x80 && object->linkNext == -1) {
                        object->linkNext = other->slotIndex;
                        other->linkPrev = object->slotIndex;
                    }
                }
            }
            head = object;
            usedBits = 0;
            if (object->linkPrev != -1) {
                other = func_ov001_0208635c(pool, object->linkPrev);
                while (other != NULL) {
                    if (other->linkPrev != -1) {
                        other = func_ov001_0208635c(pool, other->linkPrev);
                    } else {
                        head = other;
                        other = NULL;
                    }
                }
            }
            if (head->linkNext != -1) {
                while (head->linkNext != -1) {
                    u32 bit = 1 << head->linkBit;

                    if (!(usedBits & bit)) {
                        usedBits |= bit;
                        head->drawFlags |= 0x10;
                    } else {
                        head->drawFlags &= ~0x10;
                    }
                    head = func_ov001_0208635c(pool, head->linkNext);
                }
            } else {
                object->drawFlags |= 0x10;
            }
        }
    }
}
