#include "nitro/types.h"

extern void MovieFileReaderDestructorNoOp(void);
extern void DeleteMovieFileReader(void);
extern void SeekBitstreamCursor_020aa188(void); /* SeekBitstreamCursor */
extern void readStreamBytesSynchronously_020aa1d4(void); /* readStreamBytesSynchronously */
extern void beginAlignedFileReadAhead_020aa244(void); /* beginAlignedFileReadAhead */
extern void WaitMovieReaderPendingIo(void);
extern void CallVirt14_020aa2e8(void); /* CallVirt14 */

void (*gStreamIoCallbacks[7])(void) = {
    MovieFileReaderDestructorNoOp,
    DeleteMovieFileReader,
    SeekBitstreamCursor_020aa188, /* SeekBitstreamCursor */
    readStreamBytesSynchronously_020aa1d4, /* readStreamBytesSynchronously */
    beginAlignedFileReadAhead_020aa244, /* beginAlignedFileReadAhead */
    WaitMovieReaderPendingIo,
    CallVirt14_020aa2e8, /* CallVirt14 */
};
