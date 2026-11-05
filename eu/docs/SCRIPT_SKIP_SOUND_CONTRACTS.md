# Field/panel script skip and sound contracts

This block identifies 34 EU entrypoints from the matched bodies, the interpreter,
callback tables and their consumers. It describes behavior and native boundaries;
the names are descriptive rather than claims of original source spelling.
The verification section gives the official integration checks.
`InitSbcHandlersAndFastDma` belongs to the separately documented geometry block
and is not part of this inventory.

## The two VM owners

These offsets belong to two specific owners. The field VM starts at `+0x140` in
the object pointed to by the ActorManager singleton `data_ov001_020a0500`.
The panel VM starts at `+0x658` in `data_ov036_020c3940.work` (the work pointer
stored at holder `+4`). Partial local structs are views, not proven allocation
sizes or portable host layouts.

| Value | VM-relative | ActorManager singleton | Panel work |
|---|---:|---:|---:|
| Skip target pointer | 0x624 | 0x764 | 0xc7c |
| Skip-request word | 0x628 | 0x768 | 0xc80 |
| Executing-skip word | 0x62c | 0x76c | 0xc84 |
| Control word reset to 1 | 0x630 | 0x770 | 0xc88 |

`ResetScriptSkipState` clears the first three words, writes 1 to VM `+0x630`
and returns 1. Only that last word's literal/control behavior is established.
`RequestScriptSkipIfTargetSet` changes nothing when target is null; otherwise it
sets requested=1 and skipping=0. It neither advances the VM nor reports completion.
The runner observes these fields before entering `ScriptVm_FinishSkip`.

The same absolute offsets in individual actors from overlays 052/059 have other
owners and meanings; in particular actor `+0x764` can be an animation blend-table
pointer. Do not transplant the singleton VM layout into those actors.

Evidence: `src/arm9/audio/func_020258f8.c`,
`src/arm9/unclassified_helpers/func_02025cec.c`,
`src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c`,
`src/ov001/scripted_actor_behavior/RunEventScriptFrame_020884e0.c` and
`src/ov036/panel_state/RunPanelSubScriptFrame_020ba9d0.c`, interpreted through
EU wrappers and aliases.

## Request, advance and restore

Field and panel request helpers return the stored request word, not a general
success result. `RequestPanelScriptSkipAndSnapshotPositions` also snapshots the
current position pair for each of eight slots whose owner ID is not -1. It does
that snapshot even if the VM has no skip target.

`AdvanceFieldScriptSkipAndRestoreActors` runs the field VM and returns 0 while
its request word remains nonzero. Once clear, it restores each nonnull one of
512 actor slots, all three embedded party actors and the conditional camera
state, then returns 1. Calling it without a pending request can still perform
restoration. `AdvancePanelScriptSkipAndRestoreScene` likewise advances the panel
VM and restores BGM and graphics only once its request word is clear; that call
returns 1, otherwise 0.

The three current-scene adapters have different branch conditions:

- `RequestCurrentSceneScriptSkip` calls the field request when
  `GetSessionFlagsMask20()!=0`; otherwise it calls the panel request/snapshot
  directly. There is no additional state 8 guard on that second branch. The
  request result is discarded.
- `HasCurrentSceneScriptSkipTarget` first tests that mask and the field target,
  then tests `GetFieldSessionState()==8` and the panel target.
- `AdvanceCurrentSceneScriptSkip` first tries the field advance under that mask;
  if it does not return completed, it can still try the panel advance when the
  session state is 8. Other paths return 0. These are not an exclusive switch.

`UpdateSoundAndSceneScriptSkip` updates sound first. If the advance returns
nonzero, it clears `gPanelState+0xb8` and invokes callback slot 2. It does not
return a new completion status.

## BGM selection and panel restoration

`gScriptState` remains its native `u32` DATA owner initialized to `0xff`.
`SetScriptBgmSelection(u32 selection)` stores only the low 8 bits and returns the
complete original input word. `GetScriptBgmSelection` reads that byte as `s8`,
including -1 for 0xff. Neither operation is a playback query or BOOL interface.
Do not shrink the DATA object or normalize away the signed-byte conversion.

`SetPanelScriptBgmRequest(id,fade)` writes panel work `+0x10e0/+0x10e4`.
During restoration, the panel compares that requested ID with the signed cache.
A changed ID is queued only when it is -1 or greater than 1; a zero requested
fade becomes 20. Kind 4 receives the ID's low byte and the fade word, and the
cache is then updated. The native request helpers define the units of that fade;
this block does not relabel 20 as milliseconds. The session bit 0x3308/cache test,
main-brightness test, point-pair restoration and blend/clear-color branches all
remain observable parts of that panel operation.

There is a separate owner boundary in `ScriptVm_FinishSkip`: the shared source's
legacy `ScriptGlobals.busy` view reads `gScriptState+0x10`. The defining EU
source now uses an explicitly named `NativeScriptHandlerGuardView.handlerGroup3Word`
for the same native base/offset; its partial view is not a DATA allocation. The configured EU objects
are `gScriptState` at 0x02055e00 (one word), `gScriptHandlerTables` at 0x02055e04
(nine pointers), and the core table at 0x02055e28. Consequently that read is the
word of `gScriptHandlerTables[3]`, not a new busy field within the BGM cache.
Preserve the literal zero test and actual table ownership; a stronger lifecycle
meaning for that guard is not established here. A host representation should
read the real handler-table entry with its pointer type, rather than allocate a
20-byte BGM-cache object from the native address view. Slot/target cleanup after
this guarded section still executes for both values of the tested word. The engine's separate
`gBusyCounterState` is not this object. Evidence: `eu/config/arm9/symbols.txt`
and `src/arm9/shared_engine/ScriptVm_FinishSkip_0202599c.c:54`.

## Command and resume results

This is the field/panel `ScriptVm` protocol. Overlay021's stage interpreter has
a different result protocol and must not share this enum by analogy.
The header has group byte 0, table-entry byte 1, then a halfword whose low 11 bits
are command length in words. Operands begin at byte 4. `gScriptHandlerTables[0]`
selects the 33-entry core table; overlays install other groups.

For ordinary main-slot command execution in `ScriptVm_RunFrame`:

| Run result | Interpreter action |
|---:|---|
|0|Store the paired resume callback (possibly null), keep the cursor, and return 1 to the frame caller. A null resume means the command is retried on a later frame.|
|1|Clear the main resume callback, advance by the encoded length, and continue.|
|2|Clear the main resume callback and continue without the normal cursor advance.|
|3|Return0 without the normal cursor advance; this result does not itself reset the whole VM.|
|4|Unwind one nested frame and advance its caller, or set top-level status 2 and return 0.|
|5|Continue without the normal cursor advance.|
|6|Advance the cursor and return 1 to the frame caller.|

An installed main resume callback has its own handling:0 keeps waiting;1 advances
past the suspended command;2 clears the callback without the normal advance.
Auxiliary slots 1..10 are polled separately, and a nonzero result clears that slot
and saved argument. A nonzero header slot field, when not skipping, executes the
auxiliary path: run result 0 installs its resume/argument there, then the command
cursor advances. Do not apply the main-slot stop/wait rule to every callback
context or treat a returned1 as sound or I/O success.

The affected core entries are explicit in `eu/src/data/gScriptCommandTables.c`:

| Core entry | Run handler | Paired resume |
|---:|---|---|
|13|`ScriptCmd_SetPairAndTextResult`|None|
|14|`ScriptCmd_QueueSoundKind2`|None|
|15|`ScriptCmd_QueueSoundKind3`|None|
|16|`ScriptCmd_QueueSoundKind4`|None|
|17|`ScriptCmd_QueueSoundKind2AfterSequence`|`ScriptWait_QueueSoundKind2AfterSequence`|
|19|`ScriptCmd_PlaySequenceArcEntry`|None|
|20|`ScriptCmd_StopSequenceArc`|None|
|21|`ScriptCmd_QueueSequenceArcCommand`|None|
|22|`ScriptCmd_StartStream0AtZeroPosition`|None|
|25|`ScriptCmd_AcquireActorResource`|`ScriptWait_ActorResourceBinding`|
|28|`ScriptCmd_SetActorResourceFromTable`|`ScriptWait_ActorResourceBinding`|
|30|`ScriptCmd_RequestStreamSlot0Load`|`ScriptWait_StreamSlot0NotLoading`|

`ScriptCmd_SetPairAndTextResult` first resolves the third operand, then evaluates
the two integer operands. It writes VM status+0x1cc=0, pair+0x1d0/+0x1d4 and
text+0x1d8; absent text clears only its first byte, otherwise the copy is limited
to 63 bytes and byte 63 is terminated. Its return 3 is an interpreter result, not a
resource-ready or full-reset flag.

Actor-resource resume tokens are phase values. A nonnegative token waits for
request readiness, applies the binding and stores a negative token while still
returning0. A negative token finalizes the binding, clears the world shared-record
pointer and returns1; -99 represents actor 0. Skip cleanup releases the shared
record only for a nonnegative token and neither loops until idle nor clears that
pointer itself. Preserve this producer/resume/cleanup relationship.

## Streams and sound requests

`HasNonzeroStreamPlaybackPosition(index)` tests the SDK's integer millisecond
position against zero. A missing player returns0, and a valid stream at reported
position 0 also returns0. Therefore this is neither a complete playing predicate
nor a complete idle predicate. The SDK calculation uses the sample count and
sample rate; no new timing source is introduced.

`ScriptCmd_StartStream0AtZeroPosition` evaluates its ID operand first. A skip
request returns1 immediately. A nonzero reported position returns0 to the
interpreter; otherwise it invokes `PrepareAndStartStream(0,id)` and returns1,
discarding preparation success. `ScriptCmd_RequestStreamSlot0Load` also discards
the request result, but returns0 and has the explicit paired waiter. That waiter
checks only slot 0 state != 1; it does not prove successful preparation. The loader
sets state 1 when it accepts a request from state 0.

The pending sound queue has four native entries `{u8 kind,u8 arg,u16 value}`.
Kind 1 and kind 3 helpers coalesce only the newest pending entry of that same
kind. Kind 4 delegates to the existing queue/filter helper. Preserve 8/16-bit
narrowing and request order. Queue submission is not hardware completion, and
these numeric kind names intentionally avoid unproved sound-action labels.

## Native ABI work left separate

The native wrappers retain some incomplete legacy declarations. They are not a
finished portable C/C++ API:

- `SetScriptVmPackedBitHandlers` logically takes `(vm,writeHandler,readHandler)`;
  it writes the write callback at+0x644 and read callback at+0x640, substituting
  the corresponding global packed-bit function for each null input. The operand
  resolver's scratch is at+0x618 with its value word at+0x61c. Read/write callback
  signatures must follow the real dispatcher; their storage is not a loader hook.
- In `ScriptCmd_QueueSoundKind2` and `ScriptCmd_QueueSoundKind4`, the no-argument
  `IsSoundParamStale` declaration preserves live R0. The ROM passes the session
  state, or the zero skip-request word after the state 8 branch. Replacing it with
  the requested selection changes behavior.
- `ScriptCmd_QueueSoundKind2AfterSequence` passes `(vm,operands)` to the operand
  reader despite an old one-argument declaration. The cached-sequence predicate
  has no logical ID argument. Its resume callback receives a saved operand value,
  not a command pointer.
- `ScriptCmd_StopSequenceArc` evaluates all three operands even though the real
  callee uses only the first. `ScriptCmd_QueueSequenceArcCommand` evaluates two;
  its downstream four-word register interface, including unused/live register
  slots, remains incompletely recovered. Do not invent extra script operands.
- `QueueSoundKind4` keeps an integer native wrapper around the actual void queue
  backend. A leftover machine return word is not an established BOOL/success
  contract. C++ consumers, omitted inputs and unused slots remain Native ABI
  follow-up work; a rename alone does not make them portable.

Recover and verify typed interfaces as separate changes. This documentation adds
no register-forcing argument, assembly, host serialization or reconstruction
credit.

## Inventory of the 34 entrypoints

Identities below are EU bank+address, resolved from the plan's pinned baseline
`e72a267c96ac7e90c47728e397eadbac5c88ec66`; shared US filename suffixes are not
EU identities. Source/evidence paths are relative to the repository root.
The EU production wrapper for each row is `eu/` plus the path in the final column.

| EU identity / native mode | Name | Proven behavior and limit | Wrapper; evidence |
|---|---|---|---|
| `main:0204dee8` arm, 48B | `HasNonzeroStreamPlaybackPosition` | Returns NNS_SndArcStrmGetCurrentPlayingPos(handle) != 0. A valid stream at position 0 also returns false. This is not a complete playback-active test. | `src/calls/HasNonzeroStreamPlaybackPosition.c`; `src/arm9/audio/IsSoundStreamActive_0204ded4.c:1`, `src/arm9/library_nns_snd/NNS_SndArcStrmGetCurrentPlayingPos_02020320.c:1` |
| `main:0202590c` thumb, 28B | `ResetScriptSkipState` | Clears VM words +0x624/+0x628/+0x62c and sets +0x630 to 1. These are skipTarget, skipRequested and skipping. The purpose of +0x630 remains reserved/control state. No PCM role is established. | `src/calls/ResetScriptSkipState.c`; `src/arm9/audio/func_020258f8.c:1`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:32`, `src/ov001/scripted_actor_behavior/RunEventScriptFrame_020884e0.c:24` |
| `main:02025d00` thumb, 28B | `RequestScriptSkipIfTargetSet` | When VM.skipTarget is nonnull, sets skipRequested to 1 and skipping to 0. Requests the skip; it does not run or finish it. No action without a target. | `src/calls/RequestScriptSkipIfTargetSet.c`; `src/arm9/unclassified_helpers/func_02025cec.c:1`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:56` |
| `main:02025928` thumb, 52B | `SetScriptVmPackedBitHandlers` | Arguments are (vm,write,read): writes+644 and reads+640; each null input selects its matching global packed-bit default. These are script operand bit handlers, not file-loader completion callbacks. Use typed function pointers for a host interface. | `src/calls/SetScriptVmPackedBitHandlers.c`; `src/arm9/packed_bits/SetLoaderCallbacks_02025914.c:1`, `src/arm9/shared_engine/ScriptVm_ResolveOperand_02025d08.c:20` |
| `main:0202595c` thumb, 12B | `SetScriptBgmSelection` | Stores the low eight bits at gScriptState[0], but returns the complete input u32. Preserve low 8 storage, signed-byte getter and complete input-word return. It is not a busy flag or a BOOL; keep the u32 DATA owner. | `src/calls/SetScriptBgmSelection.c`; `eu/src/calls/SetScriptBgmSelection.c:1`, `eu/src/overlays/ov036/calls/AdvancePanelScriptSkipAndRestoreScene.c:65` |
| `main:02025968` thumb, 12B | `GetScriptBgmSelection` | Sign-extends the first byte of gScriptState. The consumer treats it as the cached script BGM selection; -1 is unset. It is not a hardware playback query. | `src/calls/GetScriptBgmSelection.c`; `src/arm9/shared_engine/LoadGlobalS8At0_02025954.c:1`, `eu/src/overlays/ov036/calls/AdvancePanelScriptSkipAndRestoreScene.c:65` |
| `ov036:020bd9a0` arm, 36B | `SetPanelScriptBgmRequest` | Stores two integers in the panel work at +0x10e0/+0x10e4. The same words are read as BGM ID and fade in the panel skip-restoration path. Exact owner: data_ov036_020c3940.work. No screen cursor coordinates. | `src/overlays/ov036/calls/SetPanelScriptBgmRequest.c`; `src/ov036/unclassified_helpers/SetSceneCursor_020bd980.c:3`, `eu/src/overlays/ov036/calls/AdvancePanelScriptSkipAndRestoreScene.c:30` |
| `ov001:02088844` thumb, 32B | `RequestFieldScriptSkip` | Requests skip for the VM at the actor-manager singleton +0x140, then returns singleton +0x768. Has a request side effect despite the old Get name. This mapping belongs only to singleton data_ov001_020a0500, not individual actors. | `src/overlays/ov001/calls/RequestFieldScriptSkip.c`; `src/ov001/object_creation/func_ov001_0208881c.c:3`, `src/ov001/scripted_actor_behavior/RunEventScriptFrame_020884e0.c:3`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:32` |
| `ov001:02088864` thumb, 28B | `HasFieldScriptSkipTarget` | Tests actor-manager singleton +0x764 for nonzero. This is VM.skipTarget at base +0x140 +0x624, not an actor count. Do not apply that owner layout to actors in overlays 052/059. | `src/overlays/ov001/calls/HasFieldScriptSkipTarget.c`; `src/ov001/object_creation/func_ov001_0208883c.c:3`, `src/ov001/scripted_actor_behavior/RunEventScriptFrame_020884e0.c:3` |
| `ov001:02088880` thumb, 132B | `AdvanceFieldScriptSkipAndRestoreActors` | Runs an event-script frame, waits for singleton skipRequested to clear, then restores 512 actor slots, three party actors and optional camera state. Returns zero while pending and one after restoration. Repeated calls with no request can still restore state; no universal actor activation meaning is inferred. | `src/overlays/ov001/calls/AdvanceFieldScriptSkipAndRestoreActors.c`; `src/ov001/object_creation/func_ov001_02088858.c:3` |
| `ov036:020bc600` arm, 104B | `RequestPanelScriptSkipAndSnapshotPositions` | Requests skip on the panel VM at work +0x658, snapshots position pairs for eight valid slots, and returns skipRequested at work +0xc80. The old name describes only the snapshot side effect. The exact owner is data_ov036_020c3940.work. | `src/overlays/ov036/calls/RequestPanelScriptSkipAndSnapshotPositions.c`; `src/ov036/panel_state/SnapshotActorSlotPositions_020bc5e0.c:23` |
| `ov036:020bc668` arm, 32B | `HasPanelScriptSkipTarget` | Tests the panel work pointer at +0xc7c. This is VM.skipTarget at work +0x658 +0x624, not an active-menu pointer. Exact owner only. | `src/overlays/ov036/calls/HasPanelScriptSkipTarget.c`; `src/ov036/unclassified_helpers/HasSceneActiveMenu_020bc648.c:3`, `src/ov036/panel_state/RunPanelSubScriptFrame_020ba9d0.c:3` |
| `ov036:020bc688` arm, 436B | `AdvancePanelScriptSkipAndRestoreScene` | Runs the panel VM frame. When skipRequested clears, reconciles BGM/fade/cache, restores scene points or blend/clear-color state, and returns one. Otherwise returns zero. Graphics and BGM restoration both matter. VM base +0x658 belongs only to this panel work, not an actor layout. | `src/overlays/ov036/calls/AdvancePanelScriptSkipAndRestoreScene.c`; `eu/src/overlays/ov036/calls/AdvancePanelScriptSkipAndRestoreScene.c:30` |
| `main:020284e4` thumb, 22B | `RequestCurrentSceneScriptSkip` | The field-state predicate selects the field skip request; otherwise it selects the panel skip request and position snapshot. The non-field branch has no additional mode-8 guard. Preserve dispatch and its discarded request result. | `src/calls/RequestCurrentSceneScriptSkip.c`; `src/arm9/reviewed_helpers/func_020284d0.c:1` |
| `main:020284fc` thumb, 46B | `HasCurrentSceneScriptSkipTarget` | Returns true for an active field with a field skip target, or mode 8 with a panel skip target. Checks target availability, not current skipping, menu activity or actor count. | `src/calls/HasCurrentSceneScriptSkipTarget.c`; `src/arm9/state_helpers/func_020284e8.c:1` |
| `main:0202852c` thumb, 46B | `AdvanceCurrentSceneScriptSkip` | Tries field advance under mask0x20, then can try state 8 panel advance if field did not complete; returns0/1. Other scene modes return false. This is not generic actor activation. | `src/calls/AdvanceCurrentSceneScriptSkip.c`; `src/arm9/unclassified_helpers/func_02028518.c:1` |
| `main:0202819c` thumb, 20B | `UpdateSoundAndSceneScriptSkip` | Updates sound, advances scene-script skip, and on completion clears panel +0xb8 and invokes callback slot 2. The completion notification is an observable effect. No new status result or polling loop is introduced. | `src/calls/UpdateSoundAndSceneScriptSkip.c`; `eu/src/calls/UpdateSoundAndSceneScriptSkip.c:1` |
| `main:02026590` thumb, 92B | `ScriptCmd_SetPairAndTextResult` | Resolves third operand before evaluating the two integers; writes status 0, pair and bounded text, then returns3. String type 0 clears only its first byte. Otherwise copies at most 63 bytes and terminates byte 63. Return 3 stops RunFrame without advancing the cursor; this is not a full VM reset. | `src/calls/ScriptCmd_SetPairAndTextResult.c`; `src/arm9/shared_engine/func_0202657c.c:1`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:96` |
| `main:020265ec` thumb, 72B | `ScriptCmd_QueueSoundKind2` | Reads a selection. In mode 8, stores the panel BGM request with fade 0 and returns early if skip is requested. Otherwise its predicate can update sound kind 2 and the low-byte cache. The ROM R0 discriminator passed to IsSoundParamStale is the scene mode, or skipRequested value 0 after the mode-8 branch; it is NOT the requested selection. The current empty-argument declaration preserves that live register. Confirm the live register in the overlay-qualified ROM call sequence. | `src/calls/ScriptCmd_QueueSoundKind2.c`; `src/arm9/shared_engine/func_020265d8.c:1`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:96` |
| `main:02026634` thumb, 68B | `ScriptCmd_QueueSoundKind3` | Reads a value. In mode 8, stores the panel BGM request (-1, value) and returns early if skip is requested. Otherwise sets the cache to -1 and queues/updates kind 3. The queue value narrows to 16 bits. No unproved fade/pause interpretation of kind 3 is needed for this name. | `src/calls/ScriptCmd_QueueSoundKind3.c`; `src/arm9/shared_engine/func_02026620.c:1`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:96` |
| `main:02026678` thumb, 88B | `ScriptCmd_QueueSoundKind4` | Reads two operands, records the panel BGM ID/fade in mode 8, then can queue kind 4 with the first operand narrowed to u8 and update the cache. Has the same live-R0 discriminator issue as func_020265ec. Do not replace that argument with the requested BGM ID. | `src/calls/ScriptCmd_QueueSoundKind4.c`; `src/arm9/shared_engine/func_02026664.c:1`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:96` |
| `main:020266d0` thumb, 52B | `ScriptCmd_QueueSoundKind2AfterSequence` | While the cached sequence plays, stores the operand in the VM resume-slot argument and returns 0. Otherwise updates the cache, queues kind 2 and returns 1. ReadOperandInt really receives (obj, cmd), despite the one-argument legacy declaration. IsCachedSeqPlaying takes no logical argument; do not invent an ID filter. | `src/calls/ScriptCmd_QueueSoundKind2AfterSequence.c`; `src/arm9/core_small/func_020266bc.c:1`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:96` |
| `main:02026704` thumb, 36B | `ScriptWait_QueueSoundKind2AfterSequence` | Paired resume callback: while the cached sequence plays returns 0; once it ends, uses its stored second argument to update the cache and kind 2, then returns 1. The pairing is explicit in core handler entry 17. The second word is a stored operand token, not a command pointer. | `src/calls/ScriptWait_QueueSoundKind2AfterSequence.c`; `src/arm9/core_small/func_020266f0.c:1`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:96` |
| `main:02026754` thumb, 52B | `ScriptCmd_PlaySequenceArcEntry` | Reads sequence-archive number and entry index. If VM.skipRequested is clear, calls PlaySoundChecked; returns 1. Does not return playback success. The +0x628 guard is a skip request, not a generic PCM flag. | `src/calls/ScriptCmd_PlaySequenceArcEntry.c`; `src/arm9/shared_engine/func_02026740.c:1`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:96` |
| `main:02026788` thumb, 48B | `ScriptCmd_StopSequenceArc` | Evaluates three operands and calls StopSeqArcOrDefault with the first. Returns 1. The other two operand reads are evaluated but ignored by the actual callee. Keep their side effects; do not invent fade/delay arguments. | `src/calls/ScriptCmd_StopSequenceArc.c`; `src/arm9/core_small/func_02026774.c:1`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:96` |
| `main:020267b8` thumb, 32B | `ScriptCmd_QueueSequenceArcCommand` | Evaluates two operands, retains the first sequence-archive number, calls QueueSoundCommandForArc and returns 1. Keep the second operand read. The callee has an incompletely recovered four-word ABI with live R2/R3 values; do not invent logical arguments or claim successful loading. | `src/calls/ScriptCmd_QueueSequenceArcCommand.c`; `src/arm9/core_small/func_020267a4.c:1`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:96` |
| `main:020267d8` thumb, 56B | `ScriptCmd_StartStream0AtZeroPosition` | Reads a stream ID. If skip is requested returns 1. If stream 0 playback position is nonzero returns 0. Otherwise calls PrepareAndStartStream(0, ID) and returns 1. Position zero can also mean a newly started valid stream. The preparation-success result is discarded; do not strengthen this into a complete idle check. | `src/calls/ScriptCmd_StartStream0AtZeroPosition.c`; `src/arm9/shared_engine/func_020267c4.c:1`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:96` |
| `main:02026974` thumb, 26B | `ReleasePendingScriptActorResource` | For a nonnegative resume token, calls the loader idle-sleep helper and releases VM.world.sharedRecord. The token is only a phase guard, not an array index. A negative token means the resource has already been applied. The cleanup does not clear the pointer or loop until idle. | `src/calls/ReleasePendingScriptActorResource.c`; `src/arm9/shared_records/func_02026960.c:1`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:96` |
| `main:02026ab0` thumb, 20B | `ScriptWait_StreamSlot0NotLoading` | Returns whether stream-load slot 0 state is not 1. RequestSoundSlotLoad sets state 1 when queuing. True includes state 0 and every other non-1 state; successful preparation is not implied. Paired with the slot-0 load command. | `src/calls/ScriptWait_StreamSlot0NotLoading.c`; `src/arm9/unclassified_helpers/func_02026a9c.c:1`, `src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:96` |
| `main:0204d7c4` arm, 68B | `QueueOrUpdateSoundKind1` | If the newest pending entry is kind 1, updates its u8 argument. Otherwise appends kind 1, value, 0. Returns 1. Coalesces only the newest entry, not all queued requests. The numeric kind is retained rather than inventing an unproved action name. | `src/calls/QueueOrUpdateSoundKind1.c`; `src/arm9/state_management/func_0204d7b0.c:1`, `src/arm9/audio/PushSoundQueueEntry_0204ce84.c:1` |
| `main:0204d808` arm, 68B | `QueueOrUpdateSoundKind3` | If the newest pending entry is kind 3, updates its u16 value. Otherwise appends kind 3, 0, value. The value is narrowed to 16 bits and only the newest matching entry is coalesced. | `src/calls/QueueOrUpdateSoundKind3.c`; `src/arm9/runtime_data_utilities/func_0204d7f4.c:1`, `src/arm9/audio/PushSoundQueueEntry_0204ce84.c:1` |
| `main:0204d8cc` arm, 24B | `QueueSoundKind4` | Forwards to QueueSoundRequest with kind 4 and the two input words. No synchronous completion or stable BOOL return: the real queue backend is void and filters/coalesces requests. | `src/calls/QueueSoundKind4.c`; `src/arm9/shared_engine/func_0204d8b8.c:1`, `src/arm9/audio/PushSoundQueueEntry_0204ce84.c:1` |
| `main:0202690c` thumb, 102B | `ScriptWait_ActorResourceBinding` | A nonnegative actor token waits for loading and applies the resource. A negative token finalizes the binding, clears the shared-record slot and returns 1. -99 encodes actor 0. This is the resume callback for actor-resource acquisition/binding, not an actor turn or angle operation. | `src/calls/ScriptWait_ActorResourceBinding.c`; `src/arm9/unclassified_helpers/func_020268f8.c:1`, `src/arm9/shared_engine/ScriptCmd_AcquireActorResource_02026854.c:31`, `eu/src/data/gScriptCommandTables.c:69` |
| `main:02026a9c` thumb, 18B | `ScriptCmd_RequestStreamSlot0Load` | Reads one operand, calls RequestSoundSlotLoad(0, value) and returns 0. The request result is discarded; a waiter can be installed even when the request was rejected. This is not generic event posting. | `src/calls/ScriptCmd_RequestStreamSlot0Load.c`; `src/arm9/shared_engine/ScriptCmd_PostEvent0_02026a88.c:1`, `src/arm9/audio/RequestSoundSlotLoad_0204ddc4.c:1` |

The prior numeric/descriptive identities remain traceable in configuration
history and the shared implementation paths. `InitSbcHandlersAndFastDma` was
integrated separately; it is not one of these 34 entrypoints. Native source
filenames and stale private field labels are not evidence for their old meanings.

## Verification

From `eu/`:

```sh
python tools/verify_idx.py src/calls/HasNonzeroStreamPlaybackPosition.c HasNonzeroStreamPlaybackPosition
python tools/verify_idx.py src/calls/ResetScriptSkipState.c ResetScriptSkipState --thumb
python tools/verify_idx.py src/calls/RequestScriptSkipIfTargetSet.c RequestScriptSkipIfTargetSet --thumb
python tools/verify_idx.py src/calls/SetScriptVmPackedBitHandlers.c SetScriptVmPackedBitHandlers --thumb
python tools/verify_idx.py src/calls/SetScriptBgmSelection.c SetScriptBgmSelection --thumb
python tools/verify_idx.py src/calls/GetScriptBgmSelection.c GetScriptBgmSelection --thumb
python tools/verify_idx.py src/overlays/ov036/calls/SetPanelScriptBgmRequest.c SetPanelScriptBgmRequest
python tools/verify_idx.py src/overlays/ov001/calls/RequestFieldScriptSkip.c RequestFieldScriptSkip --thumb
python tools/verify_idx.py src/overlays/ov001/calls/HasFieldScriptSkipTarget.c HasFieldScriptSkipTarget --thumb
python tools/verify_idx.py src/overlays/ov001/calls/AdvanceFieldScriptSkipAndRestoreActors.c AdvanceFieldScriptSkipAndRestoreActors --thumb
python tools/verify_idx.py src/overlays/ov036/calls/RequestPanelScriptSkipAndSnapshotPositions.c RequestPanelScriptSkipAndSnapshotPositions
python tools/verify_idx.py src/overlays/ov036/calls/HasPanelScriptSkipTarget.c HasPanelScriptSkipTarget
python tools/verify_idx.py src/overlays/ov036/calls/AdvancePanelScriptSkipAndRestoreScene.c AdvancePanelScriptSkipAndRestoreScene
python tools/verify_idx.py src/calls/RequestCurrentSceneScriptSkip.c RequestCurrentSceneScriptSkip --thumb
python tools/verify_idx.py src/calls/HasCurrentSceneScriptSkipTarget.c HasCurrentSceneScriptSkipTarget --thumb
python tools/verify_idx.py src/calls/AdvanceCurrentSceneScriptSkip.c AdvanceCurrentSceneScriptSkip --thumb
python tools/verify_idx.py src/calls/UpdateSoundAndSceneScriptSkip.c UpdateSoundAndSceneScriptSkip --thumb
python tools/verify_idx.py src/calls/ScriptCmd_SetPairAndTextResult.c ScriptCmd_SetPairAndTextResult --thumb
python tools/verify_idx.py src/calls/ScriptCmd_QueueSoundKind2.c ScriptCmd_QueueSoundKind2 --thumb
python tools/verify_idx.py src/calls/ScriptCmd_QueueSoundKind3.c ScriptCmd_QueueSoundKind3 --thumb
python tools/verify_idx.py src/calls/ScriptCmd_QueueSoundKind4.c ScriptCmd_QueueSoundKind4 --thumb
python tools/verify_idx.py src/calls/ScriptCmd_QueueSoundKind2AfterSequence.c ScriptCmd_QueueSoundKind2AfterSequence --thumb
python tools/verify_idx.py src/calls/ScriptWait_QueueSoundKind2AfterSequence.c ScriptWait_QueueSoundKind2AfterSequence --thumb
python tools/verify_idx.py src/calls/ScriptCmd_PlaySequenceArcEntry.c ScriptCmd_PlaySequenceArcEntry --thumb
python tools/verify_idx.py src/calls/ScriptCmd_StopSequenceArc.c ScriptCmd_StopSequenceArc --thumb
python tools/verify_idx.py src/calls/ScriptCmd_QueueSequenceArcCommand.c ScriptCmd_QueueSequenceArcCommand --thumb
python tools/verify_idx.py src/calls/ScriptCmd_StartStream0AtZeroPosition.c ScriptCmd_StartStream0AtZeroPosition --thumb
python tools/verify_idx.py src/calls/ReleasePendingScriptActorResource.c ReleasePendingScriptActorResource --thumb
python tools/verify_idx.py src/calls/ScriptWait_StreamSlot0NotLoading.c ScriptWait_StreamSlot0NotLoading --thumb
python tools/verify_idx.py src/calls/QueueOrUpdateSoundKind1.c QueueOrUpdateSoundKind1
python tools/verify_idx.py src/calls/QueueOrUpdateSoundKind3.c QueueOrUpdateSoundKind3
python tools/verify_idx.py src/calls/QueueSoundKind4.c QueueSoundKind4
python tools/verify_idx.py src/calls/ScriptWait_ActorResourceBinding.c ScriptWait_ActorResourceBinding --thumb
python tools/verify_idx.py src/calls/ScriptCmd_RequestStreamSlot0Load.c ScriptCmd_RequestStreamSlot0Load --thumb
python tools/verify_idx.py src/calls/ScriptVm_FinishSkip.c ScriptVm_FinishSkip --thumb
bash tools/gate.sh
```

Integration preserves baseline objects and compares production texts, resolved
relocation targets/types and addends. It requires unchanged hashes for all 108
linked modules. The extra FinishSkip check retains its 380-byte Thumb body while
correcting the private guard's meaning. Shared US code, the four-byte BGM-cache
owner, nine-pointer table owner and interpreter algorithms remain unchanged.
