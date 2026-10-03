#include "nitro/types.h"

typedef struct Ov081State {
    u8 pad_00[0x20];
    u8 label[0x63ac];
    u8 tween[0x18];
    u32 flag0 : 1;
    u32 flag1 : 1;
    u32 tweenActive : 1;
} Ov081State;

extern void *FX_Div_020c542c(Ov081State *state);
extern void CountUnlockedListEntries_020c5460(Ov081State *state, void *list, int *total, int *before);
extern int SampleTweenValue_0205258c(void *tween, int *out);
extern void *func_ov039_020bc1bc(void);
extern void func_02052514(void *tween, int a, int b, int c, int duration);
extern void func_0205255c(void *tween);
extern void *FindWidgetById_020b90a4(void *screen, int id);
extern BOOL GetField84Bit1_020b9198(void *screen, void *widget);
extern void SetEntrySlotsVisible_020b9580(void *screen, void *widget, BOOL visible);
extern char *func_ov081_020c5be4(int id);
extern void func_0202e060(char *dst, const char *fmt);
extern void func_ov081_020c5530(void *label, int a, const char *text, int b, int x, int y, int c, int d);
extern const char data_020c5d5c[];

void DrawListPageIndicator_020c5790(Ov081State *state)
{
    int total;
    int before;
    int tweenValue;
    char text[24];
    void *screen;
    void *widget;

    CountUnlockedListEntries_020c5460(state, FX_Div_020c542c(state), &total, &before);
    if (total >= 2) {
        SampleTweenValue_0205258c(state->tween, &tweenValue);
        if (state->tweenActive) {
            screen = func_ov039_020bc1bc();
            func_02052514(state->tween, 0, 0, 0, 500);
            func_0205255c(state->tween);
            widget = FindWidgetById_020b90a4(screen, 1);
            SetEntrySlotsVisible_020b9580(screen, widget, !GetField84Bit1_020b9198(screen, widget));
            widget = FindWidgetById_020b90a4(screen, 2);
            SetEntrySlotsVisible_020b9580(screen, widget, !GetField84Bit1_020b9198(screen, widget));
        }
        func_ov081_020c5530(state->label, 2, func_ov081_020c5be4(0), 1, 0x16, 0xc, 2, 0x20);
        return;
    }
    func_0202e060(text, data_020c5d5c);
    func_ov081_020c5530(state->label, 2, text, 1, 0x16, 0xc, 2, 0x20);
}
