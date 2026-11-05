#include "src/overlays/ov001/FieldCommandLabels.h"
#include "src/overlays/ov027/PackedResource.h"

extern void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
extern void func_02001620(void *context, u32 x, u32 y, u32 color, u32 flags,
                         void *text, void *font, u32 maxWidth);
extern void *GetFieldFont1(void);

void DrawPackedFieldMenuEntry(void *menuBase, const PackedResourceView *view, u32 index)
{
    u8 *base = menuBase;
    void *payload;
    void *font;

    MIi_CpuCopyFast(*(void **)(base + 0xe4),
                   *(void **)(*(u8 **)(base + index * 4 + 0x74) + 0x24), 0x200);
    payload = GetPackedFileEntry(view, index);
    font = GetFieldFont1();
    func_02001620(base + 0x34, 0, 4, 4, 0, payload, font, 0x38);
}
