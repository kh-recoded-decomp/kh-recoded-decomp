# Field-script delegation commands

This block identifies 22 existing entries in `gFieldScriptCommandHandlers`.
Each name is supported by its decoded operand, actual EU callee body and handler
table reference. Old shared-source labels such as `ScriptCmd_EnterPhase`,
`CmdOpenDialog` and `FS_UnloadOverlayImage` are not evidence of those behaviors.

## Recovered bindings

Slot is the zero-based word position in the existing handler table, not a
claim about the full external script opcode encoding. Operand decoding occurs
inside the handler only where indicated.

| Previous symbol | Current name | Table slot | Decoder / narrowing | Returned word |
|---|---|---:|---|---:|
| `func_ov001_02064ecc` | `ScriptCmd_LoadSceneTable` | 34 | `ScriptVm_ReadOperandInt` | 1 |
| `func_ov001_02064edc` | `ScriptCmd_EnterMenuItem` | 8 | `ScriptVm_ReadOperandInt` | 1 |
| `func_ov001_020651f0` | `ScriptCmd_StartSessionScene` | 22 | `ByteCode_ResolveOperand` | 0 |
| `func_ov001_02065438` | `ScriptCmd_ShowSessionNameEntry` | 44 | `ScriptVm_ReadOperandInt` | 1 |
| `func_ov001_020655e8` | `ScriptCmd_HandleFieldPanelCommand` | 74 | `ScriptVm_ReadOperandInt` | 1 |
| `func_ov001_02065638` | `ScriptCmd_LoadCameraParams` | 80 | `ByteCode_ResolveOperand` | 1 |
| `func_ov001_02065680` | `ScriptCmd_OpenFieldMenuMode` | 84 | `ScriptVm_ReadOperandInt` | 1 |
| `func_ov001_02065690` | `ScriptCmd_SetSceneLock` | 86 | `ScriptVm_ReadOperandInt` | 1 |
| `func_ov001_020656c4` | `ScriptCmd_ClearSceneEntry` | 90 | `ScriptVm_ReadOperandInt` | 1 |
| `func_ov001_0206576c` | `ScriptCmd_ResetStageOriginIfActive` | 96 | `None here` | 1 |
| `func_ov001_020658b8` | `ScriptCmd_ResetOverlaySelection` | 106 | `None here` | 1 |
| `func_ov001_02065910` | `ScriptCmd_LoadCenteredScreenSprite` | 110 | `ScriptVm_ReadOperandInt` | 1 |
| `func_ov001_02065950` | `ScriptCmd_AdvanceRecordStep` | 114 | `None here` | 1 |
| `func_ov001_020659b4` | `ScriptCmd_AddStageSlotLock1` | 120 | `ScriptVm_ReadOperandInt; u16` | 1 |
| `func_ov001_020659c8` | `ScriptCmd_TryActivateStageSlot` | 122 | `ScriptVm_ReadOperandInt; u16` | 1 |
| `func_ov001_02065a28` | `ScriptCmd_SaveCurrentSpawnPoint` | 132 | `ScriptVm_ReadOperandInt` | 1 |
| `func_ov001_02065a54` | `ScriptCmd_SetMenuHighlight` | 136 | `ScriptVm_ReadOperandInt` | 1 |
| `func_ov001_02065c10` | `ScriptCmd_BindScriptHandlersSlot7` | 148 | `ScriptVm_ReadOperandInt` | 1 |
| `func_ov001_02065c4c` | `ScriptCmd_AllocSessionNameTable` | 152 | `ScriptVm_ReadOperandInt` | 1 |
| `func_ov001_02065dbc` | `ScriptCmd_CommitChapterClearRecords` | 50 | `None here` | 1 |
| `func_ov001_02065f20` | `ScriptCmd_ClearSessionStateWords` | 178 | `None here` | 1 |
| `func_ov001_02065f80` | `ScriptCmd_ResetGaugeDisplay` | 186 | `None here` | 1 |

## Callee evidence

- `ScriptCmd_LoadSceneTable` delegates to `LoadSceneTable`: Loads the scene archive/table, relocates its entry pointers, copies per-entry UTF-16 names/title and sets currentId.
- `ScriptCmd_EnterMenuItem` delegates to `EnterMenuItem`: Sets selected menu item, clears cursor/scroll/history, marks redraw and allocates/synchronizes its panels.
- `ScriptCmd_StartSessionScene` delegates to `StartSessionScene`: Builds a named SceneRequest, pauses entries, resets stage links/origin, starts ActorManager scene and sets session flag 0x20.
- `ScriptCmd_ShowSessionNameEntry` delegates to `ShowSessionNameEntry`: Selects name from session name table, converts to UCS-2 and draws popup/header, updating packed last-name index.
- `ScriptCmd_HandleFieldPanelCommand` delegates to `HandleFieldPanelCommand`: Switches integer command 0..4 over panel-open transitions, panel mode helper and pending-panel state.
- `ScriptCmd_LoadCameraParams` delegates to `LoadCameraParams`: Uses resolved name to look up archive camera resource, replaces current resource and applies movie camera settings.
- `ScriptCmd_OpenFieldMenuMode` delegates to `OpenFieldMenuMode`: Maps requested menu kind to mode, flags pending open, pauses field entries and marks menu highlight; has busy/menu-lock exits.
- `ScriptCmd_SetSceneLock` delegates to `SetSceneLock`: Writes movie scene locked byte and calls camera enable helper with inverse of its zero/nonzero value.
- `ScriptCmd_ClearSceneEntry` delegates to `ClearSceneEntry`: Clears selected movie-scene entry ID, then calls camera mode helper with 1.
- `ScriptCmd_ResetStageOriginIfActive` delegates to `ResetStageOriginIfActive`: Calls ResetStageOrigin only when g_stageEventsState != -1.
- `ScriptCmd_ResetOverlaySelection` delegates to `ResetOverlaySelection`: Stores stepIndex=-1 in ov031 state, advances step and updates menu presentation through existing helper.
- `ScriptCmd_LoadCenteredScreenSprite` delegates to `LoadCenteredScreenSprite`: Selects fixed variant mapping, loads corresponding texture, marks visible and copies centered sprite position.
- `ScriptCmd_AdvanceRecordStep` delegates to `AdvanceRecordStep`: Increments ov031 stepIndex, dispatches stepCodes[index] when in range, otherwise advances record/end or backs index down.
- `ScriptCmd_AddStageSlotLock1` delegates to `StageEvent_SetHoldBit1`: When stage events active, calls AddStageSlotLock1 -> AddStageSlotLocks(index,1). AddStageSlotLocks ORs lockMask and marks active/pending when state==2.
- `ScriptCmd_TryActivateStageSlot` delegates to `TryActivateStageSlot`: When stage events active, calls ActivateStageSlot; valid index sets slot.active=1 and slot.pending=0.
- `ScriptCmd_SaveCurrentSpawnPoint` delegates to `SaveCurrentSpawnPoint`: Copies indexed current position/angle to saved position/angle in session.
- `ScriptCmd_SetMenuHighlight` delegates to `SetMenuHighlight`: If menu context exists, replaces flag mask 4 based on enable and calls menu-open/reset-request helpers.
- `ScriptCmd_BindScriptHandlersSlot7` delegates to `BindScriptHandlersSlot7`: Binds selected table entry into global handler slot 7, optionally loads its overlay and records index.
- `ScriptCmd_AllocSessionNameTable` delegates to `AllocSessionNameTable`: Stores count byte, allocates count*4 name-pointer words and clears their storage.
- `ScriptCmd_CommitChapterClearRecords` delegates to `CommitChapterClearRecords`: Copies/clamps current chapter clear count/time into best records and updates chapter flags under established mode conditions.
- `ScriptCmd_ClearSessionStateWords` delegates to `ClearSessionStateWords`: Zeros exactly three 32-bit session state words at +0x27a8, +0x27ac and +0x27b0; their individual meanings remain unresolved.
- `ScriptCmd_ResetGaugeDisplay` delegates to `ResetGaugeDisplay`: Resets displayed level/gauge/max flag, selects menu mode and either blends tiles or queues resource 5.

## Decoding, returns and native interface

`ScriptVm_ReadOperandInt` resolves an operand and returns its payload only for
resolved type 1, otherwise zero. `ByteCode_ResolveOperand` is used for the
name/resource paths in `LoadCameraParams` and `StartSessionScene`, retaining
relative-pointer and language-selection handling. Those two commands must not
be ported as integer-ID commands merely because their old declarations use
32-bit words.

The stage slot lock and activation handlers explicitly narrow their decoded
index to `u16`. The lock operation adds mask 1 through the stage-event helper;
it does not replace all existing locks. Their original guards remain in the
callees. None of these wrappers adds independent bounds or lifetime checks.

Twenty-one handlers return 1 after delegation; `ScriptCmd_StartSessionScene`
returns 0. The delegated helper's return value is discarded. A return of 1 is
therefore not a propagated allocation/load result, and the zero return must not
be normalized to match the other wrappers. This block does not infer a complete
VM scheduling protocol from these two values alone.

Commands marked with no decoder retain their established forwarding behavior.
Several shared templates pass a native argument word to a helper that has no
logical input through an erased declaration. Do not invent meanings for that
word or additional VM parameters to make the source look uniform.

The handler table still exposes `void(void)` entries and the shared templates
retain their existing compiled declarations. These renames do not make that an
appropriate host dispatch type. Recover the dispatcher and each command's real
argument/result contract before replacing the table with a host function-pointer
interface. EU aliases preserve the unchanged shared US source identities; a
shared file's directory name does not establish which subsystem is called.

`LoadCameraParams`, `SetSceneLock` and `ClearSceneEntry` use overlay 30's scene
state. `ResetOverlaySelection` and `AdvanceRecordStep` use overlay 31. Treat
an overlay and its load lifetime as part of a callback's identity in a port;
overlays reuse native address ranges.

## Reproduction

From `eu/`, refresh proven relocation spellings before checking a renamed unit:

```sh
python tools/rebuild_index.py --write --refresh-reloc-names
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_LoadSceneTable.c ScriptCmd_LoadSceneTable --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_StartSessionScene.c ScriptCmd_StartSessionScene --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_AddStageSlotLock1.c ScriptCmd_AddStageSlotLock1 --thumb
bash tools/gate.sh
```

All 22 command functions are checked with the official byte/relocation verifier.
The fresh linked gate also checks the handler table and all affected callers.
Naming adds no C or DATA reconstruction credit.
