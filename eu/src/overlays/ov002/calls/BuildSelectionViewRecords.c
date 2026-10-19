#pragma opt_propagation on
#pragma opt_common_subs off
#include "src/overlays/ov002/RecordSelectionView.h"
#include "src/overlays/ov002/RecordCategoryIcons.h"
#include "src/overlays/ov002/MenuRecordCategories.h"

typedef struct AvatarArchiveHeader {
    u16 signature;
    u16 countAndFlags;
    u32 mode;
    u32 fileStart;
    u32 dataOffset;
} AvatarArchiveHeader;

typedef struct AvatarEntryName {
    s8 text[8];
} AvatarEntryName;

typedef char AvatarArchiveHeaderSizeCheck[
    sizeof(AvatarArchiveHeader) == 0x10 ? 1 : -1];

extern const u16 data_ov002_0206adde[23];
extern char sOv002_WxcAvtFormat02dP2_0206c448[];
extern int OS_SPrintf(char *buffer, const char *format, ...);
extern AvatarArchiveHeader *Msg_OpenContainerAndReadHeader(
    const char *path, u32 mode, BOOL allocFromEnd);
extern int PXI_Init_0204f020(void *manager, u32 imageKey);
extern int PXI_Init_0204f0c8(void *manager, int animation, int image);
extern void Slot_SetMode2Bit(void *manager, int record, int mode);
extern void SetIndexedRecordPriority(void *manager, int record, int priority);
extern void IndexedRecord_SetPair(void *manager, int record, WidgetPoint *position);
extern void SlotTable_SetEntryPair(void *manager, int record, int xScale, int yScale);
extern void IndexedRecords_SetFlag2(void *manager, int record, int visible);
extern int ZeroHalfThenFree(void *allocation);

#define VIEW_FIELD_OFFSET(member) ((u32)&((RecordSelectionView *)0)->member)

void BuildSelectionViewRecords(void *manager, RecordSelectionView *view)
{
    WidgetPoint position;
    char path[32];
    u8 *groupSlots;
    int firstEntry;
    int entryCount;
    int restricted;
    int visible;
    fx32 scale;
    AvatarArchiveHeader *archive;
    int mode;
    u32 imageKey;
    int group;
    int image;
    int category;
    int i;
    int alternate;
    int record;
    int recordId;
    int created;
    s8 priority;
    AvatarEntryName *entries;
    u8 recordPriority;
    int archiveId;
    int archiveEntryCount;
    int tableIndex;
    const RecordCategoryIconEntry *layout;
    u16 paddedCount;

    mode = view->flags.mode;
    visible = view->flags.visible;
    position.x = view->position.x + view->offset.x;
    position.y = view->position.y + view->offset.y;
    scale = 0x1000;

    for (group = 0; group < RECORD_SELECTION_GROUP_COUNT; group++) {
        recordId = view->recordIds[group];
        archiveId = recordId / 10000;
        category = archiveId - 1;
        if (category < 0 || category >= 20)
            continue;

        if (view->flags.flag2) {
            if (category == 12) {
                /* This category's variant filter is a packed byte table. */
                if (((const u8 *)data_ov002_0206adde)[recordId % 10000] != 0)
                    continue;
            } else if (category != 11 && category != 17 && category >= 6) {
                continue;
            }
        }

        OS_SPrintf(path, sOv002_WxcAvtFormat02dP2_0206c448, archiveId);
        archive = Msg_OpenContainerAndReadHeader(path, 16, FALSE);
        alternate = FALSE;
        restricted = FALSE;
        archiveEntryCount = archive->countAndFlags & 0x1ff;
        tableIndex = gMenuRecordCategoryFlagBitOffsets[category];
        tableIndex += recordId % 10000;
        if (category == 5)
            tableIndex--;
        layout = &gMenuRecordIconLayouts[tableIndex];
        firstEntry = layout->firstEntry;
        entryCount = layout->entryCount;

        /* The P2 names follow the padded ID array and the entry offset array. */
        paddedCount = ((archiveEntryCount + 1) / 2) * 2;
        entries = (AvatarEntryName *)((u8 *)archive + sizeof(*archive)
                    + paddedCount * 2 + archiveEntryCount * 4);

        if (view->flags.flag2) {
            if (category == 0) {
                alternate = TRUE;
            } else if (category == 17) {
                restricted = TRUE;
            }
        } else if (view->flags.flag4) {
            if (category == 17 || view->flags.flag5) {
                scale = 0x910;
            } else if (category == 0) {
                if (view->flags.flag6)
                    alternate = TRUE;
                else
                    scale = 0x910;
            }
        }
        if (alternate) {
            firstEntry += 4;
            entryCount = 1;
        }

        created = 0;
        i = 0;
        entries += firstEntry;
        if (entryCount > 0) {
            /* Tagged P2 resource: archive address plus a nine-bit entry ID. */
            imageKey = ((((u32)archive + 0x8000) & 0x00fffffc) << 7) | 0x80000000;

            /* All three slot arrays share the same 16-byte group stride. */
            groupSlots = (u8 *)view + group * sizeof(view->objSlots[0]);
            do {
                priority = (entries->text[6] & 0xf) * 10 + (entries->text[7] & 0xf);
                if (!restricted || (priority >= 51 && priority < 70)) {
                    image = PXI_Init_0204f020(manager,
                                imageKey | ((firstEntry + i) & 0x1ff));
                    record = PXI_Init_0204f0c8(manager, 0, image);
                    recordPriority = view->basePriority - priority;
                    Slot_SetMode2Bit(manager, record, mode);
                    SetIndexedRecordPriority(manager, record, recordPriority);
                    IndexedRecord_SetPair(manager, record, &position);
                    SlotTable_SetEntryPair(manager, record, scale, scale);
                    if (!visible)
                        IndexedRecords_SetFlag2(manager, record, FALSE);
                    groupSlots[created + VIEW_FIELD_OFFSET(objSlots)] = image;
                    groupSlots[created + VIEW_FIELD_OFFSET(recordSlots)] = record;
                    groupSlots[created + VIEW_FIELD_OFFSET(priorities)] = priority;
                    created++;
                }
                i++;
                entries++;
            } while (i < entryCount);
        }
        view->counts[group] = created;
        ZeroHalfThenFree(archive);
    }
    view->scale.x = scale;
    view->scale.y = scale;
}
