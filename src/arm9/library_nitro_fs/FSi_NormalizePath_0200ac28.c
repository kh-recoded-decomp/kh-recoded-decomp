#include "nitro/types.h"

#define PATH_MAX_LENGTH 0x104

typedef struct FSArchive FSArchive;

typedef struct CurrentDirectory {
    FSArchive *archiveList;
    FSArchive *arc;
    u16 ownId;
    u16 index;
    u32 pos;
} CurrentDirectory;

extern CurrentDirectory g_currentDirectory_020578ec;
extern char g_currentDirectoryPath_020579fc[];
extern const char g_slashString_02055c28[];
extern FSArchive *FindRegisteredEntryByName_0200aa68(const char *name, int nameLength);
extern int func_0200abc8(char *dst, int dstSize, const char *src, int srcLength, BOOL *error);
extern int FindPrevSeparator_0200b31c(char *path, int pos);
extern int func_0200b350(char *path);

static inline BOOL IsSlash(u32 c) {
    return (c == '/') || (c == '\\');
}

static inline BOOL IsSjisLeadByte(int c) {
    return (unsigned int)((((u8)c) ^ 0x20) - 0xA1) < 0x3C;
}

static inline BOOL IsSjisTrailByte(int c) {
    return (c != 0x7F) && ((u8)(c - 0x40) <= 0xBC);
}

static inline BOOL IsSjisCharacter(const char *s) {
    return IsSjisLeadByte(s[0]) && IsSjisTrailByte(s[1]);
}

static inline int IncrementSjisPosition(const char *str, int pos) {
    return pos + 1 + IsSjisLeadByte(str[pos]);
}

FSArchive *FSi_NormalizePath_0200ac28(const char *path, u32 *baseId, char *relativePath) {
    FSArchive *arc = NULL;
    int pos = 0;
    BOOL error = FALSE;

    if (g_currentDirectory_020578ec.arc == NULL) {
        g_currentDirectory_020578ec.arc = g_currentDirectory_020578ec.archiveList;
        g_currentDirectory_020578ec.ownId = 0;
        g_currentDirectory_020578ec.pos = 0;
        g_currentDirectory_020578ec.index = 0;
        g_currentDirectoryPath_020579fc[0] = '\0';
    }
    if (IsSlash((u8)*path)) {
        arc = g_currentDirectory_020578ec.arc;
        ++path;
        if (baseId) {
            *baseId = 0;
        }
    } else {
        int i;
        for (i = 0;; i = IncrementSjisPosition(path, i)) {
            u32 c = (u8)path[i];
            if (!c || IsSlash(c)) {
                arc = g_currentDirectory_020578ec.arc;
                if (baseId) {
                    *baseId = g_currentDirectory_020578ec.ownId;
                }
                if (relativePath && g_currentDirectory_020578ec.ownId == 0 && g_currentDirectoryPath_020579fc[0] != '\0') {
                    pos += func_0200abc8(relativePath, PATH_MAX_LENGTH, g_currentDirectoryPath_020579fc, PATH_MAX_LENGTH, &error);
                    pos += func_0200abc8(relativePath + pos, PATH_MAX_LENGTH - pos, g_slashString_02055c28, 1, &error);
                }
                break;
            } else if (c == ':') {
                arc = FindRegisteredEntryByName_0200aa68(path, i);
                path += i + 1;
                if (IsSlash((u8)*path)) {
                    ++path;
                }
                if (baseId) {
                    *baseId = 0;
                }
                break;
            }
        }
    }
    if (relativePath) {
        int length = 0;
        while (!error) {
            char c = path[length];
            if (c != '\0' && !IsSlash((u8)c)) {
                length += IsSjisCharacter(&path[length]) ? 2 : 1;
            } else {
                if (length == 0) {
                } else if (length == 1 && path[0] == '.') {
                } else if (length == 2 && path[0] == '.' && path[1] == '.') {
                    if (pos > 0) {
                        --pos;
                    }
                    pos = FindPrevSeparator_0200b31c(relativePath, pos) + 1;
                } else {
                    pos += func_0200abc8(relativePath + pos, PATH_MAX_LENGTH - pos, path, length, &error);
                    if (c != '\0') {
                        pos += func_0200abc8(relativePath + pos, PATH_MAX_LENGTH - pos, g_slashString_02055c28, 1, &error);
                    }
                }
                if (c == '\0') {
                    break;
                }
                path += length + 1;
                length = 0;
            }
        }
        relativePath[pos] = '\0';
        func_0200b350(relativePath);
    }
    if (error) {
        arc = NULL;
    }
    return arc;
}
