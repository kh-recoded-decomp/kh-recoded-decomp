#ifndef FIELD_TEXT_FORMATS_H
#define FIELD_TEXT_FORMATS_H

#include "nitro/types.h"

/* UTF-16 storage includes the original terminators and alignment padding. */
typedef struct FieldTextFormats {
    u16 empty[2];
    u16 spacedColon[4];
    u16 colonSpace[4];
    u16 copyString[4];
    u16 joinThreeStrings[8];
} FieldTextFormats;

extern FieldTextFormats gFieldTextFormats;

#endif
