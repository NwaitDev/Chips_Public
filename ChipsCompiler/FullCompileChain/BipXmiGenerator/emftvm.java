import java.io.File;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.resource.Resource;

import java.util.Collections;
import java.io.FileInputStream;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.eclipse.m2m.atl.emftvm.*;
import org.eclipse.m2m.atl.emftvm.compiler.*;
import org.eclipse.m2m.atl.emftvm.impl.resource.EMFTVMResourceFactoryImpl;
import org.eclipse.m2m.atl.emftvm.util.*;
import org.eclipse.m2m.atl.core.emf.*;
import org.eclipse.m2m.atl.core.*;
import org.eclipse.m2m.atl.engine.compiler.CompileTimeError;
import org.eclipse.emf.common.notify.impl.*;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.impl.*;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.xmi.impl.*;
import org.objectweb.asm.*;




public class emftvm {


    static String chipsPath;
    static String bipPath;
    static String inputModelPath;
    static String outputModelPath;
    static String modulePath;
    static String moduleName;
    static boolean recompile = false;
    static boolean compileOnly = false;

    private static URI fileUri(String path) {
        return URI.createFileURI(new File(path).getAbsolutePath());
    }

    private static void registerPackage(ResourceSet rs, EPackage pkg) {
        rs.getPackageRegistry().put(pkg.getNsURI(), pkg);
        for (EPackage sub : pkg.getESubpackages()) {
            registerPackage(rs, sub);
        }
    }

    private static Resource loadMetamodel(ResourceSet rs, String path) {
        Resource resource = rs.getResource(fileUri(path), true);
        for (EObject root : resource.getContents()) {
            if (root instanceof EPackage) {
                registerPackage(rs, (EPackage) root);
            }
        }
        return resource;
    }

    private static String getFileExtension(String fileName){

        int dotIndex = fileName.lastIndexOf('.');
        return (dotIndex == -1) ? "No extension" : fileName.substring(dotIndex + 1);
    }

    private static String removeFileExtension(String filename, boolean removeAllExtensions) {
        if (filename == null || filename.isEmpty()) {
            return filename;
        }

        String extPattern = "(?<!^)[.]" + (removeAllExtensions ? ".*" : "[^.]*$");
        return filename.replaceAll(extPattern, "");
    }
    
    private static String getFileName(String fileName) {
        return removeFileExtension(Paths.get(fileName).getFileName().toString(),true);
    }

    private static String getPath(String filename){
        return Paths.get(filename).getParent().toString();
    }

    private static void usagePrint(){
        System.err.println("usage: ./emftvm.sh [-r] <input metamodel> <output metamodel> <input model> <atl transformations> <output model>");
        System.err.println("       ./emftvm.sh -c <atl transformations>");
        System.err.println();
        System.err.println("  -r  recompile the atl transformations before running them");
        System.err.println("  -c  only compile the atl transformations into their .emftvm file");
    }

    private static boolean setModule(String atlFile){
        if(!getFileExtension(atlFile).equals("atl")){
            System.err.println("error, transformation must be a .atl file...");
            return false;
        }
        moduleName = getFileName(atlFile);
        Path parent = Paths.get(atlFile).toAbsolutePath().getParent();
        modulePath = parent.toString() + "/";
        return true;
    }

    private static boolean parseArgs(String [] args){
        java.util.List<String> positional = new java.util.ArrayList<>();
        for(String arg : args){
            if(arg.equals("-r")){
                recompile = true;
            } else if(arg.equals("-c")){
                compileOnly = true;
            } else if(arg.startsWith("-")){
                System.err.println("error, unknown option "+arg+"...");
                return false;
            } else {
                positional.add(arg);
            }
        }

        if(compileOnly){
            if(recompile){
                System.err.println("error, -c and -r cannot be used together...");
                return false;
            }
            if(positional.size() != 1){
                System.err.println("error, -c expects exactly one .atl file, received "+positional.size()+" argument(s)...");
                return false;
            }
            return setModule(positional.get(0));
        }

        if(positional.size() != 5){
            System.err.println("error, wrong number of arguments...");
            return false;
        }

        if(!getFileExtension(positional.get(0)).equals("ecore")){
            System.err.println("error, input metamodel must be a .ecore file...");
            return false;
        }
        chipsPath = positional.get(0);

        if(!getFileExtension(positional.get(1)).equals("ecore")){
            System.err.println("error, output metamodel must be a .ecore file...");
            return false;
        }
        bipPath = positional.get(1);

        if(!getFileExtension(positional.get(2)).equals("xmi")){
            System.err.println("error, input model must be a .xmi file...");
            return false;
        }
        inputModelPath = positional.get(2);

        if(!setModule(positional.get(3))){
            return false;
        }

        if(!getFileExtension(positional.get(4)).equals("xmi")){
            System.err.println("error, output model must be a .xmi file...");
            return false;
        }
        outputModelPath = positional.get(4);
        return true;
    }


    public static void compile(String atlPath, String emftvmPath) throws Exception {

        AtlToEmftvmCompiler compiler = new AtlToEmftvmCompiler();

        FileInputStream in = new FileInputStream(atlPath);
        String out = emftvmPath;

        CompileTimeError[] errors = compiler.compile(in, out);

        in.close();

        if(errors.length ==0 ){
            System.out.println(atlPath+" compiled succesfully as "+emftvmPath);
        } else {
            for ( CompileTimeError e : errors){
                System.err.println("["+e.getSeverity()+" at "+e.getLocation()+"] "+e.getDescription());
            }
            throw new Exception("Errors happened during compilation of "+atlPath);
        }
    }

    public static void main(String[] args) throws Exception{

        if(!parseArgs(args)){
            usagePrint();
            System.exit(1);
        }

        String atlFile = modulePath+moduleName+".atl";
        String emftvmFile = modulePath+moduleName+".emftvm";

        try {
            if(compileOnly){
                compile(atlFile, emftvmFile);
                return;
            }

            if(recompile){
                compile(atlFile, emftvmFile);
            } else if(!new File(emftvmFile).exists()){
                System.err.println("error, "+emftvmFile+" does not exist, run again with -r to compile "+atlFile+"...");
                System.exit(1);
            } else if(new File(atlFile).lastModified() > new File(emftvmFile).lastModified()){
                System.err.println("warning, "+atlFile+" is newer than "+emftvmFile+", use -r to recompile it");
            }

            ResourceSet rs = new ResourceSetImpl();
            rs.getResourceFactoryRegistry().getExtensionToFactoryMap().put("ecore", new EcoreResourceFactoryImpl());
            rs.getResourceFactoryRegistry().getExtensionToFactoryMap().put("xmi", new XMIResourceFactoryImpl());
            rs.getResourceFactoryRegistry().getExtensionToFactoryMap().put("emftvm", new EMFTVMResourceFactoryImpl());
            ExecEnv env = EmftvmFactory.eINSTANCE.createExecEnv();

            Metamodel chipsMM = EmftvmFactory.eINSTANCE.createMetamodel();
            chipsMM.setResource(loadMetamodel(rs, chipsPath));
            env.registerMetaModel("chips", chipsMM);

            Metamodel bipMM = EmftvmFactory.eINSTANCE.createMetamodel();
            bipMM.setResource(loadMetamodel(rs, bipPath));
            env.registerMetaModel("bip", bipMM);

            Model inModel = EmftvmFactory.eINSTANCE.createModel();
            inModel.setResource(rs.getResource(fileUri(inputModelPath), true));
            env.registerInputModel("IN", inModel);

            Model outModel = EmftvmFactory.eINSTANCE.createModel();
            outModel.setResource(rs.createResource(fileUri(outputModelPath)));
            env.registerOutputModel("OUT", outModel);

            ModuleResolver mr = new DefaultModuleResolver(modulePath, rs);
            TimingData td = new TimingData();
            env.loadModule(mr, moduleName);
            td.finishLoading();
            env.run(td);
            td.finish();

            outModel.getResource().save(Collections.emptyMap());

            System.out.println("Transformation finished successfully.");

        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}