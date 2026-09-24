// Import function boundaries, modes, module-qualified references and reviewed types.
// @category KHRecoded
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.util.cparser.C.CParser;
import ghidra.program.model.address.*;
import ghidra.program.model.data.*;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import com.google.gson.*;
import java.io.*;
import java.nio.file.*;
import java.math.BigInteger;
import java.util.*;

public class ImportBK9E extends GhidraScript {
    private final Map<String,AddressSpace> spaces=new HashMap<>();
    private final Map<String,Namespace> namespaces=new HashMap<>();
    private final Set<String> functionEntries=new HashSet<>();
    private final List<String> warnings=new ArrayList<>();
    private int importedFunctions=0, importedReferences=0, ambiguousReferences=0;
    private Path root;
    private Address address(String module,long offset) {return spaces.get(module).getAddress(offset);}
    private String clean(String name) {return name.replaceAll("[^A-Za-z0-9_$]","_");}

    @Override public void run() throws Exception {
        String[] args=getScriptArgs();root=Paths.get(args[0]);String cpu=args[1];boolean create=args[2].equals("create");
        JsonObject manifest=JsonParser.parseString(Files.readString(root.resolve("build/ghidra/import.json"))).getAsJsonObject();
        AddressSpace ram=currentProgram.getAddressFactory().getDefaultAddressSpace();
        spaces.put("absolute",ram);Memory memory=currentProgram.getMemory();
        List<JsonObject> modules=new ArrayList<>();
        for(JsonElement item:manifest.getAsJsonArray("modules")) {
            JsonObject module=item.getAsJsonObject();String name=module.get("name").getAsString();
            if(cpu.equals("arm7")!=name.equals("arm7"))continue;
            modules.add(module);long base=module.get("base").getAsLong();
            if(name.equals(cpu)) {
                spaces.put(name,ram);
                if(create)memory.getBlock(ram.getAddress(base)).setName(name);
            } else if(create) {
                try(InputStream stream=Files.newInputStream(Paths.get(module.get("binary").getAsString()))) {
                    MemoryBlock block=memory.createInitializedBlock(name,ram.getAddress(base),stream,module.get("size").getAsLong(),monitor,name.startsWith("ov"));
                    block.setRead(true);block.setWrite(true);block.setExecute(!name.equals("dtcm"));
                    spaces.put(name,block.getStart().getAddressSpace());
                }
            } else {
                MemoryBlock block=memory.getBlock(name);
                if(block==null)throw new IOException("Missing module block "+name);
                spaces.put(name,block.getStart().getAddressSpace());
            }
            if(create)for(JsonElement b:module.getAsJsonArray("bss")) {
                JsonObject bss=b.getAsJsonObject();Address start=address(name,bss.get("start").getAsLong());
                if(memory.getBlock(start)==null) {
                    MemoryBlock block=memory.createUninitializedBlock(name+"_bss",start,bss.get("size").getAsLong(),false);
                    block.setRead(true);block.setWrite(true);block.setExecute(false);
                }
            }
            Namespace namespace=currentProgram.getSymbolTable().getNamespace(name,currentProgram.getGlobalNamespace());
            if(namespace==null)namespace=currentProgram.getSymbolTable().createNameSpace(currentProgram.getGlobalNamespace(),name,SourceType.USER_DEFINED);
            namespaces.put(name,namespace);
            for(JsonElement f:module.getAsJsonArray("functions"))functionEntries.add(name+":"+f.getAsJsonObject().get("address").getAsLong());
        }
        Register thumb=currentProgram.getProgramContext().getRegister("TMode");
        if(create)for(JsonObject module:modules) {
            String name=module.get("name").getAsString();
            for(JsonElement item:module.getAsJsonArray("functions")) {
                JsonObject f=item.getAsJsonObject();Address start=address(name,f.get("address").getAsLong());Address end=start.add(f.get("size").getAsLong()-1);
                currentProgram.getProgramContext().setValue(thumb,start,end,f.get("mode").getAsString().equals("thumb")?BigInteger.ONE:BigInteger.ZERO);
            }
        }
        for(JsonObject module:modules) {
            String name=module.get("name").getAsString();println("Importing "+name);
            for(JsonElement item:module.getAsJsonArray("functions")) {
                monitor.checkCancelled();JsonObject f=item.getAsJsonObject();Address start=address(name,f.get("address").getAsLong());Address end=start.add(f.get("size").getAsLong()-1);
                if(create)new DisassembleCommand(start,new AddressSet(start,end),false).applyTo(currentProgram,monitor);
                Function function=getFunctionAt(start);
                try {
                    if(function==null)function=currentProgram.getFunctionManager().createFunction(clean(f.get("name").getAsString()),namespaces.get(name),start,new AddressSet(start,end),SourceType.USER_DEFINED);
                    else if(create || function.getName().equals(f.get("original").getAsString())) {function.setName(clean(f.get("name").getAsString()),SourceType.USER_DEFINED);function.setParentNamespace(namespaces.get(name));}
                    if(create)function.setComment("DSD boundary: "+f.get("size").getAsInt()+" bytes, "+f.get("mode").getAsString()+".\n"+f.get("comment").getAsString());
                    importedFunctions++;
                } catch(Exception exception) {warnings.add(name+":"+start+" function: "+exception.getMessage());}
            }
            for(JsonElement item:module.getAsJsonArray("symbols")) {
                JsonObject symbol=item.getAsJsonObject();Address at=address(name,symbol.get("address").getAsLong());
                if(getFunctionAt(at)==null)try {currentProgram.getSymbolTable().createLabel(at,clean(symbol.get("name").getAsString()),namespaces.get(name),SourceType.USER_DEFINED);}catch(Exception exception){warnings.add(name+":"+at+" label: "+exception.getMessage());}
            }
        }
        for(JsonObject module:modules) {
            String name=module.get("name").getAsString();
            for(JsonElement item:module.getAsJsonArray("references")) {
                JsonObject relocation=item.getAsJsonObject();Address from=address(name,relocation.get("from").getAsLong());JsonArray targets=relocation.getAsJsonArray("modules");
                if(targets.size()!=1) {
                    ambiguousReferences++;
                    currentProgram.getBookmarkManager().setBookmark(from,"Note","Ambiguous overlay target","DSD candidates "+targets+" at "+Long.toHexString(relocation.get("to").getAsLong())+"; runtime overlay state must resolve this.");
                    continue;
                }
                String target=targets.get(0).getAsString();if(!spaces.containsKey(target))continue;
                long destination=relocation.get("to").getAsLong();
                if(functionEntries.contains(target+":"+(destination&~1L)))destination&=~1L;
                Address to=address(target,destination);String kind=relocation.get("kind").getAsString();
                if(kind.equals("load") && getFunctionContaining(from)!=null) {
                    // DSD load relocations identify address words, including literal pools.
                    // Do not leave a literal misclassified as an ARM instruction.
                    currentProgram.getListing().clearCodeUnits(from,from.add(3),false);
                    Data literal=createData(from,new Pointer32DataType());
                    MutabilitySettingsDefinition.DEF.setChoice(literal,MutabilitySettingsDefinition.CONSTANT);
                }
                RefType type=kind.contains("call")?RefType.UNCONDITIONAL_CALL:kind.equals("arm_branch")?RefType.UNCONDITIONAL_JUMP:RefType.DATA;
                ReferenceManager manager=currentProgram.getReferenceManager();
                for(Reference old:manager.getReferencesFrom(from))if(old.isMemoryReference() && old.getOperandIndex()==0)manager.delete(old);
                Reference reference=manager.addMemoryReference(from,to,type,SourceType.USER_DEFINED,0);manager.setPrimary(reference,true);importedReferences++;
            }
        }
        if(cpu.equals("arm9"))applyKnowledge();
        JsonObject report=new JsonObject();report.addProperty("program",currentProgram.getName());report.addProperty("modules",modules.size());
        report.addProperty("functions",importedFunctions);report.addProperty("references",importedReferences);report.addProperty("ambiguous_overlay_references",ambiguousReferences);
        report.add("warnings",new Gson().toJsonTree(warnings));
        Files.writeString(root.resolve("build/ghidra/"+cpu+"-import-report.json"),new GsonBuilder().setPrettyPrinting().create().toJson(report));
        println("Imported "+importedFunctions+" functions and "+importedReferences+" references; "+ambiguousReferences+" overlay ambiguities explicitly bookmarked; "+warnings.size()+" warnings.");
    }

    private void applyKnowledge() throws Exception {
        for(String relative:new String[]{"analysis/actor_model.json","analysis/overlay_loading.json","analysis/movie_playback.json"}) {
            Path knowledgePath=root.resolve(relative);if(!Files.exists(knowledgePath))continue;
            JsonObject knowledge=JsonParser.parseString(Files.readString(knowledgePath)).getAsJsonObject();
            CParser parser=new CParser(currentProgram.getDataTypeManager(),true,null);
            parser.parse(Files.readString(root.resolve(knowledge.get("types").getAsString())));
            for(JsonElement item:knowledge.getAsJsonArray("functions")) {
                JsonObject spec=item.getAsJsonObject();String module=spec.get("module").getAsString();
                Address at=address(module,Long.decode(spec.get("address").getAsString()));Function function=getFunctionAt(at);
                if(function==null)throw new IOException("No imported function for "+relative+" entry "+at);
                DataType parsed=parser.parse(spec.get("prototype").getAsString());
                if(!(parsed instanceof FunctionDefinition))throw new IOException("Expected function signature for "+at);
                ApplyFunctionSignatureCmd command=new ApplyFunctionSignatureCmd(at,(FunctionDefinition)parsed,SourceType.USER_DEFINED,true,true);
                if(!command.applyTo(currentProgram,monitor))throw new IOException(command.getStatusMsg());
                function.setCallingConvention(currentProgram.getCompilerSpec().getDefaultCallingConvention().getName());
                function.setParentNamespace(namespaces.get(module));
                function.setComment(spec.get("behavior").getAsString()+"\nEvidence: "+spec.get("evidence").getAsString()+"\nUncertainty: "+spec.get("uncertainty").getAsString());
            }
            for(JsonElement item:knowledge.getAsJsonArray("globals")) {
                JsonObject spec=item.getAsJsonObject();Address at=address(spec.get("module").getAsString(),Long.decode(spec.get("address").getAsString()));
                DataType type=currentProgram.getDataTypeManager().getDataType("/"+spec.get("pointee_type").getAsString());
                if(type==null)throw new IOException("Missing global pointee type "+spec);
                for(int depth=0;depth<spec.get("pointer_depth").getAsInt();depth++)type=new PointerDataType(type,4);
                clearListing(at,at.add(Math.max(1,type.getLength())-1));createData(at,type);
                Symbol symbol=currentProgram.getSymbolTable().getPrimarySymbol(at);
                if(symbol==null)symbol=currentProgram.getSymbolTable().createLabel(at,spec.get("name").getAsString(),namespaces.get(spec.get("module").getAsString()),SourceType.USER_DEFINED);
                else symbol.setName(spec.get("name").getAsString(),SourceType.USER_DEFINED);
                symbol.setPrimary();setEOLComment(at,spec.get("evidence").getAsString());
            }
        }
    }
}
