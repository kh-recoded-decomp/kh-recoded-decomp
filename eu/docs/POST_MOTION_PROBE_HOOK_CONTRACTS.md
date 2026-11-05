# Post-motion and post-probe hooks

These two native hooks perform no memory work and explicitly return zero. They are not the residual-register empty callbacks documented elsewhere. Their names identify a proven post-worker slot; they do not assign completion/event/cleanup semantics or invent an input parameter. The source still returns literal zero, and its legacy library template spelling does not establish an SDK role.

`Entity_PostLinkedMotionNoop` is called only after ApplyLinkedObjectMotion when the entity command pending count is nonzero and mask 0x20800 is clear. `ApplyPendingEntityMotion` propagates the zero through its epilogue, but its sole outer caller RefreshActorState replaces r0 with the saved entity at ov052:0x020cce3a before use.

`Actor_PostLinkedMeshProbeNoop` is called only after ProbeLinkedMeshEntries when actor mask 0x800 is clear. The wrapper propagates zero through its epilogue, but its sole outer caller Actor_UpdateChargeAttack restores actor in r0 at ov059:0x020c805a before the next call. The preceding instructions load other registers and do not consume r0.

Refreshed xrefs identify exactly those direct and outer callsites. Skipping a wrapper branch can preserve a different incoming register word; do not infer that either outer wrapper is a normalized BOOL query. This is name-only integration, not a signature or control-flow rewrite.

| Original EU identity | Name | Mode / bytes | Planned EU source |
|---|---|---|---|
| `Entity_PostLinkedMotionNoop` | `Entity_PostLinkedMotionNoop` | THUMB / 0x4 | `src/overlays/ov052/auto/Entity_PostLinkedMotionNoop.c` |
| `Actor_PostLinkedMeshProbeNoop` | `Actor_PostLinkedMeshProbeNoop` | THUMB / 0x4 | `src/overlays/ov059/auto/Actor_PostLinkedMeshProbeNoop.c` |


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov052/auto/Entity_PostLinkedMotionNoop.c Entity_PostLinkedMotionNoop --thumb
python tools/verify_idx.py src/overlays/ov059/auto/Actor_PostLinkedMeshProbeNoop.c Actor_PostLinkedMeshProbeNoop --thumb
bash tools/gate.sh
```
