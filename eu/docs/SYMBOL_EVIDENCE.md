# EU semantic names and recovered layouts

Names are accepted from behavior, callers and data layout, not from a desired
coverage percentage. A source may retain an address-based name when its role is
uncertain. Naming does not add code or DATA reconstruction credit.

## Collision block

| Previous name | Current name | Evidence |
|---|---|---|
| `func_02047198` | `SweepSphereAgainstRim` | The matched C translates a sphere center into a rim basis, forms quartic coefficients, selects a distance and returns a contact normal. `SweepSphereAgainstCappedCylinder` calls it for each cylinder endpoint; `SweepCylinderAgainstCylinder` also uses the endpoint-rim operation. |
| `func_02034d78` | `ProjectMotionAgainstContactNormals` | Its two real inputs are a mutable motion vector and the recovered contacts workspace. `projectionMode` selects unchanged motion, plane/crease projection or a zero result. It is used from contact push-out and the field/world sweep callers. The existing ARM/C/model tests cover its mode and threshold behavior. |
| `func_01ffb4f8` | `ResolveCollisionTreeContacts` | Its three inputs supply the initial node, mover query and collision model. It visits explicit faces and quadtree candidates, records planes, performs the enabled resolve/retry path and dispatches contact callbacks. `TestMoverAgainstModel` is its established caller; [COLLISION_TRAVERSAL.md](COLLISION_TRAVERSAL.md) records modes, ownership and outputs. |
| `data_027e00b0` | `gCollisionTraversalTop` | `ResetCollTraversal` writes the frame base; traversal reads the current frame, stores its successor on descent and stores a parent frame while backtracking. `FindQuadTreeContact` uses the same cursor through its EU wrapper. |
| `data_027e00b4` | `gCollisionTraversalFrames` | Existing BSS owns exactly 128 bytes at this address. Reset initializes eight 16-byte frames; traversal accesses child index, flags and the X/Z region at the documented offsets. |

The storage definition now uses a frame pointer and an eight-element typed
array instead of a raw `u32` and a 32-word array. The source header checks the
12-byte region, 16-byte frame and four-byte DS pointer. No object size,
parameter, data address or field offset is invented to influence compilation.
The complete frame layout and shared-state/legacy-view constraints are in
[COLLISION_TRAVERSAL.md](COLLISION_TRAVERSAL.md).

Function addresses and public calling conventions remain the same. The changed
references are EU symbol/alias mappings; the shared US implementations are not
rewritten. Historical numeric names can remain in archive files and the
ROM-derived index; current configuration and source declarations use the new
names. The index is reconstructed with `tools/rebuild_index.py`, which checks
relocations against the ROM and preserves disagreeing historical entries.

The shared-source wrappers for `CollWorld_FindHitPreserveState`,
`GatherQuadtreeFaces`, `TestMoverAgainstModelTree` and
`TestMoverAgainstModelWalls` also map the two old DTCM identifiers to the new
symbols. These mappings are necessary because the included US source still
uses its original identifiers; the renaming tool's EU-only text scan cannot
see those references inside another region's source.

## Verification commands

From `eu/`:

```sh
python tools/verify_idx.py src/calls/SweepSphereAgainstRim.c SweepSphereAgainstRim
python tools/verify_idx.py src/calls/ProjectMotionAgainstContactNormals.c ProjectMotionAgainstContactNormals
python tools/verify_idx.py src/calls/ResolveCollisionTreeContacts.c ResolveCollisionTreeContacts
python tools/verify_idx.py src/calls/ResetCollTraversal.c ResetCollTraversal
python tools/verify_idx.py src/calls/FindQuadTreeContact.c FindQuadTreeContact --thumb
python tools/verify_idx.py src/calls/CollWorld_FindHitPreserveState.c CollWorld_FindHitPreserveState
python tools/verify_idx.py src/calls/GatherQuadtreeFaces.c GatherQuadtreeFaces
python tools/verify_idx.py src/calls/TestMoverAgainstModelTree.c TestMoverAgainstModelTree --thumb
python tools/verify_idx.py src/calls/TestMoverAgainstModelWalls.c TestMoverAgainstModelWalls --thumb
python tools/test_contact_motion.py -v
bash tools/gate.sh
python tools/progress.py
```

The expected function sizes are 1480, 528, 6200, 84 and 408 bytes respectively.
The four additional wrapper sizes are 276, 1828, 892 and 872 bytes. Each check
must pass the official byte/relocation verifier. The final linked gate
also checks the DATA layout and all affected callers across 108 modules.

## Documented UI operations

| Previous name | Current name | Evidence |
|---|---|---|
| `func_ov027_020b91e8` | `SetWidgetPosition` | Six named modes update the widget's offset and send the resulting position to its indexed records. [WIDGET_POSITION.md](WIDGET_POSITION.md) documents modes, wrapping arithmetic, Y-axis asymmetry and aliasing; the existing ROM/compiled-C/model tests cover the behavior. |
| `func_ov034_020ba400` | `InitResultsScene` | Clears the task-owned results work record, copies scene arguments, obtains session parameters, initializes dependent resources, rewards and shop state, and returns `UpdateResultsScreen`. [RESULTS_SCENE.md](RESULTS_SCENE.md) records the work/parameter layouts, paired BSS views and task ownership. |

The setter's EU references are renamed together, including the declarations and
aliases used by other overlays. `InitResultsScreen` remains a different function;
its name and role are not merged with `InitResultsScene`. The ITCM name change
also needs a preprocessor mapping in the EU `TestMoverAgainstModel` wrapper,
whose included US implementation retains `func_01ffb4f8`.

From `eu/`, also run:

```sh
python tools/verify_idx.py src/overlays/ov027/calls/SetWidgetPosition.c SetWidgetPosition
python tools/verify_idx.py src/overlays/ov034/calls/InitResultsScene.c InitResultsScene
python tools/verify_idx.py src/calls/TestMoverAgainstModel.c TestMoverAgainstModel --thumb
python tools/test_widget_position.py -v
```

Those function sizes remain 408, 1972 and 344 bytes. Re-run the full gate after
the symbol changes so every caller and callback table is resolved at its
original address. This work does not change function signatures or arithmetic.

## Explicitly unresolved

The vector view at `data_027e0160` overlaps `data_027e0164`, used by the older
object-hit view. This block does not assign two independent typed objects to
that storage or infer a full allocation from one call's accesses. It needs a
separate check of lifetimes, ownership and callers before a shared union or
more specific names can be justified.
