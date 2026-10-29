#ifndef KH_RECODED_CAROUSEL_MODELS_H
#define KH_RECODED_CAROUSEL_MODELS_H

#include "nitro/types.h"
#include "nitro/fx_types.h"

/* ARM32 views of the spans used by the initializer, not complete engine types. */
typedef struct CarouselModelView {
    u8 unknown000[0xb0];
    VecFx32 scale;
    u8 unknown0bc[0xd8 - 0xbc];
    u8 animationTable[0x2c];
} CarouselModelView;

typedef struct CarouselEntryView {
    int id;
    CarouselModelView model;
} CarouselEntryView;

typedef struct CarouselSceneView {
    int step;
    int cursor;
    int entryCount;
    u8 unknown00c[8];
    CarouselModelView centerModel;
    CarouselEntryView entries[8];
    u32 projection[14];
} CarouselSceneView;

typedef struct {
    u32 ids[8];
} CarouselResourceIds;

typedef char CarouselModelSpanCheck[sizeof(CarouselModelView) == 0x104 ? 1 : -1];
typedef char CarouselEntryStrideCheck[sizeof(CarouselEntryView) == 0x108 ? 1 : -1];
typedef char CarouselScenePrefixCheck[sizeof(CarouselSceneView) == 0x990 ? 1 : -1];
typedef char CarouselResourceIdsSizeCheck[sizeof(CarouselResourceIds) == 0x20 ? 1 : -1];

extern const CarouselResourceIds data_ov087_020c7d1c;
extern const CarouselResourceIds data_ov087_020c7d3c;

#endif
