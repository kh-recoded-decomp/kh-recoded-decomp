#ifndef RECODED_BG_TEXT_TRANSFERS_H
#define RECODED_BG_TEXT_TRANSFERS_H

#include "nitro/types.h"

typedef void (*BgCharacterLoader)(const void *source, u32 offset, u32 size);
typedef void *(*BgScreenAddressGetter)(void);

extern const BgCharacterLoader gBgCharacterLoaders[4];
extern const BgScreenAddressGetter gBgScreenAddressGetters[4];

#endif
