/* BK9E 32-bit layouts, based on ov021 initialization and ov060 allocation.
 * Reserved fields preserve unknown areas. See analysis/overlay_loading.json. */
typedef struct OverlaySelectionRecord {
    unsigned char overlaySet;
    unsigned char unknown_001[0x144 - 1];
} OverlaySelectionRecord;

typedef struct OverlayObject {
    int variant;
    unsigned char unknown_004[0x1d4 - 0x004];
    OverlaySelectionRecord *selectionState;
    unsigned char selectionIndex;
    unsigned char unknown_1d9[0x1f4 - 0x1d9];
    void *updateCallback; /* Callback signature is not established. */
    unsigned char unknown_1f8[0x230 - 0x1f8];
} OverlayObject;

typedef OverlayObject *(*OverlayObjectFactory)(void);
typedef int OverlayIdTable[3][3];
typedef void (*OverlayInitializer)(void);
typedef OverlayInitializer OverlayInitializerTable[3][3];
typedef int OverlayTrackedIds[3];
