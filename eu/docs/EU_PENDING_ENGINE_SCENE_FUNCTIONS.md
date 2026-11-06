# EU functions awaiting semantic evidence

These 2 byte-exact functions retain their address names because a stronger role or field meaning remains unproven. Current source paths, function names and native declarations were revalidated at Git `c55c73c68510bfb1168844edc4e9a0deea2e61b5`. The raw-ROM scan receipt remains pinned to the earlier `28dc258674c86cde06bc8456c4c7cb9087e28905` research checkpoint. This document changes no source, prototype, structure or behavior, and makes no new official compilation or byte-exact validation claim.

## How to use this inventory

The mechanical contract is the part a port can preserve now. The blocker explains which additional meaning must remain opaque. Declarations reproduce the native source view, including synthetic register slots, old-style forwarding and private integer/pointer labels; they are not finalized host headers.

The stage-script integer result uses tag 1 at context +0x2c and value +0x30; fixed-point tag 0x10 preserves raw values with 12 fractional bits. Several helpers leave these fields unchanged on a missing-event path. The ordinary indexed-query dispatcher initializes tag 1/value 0 before invoking a selected helper, so distinguish the helper's own effects from its usual caller's initialization. The stage opcode status 0 is separate from the tagged value.

## Reference search and bank limits

The review scanned all 108 extracted domains (MAIN, ITCM, DTCM and 105 overlays), byte-aligned, for each function address and address|1. It also inspected ARM/Thumb direct-branch encodings and PC-relative literal loads using each configured bank/mode/extent, followed by a bounded control-flow reachability estimate. The unresolved function's BSS anchor 02060764 and pointer slot 02060768 were scanned separately.

All 18 functions have a direct-call or table/pool reference in this scan. Ghidra's absence of direct xrefs for indirect dispatch is therefore not treated as evidence of nonuse. Raw equal RAM addresses do not establish a bank binding; code extents may contain literal pools, and unresolved computed/switch branches limit the reachability estimate. Neither extracted-module absence nor a single caller rules out calculated pointers or compressed/dynamically loaded asset references.

The research receipt for this pass has SHA-256 `f0116bceabb1f33cf0afe91e100fc16178c9613583ed35fda872a7887e763eec`. The locations and relevant bank qualifications are reproduced per entry below; the unresolved meanings are not renamed to fit a percentage.

| Bank:address | Mode | Source | Result category |
| --- | --- | --- | --- |
| `main:0202d620` | THUMB | [eu/src/calls/func_0202d620.c](../src/calls/func_0202d620.c) | void; no ownership transfer. |
| `ov021:020a9d24` | THUMB | [eu/src/overlays/ov021/calls/IsModelSetDrawEnabled.c](../src/overlays/ov021/calls/IsModelSetDrawEnabled.c) | Normalized BOOL equivalent to ((*flags & 3) == 3). |
| `ov021:020b0ad4` | THUMB | [eu/src/overlays/ov021/calls/StageScriptExpr_GetStageWorkspaceWord1.c](../src/overlays/ov021/calls/StageScriptExpr_GetStageWorkspaceWord1.c) | Return opcode status 0. The copied integer word is not normalized or converted. |
| `ov021:020b0af0` | THUMB | [eu/src/overlays/ov021/calls/StageScriptExpr_GetStageWorkspaceWord0.c](../src/overlays/ov021/calls/StageScriptExpr_GetStageWorkspaceWord0.c) | Return opcode status 0; no allocation or pointer lifetime change. |
| `ov021:020b0edc` | THUMB | [eu/src/overlays/ov021/calls/func_ov021_020b0edc.c](../src/overlays/ov021/calls/func_ov021_020b0edc.c) | Opcode status 0; missing event or record leaves the helper's result fields unchanged. |
| `ov021:020b2044` | THUMB | [eu/src/overlays/ov021/calls/StageScriptOp_ResolveDataOperands.c](../src/overlays/ov021/calls/StageScriptOp_ResolveDataOperands.c) | Opcode status 0. Resolver/expression side effects are retained; this is not safely replaceable by an empty function. |
| `ov021:020b2fec` | THUMB | [eu/src/overlays/ov021/calls/StageScriptCmd_SetStageMarkerAuxiliaryWords.c](../src/overlays/ov021/calls/StageScriptCmd_SetStageMarkerAuxiliaryWords.c) | Opcode status 0. There is no index check, conversion, allocation or result-vector write. |
| `ov030:020bcec0` | THUMB | [eu/src/overlays/ov030/calls/StartCarriedLauncherEmission.c](../src/overlays/ov030/calls/StartCarriedLauncherEmission.c) | void. ActivateSpawnUnit uses a native hidden composite-return destination; the C VecFx32 return view preserves that operation. |

## func_0202d620

Identity: `main:0202d620`, THUMB, configured native extent 20 bytes (including any pool). Source: [eu/src/calls/func_0202d620.c](../src/calls/func_0202d620.c).

```c
void func_0202d620(u32 value);
```

- Inputs: One u32 value. The eight-byte BSS anchor is at 02060764; its second word at 02060768 is an optional pointer.
- Mechanical effects: If that pointer is nonnull, store the value as a word at target +0x600. Otherwise do nothing. No target allocation or pointer initialization occurs here.
- Result/lifetime: void; no ownership transfer.

### Callers, registration and ROM references

- `ov001:020714ca` in `ResumeFieldFromPause`: `bl #0x202d620`; configured relocation names the target bank and this instruction is reachable in the bounded estimate. Source: [eu/src/overlays/ov001/calls/ResumeFieldFromPause.c](../src/overlays/ov001/calls/ResumeFieldFromPause.c).

### Writers and related source evidence

[eu/src/overlays/ov001/calls/ResumeFieldFromPause.c](../src/overlays/ov001/calls/ResumeFieldFromPause.c), [src/ov001/field_manager/ResumeFieldFromPause_0207136c.c](../../src/ov001/field_manager/ResumeFieldFromPause_0207136c.c), [eu/src/data/bss/Bss_main_02060764.c](../src/data/bss/Bss_main_02060764.c).

### Established limit

The resume caller supplies 1 after restoring graphics, but that placement does not prove the target type or field purpose. The raw scan finds the setter's own anchor literal and no separate complete 02060768 word; calculated/prefix-based writes remain possible.

### Searches already performed and next proof

Queried references to both BSS anchor02060764 and pointer slot02060768. Each query only finds this setter. The only direct caller found is ResumeFieldFromPause(value1), after BG restore. Source search also finds only the static two-word BSS declaration and setter. This is insufficient to identify the optional target object or its+600 field.

Next proof: Trace bulk/prefix BSS initialization and indirect constructors that could receive the anchor and assign its+4 pointer. A single resume caller does not prove the target is a renderer or dirty flag.

Additional raw scan: the only complete anchor word 02060764 is the setter's own pool at MAIN0202d630, loaded at0202d620. No complete 02060768/02060769 word was found in the extracted domains. This leaves prefix-based initialization, computed references and larger shared initialization routines unresolved.

## func_ov021_020b0edc

Identity: `ov021:020b0edc`, THUMB, configured native extent 48 bytes (including any pool). Source: [eu/src/overlays/ov021/calls/func_ov021_020b0edc.c](../src/overlays/ov021/calls/func_ov021_020b0edc.c).

```c
u32 func_ov021_020b0edc(int self);
```

- Inputs: Stage-script context and active event. Read its halfword at +0x16 and pass it to GetStageMotionRecord.
- Mechanical effects: Only when both the event and resolved record exist, write integer tag 1 and copy record word +0x18 into the result.
- Result/lifetime: Opcode status 0; missing event or record leaves the helper's result fields unchanged.

### Callers, registration and ROM references

- `ov021:020b54e8` contains `020b0edd`, `gScriptQueryHandlers[100]` (173 entries). The configured relocation records this target bank. Storage: [eu/src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c](../src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c).
- `ScriptOp_DispatchIndexedCommand` resolves the selector, initializes the tagged result to integer zero, indexes this array and invokes the nonnull handler. The helper's return is discarded and the dispatcher returns 0. Source: [eu/src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c](../src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c).

### Established limit

GetStageMotionRecord resolves records used through several motion/grid/slot views. This getter's concrete record kind and the role of +0x18 must be recovered before assigning a property name.

### Searches already performed and next proof

Getter uses active event.motionId+16 to obtain a polymorphic stage record and copies record+18 as tagged integer; both missing-event and missing-record paths retain prior result. The record schema remains unresolved.

Next proof: Correlate record kind/loader at GetStageMotionRecord with this expression entry, rather than exporting a generic motion/grid/slot field.

## Closed board-node getter

The former ov032:020bb828 entry is now [GetCurrentBoardNodeCode](CURRENT_BOARD_NODE_CODE.md). The SessionBuffer10 owner, six code writers and native signed-byte loads close its former lock/rank/variant ambiguity.

## Closed timed-cue and effect-kind helpers

The [timed-cue group selector](STAGE_EVENT_TIMED_CUE_GROUP.md) now has its actual section16/10 consumer, distinct from collision cues. The [effect-kind expression](STAGE_EVENT_EFFECT_KIND.md) has actual writers, duration/expiration and hit-effect consumers; individual effect codes remain opaque.

## Closed combat, reaction and motion expressions

Native damage, defeat, gauge, override and installed sequence callbacks establish [combat values](STAGE_EVENT_COMBAT_VALUES.md), [reaction/countdown values](STAGE_EVENT_REACTION_COUNTDOWN.md), [motion/position callbacks](STAGE_MOTION_POSITION_CALLBACKS.md) and [current override ID](STAGE_CURRENT_OVERRIDE_ID.md). Raw widths, missing-event behavior and compiler ABI views are preserved; contradictory private HP/speed labels are documented rather than exported as a host layout.
