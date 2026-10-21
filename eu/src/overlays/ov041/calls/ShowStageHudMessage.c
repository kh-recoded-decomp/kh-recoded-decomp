#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))
#define va_arg(ap, type) (*(type *)(((ap) += 4) - 4))
#define va_end(ap) ((void)0)

extern int OS_SPrintf(char *buffer, const char *format, ...);

/* Shows a HUD message for 30 frames; the arguments its kind needs follow it. */
void ShowStageHudMessage(u8 kind, ...)
{
    StageHudMessage *message = &gMovieContextState->stageWork->hudMessage;
    va_list args;

    va_start(args, kind);
    switch (kind) {
    case 2:
        message->args[0] = va_arg(args, int);
        break;
    case 3:
        message->args[0] = va_arg(args, int);
        break;
    case 5:
        message->args[0] = va_arg(args, int);
        break;
    case 6:
        OS_SPrintf(message->text, va_arg(args, const char *));
        break;
    case 11:
        message->args[0] = va_arg(args, int);
        message->args[1] = va_arg(args, int);
        break;
    case 12:
        message->args[0] = va_arg(args, int);
        message->args[1] = va_arg(args, int);
        message->args[2] = va_arg(args, int);
        break;
    }
    va_end(args);
    message->kind = kind;
    message->flags |= STAGE_HUD_MESSAGE_SHOWN;
    message->timer = 30;
}
