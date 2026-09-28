#include "nitro/types.h"

typedef struct ElementType
{
    u8 pad_00[0x44];
    int id;
} ElementType;

typedef struct Element
{
    u8 pad_00[0x4];
    ElementType *type;
    u8 pad_08[0x28];
    u16 flags;
} Element;

extern BOOL func_ov001_020872b8(Element *element);

int func_ov001_02086414(Element *element)
{
    if (!func_ov001_020872b8(element) || !(element->flags & 8))
        return -1;
    return element->type->id;
}
