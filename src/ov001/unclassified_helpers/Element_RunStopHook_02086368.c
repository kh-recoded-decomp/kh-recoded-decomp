#include "nitro/types.h"

struct Element;

typedef struct ElementType
{
    u8 pad_00[0x8];
    void (*onStop)(struct Element *element);
} ElementType;

typedef struct Element
{
    u8 pad_00[0x4];
    ElementType *type;
    u8 pad_08[0x28];
    u16 flags;
} Element;

void Element_RunStopHook_02086368(Element *element)
{
    void (*onStop)(Element *element) = element->type->onStop;
    if (onStop != NULL)
        onStop(element);
    element->flags &= ~6;
}
