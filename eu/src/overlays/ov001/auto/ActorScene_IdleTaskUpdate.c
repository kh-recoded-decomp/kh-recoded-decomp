/* Idle continuation of the actor-scene task created by gOverlayObjectSystemClass.
 * Returning zero retains the task callback until ActorManager_StartScene replaces
 * it. The shared four-byte implementation keeps its historical source path.
 * See docs/ACTOR_TASK_RECORD_PROGRESS_CONTRACTS.md. */
#define FSi_CloseFileCommand_020882ac ActorScene_IdleTaskUpdate
#include "src/ov001/library_nitro_fs/FSi_CloseFileCommand_020882ac.c"
