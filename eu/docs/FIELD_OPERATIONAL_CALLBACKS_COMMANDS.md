# Field draw hooks, panel phase and literal-result script commands

These five operational names identify native owners, callback slots or VM
results. They preserve the existing matched bodies, signatures and erased
declarations. They do not claim original source spelling or an unknown
gameplay purpose.

| EU identity | Name | Existing signature / effect |
| --- | --- | --- |
| ov001:020876d4 | `FieldScene_DrawHookNoop` | void(void); empty Thumb BX LR. |
| ov001:0207abd8 | `MenuOverlay_Phase0Noop` | void(void); empty Thumb BX LR. |
| ov001:0206312c | `FieldScriptCommand0_Noop` | void(void); empty Thumb BX LR. |
| ov001:02064e5c | `ScriptCmd_FieldNoop0` | int(void*); calls the no-op and returns 1. |
| ov001:02065a24 | `ScriptCmd_FieldOp41RunZero` | int(void); returns 0. |

## Scene draw hook

The hook is called by the draw pipelines of overlays028,029,030,031,032
and035. The six owning frame runners invoke those pipelines under their
work flags mask 0x4. The inherited ov031 name `LeaveState` does not identify
a leave-state callback: its actual caller selects it in that draw phase.

In028/029/030/031/032 the hook follows `UpdateActorSlotsAndBillboards`.
Overlay031 also draws scene groups earlier. Overlay035 invokes it inside
`DispatchSceneDrawCallbacks` under context+0x22 mask 0x10, independently
of the actor/billboard mask 0x40. Other drawing may follow it. Native R0
is preserved by the empty function and is not interpreted as a status by
these pipelines or their frame runners.

The name records a no-op extension point in that phase. It does not imply
drawing work, a flush, cleanup, final-frame timing or a universal scene flag
enum. No pointer ownership or output is involved.

## Panel phase 0

`gMenuOverlayStateHandlers[0]` contains pointer 0x0207abd9.
`UpdatePanelScene` selects by the same panel's word +0x30 and supplies
`gSubscenePanelWork` in R0. It discards the residual result. The no-op
leaves every panel field unchanged.

This name deliberately says phase 0. It does not say idle or inactive and
does not claim that a persistent transition currently reaches the slot.
`InitFieldPanelScene` clears the work and synchronously writes phase 2
before handing control to the dispatcher. `RequestPanelModeChange`
accepts 0/6 with an independent guard, but is not a writer of phase 0. Finding
a persistent same-owner phase 0 transition remains a separate research gap.

## Field command 0

`EnterPendingRoom` registers `gFieldScriptCommandHandlers` at group 2
through `StoreGlobalArrayEntry`. The MAIN `ScriptVm_RunFrame` selects
the group and then its native eight-byte run/resume pair. Entry 0 is
`ScriptCmd_FieldNoop0` with a null resume pointer.

The wrapper reads no script operands. It forwards native R0 unchanged to
the empty `FieldScriptCommand0_Noop`, ignores the residual R0, then writes
literal 1. For ordinary MAIN execution this result clears the main resume,
advances by the encoded command length and continues. On the auxiliary
path, its nonzero result clears that selected callback/argument and the
interpreter advances. It is not a filesystem-unload success result.

The helper's actual definition is no-input `void(void)`; the wrapper's
legacy declaration takes a pointer. Their register behavior is documented
without adding an invented parameter. The erased table declaration also
remains unchanged; a typed port must reconcile it with the VM's actual
`run(vm, operands)` interface. No initialization/unloading/reserved purpose
is inferred from opcode 0.

## Field command 0x41

Entry 0x41 is `ScriptCmd_FieldOp41RunZero` with a null resume. Its body
consumes no input and returns literal 0. This name states the table owner,
opcode and run result without inventing an intent.

For an ordinary MAIN command, 0 stores the null resume, retains the cursor
and returns 1 to the frame caller. With no resume installed, a later MAIN
pass issues the same command again unless external VM state changes.
For a nonzero header slot while not skipping, the auxiliary path instead
stores that null resume and saved argument, clears the main resume and
advances. A null callback cannot be polled in the auxiliary slot. This is
not a universal Wait, Yield or Halt command. The distinct protocols must
remain distinct in a port.

Evidence sources:

- `eu/src/overlays/ov001/auto/FieldScene_DrawHookNoop.c`
- `eu/src/overlays/ov028/calls/DrawOv028FieldScene.c`
- `eu/src/overlays/ov029/calls/DrawOv029FieldScene.c`
- `eu/src/overlays/ov030/calls/DrawOv030FieldScene.c`
- `eu/src/overlays/ov031/calls/LeaveState.c`
- `eu/src/overlays/ov031/calls/RunStateMachine.c`
- `eu/src/overlays/ov032/calls/DrawOv032FieldScene.c`
- `eu/src/overlays/ov035/calls/DispatchSceneDrawCallbacks.c`
- `eu/src/overlays/ov035/calls/RunMovieSceneFrame.c`
- `eu/src/overlays/ov001/auto/MenuOverlay_Phase0Noop.c`
- `eu/src/overlays/ov001/calls/InitFieldPanelScene.c`
- `eu/src/overlays/ov001/calls/UpdatePanelScene.c`
- `eu/src/overlays/ov001/calls/RequestPanelModeChange.c`
- `eu/src/overlays/ov001/data/tables/gMenuOverlayStateHandlers.c`
- `eu/src/overlays/ov001/auto/FieldScriptCommand0_Noop.c`
- `eu/src/overlays/ov001/calls/ScriptCmd_FieldNoop0.c`
- `eu/src/overlays/ov001/auto/ScriptCmd_FieldOp41RunZero.c`
- `eu/src/overlays/ov001/data/tables/gFieldScriptCommandHandlers.c`
- `eu/src/overlays/ov001/calls/EnterPendingRoom.c`
- `eu/src/calls/StoreGlobalArrayEntry.c`
- `eu/src/calls/ScriptVm_RunFrame.c`

The original functions and table words in the research receipt were
compared directly with the extracted EU ROM. No candidate was compiled;
official configured-path checks and the full gate remain integration work.


## Active EU sources

- [FieldScene_DrawHookNoop](../src/overlays/ov001/auto/FieldScene_DrawHookNoop.c).
- [MenuOverlay_Phase0Noop](../src/overlays/ov001/auto/MenuOverlay_Phase0Noop.c).
- [FieldScriptCommand0_Noop](../src/overlays/ov001/auto/FieldScriptCommand0_Noop.c).
- [ScriptCmd_FieldNoop0](../src/overlays/ov001/calls/ScriptCmd_FieldNoop0.c).
- [ScriptCmd_FieldOp41RunZero](../src/overlays/ov001/auto/ScriptCmd_FieldOp41RunZero.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/auto/FieldScene_DrawHookNoop.c FieldScene_DrawHookNoop --thumb
python tools/verify_idx.py src/overlays/ov001/auto/MenuOverlay_Phase0Noop.c MenuOverlay_Phase0Noop --thumb
python tools/verify_idx.py src/overlays/ov001/auto/FieldScriptCommand0_Noop.c FieldScriptCommand0_Noop --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_FieldNoop0.c ScriptCmd_FieldNoop0 --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScriptCmd_FieldOp41RunZero.c ScriptCmd_FieldOp41RunZero --thumb
bash tools/gate.sh
```
