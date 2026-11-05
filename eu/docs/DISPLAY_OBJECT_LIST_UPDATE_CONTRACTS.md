# Display object list update entrypoints

This document records 2 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

Both functions operate on the display-object list manager. The shared source aliases previously made one look like an NNS foundation-list initializer and the other like a stream alarm callback. Their callee is `DispObjList_Update`, which writes OAM records, advances cell animations and delegates upload handling to `OamBuffer_Flush`.

`UpdateDisplayObjectListQueued` supplies mode 0; the OAM copy is queued. `UpdateDisplayObjectListImmediate` supplies mode 1; the CPU cache is flushed and GX/GXS OAM upload is called directly. Neither function owns or frees the manager, and the queued entrypoint does not drain the global VRAM task queue. Both are `void` operations. The old sound-related enum is a source artifact for the constant 1, not an audio contract.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `main:0204f130` | ARM | `NNS_FndInitListWithOffset0_0204f130` | `UpdateDisplayObjectListQueued` | [eu/src/calls/UpdateDisplayObjectListQueued.c](../src/calls/UpdateDisplayObjectListQueued.c) |
| `main:0204f140` | ARM | `AlarmCallback_0204f140` | `UpdateDisplayObjectListImmediate` | [eu/src/calls/UpdateDisplayObjectListImmediate.c](../src/calls/UpdateDisplayObjectListImmediate.c) |

## UpdateDisplayObjectListQueued

Identity: `main:0204f130`, ARM, native extent 16 bytes (including any configured pool). Previous symbol: `NNS_FndInitListWithOffset0_0204f130`.

EU entrypoint: [eu/src/calls/UpdateDisplayObjectListQueued.c](../src/calls/UpdateDisplayObjectListQueued.c).

```c
void UpdateDisplayObjectListQueued(void *list);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Calls the real DispObjList_Update(manager,0) through an old NNS list-initializer source alias. Source: [src/arm9/library_nitro_nns/NNS_FndInitListWithOffset0_0204f11c.c:1-6](../../src/arm9/library_nitro_nns/NNS_FndInitListWithOffset0_0204f11c.c).
- Alias proves the callee identity. Source: [eu/src/calls/UpdateDisplayObjectListQueued.c:1-3](../src/calls/UpdateDisplayObjectListQueued.c).
- Passes mode to OamBuffer_Flush after OAM writing and cell animation tick. Source: [src/arm9/shared_engine/DispObjList_Update_0204ed34.c:1-50](../../src/arm9/shared_engine/DispObjList_Update_0204ed34.c).
- Zero mode queues the OAM copy; nonzero directly uploads the OAM buffer. Source: [src/arm9/shared_engine/OamBuffer_Flush_0204e390.c:1-51](../../src/arm9/shared_engine/OamBuffer_Flush_0204e390.c).

Contract limits:

- Not an NNS list initializer.
- Does not itself flush the global VRAM task queue.

## UpdateDisplayObjectListImmediate

Identity: `main:0204f140`, ARM, native extent 16 bytes (including any configured pool). Previous symbol: `AlarmCallback_0204f140`.

EU entrypoint: [eu/src/calls/UpdateDisplayObjectListImmediate.c](../src/calls/UpdateDisplayObjectListImmediate.c).

```c
void UpdateDisplayObjectListImmediate(void * arg);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Calls the real DispObjList_Update with a nonzero interval enum value used here as immediate-upload mode. Source: [src/arm9/library_nns_snd/AlarmCallback_0204f12c.c:1-12](../../src/arm9/library_nns_snd/AlarmCallback_0204f12c.c).
- EU aliases StrmCallback to DispObjList_Update. Source: [eu/src/calls/UpdateDisplayObjectListImmediate.c:1-3](../src/calls/UpdateDisplayObjectListImmediate.c).
- NNS_SND_STRM_CALLBACK_INTERVAL is the second enum value,1. Source: [include/nnsys/snd.h:1-464](../../include/nnsys/snd.h).
- Nonzero immediate mode flushes CPU cache and calls GX/GXS_LoadOAM directly. Source: [src/arm9/shared_engine/OamBuffer_Flush_0204e390.c:1-51](../../src/arm9/shared_engine/OamBuffer_Flush_0204e390.c).

Contract limits:

- Not an audio alarm callback.
- The real logical input is the display manager; the old NNSSndStrm type is false.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/calls/UpdateDisplayObjectListQueued.c UpdateDisplayObjectListQueued
python tools/verify_idx.py src/calls/UpdateDisplayObjectListImmediate.c UpdateDisplayObjectListImmediate
bash tools/gate.sh
```

All entrypoints in this document pass their official function checks. The
combined106-entrypoint block passes the fresh108-module gate; affected function
bytes, resolved relocation targets/types and addends, and all module hashes
match the preserved pre-rename baseline. No algorithm, signature or native
matching-policy change is included. Verified-library receipts remain current.
