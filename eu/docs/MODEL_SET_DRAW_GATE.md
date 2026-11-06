# Model-set draw gate

`IsModelSetDrawEnabled` (ov021:020a9d24) returns a normalized BOOL equivalent to `(*flags & 3) == 3`. Its native declaration remains `BOOL ...(u32 *flags)` with no NULL guard.

LoadModelObject sets header bit 0 during resource initialization; ReleaseModelSet clears the header. SetBit1WhenBit0Set changes bit 1 while bit 0 is set. DrawModelWithAttachment emits geometry only when both bits are set, proving this predicate's drawing role. Actor callers pass the same model-set headers.

This result does not establish GPU completion or final visibility: the load bit is set before loader calls, and higher-level draw gates still apply. Model animation flags at +8 and unrelated actor, task or entry-pool flags have separate owners. Preserve the exact low-bit test and normalized result when replacing the DS renderer.


## Active EU sources

- [IsModelSetDrawEnabled](../src/overlays/ov021/calls/IsModelSetDrawEnabled.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov021/calls/IsModelSetDrawEnabled.c IsModelSetDrawEnabled --thumb
bash tools/gate.sh
```
