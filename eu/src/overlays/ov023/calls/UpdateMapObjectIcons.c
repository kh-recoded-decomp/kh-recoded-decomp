#pragma optimization_level 4
#pragma opt_common_subs on
#pragma opt_propagation on
#pragma opt_lifetimes on
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MapPoint {
    fx32 x;
    fx32 y;
} MapPoint;

typedef struct MenuAnimSlot {
    int slot;
    int sequence;
} MenuAnimSlot;

typedef struct MapDrawEntry MapDrawEntry;
typedef struct MapDrawList {
    MapDrawEntry *head;
    MapDrawEntry *tail;
    u16 count;
    u16 linkOffset;
} MapDrawList;

struct MapDrawEntry {
    MapDrawEntry *next;
    MapDrawEntry *previous;
    u32 unknown_08;
    MapPoint position;
    s32 distance;
    int sequence;
    u8 priority;
    u8 unknown_1d[3];
};

typedef struct MapMenu {
    u8 unknown_00[0x20];
    s32 tileScale;
    u8 unknown_24[0x50 - 0x24];
    s32 originX;
    s32 originY;
    u8 renderer[0x64a4 - 0x58];
    MenuAnimSlot icons[121];
    s32 scratchCount;
    s32 paletteIndex;
    MapDrawList drawList;
    MapDrawEntry drawPool[64];
    s32 poolCapacity;
    s32 poolUsed;
    MapDrawEntry scratch[121];
    u8 unknown_7fa8[0x7fb4 - 0x7fa8];
    BOOL distanceShown;
} MapMenu;

typedef struct MapObjectDescriptor {
    u8 unknown_00[0x7d];
    u8 kind;
} MapObjectDescriptor;

typedef struct MapObject MapObject;
struct MapObject {
    void *unknown_00;
    MapObject *next;
    MapObjectDescriptor *descriptor;
    u8 unknown_0c[0x3b - 0xc];
    u8 lowKind : 4;
    u8 mapKind : 4;
    u8 unknown_3c[0x4e - 0x3c];
    u16 flags;
};

typedef struct MapNodeDescriptor {
    u8 unknown_00[0x5a];
    u8 kind;
} MapNodeDescriptor;

typedef struct MapNode MapNode;
struct MapNode {
    MapNode *next;
    MapNodeDescriptor *descriptor;
    u8 unknown_08[0x30 - 8];
    u16 flags;
};

typedef struct EventTargetInfo {
    u16 id;
    u16 isPartner : 1;
    u16 isLocked : 1;
    u16 isScripted : 1;
    u16 isHidden : 1;
    u16 isVisible : 1;
    u16 reserved : 11;
    u16 kind;
    u16 unknown_06;
    VecFx32 position;
    s32 width;
    s32 height;
    s32 displayWidth;
    s32 displayHeight;
} EventTargetInfo;

#define MAP_OFFSET(type, field) ((u32)&((type *)0)->field)
#define MAP_CHECK_OFFSET(type, field, offset, name) \
    typedef char name[MAP_OFFSET(type, field) == (offset) ? 1 : -1]
typedef char MapPointIs8Bytes[sizeof(MapPoint) == 8 ? 1 : -1];
typedef char MenuAnimSlotIs8Bytes[sizeof(MenuAnimSlot) == 8 ? 1 : -1];
typedef char MapDrawListIs12Bytes[sizeof(MapDrawList) == 12 ? 1 : -1];
typedef char MapDrawEntryIs32Bytes[sizeof(MapDrawEntry) == 32 ? 1 : -1];
typedef char EventTargetInfoIs36Bytes[sizeof(EventTargetInfo) == 36 ? 1 : -1];
MAP_CHECK_OFFSET(MapDrawEntry, position, 0xc, MapDrawEntryPositionOffset);
MAP_CHECK_OFFSET(MapDrawEntry, sequence, 0x18, MapDrawEntrySequenceOffset);
MAP_CHECK_OFFSET(MapDrawEntry, priority, 0x1c, MapDrawEntryPriorityOffset);
MAP_CHECK_OFFSET(MapMenu, renderer, 0x58, MapRendererOffset);
MAP_CHECK_OFFSET(MapMenu, icons, 0x64a4, MapIconsOffset);
MAP_CHECK_OFFSET(MapMenu, scratchCount, 0x686c, MapScratchCountOffset);
MAP_CHECK_OFFSET(MapMenu, paletteIndex, 0x6870, MapPaletteIndexOffset);
MAP_CHECK_OFFSET(MapMenu, drawList, 0x6874, MapDrawListOffset);
MAP_CHECK_OFFSET(MapMenu, drawPool, 0x6880, MapDrawPoolOffset);
MAP_CHECK_OFFSET(MapMenu, poolCapacity, 0x7080, MapPoolCapacityOffset);
MAP_CHECK_OFFSET(MapMenu, poolUsed, 0x7084, MapPoolUsedOffset);
MAP_CHECK_OFFSET(MapMenu, scratch, 0x7088, MapScratchOffset);
MAP_CHECK_OFFSET(MapMenu, distanceShown, 0x7fb4, MapDistanceShownOffset);
MAP_CHECK_OFFSET(MapObject, descriptor, 8, MapObjectDescriptorOffset);
MAP_CHECK_OFFSET(MapObject, flags, 0x4e, MapObjectFlagsOffset);
MAP_CHECK_OFFSET(MapNode, descriptor, 4, MapNodeDescriptorOffset);
MAP_CHECK_OFFSET(MapNode, flags, 0x30, MapNodeFlagsOffset);
MAP_CHECK_OFFSET(EventTargetInfo, position, 8, EventTargetPositionOffset);
#undef MAP_CHECK_OFFSET
#undef MAP_OFFSET

extern void NNS_FndInitList(MapDrawList *, u16);
extern MapDrawEntry *NNS_FndGetNextListObject(MapDrawList *, MapDrawEntry *);
extern MapObject *func_ov001_0207f0b4(void);
extern BOOL UpdateMapTargetDistance(MapMenu *, MapObject *);
extern BOOL IsObjectFlagClear(MapObject *);
extern VecFx32 *FieldObject_GetPosition(MapObject *);
extern void WorldToMapPosition(MapMenu *, MapPoint *, const VecFx32 *);
extern BOOL IsMapPointInBounds(const MapPoint *);
extern void ChangeMenuAnimSequence(void *, MenuAnimSlot *, int, u32);
extern void IndexedRecords_SetFlag2(void *, int, int);
extern void IndexedRecord_SetPair(void *, int, const MapPoint *);
extern s32 ForwardToActiveServiceWithResult(void);
extern BOOL GetStageEventTargetInfo(u32, EventTargetInfo *);
extern s32 func_ov001_0208796c(s32);
extern VecFx32 *GetManagedActorPosition(int);
extern MapNode *func_ov001_02087264(void);
extern u16 func_ov001_02087644(void);
extern BOOL IsNodeFlagBitClear(MapNode *);
extern BOOL func_ov020_020a34b0(MapNode *);
extern int Object_GetKindValue(MapNode *);
extern int GetObjectPosition(MapNode *, VecFx32 *);
extern void StartDistanceSqrt(const MapPoint *, const MapPoint *);
extern MapDrawEntry *AllocDrawEntry(MapMenu *, int, const MapPoint *, u8);
extern void MI_CpuCopy8(const void *, void *, u32);

void UpdateMapObjectIcons(MapMenu *menu)
{
    VecFx32 positions[64];
    EventTargetInfo info;
    MapPoint iconPoint;
    MapPoint playerPoint;
    MapPoint point;
    int iconCount;
    void *renderer;
    int variant;
    int sequence;
    s32 eventId;
    VecFx32 *playerPosition;
    u8 priority;
    int count;
    MapNode *node;
    int overflow;
    MapObject *object;
    int kind;
    VecFx32 *objectPosition;
    int i;
    MapDrawEntry *entry;

    renderer = menu->renderer;
    NNS_FndInitList(&menu->drawList, 0);
    iconCount = 0;
    variant = menu->tileScale == 1 ? 0 : 1;
    menu->distanceShown = FALSE;
    for (object = func_ov001_0207f0b4(); object;) {
        if (object->descriptor->kind == 3) {
            if (!UpdateMapTargetDistance(menu, object)) {
                goto finish;
            }
            object = object->next;
            continue;
        }
        if (!IsObjectFlagClear(object) || !(object->flags & 0x20)) {
            goto advanceObject;
        }
        kind = object->mapKind;
        objectPosition = FieldObject_GetPosition(object);
        /* Unhandled map kinds retain the previous sequence and priority. */
        switch (kind) {
        case 0:
        case 8:
            sequence = -1;
            break;
        case 1:
            sequence = 10;
            priority = 5;
            break;
        case 2:
            sequence = 8;
            priority = 5;
            break;
        case 3:
            sequence = 14;
            priority = 6;
            break;
        case 4:
            sequence = 22;
            priority = 7;
            break;
        case 5:
            sequence = 26;
            priority = 8;
            break;
        case 6:
            sequence = 12;
            priority = 3;
            break;
        case 7:
            sequence = 6;
            priority = 4;
            break;
        }
        if (sequence >= 0 && objectPosition) {
            WorldToMapPosition(menu, &iconPoint, objectPosition);
            if (IsMapPointInBounds(&iconPoint)) {
                ChangeMenuAnimSequence(renderer, &menu->icons[iconCount], sequence + variant, priority);
                IndexedRecords_SetFlag2(renderer, menu->icons[iconCount].slot, 1);
                IndexedRecord_SetPair(renderer, menu->icons[iconCount].slot, &iconPoint);
                iconCount++;
            }
        }
advanceObject:
        object = object->next;
    }
    eventId = ForwardToActiveServiceWithResult();
    while (eventId) {
        if (!GetStageEventTargetInfo(eventId, &info)) {
            eventId = func_ov001_0208796c(eventId);
            continue;
        }
        if (info.isVisible) {
            eventId = func_ov001_0208796c(eventId);
            continue;
        }
        if (info.isPartner == 1) {
            sequence = 12;
            priority = 3;
        } else {
            sequence = 6;
            priority = 4;
        }
        WorldToMapPosition(menu, &iconPoint, &info.position);
        if (IsMapPointInBounds(&iconPoint)) {
            ChangeMenuAnimSequence(renderer, &menu->icons[iconCount], sequence + variant, priority);
            IndexedRecords_SetFlag2(renderer, menu->icons[iconCount].slot, 1);
            IndexedRecord_SetPair(renderer, menu->icons[iconCount].slot, &iconPoint);
            iconCount++;
        }
        eventId = func_ov001_0208796c(eventId);
    }
    overflow = 0;
    playerPosition = GetManagedActorPosition(0);
    node = func_ov001_02087264();
    if (!playerPosition) {
        goto finish;
    }
    menu->scratchCount = iconCount;
    WorldToMapPosition(menu, &playerPoint, playerPosition);
    if (func_ov001_02087644() - (121 - menu->scratchCount) >= 0) {
        overflow = func_ov001_02087644() - (121 - menu->scratchCount);
    }
    menu->poolCapacity = overflow;
    menu->poolUsed = 0;
    for (; node; node = node->next) {
        int nodeSequence;
        if (!IsNodeFlagBitClear(node) || !(node->flags & 0x10)) {
            continue;
        }
        switch (node->descriptor->kind) {
        case 1:
            if (func_ov020_020a34b0(node)) {
                nodeSequence = 22;
                priority = 7;
            } else {
                nodeSequence = 20;
                priority = 8;
            }
            break;
        case 2:
            nodeSequence = 24;
            priority = 9;
            break;
        case 3:
            nodeSequence = 24;
            priority = 9;
            break;
        case 5:
        case 9:
            kind = Object_GetKindValue(node);
            if (kind == 12 || kind == 13 || kind == 14 || kind == 15 || kind == 10 || kind == 1) {
                nodeSequence = 22;
                priority = 7;
            } else if (kind == 0 || kind == 16 || kind == 11 || kind == 3) {
                nodeSequence = 20;
                priority = 8;
            } else {
                nodeSequence = 24;
                priority = 9;
            }
            break;
        default:
            nodeSequence = 20;
            priority = 8;
            break;
        }
        count = GetObjectPosition(node, positions);
        for (i = 0; i < count; i++) {
            if (nodeSequence < 0) {
                continue;
            }
            WorldToMapPosition(menu, &point, &positions[i]);
            if (!IsMapPointInBounds(&point)) {
                continue;
            }
            StartDistanceSqrt(&playerPoint, &point);
            entry = AllocDrawEntry(menu, (int)&playerPoint, &point, priority);
            if (entry) {
                entry->sequence = nodeSequence + variant;
            }
        }
    }
    if (menu->scratchCount < 121) {
        for (entry = NNS_FndGetNextListObject(&menu->drawList, 0); entry;
             entry = NNS_FndGetNextListObject(&menu->drawList, entry)) {
            MI_CpuCopy8(entry, &menu->scratch[menu->scratchCount], sizeof(MapDrawEntry));
            menu->scratchCount++;
        }
    }
    for (i = iconCount; i < menu->scratchCount; i++) {
        entry = &menu->scratch[iconCount];
        ChangeMenuAnimSequence(renderer, &menu->icons[iconCount], entry->sequence, entry->priority);
        IndexedRecords_SetFlag2(renderer, menu->icons[iconCount].slot, 1);
        IndexedRecord_SetPair(renderer, menu->icons[iconCount].slot, &entry->position);
        iconCount++;
    }
    for (; iconCount < 121; iconCount++) {
        IndexedRecords_SetFlag2(renderer, menu->icons[iconCount].slot, 0);
    }
finish:
    return;
}
