#include "nitro/types.h"

typedef struct GaugeArt {
    u8 pad_00[0x24];
    void *pixels;
} GaugeArt;

typedef struct CooldownGauge {
    u32 startTick;
    u32 duration;
    u32 owner;
    s32 recordId;
    s32 kind;
    u8 pad_14[0x08];
    GaugeArt *art;
    u8 pad_20[0x08];
    u16 flags;
    u16 repeat;
} CooldownGauge;

typedef struct GaugeWindow {
    u8 pad_00[0xe0];
    void *pixels;
} GaugeWindow;

typedef struct CommandRecord {
    u8 pad_00[0x10];
    s32 kind;
    u8 pad_14[0x08];
    u16 cooldown;
    u8 pad_1e[0x0a];
    int nameId;
} CommandRecord;

extern u8 data_020603c8;
extern u16 data_ov001_0209eec8[];

extern void func_01ff878c(const void *src, void *dst, u32 size);
extern CommandRecord *GetRecordSlotPair1Entry_02051ef4(s32 index);
extern BOOL IsFieldFlag10Set_020728c4(void);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL IsFieldFlag8Set_020728a4(void);
extern u32 func_01ff80d4(void);
extern void *GetFieldFont1_020711c8(void);
extern void func_0200160c(GaugeWindow *window, u32 x, u32 y, u32 color, u32 flags, int value, void *font, u32 width);
extern void DrawTextAnchored_020015a0(GaugeWindow *window, int x, int y, int color, u32 flags, const u16 *text);

void StartCommandCooldownGauge_02076b80(GaugeWindow *window, CooldownGauge *gauge, u32 owner, s32 recordId, u16 repeat, u8 bonusKind, u8 bonusPercent)
{
    CommandRecord *record;
    u32 scale;
    u16 *flags;

    gauge->recordId = recordId;
    gauge->repeat = repeat;
    gauge->owner = owner;
    func_01ff878c(window->pixels, gauge->art->pixels, 0x200);
    switch (data_020603c8) {
    case 0:
        scale = 2;
        break;
    case 1:
        scale = 3;
        break;
    case 2:
        scale = 1;
        break;
    }
    if (recordId == -1) {
        gauge->kind = -1;
        record = NULL;
        gauge->flags &= ~1;
        gauge->duration = 0;
        gauge->startTick = 0;
        gauge->flags &= ~4;
    } else {
        record = GetRecordSlotPair1Entry_02051ef4(recordId);
        if (IsFieldFlag10Set_020728c4() || IsHudFlag7Set_020725bc() || IsFieldFlag8Set_020728a4()) {
            gauge->duration = record->cooldown;
        } else {
            gauge->duration = record->cooldown * scale;
            if (bonusKind == 2 || bonusKind == 3) {
                gauge->duration -= (gauge->duration >> 1) * bonusPercent / 100;
            }
        }
        gauge->startTick = func_01ff80d4();
        gauge->kind = record->kind;
        gauge->flags |= 4;
        flags = &gauge->flags;
        *flags = record->kind == 3 ? (repeat == 0 ? (*flags & 0xfffe) : (*flags | 1)) : (*flags & 0xfffe);
    }
    if (record == NULL) {
        DrawTextAnchored_020015a0(window, 0, 4, 4, 0, data_ov001_0209eec8);
    } else {
        func_0200160c(window, 0, 4, 2, 0, record->nameId, GetFieldFont1_020711c8(), 0x38);
    }
}
