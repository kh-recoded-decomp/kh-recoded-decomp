# Two recovered overlay entry identities

A DS overlay address is meaningful together with its loaded bank. Two EU
adapters used aliases to unrelated objects at the same numeric RAM addresses.
This block corrects those local bindings and narrows their relocation owners
using the actual overlay-loading paths. It does not globally rename either old
object or change an instruction, data byte or load order.

| Caller | Correct target | Separate object at the same RAM address |
|---|---|---|
| `InstallSessionOv036Handlers`, ov001:02062c0c, Thumb, 24 bytes | `InitPanelCallbackTable`, ov036:020bc4c8, ARM | `data_ov035_020bc4c8`, the real ov035 model-name format data. |
| `IsShapeWithinActiveCameraView`, ov021:020af758, Thumb, 64 bytes | `IsShapeInViewDepth`, ov043:020bd20c, ARM | `dispatch_input_handler_pair_20`, the independent ov039 input dispatcher. |

## Session state 8 and overlay036

`SetSessionState` obtains the requested state's overlay ID, loads that bank and
selects its installer. State 8 selects overlay 36. The installer passes the
session address plus 0x280c in r0 and tail-branches through ARM address
0x020bc4c8. The actual ov036 body at that address installs nine callbacks.

The old alias `data_ov028_020bc4a8 -> data_ov035_020bc4c8` in this EU wrapper is
now bound to `InitPanelCallbackTable`. Its literal relocation at 0x02062c1c is
narrowed from candidate overlays (35,36,38) to overlay 36. The literal address
and BX boundary remain unchanged.

The ov035 data definition and its `LoadFadeModel` consumer remain separate. The
format starts with `%s%02d`; the nearby `area` string and its data bank are not
callback code. Equal RAM addresses cannot identify those objects across banks.

The session callback storage begins at +0x280c. Other installers and consumers
establish twelve native 32-bit slots, through +0x2838: a 48-byte view. The old
`overlayWork[0x10]` declaration in the shared adapter is a placeholder prefix,
not an allocation bound. The slots have different signatures and null rules;
do not turn them into one universal host `void(void)` callback array.

This block retains the erased native function-address call for its exact
interworking sequence. Its logical target is an initializer taking a callback
table pointer. Recovering typed host callbacks is separate from preserving the
DS entry boundary; the old function-as-data declaration is not a portable API.

Source proof: `src/overlays/ov001/calls/SetSessionState.c`,
`src/overlays/ov001/data/tables/gFieldSessionClassData.c`,
`src/overlays/ov001/calls/InstallSessionOv036Handlers.c` and
`src/overlays/ov036/calls/InitPanelCallbackTable.c`, read with their shared US
implementations and current EU aliases.

## Camera mode 2 and overlay043

`StartSubMode` loads the camera bank selected by the mode before initializing
it. Mode 2 selects overlay043. In this mode the shape-visibility dispatcher
calls ARM address 0x020bd20c with the shape and margin still in r0/r1.
The actual ov043 implementation is `IsShapeInViewDepth`, which applies the
scene's negative-Z depth limit and the existing four-plane shape test.

The local alias `func_ov043_020bd1ec -> dispatch_input_handler_pair_20` is now
bound to `IsShapeInViewDepth`. The BLX relocation at 0x020af784 is narrowed from
candidate overlays (39,43) to overlay43. The unrelated ov039 dispatcher and all
its input consumers keep their own symbol and bytes.

The switch is preserved: modes 0 and 3 use the MAIN plane test, mode 1 uses the
view-space bounds test, mode 2 uses the depth-and-plane test, and the default
returns zero. The logical inputs are shape and margin; an old omitted callee
argument or private label does not make the second input a plane count. The
shared DS adapter remains unchanged apart from its name and corrected binding;
this block does not claim that every legacy declaration is a typed host API.

The separate plane-normal dispatcher has its own preconditions. Its mode-1
address is not established as a getter in overlay042, and normal mode-1
visibility uses the bounds path. This correction does not rewrite that branch
or assert a universal four-plane view for every camera mode.

Source proof: `src/overlays/ov021/calls/StartSubMode.c`, the shared mode-loader
table, `src/overlays/ov021/calls/IsShapeWithinActiveCameraView.c` and
`src/overlays/ov043/calls/IsShapeInViewDepth.c`. Read-only Ghidra queries use
`program=recoded.nds` and the corresponding `arm9_ovNNN` address space, with ROM
instructions checked at both targets.

## Verification

From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/InstallSessionOv036Handlers.c InstallSessionOv036Handlers --thumb
python tools/verify_idx.py src/overlays/ov021/calls/IsShapeWithinActiveCameraView.c IsShapeWithinActiveCameraView --thumb
bash tools/gate.sh
```

The official per-function checks retain 24 and 64 bytes. Integration compares
affected production texts, resolved relocation targets/types and addends to the
saved baseline, and requires all 108 linked module hashes to remain identical.
The source/loading-path proof establishes the bank identity in addition to the
byte check; a matching absolute address alone would not distinguish the banks.
