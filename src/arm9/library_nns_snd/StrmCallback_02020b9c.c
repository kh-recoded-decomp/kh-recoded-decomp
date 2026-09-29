#include "nitro/types.h"
#include "nitro/os.h"
#include "nnsys/fnd.h"

typedef struct StreamPlayer {
    u8 pad_000[0x124];
    volatile int commandCount;
} StreamPlayer;

typedef struct LoadCommand {
    NNSFndLink link;
    StreamPlayer *player;
    int status;
    int numChannels;
    void *buffer[6];
    u32 bufLen;
} LoadCommand;

typedef struct StreamThread {
    u8 pad_0000[0x10c0];
    OSThreadQueue threadQueue;
    u8 pad_10c8[0x18];
    NNSFndList commandList;
} StreamThread;

typedef struct StreamStatics {
    u32 unk_00;
    StreamThread *prepareThread;
} StreamStatics;

extern StreamThread g_strmThread_0205ecd0;
extern StreamStatics g_strmStatics_0205e324;

extern void *NNS_FndGetNextListObject_02012a38(NNSFndList *list, void *object);
extern void RemoveIntrusiveListObject_020129d8(NNSFndList *list, void *object);
extern void AppendIntrusiveListObject_020128d0(NNSFndList *list, void *object);
extern void OS_WakeupThread_02002af8(OSThreadQueue *queue);
extern void MI_CpuFill8_01ff8830(void *dest, u8 value, u32 size);
extern LoadCommand *AllocLoadCommand_02020a94(void);
extern void FreeLoadCommand_02020ad8(LoadCommand *command);

void StrmCallback_02020b9c(int status, int numChannels, void *buffer[], u32 len, int format, void *arg)
{
    StreamPlayer *player = (StreamPlayer *)arg;
    LoadCommand *command;
    StreamThread *thread;
    int channel;

    if (player->commandCount >= 2) {
        command = NULL;
        while ((command = (LoadCommand *)NNS_FndGetNextListObject_02012a38(&g_strmThread_0205ecd0.commandList, command)) != NULL) {
            if (command->player == player) {
                break;
            }
        }

        for (channel = 0; channel < command->numChannels; channel++) {
            MI_CpuFill8_01ff8830(command->buffer[channel], 0, command->bufLen);
        }

        RemoveIntrusiveListObject_020129d8(&g_strmThread_0205ecd0.commandList, command);
        player->commandCount--;
        FreeLoadCommand_02020ad8(command);
    }

    command = AllocLoadCommand_02020a94();

    command->player = player;
    command->status = status;
    command->numChannels = numChannels;
    for (channel = 0; channel < numChannels; channel++) {
        command->buffer[channel] = buffer[channel];
    }
    command->bufLen = len;

    thread = &g_strmThread_0205ecd0;
    if (status == 0 && g_strmStatics_0205e324.prepareThread) {
        thread = g_strmStatics_0205e324.prepareThread;
    }

    player->commandCount++;
    AppendIntrusiveListObject_020128d0(&thread->commandList, command);

    OS_WakeupThread_02002af8(&thread->threadQueue);
}
