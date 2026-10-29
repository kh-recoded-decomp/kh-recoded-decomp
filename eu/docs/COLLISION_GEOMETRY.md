# EU collision geometry

The common definitions are in `src/collision/CollisionGeometry.h`. They describe
the recovered 32-bit DS layout, not a portable host ABI. Coordinates are `fx32`
(4096 represents one unit). The size checks deliberately reject a different
pointer width; a future port will need to separate host objects from ROM layouts.

## Bounds order and movement

`SphereToBounds` at EU `0x020499d8` writes the center into both endpoints, adds
the radius to the first vector and subtracts it from the second. The order is
therefore **maximum, minimum**. `GetShapeBounds` independently uses that same
order. The old shared `OffsetBoxByDelta` source named those endpoints the other
way round; the EU implementation now uses the common type and correct names.
Its instruction bytes are unchanged.

| Type | Size | Fields |
|---|---:|---|
| `CollisionBounds` | `0x18` | maximum vector at `0x00`, minimum at `0x0c` |
| `CollisionSphere` | `0x10` | center at `0x00`, radius at `0x0c` |
| `CollisionShape` | `0x20` | geometry pointer at `0x00`, bounds at `0x04`, kind at `0x1c` |
| `SweptCollisionShape` | `0x44` | shape at `0x00`, displacement at `0x20`, swept bounds at `0x2c` |

`MakeSphereShape` at EU `0x0203ad28` retains the caller's sphere pointer, copies
the initial center into that sphere, writes its radius, selects kind zero and
calls the first entry of `gCollisionBoundsDispatch` to compute bounds. The caller
owns both objects and must keep the sphere alive while the shape is used.

`OffsetBoxByDelta` at EU `0x0203ac84` produces the union of the original bounds
and those bounds translated by the displacement. For each axis:

```text
out.max = source.max + max(delta, 0)
out.min = source.min + min(delta, 0)
```

The output can alias the input bounds. The displacement remains unchanged.
This is a bounds operation, not collision detection or a position update.

## Matched touched-object sweep

`SweepTouchSphere` is now matched through
`src/overlays/ov007/calls/SweepTouchSphere.c`, which maps the shared
`src/ov007/shared_engine/SweepTouchSphere_020a098c.c` implementation to EU
symbols. Commit `8725d677` supplied this match; the older local nonmatching
candidate has been removed. The operation name does not claim a particular
enemy, reward or gameplay event.

The four ARM arguments are an owner pointer, an initial position, a displacement
and an output position. The owner supplies the query actor address through its
pointer at `0x0c`, plus `0x10` into that object's body. Only that prefix is typed.
The function constructs a sphere with radius `0x200` (one eighth of a unit),
prepares a swept shape, initializes a query with the original `15, 9, 1, 1, 0`
parameters and installs `CanTouchedObjectAct` with a null context as its filter.
The meanings of the query's remaining fields are intentionally left unknown.

On a hit, it copies the sphere's updated center to the output and returns true.
On a miss, it writes initial position plus displacement and returns false.
`StepBounceBody` and `StepHomingBounceBody` consume this distinction. The sphere,
shape and query live on the stack; the query must not escape the call.

The accepted source selects `dsi/1.3p1` and matches all 304 bytes and six
relocations. It snapshots the three initial coordinates and expresses sphere
construction as returning a `CollisionShape`. The original ARM calling sequence
passes a hidden result address in r0, followed by the sphere, center and radius
in r1-r3. The low-level `MakeSphereShape` definition uses that explicit output
pointer. These source-level declarations describe the same ROM register
interface; a host port must choose one consistent API and adapt its callers,
rather than assuming the two C declarations are interchangeable.

## Reproduce the checks

Run from `eu/`, after setting up the local toolchain and ROM-derived index:

```sh
python tools/verify_idx.py src/calls/MakeSphereShape.c MakeSphereShape
python tools/verify_idx.py src/calls/SphereToBounds.c SphereToBounds
python tools/verify_idx.py src/calls/OffsetBoxByDelta.c OffsetBoxByDelta
python tools/test_collision_geometry.py -v
python tools/verify_idx.py src/overlays/ov007/calls/SweepTouchSphere.c SweepTouchSphere
```

The four function checks must match (64, 60, 164 and 304 bytes).
The semantic tests execute the ROM-derived ARM instructions in `arm_exec.py`,
including the sphere's real bounds-dispatch call. They check 408 sphere cases
and 454 displacement cases, including every combination of positive, negative
and zero axes, in-place output, unchanged inputs and output boundaries.
Coordinates stay within signed 32-bit range; overflow behavior is not tested.
These tests do not issue library receipts or change progress categories.

The subsequent contact response is documented in [CONTACT_MOTION.md](CONTACT_MOTION.md),
including its independently checked pending C implementation and current byte differences.
