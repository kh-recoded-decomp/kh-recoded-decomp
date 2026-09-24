"""Exclusive, byte-conserving system / module / subsection / function progress."""

from __future__ import annotations

import re


def merged_ranges(ranges):
    result = []
    for start, stop in sorted(ranges):
        if stop <= start:
            raise RuntimeError("Invalid analysed code range")
        if result and start <= result[-1][1]:
            result[-1] = (result[-1][0], max(stop, result[-1][1]))
        else:
            result.append((start, stop))
    return result


def stats(code_bytes, matched_bytes, functions, matched_functions, unknown_modules=0):
    if code_bytes is not None and not 0 <= matched_bytes <= code_bytes:
        raise RuntimeError("Matching bytes exceed subsection denominator")
    return {"code_bytes": code_bytes, "matched_c_bytes": matched_bytes,
            "identified_functions": functions, "matched_c_functions": matched_functions,
            "unknown_code_modules": unknown_modules,
            "percent": 100 * matched_bytes / code_bytes if code_bytes else None,
            "complete": bool(code_bytes) and matched_bytes == code_bytes and not unknown_modules}


def rollup(children):
    known = [c["code_bytes"] for c in children if c["code_bytes"] is not None]
    return stats(sum(known) if known else None,
                 sum(c["matched_c_bytes"] for c in children),
                 sum(c["identified_functions"] for c in children),
                 sum(c["matched_c_functions"] for c in children),
                 sum(c["unknown_code_modules"] for c in children))


def named_record(record, scope):
    if not re.fullmatch(r"[a-z][a-z0-9_]*", record.get("id", "")):
        raise RuntimeError(f"Invalid organization ID in {scope}")
    for key in ("name", "evidence"):
        if not isinstance(record.get(key), str) or not record[key].strip():
            raise RuntimeError(f"Missing {key} in {scope}")
    result = {key: record[key] for key in ("id", "name", "evidence")}
    if record.get("uncertainty"):
        result["uncertainty"] = record["uncertainty"]
    return result


def build_hierarchy(inv, verified, catalog):
    """Only fresh verify_matches output may supply the matched numerator.

    Semantic ownership lives in the catalog; omitted functions and every code
    gap belong to unclassified. Inventory addresses and sizes are authoritative.
    No denominator or completion flag from the catalog is consumed.
    """
    if catalog.get("version") != 1 or not isinstance(catalog.get("systems"), list):
        raise RuntimeError("Invalid organization catalog schema")
    matches = {}
    for match in verified:
        key = (match["module"], match["symbol"])
        function = inv.get(key[0], {}).get("symbols", {}).get(key[1])
        if key in matches or function is None or match["bytes"] != function["size"]:
            raise RuntimeError(f"Duplicate, unknown or wrong-sized verified function: {key}")
        if match["language"] not in ("c", "cpp"):
            raise RuntimeError(f"Not a verified C/C++ function: {key}")
        matches[key] = match
    systems, seen_systems, seen_modules = [], set(), set()
    for system_spec in catalog["systems"]:
        system = named_record(system_spec, "system")
        if system["id"] in seen_systems:
            raise RuntimeError(f"Duplicate system: {system['id']}")
        seen_systems.add(system["id"])
        system["modules"] = []
        for module_spec in system_spec["modules"]:
            name = module_spec["module"]
            if name in seen_modules or name not in inv:
                raise RuntimeError(f"Duplicate or unknown module: {name}")
            seen_modules.add(name)
            data = inv[name]
            sections, owners = {}, {}
            for section_spec in module_spec["subsections"]:
                section = named_record(section_spec, name)
                sid = section["id"]
                if sid in sections or sid == "unclassified":
                    raise RuntimeError(f"Duplicate or reserved subsection: {name}/{sid}")
                section["functions"] = []
                sections[sid] = section
                for symbol in section_spec["symbols"]:
                    if symbol in owners or symbol not in data["symbols"]:
                        raise RuntimeError(f"Duplicate or unknown ownership: {name}/{symbol}")
                    owners[symbol] = sid
            sections["unclassified"] = {
                "id": "unclassified", "name": "Unclassified code",
                "evidence": "Functions without reviewed ownership and code outside identified function spans.",
                "functions": []}
            ranges = merged_ranges(data["code_ranges"])
            code_bytes = data["code_bytes"]
            if code_bytes is None:
                if ranges or data["symbols"]:
                    raise RuntimeError(f"Unknown denominator has code inventory: {name}")
            elif sum(b - a for a, b in ranges) != code_bytes:
                raise RuntimeError(f"Code denominator differs from ranges: {name}")
            previous_end = None
            spans = []
            for symbol, f in sorted(data["symbols"].items(), key=lambda item: item[1]["address"]):
                start, stop = f["address"], f["address"] + f["size"]
                if stop <= start or (previous_end is not None and start < previous_end):
                    raise RuntimeError(f"Invalid or overlapping function inventory: {name}/{symbol}")
                if not any(a <= start and stop <= b for a, b in ranges):
                    raise RuntimeError(f"Function outside analysed code: {name}/{symbol}")
                previous_end = stop
                spans.append((start, stop))
                match = matches.get((name, symbol))
                section = sections[owners.get(symbol, "unclassified")]
                row = {"symbol": symbol, "address": f"0x{start:08x}", "bytes": f["size"],
                       "matched": match is not None, "name": match["name"] if match else symbol}
                if match:
                    row["source"] = match["source"]
                section["functions"].append(row)
            gaps = []
            span_index = 0
            for start, stop in ranges:
                cursor = start
                while span_index < len(spans) and spans[span_index][0] < stop:
                    a, b = spans[span_index]
                    if cursor < a:
                        gaps.append((cursor, a))
                    cursor = b
                    span_index += 1
                if cursor < stop:
                    gaps.append((cursor, stop))
            gap_bytes = sum(b - a for a, b in gaps)
            for sid, section in sections.items():
                functions = section["functions"]
                unassigned = gap_bytes if sid == "unclassified" else 0
                denominator = (sum(f["bytes"] for f in functions) + unassigned
                               if code_bytes is not None else None)
                section.update(stats(denominator, sum(f["bytes"] for f in functions if f["matched"]),
                                     len(functions), sum(f["matched"] for f in functions)))
                section["unattributed_code_bytes"] = unassigned
                if sid == "unclassified":
                    section["unattributed_code_ranges"] = [
                        {"start": f"0x{a:08x}", "end": f"0x{b:08x}"} for a, b in gaps]
            module = {"module": name, "subsections": list(sections.values()),
                      **rollup(list(sections.values()))}
            module["unknown_code_modules"] = int(code_bytes is None)
            if module["code_bytes"] != code_bytes:
                raise RuntimeError(f"Organization lost code bytes: {name}")
            system["modules"].append(module)
        if not system["modules"]:
            raise RuntimeError(f"System has no modules: {system['id']}")
        system.update(rollup(system["modules"]))
        systems.append(system)
    if seen_modules != set(inv):
        raise RuntimeError(f"Modules missing from organization: {sorted(set(inv) - seen_modules)}")
    return {"version": 1, "systems": systems, **rollup(systems)}


def coverage(row):
    denominator = f"{row['code_bytes']:,}" if row["code_bytes"] is not None else "unknown"
    percentage = f"{row['percent']:.3f}%" if row["percent"] is not None else "n/a"
    unknown = row["unknown_code_modules"]
    suffix = f"; {unknown} module(s) with unknown code size" if unknown else ""
    return f"{row['matched_c_bytes']:,} / {denominator} bytes ({percentage}){suffix}"


def markdown(hierarchy):
    lines = ["## System → overlay → subsection → function", "",
             "Ownership is defined in `config/bk9e/organization.json`. Every identified function has one "
             "owning subsection. Unclassified code also retains all gaps outside identified functions. "
             "Percentages are byte-weighted; subsection totals add up to the overlay, system, and overall totals.", "",
             "100% means all bytes currently assigned to that subsection have verified C/C++ matches. "
             "Groupings can expand as Ghidra callers and shared structures establish more relationships. "
             "Empty groups are not complete. ARM7 has an unknown denominator and is excluded from the "
             "analysed ARM9 percentage.", "",
             "Browse every function (including unmatched functions) with "
             "`python tools/khrecoded.py progress --module ov001 --subsection actor_animation --functions`. "
             "The full hierarchy and all function owners are in `build/progress.json`.", ""]
    for system in hierarchy["systems"]:
        lines += [f"### {system['name']}", "", f"{coverage(system)}. System ID: `{system['id']}`.", "",
                  "| Overlay / module | Verified C/C++ | Matched / identified functions |",
                  "|---|---:|---:|"]
        for module in system["modules"]:
            lines.append(f"| {module['module']} | {coverage(module)} | "
                         f"{module['matched_c_functions']} / {module['identified_functions']} |")
        lines.append("")
        for module in system["modules"]:
            # Fully unclassified modules already appear in the system table.
            if len(module["subsections"]) == 1:
                continue
            lines += [f"<details><summary>{module['module']} subsections</summary>", "",
                      "| Subsection | Verified C/C++ | Functions | Status |",
                      "|---|---:|---:|---|"]
            for section in module["subsections"]:
                state = "Complete" if section["complete"] else (
                    "No assigned code" if section["code_bytes"] == 0 else "Incomplete")
                lines.append(f"| {section['name']} (`{section['id']}`) | {coverage(section)} | "
                             f"{section['matched_c_functions']} / {section['identified_functions']} | {state} |")
            lines += ["", "</details>", ""]
    return lines


def print_tree(hierarchy, system_id=None, module_id=None, subsection_id=None, functions=False):
    found = False
    for system in hierarchy["systems"]:
        if system_id and system["id"] != system_id:
            continue
        modules = [m for m in system["modules"] if not module_id or m["module"] == module_id]
        if not modules:
            continue
        print(f"{system['name']} [{system['id']}]: {coverage(system)}")
        for module in modules:
            sections = [s for s in module["subsections"] if not subsection_id or s["id"] == subsection_id]
            if not sections:
                continue
            print(f"  {module['module']}: {coverage(module)}")
            for section in sections:
                found = True
                state = "complete" if section["complete"] else "incomplete"
                print(f"    {section['name']} [{section['id']}]: {coverage(section)}; {state}")
                if functions:
                    for f in section["functions"]:
                        status = "MATCH" if f["matched"] else "pending"
                        print(f"      {status:7} {f['symbol']} {f['bytes']:5} B  {f['name']}")
                    if section["unattributed_code_bytes"]:
                        print(f"      pending {section['unattributed_code_bytes']} B outside identified functions")
    if not found:
        raise RuntimeError("No organization entries match the requested filters")
