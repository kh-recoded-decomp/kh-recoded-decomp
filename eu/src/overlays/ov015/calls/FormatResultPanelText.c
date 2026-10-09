#include "nitro/types.h"

extern void *SPrintfUnbounded(void *dst, const void *format, ...);

void FormatResultPanelText(u16 *dst, const u16 *format, const void *text, int value)
{
    int i = 0;

    for (;;) {
        u16 ch = format[i];
        dst[i] = ch;
        if (ch == 0) {
            return;
        }
        if (ch == '%') {
            u16 specifier = format[i + 1];
            if (specifier == 's' || specifier == 'S') {
                SPrintfUnbounded(dst, format, text);
                return;
            }
            SPrintfUnbounded(dst, format, value, text);
            return;
        }
        i++;
    }
}
