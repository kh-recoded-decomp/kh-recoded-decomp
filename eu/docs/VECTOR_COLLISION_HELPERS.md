# Vector, collision and embedded-resource helper contracts

These names describe the actual bodies and their native callers. Four logical
interfaces are made explicit using the checked vector/query headers; other
shared-source adapters retain their matched implementation and documented limits.
No collision algorithm, fixed-point arithmetic or verified traversal is rewritten.

## Vector callback and quaternion interfaces

`RotateVectorByQuaternion(dst, quaternion, src)` builds a 3x3 matrix from the
quaternion, then calls `MTX_MultVec33(src, matrix, dst)`. The old argument called
unused is the live quaternion consumed by the builder, and the old source/output
names were reversed. The recovered quaternion word order is **W, X, Y, Z**, as
read by `QuaternionToRotationMatrix`; a host library's XYZW layout is not
interchangeable. The wrapper does not normalize the quaternion or replace the
existing fixed-point products/rounding.

`TransformVec3Components(values, transform)` calls a unary 32-bit-word callback
three times in XYZ order. It writes each callback result before loading the next
component. The old `ApplyScalarToVec3` name and sign parameter declarations were
false: there is no scalar multiply in this function. The callback may have side
effects; it is not restricted to negation, and calls must not be combined or
reordered.

`CopyVec3WithComponentTransform(out, source, transform)` first copies all three
source words to a local vector. It applies the same callback sequence to that
local vector and writes the output only after all three calls. Preserve that
copy boundary and alias behavior. `VectorTransforms.h` uses a real function
pointer for the callback rather than an integer carrying a code address.
Remaining shared callers still have legacy word declarations that a host port
must recover together.

## Segment query and contact helpers

`QueryModelSegmentCollision(scene, params)` sets **params.radius at +8 to zero**,
then returns `QueryModelCollision(scene, params)`. `MoverCastParams` records
start pointer, delta pointer, fx32 radius, flags/group-mask halfwords and owner ID;
compile-time checks retain the 20-byte native view and +8 radius offset. The
vector input is a delta, not an end point, and the cleared word is not result
flags. Existing private decompiler views using those labels are not API evidence.

The query returns the shared `CollisionResult` pointer on a hit or NULL. The
native caller in overlay017 consumes that pointer. It is borrowed workspace and
can be overwritten by later queries; it is neither a fresh allocation nor a
permanent result handle. The scene/result types remain opaque here rather than
inventing a full owner layout.

`PushContactWithDefaultMetadata` supplies the existing contact helper with the
normal pointer and zero value/field/surface metadata. The callee keeps its
16-entry bound and shifts entries when full; no allocation or new meaning for
the zero metadata is added.

`TestCapsuleAgainstCylinderWithRadiusSum` copies the second 44-byte cylinder
view, adds the first cylinder's radius at +0x28 to the local radius, and calls
the existing capsule/cylinder helper with flag 2 forced. It does not change the
original cylinders. The remaining local reference fields are not all initialized
by this path; a port must recover their actual reads before treating the view as
a complete public shape structure.

## Resource and registry lifetimes

`ReleaseModelAnimationResources` traverses five animation groups backwards and
frees each animation object. It frees one remembered nonnull list allocation
after traversal, then releases and clears the optional shared-resource handle.
Counts and list pointers are not cleared, so this is not generally idempotent.
The five groups are not proved to own five independent list allocations. Do not
replace the existing ownership pattern without the corresponding constructor.

The embedded-model release and quadtree-removal helpers below retain their exact
flag guards and native owner offsets. The guard is evidence for that operation,
not permission to free an entire owner or infer unrelated field semantics.

## Entrypoints, evidence and limits

Evidence source paths are relative to the repository root; current helper
source paths are relative to `eu/`. Historical US implementation paths remain
unchanged and are read through the current EU aliases.

### `RotateVectorByQuaternion`

Previously `func_0202fbbc`; 52 bytes, arm. Current source: `src/calls/RotateVectorByQuaternion.c`.

- Builds9word local matrix, calls QuaternionToRotationMatrix then MTX_MultVec33. Evidence: `src/arm9/core_small/func_0202fba8.c`:1.
- Real quaternion builder takes matrix plus quaternion; R1 is consumed as quaternion, not unused. Evidence: `src/arm9/runtime_data_utilities/QuaternionToRotationMatrix_0202f808.c`:1.
- MTX_MultVec33 actual order is src,matrix,dst. Evidence: `src/itcm/library_nitro_mtx/func_01ff9404.c`:20.
- ROM decompile shows unused/r1 carried to quaternion converter; current names in_vec/out_vec are reversed. Confirm against the overlay-qualified ROM call and the current EU aliases.

Real signature is dst,quaternion,src; do not preserve falsely named unused parameter. No quaternion normalization or floating-point substitution is added. Matrix and vector fixed-point rounding stay delegated to real helpers.

### `TransformVec3Components`

Previously `ApplyScalarToVec3`; 52 bytes, arm. Current source: `src/calls/TransformVec3Components.c`.

- Receives function pointer and invokes it once for each of3input words, writing each result. Evidence: `src/arm9/reviewed_helpers/func_0204abf4.c`:1.

Existing name is wrong: this is NOT scalar multiply or sign-only negation. Operation is a unary32-bit word callback, applied in XYZ order. Preserve order/side effects.

### `CopyVec3WithComponentTransform`

Previously `func_0204966c`; 56 bytes, arm. Current source: `src/calls/CopyVec3WithComponentTransform.c`.

- Copies vector to local, passes third input to component transform helper and copies result to output. Evidence: `src/arm9/math/func_02049658.c`:1.
- Third wrapper word is callback address, not integer sign. Evidence: `src/arm9/reviewed_helpers/func_0204abf4.c`:1.
- Used to transform polynomial vectors in SweepCircleAgainstCircle. Confirm against the overlay-qualified ROM call and the current EU aliases.

All three source words are snapshotted before callbacks; the wrapper itself writes only its temporary until the final output copy. A callback may still reach the original source through another alias. Do not replace this with in-place mapping if alias/side effects matter. Existing s32 sign parameter/prototype is false; typed callback is necessary for host portability.

### `PushContactWithDefaultMetadata`

Previously `func_02032000`; 28 bytes, arm. Current source: `src/calls/PushContactWithDefaultMetadata.c`.

- Forwards list,zeros for value/field/surfaceType and normal pointer to PushContact. Evidence: `src/arm9/unclassified_helpers/func_02031fec.c`:1.
- Actual helper stores contact metadata and copies normal into fixed16-entry list; shifts when full. Evidence: `src/arm9/spatial_queries/PushContact_02032008.c`:1.

No new allocation or meaning assigned to zero metadata. Existing list eviction behavior remains. Real second pointer is a normal vector, not a generic callback or ownership handle.

### `QueryModelSegmentCollision`

Previously `func_020351cc`; 20 bytes, arm. Current source: `src/calls/QueryModelSegmentCollision.c`.

- Writes query+8=0 then invokes QueryModelCollision. Evidence: `src/arm9/unclassified_helpers/func_020351b8.c`:1.
- MoverCastParams+8 is radius; radius0 selects segment-cylinder representation from start+delta. Evidence: `src/arm9/spatial_queries/InitMoverCast_02032b0c.c`:49.
- Tree query returns shared CollisionResult pointer or null. Evidence: `src/itcm/spatial_queries/QueryModelCollision_01ffce24.c`:1.
- Native caller consumes pointer result. Evidence: `eu/src/overlays/ov017/calls/UpdateGridObjectDropOffsetFromRay.c`:28.

The cleared field is radius, NOT resultFlags. Existing QueryCollisionSegment private names end/resultFlags are misleading; source actually means delta/radius. Input query is mutated. Return is borrowed shared collision result, overwritten by later queries. Legacy void return loses the actual observed pointer result; recover it with exact check.

### `TestCapsuleAgainstCylinderWithRadiusSum`

Previously `func_02041078`; 60 bytes, thumb. Current source: `src/calls/TestCapsuleAgainstCylinderWithRadiusSum.c`.

- Copies44-byte second shape, adds first shape word+0x28 to its last word, passes pointer in local reference and flags|2. Evidence: `src/arm9/unclassified_helpers/func_02041064.c`:1.
- CollisionCylinder has start/end/direction/length/radius; radius at+0x28. Flag2 forces segment-against-cylinder branch. Evidence: `src/arm9/spatial_queries/TestCapsuleAgainstCylinder_02040548.c`:8.

Two opaque private type names Manager/Payload44 are actual cylinder data/reference views, not arbitrary manager parameters. Does not mutate either original cylinder; only local radius sum is changed. Preserve arithmetic and forcedflag2. No claim of a new exact geometric algorithm beyond existing delegation. Remaining local reference fields are not initialized by existing path.

### `ReleaseModelAnimationResources`

Previously `func_0202eb08`; 144 bytes, arm. Current source: `src/calls/ReleaseModelAnimationResources.c`.

- Walks5animation groups backwards, frees each animation object, frees last nonnull list allocation, releases optional shared resource and clears its handle. Evidence: `src/arm9/resource_management/func_0202eaf4.c`:1.
- Called on model+0xd8 before releasing model archive resource and detaching node. Evidence: `src/arm9/runtime/ReleaseResourceAndDetach_0202eee8.c`:1.

Counts/list pointers are not cleared; do not promise idempotence. Only optional shared-resource handle is cleared. Only one list-base allocation is freed after traversal; do not reinterpret as independently owned5arrays without constructor proof.

### `ReleaseEmbeddedModelOnce`

Previously `func_020353b8`; 44 bytes, arm. Current source: `src/calls/ReleaseEmbeddedModelOnce.c`.

- If prefixflag0x20 clear, calls ReleaseResourceAndDetach atprefix+4; always sets0x20 afterward. Evidence: `src/arm9/core_small/func_020353a4.c`:1.
- Actual operation releases model animation/resource tables and detaches object tree node. Evidence: `src/arm9/runtime/ReleaseResourceAndDetach_0202eee8.c`:1.

Once-only property is controlled by bit0x20 at enclosing prefix, not by clearing every model resource pointer. No free of outer container itself.

### `ReleaseFlaggedEmbeddedModel`

Previously `func_020359c4`; 36 bytes, thumb. Current source: `src/calls/ReleaseFlaggedEmbeddedModel.c`.

- If outerflags+8 bit4 set, invokes release-once on embedded prefix+0x10 then clears outerbit4. Evidence: `src/arm9/shared_engine/func_020359b0.c`:3.

Two different flag words/scopes; outerbit4 is cleared even if innerrelease is already guarded. Do not merge masks.

### `RemoveEmbeddedObjectFromQuadTreeIfFlagged`

Previously `func_020369a8`; 52 bytes, arm. Current source: `src/calls/RemoveEmbeddedObjectFromQuadTreeIfFlagged.c`.

- Outerflags+8 bit0x100 gates Obj_RemoveFromQuadTree on embedded object+0x10; then clears outerbit. Evidence: `src/arm9/shared_engine/func_02036994.c`:3.
- Inner object independently checks flags8/0x10 and owns its tree/node fields. Evidence: `src/arm9/shared_engine/Obj_RemoveFromQuadTree_020355f4.c`:3.

Outer flag can clear even when inner operation returns without removal. No object destruction/allocation.

### `GetCollisionTestSegmentHitPoint`

Previously `func_0203f5c0`; 40 bytes, arm. Current source: `src/calls/GetCollisionTestSegmentHitPoint.c`.

- Computes hit point into temporary12-byte vector then copies to supplied destination. Evidence: `src/arm9/shared_engine/func_0203f5ac.c`:1.
- Inputs are hit record and segment; time is Q27, including vertical special case. Evidence: `src/arm9/spatial_queries/GetSegmentPointAtHitTime_0203b4ac.c`:3.

Backend actual signature takes output plus two inputs; fourth old wrapper slot is unused. Temporary protects output from intermediate writes; retain behavior and rounding.

### `GetCollisionTestUnitCross`

Previously `func_02040010`; 40 bytes, arm. Current source: `src/calls/GetCollisionTestUnitCross.c`.

- Calls shared unit-cross backend into temporary and copies12bytes to destination. Evidence: `src/arm9/shared_engine/func_0203fffc.c`:1.
- Fixed-point cross length threshold0x10; returns normalized perpendicular fallback for short/degenerate cross. Evidence: `src/arm9/math/GetUnitCross_0204aa68.c`:1.
- Used by static box/capsule, segment and cylinder tests. Confirm against the overlay-qualified ROM call and the current EU aliases.

Test-vs-sweep qualifier describes observed caller domain, not different math; duplicate entry points remain separately matched. Backend returns VecFx32 by value; current untyped out-pointer declaration is an ABI view, not original C prototype. Preserve struct-return convention and report BOOL pointer in degeneracy variant.

### `GetSweepUnitCross`

Previously `func_0204800c`; 40 bytes, arm. Current source: `src/calls/GetSweepUnitCross.c`.

- Calls shared unit-cross backend into temporary and copies12bytes to destination. Evidence: `src/arm9/shared_engine/func_02047ff8.c`:1.
- Fixed-point cross length threshold0x10; returns normalized perpendicular fallback for short/degenerate cross. Evidence: `src/arm9/math/GetUnitCross_0204aa68.c`:1.
- Used by SweepObbAgainstSegment and SweepCircleAgainstCircle. Confirm against the overlay-qualified ROM call and the current EU aliases.

Test-vs-sweep qualifier describes observed caller domain, not different math; duplicate entry points remain separately matched. Backend returns VecFx32 by value; current untyped out-pointer declaration is an ABI view, not original C prototype. Preserve struct-return convention and report BOOL pointer in degeneracy variant.

### `GetCollisionTestUnitCrossWithDegeneracy`

Previously `func_020404b4`; 40 bytes, arm. Current source: `src/calls/GetCollisionTestUnitCrossWithDegeneracy.c`.

- Calls shared unit-cross backend into temporary and copies12bytes to destination. Evidence: `src/arm9/shared_engine/func_020404a0.c`:1.
- Fixed-point cross length threshold0x10; returns normalized perpendicular fallback for short/degenerate cross. Evidence: `src/arm9/math/GetUnitCrossReportDegenerate_0204ab10.c`:1.
- Called by TestSegmentAgainstSegment. Confirm against the overlay-qualified ROM call and the current EU aliases.

Test-vs-sweep qualifier describes observed caller domain, not different math; duplicate entry points remain separately matched. Backend returns VecFx32 by value; current untyped out-pointer declaration is an ABI view, not original C prototype. Preserve struct-return convention and report BOOL pointer in degeneracy variant.

### `GetSweepUnitCrossWithDegeneracy`

Previously `func_020483f8`; 40 bytes, arm. Current source: `src/calls/GetSweepUnitCrossWithDegeneracy.c`.

- Calls shared unit-cross backend into temporary and copies12bytes to destination. Evidence: `src/arm9/shared_engine/func_020483e4.c`:1.
- Fixed-point cross length threshold0x10; returns normalized perpendicular fallback for short/degenerate cross. Evidence: `src/arm9/math/GetUnitCrossReportDegenerate_0204ab10.c`:1.
- Called by SweepSegmentAgainstSegment. Confirm against the overlay-qualified ROM call and the current EU aliases.

Test-vs-sweep qualifier describes observed caller domain, not different math; duplicate entry points remain separately matched. Backend returns VecFx32 by value; current untyped out-pointer declaration is an ABI view, not original C prototype. Preserve struct-return convention and report BOOL pointer in degeneracy variant.

### `SetCollisionTestVectorComponents`

Previously `func_02041048`; 40 bytes, arm. Current source: `src/calls/SetCollisionTestVectorComponents.c`.

- Calls SetVec3/SetVec3Values on local vector then copies it to destination. Evidence: `src/arm9/shared_engine/func_02041034.c`:1.
- Actual backend stores x/y/z scalars. Evidence: `src/arm9/fixed_point_math/SetVec3_0204105c.c`:1.
- Called by TestSegmentAgainstCylinder. Confirm against the overlay-qualified ROM call and the current EU aliases.

Real inputs are destination,x,y,z. Test/sweep qualifier retains separate entry point instead of unifying duplicate functions.

### `SetSweepVectorComponents`

Previously `func_0204963c`; 40 bytes, arm. Current source: `src/calls/SetSweepVectorComponents.c`.

- Calls SetVec3/SetVec3Values on local vector then copies it to destination. Evidence: `src/arm9/shared_engine/func_02049628.c`:1.
- Actual backend stores x/y/z scalars. Evidence: `src/arm9/fixed_point_math/SetVec3_0204105c.c`:1.
- Called by SweepCircleAgainstCircle. Confirm against the overlay-qualified ROM call and the current EU aliases.

Real inputs are destination,x,y,z. Test/sweep qualifier retains separate entry point instead of unifying duplicate functions.

## Reproduction

Run from `eu/`:

```sh
python tools/verify_idx.py src/calls/RotateVectorByQuaternion.c RotateVectorByQuaternion
python tools/verify_idx.py src/calls/TransformVec3Components.c TransformVec3Components
python tools/verify_idx.py src/calls/CopyVec3WithComponentTransform.c CopyVec3WithComponentTransform
python tools/verify_idx.py src/calls/PushContactWithDefaultMetadata.c PushContactWithDefaultMetadata
python tools/verify_idx.py src/calls/QueryModelSegmentCollision.c QueryModelSegmentCollision
python tools/verify_idx.py src/calls/TestCapsuleAgainstCylinderWithRadiusSum.c TestCapsuleAgainstCylinderWithRadiusSum --thumb
python tools/verify_idx.py src/calls/ReleaseModelAnimationResources.c ReleaseModelAnimationResources
python tools/verify_idx.py src/calls/ReleaseEmbeddedModelOnce.c ReleaseEmbeddedModelOnce
python tools/verify_idx.py src/calls/ReleaseFlaggedEmbeddedModel.c ReleaseFlaggedEmbeddedModel --thumb
python tools/verify_idx.py src/calls/RemoveEmbeddedObjectFromQuadTreeIfFlagged.c RemoveEmbeddedObjectFromQuadTreeIfFlagged
python tools/verify_idx.py src/calls/GetCollisionTestSegmentHitPoint.c GetCollisionTestSegmentHitPoint
python tools/verify_idx.py src/calls/GetCollisionTestUnitCross.c GetCollisionTestUnitCross
python tools/verify_idx.py src/calls/GetSweepUnitCross.c GetSweepUnitCross
python tools/verify_idx.py src/calls/GetCollisionTestUnitCrossWithDegeneracy.c GetCollisionTestUnitCrossWithDegeneracy
python tools/verify_idx.py src/calls/GetSweepUnitCrossWithDegeneracy.c GetSweepUnitCrossWithDegeneracy
python tools/verify_idx.py src/calls/SetCollisionTestVectorComponents.c SetCollisionTestVectorComponents
python tools/verify_idx.py src/calls/SetSweepVectorComponents.c SetSweepVectorComponents
bash tools/gate.sh
```

Integration retains the baseline and compares affected production texts,
resolved relocation targets/types and addends, then checks all 108 linked module
hashes. This is naming and interface recovery; it adds no C or DATA credit.
