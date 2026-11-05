#include "nitro/types.h"

typedef void (*ModeHandler)(void);

typedef struct ModeHandlers {
    ModeHandler handlers[10];
} ModeHandlers;

extern void CreateResumeModeTask(void);
extern void IsResumeModeReady(void);
extern void ClearResumeModeReadyFlag(void);
extern void CompleteResumeModeWithResult(void);
extern void HasResumeModeTaskExitSignal(void);
extern void DestroyResumeModeTask(void);
extern void ResumeModeNoOpCallback(void);
extern void GetResumeModeResult(void);

void InstallResumeModeHandlers(ModeHandlers *table)
{
    table->handlers[0] = CreateResumeModeTask;
    table->handlers[1] = IsResumeModeReady;
    table->handlers[2] = ClearResumeModeReadyFlag;
    table->handlers[3] = CompleteResumeModeWithResult;
    table->handlers[4] = HasResumeModeTaskExitSignal;
    table->handlers[5] = DestroyResumeModeTask;
    table->handlers[6] = NULL;
    table->handlers[7] = ResumeModeNoOpCallback;
    table->handlers[8] = NULL;
    table->handlers[9] = GetResumeModeResult;
}
