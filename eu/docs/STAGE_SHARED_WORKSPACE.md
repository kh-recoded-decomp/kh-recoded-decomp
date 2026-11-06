# Stage-manager shared workspace

`StageScriptExpr_GetStageWorkspaceWord0` (ov021:020b0af0) reads manager+0x18e78. `StageScriptExpr_GetStageWorkspaceWord1` (ov021:020b0ad4) reads +0x18e7c. Both preserve their native integer tag 1, raw 32-bit result and opcode status 0, without a manager NULL guard.

The task descriptor allocates 0x18f60 bytes of cleared work; CreateStageManager publishes that work through gStageManager, and release destroys it and clears the global. These reads therefore share the manager's lifetime.

Two proven access views overlap. ScriptOp_SetStageMarker writes two 32-byte marker/spawn records starting at +0x18e78, consumed by SpawnLinkedWalkers. ProcessStageCues also copies a collision-query point into the first 12 bytes. Its attempted-probe path copies even when the probe reports FALSE; do not infer a successful hit or a fresh value from a read.

Word 0 can consequently contain marker flags or raw probe X bits, and word 1 can contain marker position.x or raw probe Y bits. Preserve storage sharing, raw bits and lifetime. The evidence does not prove an original C union or justify universal field types, freshness checks or extra allocation.


## Active EU sources

- [StageScriptExpr_GetStageWorkspaceWord0](../src/overlays/ov021/calls/StageScriptExpr_GetStageWorkspaceWord0.c).
- [StageScriptExpr_GetStageWorkspaceWord1](../src/overlays/ov021/calls/StageScriptExpr_GetStageWorkspaceWord1.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptExpr_GetStageWorkspaceWord0.c StageScriptExpr_GetStageWorkspaceWord0 --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptExpr_GetStageWorkspaceWord1.c StageScriptExpr_GetStageWorkspaceWord1 --thumb
bash tools/gate.sh
```
