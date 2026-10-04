#include "nitro/types.h"

typedef struct TextLayer {
    u8 pad_00[0x34];
} TextLayer;

typedef struct ScoreScreen {
    u8 pad0;
    u8 dirty;
    u8 pad2[4];
    u16 timerDigits;
    u8 pad8[4];
    int elapsedSeconds;
    u8 pad10[0x80];
    u8 row;
    u8 labelColumn;
    u8 valueColumn;
    s8 markIndex;
    s16 markValue;
    s16 markOverride;
    u16 baseA;
    u16 baseB;
    u16 baseC;
    u16 baseD;
    u16 baseE;
    u16 baseF;
    s16 valueB;
    s16 valueC;
    s16 valueD;
    s16 valueE;
    s16 valueF;
    s16 limitB;
    s16 limitC;
    s16 limitD;
    s16 limitE;
    s16 limitF;
    TextLayer textLayers[2];
    const u16 *caption;
    void *records;
    void *cells;
    int *slots[2];
    int pad134;
    int *rowSlots[6];
    u8 pad150[0x1c];
    u8 tileBuffer[0x600];
} ScoreScreen;

extern u8 *data_0205fe0c;
extern char data_ov083_020bf6d8[];
extern char data_ov083_020bf6e0[];

extern u64 func_02003fd4(void);
extern u64 GetCardThreadStartTick_0202726c(void);
extern u64 func_02023d54(u64 dividend, u64 divisor);
extern void func_ov039_020be450(void *cells, int digits, int value, void *origin);
extern int func_ov039_020bca30(void);
extern int GetFieldCa4a_020bc9e0(void);
extern void ApplyScoreEvents_020bf388(ScoreScreen *screen);
extern void CallStateWidget_020bc14c(int a, int b, int c, int d, int e);
extern void *UpdateScreenWidgetLayer_020bc1e4(int screen);
extern void func_01ff8ad8(const void *src, void *dst, u32 len);
extern void SetScreenLayerDirty_020bc104(int screen);
extern void CallVirtualHandlerSlot1_02001574(TextLayer *layer, int arg);
extern void DrawTableString_020bf53c(ScoreScreen *screen, s16 x, s16 y, int stringIndex);
extern void func_ov083_020bf56c(ScoreScreen *screen, s16 x, s16 y, int color, const char *format, ...);
extern void SetEntrySlotsVisible_020b9580(void *cells, int *slots, int visible);
extern int func_ov083_020bf5fc(s16 value, s16 other);
extern int func_ov083_020bf5ac(s16 value, s16 other, s16 limit);
extern int func_ov083_020bf5cc(s16 value, s16 other, s16 limit);
extern int func_020275c8(void);
extern void Text_UploadTileBuffer_02001520(TextLayer *layer);
extern void DrawTextAnchored_020015a0(TextLayer *layer, int x, int y, int color, int flags, const u16 *text);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);

void UpdateScoreScreen_020bef1c(ScoreScreen *screen)
{
    u8 labelColumn;
    u8 valueColumn;
    u8 row;
    int shown;
    int color;
    int value;

    screen->elapsedSeconds = *(int *)(data_0205fe0c + 0x28c8)
        + func_02023d54((func_02003fd4() - GetCardThreadStartTick_0202726c()) * 64, 0x1ff6210);
    func_ov039_020be450(screen->cells, screen->timerDigits, screen->elapsedSeconds, NULL);
    if (func_ov039_020bca30() != 0) {
        return;
    }
    ApplyScoreEvents_020bf388(screen);
    GetFieldCa4a_020bc9e0();
    if (screen->dirty != 0) {
        CallStateWidget_020bc14c(0x1a, 0, 0, 0x20, 0x12);
        func_01ff8ad8(screen->tileBuffer, UpdateScreenWidgetLayer_020bc1e4(0x19), 0x600);
        SetScreenLayerDirty_020bc104(0x19);

        labelColumn = screen->labelColumn;
        valueColumn = screen->valueColumn;
        row = screen->row;
        CallVirtualHandlerSlot1_02001574(&screen->textLayers[0], 0);
        DrawTableString_020bf53c(screen, labelColumn, row + 16, 6);
        DrawTableString_020bf53c(screen, valueColumn, row, 7);
        row += 16;
        DrawTableString_020bf53c(screen, valueColumn, row, 10);
        row += 16;
        DrawTableString_020bf53c(screen, valueColumn, row, 12);
        row += 16;
        DrawTableString_020bf53c(screen, valueColumn, row, 11);
        DrawTableString_020bf53c(screen, valueColumn, (u8)(row + 16), 13);

        labelColumn += 0x58;
        valueColumn += 0x68;
        row = screen->row;
        if (screen->markIndex >= 0) {
            func_ov083_020bf56c(screen, labelColumn, row, 2, data_ov083_020bf6d8, screen->markIndex);
        }
        SetEntrySlotsVisible_020b9580(screen->cells, screen->rowSlots[0], screen->markOverride >= 0);
        SetEntrySlotsVisible_020b9580(screen->cells, screen->rowSlots[1], screen->valueB >= 0);
        SetEntrySlotsVisible_020b9580(screen->cells, screen->rowSlots[2], screen->valueC >= 0);
        SetEntrySlotsVisible_020b9580(screen->cells, screen->rowSlots[3], screen->valueD >= 0);
        SetEntrySlotsVisible_020b9580(screen->cells, screen->rowSlots[4], screen->valueE >= 0);
        SetEntrySlotsVisible_020b9580(screen->cells, screen->rowSlots[5], screen->valueF >= 0);

        if (screen->markValue >= 0) {
            int markRow;

            if (screen->markOverride >= 0) {
                shown = screen->markOverride;
            } else {
                shown = screen->markValue;
            }
            markRow = row + 16;
            func_ov083_020bf56c(screen, labelColumn, markRow,
                                func_ov083_020bf5fc(screen->markValue, screen->markOverride),
                                data_ov083_020bf6d8, shown);
            if (screen->markOverride >= 0) {
                func_ov083_020bf56c(screen, labelColumn - 0x18, markRow, 2, data_ov083_020bf6d8, screen->markValue);
            }
        }

        color = func_ov083_020bf5ac(screen->baseB, screen->valueB, screen->limitB);
        if (color != 2) {
            func_ov083_020bf56c(screen, valueColumn, row, color, data_ov083_020bf6d8,
                                screen->valueB >= 0 ? screen->valueB : screen->baseB);
        } else {
            func_ov083_020bf56c(screen, valueColumn, row, color, data_ov083_020bf6e0, screen->baseA, screen->baseB);
        }
        row += 16;

        if (screen->valueC >= 0) {
            value = screen->valueC;
        } else {
            value = screen->baseC;
        }
        func_ov083_020bf56c(screen, valueColumn, row,
                            func_ov083_020bf5ac(screen->baseC, screen->valueC, screen->limitC),
                            data_ov083_020bf6d8, value);
        row += 16;

        if (screen->valueD >= 0) {
            value = screen->valueD;
        } else {
            value = screen->baseD;
        }
        func_ov083_020bf56c(screen, valueColumn, row,
                            func_ov083_020bf5ac(screen->baseD, screen->valueD, screen->limitD),
                            data_ov083_020bf6d8, value);
        row += 16;

        if (screen->valueE >= 0) {
            value = screen->valueE;
        } else {
            value = screen->baseE;
        }
        func_ov083_020bf56c(screen, valueColumn, row,
                            func_ov083_020bf5ac(screen->baseE, screen->valueE, screen->limitE),
                            data_ov083_020bf6d8, value);

        value = screen->valueF;
        if (value < 0) {
            value = screen->baseF;
        }
        func_ov083_020bf56c(screen, valueColumn, (u8)(row + 16),
                            func_ov083_020bf5cc(screen->baseF, screen->valueF, screen->limitF), data_ov083_020bf6d8,
                            value * func_020275c8());

        Text_UploadTileBuffer_02001520(&screen->textLayers[0]);
        CallVirtualHandlerSlot1_02001574(&screen->textLayers[1], 0);
        if (screen->caption != NULL) {
            DrawTextAnchored_020015a0(&screen->textLayers[1], 0x60, 8, 2, 8, screen->caption);
        }
        Text_UploadTileBuffer_02001520(&screen->textLayers[1]);
        TagTracker_InvokeCallback_020b8210(screen->records, FindActiveRecordById_020b8184(screen->records, 0));
        TagTracker_InvokeCallback_020b8210(screen->records, FindActiveRecordById_020b8184(screen->records, 1));
        screen->dirty--;
    }
}
