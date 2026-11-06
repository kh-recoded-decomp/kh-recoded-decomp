# Stage operands and marker auxiliary words

`StageScriptOp_ResolveDataOperands` (ov021:020b2044, opcode 60) resolves three tagged references in order, then reads the first reference's value and computes a buffer-relative address. It discards that address and returns 0. The actual command and resolver chain contain no stores. Earlier concern about possible expression side effects did not establish a mutation; this name describes only the observed resolution operation. Original command intent remains unknown. Preserve the calls, reads, evaluation order and native forwarding rather than replacing them with an empty body.

`StageScriptCmd_SetStageMarkerAuxiliaryWords` (ov021:020b2fec, opcode 53) evaluates an index and three values. It stores them at manager+0x18e78+index*32+0x14/+0x18/+0x1c, the tail of a marker/spawn record. ScriptOp_SetStageMarker writes its preceding flags, position and radius. SpawnLinkedWalkers reads only the middle auxiliary word as a Y-rotation table angle after shifting right by four. The outer two words remain opaque; they are not established as rotation-vector components.

Keep unchecked index arithmetic, raw values and store widths. [The workspace contract](STAGE_SHARED_WORKSPACE.md) explains the shared lifetime and overlapping probe view. These names introduce no new fields, allocation or ABI.


## Active EU sources

- [StageScriptOp_ResolveDataOperands](../src/overlays/ov021/calls/StageScriptOp_ResolveDataOperands.c).
- [StageScriptCmd_SetStageMarkerAuxiliaryWords](../src/overlays/ov021/calls/StageScriptCmd_SetStageMarkerAuxiliaryWords.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptOp_ResolveDataOperands.c StageScriptOp_ResolveDataOperands --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptCmd_SetStageMarkerAuxiliaryWords.c StageScriptCmd_SetStageMarkerAuxiliaryWords --thumb
bash tools/gate.sh
```
