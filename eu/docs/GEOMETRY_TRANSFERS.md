# Geometry transfer state and overlay barriers

These names follow the geometry DMA bodies and their callers. They describe
operations rather than claiming original SDK symbols. The matched C and linked
modules retain their original bytes; the final section gives the official checks.

| Previous symbol | Proposed name | Established operation |
|---|---|---|
| `func_01ffa1e8` | `ClearGeometryTransferBusy` | DMA callback that clears its supplied busy word. |
| `func_01ffa1f4` | `SetGeometryDmaFastMode` | Stores the selector used to choose the fast or ordinary GX DMA sender. |
| `func_02019cf4` | `SetGeometryCommandBufferIfUnset` | Installs a buffer only while the global buffer pointer is null and clears its count. |
| `FSi_WaitForCardThread` | `WaitForGeometryTransfer` | Spins while the geometry transfer busy word is nonzero. |
| `func_02029f8c` | `LoadOverlayAfterGeometryTransfer` | Waits for that transfer, then calls `FS_LoadOverlay` with the processor/overlay pair. |
| `func_02029fac` | `UnloadOverlayAfterGeometryTransfer` | Waits, then calls `FS_UnloadOverlay` with the same pair. |
| `InitializeArchiveBackend` | `InitSbcHandlersAndFastDma` | Installs the 14 SBC command handlers and selects fast geometry DMA. This additional rename corrects a misleading existing name. |

`FlushGeometryCommandBuffer` establishes the shared state:

- `data_027e00a8` points to a count word followed by 192 geometry-command words.
- `data_027e00ac` is the busy flag. It becomes one before a large async transfer;
  its completion callback receives the flag's address and clears it.
- The first word of `data_01fffea0` selects
  `MI_SendGXCommandAsyncFast` when nonzero and `MI_SendGXCommandAsync` when zero.
  The owning BSS allocation is eight words; only the first word's role is
  established. Do not replace the whole allocation with one scalar.

The small-transfer path can append data to the command buffer while a transfer
is busy when capacity permits. Otherwise it waits and sends buffered/current
commands through the CPU path. The large-transfer path drains any buffered
words before setting busy and issuing async DMA. Neither the busy callback nor
the wait routine allocates or releases the command buffer.

The setter stores the mode word unchanged; it does not normalize it to one.
The old `seed` parameter and `srand` alias are misleading: this state selects a
geometry DMA backend and has no demonstrated random-number role. Similarly,
`InitializeArchiveBackend` installs rendering SBC handlers, not a file archive
backend. The actual LCG state is elsewhere at `data_020604d8`.

The set-if-unset buffer routine clears the count only when it installs a new
pointer. It neither replaces an existing buffer nor validates a null input on
that path. There is no ownership transfer, capacity parameter or allocation in
its interface. Use the existing count-plus-192-word type/extent when recovering
the DS view, and keep borrowed stack/global lifetime explicit at callers.

The completion callback now exposes its real `void callback(void *)` contract;
its generated four argument slots and returned pointer word were not logical DMA
inputs or a completion result. The wait definition now takes no argument. The
two shared-source overlay wrappers still pass their existing processor/overlay
register words through an old erased declaration; the wait reads neither word.
These are legacy DS call adapters, not additional synchronization inputs. It does not sleep, yield or time out. The overlay wrappers
wait before the SDK operation and discard its return value; a name must not
invent a successful-load result.

For a host port, replace this geometry barrier deliberately with the renderer's
synchronization contract. Do not turn it into a card/filesystem wait solely
because of the old `FSi` label. Buffer ownership, DMA completion and overlay
code lifetime are separate concerns. The wait's global busy flag is not a
portable host synchronization primitive or proof of reentrancy.

Implementation note: `WaitForGeometryTransfer.c` retains the historical
`libs/nitro/fs/calls` directory to preserve the existing build classification.
The filename and symbol now describe its actual rendering role. The existing
renamer scans library sources too and checks the complete rename before writing
references. Shared US source filenames and macro input identifiers remain intact;
EU aliases bind their actual targets.

Evidence: `src/itcm/library_nitro_nns/func_01ffa204.c`,
`src/itcm/library_nitro_fs/FSi_WaitForCardThread_01ff8140.c`,
`src/arm9/core_small/func_02019ce0.c`,
`src/arm9/core_small/func_02029f78.c`,
`src/arm9/core_small/func_02029f98.c`,
`src/arm9/archive_startup/InitializeArchiveBackend_0203a858.c` and EU aliases.

## Verification

From `eu/`:

```sh
python tools/verify_idx.py src/auto/ClearGeometryTransferBusy.c ClearGeometryTransferBusy
python tools/verify_idx.py src/calls/SetGeometryDmaFastMode.c SetGeometryDmaFastMode
python tools/verify_idx.py src/calls/SetGeometryCommandBufferIfUnset.c SetGeometryCommandBufferIfUnset
python tools/verify_idx.py libs/nitro/fs/calls/WaitForGeometryTransfer.c WaitForGeometryTransfer
python tools/verify_idx.py src/calls/LoadOverlayAfterGeometryTransfer.c LoadOverlayAfterGeometryTransfer
python tools/verify_idx.py src/calls/UnloadOverlayAfterGeometryTransfer.c UnloadOverlayAfterGeometryTransfer
python tools/verify_idx.py src/calls/InitSbcHandlersAndFastDma.c InitSbcHandlersAndFastDma --thumb
bash tools/gate.sh
```

Expected sizes are 12, 16, 32, 24, 32, 32 and 128 bytes. Integration also compares
affected production function texts, resolved relocation targets/types and addends
with the saved baseline, and requires unchanged hashes for all 108 linked modules.
