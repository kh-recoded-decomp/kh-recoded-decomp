# Field-scene transition hook

`InvokeFieldSceneTransitionHook` is ov001:02064de8, Thumb, 28 bytes, with the unchanged native declaration void(void). Its EU source is src/overlays/ov001/calls/InvokeFieldSceneTransitionHook.c; the ROOT body remains src/ov001/unclassified_helpers/func_ov001_02064de8.c.

The field session owns a 48-byte callback table beginning at +0x280c. The helper loads its optional hook at +0x2838, calls it without logical arguments when present and discards its return. It does not access a heap or a TaskObject work pointer.

InstallSessionOv028Handlers, InstallSessionOv030Handlers and InstallSessionOv031Handlers pass this exact table to their bank-qualified scene installers. Each writes the hook at table +0x2c. The targets are BeginFieldSceneSlowdownTransition, SuspendSceneAtQuarterRate and ResetSceneState, respectively. Their actual bodies pause field entries, prepare the screen transition, call the primary actor reset hook if present, stop sequence players from slot 2 and set scene flag 0x40. Preserve backend-specific extra operations, including overlay 028's camera flag.

The paired slot at table +0x28, session +0x2834, provides the transition check. The script run command ScriptCmd_InvokeSessionCallback invokes the transition hook and returns 0. Its registered resume ScriptCmd_TestSessionCheckCallback waits while the installed check returns nonzero; a zero result or an absent check completes that resume. The native run return is 0, not 1. RunSessionCheckCallback returns TRUE when its check is absent. These original-code facts correct contradictory notes in the historical callback review.

Do not assign a single signature to all table slots, add a missing-hook error, treat transition flags as Boolean-normalized data or infer a universal shutdown operation. The original nullable hook, callback return handling and VM protocol remain intact.

RESULTS_TRANSITION_SCROLL5_REVIEW_V1.json records source paths and hashes, numbered writer/consumer evidence, exact script-table words and complete original BK9P NDS function comparisons. Native declarations and bodies remain unchanged.




## Active EU sources

- [InvokeFieldSceneTransitionHook](../src/overlays/ov001/calls/InvokeFieldSceneTransitionHook.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/InvokeFieldSceneTransitionHook.c InvokeFieldSceneTransitionHook --thumb
bash tools/gate.sh
```
