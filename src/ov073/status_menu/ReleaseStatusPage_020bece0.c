#include "nitro/types.h"

typedef struct TextLayer {
    u8 pad_00[0x34];
} TextLayer;

typedef struct StatusPage {
    u8 pad_000[0x140];
    void *fileData;
    void *resource;
    u8 buffers[0x1c];
    BOOL bgOffsetHookActive;
    u8 pad_168[0x170 - 0x168];
    BOOL unk_170;
    u8 pad_174[0x198 - 0x174];
    TextLayer upperText;
    TextLayer lowerText;
} StatusPage;

extern const char data_ov073_020c4188[];
extern void NotifyBothOrOne_02001154(u32 kind, const char *name, int index);
extern BOOL DestroyFndObjectList_020014f0(TextLayer *layer);
extern void func_ov073_020c3c50(StatusPage *page);
extern int ZeroHalfThenFree_0202cd78(void *block);
extern void ReleaseResourceWithBuffers_0205206c(void **resourceHandle, int unused);
extern void FreeAllocatedBuffers_020b9a60(void *owner);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);

void ReleaseStatusPage_020bece0(void *menu, StatusPage *page)
{
    if (page->bgOffsetHookActive) {
        NotifyBothOrOne_02001154(1, data_ov073_020c4188, 0);
        page->bgOffsetHookActive = FALSE;
    }
    DestroyFndObjectList_020014f0(&page->upperText);
    DestroyFndObjectList_020014f0(&page->lowerText);
    func_ov073_020c3c50(page);
    ZeroHalfThenFree_0202cd78(page->fileData);
    ReleaseResourceWithBuffers_0205206c(&page->resource, 0xe);
    FreeAllocatedBuffers_020b9a60(page->buffers);
    page->unk_170 = 0;
    ReleaseRecordSlot_02051dfc(1);
}
