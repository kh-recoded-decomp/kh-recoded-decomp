# Native references across overlay banks

An EU address alone does not identify storage. Different overlays reuse RAM,
and a child overlay can reference a resident parent's object. Follow the
loader and the actual consumer before choosing a C identity or host owner.

## Camera child and resident manager

Overlay047 has 21 native pointer words containing `0x020c3500`. Their owner is
resident overlay046's `gCameraManager`. StartSubMode mode0 loads 046; its manager
initializer stores the allocated 0x414-byte work and loads 047 before resetting
tracking. The parent is present while these child helpers use that pointer.

The former `data_ov036_020c3500` spelling belongs to physical text-window DATA
in a different bank. It cannot identify the camera manager. The partial view
in `src/overlays/ov047/Ov047CameraState.h` and the shared-body alias in
`src/overlays/ov047/calls/Camera_SweepLookAt.c` now reference the resident owner.
All 21 corresponding load relocations explicitly select `overlay(46)`.
The partial camera view does not establish a complete portable manager type.

## Report registry and record-table tail

At ov039:020be9a4 the registry's eight-byte pair is `{91, 0x020c2b18}`.
LoadPrimarySubOverlay reads the ID and loads that bank before using its
paired descriptor pointer. This entry therefore references ov091's existing
`gReportTopMenuDescriptor`, not physical ov086 DATA at the same RAM address.

The registry source `src/ov039/data/Data_ov039_020be950.c` now uses that actual
descriptor. Its load relocation at 020be9a8 explicitly selects `overlay(91)`.
The ov086 label continues to identify its own record-table fragment; this
correction does not create a second descriptor or change physical storage.

## Validation

The original 21 camera words and report ID/pointer pair were checked against
the native modules, using RAM bases from the original NDS overlay table.
Only 21 approved camera relocation names change in the function index; all
instruction bytes, sizes, modes and relocation offsets remain unchanged.

All 21 affected official function checks pass at their real source paths.
All 22 complete production objects preserve allocated bytes/alignment, symbol
layouts and relocation target/type/addend records after the two explicit
reference bindings are canonicalized. A fresh gate passes all 108 linked
modules with every hash unchanged. These are reference corrections; the
physical ov036 and ov086 owners retain their separate identities.

Run from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov047/calls/Camera_GetTrackingController.c Camera_GetTrackingController --thumb
python tools/verify_idx.py src/overlays/ov047/calls/Camera_SweepLookAt.c Camera_SweepLookAt --thumb
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
