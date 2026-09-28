#include "nitro/types.h"

typedef struct {
    u32 typeTag;
    u32 value;
} TypeTagPair;

typedef struct {
    u8 pad_00[0x18];
    u32 value;
} PairSource;

extern u32 data_02057b00;

void MakeTypeTagPair_0200b824(TypeTagPair *result, PairSource *source) {
    TypeTagPair pair = { data_02057b00, source->value };
    *result = pair;
}
