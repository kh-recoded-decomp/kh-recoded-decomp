#include "nitro/types.h"
#include "nitro/fs.h"
#include "nnsys/snd.h"

typedef struct StreamPlayer {
    u8 pad_00[0x64];
    FSFile file;
    u32 fileOffset;
    NNSSndStrmData info;
} StreamPlayer;

extern s32 NNS_SndArcReadFile_0201ed3c(u32 fileId, void *buffer, s32 size, s32 offset);
extern FSFileID NNS_SndArcGetFileID_0201ee08(void);
extern BOOL OpenFileFast_0200b4d4(FSFile *file, FSFileID id);
extern FSArchive *func_0201ef04(void);
extern u32 func_0201ef18(void);
extern u32 func_0201ef2c(void);
extern BOOL SendMessageAndDispatch_0200b52c(FSFile *file, FSArchive *archive, u32 mode);
extern BOOL SendSyncMessageArgs2_0200b5c4(FSFile *file, u32 top, u32 bottom);
extern u32 NNS_SndArcGetFileOffset_0201ecec(u32 fileId);

BOOL OpenFileStream_02021684(StreamPlayer *player, u32 fileId)
{
    FSArchive *archive;
    u32 imageTop;
    u32 imageBottom;
    BOOL opened;
    BOOL positioned;

    if (NNS_SndArcReadFile_0201ed3c(fileId, &player->info, sizeof(player->info), 0) != sizeof(player->info)) {
        return FALSE;
    }

    if (!OpenFileFast_0200b4d4(&player->file, NNS_SndArcGetFileID_0201ee08())) {
        archive = func_0201ef04();
        if (archive == NULL) {
            return FALSE;
        }

        imageTop = func_0201ef18();
        imageBottom = func_0201ef2c();
        if (imageTop == 0) {
            return FALSE;
        }
        if (imageBottom == 0) {
            return FALSE;
        }

        opened = SendMessageAndDispatch_0200b52c(&player->file, archive, 1);
        positioned = SendSyncMessageArgs2_0200b5c4(&player->file, imageTop, imageBottom);
        if (!opened) {
            return FALSE;
        }
        if (!positioned) {
            return FALSE;
        }
    }

    player->fileOffset = NNS_SndArcGetFileOffset_0201ecec(fileId);
    return TRUE;
}
