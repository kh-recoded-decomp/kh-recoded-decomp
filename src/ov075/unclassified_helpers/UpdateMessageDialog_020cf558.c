#include "nitro/types.h"
#include "nitro/fx_types.h"

#define REG_DISPCNT (*(volatile u32 *)0x04000000)

typedef struct {
    u8 pad_00[4];
    s16 x;
    s16 y;
    u16 state;
} TouchState;

typedef struct {
    u8 data[0x18];
    u32 unk_0 : 1;
    u32 unk_1 : 1;
    u32 opened : 1;
    u32 unk_3 : 29;
    u8 pad_1c[8];
} FadeAnim;

typedef struct {
    void *func;
    void *context;
} DialogCallback;

typedef struct {
    s16 seqArc;
    s16 index;
} SoundPair;

typedef struct {
    fx32 x;
    fx32 y;
} WidgetPos;

typedef struct {
    int state;
    int mode;
    u16 screen[0x300];
    u8 chars[0x9c0c - 0x608];
    s16 tileX;
    s16 tileY;
    u16 width;
    u16 height;
    FadeAnim fade;
    BOOL active : 1;
    BOOL selectedYes : 1;
    BOOL pressed : 1;
    u8 pad_9c3c[8];
    DialogCallback callbacks[3];
    SoundPair sounds[2];
} Dialog;

extern u16 data_02060500;

extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern TouchState *func_ov039_020bca00(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void BeginPickerFadeOut_020cf518(Dialog *dialog);
extern void UpdateYesNoDialogInput_020cf02c(Dialog *dialog);
extern void SampleTweenValue_0205258c(FadeAnim *anim, fx32 *value);
extern void func_ov075_020ceee0(int x, int y, int width, int height, u16 *screen);
extern void func_0200344c(void *buffer, u32 size);
extern void GX_LoadBG1Scr_02007630(const void *src, u32 offset, u32 size);
extern void GX_LoadBG1Char_020079b0(const void *src, u32 offset, u32 size);
extern u16 *G2_GetBG1ScrPtr_02006e34(void);
extern void FillBackgroundTileRectangle_02017adc(u16 *dst, int width, int height, int x, int y, int stride, int value, int palette);
extern void func_ov075_020cf918(u16 tag, void *info);
extern void *func_ov039_020bc1bc(void);
extern void *FindWidgetById_020b90a4(void *widgets, int id);
extern void func_ov027_020b91c8(void *widgets, void *widget, WidgetPos *pos, int flag);
extern void SetEntrySlotsVisible_020b9580(void *widgets, void *widget, BOOL visible);
extern void GetDialogPixelBounds_020ceff8(Dialog *dialog, int *bottom, int *left, int *right);

void UpdateMessageDialog_020cf558(Dialog *dialog, BOOL handleInput)
{
    fx32 progress;
    WidgetPos markerPos;
    void *cursors[2];
    void *frames[2];
    WidgetPos pos;
    fx32 xs[2];
    int bottom;
    int left;
    int right;
    void *ok;
    void *cursor;
    void (*callback)();
    int width;
    int height;
    int shownWidth;
    int shownHeight;
    u32 size;
    void *widgets;
    void *widget;
    int selected;
    void *other;
    u32 planes;

    if (dialog->active) {
        if (dialog->state == 1) {
            dialog->state = 2;
        } else if (dialog->state == 3) {
            dialog->state = 4;
            SetSecondaryElementEnabled_020bc084(TRUE);
            planes = (REG_DISPCNT & 0x1f00) >> 8;
            REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | ((planes & ~2) << 8);
            callback = dialog->callbacks[0].func;
            if (callback != NULL) {
                dialog->callbacks[0].func = NULL;
                callback(dialog->callbacks[0].context);
            }
            dialog->sounds[0].seqArc = 0;
            dialog->sounds[0].index = 1;
            dialog->sounds[1].seqArc = 0;
            dialog->sounds[1].index = 3;
        }
        if (handleInput && dialog->state == 2) {
            switch (dialog->mode) {
            case 1:
                if ((data_02060500 & 1) || (data_02060500 & 2) || (data_02060500 & 8)
                    || (func_ov039_020bca00()->state & 3) == 1) {
                    callback = dialog->callbacks[2].func;
                    if (callback != NULL) {
                        callback(dialog->callbacks[2].context, 1);
                    }
                    PlaySoundEffect_0204d924(0, 1);
                    BeginPickerFadeOut_020cf518(dialog);
                }
                break;
            case 2:
                UpdateYesNoDialogInput_020cf02c(dialog);
                break;
            }
        }
    }
    if (!dialog->active) {
        if (!dialog->fade.opened) {
            SampleTweenValue_0205258c(&dialog->fade, &progress);
            width = dialog->width;
            shownWidth = (width * progress + 0x2000) >> 12;
            if (shownWidth > width) {
                shownWidth = width;
            }
            height = dialog->height;
            shownHeight = (height * progress + 0x2000) >> 12;
            if (shownHeight > height) {
                shownHeight = height;
            }
            func_ov075_020ceee0(dialog->tileX + (width - shownWidth) / 2, dialog->tileY + (height - shownHeight) / 2, shownWidth, shownHeight, dialog->screen);
            func_0200344c(dialog->screen, 0x600);
            GX_LoadBG1Scr_02007630(dialog->screen, 0, 0x600);
        } else {
            if (dialog->state == 0) {
                width = dialog->width - 2;
                height = dialog->height - (dialog->mode == 2 ? 4 : 2);
                callback = dialog->callbacks[1].func;
                dialog->callbacks[1].func = func_ov075_020cf918;
                callback(dialog->callbacks[1].context, dialog, width, height);
                if (width != 0 && height != 0) {
                    size = height * (width << 6);
                    func_0200344c(dialog->chars, size);
                    GX_LoadBG1Char_020079b0(dialog->chars, 0x140, size);
                    FillBackgroundTileRectangle_02017adc(G2_GetBG1ScrPtr_02006e34(), width, height, dialog->tileX + 1, dialog->tileY + 1, 0x20, 5, 0);
                }
                dialog->state = 1;
            }
            dialog->active = TRUE;
        }
    }
    widgets = func_ov039_020bc1bc();
    switch (dialog->mode) {
    case 1:
        widget = FindWidgetById_020b90a4(widgets, 0x27);
        if ((u32)(dialog->state - 1) <= 1) {
            markerPos.x = (dialog->tileX + dialog->width - 2) << 15;
            markerPos.y = ((dialog->tileY + dialog->height) << 15) - 0x1000;
            func_ov027_020b91c8(widgets, widget, &markerPos, 0);
            SetEntrySlotsVisible_020b9580(widgets, widget, TRUE);
            return;
        }
        SetEntrySlotsVisible_020b9580(widgets, widget, FALSE);
        return;
    case 2:
        selected = 0;
        ok = FindWidgetById_020b90a4(widgets, 0);
        cursors[0] = FindWidgetById_020b90a4(widgets, 0x23);
        cursors[1] = FindWidgetById_020b90a4(widgets, 0x24);
        frames[0] = FindWidgetById_020b90a4(widgets, 0x25);
        frames[1] = FindWidgetById_020b90a4(widgets, 0x26);
        if ((u32)(dialog->state - 1) <= 1) {
            if (!dialog->selectedYes) {
                selected = 1;
            }
            GetDialogPixelBounds_020ceff8(dialog, &bottom, &left, &right);
            pos.x = xs[0] = left << 12;
            pos.y = bottom << 12;
            cursor = cursors[selected];
            func_ov027_020b91c8(widgets, cursor, &pos, 0);
            pos.x = xs[1] = right << 12;
            other = frames[selected == 0];
            func_ov027_020b91c8(widgets, other, &pos, 0);
            pos.x = xs[selected] - 0x2a000;
            func_ov027_020b91c8(widgets, ok, &pos, 0);
            SetEntrySlotsVisible_020b9580(widgets, ok, TRUE);
            SetEntrySlotsVisible_020b9580(widgets, cursor, TRUE);
            SetEntrySlotsVisible_020b9580(widgets, other, TRUE);
            SetEntrySlotsVisible_020b9580(widgets, cursors[selected == 0], FALSE);
            SetEntrySlotsVisible_020b9580(widgets, frames[selected], FALSE);
            return;
        }
        if (dialog->state != 4) {
            SetEntrySlotsVisible_020b9580(widgets, ok, selected);
            SetEntrySlotsVisible_020b9580(widgets, cursors[0], selected);
            SetEntrySlotsVisible_020b9580(widgets, cursors[1], selected);
            SetEntrySlotsVisible_020b9580(widgets, frames[0], selected);
            SetEntrySlotsVisible_020b9580(widgets, frames[1], selected);
        }
        break;
    }
}
