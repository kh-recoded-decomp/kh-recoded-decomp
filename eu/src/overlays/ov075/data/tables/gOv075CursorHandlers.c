#include "nitro/types.h"

extern void MatrixMenu_UpdatePage1CursorNoop(void); /* _fp_init */
extern void MatrixMenu_UpdatePage2CursorNoop(void); /* _fp_init */
extern void StepScrollTowardTarget(void);
extern void MoveCursorToSelectedColumn(void); /* MoveCursorToSelectedColumn */
extern void MatrixMenu_UpdatePage5CursorNoop(void); /* _fp_init */

void (*const gOv075CursorHandlers[5])(void) = {
    MatrixMenu_UpdatePage1CursorNoop, /* _fp_init */
    MatrixMenu_UpdatePage2CursorNoop, /* _fp_init */
    StepScrollTowardTarget,
    MoveCursorToSelectedColumn, /* MoveCursorToSelectedColumn */
    MatrixMenu_UpdatePage5CursorNoop, /* _fp_init */
};
