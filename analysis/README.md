# Actor model appearance: connected analysis

The first connected investigation follows the command that makes an actor's
model partly transparent and clears its vertical offset. Shared structures and
signatures are applied to the persistent Ghidra project so they improve related
callers as well.

## What is established

- `ov001:0208deb0` reads a script actor ID, finds the actor, clears `offset.y`,
  sets all model material alpha values to 8, and sets polygon IDs to 63.
- `ActorNode.modelResource` is at `+0x7c`; the offset vector is at `+0xb4`.
- `ModelResource.materialCount` is at `+0x18`; its material table offset is at `+8`.
- `Actor_GetById` has 218 direct callsites. Its registry has a pointer array
  beginning at `+0x20`; each pointer addresses storage with the actor at `+0x10`.
- The material alpha setter changes bits 16–20. The polygon-ID setter changes
  bits 24–29. Both operations are corroborated by the recovered shared model API.

The scenes and actors that trigger this command remain unobserved. No specific
enemy, disappearance event, or fading effect is assigned to neighboring code
without further evidence.

## Persistent knowledge

- [actor_model.json](actor_model.json): reviewed function signatures, names,
  local-variable names, evidence, uncertainty, and module-qualified callers.
- [types/actor_model.h](types/actor_model.h): partial shared structures. Reserved
  fields explicitly preserve unknown areas. These are 32-bit ARM layouts.
- The Ghidra project is local at `build/ghidra/project/BK9E.gpr`.
- Ghidra reports, the full generated import graph, and pseudocode are local under
  `build/ghidra/`. Pseudocode is not added to matching coverage.

## Create or update the project

After the regular ROM setup, with JDK 21 or newer available:

```powershell
python tools/ghidra_project.py install
python tools/ghidra_project.py create
# After reviewing and editing the shared knowledge:
python tools/ghidra_project.py update
```

The pinned Ghidra installation defaults to `../decomp-tools/`, outside this
repository. Set `GHIDRA_HOME` to use a compatible existing installation. Open
`BK9E.gpr` in Ghidra, then open `arm9.bin` in its CodeBrowser.

ARM9, ITCM, and DTCM share the main address space. Each of the 105 overlays has
its own named Ghidra overlay address space. ARM7 has a separate program; its
functions remain unanalysed. DSD references with one known target are imported
with their module identity. Multiple possible overlays are bookmarked as
ambiguous; runtime overlay state must resolve them. They are not silently merged.

The initial import seeded 10,359 ARM9 functions, 57,709 references, and 388
ambiguous overlay-reference bookmarks. It also imported all established C match
names. Updates preserve unrelated manual function names and comments; the
reviewed JSON explicitly controls its listed signatures and types. Keep the
project closed during headless updates. No automatic whole-program analysis
has been run beyond the imported boundaries and explicit disassembly.

## Continue the discovery

1. Start at `ov001::Script_MakeActorTranslucentAndClearVerticalOffset`.
2. Follow its named model setters and use their references to inspect other
   callers. All pointers to `ActorNode` can now expose the same known fields.
3. Investigate the nearby paths below. Keep unknown fields unnamed by gameplay
   purpose until their consumers or runtime behavior establish it.
4. Record new evidence in the JSON and partial types, then update Ghidra.
5. Recover C and compile it against the original bytes. A semantic annotation
   alone does not change the progress percentage.

| Next path | Established connection | What is still unknown |
|---|---|---|
| `ov001:0208de3c → 0208a848 → 02089060` | Adjacent script command and shared animation-selection path | Which animation/event each operand selects |
| `ov001:0208cbb4 → 0208a2fc` | Resolves an actor, updates its `+0x80` halfword and flag `0x20`, propagates a value | Meaning and units of that value |
| `ov001:0208df48 → 0208c2c4 → 02089db0` | Adjacent command, 3D transforms, actor lookup and virtual calls | The in-game action and relevant virtual method |

Emulator observation is the next source of evidence when static callers cannot
establish the visible effect. No emulator behavior has been claimed as tested.

Ghidra's [analysis guide](https://ghidra.re/ghidra_docs/GhidraClass/Advanced/improvingDisassemblyAndDecompilation.pdf)
describes applying shared data types and signatures to improve decompilation.
