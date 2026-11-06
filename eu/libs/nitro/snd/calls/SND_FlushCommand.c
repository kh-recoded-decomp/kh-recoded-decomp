#define data_02057c50 gSoundCommandQueueState
#define data_02057c74 gSoundSubmittedCommandListsStorage
#define data_02057f20 gSoundCommandPoolPrefix
#include "eu/libs/nitro/os/os_interrupt_state.h"

#define audio_flush_reserved_commands_0200f080 SND_FlushCommand
#define func_0200e30c PXI_SendWordByFifo
#define func_0200eec0 SND_RecvCommandReply
#include "src/arm9/audio/audio_flush_reserved_commands_0200f080.c"
