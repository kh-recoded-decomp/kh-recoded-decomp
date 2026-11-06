# EU functions awaiting semantic evidence

These 15 byte-exact functions retain their address names because a stronger role or field meaning remains unproven. Current source paths, function names and native declarations were revalidated at Git `c55c73c68510bfb1168844edc4e9a0deea2e61b5`. The raw-ROM scan receipt remains pinned to the earlier `28dc258674c86cde06bc8456c4c7cb9087e28905` research checkpoint. This document changes no source, prototype, structure or behavior, and makes no new official compilation or byte-exact validation claim.

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
| `ov021:020a9d24` | THUMB | [eu/src/overlays/ov021/calls/func_ov021_020a9d24.c](../src/overlays/ov021/calls/func_ov021_020a9d24.c) | Normalized BOOL equivalent to ((*flags & 3) == 3). |
| `ov021:020b0ad4` | THUMB | [eu/src/overlays/ov021/calls/func_ov021_020b0ad4.c](../src/overlays/ov021/calls/func_ov021_020b0ad4.c) | Return opcode status 0. The copied integer word is not normalized or converted. |
| `ov021:020b0af0` | THUMB | [eu/src/overlays/ov021/calls/func_ov021_020b0af0.c](../src/overlays/ov021/calls/func_ov021_020b0af0.c) | Return opcode status 0; no allocation or pointer lifetime change. |
| `ov021:020b0dd4` | THUMB | [eu/src/overlays/ov021/calls/func_ov021_020b0dd4.c](../src/overlays/ov021/calls/func_ov021_020b0dd4.c) | Opcode status 0; the raw stored fixed-point value retains 12 fractional bits. |
| `ov021:020b0df0` | THUMB | [eu/src/overlays/ov021/calls/func_ov021_020b0df0.c](../src/overlays/ov021/calls/func_ov021_020b0df0.c) | Opcode status 0; the tagged operand evaluation still occurs on the missing-event path. |
| `ov021:020b0e24` | THUMB | [eu/src/overlays/ov021/calls/func_ov021_020b0e24.c](../src/overlays/ov021/calls/func_ov021_020b0e24.c) | Opcode status 0; no sign extension of the source halfword. |
| `ov021:020b0edc` | THUMB | [eu/src/overlays/ov021/calls/func_ov021_020b0edc.c](../src/overlays/ov021/calls/func_ov021_020b0edc.c) | Opcode status 0; missing event or record leaves the helper's result fields unchanged. |
| `ov021:020b10b0` | THUMB | [eu/src/overlays/ov021/calls/func_ov021_020b10b0.c](../src/overlays/ov021/calls/func_ov021_020b10b0.c) | Opcode status 0; no ownership transfer. |
| `ov021:020b10c0` | THUMB | [eu/src/overlays/ov021/calls/func_ov021_020b10c0.c](../src/overlays/ov021/calls/func_ov021_020b10c0.c) | Opcode status 0; copy raw fixed-point bits. |
| `ov021:020b12b8` | THUMB | [eu/src/overlays/ov021/calls/func_ov021_020b12b8.c](../src/overlays/ov021/calls/func_ov021_020b12b8.c) | Opcode status 0; no conversion beyond assigning the tag. |
| `ov021:020b1a9c` | THUMB | [eu/src/overlays/ov021/calls/func_ov021_020b1a9c.c](../src/overlays/ov021/calls/func_ov021_020b1a9c.c) | Opcode status 0; second callback can write the context vector. Callback and record pointers are borrowed. |
| `ov021:020b2044` | THUMB | [eu/src/overlays/ov021/calls/func_ov021_020b2044.c](../src/overlays/ov021/calls/func_ov021_020b2044.c) | Opcode status 0. Resolver/expression side effects are retained; this is not safely replaceable by an empty function. |
| `ov021:020b2fec` | THUMB | [eu/src/overlays/ov021/calls/func_ov021_020b2fec.c](../src/overlays/ov021/calls/func_ov021_020b2fec.c) | Opcode status 0. There is no index check, conversion, allocation or result-vector write. |
| `ov030:020bcec0` | THUMB | [eu/src/overlays/ov030/calls/func_ov030_020bcec0.c](../src/overlays/ov030/calls/func_ov030_020bcec0.c) | void. ActivateSpawnUnit uses a native hidden composite-return destination; the C VecFx32 return view preserves that operation. |

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

## func_ov021_020a9d24

Identity: `ov021:020a9d24`, THUMB, configured native extent 24 bytes (including any pool). Source: [eu/src/overlays/ov021/calls/func_ov021_020a9d24.c](../src/overlays/ov021/calls/func_ov021_020a9d24.c).

```c
BOOL func_ov021_020a9d24(u32 *flags);
```

- Inputs: Pointer to a u32 flag word. There is no NULL check.
- Mechanical effects: Read bit 0 first. If clear, return FALSE. Otherwise return whether bit 1 is set. It changes no flags.
- Result/lifetime: Normalized BOOL equivalent to ((*flags & 3) == 3).

### Callers, registration and ROM references

- `ov052:020ce680` in `BuildActorStatusFlags`: `bl #0x20a9d24`; configured relocation names the target bank and this instruction is reachable in the bounded estimate. Source: [eu/src/overlays/ov052/calls/BuildActorStatusFlags.c](../src/overlays/ov052/calls/BuildActorStatusFlags.c).
- `ov052:020ce698` in `BuildActorStatusFlags`: `bl #0x20a9d24`; configured relocation names the target bank and this instruction is reachable in the bounded estimate. Source: [eu/src/overlays/ov052/calls/BuildActorStatusFlags.c](../src/overlays/ov052/calls/BuildActorStatusFlags.c).
- `ov052:020cfb5c` in `AnySubObjectFlagsActive`: `bl #0x20a9d24`; configured relocation names the target bank and this instruction is reachable in the bounded estimate. Source: [eu/src/overlays/ov052/calls/AnySubObjectFlagsActive.c](../src/overlays/ov052/calls/AnySubObjectFlagsActive.c).
- `ov052:020d1ec2` in `RunVolumeHitScan`: `bl #0x20a9d24`; configured relocation names the target bank and this instruction is reachable in the bounded estimate. Source: [eu/src/overlays/ov052/calls/RunVolumeHitScan.c](../src/overlays/ov052/calls/RunVolumeHitScan.c).
- `ov053:020d26be` in `UpdateModelBlinkEffect`: `bl #0x20a9d24`; configured relocation names the target bank and this instruction is reachable in the bounded estimate. Source: [eu/src/overlays/ov053/calls/UpdateModelBlinkEffect.c](../src/overlays/ov053/calls/UpdateModelBlinkEffect.c).
- `ov053:020d26e6` in `UpdateModelBlinkEffect`: `bl #0x20a9d24`; configured relocation names the target bank and this instruction is reachable in the bounded estimate. Source: [eu/src/overlays/ov053/calls/UpdateModelBlinkEffect.c](../src/overlays/ov053/calls/UpdateModelBlinkEffect.c).
- `ov053:020d27a0` in `UpdateModelBlinkEffect`: `bl #0x20a9d24`; configured relocation names the target bank and this instruction is reachable in the bounded estimate. Source: [eu/src/overlays/ov053/calls/UpdateModelBlinkEffect.c](../src/overlays/ov053/calls/UpdateModelBlinkEffect.c).
- `ov059:020c76cc` in `UpdateToggleEffectTimer`: `blx #0x20a9d24`; configured relocation names the target bank and this instruction is reachable in the bounded estimate. Source: [eu/src/overlays/ov059/calls/UpdateToggleEffectTimer.c](../src/overlays/ov059/calls/UpdateToggleEffectTimer.c).
- `ov059:020c7700` in `UpdateToggleEffectTimer`: `blx #0x20a9d24`; configured relocation names the target bank and this instruction is reachable in the bounded estimate. Source: [eu/src/overlays/ov059/calls/UpdateToggleEffectTimer.c](../src/overlays/ov059/calls/UpdateToggleEffectTimer.c).
- `ov059:020c7814` in `UpdateToggleEffectTimer`: `blx #0x20a9d24`; configured relocation names the target bank and this instruction is reachable in the bounded estimate. Source: [eu/src/overlays/ov059/calls/UpdateToggleEffectTimer.c](../src/overlays/ov059/calls/UpdateToggleEffectTimer.c).
- `ov059:020cd158` in `Actor_AnyAnimSlotBusy`: `bl #0x20a9d24`; configured relocation names the target bank and this instruction is reachable in the bounded estimate. Source: [eu/src/overlays/ov059/calls/Actor_AnyAnimSlotBusy.c](../src/overlays/ov059/calls/Actor_AnyAnimSlotBusy.c).

### Writers and related source evidence

[eu/src/overlays/ov052/calls/BuildActorStatusFlags.c](../src/overlays/ov052/calls/BuildActorStatusFlags.c), [src/ov052/unclassified_helpers/BuildActorStatusFlags_020ce5d4.c](../../src/ov052/unclassified_helpers/BuildActorStatusFlags_020ce5d4.c), [eu/src/overlays/ov053/calls/UpdateModelBlinkEffect.c](../src/overlays/ov053/calls/UpdateModelBlinkEffect.c), [src/ov053/unclassified_helpers/UpdateModelBlinkEffect_020d265c.c](../../src/ov053/unclassified_helpers/UpdateModelBlinkEffect_020d265c.c), [eu/src/overlays/ov059/calls/UpdateToggleEffectTimer.c](../src/overlays/ov059/calls/UpdateToggleEffectTimer.c).

### Established limit

The concrete owners in overlays052/053/059 differ. Their two bits are not established as generic active/visible/busy flags. Bit-1 toggling conditional on bit 0 does not identify the constructor meaning of either bit.

### Searches already performed and next proof

New Ghidra references identify eleven uses across concrete052/053/059 owners. UpdateModelBlinkEffect and UpdateToggleEffectTimer toggle bit1 conditionally on bit0, while BuildActorStatusFlags compares the result against an owner state bit. Neither construction nor both flag meanings is established; late reviewer confirmed no stronger contract.

Next proof: Find writes that establish bit0 and bit1 on the exact flag subobjects, then match each reader to those writers. Do not equate them with TaskObject flags or EntryPool.state.

## func_ov021_020b0ad4

Identity: `ov021:020b0ad4`, THUMB, configured native extent 28 bytes (including any pool). Source: [eu/src/overlays/ov021/calls/func_ov021_020b0ad4.c](../src/overlays/ov021/calls/func_ov021_020b0ad4.c).

```c
u32 func_ov021_020b0ad4(int self);
```

- Inputs: Stage-script context. Obtain the current stage manager through GetStageManager.
- Mechanical effects: Write tag 1 at context +0x2c and copy the raw word at manager +0x18e7c to context +0x30.
- Result/lifetime: Return opcode status 0. The copied integer word is not normalized or converted.

### Callers, registration and ROM references

- `ov021:020b55e4` contains `020b0ad5`, `gScriptQueryHandlers[163]` (173 entries). The configured relocation records this target bank. Storage: [eu/src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c](../src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c).
- `ScriptOp_DispatchIndexedCommand` resolves the selector, initializes the tagged result to integer zero, indexes this array and invokes the nonnull handler. The helper's return is discarded and the dispatcher returns 0. Source: [eu/src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c](../src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c).

### Writers and related source evidence

[eu/src/overlays/ov021/calls/ScriptCmd_SetProperty.c](../src/overlays/ov021/calls/ScriptCmd_SetProperty.c), [src/ov021/script_ops/ScriptOp_SetStageMarker_020b2f58.c](../../src/ov021/script_ops/ScriptOp_SetStageMarker_020b2f58.c), [src/ov021/script_ops/ScriptOp_SpawnLinkedWalkers_020b3114.c](../../src/ov021/script_ops/ScriptOp_SpawnLinkedWalkers_020b3114.c).

### Established limit

This offset is an X component in one spawn/marker layout, while other stage-cue code reuses the workspace with a different view. A universal position or spawn-offset name would hide the required last-writer/context proof.

### Searches already performed and next proof

Revisited ScriptCmd_SetProperty SpawnPoint view and ScriptOp_SetStageMarker/SpawnLinkedWalkers. They model the shared18e78 workspace as flags plus offset/radius, but earlier ProcessStageCues also writes a hit-point vector at that base. The scalar18e7c read therefore remains command-context dependent.

Next proof: Trace bytecode expression identity and last writer for this specific expression path; establish whether the workspace is a union and which view is active.

## func_ov021_020b0af0

Identity: `ov021:020b0af0`, THUMB, configured native extent 28 bytes (including any pool). Source: [eu/src/overlays/ov021/calls/func_ov021_020b0af0.c](../src/overlays/ov021/calls/func_ov021_020b0af0.c).

```c
u32 func_ov021_020b0af0(int self);
```

- Inputs: Stage-script context and the stage-manager global obtained by GetStageManager.
- Mechanical effects: Write tag 1 at context +0x2c and copy the raw word at manager +0x18e78 to context +0x30.
- Result/lifetime: Return opcode status 0; no allocation or pointer lifetime change.

### Callers, registration and ROM references

- `ov021:020b55e0` contains `020b0af1`, `gScriptQueryHandlers[162]` (173 entries). The configured relocation records this target bank. Storage: [eu/src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c](../src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c).
- `ScriptOp_DispatchIndexedCommand` resolves the selector, initializes the tagged result to integer zero, indexes this array and invokes the nonnull handler. The helper's return is discarded and the dispatcher returns 0. Source: [eu/src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c](../src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c).

### Writers and related source evidence

[eu/src/overlays/ov021/calls/ScriptCmd_SetProperty.c](../src/overlays/ov021/calls/ScriptCmd_SetProperty.c), [src/ov021/script_ops/ScriptOp_SetStageMarker_020b2f58.c](../../src/ov021/script_ops/ScriptOp_SetStageMarker_020b2f58.c), [src/ov021/script_ops/ScriptOp_SpawnLinkedWalkers_020b3114.c](../../src/ov021/script_ops/ScriptOp_SpawnLinkedWalkers_020b3114.c).

### Established limit

The marker/spawn view calls this word flags, but an earlier cue path writes a hit-point vector beginning at this address. Neither view alone establishes the expression's universal property.

### Searches already performed and next proof

Same workspace audit as0ad4:18e78 is flags in the marker/spawn layout, but the cue path uses it as vector storage. Raw integer tagging is proven, a universal field meaning is not.

Next proof: Recover last-writer/consumer order in the owning script command stream and document the workspace lifetime before naming the value.

## func_ov021_020b0dd4

Identity: `ov021:020b0dd4`, THUMB, configured native extent 28 bytes (including any pool). Source: [eu/src/overlays/ov021/calls/func_ov021_020b0dd4.c](../src/overlays/ov021/calls/func_ov021_020b0dd4.c).

```c
u32 func_ov021_020b0dd4(int self);
```

- Inputs: Stage-script context and the active event pointer.
- Mechanical effects: With an active event, write fixed-point tag 0x10 and copy its word +0x74 to context +0x30. With no event, leave the result untouched.
- Result/lifetime: Opcode status 0; the raw stored fixed-point value retains 12 fractional bits.

### Callers, registration and ROM references

- `ov021:020b5524` contains `020b0dd5`, `gScriptQueryHandlers[115]` (173 entries). The configured relocation records this target bank. Storage: [eu/src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c](../src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c).
- `ScriptOp_DispatchIndexedCommand` resolves the selector, initializes the tagged result to integer zero, indexes this array and invokes the nonnull handler. The helper's return is discarded and the dispatcher returns 0. Source: [eu/src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c](../src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c).

### Writers and related source evidence

[eu/src/overlays/ov021/calls/ScriptCmd_SetProperty.c](../src/overlays/ov021/calls/ScriptCmd_SetProperty.c).

### Established limit

Property 0x90 copies event +0x70/+0x74 together and has a kind-0x3d zero-crossing response. That relation is not sufficient to assign maxHP to +0x74 for every event kind.

### Searches already performed and next proof

Property command0x90 copies70/74 as a pair; for kind3d, a positive-to-nonpositive70 transition triggers ApplyHitToEnemyGroup with74 and resets70 to1. This proves a relation, not a universal maxHP meaning for74 across event kinds.

Next proof: Collect initialization/damage/reset paths per event kind and identify the quantity/units for both words; keep the current fixed-point tag0x10.

## func_ov021_020b0df0

Identity: `ov021:020b0df0`, THUMB, configured native extent 52 bytes (including any pool). Source: [eu/src/overlays/ov021/calls/func_ov021_020b0df0.c](../src/overlays/ov021/calls/func_ov021_020b0df0.c).

```c
u32 func_ov021_020b0df0(int self, int args);
```

- Inputs: Stage-script context and operand block. Resolve the tagged operand at +8 before testing whether an event exists.
- Mechanical effects: If the event exists, write tag 0x10; call GetEntryScaledValue(event, (resolved.value + 1U) & 0xffff) and store its result at context +0x30. Missing event leaves the result unchanged after the operand evaluation.
- Result/lifetime: Opcode status 0; the tagged operand evaluation still occurs on the missing-event path.

### Callers, registration and ROM references

- `ov021:020b551c` contains `020b0df1`, `gScriptQueryHandlers[113]` (173 entries). The configured relocation records this target bank. Storage: [eu/src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c](../src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c).
- `ScriptOp_DispatchIndexedCommand` resolves the selector, initializes the tagged result to integer zero, indexes this array and invokes the nonnull handler. The helper's return is discarded and the dispatcher returns 0. Source: [eu/src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c](../src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c).

### Established limit

The event's 32-byte entry schema and type-3 behavior remain unproven. The narrowed index and fixed-point result are known; a category name for the entries is not.

### Searches already performed and next proof

Re-read that the argument is evaluated before the active-event guard, its value is increased by1 then narrowed16bits, and GetEntryScaledValue is tagged fixed point. No event+A8 entry schema or category was recovered.

Next proof: Trace GetEntryScaledValue records and all type3 branches to prove index domain, entry category and scaling meaning.

## func_ov021_020b0e24

Identity: `ov021:020b0e24`, THUMB, configured native extent 28 bytes (including any pool). Source: [eu/src/overlays/ov021/calls/func_ov021_020b0e24.c](../src/overlays/ov021/calls/func_ov021_020b0e24.c).

```c
u32 func_ov021_020b0e24(int self);
```

- Inputs: Stage-script context and active event.
- Mechanical effects: With an event, write integer tag 1 and zero-extend its halfword +0x1e into context +0x30. Otherwise preserve the result.
- Result/lifetime: Opcode status 0; no sign extension of the source halfword.

### Callers, registration and ROM references

- `ov021:020b5518` contains `020b0e25`, `gScriptQueryHandlers[112]` (173 entries). The configured relocation records this target bank. Storage: [eu/src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c](../src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c).
- `ScriptOp_DispatchIndexedCommand` resolves the selector, initializes the tagged result to integer zero, indexes this array and invokes the nonnull handler. The helper's return is discarded and the dispatcher returns 0. Source: [eu/src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c](../src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c).

### Writers and related source evidence

[eu/src/overlays/ov021/calls/ScriptCmd_SetProperty.c](../src/overlays/ov021/calls/ScriptCmd_SetProperty.c).

### Established limit

The event's +0x1e schema/writer is still unknown; it lies within an explicitly opaque range of the reviewed native view.

### Searches already performed and next proof

Exact getter returns event+1e as unsigned halfword tagged integer. Native PropertyEvent reserves1c..6f rather than identifying that field.

Next proof: Find the loading/copying schema and writers for event+1e, with a concrete event-kind caller.

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

## func_ov021_020b10b0

Identity: `ov021:020b10b0`, THUMB, configured native extent 16 bytes (including any pool). Source: [eu/src/overlays/ov021/calls/func_ov021_020b10b0.c](../src/overlays/ov021/calls/func_ov021_020b10b0.c).

```c
u32 func_ov021_020b10b0(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

- Inputs: Stage-script context in the first native register word. The three remaining generated arguments are unused.
- Mechanical effects: Write integer tag 1 and zero-extend context halfword +0xa2 into context +0x30.
- Result/lifetime: Opcode status 0; no ownership transfer.

### Callers, registration and ROM references

- `ov021:020b53b4` contains `020b10b1`, `gScriptQueryHandlers[23]` (173 entries). The configured relocation records this target bank. Storage: [eu/src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c](../src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c).
- `ScriptOp_DispatchIndexedCommand` resolves the selector, initializes the tagged result to integer zero, indexes this array and invokes the nonnull handler. The helper's return is discarded and the dispatcher returns 0. Source: [eu/src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c](../src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c).

### Writers and related source evidence

[src/ov021/unclassified_helpers/InitSequencer_020b4aac.c](../../src/ov021/unclassified_helpers/InitSequencer_020b4aac.c), [src/ov021/unclassified_helpers/SelectSequenceTrack_020b4bdc.c](../../src/ov021/unclassified_helpers/SelectSequenceTrack_020b4bdc.c).

### Established limit

InitSequencer clears this area but identifies only the neighboring ID at +0xa0. The +0xa2 field remains padding in that view. A four-register native declaration is not a four-parameter portable contract.

### Searches already performed and next proof

InitSequencer zeroes its full0xa8 view, sets id at+a0 and retains+a2 in pad_a2[6]. SelectSequenceTrack only changes track/cursor/timer/frame. The+a2 expression is real, but initialization supplies only zero and no semantic writer was found.

Next proof: Find later+a2 writes in all sequencer owners and sequence-file/expression use. Zero initialization alone does not establish an ID/category.

## func_ov021_020b10c0

Identity: `ov021:020b10c0`, THUMB, configured native extent 28 bytes (including any pool). Source: [eu/src/overlays/ov021/calls/func_ov021_020b10c0.c](../src/overlays/ov021/calls/func_ov021_020b10c0.c).

```c
u32 func_ov021_020b10c0(int self);
```

- Inputs: Stage-script context and active event.
- Mechanical effects: With an event, write fixed-point tag 0x10 and copy event word +0x70 to context +0x30; otherwise preserve the helper's result fields.
- Result/lifetime: Opcode status 0; copy raw fixed-point bits.

### Callers, registration and ROM references

- `ov021:020b53b0` contains `020b10c1`, `gScriptQueryHandlers[22]` (173 entries). The configured relocation records this target bank. Storage: [eu/src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c](../src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c).
- `ScriptOp_DispatchIndexedCommand` resolves the selector, initializes the tagged result to integer zero, indexes this array and invokes the nonnull handler. The helper's return is discarded and the dispatcher returns 0. Source: [eu/src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c](../src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c).

### Writers and related source evidence

[eu/src/overlays/ov021/calls/ScriptCmd_SetProperty.c](../src/overlays/ov021/calls/ScriptCmd_SetProperty.c).

### Established limit

Property 0x16 writes this quantity from TaggedValueToFixed; property 0x90 copies it with +0x74. A kind-0x3d damage-like response does not prove a universal HP quantity for all event kinds.

### Searches already performed and next proof

Property0x16 writes event+70 from TaggedValueToFixed. Property0x90 copies70/74 and has a kind3d zero-crossing response. The field can be script-assigned and no universal HP contract is proven.

Next proof: Trace initial values and event-kind consumers, including ApplyHitToEnemyGroup, before choosing a universal quantity name.

## func_ov021_020b12b8

Identity: `ov021:020b12b8`, THUMB, configured native extent 32 bytes (including any pool). Source: [eu/src/overlays/ov021/calls/func_ov021_020b12b8.c](../src/overlays/ov021/calls/func_ov021_020b12b8.c).

```c
u32 func_ov021_020b12b8(int self);
```

- Inputs: Stage-script context and active event.
- Mechanical effects: With an event, write fixed-point tag 0x10 and copy event word +0x1a0 to context +0x30. Otherwise return without writing the result.
- Result/lifetime: Opcode status 0; no conversion beyond assigning the tag.

### Callers, registration and ROM references

- `ov021:020b5364` contains `020b12b9`, `gScriptQueryHandlers[3]` (173 entries). The configured relocation records this target bank. Storage: [eu/src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c](../src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c).
- `ScriptOp_DispatchIndexedCommand` resolves the selector, initializes the tagged result to integer zero, indexes this array and invokes the nonnull handler. The helper's return is discarded and the dispatcher returns 0. Source: [eu/src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c](../src/overlays/ov021/calls/ScriptOp_DispatchIndexedCommand.c).

### Writers and related source evidence

[eu/src/overlays/ov021/calls/ScriptCmd_SetProperty.c](../src/overlays/ov021/calls/ScriptCmd_SetProperty.c).

### Established limit

The producer and event-kind schema for +0x1a0 remain unknown. Similarly located fields in other actor owners are not evidence for this event field.

### Searches already performed and next proof

Exact getter copies event+1a0 as fixed point; reviewed native PropertyEvent keeps that range opaque. No producer/schema was identified by this pass.

Next proof: Find event-kind initialization and property writes to+1a0, preserving the distinction from similarly offset fields in unrelated actors.

## func_ov021_020b1a9c

Identity: `ov021:020b1a9c`, THUMB, configured native extent 88 bytes (including any pool). Source: [eu/src/overlays/ov021/calls/func_ov021_020b1a9c.c](../src/overlays/ov021/calls/func_ov021_020b1a9c.c).

```c
u32 func_ov021_020b1a9c(int self);
```

- Inputs: Stage-script context. The body dereferences the active event to obtain its halfword +0x16 without an event-NULL guard, then resolves a stage record.
- Mechanical effects: If that record exists, obtain GetGlobalScaleValue and the stage manager. Invoke optional manager +0x18f54 as (record, value), then independently reacquire the manager and invoke optional +0x18f58 as (record, context +0x34).
- Result/lifetime: Opcode status 0; second callback can write the context vector. Callback and record pointers are borrowed.

### Callers, registration and ROM references

- `ov021:020b532c` contains `020b1a9d`, `gScriptVectorHandlers[22]` (33 entries). The configured relocation records this target bank. Storage: [eu/src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c](../src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c).
- `DispatchScriptHandler` resolves the selector and invokes the nonnull vector-table entry with (context, operands), discarding its return. Source: [eu/src/overlays/ov021/calls/DispatchScriptHandler.c](../src/overlays/ov021/calls/DispatchScriptHandler.c).

### Established limit

The two callback installations, their actual handler semantics and the supplied scalar's role are not proven. Same-offset callback fields in other owners do not complete this contract.

### Searches already performed and next proof

Source search for18f54/18f58 found only this callback invocation pair in the reviewed021 source views. The first receives(member,GetGlobalScaleValue()), the second(member,contextVector). Ghidra finds no direct function reference; expression-table dispatch is indirect.

Next proof: Recover stage-manager callback installation, signature and GetGlobalScaleValue producer; then name the resulting vector action from real handlers.

## func_ov021_020b2044

Identity: `ov021:020b2044`, THUMB, configured native extent 44 bytes (including any pool). Source: [eu/src/overlays/ov021/calls/func_ov021_020b2044.c](../src/overlays/ov021/calls/func_ov021_020b2044.c).

```c
u32 func_ov021_020b2044(u32 self, int args);
```

- Inputs: Stage-script context and three tagged operands at offsets 0, 8 and 0x10. The first old-style C call relies on the incoming native registers.
- Mechanical effects: Resolve all three operands in order. Using the first resolved value, call ResolveStageScriptCommandDataOffset. Discard the returned address. The native instructions contain no direct stores in this command.
- Result/lifetime: Opcode status 0. Resolver/expression side effects are retained; this is not safely replaceable by an empty function.

### Callers, registration and ROM references

- `ov021:020b4a94` contains `020b2045`. The configured relocation records this target bank. Storage: [eu/src/overlays/ov021/calls/InitScriptHandlerTable.c](../src/overlays/ov021/calls/InitScriptHandlerTable.c).
- Reachable literal load `ov021:020b4982` in `InitScriptHandlerTable` reads pointer pool `020b4a94`: `ldr r0, [pc, #0x110]`.
- The initializer installs this pointer in runtime stage command handler slot 60; its shared source and EU aliases establish the registration.

### Writers and related source evidence

[eu/src/overlays/ov021/calls/InitScriptHandlerTable.c](../src/overlays/ov021/calls/InitScriptHandlerTable.c), [src/ov021/script_ops/InitScriptHandlerTable_020b4884.c](../../src/ov021/script_ops/InitScriptHandlerTable_020b4884.c).

### Established limit

The native listing confirms the discarded calculation, so an omitted store in the recovered C is not the current explanation. Its intended command/bytecode role remains unknown; no memory-copy, decode or other operation is invented.

### Searches already performed and next proof

Compared EU native instructions: BL ResolveTaggedValueRef at204a,2056,2060; BL data-offset helper at2068; MOVr0,0 at206c. The calculated address is indeed discarded and there are no direct stores. The three evaluations may have expression side effects, so replacing this by a no-op is invalid.

Next proof: Recover opcode/bytecode identity or original command contract. An operational evaluate-only description is possible, but no memory-transfer or other intended role is claimed.

## func_ov021_020b2fec

Identity: `ov021:020b2fec`, THUMB, configured native extent 100 bytes (including any pool). Source: [eu/src/overlays/ov021/calls/func_ov021_020b2fec.c](../src/overlays/ov021/calls/func_ov021_020b2fec.c).

```c
u32 func_ov021_020b2fec(u32 context, s32 operands);
```

- Inputs: Stage-script context and four tagged operands: an index followed by three values. Preserve evaluation order and native first-call register forwarding.
- Mechanical effects: Copy the three raw value words to stage manager + index*0x20 + 0x18e8c/0x18e90/0x18e94.
- Result/lifetime: Opcode status 0. There is no index check, conversion, allocation or result-vector write.

### Callers, registration and ROM references

- `ov021:020b4a5c` contains `020b2fed`. The configured relocation records this target bank. Storage: [eu/src/overlays/ov021/calls/InitScriptHandlerTable.c](../src/overlays/ov021/calls/InitScriptHandlerTable.c).
- Reachable literal load `ov021:020b4948` in `InitScriptHandlerTable` reads pointer pool `020b4a5c`: `ldr r0, [pc, #0x110]`.
- The initializer installs this pointer in runtime stage command handler slot 53; its shared source and EU aliases establish the registration.

### Writers and related source evidence

[eu/src/overlays/ov021/calls/InitScriptHandlerTable.c](../src/overlays/ov021/calls/InitScriptHandlerTable.c), [src/ov021/script_ops/InitScriptHandlerTable_020b4884.c](../../src/ov021/script_ops/InitScriptHandlerTable_020b4884.c), [src/ov021/script_ops/ScriptOp_SetStageMarker_020b2f58.c](../../src/ov021/script_ops/ScriptOp_SetStageMarker_020b2f58.c), [src/ov021/script_ops/ScriptOp_SpawnLinkedWalkers_020b3114.c](../../src/ov021/script_ops/ScriptOp_SpawnLinkedWalkers_020b3114.c).

### Established limit

These are the trailing three words in the reviewed 32-byte marker/spawn layout, not its VecFx32 offset. Their readers and individual meanings remain unproven.

### Searches already performed and next proof

SetStageMarker and SpawnLinkedWalkers place32-byte records at18e78; this helper writes at18e8c/90/94, corresponding to the trailing three words of that layout, not its VecFx32 offset. The vector hypothesis is disproven for that view.

Next proof: Find exact readers of those three trailing words per indexed record; do not name them a position or vector.

## func_ov030_020bcec0

Identity: `ov030:020bcec0`, THUMB, configured native extent 130 bytes (including any pool). Source: [eu/src/overlays/ov030/calls/func_ov030_020bcec0.c](../src/overlays/ov030/calls/func_ov030_020bcec0.c).

```c
void func_ov030_020bcec0(u32 base, u32 source, u32 record);
```

- Inputs: Unit/base pointer, a slot input passed to ActivateSpawnUnit, and a descriptor pointer. Resolve the actor owner from signed byte base +0x3c.
- Mechanical effects: If active count +0x3f is zero, clear byte +0x40. Always activate/place the spawn unit and obtain its VecFx32 position. If signed active count +0x3f is below limit +0x3e, set byte +0x1b0 to 1; clear +0x1a0, +0x1a4 and +0x1b4; copy descriptor bytes +4/+5 to +0x1a8/+0x1a9 and descriptor word +8 to +0x1ac; store placement minus actor position +0xbc into base +0x194; increment active count.
- Result/lifetime: void. ActivateSpawnUnit uses a native hidden composite-return destination; the C VecFx32 return view preserves that operation.

### Callers, registration and ROM references

- `ov056:020d811c` contains `020bcec1`, `data_ov056_020d80d0[19]`. The configured relocation admits overlays(30,38); this does not uniquely prove the runtime bank. Storage: [eu/src/ov056/data/Data_ov056_020d80d0.c](../src/ov056/data/Data_ov056_020d80d0.c).

### Writers and related source evidence

[eu/src/ov056/data/Data_ov056_020d80d0.c](../src/ov056/data/Data_ov056_020d80d0.c), [src/ov056/unclassified_helpers/DispatchSourceKindEvent_020d7db4.c](../../src/ov056/unclassified_helpers/DispatchSourceKindEvent_020d7db4.c), [eu/src/overlays/ov021/calls/ActivateSpawnUnit.c](../src/overlays/ov021/calls/ActivateSpawnUnit.c), [src/ov030/shared_engine/UpdateCarriedLauncher_020bc900.c](../../src/ov030/shared_engine/UpdateCarriedLauncher_020bc900.c).

### Established limit

The indirect table is indexed by source.kind +0x3d. Its raw pointer is real, but the configured relocation allows overlays30 and38 at the same numeric address. The callback's exact factory/updater linkage and descriptor fields still require bank/lifetime proof. Hitting the count limit does not suppress the earlier placement call.

### Searches already performed and next proof

Located indirect registration at data_ov056_020d80d0[19]; DispatchSourceKindEvent selects it from source.kind+3d with(source,arg1,arg2). Native ASM confirms the hidden composite-return output pointer used for ActivateSpawnUnit, then a bounded active-count increment and owner-relative vector. UpdateCarriedLauncher shares mode1b0 but its duration/interval fields differ from descriptor writes here; exact owner/factory link still needed.

Next proof: Prove source kind19 factory/updater identity and each descriptor field. Then determine whether this begins a burst/launcher action; do not name it from similar actor callbacks.

## Closed board-node getter

The former ov032:020bb828 entry is now [GetCurrentBoardNodeCode](CURRENT_BOARD_NODE_CODE.md). The SessionBuffer10 owner, six code writers and native signed-byte loads close its former lock/rank/variant ambiguity.

## Closed timed-cue and effect-kind helpers

The [timed-cue group selector](STAGE_EVENT_TIMED_CUE_GROUP.md) now has its actual section16/10 consumer, distinct from collision cues. The [effect-kind expression](STAGE_EVENT_EFFECT_KIND.md) has actual writers, duration/expiration and hit-effect consumers; individual effect codes remain opaque.
