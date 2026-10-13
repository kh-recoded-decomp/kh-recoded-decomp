#include "src/overlays/ov086/RecordPageMenu.h"

extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void *func_ov027_020ba2c8(int *messages, int messageId);
extern void DrawTextAnchored(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern int GetPageSectionIndex(RecordPageMenu *menu);
extern int FindThresholdRank(int section, u32 value);
extern void *OS_SNPrintf_0202e094(char *buffer, unsigned int count, const char *format, ...);
extern void DrawRecordRowNames(RecordPageMenu *menu, int row, int rank);

void DrawRecordStatisticsRow(RecordPageMenu *menu, int row)
{
    RecordRowMessageIds labels = gRecordRowLabelMessageIds;
    RecordRowMessageIds ranks = gRecordRankMessageIds;
    u16 valueText[16];
    u32 bitOffset;
    u32 value;
    const u16 *label;
    int rank;
    int y = row * 0x48;

    if (menu->stepCount > 1) {
        bitOffset = gRecordStepCounterBitOffsets[menu->stepCount - 2][row];
    } else {
        bitOffset = gRecordPageCounterBitOffsets[menu->pageIndex][row];
    }
    value = ReadSessionPackedBits(bitOffset, 20);
    label = func_ov027_020ba2c8((int *)&menu->messages, labels.ids[row]);
    DrawTextAnchored(menu->textLayer, 6, y + 3, 1, 0x209, label);
    DrawTextAnchored(menu->textLayer, 5, y + 2, 2, 0x209, label);
    DrawTextAnchored(menu->textLayer, 80, y + 2, 6, 0x209,
                     func_ov027_020ba2c8((int *)&menu->messages, 22));
    rank = FindThresholdRank(GetPageSectionIndex(menu), value);
    DrawTextAnchored(menu->textLayer, 135, y + 2, 2, 0x209,
                     func_ov027_020ba2c8((int *)&menu->messages, ranks.ids[rank]));
    OS_SNPrintf_0202e094((char *)valueText, 16, (const char *)gRecordStatisticNumberFormat, value);
    DrawTextAnchored(menu->textLayer, 185, y + 2, 2, 0x821, valueText);
    DrawTextAnchored(menu->textLayer, 185, y + 2, 2, 0x821, valueText);
    DrawRecordRowNames(menu, row, rank);
}
