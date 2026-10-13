#ifndef KH_RECODED_CONTINUE_MENU_H
#define KH_RECODED_CONTINUE_MENU_H

#include "nitro/types.h"

typedef struct ContinueMenuTileConfig {
    const s32 *ids;
    s32 count;
    u16 width;
    u16 height;
    u16 reserved[2];
} ContinueMenuTileConfig;

typedef struct ContinueMenuWidgetSource {
    u8 reserved00[8];
    void *screenData;
} ContinueMenuWidgetSource;

typedef struct ContinueMenuWidget {
    u8 reserved00[2];
    s16 x;
    s16 y;
    u16 srcX;
    u16 srcY;
    u8 reserved0a[6];
    s32 tableId;
    u8 reserved14[4];
    ContinueMenuWidgetSource *source;
} ContinueMenuWidget;

typedef struct ContinueMenuListConfig {
    s32 recordCount;
    s32 elementCount;
    s32 textCount;
    void (*blitWidget)(ContinueMenuWidget *);
    void (*clearWidget)(ContinueMenuWidget *);
} ContinueMenuListConfig;

typedef struct ContinueMenuTileTable {
    s32 *ids;
    s32 count;
    u16 width;
    u16 height;
    u16 rowLength;
    u16 reserved0e;
    u16 *rows;
    s32 loadImmediately;
    u8 dirtyMask;
    u8 reserved19[3];
} ContinueMenuTileTable;

/* Graphics prefix of the context allocated by CreateOv037Context. */
typedef struct ContinueMenuGraphicsState {
    u8 reserved00[8];
    u8 list[0x4c];
    ContinueMenuTileTable tileTable;
} ContinueMenuGraphicsState;

extern ContinueMenuGraphicsState *gContinueScreenContext;
extern const s32 gContinueMenuTileIds[2];
extern const ContinueMenuTileConfig gContinueMenuTileConfig;
extern const ContinueMenuListConfig gContinueMenuListConfig;

void BlitContinueMenuWidget(ContinueMenuWidget *widget);
void ClearContinueMenuWidget(ContinueMenuWidget *widget);

#endif
