# Scene-group contact callback

The callback registration, dispatcher and result consumers establish this EU
contact contract. The existing prototype and callback behavior are preserved.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov031:020bb5b8` | THUMB | `func_ov031_020bb5b8` | `MarkMixedKind2SceneGroupContactAndStop` | [eu/src/overlays/ov031/calls/MarkMixedKind2SceneGroupContactAndStop.c](../src/overlays/ov031/calls/MarkMixedKind2SceneGroupContactAndStop.c) |

## MarkMixedKind2SceneGroupContactAndStop

```c
u32 MarkMixedKind2SceneGroupContactAndStop(u32 unused, int *entry);
```

Identity: `ov031:020bb5b8`, THUMB, configured native extent30 bytes.

The scene builder creates polygon collision objects and installs this helper in their callback pair at+0x78. The shared collision dispatcher proves this pair is the object-contact hook, despite the private onStay label in the builder source. Its second input is mover.owner, not a contact plane, collision object or arbitrary scene work pointer.

- Inputs: Full dispatcher supplies9 arguments; this native implementation uses only the second, with parent pointer at+0 and kind at+4.
- Result and effects: If owner is nonnull,owner.kind==2,parent.kind!=2: writes parent+8=1 and returns2. Otherwise returns1. Code2 propagates to stop the current contact traversal.
- Lifetime: No allocation/free and no returned pointer. Parent storage belongs to the incoming owner chain.

Evidence:

- For nonnull incoming owner with kind2 and parent.kind!=2, sets parent+8 to1 and returns2; otherwise returns1. Source: [eu/src/overlays/ov031/calls/MarkMixedKind2SceneGroupContactAndStop.c:1-10](../src/overlays/ov031/calls/MarkMixedKind2SceneGroupContactAndStop.c).
- The EU builder aliases the shared bb598 callback to this exact EU bb5b8 entrypoint. Source: [eu/src/overlays/ov031/calls/BuildSceneGroups.c:1-16](../src/overlays/ov031/calls/BuildSceneGroups.c).
- The constructed0x88-byte collision-object layout puts the second callback pair at+0x78, after shape/delta/bounds and two info words. Source: [src/ov031/overlay_state/BuildSceneGroups_020bb6f0.c:9-44](../../src/ov031/overlay_state/BuildSceneGroups_020bb6f0.c).
- The scene builder initializes each polygon CollisionObject and installs this function in the callback pair at+0x78. Its private onStay label is not the actual shared dispatch contract. Source: [src/ov031/overlay_state/BuildSceneGroups_020bb6f0.c:253-278](../../src/ov031/overlay_state/BuildSceneGroups_020bb6f0.c).
- The real CollObject prefix defines+0x78 as ObjectContactFn onContact, with an explicit mover-owner argument. Source: [src/arm9/spatial_queries/DispatchContactCallbacks_02031bf0.c:18-32](../../src/arm9/spatial_queries/DispatchContactCallbacks_02031bf0.c).
- Dispatcher invokes object callback(object,mover.owner,plane,userData,sweep,moving,planes,entries,index); results other than1 are returned before the mover callback. Source: [src/arm9/spatial_queries/DispatchContactCallbacks_02031bf0.c:54-77](../../src/arm9/spatial_queries/DispatchContactCallbacks_02031bf0.c).
- Contact-plane processing propagates callback results other than1 without recording further plane data. Source: [src/arm9/spatial_queries/RecordContactPlane_02031d24.c:94-105](../../src/arm9/spatial_queries/RecordContactPlane_02031d24.c).
- The hit-contact consumer treats result2 as TRUE to stop this traversal; result1 continues and advances the plane index. Source: [src/arm9/spatial_queries/RecordHitContact_020312fc.c:64-77](../../src/arm9/spatial_queries/RecordHitContact_020312fc.c).
- The plane-resolution path likewise ends its current operation when DispatchContactCallbacks returns2. Source: [src/arm9/spatial_queries/ResolvePlaneContacts_020322f0.c:210-220](../../src/arm9/spatial_queries/ResolvePlaneContacts_020322f0.c).

Contract limits:

- Kind2 remains numeric; no actor/gameplay type is invented for it.
- The word at parent+8 remains operationally described; no stronger active/blocked/hit-state meaning is inferred.
- Stop means the observed callback chain/current collision traversal. The helper does not itself zero movement or end every future collision query.
- Only the incoming-owner NULL check exists; there is no parent NULL check.
- A portable callback declaration must obey the full ObjectContactFn signature; the matched two-argument C view merely ignores extra native arguments.


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov031/calls/MarkMixedKind2SceneGroupContactAndStop.c MarkMixedKind2SceneGroupContactAndStop --thumb
bash tools/gate.sh
```
