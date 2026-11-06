# Current stage motion-record word 6

`StageScriptExpr_GetCurrentMotionRecordWord6` copies a raw word from the record selected by the current stage event. **Word 6 is a zero-based 32-bit word position: byte offset 0x18.** The record owner and extent are proved; the word's gameplay meaning remains opaque.

| EU identity | Name | Source after rename |
| --- | --- | --- |
| `ov021:020b0edc` | `StageScriptExpr_GetCurrentMotionRecordWord6` | `eu/src/overlays/ov021/calls/StageScriptExpr_GetCurrentMotionRecordWord6.c` |

## Exact result contract

The helper retains its current `u32 (int self)` source declaration and these operations:

1. Read the active event pointer from the first word of `gActiveFieldContextStorage` at `ov021:020b56c4`. If it is zero, return opcode status 0 without changing the tagged result.
2. Read the event's halfword at +0x16 and pass it to `GetStageMotionRecord`. If the returned pointer is zero, again leave the result unchanged and return 0.
3. Store integer tag 1 as a halfword at context +0x2c, copy the raw 32-bit record word at +0x18 to context +0x30, and return opcode status 0.

No normalization, fixed-point conversion or unit conversion occurs. The opcode status is separate from the tagged value. A numeric zero in the record is still a successfully copied tagged value.

Native proof: `020b0eec` reads event +0x16; `020b0eee` calls resolver `0209c1b4`; `020b0efc` writes tag 1; `020b0efe/020b0f00` copies the record word. The two early returns precede both result stores.

## Concrete owner and common extent

`GetStageMotionRecord` resolves the pool pointer at `gStageManager +0x18d98` and forwards the handle to `GetHandlePoolElement`. The stage-manager constructor installs this exact pool with backing storage at manager +0x17a14, **stride 0x40 and capacity 0x20**. It is the `buffersA` pool in the constructor's private view.

This gives each valid pool element 64 bytes, or 16 aligned 32-bit word positions. Word 6 lies within that common extent. This count does not create a new C array or a complete portable record layout.

The native ownership chain is explicit:

- `CreateStageManager` loads backing offset `0x17a14`, supplies stride `0x40` and count `0x20` at `02099830/02099834`, creates the pool at `02099838`, and stores it at `0x18de4 - 0x4c = 0x18d98` at `02099840`.
- `HandlePool_Create` stores the backing pointer at pool +0x0c, element size at +0x10 and capacity at +0x12 (`0208f08c/0208f08e/0208f094`).
- `GetStageMotionRecord` loads offset `0x18d98` and invokes `GetHandlePoolElement` at `0209c1c4`.
- `GetHandlePoolElement` uses the stored element size and computes `elements + elementSize * u16(handle - 1)` (`0208f280..0208f28c`).
- `ClearStageTables` clears the same 0x800-byte backing region, covering all 32 elements (`src/ov001/shared_engine/ClearStageTables_0209a094.c:47`; native call at `0209a10a`).

Sources: `src/ov001/shared_engine/CreateStageManager_02099628.c:161`, `src/ov001/unclassified_helpers/HandlePool_Create_0208f038.c:28`, `src/ov001/shared_engine/GetStageMotionRecord_0209c18c.c:14`, and `eu/src/overlays/ov001/calls/GetHandlePoolElement.c:3`.

The pool accessor does not check capacity or activity. In particular, handle zero is narrowed after subtracting one; it is not automatically a safe NULL result. The getter's two NULL checks remain exactly as implemented and do not establish validity for arbitrary handles.

## Active-event setup, writer and dispatch

`RunScriptThread` backs up and clears the active field context, then installs `GetStageEventRecord(thread->ownerId)` when the owner kind is 1 (`eu/src/overlays/ov021/calls/RunScriptThread.c:64`). Native `020b4c56/020b4c5c` performs that resolve/store. This establishes which event owns the +0x16 handle used by the expression. Other thread-owner kinds do not create a fabricated event pointer.

There is an independently traced writer through the same resolver. `ScriptCmd_SetProperty` resolves `event->motionId` (`eu/src/overlays/ov021/calls/ScriptCmd_SetProperty.c:609`) and, in its property-0x87 branch, zeros the record's three vector views (`eu/src/overlays/ov021/calls/ScriptCmd_SetProperty.c:769`). The second vector covers bytes +0x10 through +0x1b, including word 6.

Original ROM `020b40be` calls the same resolver and `020b40c4` retains its pointer at stack +0x10. The writer loads the original zero-vector constant at `0205344c`, sets R5 to record +0x10 for the second 12-byte copy, advances R5 by eight through `STM`, and stores that copy's last word at **record +0x18** at `020b4474`. This confirms same-owner writing without exporting a universal vector/component meaning: other consumers use these records through motion, grid and slot views.

The original query table registers the expression at `gScriptQueryHandlers[100]`: word `ov021:020b54e8` is `020b0edd`, including the Thumb bit. The source table is `eu/src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c:183`.

`ScriptOp_DispatchIndexedCommand` initializes tag 1/value 0 before invoking a selected non-NULL query handler (`src/ov021/script_ops/ScriptOp_DispatchIndexedCommand_020b39a8.c:13`; native stores `020b39d4/020b39d8` and invocation `020b39ea`). That ordinary caller therefore supplies a default zero, while direct invocation of the helper can preserve an earlier result on its missing-event/record path. The dispatcher discards the helper's status and returns 0 itself.

## Porting boundary and validation

The name identifies the owner and raw operation. It does not call word 6 a position, speed, timer, property, unit or enum, and does not adopt one private struct view as a universal layout. Existing `int` address arithmetic and old-style resolver declarations remain unchanged in this naming block; no host ABI or new parameter is introduced.

Research captured the complete original getter, resolver, pool constructor, stage-manager constructor/reset, active-context setup, property writer and dispatcher, with separately decoded writer windows for code beyond inline pools. Both involved original overlays match their extracted modules, and MAIN evidence windows match the extracted MAIN bytes. The candidate has an exact complete active delink owner. No compiler or official gate ran in this review; integration matching and module-invariance receipts are pending.


## Active EU sources

- [StageScriptExpr_GetCurrentMotionRecordWord6](../src/overlays/ov021/calls/StageScriptExpr_GetCurrentMotionRecordWord6.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptExpr_GetCurrentMotionRecordWord6.c StageScriptExpr_GetCurrentMotionRecordWord6 --thumb
bash tools/gate.sh
```
