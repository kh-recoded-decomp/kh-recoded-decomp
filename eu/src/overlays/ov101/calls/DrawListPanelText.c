#include "src/overlays/ov101/ListMenuData.h"

extern u16 *func_ov027_020ba2c8(ListTextArchiveView *view, s32 index);
extern void CallVirtualHandlerSlot1(ListTextLayer *layer, s32 argument);
extern void DrawShadowedAnchoredText_020bfd34(ListTextLayer *layer, s32 x, s32 y,
                                             s32 color, u32 anchor, const u16 *text);
extern void Text_UploadTileBuffer(ListTextLayer *layer);
extern u32 GetNestedModeByte(ListTextLayer *layer);
extern BOOL IsGlobalPackedBitSet(s32 bit);
extern BOOL IsStateFlagSet(s32 set, s32 bit);

void DrawListPanelText(s32 which, ListSceneState *scene)
{
    ListTextArchiveView *commonView = &scene->textArchives[0];
    ListTextArchiveView *nameView = &scene->textArchives[2];
    ListTextArchiveView *descriptionView = &scene->textArchives[1];
    const ListEntryTextIndices *entry;
    const u16 *text;
    s32 y;
    Ov101ScrollPanel *panel;
    s32 i;
    s32 row;
    s32 selected;
    BOOL known;

    /* Draw the entry list, the description, or both (-1). */
    if ((u32)(which + 1) <= 1) {
        i = 0;
        text = func_ov027_020ba2c8(commonView, 0);
        CallVirtualHandlerSlot1(&scene->textLayers[0], 0);
        DrawShadowedAnchoredText_020bfd34(&scene->textLayers[0], 4, 2, 3, 0, text);
        Text_UploadTileBuffer(&scene->textLayers[0]);
        panel = &scene->panels[0];
        CallVirtualHandlerSlot1(&scene->textLayers[1], 0);
        for (; i < panel->pageRows; i++) {
            y = i * (GetNestedModeByte(&scene->textLayers[1]) + 6);
            row = panel->scroll + i;
            if (row == 7) {
                known = IsGlobalPackedBitSet(0xa0d);
            } else {
                known = IsStateFlagSet(0, row);
            }
            if (known) {
                text = func_ov027_020ba2c8(nameView, gListEntryTextIndices[row].nameIndex);
            } else {
                text = func_ov027_020ba2c8(commonView, 3);
            }
            DrawShadowedAnchoredText_020bfd34(&scene->textLayers[1], 4, y + 4, 1, 0, text);
        }
        Text_UploadTileBuffer(&scene->textLayers[1]);
    }
    if (which != 1 && which != -1) {
        return;
    }
    text = func_ov027_020ba2c8(commonView, 2);
    CallVirtualHandlerSlot1(&scene->textLayers[2], 0);
    DrawShadowedAnchoredText_020bfd34(&scene->textLayers[2], 4, 4, 3, 0, text);
    Text_UploadTileBuffer(&scene->textLayers[2]);
    selected = scene->activeList;
    entry = &gListEntryTextIndices[selected];
    func_ov027_020ba2c8(descriptionView, entry->descriptionIndex);
    CallVirtualHandlerSlot1(&scene->textLayers[3], 0);
    if (selected == 7) {
        known = IsGlobalPackedBitSet(0xa0d);
    } else {
        known = IsStateFlagSet(0, selected);
    }
    if (known) {
        /* Lines were split and cached when the scene was initialized. */
        s32 line;
        ListTextPage *page = &scene->textPages[selected];
        Ov101ScrollPanel *descriptionPanel = &scene->panels[1];
        u32 fontHeight = GetNestedModeByte(&scene->textLayers[3]);
        s32 visibleRows = descriptionPanel->pageRows;
        if (descriptionPanel->totalRows < visibleRows) {
            visibleRows = descriptionPanel->totalRows;
        }
        row = descriptionPanel->scroll;
        if (row < 0) {
            row = 0;
            descriptionPanel->scroll = row;
        }
        line = 0;
        for (; line < visibleRows; line++) {
            y = line * (fontHeight + 6);
            DrawShadowedAnchoredText_020bfd34(&scene->textLayers[3], 4, y + 4, 1, 0,
                                             page->lines[line + descriptionPanel->scroll]);
        }
    }
    Text_UploadTileBuffer(&scene->textLayers[3]);
}
