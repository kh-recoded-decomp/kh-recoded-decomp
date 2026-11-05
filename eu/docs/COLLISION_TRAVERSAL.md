# Collision tree traversal

EU `func_01ffb4f8` at `0x01ffb4f8` traverses collision candidates, resolves
contact planes and dispatches the final contact callbacks. Its C implementation
is `src/calls/func_01ffb4f8.c`; the address-based public name is retained so the
existing callers and symbol map keep the same interface.

## Inputs and ownership

The three ARM arguments are the initial `CollNode *`, a mutable `CollMover *`
query and its `CollModel *`. The model supplies the root and face arrays used
when a revised movement requires another traversal. The mover supplies the
shape, displacement, candidate lists, group masks, contact list and callbacks.
These objects belong to the caller. This function performs no heap allocation.

The local plane, contact-entry, hit-face and hit-target buffers hold up to
`COLLISION_CONTACT_LIMIT` entries. The geometry-copy buffer and these arrays are
scratch for this call; helpers must not retain their addresses. The object
definitions describe recovered DS fields and offsets, not complete allocation
sizes or a host ABI. Bounds use maximum followed by minimum, as documented in
[COLLISION_GEOMETRY.md](COLLISION_GEOMETRY.md).

## Traversal and response

The function first handles explicit face lists, then visits the tree's enabled
face categories and linked targets. It keeps the number of processed contacts
separate from hit counts that can grow during a pass. `processedPrefixes` has
three named indices for floor, wall and ceiling; targets have their own prefix.
These values are counts, not face IDs. A retry restores the processed prefixes
before testing the revised movement.

`planeMode` controls the plane-response path:

| Value | Behavior |
|---|---|
| `0` | Record planes and resolve contacts; allow up to ten retries after the initial traversal. |
| `1` | Record planes without the resolve-and-retry path. |
| `2` | Pass a null plane buffer to the contact helpers. |

The caller's contact list and callbacks remain part of the query in each mode.
Target callbacks and the mover callback receive the recovered contexts and
contact normals synchronously. Accepted movement can update the caller's shape
geometry and displacement. For mode zero, the final displacement is also stored
in `data_027e0160` and may be limited by `maxDistance`; `0x7fffffff` disables that
final distance limit.

The traversal uses the shared frame cursor `gCollisionTraversalTop` and the frame storage
beginning at `gCollisionTraversalFrames`. A port must preserve this shared-state contract or
move it into a per-query traversal context before allowing concurrent or nested
queries. The contact-response helpers are documented separately in
[CONTACT_MOTION.md](CONTACT_MOTION.md).

## Recovered traversal workspace

`src/collision/CollisionTraversal.h` gives the EU frame and region types.
The complete workspace at DTCM `0x027e00b0..0x027e0134` is a four-byte cursor
followed by eight 16-byte frames. This size is supported independently by the
claimed BSS span and `ResetCollTraversal`, which initializes eight region sizes
by repeatedly halving the root size. The first frame also receives the root's
X/Z center. The reset does not initialize every child index or flag word.

| Symbol | Address | Recovered purpose |
|---|---|---|
| `gCollisionTraversalTop` | `0x027e00b0` | Pointer to the current frame; reset to the first frame, advanced on descent and restored during backtracking. |
| `gCollisionTraversalFrames` | `0x027e00b4` | Eight frames, 128 bytes in total, ending immediately before the next BSS object at `0x027e0134`. |

| Frame offset | Type | Meaning |
|---|---|---|
| `0x00` | `s16` | Child index used by backtracking. |
| `0x02` | `u16` | Saved parent-node flags used to select remaining siblings. |
| `0x04` | `s32` | Region center X. |
| `0x08` | `s32` | Region center Z. |
| `0x0c` | `s32` | Region size for that depth. |

The traversal assumes that the input tree fits the eight-frame workspace; it
does not add a bounds check on descent. The shared `FindQuadTreeContact` source
retains its older `QuadCell` view of this same storage: child/quadrant at zero,
two otherwise unused bytes, then the same region fields. Its EU wrapper maps
the cursor to the same symbol. A port should unify these declarations with its
chosen frame type rather than assume distinct C structure types are
interchangeable merely because their DS layouts agree.

The remaining scratch at `0x027e0160` is not renamed in this block: the existing
symbol at `0x027e0164` lies inside its vector-sized view, so naming it as a new
independent allocation would hide a storage overlap that still needs a lifetime
analysis. See [SYMBOL_EVIDENCE.md](SYMBOL_EVIDENCE.md) for the naming evidence.

## Matching and porting

CodeWarrior expands the three-element prefix-reset loop and separates the
resulting scalar live ranges. The two compiler pragmas selecting those passes
are guarded by `__MWERKS__`. They change code generation, while the reset itself
is ordinary C and initializes each prefix once. There are no added arguments,
assembly blocks, artificial volatile accesses, dummy fields or object patches.

The implementation retains the DS fixed-point arithmetic, callback ABI and
32-bit layout views. A host port should adapt those layouts and helper APIs
consistently, including the vector-return conventions, rather than copying the
DS pointer offsets into host objects.

From `eu/`, verify the function and then rebuild every linked module:

```sh
python tools/verify_idx.py src/calls/func_01ffb4f8.c func_01ffb4f8
bash tools/gate.sh
```

The function check reports 6,200 matching bytes and 41 matching references.
The integrated build also passes the full module gate: all 108 linked modules
are byte-exact. Repeat both checks after changing this function or its headers.
