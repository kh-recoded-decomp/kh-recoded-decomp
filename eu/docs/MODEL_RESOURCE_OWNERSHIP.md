# Resource ownership and model texture trimming

The current names follow the matched heap, loader and model bodies and their
actual callers. The native wrapper now exposes its three logical inputs and
byte-size result through the existing `HeapRecord.h`; the shared core algorithm
is preserved. Reproduction commands are given below.

## The apparent sound/free chain is heap resizing

`ResizeExpandedHeapBlock` accepts `(heapHead, existingBlock, requestedBytes)` and resizes in place. It rounds to four bytes, can grow into the immediately following free block, and recycles a shrinking tail. It returns the resulting block size; growth failure returns zero and failed
tail recycling restores and returns the old size. Growth can absorb a remaining
fragment too small for a free-block header, so the returned size need not equal
the rounded request. The native u32 four-byte rounding is preserved. It does not relocate the pointer. See `src/arm9/library_nitro_nns/func_02013164.c:98`.

`ResizeExpandedHeapBlockWithHeapRef` is a forwarding wrapper for that operation. The EU aliases resolve its callee to the resize implementation. The ROM at `0202a294` loads `[r0]` into `r0` and tail-branches without changing `r1` or `r2`. Thus its inputs are a heap reference, block pointer and requested size. The old two-argument sound signature suppressed the live third input. The
current defining EU wrapper states all three inputs and the native size result.

The current names are `ResizeExpandedHeapBlock` and
`ResizeExpandedHeapBlockWithHeapRef`. The wrapper takes an existing `HeapRecord`,
block pointer and requested byte size; it loads the first heap word and forwards
all three inputs. Its return is the resulting size, not a sound status or pointer.
The actual core type `struct NnsFndHeapHead` is kept opaque in the shared header.
The 16-byte wrapper and the 352-byte core retain their original instructions.

## Trimming an archive after texture setup

`TrimArchiveBeforeTexturePayload` finds section 7 entry 0 of the archive, obtains its texture block, and requests an allocation size of:

```c
newBytes = (u8 *)resTex + resTex->texInfo.ofsTex - (u8 *)archive;
```

The field identity follows `NNSG3dResTex` in `include/nnsys/g3d.h:155`. The helper does nothing when the entry or texture block is absent. It changes the heap allocation size; it does not rewrite archive file lengths or copy the retained prefix. The existing option word is passed in `r3` but is not an input to the three-argument resize target.

`TrimModelArchiveBeforeTexturePayload` obtains the archive and heap reference from the model resource slot at `model + 0x74` and forwards to this helper. The entrypoints are `TrimArchiveBeforeTexturePayload` and `TrimModelArchiveBeforeTexturePayload`.

## Initializer variants

`InitModelWithOptionalTextureTrim` stores the resource slot at `model + 0x74`, then calls `InitModelInstance(model, NULL, trimOption, 1, extra)`. Its third input selects optional trimming, so `InitModelWithOptionalTextureTrim` describes its actual behavior.

`InitModelUsingTextureHeader` instead supplies a texture header with trimOption zero: `InitModelInstance(model, textureHeader, 0, 1, extra)`. The acquisition path can reuse a cached texture block or locate/copy the header prefix from the supplied file. It is named `InitModelUsingTextureHeader`; a boolean texture flag would be an incorrect parameter type.

The core initializer selects direct texture/palette upload hooks before the branch that trims the file, then restores queued hooks. `SetFileLoaderTextureUploadQueueMode(0)` selects `Gfd_LoadTex_0202c1b0` and `Gfd_LoadTexPltt_0202c1f4`; nonzero selects `EnqueueGfxCmd0/1`. Keep this ordering when separating the renderer and asset system for a port. A standalone call to the trim helper has no upload-completion check.

## Distinct references in the shared resource slot

The source views establish different counters and ownership operations at these offsets:

| Offset | Established behavior |
| --- | --- |
| `+0x00` | File reference count decremented by `ReleaseSharedRecordSlot`; zero releases the archive and optional copied block. |
| `+0x02` | Resource binding/load acquisition count used by `AcquireOrRefreshResourceBlock`; initial acquisition initializes the resource. |
| `+0x04` | Counter incremented when its resource setup flag is nonzero. |
| `+0x06` | Halfword forwarded by the model trim wrapper; meaning still unproven. |
| `+0x08` | Heap reference for the archive allocation. |
| `+0x0c` | Archive resource data pointer. |
| `+0x10` | Optional cached/copied texture header block. |

Do not combine the first three halfwords into a single refcount. Their full decrement pairing needs the corresponding release paths before a common ownership type is finalized. Relevant sources are `src/arm9/archive_startup/func_0202c940.c:19`, `src/arm9/shared_records/ReleaseSharedRecordSlot_0202c8a8.c:24`, and `src/arm9/model_animation/InitModelInstance_0202eb84.c:79`.

## Palette submission

`SubmitResourcePaletteUpload` submits `resTex + plttInfo.ofsPlttData` to the selected palette hook, using `(vramKey & 0xffff) << 3` and `sizePltt << 3`. It sets flag bit 0 immediately after submission. `SubmitResourcePaletteUpload` deliberately does not promise completion; queue mode determines whether the hook is direct or deferred.

## Native result and host boundary

The trim adapters still have legacy word/return declarations. The model wrapper
propagates the underlying native register word through its epilogue, while the
archive adapter's C is void; neither spelling establishes a new Boolean success
protocol. No caller is promised that trimming reached exactly the requested
byte count. A port must preserve actual-size/failure behavior and texture-upload
completion before releasing CPU payload storage.

The core resizes an existing allocation in place. It is not a normal free or a
moving realloc. The heap reference is borrowed; the wrapper does not allocate,
destroy or take ownership of the heap record.

## Reproduction

From `eu/`:

```sh
python tools/verify_idx.py src/calls/SubmitResourcePaletteUpload.c SubmitResourcePaletteUpload
python tools/verify_idx.py src/calls/ResizeExpandedHeapBlock.c ResizeExpandedHeapBlock
python tools/verify_idx.py src/calls/ResizeExpandedHeapBlockWithHeapRef.c ResizeExpandedHeapBlockWithHeapRef
python tools/verify_idx.py src/calls/TrimArchiveBeforeTexturePayload.c TrimArchiveBeforeTexturePayload
python tools/verify_idx.py src/calls/InitModelWithOptionalTextureTrim.c InitModelWithOptionalTextureTrim
python tools/verify_idx.py src/calls/InitModelUsingTextureHeader.c InitModelUsingTextureHeader
python tools/verify_idx.py src/calls/TrimModelArchiveBeforeTexturePayload.c TrimModelArchiveBeforeTexturePayload
bash tools/gate.sh
```

Integration compares preserved production texts and resolved relocation
targets/types/addends, then requires all 108 linked module hashes unchanged.
Ownership and logical input meanings are established from source/ROM dataflow
in addition to the instruction checks.
