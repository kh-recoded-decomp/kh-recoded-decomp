# Results screen task and drawing helpers

This document records 5 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

The results interface's create slot instantiates a TaskObject using its results descriptor. The optional callback in slot 7 returns literal zero, while the cleanup no-op is invoked before the enclosing session resources are freed by its caller. Neither empty hook releases an allocation itself, and unused arguments supplied by other callers do not establish list-initializer semantics.

The default object-slot adapter preserves manager, resource/animation inputs and X/Y, while supplying mode 0, priority 0, palette -1 and enabled 0. Its result is the indexed-record ID. Enabled zero is retained; this is not a visible-by-default sprite constructor.

The textured-quad helper uses the high 16 bits of select as the image metadata index and the low 16 bits as color. Packed position stores signed X in the high half and signed Y in the low half; screen Y is inverted with 192. Depth is a caller-supplied fixed-point value. It submits texture/palette words and four vertices after changing G3d transforms/material state, without restoring the previous state. A port should keep that caller-visible state effect separate from image/resource ownership.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov034:020bde10` | THUMB | `func_ov034_020bde10` | `CreateResultsScreenTask` | [eu/src/overlays/ov034/calls/CreateResultsScreenTask.c](../src/overlays/ov034/calls/CreateResultsScreenTask.c) |
| `ov034:020bdea4` | THUMB | `func_ov034_020bdea4` | `ResultsScreenNoOpCallback` | [eu/src/overlays/ov034/auto/ResultsScreenNoOpCallback.c](../src/overlays/ov034/auto/ResultsScreenNoOpCallback.c) |
| `ov034:020bdea8` | THUMB | `func_ov034_020bdea8` | `CreateResultsObjectSlotDefault` | [eu/src/overlays/ov034/calls/CreateResultsObjectSlotDefault.c](../src/overlays/ov034/calls/CreateResultsObjectSlotDefault.c) |
| `ov034:020be734` | THUMB | `func_ov034_020be734` | `ResultsSessionCleanupNoOp` | [eu/src/overlays/ov034/auto/ResultsSessionCleanupNoOp.c](../src/overlays/ov034/auto/ResultsSessionCleanupNoOp.c) |
| `ov034:020be738` | THUMB | `func_ov034_020be738` | `DrawResultsTexturedQuad` | [eu/src/overlays/ov034/calls/DrawResultsTexturedQuad.c](../src/overlays/ov034/calls/DrawResultsTexturedQuad.c) |

## CreateResultsScreenTask

Identity: `ov034:020bde10`, THUMB, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov034_020bde10`.

EU entrypoint: [eu/src/overlays/ov034/calls/CreateResultsScreenTask.c](../src/overlays/ov034/calls/CreateResultsScreenTask.c).

```c
void CreateResultsScreenTask(int arg);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Creates and stores the task using the results descriptor and caller argument. Source: [src/ov034/shared_engine/MobiClip_SrcOpen_020bddf0.c:1-7](../../src/ov034/shared_engine/MobiClip_SrcOpen_020bddf0.c).
- Installs this exact function as interface create slot0. Source: [eu/src/overlays/ov034/calls/InitResultsMovieSourceOps.c:1-9](../src/overlays/ov034/calls/InitResultsMovieSourceOps.c).

Contract limits:

- This is a task creation adapter; the MobiClip source label is not the operation performed.

## ResultsScreenNoOpCallback

Identity: `ov034:020bdea4`, THUMB, native extent 4 bytes (including any configured pool). Previous symbol: `func_ov034_020bdea4`.

EU entrypoint: [eu/src/overlays/ov034/auto/ResultsScreenNoOpCallback.c](../src/overlays/ov034/auto/ResultsScreenNoOpCallback.c).

```c
int ResultsScreenNoOpCallback(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns zero with no side effects. Source: [src/ov034/library_nitro_fs/FSi_CloseFileCommand_020bde84.c:1-1](../../src/ov034/library_nitro_fs/FSi_CloseFileCommand_020bde84.c).
- Installed as optional callback slot7 of the results interface. Source: [eu/src/overlays/ov034/calls/InitResultsMovieSourceOps.c:1-9](../src/overlays/ov034/calls/InitResultsMovieSourceOps.c).

Contract limits:

- Other overlays also call the same no-op with unused arguments; do not infer a list initializer interface from those call signatures.

## CreateResultsObjectSlotDefault

Identity: `ov034:020bdea8`, THUMB, native extent 28 bytes (including any configured pool). Previous symbol: `func_ov034_020bdea8`.

EU entrypoint: [eu/src/overlays/ov034/calls/CreateResultsObjectSlotDefault.c](../src/overlays/ov034/calls/CreateResultsObjectSlotDefault.c).

```c
int CreateResultsObjectSlotDefault(void *manager, int animation, int resource, int x, int y);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Calls CreateObjectSlot with mode0, priority0, palette-1 and enabled0 while preserving supplied manager/resource/animation and X/Y. Source: [eu/src/overlays/ov034/calls/CreateResultsObjectSlotDefault.c:1-8](../src/overlays/ov034/calls/CreateResultsObjectSlotDefault.c).
- The full callee allocates an indexed record, sets its fixed-point position/mode/priority and optionally animation frame. Source: [src/ov034/unclassified_helpers/CreateObjectSlot_020bdea4.c:1-31](../../src/ov034/unclassified_helpers/CreateObjectSlot_020bdea4.c).

Contract limits:

- This helper returns the indexed record ID.
- The defaults include enabled0; do not label this a visible-by-default sprite constructor.

## ResultsSessionCleanupNoOp

Identity: `ov034:020be734`, THUMB, native extent 2 bytes (including any configured pool). Previous symbol: `func_ov034_020be734`.

EU entrypoint: [eu/src/overlays/ov034/auto/ResultsSessionCleanupNoOp.c](../src/overlays/ov034/auto/ResultsSessionCleanupNoOp.c).

```c
void ResultsSessionCleanupNoOp(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Empty function, reached during results-session close. Source: [src/ov034/library_msl_c/_fp_init_020be714.c:1-1](../../src/ov034/library_msl_c/_fp_init_020be714.c).
- Close path passes its menuState before freeing the surrounding session resources. Source: [eu/src/overlays/ov034/calls/CloseResultsSession.c:1-83](../src/overlays/ov034/calls/CloseResultsSession.c).

Contract limits:

- Does not clean up an allocation itself.
- The shared _fp_init label does not describe its game callback role.

## DrawResultsTexturedQuad

Identity: `ov034:020be738`, THUMB, native extent 388 bytes (including any configured pool). Previous symbol: `func_ov034_020be738`.

EU entrypoint: [eu/src/overlays/ov034/calls/DrawResultsTexturedQuad.c](../src/overlays/ov034/calls/DrawResultsTexturedQuad.c).

```c
void DrawResultsTexturedQuad(const MenuImage *images, u32 select, u32 pos, fx32 depth);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Chooses image metadata using select high16, sets width/height scale and screen-centered translation, binds texture/palette words, sets color from select low16 and emits four textured vertices. Source: [eu/src/overlays/ov034/calls/DrawResultsTexturedQuad.c:1-75](../src/overlays/ov034/calls/DrawResultsTexturedQuad.c).
- Geometry command definitions identify COLOR0x20,TEXCOORD0x22,VTX_160x23,BEGIN0x40,END0x41. Source: [include/nitro/gx.h:1-629](../../include/nitro/gx.h).

Contract limits:

- Packed pos stores signed X in high16 and signed Y in low16; screen-space Y is inverted using192.
- Depth remains a fixed-point caller value.
- Mutates NNS G3d global state and does not restore prior transforms/material words.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov034/calls/CreateResultsScreenTask.c CreateResultsScreenTask --thumb
python tools/verify_idx.py src/overlays/ov034/auto/ResultsScreenNoOpCallback.c ResultsScreenNoOpCallback --thumb
python tools/verify_idx.py src/overlays/ov034/calls/CreateResultsObjectSlotDefault.c CreateResultsObjectSlotDefault --thumb
python tools/verify_idx.py src/overlays/ov034/auto/ResultsSessionCleanupNoOp.c ResultsSessionCleanupNoOp --thumb
python tools/verify_idx.py src/overlays/ov034/calls/DrawResultsTexturedQuad.c DrawResultsTexturedQuad --thumb
bash tools/gate.sh
```

All entrypoints in this document pass the official function check. The combined
112-entrypoint block passes the fresh108-module gate. Affected function bytes,
resolved relocation targets/types and addends, and all module hashes match the
preserved baseline. No signature or algorithm is changed; library receipts
remain current.
