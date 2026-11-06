# Field command 3 no-op and word-payload hook

These three operational names preserve the matched definitions and their
native call behavior. They do not identify an unknown gameplay feature or
claim a portable callback signature from legacy erased declarations.

| EU identity | Name |
| --- | --- |
| ov001:0206339c | `FieldScriptCommand3_Noop` |
| ov001:02064ec0 | `ScriptCmd_FieldNoop3` |
| ov001:02068980 | `FieldScript_WordPayloadHookNoop` |

## Field command 3

The registered field group 2 entry 0x3 is a run/resume pair containing
pointer 0x02064ec1 and null. The wrapper forwards native R0 unchanged to
the empty helper, then writes literal 1. Neither function reads operands
or dereferences the supplied VM or operand pointers.

The actual helper remains `void(void)`; its native BX LR preserves R0.
The wrapper's legacy pointer declaration does not establish another
logical input. No new parameter or shared ROOT signature is proposed.
MAIN run result 1 clears the resume, advances by encoded command length
and continues; an auxiliary nonzero result clears its callback/argument
then advances. There is no filesystem unload or FS success result.
Opcode 3 is the proven table index, not a guessed initialization or
reserved-command role.

## Word-payload hook

`ScriptOp_SendPayloadWords` is field group 2 entry 0x34, paired with a null
resume. It decodes two initial integers, then builds a local word buffer.
Within the following descriptor loop, kind 0 appends three FX32 values,
kind 1 appends one integer and kind 2 appends one FX32 value. An unrecognized
kind consumes its kind descriptor without appending a word. The loop's
index counts consumed descriptors, including each kind descriptor.

The caller passes the first integer in R0, the local buffer in R1 and
`wordCount * 4` bytes in R2 to the hook at 02068980. The helper is a two-byte
BX LR: it consumes no argument, performs no memory change and retains no
buffer. The caller then overwrites R0 with 1. This is the VM advance result,
not a result from a send operation.

The buffer is a temporary `u32 words[128]` and is borrowed for this immediate
call. The caller does not add a bounds check; this review adds none. Word
units, integer-ID domain and feature intent remain opaque. The existing
caller name does not prove a network packet, IPC, queue, transport or a
disabled/optional feature. `WordPayloadHookNoop` describes only the actual
decoded-word call boundary and empty implementation.

The helper's definition remains no-input `void(void)`. The legacy caller
declaration supplies three native words; no parameter is invented to make
those declarations look like a recovered portable API.

Evidence sources:

- `eu/src/overlays/ov001/auto/FieldScriptCommand3_Noop.c`
- `eu/src/overlays/ov001/calls/ScriptCmd_FieldNoop3.c`
- `eu/src/overlays/ov001/auto/FieldScript_WordPayloadHookNoop.c`
- `eu/src/overlays/ov001/calls/ScriptOp_SendPayloadWords.c`
- `eu/src/overlays/ov001/data/tables/gFieldScriptCommandHandlers.c`
- `eu/src/overlays/ov001/calls/EnterPendingRoom.c`
- `eu/src/calls/StoreGlobalArrayEntry.c`
- `eu/src/calls/ScriptVm_RunFrame.c`

Nine original function extents and the field handler-table words were
compared directly with the extracted EU ROM. No candidate was compiled;
official configured-path checks and the full gate remain integration work.


## Active EU sources

- [FieldScriptCommand3_Noop](../src/overlays/ov001/auto/FieldScriptCommand3_Noop.c).
- [ScriptCmd_FieldNoop3](../src/overlays/ov001/calls/ScriptCmd_FieldNoop3.c).
- [FieldScript_WordPayloadHookNoop](../src/overlays/ov001/auto/FieldScript_WordPayloadHookNoop.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/auto/FieldScriptCommand3_Noop.c FieldScriptCommand3_Noop --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_FieldNoop3.c ScriptCmd_FieldNoop3 --thumb
python tools/verify_idx.py src/overlays/ov001/auto/FieldScript_WordPayloadHookNoop.c FieldScript_WordPayloadHookNoop --thumb
bash tools/gate.sh
```
