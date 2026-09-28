/* Adapted from CC0-1.0 source Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov024/calls/func_ov024_02084ec4.cpp.
 * Constructs the reader and stream objects around an already-open file,
 * releasing partially-created objects on initialization failure.
 */
/* The reader is bound to the file before the stream receives the reader and
 * frame-slot count. Its virtual deleting destructor handles reader-binding
 * failure. Both objects use the movie overlay's allocation wrappers.
 */
typedef unsigned int u32;

struct MobiClipReaderRaw {
    const void *pVtable;
    u32 fileSize;
    u32 filePosition;
    void *fileContext;
    u32 stateWord;
};

class MobiClipReader {
public:
    virtual ~MobiClipReader();
};

extern "C" {

extern int data_ov022_020b7d28;
extern int data_ov022_020b7d4c;

extern void *func_ov022_020aa118(u32 nSize);
extern void *func_ov022_020a93d4(u32 nSize);
extern void func_ov022_020a93e0(void *pBlock);
extern int func_ov022_020aa130(void *pReader, void *pFile);
extern void *func_ov022_020a93ec(void *pBlock);
extern int func_ov022_020a9170(void *pStream, void *pReader, int slotCount);
extern void func_ov022_020a941c(void *pStream);

void *createMovieStream_020a91a0(void *pFile, int slotCount)
{
    MobiClipReaderRaw *pReader;
    void *pStream;

    pReader = (MobiClipReaderRaw *)func_ov022_020aa118(0x14);
    if (pReader != 0) {
        pReader->pVtable = &data_ov022_020b7d28;
        pReader->fileSize = 0;
        pReader->filePosition = 0;
        pReader->pVtable = &data_ov022_020b7d4c;
    }
    if (pReader == 0) {
        return 0;
    }

    if (func_ov022_020aa130(pReader, pFile) == 0) {
        delete (MobiClipReader *)pReader;
        return 0;
    }

    pStream = func_ov022_020a93d4(0xd8);
    if (pStream != 0) {
        pStream = func_ov022_020a93ec(pStream);
    }
    if (func_ov022_020a9170(pStream, pReader, slotCount) == 0) {
        if (pStream != 0) {
            func_ov022_020a941c(pStream);
            func_ov022_020a93e0(pStream);
        }
        return 0;
    }
    return pStream;
}

}
