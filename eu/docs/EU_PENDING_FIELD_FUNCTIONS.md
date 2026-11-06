# Overlay 001 functions retained for further evidence

These 16 native EU functions retain address-based names. The available evidence
establishes the mechanics listed here but does not yet justify a stable semantic
name or a complete public type contract. Each entry identifies the actual EU
source, the precise unresolved point and the next useful proof. This ledger is
intended to keep a later port from inheriting guessed gameplay labels, erased
callback signatures or misleading partial structure members.

The identity is overlay bank plus native address. Thumb entrypoints have an
odd callable pointer, while the displayed address is even. Source paths are
repository-relative and point to the current EU wrapper. An included shared
source can contain different regional addresses; its spelling or template
comments do not establish the EU contract. Native offsets and numeric values
are preserved explicitly in the observations.

No missing return type, pointer ownership, index bound, mode/flag meaning or
callback purpose should be filled in from a neighboring function's name alone.
An empty callback can be behaviorally known while its registration role remains
unresolved. A constant return has different meanings in the VM, task scheduler,
controller state machine and ordinary callback protocols; the next-proof column
keeps those distinctions concrete.

## Session state, script bridges and resource requests

| EU identity and native size | Current EU source | Observed mechanical contract | Semantic blocker | Next proof |
|---|---|---|---|---|
| ov001:0x0206312c (Thumb, 0x2 bytes) | `eu/src/overlays/ov001/auto/func_ov001_0206312c.c` | Empty helper called by script wrapper 0x02064e5c. | No descriptor or asset evidence establishes intentional semantic purpose. | Trace original command usage and any address-taken registrations beyond the C wrapper. |
| ov001:0x0206339c (Thumb, 0x2 bytes) | `eu/src/overlays/ov001/auto/func_ov001_0206339c.c` | Empty helper called by script wrapper 0x02064ec0. | No semantic role proven for this placeholder implementation. | Trace descriptor/provenance and original script usage before assigning a purpose. |
| ov001:0x02064e5c (Thumb, 0xa bytes) | `eu/src/overlays/ov001/calls/func_ov001_02064e5c.c` | Calls empty helper 0x0206312c and returns 1; descriptor identifies a script command slot. | Purpose/reservation of an empty command cannot be inferred from a no-op body. | Inspect opcode usage in script bytecode and neighboring descriptor lifecycle before assigning a reserved/no-op contract. |
| ov001:0x02064ec0 (Thumb, 0xa bytes) | `eu/src/overlays/ov001/calls/func_ov001_02064ec0.c` | Calls empty helper 0x0206339c and returns 1. | No body work or consumer establishes semantic command purpose. | Inspect opcode descriptor and bytecode usage rather than naming from an unused input or neighboring command. |
| ov001:0x02065a24 (Thumb, 0x4 bytes) | `eu/src/overlays/ov001/auto/func_ov001_02065a24.c` | Group 2 opcode 0x41 run handler, null resume, constant return 0. MAIN retains this command; an auxiliary path can advance it. | Intentional use of this non-advancing command is unknown; Yield would misdescribe MAIN behavior. | Find group-2 opcode 0x41 bytecode users and VM context before naming indefinite wait or reserved halt. |
| ov001:0x02065f04 (Thumb, 0x1c bytes) | `eu/src/overlays/ov001/calls/func_ov001_02065f04.c` | ORs session +0x27b6 with mask 0x20 and returns 1. | No consumer establishes the role of this bit. | Find every mask-0x20 reader/writer of this exact owner field, including clearing/transition cases. |

## Stage/group records and small services

| EU identity and native size | Current EU source | Observed mechanical contract | Semantic blocker | Next proof |
|---|---|---|---|---|
| ov001:0x02068980 (Thumb, 0x2 bytes) | `eu/src/overlays/ov001/auto/func_ov001_02068980.c` | Empty callee of ScriptOp_SendPayloadWords with(id,temporary words,bytecount). | Payload transport feature and disabled/optional intent are unknown. | Trace original script opcode assets and any native address-taken registrations; no packet/network/queue label based on parameters alone. |

## Managed actors, contact state and HUD resources

| EU identity and native size | Current EU source | Observed mechanical contract | Semantic blocker | Next proof |
|---|---|---|---|---|
| ov001:0x0206dc98 (Thumb, 0x14 bytes) | `eu/src/overlays/ov001/calls/func_ov001_0206dc98.c` | Clears event work +0xf8 when the owner exists; invoked by RefreshStageEntriesIfLoaded only with its manager present. | No writer or consumer establishes the meaning of event-work +0xf8. | Trace all native reads/writes of event work +0xf8 and their initialization; do not borrow the caller name as a field role. |
| ov001:0x0206df78 (Thumb, 0x44 bytes) | `eu/src/overlays/ov001/calls/func_ov001_0206df78.c` | Conditionally sets session flag 0x3707, increments counter category 6, then increments packed save field 0xb26/17 bits with cap 99999. Used by HandleRewardActorCommand and SelectMenuMember. | Neither numeric stat category nor saved field has a proven localized/stat consumer. | Trace save field 0xb26 and category 6 to displayed stat or command case/assets before naming a gameplay event. |
| ov001:0x0206e2b0 (Thumb, 0x20 bytes) | `eu/src/overlays/ov001/calls/func_ov001_0206e2b0.c` | True precisely for session-kind byte 7 and session flag 0x370d. Consumers include ledge/glide, model and action paths. | Kind 7 and flag 0x370d have no semantic enum/writer proof. | Resolve their constructors and flag setters against assets or mode dispatch; do not guess a character/form label. |
| ov001:0x0206e31c (Thumb, 0x20 bytes) | `eu/src/overlays/ov001/calls/func_ov001_0206e31c.c` | True precisely for session-kind byte 6 and session flag 0x3715. Actor 053 resource, animation and music consumers test it. | The mode/flag combination is observed but its named gameplay role is not proved. | Link kind 6 and flag 0x3715 writers to selected resources/assets before assigning a character or form name. |

## Menu, notice and panel callback states

| EU identity and native size | Current EU source | Observed mechanical contract | Semantic blocker | Next proof |
|---|---|---|---|---|
| ov001:0x0207abd8 (Thumb, 0x2 bytes) | `eu/src/overlays/ov001/auto/func_ov001_0207abd8.c` | Empty slot0 of gMenuOverlayStateHandlers. Dispatcher supplies panel work and ignores its return. InitFieldPanelScene zero-fills then sets phase2 synchronously before dispatch. RequestPanelModeChange accepts0/6 with a separate +0x38 guard. | No persistent same-owner phase0 transition reaching the dispatcher is established. | Find a writer of panel+0x30=0 whose result reaches dispatch, or an explicit descriptor contract; see [the phase review](FIELD_CALLBACK_PHASE_CONTRACTS.md). |

## Field-object classes and pool callbacks

| EU identity and native size | Current EU source | Observed mechanical contract | Semantic blocker | Next proof |
|---|---|---|---|---|
| ov001:0x020846b8 (Thumb, 0x14 bytes) | `eu/src/overlays/ov001/calls/func_ov001_020846b8.c` | Type9 class hook14 calls SetPackedStateLowBit(actor,1), writes actor +0x82=1, returns 0. | Hook14 callback purpose and actor byte 0x82 have no consumer proof. | Trace actual hook14 dispatcher and byte 0x82 reader in PatrolObject update before labeling activation/state transition. |
| ov001:0x020876d4 (Thumb, 0x2 bytes) | `eu/src/overlays/ov001/auto/func_ov001_020876d4.c` | Empty operation called by five scene draw/leave callbacks, guarded by scene flags 10 in ov035. | Shared draw-stage purpose not established, nor whether flag 10 is a complete contract. | Trace scene draw flag 10 descriptor and corresponding other scene calls; do not infer rendering work from empty body. |
| ov001:0x02087784 (Thumb, 0x4c bytes) | `eu/src/overlays/ov001/calls/func_ov001_02087784.c` | Guard active stage service, fetch object(index+1 narrowed16), bound entryIndex by signed 16-bit range(end-start+1), return stored halfword at +0xa+2index plus1; else0. | Storage looks like adjacent bound fields for large index, and actual stage-record lookup semantics remain unproved. | Compare native GetStageObjectHandle record layout and all entryIndex callers (observed0) to prove whether API enumerates IDs or only accesses boundary fields. |

## Actor scene, animation and script callbacks

| EU identity and native size | Current EU source | Observed mechanical contract | Semantic blocker | Next proof |
|---|---|---|---|---|

## Stage actors and controller states

| EU identity and native size | Current EU source | Observed mechanical contract | Semantic blocker | Next proof |
|---|---|---|---|---|
| ov001:0x0209d08c (Thumb, 0x1c bytes) | `eu/src/overlays/ov001/calls/func_ov001_0209d08c.c` | True for IDs70..97 or99. Consumers alter drop counter27, stage resource spawn flags and display style (which separately excludes99). | No asset/record mapping proves a single gameplay family covering range and exception. | Map actual resource definitions for 70..97/99 and spawn/display/drop branches; do not call them bosses solely from range. |

## Recurring boundaries to preserve during a port

- Session +0x208/+0x20a are signed halfwords with unresolved domain labels;
  legacy music/track views are not proof of their meaning.
- Pending world-entry payload bytes 1/3 flow to session +0x2744/+0x2745, but
  world/room identity must be established from the downstream format.
- Class objects use class +0x08; entry-pool objects use owner +0x04. Callback
  slot numbers and result meanings must be proved for the correct family.
- Aggregate native words can carry pointers or raw status. Preserve original
  signed extension, narrowing, null/sentinel behavior and callback argument
  registers while deriving explicit portable types.
- Descriptor indices and empty bodies alone do not prove a gameplay purpose.
  Record the actual writer, consumer and transition before choosing a name.

The next-proof entries are bounded investigations, not instructions to rewrite
working code. Resolve one owner, field or protocol at a time and retain the
native identity so that any later name can be traced to its evidence.

## Resolved actor-scene continuation

The former ov001:020882d4 entry is now ActorScene_IdleTaskUpdate. The complete
descriptor/initializer/task-runner chain proves zero means retain the current
callback. [ACTOR_TASK_RECORD_PROGRESS_CONTRACTS.md](ACTOR_TASK_RECORD_PROGRESS_CONTRACTS.md)
records the native registration, manager task handle and explicit transition
out of the idle state. Its four bytes and original argument list are unchanged.

## Closed primary actor health helpers

The former 02063c94 / 0206550c entries are now RestorePrimaryActorHealth and ScriptCmd_RestorePrimaryActorHealth. The actor record owner, current/max HP writers and final HUD consumers close their former field-role gap. [Actor health restoration](ACTOR_HEALTH_RESTORATION.md) records the corrected SetActorHealthClamped dependency and the preserved native ABI limits.

## Closed stage, request and common-sprite callbacks

Seven entries now have proved owners and result protocols: [stage idle callbacks](STAGE_IDLE_CALLBACK_CONTRACTS.md), [SubScene9 request availability](SUBSCENE9_REQUEST_CONTRACT.md) and [the common field message-sprite wait](COMMON_FIELD_MESSAGE_SPRITE_WAIT.md). Their native declarations and bytes are retained. The common sprite is not an IO loader, and the SubScene9 wait does not guarantee a new request was accepted.

## Closed interface and field-object callbacks

Four entries now have proved phases or pre-release roles in [the callback contracts](FIELD_CALLBACK_PHASE_CONTRACTS.md). Their empty bodies remain distinct registered callbacks. The class11 object+0x68 hook runs before release; the old private update/draw names are not used as behavioral evidence.

## Closed class activation, LOD and command accessors

Four numeric helpers now follow [the field-object class owner and its consumers](FIELD_OBJECT_CLASS_ACTIVATION_LOD_COMMANDS.md). The related script label is corrected to ScriptCmd_ConfigureFieldObjectClassLod: it configures a secondary resource and hysteresis thresholds; it does not spawn an object. Native index forwarding and signed/unsigned field reads remain explicit.
