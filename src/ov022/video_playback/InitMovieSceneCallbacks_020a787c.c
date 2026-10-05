#include "nitro/types.h"

typedef struct MovieSceneCallbacks {
    void (*open)(int arg);
    void *userData;
    void (*start)(void);
    void (*update)(void);
    BOOL (*isDone)(void);
    void (*close)(void);
    int unk18;
    int unk1c;
    int state;
} MovieSceneCallbacks;

extern void func_ov022_020a77f0(int arg);
extern void func_ov022_020a7814(void);
extern void func_ov022_020a7834(void);
extern void func_ov022_020a7858(void);
extern BOOL func_ov022_020a785c(void);

void InitMovieSceneCallbacks_020a787c(MovieSceneCallbacks *callbacks)
{
    callbacks->open = func_ov022_020a77f0;
    callbacks->close = func_ov022_020a7814;
    callbacks->start = func_ov022_020a7834;
    callbacks->update = func_ov022_020a7858;
    callbacks->isDone = func_ov022_020a785c;
    callbacks->userData = NULL;
    callbacks->state = 0;
}
