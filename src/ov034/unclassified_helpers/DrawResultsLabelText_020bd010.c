#include "nitro/types.h"

typedef struct ResultsLabel {
    u8 pad_00[0x40];
    const char *text;
} ResultsLabel;

typedef struct ResultsWork {
    u8 pad_0000[0x6b54];
    u8 textState[0x68];
} ResultsWork;

typedef struct ResultsScreen {
    void *params;
    ResultsWork *work;
} ResultsScreen;

typedef struct RankMarks {
    const char *marks[3];
} RankMarks;

extern ResultsScreen g_resultsScreen_020c0f80;
extern const RankMarks data_ov034_020be954;
extern const char data_ov034_020c0f2c[];
extern const char data_ov034_020c0f38[];
extern void *OS_SNPrintf_0202e080(char *dst, unsigned int len, const char *fmt, ...);
extern void func_0200160c(int *context, u32 x, u32 y, u32 color, u32 flags, const char *text, void *textState, int maxWidth);

void DrawResultsLabelText_020bd010(int *context, u32 x, u32 y, u32 color, u32 flags, ResultsLabel *label, s16 count, s16 rank)
{
    const char *text = label->text;
    char buffer[0x40];

    if (rank > 0) {
        RankMarks marks = data_ov034_020be954;
        OS_SNPrintf_0202e080(buffer, 0x20, data_ov034_020c0f2c, text, marks.marks[rank - 1]);
        text = buffer;
    }
    if (count > 0) {
        OS_SNPrintf_0202e080(buffer, 0x20, data_ov034_020c0f38, text, count);
        text = buffer;
    }
    func_0200160c(context, x, y, color, flags, text, g_resultsScreen_020c0f80.work->textState, 0x68);
}
