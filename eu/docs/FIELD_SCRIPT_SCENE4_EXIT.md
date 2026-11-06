# Script request to leave the field for primary scene 4

`ScriptCmd_RequestFieldExitToScene4` is ov001:02065e8c, Thumb, 22 bytes, with the unchanged native declaration u32(s32 entry). Its EU source is src/overlays/ov001/calls/ScriptCmd_RequestFieldExitToScene4.c. The ROOT body remains src/ov001/unclassified_helpers/func_ov001_02065e8c.c.

The command calls SetPendingFieldValue(3), clears the VM status word at +0x1cc and returns 3. SetPendingFieldValue writes session halfword +0x210 only if it was -1, preserving an earlier pending exit request. MAIN ScriptVm_RunFrame treats command return 3 as stream completion and returns 0. RunSessionScriptFrame then returns the cleared VM status, 0.

The field phase handlers route this completed script to phase 11, HandleSessionScriptResult. A nonnegative exit kind selects phase 12, ExitSessionAndCommitSave. Its case 3 calls SetPendingScene(4, 0). This exact consumer establishes the destination. Scene 4 remains a numeric dispatcher identity; no title, menu or gameplay meaning is assigned.

The command ends its stream even if a different request was already pending. It therefore requests scene 4 without guaranteeing arrival there. Preserve the existing unprototyped setter declaration, first-request rule, VM status clear and command return. No new arguments, guards, cancellation or scene enum is introduced.

RESULTS_TRANSITION_SCROLL5_REVIEW_V1.json records source paths and hashes, numbered writer/consumer evidence, exact script-table words and complete original BK9P NDS function comparisons. Native declarations and bodies remain unchanged.




## Active EU sources

- [ScriptCmd_RequestFieldExitToScene4](../src/overlays/ov001/calls/ScriptCmd_RequestFieldExitToScene4.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_RequestFieldExitToScene4.c ScriptCmd_RequestFieldExitToScene4 --thumb
bash tools/gate.sh
```
