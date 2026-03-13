import java.util.Collections;
import java.io.FileInputStream;

import org.eclipse.m2m.atl.emftvm.compiler.*;
import org.eclipse.m2m.atl.emftvm.impl.resource.EMFTVMResourceFactoryImpl;
import org.eclipse.m2m.atl.emftvm.util.*;
import org.eclipse.m2m.atl.core.emf.*;
import org.eclipse.m2m.atl.core.*;
import org.eclipse.emf.common.notify.impl.*;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.impl.*;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.xmi.impl.*;

import org.eclipse.m2m.atl.emftvm.*;


public class EMFTVMLauncher {

    public static void compile(String atlPath, String emftvmPath) throws Exception {

        AtlToEmftvmCompiler compiler = new AtlToEmftvmCompiler();

        FileInputStream in = new FileInputStream(atlPath);
        String out = emftvmPath;

        compiler.compile(in, out);

        in.close();

        System.out.println("ATL compiled to EMFTVM successfully.");
    }

    public static void main(String[] args) {

        try {

            String chipsPath = "metamodels/chips1.1.ecore";
            String bipPath = "metamodels/BIP.ecore";
            String inputModelPath = "models/TeaStoreVariation.xmi";
            String outputModelPath = "models/output.xmi";
            String modulePath = "transformations"; // folder containing .emftvm and its atl file
            String moduleName = "chips2bip";

            compile(
                modulePath+"/"+moduleName+".atl",
                modulePath+"/"+moduleName+".emftvm"
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



            Model inModel = EmftvmFactory.eINSTANCE.createModel();
            inModel.setResource(rs.getResource(URI.createURI(inputModelPath), true));
            env.registerInputModel("IN", inModel);



            Model outModel = EmftvmFactory.eINSTANCE.createModel();
            outModel.setResource(rs.createResource(URI.createFileURI(outputModelPath)));
            env.registerOutputModel("OUT", outModel);

            // Load and run module
            ModuleResolver mr = new DefaultModuleResolver("transformations/", new ResourceSetImpl());
            TimingData td = new TimingData();
            env.loadModule(mr, "chips2bip");
            td.finishLoading();
            env.run(td);
            td.finish();

            // Save model
            outModel.getResource().save(Collections.emptyMap());

            System.out.println("Transformation finished successfully.");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}