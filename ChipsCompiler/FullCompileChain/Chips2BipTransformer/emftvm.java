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
        System.err.println("usage: ./emftvm.sh <input metamodel> <output metamodel> <input model> <atl transformations> <output model>");
    }

    private static boolean parseArgs(String [] args){
        if(args.length != 5){
            System.err.println("error, wrong number of arguments...");
            System.err.println("expected 5, received "+args.length);
            return false;
        }

        if(!getFileExtension(args[0]).equals("ecore")){
            System.err.println("error, input metamodel must be a .ecore file...");
            return false;
        } else {
            chipsPath = args[0];
        }

        if(!getFileExtension(args[1]).equals("ecore")){
            System.err.println("error, output metamodel must be a .ecore file...");
            return false;
        } else {
            bipPath = args[1];
        }

        if(!getFileExtension(args[2]).equals("xmi")){
            System.err.println("error, input model must be a .xmi file...");
            return false;
        } else {
            inputModelPath = args[2];
        }

        if(!getFileExtension(args[3]).equals("atl")){
            System.err.println("error, transformation must be a .atl file...");
            return false;
        } else {
            moduleName = getFileName(args[3]);
            modulePath = getPath(args[3]) + "/";
        }

        if(!getFileExtension(args[4]).equals("xmi")){
            System.err.println("error, output model must be a .xmi file...");
            return false;
        } else {
            outputModelPath = args[4];
        }
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

    public static void main(String[] args) {

        boolean commandParseError = !parseArgs(args);
    
        if(commandParseError){
            usagePrint();
            return;
        }

        try {
            compile(
                modulePath+moduleName+".atl",
                modulePath+moduleName+".emftvm"
            );

            ResourceSet rs = new ResourceSetImpl();
            ExecEnv env = EmftvmFactory.eINSTANCE.createExecEnv();


            // Load metamodels
            Metamodel chipsMM = EmftvmFactory.eINSTANCE.createMetamodel();
            chipsMM.setResource(rs.getResource(URI.createURI(chipsPath), true));
            env.registerMetaModel("chips", chipsMM);
            Metamodel bipMM = EmftvmFactory.eINSTANCE.createMetamodel();
            bipMM.setResource(rs.getResource(URI.createURI(bipPath), true));
            env.registerMetaModel("bip", bipMM);

            rs.getResourceFactoryRegistry().getExtensionToFactoryMap().put("xmi", new XMIResourceFactoryImpl());
		    rs.getResourceFactoryRegistry().getExtensionToFactoryMap().put("emftvm", new EMFTVMResourceFactoryImpl());

            Model inModel = EmftvmFactory.eINSTANCE.createModel();
            inModel.setResource(rs.getResource(URI.createURI(inputModelPath,true), true));
            env.registerInputModel("IN", inModel);



            Model outModel = EmftvmFactory.eINSTANCE.createModel();
            outModel.setResource(rs.createResource(URI.createFileURI(outputModelPath)));
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
        }
    }
}

