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
