#include "nitro/types.h"

extern void MovieBaseReaderDestructorNoOp(void);
extern void DeleteMovieBaseReader(void);

void (*gStreamStateHandlers[9])(void) = {
    MovieBaseReaderDestructorNoOp,
    DeleteMovieBaseReader,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};
