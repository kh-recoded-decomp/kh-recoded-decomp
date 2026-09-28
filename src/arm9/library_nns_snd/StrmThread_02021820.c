#include "nitro/types.h"
#include "nitro/os.h"
#include "nnsys/snd.h"

typedef struct LoadCommand {
    NNSFndLink link;
    NNSSndStrmPlayer *player;
    NNSSndStrmCallbackStatus status;
    int numChannels;
    void *buffer[6];
    u32 bufLen;
} LoadCommand;

typedef struct StrmThreadState {
    u8 pad_thread[0xc0];
    u8 stack[0x1000];
    OSThreadQueue threadQ;
    OSMutex mutex;
    NNSFndList commandList;
} StrmThreadState;

extern void SleepCurrentThread_02002aa8(OSThreadQueue *queue);
extern void func_02003158(OSMutex *mutex);
extern void ReleaseSyncObject_020031a8(void *obj);
extern LoadCommand *DequeueStreamLoadCommand_02020a44(NNSFndList *commandList);
extern void func_02020e14(LoadCommand *command);
extern void func_02020ad8(LoadCommand *command);

/* NitroSystem sndarc_stream.c: StrmThread */
void StrmThread_02021820(StrmThreadState *thread)
{
    LoadCommand *command;

    while (TRUE) {
        SleepCurrentThread_02002aa8(&thread->threadQ);

        while (TRUE) {
            func_02003158(&thread->mutex);

            command = DequeueStreamLoadCommand_02020a44(&thread->commandList);
            if (command == NULL) {
                ReleaseSyncObject_020031a8(&thread->mutex);
                break;
            }

            func_02020e14(command);
            func_02020ad8(command);
            ReleaseSyncObject_020031a8(&thread->mutex);
        }
    }
}
