# Script control of the scene scroll speed target

`ScriptCmd_SetSceneScrollSpeedTarget` is ov001:0206595c, Thumb, 46 bytes. Its native declaration remains int(void *context, ScriptCommand *command), and its EU source is src/overlays/ov001/calls/ScriptCmd_SetSceneScrollSpeedTarget.c. The ROOT body remains src/ov001/unclassified_helpers/func_ov001_0206595c.c.

The command reads an integer selector and an fx32 acceleration amount. A nonzero selector supplies GetCurrentRecordTargetScrollSpeed() as the target; zero supplies target 0. It then calls the overlay 031 setter and returns 1 to advance the VM command. The current-record target is distinct from the currently interpolated scroll speed.

SetSceneScrollSpeedTarget writes the target at scene work +0x30 and the acceleration step at +0x34. UpdateSceneScroll approaches that target by the step and moves scene groups along the scene direction. BeginNextRecord uses record +0x14 for this same target and passes it to the same setter. The private record label position therefore does not denote a position here.

Preserve the current native u32 callee declarations, fixed-point decode, operand evaluation order, return value and absent record guard. The acceleration is consumed per native update; seconds, a frame rate and host timestep conversion are not established by this command.

RESULTS_TRANSITION_SCROLL5_REVIEW_V1.json records source paths and hashes, numbered writer/consumer evidence, exact script-table words and complete original BK9P NDS function comparisons. Native declarations and bodies remain unchanged.




## Active EU sources

- [ScriptCmd_SetSceneScrollSpeedTarget](../src/overlays/ov001/calls/ScriptCmd_SetSceneScrollSpeedTarget.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_SetSceneScrollSpeedTarget.c ScriptCmd_SetSceneScrollSpeedTarget --thumb
bash tools/gate.sh
```
