#!/usr/bin/env python3
"""Prove the hand-written MobiClip blocks of ov022 and write their receipts.

MobiClip (Actimagine) ships hand-written ARM: the video decoder the player
copies into its arena, the colour converter, the FastAudio decoder, the
deblocking filter, and the two run/level prefix tables the decoder reads. No compiler produces that code,
so it cannot match as C. A block counts as reconstructed only when every gate
below passes for its checked-in source; the receipt records each result.

1. Source: ARM mnemonics with one address label per instruction, named DATA
   regions, symbolic dispatch words; GAS output equals the ROM bytes at the
   block's addresses and survives a partial link with the project's linker
   (verify_payload.py). Tables: 4096 `vlc` entries plus 256 residue bytes that
   assemble to the ROM bytes.
2. Inventory: the reachable instructions and the declared DATA ranges tile the
   block exactly (mobiclip_inventory.py, mobiclip_kernel_inventory.py).
3. Semantics: a portable implementation reproduces the original code.
   * decoder and tables: complete MODS streams decoded by mobiclip_reference.py
     equal FFmpeg's decode frame for frame, and a hardware capture of one decoded
     frame (state, planes, consumed bytes) is reproduced;
   * colour converter, FastAudio and deblocking: the model and the ROM's own
     instructions, run in arm_exec.py, agree on random inputs and on decoded
     frames, and a hardware capture of the real call is reproduced.

    python tools/mobiclip/verify_mobiclip.py                 # all blocks
    python tools/mobiclip/verify_mobiclip.py --streams w2_OP  # decode a stream first

Hardware captures come from this ROM running in DeSmuME:
capture_mobiclip_decoder.lua writes one decoded frame to eu/build/mobiclip/captures,
capture_mobiclip_kernels.lua the colour converter, deblocking, FastAudio and coding-1
calls to eu/build/mobiclip/kernel_captures (forcing the paths the movies never take). Stream results are cached in eu/build/mobiclip/streams. Receipts are
kept in eu/mobiclip_receipts.json (checked in, like eu/data_matches.json); each
applies only while its source's SHA-256 is unchanged, and eu/tools/audit_progress.py
counts the blocks they cover.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import region  # noqa: E402

POLICY = region.EU / "config" / "arm9" / "mobiclip_blocks.json"
RECEIPTS = region.EU / "mobiclip_receipts.json"
STREAMS = region.WORK / "streams"
CAPTURES = region.WORK / "captures"
KERNEL_CAPTURES = region.WORK / "kernel_captures"
HERE = Path(__file__).resolve().parent


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def oracle_sha() -> str:
    return sha256((HERE / "mobiclip_reference.py").read_bytes())


# -- 1. source ---------------------------------------------------------------------

def source_gate(block: dict) -> dict:
    import verify_payload
    source = region.ROOT / block["source"]
    if block["format"] == "arm_mnemonic_payload_v1":
        status, message, info = verify_payload.verify(source, block["name"], POLICY)
        if status != verify_payload.MATCH:
            raise AssertionError(f"source: {message}")
        return {"result": message, "instruction_count": info["instruction_count"],
                "embedded_data_bytes": info["embedded_data_bytes"]}
    if block["format"] == "run_level_table_v1":
        text = source.read_text(encoding="ascii")
        entries = len(re.findall(r"\bvlc\s+\d+,\s*\d+,\s*\d+,\s*[01]\b", text))
        if entries != 4096:
            raise AssertionError(f"source: {entries} vlc entries, expected 4096")
        if re.search(r"^\s*\.(?:incbin|inst|insn|word|4byte|long|fill|space|zero)\b", text, re.M | re.I):
            raise AssertionError("source: opaque directive in a run/level table")
        with tempfile.TemporaryDirectory() as directory:
            obj = Path(directory) / "table.o"
            subprocess.run(["arm-none-eabi-as", "-mcpu=arm946e-s", "-meabi=gnu", "-o", str(obj), str(source)],
                           check=True, capture_output=True)
            from elftools.elf.elffile import ELFFile
            with obj.open("rb") as stream:
                data = ELFFile(stream).get_section_by_name(".text").data()
        lo, hi = int(block["start"], 0), int(block["end"], 0)
        if data != region.ov022_bytes(lo, hi):
            raise AssertionError("source: assembled table differs from the ROM")
        return {"result": f"{entries} entries + 256 residue bytes, GAS exact", "entries": entries}
    raise AssertionError(f"unknown block format {block['format']}")


# -- 2. inventory ------------------------------------------------------------------

def inventory_gate(block: dict, source: dict) -> dict:
    lo, hi = int(block["start"], 0), int(block["end"], 0)
    if block["format"] == "run_level_table_v1":
        return {"result": "pure table: 0x2000 bytes of entries and 0x100 residue bytes"}
    if block["name"] == "mobiclip_decoder_payload":
        import mobiclip_inventory
        counts = mobiclip_inventory.build_inventory(region.ov022_bytes(lo, hi))["counts"]
        code, data = counts["code_bytes"], counts["data_bytes"]
    else:
        import mobiclip_kernel_inventory
        walk = mobiclip_kernel_inventory.walk(block["inventory"])
        if walk["gaps"] or walk["covered"] != walk["size"]:
            raise AssertionError(f"inventory: gaps {walk['gaps']}")
        code, data = walk["instructions"] * 4, walk["embedded_data_bytes"]
    if code + data != hi - lo or code != 4 * source["instruction_count"] or data != source["embedded_data_bytes"]:
        raise AssertionError(f"inventory: {code:#x} code + {data:#x} DATA disagrees with the source")
    return {"result": f"{code:#x} bytes of reachable ARM code + {data:#x} bytes of DATA tile the block",
            "code_bytes": code, "data_bytes": data}


# -- 3. semantics ------------------------------------------------------------------

def stream_records(require_complete: bool = True) -> list[dict]:
    """Cached complete-stream decodes that still apply to the current oracle and tables."""
    import mobiclip_mods
    tables = sha256(b"".join(region.run_level_tables()))
    records = []
    for path in sorted(STREAMS.glob("*.json")):
        record = json.loads(path.read_text(encoding="utf-8"))
        mods = region.MODS_DIR / record["mods_name"]
        if not mods.is_file() or sha256(mods.read_bytes()) != record["mods_sha256"]:
            continue
        if record["oracle_sha256"] != oracle_sha() or record["tables_sha256"] != tables:
            continue
        header = mobiclip_mods.parse_header(mods.read_bytes())
        if not record["all_match"]:
            raise AssertionError(f"streams: {record['mods_name']} does not match FFmpeg")
        if require_complete and record["verified_frames"] != header.frame_count:
            continue
        records.append(record)
    return records


def decode_stream(name: str) -> dict:
    """Decode every frame of one movie with the oracle and compare with FFmpeg."""
    import mobiclip_frame_verify
    import mobiclip_mods
    mods = region.MODS_DIR / f"{name}.mods"
    data = mods.read_bytes()
    header = mobiclip_mods.parse_header(data)
    table0, table1 = region.table_paths()
    result = mobiclip_frame_verify.verify_sequence(mods, table0, table1, header.frame_count)
    record = {
        "mods_name": mods.name, "mods_sha256": sha256(data), "frame_count": header.frame_count,
        "verified_frames": result["verified_frames"], "i_frames": result["i_frames"],
        "p_frames": result["p_frames"], "all_match": result["all_match"],
        "oracle_sha256": oracle_sha(), "tables_sha256": sha256(b"".join(region.run_level_tables())),
        "frames_sha256": sha256(json.dumps(result["frames"]).encode()),
    }
    STREAMS.mkdir(parents=True, exist_ok=True)
    (STREAMS / f"{name}.json").write_text(json.dumps(record, indent=2) + "\n", encoding="utf-8")
    return record


def decoder_semantics() -> dict:
    import mobiclip_capture_verify
    streams = stream_records()
    if not streams:
        raise AssertionError("semantics: no complete MODS stream verified against FFmpeg (use --streams)")
    manifests = sorted(CAPTURES.glob("*_manifest.json"))
    if not manifests:
        raise AssertionError(f"semantics: no decoder capture under {CAPTURES}")
    table0, table1 = region.table_paths()
    captures = []
    for manifest in manifests:
        report = mobiclip_capture_verify.verify_capture(manifest, table0, table1)
        if not report["allMatch"]:
            raise AssertionError(f"semantics: capture {manifest.name} differs: {report['checks']}")
        captures.append({"manifest": manifest.name, "manifest_sha256": sha256(manifest.read_bytes()),
                         "checks": sorted(report["checks"])})
    frames = sum(r["verified_frames"] for r in streams)
    return {"result": f"{len(streams)} complete streams ({frames} frames) equal FFmpeg; "
                      f"{len(captures)} hardware capture(s) reproduced",
            "streams": [{k: r[k] for k in ("mods_name", "mods_sha256", "verified_frames", "i_frames", "p_frames")}
                        for r in streams],
            "captures": captures}


def kernel_semantics(kind: str) -> dict:
    import contextlib
    import io
    module = __import__(f"mobiclip_{kind}")
    pattern = "audio_transform_[0-9].json" if kind == "audio" else f"{kind}.json"
    manifests = sorted(KERNEL_CAPTURES.glob(pattern))
    if not manifests:
        raise AssertionError(f"semantics: no {kind} capture under {KERNEL_CAPTURES}")
    log = io.StringIO()
    with contextlib.redirect_stdout(log):
        if kind in ("deblock", "colour"):
            streams = stream_records()
            module.selftest(40, 1, str(region.MODS_DIR / streams[0]["mods_name"]) if streams else None)
        elif kind == "audio":
            module.selftest(60, 1)
        else:
            module.selftest(200, 4, 100, 1)
        for manifest in manifests:
            module.replay_capture(str(manifest))
    return {"result": " / ".join(line.strip() for line in log.getvalue().splitlines() if line.strip()),
            "captures": [{"manifest": m.name, "manifest_sha256": sha256(m.read_bytes())} for m in manifests]}


def semantic_gate(block: dict) -> dict:
    kind = block["semantics"]
    if kind == "decoder":
        return decoder_semantics()
    if kind in ("fastaudio", "deblock", "colour", "audio"):
        return kernel_semantics(kind)
    raise AssertionError(f"unknown semantics {kind}")


# -- driver ------------------------------------------------------------------------

def relative(value):
    """Receipts are checked in: keep repo paths, never this machine's."""
    if isinstance(value, dict):
        return {k: relative(v) for k, v in value.items() if k != "verified_at"}
    if isinstance(value, list):
        return [relative(v) for v in value]
    if isinstance(value, str):
        for prefix in (str(region.ROOT) + "\\", str(region.ROOT) + "/", region.ROOT.as_posix() + "/"):
            value = value.replace(prefix, "")
        return value.replace("\\", "/")
    return value


def verify_block(block: dict) -> dict:
    source = source_gate(block)
    inventory = inventory_gate(block, source)
    semantics = semantic_gate(block)
    path = region.ROOT / block["source"]
    return {
        "schema_version": 1, "kind": "mobiclip_block", "name": block["name"], "unit": block["unit"],
        "symbol": block["symbol"], "source": block["source"], "source_sha256": sha256(path.read_bytes()),
        "start": block["start"], "end": block["end"], "sha256": block["sha256"],
        "gates": {"source": source, "inventory": inventory, "semantics": semantics},
    }


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("names", nargs="*", help="block names (default: all)")
    parser.add_argument("--streams", nargs="*", default=[], help="decode these movies (mv/<name>.mods) first")
    args = parser.parse_args()
    for name in args.streams:
        record = decode_stream(name)
        print(f"stream {record['mods_name']}: {record['verified_frames']}/{record['frame_count']} frames "
              f"({record['i_frames']} I + {record['p_frames']} P) equal FFmpeg", flush=True)
    policy = json.loads(POLICY.read_text(encoding="utf-8"))
    manifest = json.loads(RECEIPTS.read_text(encoding="utf-8")) if RECEIPTS.is_file() else {"schema_version": 1, "receipts": {}}
    failed = 0
    for block in policy["blocks"]:
        if args.names and block["name"] not in args.names:
            continue
        try:
            receipt = verify_block(block)
        except (AssertionError, subprocess.CalledProcessError, FileNotFoundError) as exc:
            failed += 1
            manifest["receipts"].pop(block["name"], None)
            print(f">>> REFUSED <<< {block['name']}: {exc}")
            continue
        receipt = relative(receipt)
        manifest["receipts"][block["name"]] = receipt
        gates = receipt["gates"]
        print(f">>> PROVED <<< {block['name']}: {gates['source']['result']}; {gates['inventory']['result']}; "
              f"{gates['semantics']['result']}")
    manifest["receipts"] = dict(sorted(manifest["receipts"].items()))
    RECEIPTS.write_text(json.dumps(manifest, indent=1) + "\n", encoding="utf-8", newline="\n")
    raise SystemExit(1 if failed else 0)


if __name__ == "__main__":
    main()
