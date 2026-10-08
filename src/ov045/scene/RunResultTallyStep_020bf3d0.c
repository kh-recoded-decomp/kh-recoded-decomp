#include "nitro/types.h"
#pragma opt_propagation off

typedef struct TileResource {
    u16 header;
    u8 unknown_02[0x0a];
    u16 tiles[1];
} TileResource;

typedef struct TileResourceRef {
    u8 unknown_00[0x08];
    TileResource *resource;
} TileResourceRef;

typedef struct Record {
    u16 id;
    s16 x;
    s16 y;
    u16 srcX;
    u16 srcY;
    s16 width;
    u8 unknown_0c[0x0c];
    TileResourceRef *ref;
} Record;

typedef struct Tween {
    u8 unknown_00[0x18];
    u32 unknownFlags : 2;
    u32 finished : 1;
    u8 unknown_1c[0x0c];
} Tween;

typedef struct PanelSprite {
    u32 texParams[2];
    u8 unknown_08[0x1a];
    u8 alpha : 5;
    u8 depthOffset : 3;
    u8 unknown_23[0x05];
} PanelSprite;

typedef struct RewardCell {
    s32 itemId : 16;
    s32 unknown_bits : 16;
    u8 category;
    u8 rarity;
} RewardCell;

typedef struct ItemInfo {
    u16 category : 2;
    u16 marks : 3;
    u16 unknown_00 : 11;
    u16 unknown_02 : 1;
    u16 rarity : 7;
    u16 unknown_02b : 8;
} ItemInfo;

typedef struct ItemEntry {
    u8 unknown_00[0x40];
    const u16 *name;
} ItemEntry;

typedef struct GameState {
    u8 unknown_00[0x28d4];
    s8 eventMode;
    u8 unknown_28d5[0x38d];
    u8 difficulty;
} GameState;

typedef struct ResultWork {
    u16 unknown_00;
    u16 course;
    int mode;
    u32 score;
    u32 time;
    s16 step;
    u8 unknown_12[0x02];
    u8 counter;
    u8 unknown_15[0x03];
    BOOL started;
    u8 unknown_1c[0x18];
    BOOL screensDirty;
    u8 records[0x4c];
    u16 subScreen[0x600];
    u16 mainScreen[0x600];
    u16 subRows[2][32];
    u16 mainRows[2][32];
    BOOL isNewRecord;
    u8 row;
    u8 unknown_1989[0x03];
    Record *digits[12];
    u8 textLayer[0x34];
    s16 rewardCount;
    u8 unknown_19f2[0x02];
    const u16 *rewardNames[5];
    PanelSprite panel;
    Tween tween;
} ResultWork;

extern ResultWork *data_ov045_020c0880;
extern GameState *data_0205fe0c;
extern u16 data_02060500;
extern const u16 data_ov045_020c086c[];

extern void ScrollTileRowPairLeft_020bf05c(u16 *tilemap, int row, int shift);
extern void CopyTileRowPair_020bf098(u16 *tilemap, const u16 *src, int row, int column);
extern void InvokeCallbackForRecordId_020bf0c4(void *pool, u32 recordId);
extern void OffsetRecordYById_020bf0dc(void *pool, s16 recordId, s16 offsetY);
extern u16 DrawTimeRecords_020bf104(void *pool, Record **digits, u32 value, int offsetY);
extern u16 DrawDigitRecords_020bf19c(void *pool, Record **digits, u32 value, int offsetY);
extern void StartUnitTween_020bf1f8(Tween *tween, int duration);
extern void ArmTagAtPosition_020bf218(void *tracker, int id, int position);
extern void ArmTagById_020bf248(void *tracker, int id);
extern void DisarmTagById_020bf26c(void *tracker, s16 id);
extern void DrawShadowedText_020bf284(void *layer, int x, int y, const u16 *text, u8 color);
extern int GetRemainingScoreTens_020bf2bc(ResultWork *work);
extern void CollectRecordPickup_020bf324(ResultWork *work, int id);
extern BOOL UpdateTweenIsFinished_020bf3bc(Tween *tween);
extern void func_ov045_020c0334(int left, int right, int top, int bottom);
extern void DrawLayeredPanel_020c05a0(PanelSprite *sprite, BOOL split);
extern void SampleTweenValue_0205258c(Tween *tween, s32 *value);
extern u32 ReadPackedRecord_0207ebac(int row, int column);
extern void WritePackedRecord_0207ebd0(int row, int column, u32 value);
extern int FindThresholdRank_0207ebf4(int row, u32 value);
extern RewardCell *GetLayoutCell_0207ec2c(int row, int column, int offset);
extern u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);
extern void WriteGlobalPackedBits_02027360(u32 bitOffset, u32 bitCount, u32 value);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern int func_ov001_020644b0(void);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern ItemEntry *GetRecordSlotPair0Entry_02051ec8(s32 index);
extern void func_02029240(int id, ItemInfo *info);
extern void func_01ff869c(const void *src, void *dst, u32 size);
extern void func_01ff8684(u16 value, void *dst, u32 size);
extern void FillBackgroundLayerRect_02001a60(void *layer, u16 *dst, int x, int y, u8 palette);
extern void Text_UploadTileBuffer_02001520(void *layer);
extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern Record *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void InvokeCallback40_020b8268(void *pool, Record *record);
extern void *func_ov001_0207123c(void);
extern void ClearTileTableRowAndMarkDirty_020b9d18(void *table, int row);
extern void func_ov027_020b7dd4(void *pool);
extern int GFXi_EnqueueCommand_02014090(int engine, int offset, void *src, int size);

int RunResultTallyStep_020bf3d0(void)
{
    ResultWork *work = data_ov045_020c0880;
    s32 fade;

    if (work->step < 0) {
        return 0;
    }
    switch (work->step) {
    case 0: {
        int alpha;

        if (!work->started) {
            StartUnitTween_020bf1f8(&work->tween, 1000);
            work->started = TRUE;
        }
        SampleTweenValue_0205258c(&work->tween, &fade);
        alpha = (fade >> 7) - 1;
        if (alpha < 0) {
            alpha = 0;
        }
        work->panel.alpha = (u8)alpha;
        if (work->tween.finished) {
            work->started = FALSE;
            work->step = work->step + 1;
        }
        break;
    }
    case 1: {
        BOOL isNew;

        if (!work->started) {
            InvokeCallbackForRecordId_020bf0c4(work->records, 0x168);
            work->started = TRUE;
            StartUnitTween_020bf1f8(&work->tween, 800);
        }
        if (UpdateTweenIsFinished_020bf3bc(&work->tween)) {
            isNew = FALSE;
            work->started = FALSE;
            if (work->mode != 2 && (work->mode == 1 || work->course < 1 || work->course >= 6)) {
                isNew = TRUE;
            }
            work->isNewRecord = isNew;
            if (isNew) {
                work->step = 2;
            } else {
                work->step = 4;
            }
        }
        break;
    }
    case 2:
        if (!work->started) {
            DrawTimeRecords_020bf104(work->records, work->digits, work->time, 0);
            InvokeCallbackForRecordId_020bf0c4(work->records, 0x177);
            work->started = TRUE;
            StartUnitTween_020bf1f8(&work->tween, 800);
        }
        if (UpdateTweenIsFinished_020bf3bc(&work->tween)) {
            work->started = FALSE;
            work->step = 3;
        }
        break;
    case 3:
        if (!work->started) {
            int bonus;

            InvokeCallbackForRecordId_020bf0c4(work->records, 0x176);
            bonus = GetRemainingScoreTens_020bf2bc(work);
            if (bonus < 0) {
                bonus = 0;
            }
            DrawDigitRecords_020bf19c(work->records, work->digits, bonus, 2);
            work->score += bonus;
            if (work->score > 999999) {
                work->score = 999999;
            }
            work->started = TRUE;
            StartUnitTween_020bf1f8(&work->tween, 800);
        }
        if (UpdateTweenIsFinished_020bf3bc(&work->tween)) {
            work->started = FALSE;
            work->step = 4;
        }
        break;
    case 4:
        if (!work->started) {
            u32 score;
            int offset;
            u8 difficulty = data_0205fe0c->difficulty;

            offset = (u16)(work->isNewRecord ? 4 : 2);

            if (work->mode == 2) {
                DrawTimeRecords_020bf104(work->records, work->digits, work->time, offset - 2);
                InvokeCallbackForRecordId_020bf0c4(work->records, 0x177);
                work->score = (s64)GetRemainingScoreTens_020bf2bc(work) * 30000 / 30000;
            } else {
                DrawDigitRecords_020bf19c(work->records, work->digits, work->score, offset);
                offset -= 2;
                OffsetRecordYById_020bf0dc(work->records, 0x169, offset);
                score = work->score;
                if (work->mode == 0) {
                    if (ReadPackedRecord_0207ebac(work->course, difficulty) < score) {
                        WritePackedRecord_0207ebd0(work->course, difficulty, score);
                        OffsetRecordYById_020bf0dc(work->records, 0x16a, offset);
                    }
                } else {
                    difficulty = 0x14;
                    if (ReadGlobalPackedBits_02027348(0xe2a, 0x14) < score) {
                        WriteGlobalPackedBits_02027360(0xe2a, difficulty, score);
                        OffsetRecordYById_020bf0dc(work->records, 0x16a, offset);

                    }
                }
            }
            work->started = TRUE;
            StartUnitTween_020bf1f8(&work->tween, 800);
        }
        if (UpdateTweenIsFinished_020bf3bc(&work->tween)) {
            work->started = FALSE;
            work->step = (work->mode == 2) ? 5 : 6;
        }
        break;
    case 5:
        if (!work->started) {
            u16 offset = work->isNewRecord ? 4 : 2;
            int shift;

            DrawDigitRecords_020bf19c(work->records, work->digits, work->score, offset);
            shift = offset - 2;
            OffsetRecordYById_020bf0dc(work->records, 0x169, shift);
            if (work->mode == 2) {
                u32 score = work->score;

                if (ReadGlobalPackedBits_02027348(0xe3e, 0x14) < score) {
                    WriteGlobalPackedBits_02027360(0xe3e, 0x14, score);
                    OffsetRecordYById_020bf0dc(work->records, 0x16a, shift);
                }
            }
            work->started = TRUE;
            StartUnitTween_020bf1f8(&work->tween, 800);
        }
        if (UpdateTweenIsFinished_020bf3bc(&work->tween)) {
            work->started = FALSE;
            work->step = 6;
        }
        break;
    case 6: {
        u32 rank;
        const u16 *name;
        u8 color;

        if (work->mode == 0) {
            rank = FindThresholdRank_0207ebf4(work->course, work->score);
        } else {
            rank = 3;
        }
        if (!work->started) {
            u16 isNew = work->isNewRecord ? 1 : 0;

            if (rank < 3) {
                int column;

                if (data_0205fe0c->eventMode == 3 && func_ov001_020644b0() == 400) {
                    column = 3 - ReadSessionPackedBits_02064574(0x3633, 2);
                } else {
                    column = 3 - data_0205fe0c->difficulty;
                }
                OffsetRecordYById_020bf0dc(work->records, 0x16b, isNew);
                OffsetRecordYById_020bf0dc(work->records, rank + 0x16c, isNew);
                for (; rank < 3; rank++) {
                    ItemInfo info;
                    ItemInfo *infoPtr;
                    RewardCell *cell = GetLayoutCell_0207ec2c(work->course, column, rank);
                    ItemEntry *entry = GetRecordSlotPair0Entry_02051ec8(cell->itemId);

                    work->rewardNames[work->rewardCount++] = entry->name;
                    info.rarity = cell->rarity;
                    info.category = cell->category;
                    info.marks = 0;
                    if (cell->itemId >= 0 && cell->itemId <= 0x7f) {
                        infoPtr = &info;
                    } else {
                        infoPtr = NULL;
                    }
                    func_02029240(cell->itemId, infoPtr);
                    SetGlobalPackedBit_02027320(cell->itemId);
                }
            } else {
                switch (work->mode) {
                case 0:
                    CollectRecordPickup_020bf324(work, 0x80);
                    break;
                case 1:
                    if (work->score >= 40000 && !IsGlobalPackedBitSet_02027304(0x1e04)) {
                        CollectRecordPickup_020bf324(work, 0x161);
                        SetGlobalPackedBit_02027320(0x1e04);
                    }
                    break;
                case 2:
                    if (work->score >= 1) {
                        CollectRecordPickup_020bf324(work, 0xf3);
                    }
                    break;
                }
                work->row -= 3;
            }
            work->row += (u8)isNew;
            work->started = TRUE;
            StartUnitTween_020bf1f8(&work->tween, 800);
        }
        if (rank != 3 && !UpdateTweenIsFinished_020bf3bc(&work->tween)) {
            break;
        }
        {
            Record *record = FindActiveRecordById_020b8184(work->records, 0x173);
            TileResource *resource = record->ref->resource;
            u16 width = resource->header >> 3;
            const u16 *tiles = resource->tiles + record->srcX + record->srcY * width;
            u16 *rows = &work->subRows[0][record->x];
            u16 size = record->width * 2;

            func_01ff869c(tiles, rows, size);
            func_01ff869c(tiles + width, &rows[32], size);
        }


        FillBackgroundLayerRect_02001a60(work->textLayer, work->mainRows[0], 0x12, 0, 0);
        if (work->rewardCount == 0) {
            name = data_ov045_020c086c;
            color = 0xf4;
        } else {
            work->rewardCount--;
            name = work->rewardNames[work->rewardCount];
            color = 0xf2;
            PlaySoundEffect_0204d924(0, 9);
        }
        DrawShadowedText_020bf284(work->textLayer, 0x4f, 2, name, color);
        Text_UploadTileBuffer_02001520(work->textLayer);
        work->started = FALSE;
        work->counter = 8;
        work->step = 10;
        break;
    }
    case 7:
        if (!work->started) {
            if (work->isNewRecord) {
                ArmTagById_020bf248(work->records, 7);
            } else {
                ArmTagAtPosition_020bf218(work->records, 5, work->row + 2);
            }
            func_01ff869c(&work->subScreen[work->row * 32], work->subRows, 0x80);
            func_01ff869c(&work->mainScreen[work->row * 32], work->mainRows, 0x80);
            work->started = TRUE;
        } else if (data_02060500 & 0x2f0f) {
            int tag;

            PlaySoundEffect_0204d924(0, 1);
            tag = 7;
            if (!work->isNewRecord) {
                tag = 5;
            }
            DisarmTagById_020bf26c(work->records, tag);
            if (work->rewardCount > 0) {
                work->step = 8;
                InvokeCallback40_020b8268(work->records,
                    FindActiveRecordById_020b8184(work->records, work->isNewRecord ? 0x23c : 0x174));
                work->started = FALSE;
                work->counter = 0;
            } else {
                work->started = FALSE;
                work->step = -1;
                ClearTileTableRowAndMarkDirty_020b9d18(func_ov001_0207123c(), 0xb);
                ClearTileTableRowAndMarkDirty_020b9d18(func_ov001_0207123c(), 0xa);
            }
        }
        break;
    case 8:
        work->step = 9;
        if (work->isNewRecord) {
            Record *record = FindActiveRecordById_020b8184(work->records, 0x23c);

            func_01ff8684(0, &work->subScreen[record->x + record->y * 32], 4);
            func_01ff8684(0, &work->subScreen[record->x + (record->y + 1) * 32], 4);
        }
        break;
    case 9:
        ScrollTileRowPairLeft_020bf05c(work->subScreen, work->row, 4);
        ScrollTileRowPairLeft_020bf05c(work->mainScreen, work->row, 4);
        work->screensDirty = TRUE;
        work->counter++;
        if (work->counter == 8) {
            CallVirtualHandlerSlot1_02001574(work->textLayer, 0);
            work->rewardCount--;
            DrawShadowedText_020bf284(work->textLayer, 0x4f, 2, work->rewardNames[work->rewardCount], 0xf2);
            Text_UploadTileBuffer_02001520(work->textLayer);
            work->step = 10;
            PlaySoundEffect_0204d924(0, 9);
        }
        break;
    case 10: {
        u16 column;

        work->counter--;
        column = work->counter * 4;
        CopyTileRowPair_020bf098(work->subScreen, work->subRows[0], work->row, column);
        CopyTileRowPair_020bf098(work->mainScreen, work->mainRows[0], work->row, column);
        work->screensDirty = TRUE;
        if (work->counter == 0) {
            work->step = 7;
        }
        break;
    }
    }
    func_ov027_020b7dd4(work->records);
    func_ov045_020c0334(0, 0x100000, 0, 0xc0000);
    DrawLayeredPanel_020c05a0(&work->panel, work->step >= 1);
    if (work->screensDirty) {
        GFXi_EnqueueCommand_02014090(0xb, 0, work->subScreen, 0x600);
        GFXi_EnqueueCommand_02014090(0xa, 0, work->mainScreen, 0x600);
        work->screensDirty = FALSE;
    }
    return 0;
}
