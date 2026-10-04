#include "nitro/types.h"

typedef struct {
    u8 bytes[0x20];
} FadeRecord;

typedef struct Ov081State {
    u8 pad_00[0x63c8];
    BOOL arrowsShown;
    FadeRecord arrowFade;
} Ov081State;

typedef struct EntryList EntryList;

extern void *func_ov039_020bc1bc(void);
extern void *FindWidgetById_020b90a4(void *root, int id);
extern EntryList *FX_Div_020c542c(void);
extern void CountUnlockedListEntries_020c5460(Ov081State *state, EntryList *list, int *total, int *before);
extern void SetEntrySlotsVisible_020b9580(void *panel, void *element, BOOL visible);
extern void func_02052514(FadeRecord *record, int value0, int value1, int value2, int value3);
extern void func_0205255c(FadeRecord *record);

void UpdateScrollArrows_020c4dfc(Ov081State *state)
{
    void *panel = func_ov039_020bc1bc();
    void *leftArrow = FindWidgetById_020b90a4(panel, 1);
    void *rightArrow = FindWidgetById_020b90a4(panel, 2);
    int total;
    int before;

    CountUnlockedListEntries_020c5460(state, FX_Div_020c542c(), &total, &before);
    if (total >= 2) {
        if (state->arrowsShown == FALSE) {
            state->arrowsShown = TRUE;
            SetEntrySlotsVisible_020b9580(panel, leftArrow, TRUE);
            SetEntrySlotsVisible_020b9580(panel, rightArrow, TRUE);
            func_02052514(&state->arrowFade, 0, 0, 0, 500);
            func_0205255c(&state->arrowFade);
        }
    } else if (state->arrowsShown != FALSE) {
        state->arrowsShown = FALSE;
        SetEntrySlotsVisible_020b9580(panel, leftArrow, FALSE);
        SetEntrySlotsVisible_020b9580(panel, rightArrow, FALSE);
    }
}
