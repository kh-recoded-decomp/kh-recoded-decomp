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

extern void CreateMovieSceneTask(int arg);
extern void DestroyMovieSceneTaskIfSet(void);
extern void RequestMovieSceneStart(void);
extern void MovieSceneUpdateNoOp(void);
extern BOOL IsMovieSceneFinished(void);

void InitMovieSceneCallbacks(MovieSceneCallbacks *callbacks)
{
    callbacks->open = CreateMovieSceneTask;
    callbacks->close = DestroyMovieSceneTaskIfSet;
    callbacks->start = RequestMovieSceneStart;
    callbacks->update = MovieSceneUpdateNoOp;
    callbacks->isDone = IsMovieSceneFinished;
    callbacks->userData = NULL;
    callbacks->state = 0;
}
