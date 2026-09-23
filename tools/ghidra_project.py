"""Create/update a persistent, overlay-aware Ghidra project from verified local inputs."""
from __future__ import annotations
import argparse
import hashlib
import json
import os
import re
import subprocess
import urllib.request
import zipfile
from pathlib import Path
import khrecoded as kh

ROOT=Path(__file__).resolve().parents[1]
OUTPUT=ROOT/'build/ghidra'
CONFIG=ROOT/'config/bk9e/arm9'
FUNCTION=re.compile(r'^(\S+) kind:function\((arm|thumb),size=0x([0-9a-f]+)\) addr:0x([0-9a-f]+)',re.I)
SYMBOL=re.compile(r'^(\S+) kind:.* addr:0x([0-9a-f]+)',re.I)
RELOC=re.compile(r'^from:0x([0-9a-f]+) kind:(\S+) to:0x([0-9a-f]+) module:(\S+)',re.I)

def config():return json.loads((ROOT/'profiles/ghidra.json').read_text())

def installation():
    return Path(os.environ.get('GHIDRA_HOME',str(ROOT.parent/'decomp-tools'/config()['directory'])))

def install():
    settings=config(); folder=installation().parent;folder.mkdir(parents=True,exist_ok=True)
    archive=folder/settings['archive']
    if not archive.exists():urllib.request.urlretrieve(settings['url'],archive)
    if kh.sha256(archive)!=settings['sha256']:raise RuntimeError('Ghidra archive checksum mismatch')
    if not installation().exists():
        with zipfile.ZipFile(archive) as z:
            for name in z.namelist():
                if not (folder/name).resolve().is_relative_to(folder.resolve()):raise RuntimeError('Unsafe archive path')
            z.extractall(folder)
    print(installation())

def module_targets(value):
    if value=='main':return ['arm9']
    if value in ('itcm','dtcm'):return [value]
    if value=='none':return ['absolute']
    match=re.fullmatch(r'overlays?\(([0-9,]+)\)',value)
    if not match:raise RuntimeError('Unknown relocation module '+value)
    return [f'ov{int(i):03}' for i in match[1].split(',')]

def prepare():
    kh.validate_rom(kh.rom_path(None));inv=kh.inventory()
    matches={(m['module'],m['symbol']):m for m in json.loads((ROOT/'matches.json').read_text())['matches']}
    modules=[]
    for name,data in inv.items():
        folder=CONFIG if name=='arm9' else CONFIG/name if name in ('itcm','dtcm') else CONFIG/'overlays'/name
        row={'name':name,'binary':str(data['binary']),'base':data['base'],'size':data['binary_bytes'],
             'sha256':kh.sha256(data['binary']),'functions':[],'symbols':[],'references':[],'bss':[]}
        if name!='arm7':
            for line in (folder/'symbols.txt').read_text().splitlines():
                symbol=SYMBOL.match(line)
                if not symbol:continue
                function=FUNCTION.match(line)
                if function and int(function[3],16):
                    original=function[1]; known=matches.get((name,original))
                    row['functions'].append({'name':known['source_symbol'] if known else original,
                        'original':original,'address':int(function[4],16),'size':int(function[3],16),'mode':function[2],
                        'comment':(known['behavior']+'\nEvidence: '+known['evidence']+'\nUncertainty: '+known['uncertainty']) if known else ''})
                else:row['symbols'].append({'name':symbol[1],'address':int(symbol[2],16)})
            for line in (folder/'relocs.txt').read_text().splitlines():
                m=RELOC.match(line)
                if m:row['references'].append({'from':int(m[1],16),'kind':m[2],'to':int(m[3],16),'modules':module_targets(m[4])})
            for start,end in re.findall(r'start:0x([0-9a-f]+) end:0x([0-9a-f]+) kind:bss',(folder/'delinks.txt').read_text()):
                if int(end,16)>int(start,16):row['bss'].append({'start':int(start,16),'size':int(end,16)-int(start,16)})
        modules.append(row)
    OUTPUT.mkdir(parents=True,exist_ok=True)
    payload={'rom_sha256':kh.profile()['rom_sha256'],'modules':modules}
    (OUTPUT/'import.json').write_text(json.dumps(payload,indent=2))
    print(f"Prepared {len(modules)} modules, {sum(len(m['functions']) for m in modules)} functions; ambiguous overlay targets remain explicit.")
    return payload

def run(mode):
    prepare();settings=config();ghidra=installation()
    executable=ghidra/'support'/('analyzeHeadless.bat' if os.name=='nt' else 'analyzeHeadless')
    if not executable.exists():raise RuntimeError('Run python tools/ghidra_project.py install first')
    project=OUTPUT/'project';project.mkdir(exist_ok=True)
    for processor in ('arm9','arm7'):
        exists=(project/'BK9E.gpr').exists()
        base=[str(executable),str(project),'BK9E']
        if mode=='create':
            if (OUTPUT/f'{processor}-import-report.json').exists():
                print(processor+' is already imported; use update to apply new knowledge');continue
            data=next(m for m in json.loads((OUTPUT/'import.json').read_text())['modules'] if m['name']==processor)
            base+=['-import',data['binary'],'-processor',settings[processor+'_language'],
                   '-loader','BinaryLoader','-loader-baseAddr',hex(data['base'])]
        else:
            if not exists:raise RuntimeError('Project does not exist; run create first')
            base+=['-process',processor+'.bin']
        base+=['-scriptPath',str(ROOT/'tools/ghidra'),'-noanalysis',
               '-preScript','ImportBK9E.java',str(ROOT),processor,mode,
               '-postScript','ExportBK9E.java',str(ROOT),processor,
               '-log',str(OUTPUT/(processor+'-headless.log')),
               '-scriptlog',str(OUTPUT/(processor+'-scripts.log'))]
        report=OUTPUT/(processor+'-import-report.json')
        previous_report_time=report.stat().st_mtime_ns if report.exists() else None
        export=OUTPUT/'actor-model-export.json'
        previous_export_time=export.stat().st_mtime_ns if export.exists() else None
        result=subprocess.run(base,cwd=ROOT)
        if result.returncode:raise RuntimeError('Ghidra process failed')
        if not report.exists() or report.stat().st_mtime_ns==previous_report_time:
            raise RuntimeError('Ghidra did not produce a fresh import report; inspect its log')
        if processor=='arm9':
            if not export.exists() or export.stat().st_mtime_ns==previous_export_time:
                raise RuntimeError('Ghidra did not produce a fresh typed decompiler export')
            if not all(record['decompiled'] for record in json.loads(export.read_text())):
                raise RuntimeError('A typed gameplay function could not be decompiled; inspect the export')
    print('Persistent project: '+str(project/'BK9E.gpr'))

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command',choices=['install','prepare','create','update'])
    command=parser.parse_args().command
    if command=='install':install()
    elif command=='prepare':prepare()
    else:run(command)
