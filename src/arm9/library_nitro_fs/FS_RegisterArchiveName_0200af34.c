#include "nitro/types.h"

typedef struct FSArchive {
    union {
        char ptr[4];
        u32 pack;
        char *longName;
    } name;
    struct FSArchive *next;
    u8 pad_08[0xc];
    u32 flag;
} FSArchive;

extern FSArchive *g_archiveList_020578ec;
extern FSArchive *g_archiveListLink_020578ec;
extern char data_020578fc[16][16];
extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern FSArchive *FindRegisteredEntryByName_0200aa68(const char *name, u32 nameLength);
extern int Strlcpy_02010bcc(char *dst, const char *src, int size);
extern void RunResetCallbackAndIdle_02004cf0(void);

BOOL FS_RegisterArchiveName_0200af34(FSArchive *arc, const char *name, u32 nameLength) {
    BOOL result = FALSE;
    u32 savedState = func_02004938();
    if (!FindRegisteredEntryByName_0200aa68(name, nameLength)) {
        FSArchive *tail = g_archiveList_020578ec;
        FSArchive **link = &g_archiveListLink_020578ec;

        while (tail != NULL) {
            link = &tail->next;
            tail = tail->next;
        }
        *link = arc;
        if (nameLength <= 3) {
            arc->name.pack = 0;
            Strlcpy_02010bcc(arc->name.ptr, name, nameLength + 1);
        } else if (nameLength <= 15) {
            int i;
            for (i = 0;; ++i) {
                if (i >= 16) {
                    RunResetCallbackAndIdle_02004cf0();
                } else if (data_020578fc[i][0] == '\0') {
                    Strlcpy_02010bcc(data_020578fc[i], name, nameLength + 1);
                    arc->name.longName = data_020578fc[i];
                    break;
                }
            }
        } else {
            RunResetCallbackAndIdle_02004cf0();
        }
        arc->flag |= 1;
        result = TRUE;
    }
    func_0200494c(savedState);
    return result;
}




