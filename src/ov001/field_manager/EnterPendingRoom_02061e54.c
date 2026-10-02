#include "nitro/types.h"

typedef struct RoomSlots {
    s16 current;
    s16 entry;
    s16 next;
    s16 nextEntry;
    u8 pad_08[4];
    u32 unk0 : 4;
    u32 forceReload : 1;
} RoomSlots;

typedef struct SessionAudio {
    u8 channel[0x81c];
    void *message;
} SessionAudio;

typedef struct SessionState {
    u8 pad_000[0x1b];
    u8 loading;
    u8 pad_01c[0x1ec];
    RoomSlots room;
    u8 pad_218[0x32];
    s16 loadedEntry;
    u8 pad_24c[0x1cc4];
    SessionAudio audio;
} SessionState;

extern SessionState *data_ov001_020a0460;
extern char data_ov001_0209e6f8[];
extern char data_ov001_0209e6b4[];
extern char data_ov001_0209e6c4[];
extern char data_ov001_0209e6d0[];
extern char data_ov001_0209e6d4[];
extern void StoreGlobalArrayEntry_02025668(int index, char *value);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);
extern void *OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void func_ov001_02063560(s32 index, void *value);
extern void LoadSessionArchiveResource_02062e30(void);
extern u16 LookupSessionKeyValue_02062e7c(int key);
extern void func_020257c4(void *channel, u32 source, u32 param);
extern void OpenSessionArchive_020635b0(char *name, char *flag);
extern void func_ov001_02064364(int id);
extern void func_ov001_020645e8(int flag);

int EnterPendingRoom_02061e54(void) {
    SessionState *state = data_ov001_020a0460;
    char name[32];
    BOOL changed;
    SessionAudio *audio = &state->audio;
    RoomSlots *room = &state->room;

    changed = TRUE;

    if (room->next == state->room.current) {
        changed = FALSE;
    }
    StoreGlobalArrayEntry_02025668(2, data_ov001_0209e6f8);
    room->current = room->next;
    room->entry = room->nextEntry;
    if (room->entry >= 0) {
        WriteSessionPackedBits_0206459c(0x3315, 10, room->entry);
    }
    if (changed) {
        if (room->next >= 1000) {
            OS_SPrintf_02002428(name, data_ov001_0209e6b4, room->next);
        } else {
            OS_SPrintf_02002428(name, data_ov001_0209e6c4, room->next);
        }
        audio->message = Msg_OpenContainerAndReadHeader_0202cc6c(name, 2, FALSE);
        func_ov001_02063560(0, audio->message);
        LoadSessionArchiveResource_02062e30();
        func_020257c4(audio, LookupSessionKeyValue_02062e7c(-1), 2);
        OpenSessionArchive_020635b0(data_ov001_0209e6d0, data_ov001_0209e6d4);
    } else {
        func_020257c4(audio, LookupSessionKeyValue_02062e7c(room->entry), 2);
        OpenSessionArchive_020635b0(NULL, data_ov001_0209e6d4);
        room->nextEntry = -1;
    }
    if (state->loadedEntry != room->entry || room->forceReload) {
        func_ov001_02064364(0x42);
    }
    data_ov001_020a0460->loading = 1;
    func_ov001_020645e8(0x3632);
    return 2;
}
