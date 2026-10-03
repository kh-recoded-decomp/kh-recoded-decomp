#include "nitro/types.h"

typedef struct ResultsWork {
    u8 pad_0000[0x10];
    u8 tagTracker[0x4c];
    u8 objects[0x6b04];
    u8 text[0xa4];
    int counters[8][10];
    int badgeEntry;
    int rowEntries[6];
} ResultsWork;

typedef struct ResultsScreen {
    void *params;
    ResultsWork *work;
} ResultsScreen;

extern ResultsScreen g_resultsScreen_020c0f80;

extern void *func_ov027_020b90a4(void *objects, int id);
extern void func_ov027_020b9580(void *objects, void *object, int visible);
extern void CallVirtualHandlerSlot1_02001574(void *text, int arg);
extern void Text_UploadTileBuffer_02001520(void *text);
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void InvokeCallback40_020b8268(void *pool, void *record);
extern void func_0204f378(void *objects, int slotIndex, int enabled);
extern void func_0204f0c0(void *objects, int slotIndex);

#define WORK (g_resultsScreen_020c0f80.work)

void ResetResultsObjects_020bce50(void)
{
    int i;
    int row;
    void *object;

    for (i = 0; i <= 0xe6; i++) {
        object = func_ov027_020b90a4(WORK->objects, i);
        if (object != NULL) {
            func_ov027_020b9580(WORK->objects, object, 0);
        }
    }
    CallVirtualHandlerSlot1_02001574(WORK->text, 0);
    Text_UploadTileBuffer_02001520(WORK->text);
    for (i = 0; i < 7; i++) {
        InvokeCallback40_020b8268(WORK->tagTracker, FindActiveRecordById_020b8184(WORK->tagTracker, i));
    }
    func_0204f378(WORK->objects, WORK->badgeEntry, 0);
    for (i = 0; i < 6; i++) {
        func_0204f378(WORK->objects, WORK->rowEntries[i], 0);
    }
    for (row = 0; row < 8; row++) {
        for (i = 0; i < 10; i++) {
            if (WORK->counters[row][i] >= 0) {
                func_0204f0c0(WORK->objects, WORK->counters[row][i]);
            }
            WORK->counters[row][i] = -1;
        }
    }
}
