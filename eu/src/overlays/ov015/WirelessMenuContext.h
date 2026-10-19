#ifndef KH_RECODED_WIRELESS_MENU_CONTEXT_H
#define KH_RECODED_WIRELESS_MENU_CONTEXT_H

#include "nitro/types.h"
#include "src/overlays/ov027/WidgetPosition.h"
#include "src/overlays/ov002/RecordSelectionView.h"

typedef union WirelessPaletteColor {
    u16 value;
    struct {
        u16 red : 5;
        u16 green : 5;
        u16 blue : 5;
        u16 unused : 1;
    } rgb;
} WirelessPaletteColor;

typedef struct WirelessSelectionResource {
    u8 data[0x70];
} WirelessSelectionResource;
typedef RecordSelectionView WirelessSelectionView;

/* The menu allocates 0xdec4 bytes. Unrecovered fields remain opaque. */
typedef struct WirelessMenuContext {
    u8 reserved00[0xc2];
    WirelessPaletteColor baseColor;
    WirelessPaletteColor highlightColor;
    u8 reservedc6[0x16];
    s32 phaseDegrees;
    u8 reservede0[2];
    struct {
        u8 increasing : 1;
        u8 enabled : 1;
        u8 subEngine : 1;
        u8 reserved : 5;
    } paletteFlags;
    u8 reservede3;
    u8 reservede4[0x69dc];
    u8 widgetManager[0x6444]; /* 0x6ac0 */
    u16 touchCursor;         /* 0xcf04 */
    u8 reservedcf06[0x52];
    WirelessSelectionResource selections[3]; /* 0xcf58 */
    WirelessSelectionView views[3];          /* 0xd0a8 */
    u8 reserveddeac[0x18];
} WirelessMenuContext;

typedef char WirelessPaletteColorSizeCheck[
    sizeof(WirelessPaletteColor) == sizeof(u16) ? 1 : -1];
typedef char WirelessMenuContextSizeCheck[
    sizeof(WirelessMenuContext) == 0xdec4 ? 1 : -1];
typedef char WirelessSelectionViewSizeCheck[
    sizeof(WirelessSelectionView) == 0x4ac ? 1 : -1];

void SetupWirelessSelectionSlot(s32 slot, WidgetPoint *position);

#endif
