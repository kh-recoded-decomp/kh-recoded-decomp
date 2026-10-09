#include "nitro/types.h"

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))
#define va_arg(ap, type) (*(type *)(((ap) += 4) - 4))

typedef struct {
    int ids[7];
} RowLabelTable;

typedef struct {
    int ids[4];
} TierLabelTable;

typedef struct {
    u8 pad_000[0xc];
    u8 textLayer[0x128];
    int group;
    u8 pad_138[0xb0];
    u8 clearedGroups;
} RecordPanel;

extern const RowLabelTable data_ov086_020c21d0;
extern const TierLabelTable data_ov086_020c20e8;
extern char data_ov086_020c2fc8[];
extern char data_ov086_020c2fd0[];
extern char data_ov086_020c2fc4[];
extern const u16 *func_ov027_020ba2a8(RecordPanel *panel, int index);
extern u16 *func_ov027_020ba2e0(RecordPanel *panel, unsigned id, char *buffer, unsigned size, ...);
extern void *OS_SNPrintf_0202e080(char *dst, unsigned int len, const char *fmt, ...);
extern void DrawTextAnchored_020015a0(void *layer, int x, int y, int color, u32 flags, const void *text);

void DrawRecordStatRow_020bee0c(RecordPanel *panel, int row, ...)
{
    RowLabelTable rowLabels = data_ov086_020c21d0;
    TierLabelTable tierLabels = data_ov086_020c20e8;
    char text[32];
    va_list args;
    BOOL hasSecond = FALSE;
    const u16 *label;
    int first;
    int second;

    if (row == 6) {
        label = func_ov027_020ba2a8(panel, 5);
        DrawTextAnchored_020015a0(panel->textLayer, 0x10, 0x1b, 1, 0x209, label);
        DrawTextAnchored_020015a0(panel->textLayer, 0xf, 0x1a, 2, 0x209, label);
        DrawTextAnchored_020015a0(panel->textLayer, 0xa7, 0x19, 2, 0x821, data_ov086_020c2fc4);
        DrawTextAnchored_020015a0(panel->textLayer, 0xc0, 0x19, 2, 0x821, data_ov086_020c2fc4);
        return;
    }
    label = func_ov027_020ba2a8(panel, rowLabels.ids[row]);
    DrawTextAnchored_020015a0(panel->textLayer, 0x10, row * 16 + 0xb, 1, 0x209, label);
    DrawTextAnchored_020015a0(panel->textLayer, 0xf, row * 16 + 0xa, 2, 0x209, label);
    va_start(args, row);
    switch (row) {
    case 0:
    case 1:
        OS_SNPrintf_0202e080(text, 0x10, data_ov086_020c2fc8, va_arg(args, int));
        DrawTextAnchored_020015a0(panel->textLayer, 0xa7, row * 16 + 9, 2, 0x821, text);
        break;
    case 2:
        if (panel->group == 7) {
            OS_SNPrintf_0202e080(text, 0x10, data_ov086_020c2fd0, data_ov086_020c2fc4);
        } else {
            OS_SNPrintf_0202e080(text, 0x10, data_ov086_020c2fc8, va_arg(args, int));
        }
        DrawTextAnchored_020015a0(panel->textLayer, 0xa7, row * 16 + 9, 2, 0x821, text);
        break;
    case 3:
        first = va_arg(args, int);
        second = va_arg(args, int);
        if (second == 0) {
            OS_SNPrintf_0202e080(text, 0x10, data_ov086_020c2fd0, data_ov086_020c2fc4);
        } else {
            hasSecond = TRUE;
            OS_SNPrintf_0202e080(text, 0x10, data_ov086_020c2fc8, first);
        }
        DrawTextAnchored_020015a0(panel->textLayer, 0xa7, row * 16 + 9, 2, 0x821, text);
        if (!hasSecond) {
            OS_SNPrintf_0202e080(text, 0x10, data_ov086_020c2fd0, data_ov086_020c2fc4);
            DrawTextAnchored_020015a0(panel->textLayer, 0xc0, row * 16 + 9, 2, 0x821, text);
        } else {
            OS_SNPrintf_0202e080(text, 0x10, data_ov086_020c2fc8, second);
            DrawTextAnchored_020015a0(panel->textLayer, 0xc0, row * 16 + 9, 2, 0x821, text);
        }
        break;
    case 4:
        break;
    case 5:
        first = va_arg(args, int);
        if (first == 0) {
            OS_SNPrintf_0202e080(text, 0x10, data_ov086_020c2fd0, data_ov086_020c2fc4);
            DrawTextAnchored_020015a0(panel->textLayer, 0xa7, row * 16 + 9, 2, 0x821, text);
        } else {
            func_ov027_020ba2e0(panel, 0x1a, text, 0x10, first);
            DrawTextAnchored_020015a0(panel->textLayer, 0xa7, row * 16 + 9, 2, 0x821, text);
        }
        break;
    }
    if (row == 5) {
        if (va_arg(args, int) != 0) {
            panel->clearedGroups |= 1 << panel->group;
            return;
        }
        OS_SNPrintf_0202e080(text, 0x10, data_ov086_020c2fd0, data_ov086_020c2fc4);
        DrawTextAnchored_020015a0(panel->textLayer, 0xc0, row * 16 + 9, 2, 0x821, text);
        return;
    }
    if (row == 4) {
        label = func_ov027_020ba2a8(panel, tierLabels.ids[va_arg(args, int)]);
        DrawTextAnchored_020015a0(panel->textLayer, 0xc0, row * 16 + 0xa, 2, 0x821, label);
        return;
    }
    if (row == 3) {
        return;
    }
    if (row == 2 && panel->group == 7) {
        OS_SNPrintf_0202e080(text, 0x10, data_ov086_020c2fd0, data_ov086_020c2fc4);
    } else {
        OS_SNPrintf_0202e080(text, 0x10, data_ov086_020c2fc8, va_arg(args, int));
    }
    DrawTextAnchored_020015a0(panel->textLayer, 0xc0, row * 16 + 9, 2, 0x821, text);
}
