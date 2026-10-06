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

extern BOOL IsNodeFlagBitClear(Element *element);

int func_ov001_0208643c(Element *element)
{
    if (!IsNodeFlagBitClear(element) || !(element->flags & 8))
        return -1;
    return element->type->id;
}
