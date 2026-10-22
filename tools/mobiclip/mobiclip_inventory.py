#!/usr/bin/env python3
"""Reproducible ARM-code/data inventory for the ignored MobiClip payload."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from collections import deque
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_LITTLE_ENDIAN, Cs
from capstone.arm import (
    ARM_CC_AL,
    ARM_CC_INVALID,
    ARM_OP_IMM,
    ARM_OP_REG,
    ARM_REG_LR,
    ARM_REG_PC,
)
from mobiclip_reference import (
    BLOCK4X4_COEFFICIENT_MASKS,
    BLOCK8X8_COEFFICIENT_MASKS,
    PACKED_AVERAGE_LANE_MASK,
    PFRAME_BLOCK4X4_COEFFICIENT_MASKS,
    PFRAME_BLOCK8X8_COEFFICIENT_MASKS,
    QUANT4X4,
    QUANT8X8,
    ZIGZAG4X4,
    ZIGZAG8X8,
)

import region

ROOT = region.ROOT
BASE, SIZE = 0x020B0BC0, 0x659C
SHA256 = "5508ae5f765eb86e81b2ad8d76dccf6d4a30e3381d3e8b248fb8d4a6204b83f5"

# Entries validated independently in Ghidra. Some routines share tails.
ENTRIES = (
    0x020B0C4C, 0x020B0D94, 0x020B0DBC, 0x020B0DD4, 0x020B0DEC,
    0x020B0E04, 0x020B0E1C, 0x020B0E34, 0x020B0E50, 0x020B0E6C,
    0x020B0EE0, 0x020B10C4, 0x020B12FC, 0x020B1648, 0x020B199C,
    0x020B22B0, 0x020B24C4, 0x020B2588, 0x020B2660, 0x020B289C,
    0x020B28F4, 0x020B29EC, 0x020B2BA4, 0x020B2BF4, 0x020B2C24,
    0x020B2C38, 0x020B2C74, 0x020B2C78, 0x020B3188, 0x020b4354,
    0x020b4970, 0x020b4b5c, 0x020b5514, 0x020B56B8, 0x020b5830,
    0x020B59A8, 0x020b5b84, 0x020B5CF8, 0x020B5EC4, 0x020B6010,
)

# Computed continuations that are not standalone Ghidra functions.
COMPUTED_SEEDS = (
    0x020B0DB4,
    0x020B244C,
    0x020B4DC4,
    0x020B4F70,
    0x020B5090,
    0x020B5210,
)

# table address, entry count, relative base, name
TABLES = (
    (0x020B0BCC, 16, 0x020B0BCC, "luma_interpolation"),
    (0x020B0C0C, 16, 0x020B0C0C, "chroma_interpolation"),
    (0x020B0D60, 10, 0x020B0D60, "pframe_macroblock"),
    (0x020B0EA0, 16, 0x020B0EA0, "motion16_dispatch"),
    (0x020B0FE4, 10, 0x020B0FE4, "motion16_modes"),
    (0x020B10F8, 8, 0x020B0FE4, "motion8x16_dispatch"),
    (0x020B121C, 10, 0x020B121C, "motion8x16_modes"),
    (0x020B1330, 4, 0x020B121C, "intra16_dispatch"),
    (0x020B1454, 10, 0x020B1454, "intra16_modes_a"),
    (0x020B1568, 10, 0x020B1568, "intra16_modes_b"),
    (0x020B168C, 10, 0x020B168C, "motion16x8_modes_a"),
    (0x020B17B0, 10, 0x020B17B0, "motion16x8_modes_b"),
    (0x020B18BC, 10, 0x020B18BC, "motion16x8_modes_c"),
    (0x020B19E0, 10, 0x020B19E0, "predicted_intra_modes_a"),
    (0x020B1B04, 10, 0x020B1B04, "predicted_intra_modes_b"),
    (0x020B1C10, 10, 0x020B1C10, "predicted_intra_modes_c"),
    (0x020B1D50, 10, 0x020B1D50, "predicted_intra_modes_d"),
    (0x020B1E80, 10, 0x020B1E80, "predicted_intra_modes_e"),
    (0x020B1FA8, 10, 0x020B1FA8, "predicted_intra_modes_f"),
    (0x020B20B8, 10, 0x020B20B8, "predicted_intra_modes_g"),
    (0x020B21C0, 10, 0x020B21C0, "predicted_intra_modes_h"),
    (0x020B27D8, 20, 0x020B27D8, "intra_prediction"),
)

# These four-way tables contain signed offsets back to prediction helpers.
SIGNED_TABLES = (
    (0x020B35F4, 4, 0x020B35F4, "intra8_neighbor_dispatch"),
    (0x020B45A8, 4, 0x020B45A8, "intra4_neighbor_dispatch"),
)

# Proven non-instruction ranges. End addresses are exclusive.
DATA_REGIONS = (
    (0x020B0BC4, 0x020B0BCC, "payload_header"),
    (0x020B0BCC, 0x020B0C0C, "luma_interpolation_dispatch"),
    (0x020B0C0C, 0x020B0C4C, "chroma_interpolation_dispatch"),
    (0x020B0D40, 0x020B0D94, "pframe_prefix_offsets_and_lengths"),
    (0x020B0EA0, 0x020B0EE0, "luma_kernel_dispatch"),
    (0x020B0FD4, 0x020B1018, "motion16_selector_and_offsets"),
    (0x020B10F8, 0x020B1118, "chroma_kernel_dispatch"),
    (0x020B120C, 0x020B1250, "motion8x16_selector_and_offsets"),
    (0x020B1330, 0x020B1340, "chroma_narrow_kernel_dispatch"),
    (0x020B1434, 0x020B1490, "intra16_selector_and_offsets"),
    (0x020B1558, 0x020B159C, "motion8x8_selector_and_offsets"),
    (0x020B167C, 0x020B16C0, "motion16x4_selector_and_offsets"),
    (0x020B17A0, 0x020B17E4, "motion16x2_selector_and_offsets"),
    (0x020B18AC, 0x020B18F0, "motion8x8_alt_selector_and_offsets"),
    (0x020B19D0, 0x020B1A14, "predicted_mode_a_selector_and_offsets"),
    (0x020B1AF4, 0x020B1B38, "predicted_mode_b_selector_and_offsets"),
    (0x020B1C00, 0x020B1C50, "predicted_mode_c_selector_and_offsets"),
    (0x020B1D30, 0x020B1D90, "predicted_mode_d_selector_and_offsets"),
    (0x020B1E70, 0x020B1EC0, "predicted_mode_e_selector_and_offsets"),
    (0x020B1F88, 0x020B1FE0, "predicted_mode_f_selector_and_offsets"),
    (0x020B20A8, 0x020B20F0, "predicted_mode_g_selector_and_offsets"),
    (0x020B21B8, 0x020B2200, "predicted_mode_h_selector_and_offsets"),
    (0x020B2484, 0x020B24C4, "iframe_residual_permutation"),
    (0x020B2620, 0x020B2660, "pframe_residual_mask"),
    (0x020B27D8, 0x020B2828, "intra_prediction_dispatch"),
    (0x020B29B4, 0x020B29C8, "intra_coefficient_mask"),
    (0x020B2A84, 0x020B2A94, "pframe_coefficient_mask"),
    (0x020B35F4, 0x020B3604, "intra8_neighbor_dispatch"),
    (0x020B45A8, 0x020B45B8, "intra4_neighbor_dispatch"),
    (0x020B5278, 0x020B53F8, "quant8_base_matrices"),
    (0x020B53F8, 0x020B5438, "scan8"),
    (0x020B5438, 0x020B5498, "quant4_base_matrices"),
    (0x020B5498, 0x020B54A8, "scan4"),
    (0x020B54A8, 0x020B54DE, "qp_shift"),
    (0x020B54DE, 0x020b5514, "qp_matrix_selector"),
    (0x020B6148, 0x020B614C, "packed_average_lane_mask"),
    (0x020B68F4, 0x020B68F8, "packed_average_lane_mask_1"),
    (0x020B6DF0, 0x020B6DF4, "packed_average_lane_mask_2"),
    (0x020B7084, 0x020B7088, "packed_average_lane_mask_3"),
)


def inside(address: int) -> bool:
    return BASE <= address < BASE + SIZE and address % 4 == 0


def read_tables(payload: bytes) -> tuple[list[dict], set[int]]:
    records, targets = [], set()
    for address, count, relative_base, name in TABLES:
        entries = []
        for index in range(count):
            offset = struct.unpack_from("<I", payload, address - BASE + 4 * index)[0]
            if offset == 0:
                entries.append({"index": index, "offset": 0, "target": None})
                continue
            target = relative_base + offset
            if not inside(target):
                raise ValueError(f"{name}[{index}] target outside payload: {target:#x}")
            targets.add(target)
            entries.append({"index": index, "offset": offset, "target": f"0x{target:08x}"})
        records.append({
            "name": name, "address": f"0x{address:08x}", "size": count * 4,
            "relative_base": f"0x{relative_base:08x}", "entries": entries,
        })
    return records, targets


def read_signed_tables(payload: bytes) -> tuple[list[dict], set[int]]:
    records, targets = [], set()
    for address, count, relative_base, name in SIGNED_TABLES:
        entries = []
        for index in range(count):
            offset = struct.unpack_from("<i", payload, address - BASE + 4 * index)[0]
            target = relative_base + offset
            if not inside(target):
                raise ValueError(f"{name}[{index}] target outside payload: {target:#x}")
            targets.add(target)
            entries.append({"index": index, "offset": offset, "target": f"0x{target:08x}"})
        records.append({
            "name": name, "address": f"0x{address:08x}", "size": count * 4,
            "relative_base": f"0x{relative_base:08x}", "entries": entries,
        })
    return records, targets


def verify_semantic_data(payload: bytes) -> list[dict]:
    flatten = lambda rows: bytes(value for row in rows for value in row)
    regions = (
        (0x020B2484, "iframe_residual_permutation", bytes(BLOCK8X8_COEFFICIENT_MASKS)),
        (0x020B2620, "pframe_residual_mask", bytes(PFRAME_BLOCK8X8_COEFFICIENT_MASKS)),
        (
            0x020B29B4,
            "intra_coefficient_mask_padded",
            bytes((0, *BLOCK4X4_COEFFICIENT_MASKS, 0, 0, 0)),
        ),
        (
            0x020B2A84,
            "pframe_coefficient_mask",
            bytes(PFRAME_BLOCK4X4_COEFFICIENT_MASKS),
        ),
        (0x020B5278, "quant8_base_matrices", flatten(QUANT8X8)),
        (0x020B53F8, "scan8", bytes(ZIGZAG8X8)),
        (0x020B5438, "quant4_base_matrices", flatten(QUANT4X4)),
        (0x020B5498, "scan4", bytes(ZIGZAG4X4)),
        (0x020B54A8, "qp_shift", bytes(qp // 6 for qp in range(54))),
        (0x020B54DE, "qp_matrix_selector", bytes(qp % 6 for qp in range(54))),
        (
            0x020B6148,
            "packed_average_lane_mask",
            PACKED_AVERAGE_LANE_MASK.to_bytes(4, "little"),
        ),
        (
            0x020B68F4,
            "packed_average_lane_mask_1",
            PACKED_AVERAGE_LANE_MASK.to_bytes(4, "little"),
        ),
        (
            0x020B6DF0,
            "packed_average_lane_mask_2",
            PACKED_AVERAGE_LANE_MASK.to_bytes(4, "little"),
        ),
        (
            0x020B7084,
            "packed_average_lane_mask_3",
            PACKED_AVERAGE_LANE_MASK.to_bytes(4, "little"),
        ),
    )
    records = []
    for address, name, expected in regions:
        observed = payload[address - BASE:address - BASE + len(expected)]
        if observed != expected:
            raise ValueError(f"semantic data mismatch in {name} at {address:#010x}")
        records.append({
            "name": name,
            "address": f"0x{address:08x}",
            "size": len(expected),
            "sha256": hashlib.sha256(expected).hexdigest(),
            "matches_payload": True,
        })
    return records


def infer_relative_tables(payload: bytes) -> tuple[list[dict], set[int]]:
    """Find additional relative dispatch tables whose targets begin in ARM mode."""
    records, targets = [], set()
    address = BASE
    while address < BASE + SIZE:
        entries = []
        cursor = address
        while cursor < BASE + SIZE:
            offset = struct.unpack_from("<I", payload, cursor - BASE)[0]
            target = address + offset
            if offset % 4 or not inside(target):
                break
            target_word = struct.unpack_from("<I", payload, target - BASE)[0]
            if target_word >> 28 != 0xE:
                break
            entries.append({"offset": offset, "target": f"0x{target:08x}"})
            cursor += 4
        if len(entries) >= 3:
            records.append({
                "name": f"inferred_relative_{address:08x}",
                "address": f"0x{address:08x}",
                "size": len(entries) * 4,
                "relative_base": f"0x{address:08x}",
                "entries": [
                    {"index": index, **entry} for index, entry in enumerate(entries)
                ],
            })
            targets.update(int(entry["target"], 16) for entry in entries)
            address = cursor
        else:
            address += 4
    return records, targets


def discover(payload: bytes, seeds: set[int]) -> tuple[set[int], set[int]]:
    decoder = Cs(CS_ARCH_ARM, CS_MODE_ARM | CS_MODE_LITTLE_ENDIAN)
    decoder.detail = True
    pending, queued, code, targets = deque(sorted(seeds)), set(seeds), set(), set()
    while pending:
        address = pending.popleft()
        while inside(address) and address not in code:
            raw = payload[address - BASE:address - BASE + 4]
            decoded = list(decoder.disasm(raw, address, count=1))
            if len(decoded) != 1 or decoded[0].size != 4:
                break
            insn = decoded[0]
            code.add(address)
            mnemonic = insn.mnemonic
            # Private dispatchers synthesize LR immediately before an
            # indirect `add pc, ...`.  That address is a real continuation,
            # but no direct branch points at it, so seed it explicitly.
            continuation = None
            if (
                mnemonic in {"add", "sub"}
                and len(insn.operands) >= 3
                and insn.operands[0].type == ARM_OP_REG
                and insn.operands[0].reg == ARM_REG_LR
                and insn.operands[1].type == ARM_OP_REG
                and insn.operands[1].reg == ARM_REG_PC
                and insn.operands[2].type == ARM_OP_IMM
            ):
                delta = insn.operands[2].imm
                continuation = address + 8 + (delta if mnemonic == "add" else -delta)
            elif (
                mnemonic == "mov"
                and len(insn.operands) >= 2
                and insn.operands[0].type == ARM_OP_REG
                and insn.operands[0].reg == ARM_REG_LR
                and insn.operands[1].type == ARM_OP_REG
                and insn.operands[1].reg == ARM_REG_PC
            ):
                continuation = address + 8
            if continuation is not None and inside(continuation):
                targets.add(continuation)
                if continuation not in queued and continuation not in code:
                    queued.add(continuation)
                    pending.append(continuation)
            if mnemonic.startswith("b") and insn.operands:
                operand = insn.operands[-1]
                target = operand.imm & 0xFFFFFFFF if operand.type == ARM_OP_IMM else None
                if target is not None and inside(target):
                    targets.add(target)
                    if target not in queued and target not in code:
                        queued.add(target)
                        pending.append(target)
            call = mnemonic in {"bl", "blx"}
            branch = mnemonic == "b" or (
                mnemonic.startswith("b") and not call
                and mnemonic not in {"bic", "bfi", "bfc"}
            )
            conditional = insn.cc not in {ARM_CC_AL, ARM_CC_INVALID}
            writes_pc = ARM_REG_PC in insn.regs_write
            explicit_pc_destination = (
                bool(insn.operands)
                and insn.operands[0].type == ARM_OP_REG
                and insn.operands[0].reg == ARM_REG_PC
            )
            stack_return = mnemonic.startswith("pop") and "pc" in insn.op_str
            stack_return |= mnemonic.startswith("ldm") and "pc" in insn.op_str
            if (branch and not conditional) or mnemonic in {"bx", "bxj"}:
                break
            if stack_return:
                break
            # Direct conditional branches write PC but also have a fallthrough.
            # Only terminate here for computed PC writes such as ldr/add/mov pc.
            if (
                (writes_pc or explicit_pc_destination)
                and not call
                and not branch
                and not conditional
            ):
                break
            address += 4
    return code, targets


def make_ranges(addresses: set[int], classification: str) -> list[dict]:
    if not addresses:
        return []
    result = []
    start = previous = min(addresses)
    for address in sorted(addresses)[1:]:
        if address != previous + 4:
            result.append({
                "classification": classification, "start": f"0x{start:08x}",
                "end": f"0x{previous + 4:08x}", "size": previous + 4 - start,
            })
            start = address
        previous = address
    result.append({
        "classification": classification, "start": f"0x{start:08x}",
        "end": f"0x{previous + 4:08x}", "size": previous + 4 - start,
    })
    return result


def build_inventory(payload: bytes) -> dict:
    digest = hashlib.sha256(payload).hexdigest()
    if len(payload) != SIZE or digest != SHA256:
        raise ValueError(f"unexpected payload: size={len(payload):#x}, sha256={digest}")
    semantic_data = verify_semantic_data(payload)
    tables, table_targets = read_tables(payload)
    signed_tables, signed_targets = read_signed_tables(payload)
    table_targets |= signed_targets
    inferred, inferred_targets = infer_relative_tables(payload)
    known_table_addresses = {address for address, _, _, _ in TABLES}
    inferred = [
        table for table in inferred
        if int(table["address"], 16) not in known_table_addresses
    ]
    table_targets |= inferred_targets
    seeds = set(ENTRIES) | set(COMPUTED_SEEDS) | table_targets | {BASE}
    code, targets = discover(payload, seeds)
    data = set(range(BASE, BASE + SIZE, 4)) - code
    expected_data = {
        address
        for address in range(BASE, BASE + SIZE, 4)
        if any(address < end and address + 4 > start for start, end, _ in DATA_REGIONS)
    }
    if data != expected_data:
        missing = sorted(expected_data - data)
        unexpected = sorted(data - expected_data)
        raise ValueError(
            "code/data inventory drift: "
            f"missing={[hex(x) for x in missing[:8]]}, "
            f"unexpected={[hex(x) for x in unexpected[:8]]}"
        )
    return {
        "schema_version": 1,
        "payload_base": f"0x{BASE:08x}", "payload_size": SIZE,
        "payload_sha256": digest, "architecture": "ARMv5TE little-endian ARM mode",
        "method": "recursive traversal from validated entries and relative dispatch tables",
        "counts": {
            "validated_function_entries": len(ENTRIES), "unique_seed_entries": len(seeds),
            "direct_control_flow_targets": len(targets), "code_instructions": len(code),
            "code_bytes": len(code) * 4, "data_bytes": len(data) * 4,
            "semantic_data_bytes": sum(region["size"] for region in semantic_data),
            "control_metadata_bytes": (
                len(data) * 4 - sum(region["size"] for region in semantic_data)
            ),
            "classified_bytes": SIZE,
        },
        "validated_entries": [f"0x{x:08x}" for x in ENTRIES],
        "computed_continuations": [f"0x{x:08x}" for x in COMPUTED_SEEDS],
        "relative_tables": tables,
        "signed_relative_tables": signed_tables,
        "inferred_relative_tables": inferred,
        "embedded_data_regions": [
            {
                "name": name, "start": f"0x{start:08x}",
                "end": f"0x{end:08x}", "size": end - start,
            }
            for start, end, name in DATA_REGIONS
        ],
        "semantic_data_regions": semantic_data,
        "ranges": sorted(
            make_ranges(code, "arm_code")
            + make_ranges(data, "embedded_data"),
            key=lambda item: int(item["start"], 16),
        ),
    }


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--payload", type=Path, help="payload image (default: read from the extracted ov022)")
    parser.add_argument("--output", type=Path, default=region.WORK / "mobiclip_inventory.json")
    args = parser.parse_args()
    data = args.payload.read_bytes() if args.payload else region.ov022_bytes(*region.PAYLOAD)
    inventory = build_inventory(data)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(inventory, indent=2) + "\n", encoding="utf-8")
    counts = inventory["counts"]
    print(f"classified {SIZE:#x} bytes: {counts['code_bytes']:#x} ARM code, {counts['data_bytes']:#x} embedded data")
    print(f"validated entries: {counts['validated_function_entries']}")
    print(f"inventory: {args.output}")


if __name__ == "__main__":
    main()
