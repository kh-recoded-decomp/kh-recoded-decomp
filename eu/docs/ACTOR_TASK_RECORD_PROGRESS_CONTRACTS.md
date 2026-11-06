# Actor-scene continuation and record-panel progress

These two names follow their native owners and consumers. Source declarations,
return conventions, algorithms, numeric bounds and shared ROOT implementations
are unchanged.

## ActorScene_IdleTaskUpdate

Identity: ov001:020882d4, Thumb, four bytes; existing `int name(void)` definition.
The native body is `movs r0,#0; bx lr` and consumes no logical input.

The owning gOverlayObjectSystemClass descriptor stores InitOverlayObjectSystem
at +4 and a work size of 0x3f20. Obj_Construct calls that initializer and stores its
returned callback at current task+0x14. The initializer publishes work as
`gActorSceneManager`, records the same task handle at manager+0x3ee4 and returns
the callable word 020882d5.

Obj_UpdateAll invokes task+0x14 and replaces that word only for a nonzero return.
Zero therefore leaves this idle callback installed. ActorManager_StartScene
loads manager+0x3ee4 and installs TryFinishIntroSequence through Obj_SetWord14;
RunEventScriptFrame installs TryShutdownActorSystem on that same task. The latter
returns 020882d5 when shutdown completes, restoring the idle continuation.

This is an active task that keeps its state until another operation replaces
its callback. Its zero is neither Boolean failure nor the runner's separate
suspension/destruction sentinels. Incidental incoming R0 contains the callback
address at BLX, not an evidenced task argument; no parameter is introduced.

The EU source is
`src/overlays/ov001/auto/ActorScene_IdleTaskUpdate.c`. Its shared four-byte
implementation retains the historical ROOT path
`src/ov001/library_nitro_fs/FSi_CloseFileCommand_020882ac.c`; the descriptor,
callers and runner establish its actor-scene role. The ROOT body stays intact.

## SetRecordPanelProgress

Identity: ov002:020674fc, ARM, 40 bytes. The existing setter clamps its input to
0..100 and writes seven packed bits starting at bit 0x9f0. Context command
0x80000007 dispatches that write; query 7 reads the same field.

RecordPanelClear raises the field to the selected index+1. Panel selection tests
progress against its cursor. Removing an earlier row decrements this field and
shifts later slots. These operations establish record-panel progress/index
threshold behavior. The clamp alone does not establish percentage units, and
these observations do not distinguish a cleared-row count from a maximal
frontier beyond the actual updates.

The source is `src/overlays/ov002/calls/SetRecordPanelProgress.c`. Its previous
SetClampedPercentValue name is retained only in historical shared source
spelling. No getter prototype, packed-field representation, clamp or comparison
is changed by this identifier correction.

## Validation

Five fresh official checks pass: both renamed functions, InitOverlayObjectSystem,
TryShutdownActorSystem and DispatchContextCommand. All five complete production
objects preserve allocated bytes/alignment, symbol layouts and relocation
targets/types/addends after the two name mappings. A fresh gate passes all 108
modules with identical hashes. No compiler flag, function argument or shared
ROOT body is changed.

```sh
python tools/verify_idx.py src/overlays/ov001/auto/ActorScene_IdleTaskUpdate.c ActorScene_IdleTaskUpdate --thumb
python tools/verify_idx.py src/overlays/ov002/calls/SetRecordPanelProgress.c SetRecordPanelProgress
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
