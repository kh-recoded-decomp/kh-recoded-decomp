#ifndef RECODED_RECORD_PAGE_MENU_H
#define RECODED_RECORD_PAGE_MENU_H

#include "nitro/types.h"

typedef struct RecordMenuMessages {
    u32 reserved00;
    u32 entryCount;
    u8 *entries;
} RecordMenuMessages;

typedef struct RecordPageMenu {
    RecordMenuMessages messages;
    u8 textLayer[0x128];
    int pageIndex;
    u8 reserved138[4];
    int stepCount;
} RecordPageMenu;

typedef struct RecordRowMessageIds {
    u32 ids[4];
} RecordRowMessageIds;

extern const RecordRowMessageIds gRecordRowLabelMessageIds;
extern const RecordRowMessageIds gRecordRankMessageIds;
extern const u32 gRecordStepCounterBitOffsets[2][4];
extern const u32 gRecordPageCounterBitOffsets[8][4];
extern u16 gRecordStatisticNumberFormat[4];

void DrawRecordStatisticsRow(RecordPageMenu *menu, int row);

#endif
