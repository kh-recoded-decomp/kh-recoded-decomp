#include "nitro/types.h"

typedef struct TextBoxSize {
    s32 width;
    s32 height;
} TextBoxSize;

extern void MeasureScriptTextBox_020bdb20(TextBoxSize *outSize, void *vm, void *operand);
extern void MeasureScriptOperandText_020bdb5c(TextBoxSize *outSize, void *vm, void *operand);
extern int ComputePageScrollOffset_020bdb98(int from, int to, BOOL forward);

void AccumulateTextBoxScroll_020bdc04(void *vm, void *operand, int kind, int direction, s32 *scroll)
{
    BOOL downward = FALSE;
    BOOL forward = FALSE;
    TextBoxSize current;
    TextBoxSize target;
    int deltaY;

    if (kind == 0xe) {
        return;
    }
    if (direction <= 3) {
        downward = TRUE;
        forward = TRUE;
    } else if (direction <= 7) {
        downward = TRUE;
    } else if (direction <= 0xb) {
        forward = TRUE;
    }
    MeasureScriptTextBox_020bdb20(&current, vm, operand);
    MeasureScriptOperandText_020bdb5c(&target, vm, operand);
    deltaY = target.height - current.height;
    if (target.width - current.width != 0) {
        scroll[0] += ComputePageScrollOffset_020bdb98(current.width, target.width, forward);
    }
    if (kind == 0xf) {
        deltaY -= deltaY % 2;
    }
    if (deltaY != 0) {
        scroll[1] += downward ? deltaY * 8 / 2 : -(deltaY * 8 / 2);
    }
}
