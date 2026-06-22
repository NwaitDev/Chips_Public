/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 * 
 * This software is a computer program whose purpose is to generate
 * executable code from BIP models.
 * 
 * This software is governed by the CeCILL-B license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-B
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security.
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-B license and that you accept its terms.
 */

package ujf.verimag.bip.backend.cpp;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Stack;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.logging.Level;
import java.util.logging.Logger;
import joptsimple.OptionSet;
import joptsimple.OptionSpec;
import org.eclipse.emf.common.util.BasicMonitor;
import org.eclipse.emf.ecore.EPackage;
import bip2.Bip2Package;
import bip2.ujf.verimag.bip.instance.ComponentInstance;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import bip2.ujf.verimag.bip.packaging.BipPackageSet;
import bip2.ujf.verimag.bip.packaging.PackagingFactory;
import ujf.verimag.bip.backend.BackendStatus;
import ujf.verimag.bip.backend.Backendable;
import ujf.verimag.bip.backend.BackendStatusEnum;
import ujf.verimag.bip.backend.cpp.templates.Cmake;
import ujf.verimag.bip.backend.cpp.templates.GenerateDeploy;
import ujf.verimag.bip.backend.cpp.templates.GeneratePackage;
import ujf.verimag.bip.backend.error.BackendGenericError;
import ujf.verimag.bip.error.GenericError;

/**
 * CPP backend for BIP compiler.
 * 
 * This backend is responsible for generating CPP code from a BIP model.
 */
public class CppBackend implements Backendable {

    private Logger logger = Logger.getLogger(this.getClass().getName());

    /**
     * all available optimizations. Each [] represents one level.
     */
    private static final String[][] OptimizationLevels = {
        {}, // by default, no optimization is enabled.
        {"rdvconnector"}, // 1
        {"poolci", "poolciv", "ports-index", "ports-reset", "transitions-update"}, // 2
        {"no-side-effect", "early-update"} // 3
    };

    /**
     * Parameter for specifying where the files should be written
     */
    private static final String GENCPP_OUTPUT_DIR = "gencpp-output-dir";
    private String outputdir= null;

    /**
     * In case of used packages, should the backend also create code for them or assume
     * everything is already done.
     */
    private static final String GENCPP_FOLLOW_USED_PACKAGES = "gencpp-follow-used-packages";
    private boolean follow_used_package = false;

    /**
     * Disables some code that can be used to serialize the state of the system.
     * Useful when custom data is used and default C++ stream op can't
     * get a string repr.
     */
    private static final String GENCPP_NO_SERIALIZATION = "gencpp-no-serial";
    private boolean no_serialization = false;
    
    /**
     * Disables the generation of a main function.
     */
    private static final String GENCPP_NO_MAIN = "gencpp-no-main";
    private boolean no_main = false;

    /**
     * User can specify extra search paths for includes in the command line.
     * These paths will be added to other paths when calling
     * the C++ compiler
     */
    private static final String GENCPP_CC_I = "gencpp-cc-I";
    private final List<String> user_include_dirs = new ArrayList<String>();

    /**
     * User can specify extra search paths for libraries in the command line.
     * These paths will be added to other paths at link time by the linker
     */
    private static final String GENCPP_LD_L = "gencpp-ld-L";
    private final List<String> user_lib_dirs = new ArrayList<String>();

    /**
     * User can specify extra library in the command line.
     * These library will be used at link time by the linker
     */
    private static final String GENCPP_LD_l = "gencpp-ld-l";
    private final List<String> user_libs= new ArrayList<String>();

    /**
     * User can specify extra source files to compile along with the generated code
     */
    private static final String GENCPP_CC_EXTRA_SRC = "gencpp-cc-extra-src";
    private final List<String> user_extra_src= new ArrayList<String>();

    /**
     * User can specify extra objects files to link with the others parts
     */
    private static final String GENCPP_LD_EXTRA_OBJ = "gencpp-ld-extra-obj";
    private final List<String> user_extra_obj= new ArrayList<String>();

    /**
     * User can specify extra options passed to the compiler
     */
    private static final String GENCPP_CC_EXTRA_OPT = "gencpp-cc-extra-opt";
    private final List<String> user_extra_cc_opt = new ArrayList<String>();
    
    /**
     * User can specify extra options passed to the linker
     */
    private static final String GENCPP_LD_EXTRA_OPT = "gencpp-ld-extra-opt";
    private final List<String> user_extra_ld_opt= new ArrayList<String>();
    /**
     * Optimization level.
     * 0 means "none".
     * The greater the level, the more aggressive the optimizations.
     */
    private static final String GENCPP_OPTIM_LVL= "gencpp-optim";
    private int optim_lvl = 0;
    
    private static final String GENCPP_ENABLE_OPTIM = "gencpp-enable-optim";
    private final HashSet<String> enabled_opts = new HashSet<String>();

    private static final String GENCPP_DISABLE_OPTIM = "gencpp-disable-optim";
    private final HashSet<String> disabled_opts = new HashSet<String>();

    private static final String GENCPP_SET_OPTIM_PARAM= "gencpp-set-optim-param";

    private static final String GENCPP_ENABLE_BIP_LEVEL_DEBUG= "gencpp-enable-bip-debug";
    @SuppressWarnings("unused")
    private boolean enable_bip_level_debug = false;
    
    private static final String GENCPP_ENABLE_MARSHALLING = "gencpp-enable-marshalling";
    @SuppressWarnings("unused")
    private boolean enable_marshalling = false;

//    private static final String GENCPP_CONCURRENT_THREAD = "gencpp-thread";
    private int threads = 1;

    /**
     * This variable is part of the interface convention between the compiler
     * and the backend. DO NOT CHANGE ITS TYPE OR NAME
     */
    public final static String[][] backend_options_with_params = { 
        {GENCPP_OUTPUT_DIR, "Output directory for CPP backend"}, 
        {GENCPP_CC_I,"Add a path to the include search path (used when calling the C++ compiler)" },
        {GENCPP_LD_l,"Link with this library (use several times to add many libraries)" },
        {GENCPP_LD_L,"Add a path to the libraries search path (used when calling the linker)" },
        {GENCPP_CC_EXTRA_SRC,"Add an extra source file to the compilation list" },
        {GENCPP_LD_EXTRA_OBJ,"Add an extra object file to be linked with the other parts" },
        {GENCPP_CC_EXTRA_OPT,"Add extra options to the compiler" },
        {GENCPP_LD_EXTRA_OPT,"Add extra options to the linker" },
        {GENCPP_OPTIM_LVL,"Set the optimization level (defaults to none = 0). Each level includes a set of optimization." },
        {GENCPP_ENABLE_OPTIM, "Enable a specific optimization (can be used several times)"},
        {GENCPP_DISABLE_OPTIM, "Disable a specific optimization (can be used several times)"},
        {GENCPP_SET_OPTIM_PARAM, "Set an optimisation parameter: optimname:key:value"},
//        {GENCPP_CONCURRENT_THREAD, "How many threads can be used"},
    };

    /**
     * This variable is part of the interface convention between the compiler
     * and the backend.
     * DO NOT CHANGE ITS TYPE OR NAME
     */
    public final static String[][] backend_options_with_no_params={
        {GENCPP_FOLLOW_USED_PACKAGES, "Also generate code for used packages."},
        {GENCPP_NO_SERIALIZATION, "Disable the generation of serialization code"},
        {GENCPP_NO_MAIN, "Disable the generation of a main function"},
        {GENCPP_ENABLE_BIP_LEVEL_DEBUG, "Generates extra code to enable GDB to debug at the BIP level"},
        {GENCPP_ENABLE_MARSHALLING, "Enables the marshalling support"},
    };

    /**
     * Keep track of generated package. Useful at least for cmake
     * generation as we need results from type generation in instance generation. 
     */
    private final ArrayList<BipPackage> generated_packages = new ArrayList<BipPackage>();
    private BlockingQueue<BipPackage> sync_fifo_package;

    /**
     * Stores the root package. This is nearly useless. We use that to pass
     * a valid and coherent package when generating a cmake from instances.
     * This object is (currently) not even used in the template. But
     * acceleo needs to have a model object as first argument.
     */
    private BipPackage the_root_package;

    @Override
    public boolean canGenerateFromPackage() {
        return true;
    }

    @Override
    public boolean canGenerateFromInstance() {
        return true;
    }

    private static boolean optimisationExists(final String optim){
        for (final String[] opt_level : OptimizationLevels){
            for (final String opt : opt_level){
                if (opt.equals(optim)){
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * This class could be used to run concurrent generation jobs
     * Unfortunately, something looks not thread-safe as
     * errors are raised at runtime when running more than 1 worker.
     *  Leaving the code ready for multiple thread in case a solution
     *  can be found. No noticeable overhead measured...
     * @author poulhies
     */
    private class PackageWorker extends Thread {
        final private File outputdirF;
        final private int id;
        public Exception e = null;

        public PackageWorker(final File outputdirF, int id){
            this.outputdirF = outputdirF;
            this.id = id;
        }

        public void run() {
            try {
                GeneratePackage generator;
                List<Object> tmpl_args = new ArrayList<Object>();

                tmpl_args.add(user_include_dirs);
                tmpl_args.add(no_serialization);
                BipPackageSet packs = PackagingFactory.eINSTANCE.createBipPackageSet();
                sync_fifo_package.drainTo(packs.getPackages());

                logger.log(Level.INFO, "Thread " + id + " generating " + packs.getPackages().size() + " package(s)");

                //                    File package_outputdirF = new File(outputdirF, bp.getName());
                //                    package_outputdirF.mkdirs();
                outputdirF.mkdirs();
                generator = new GeneratePackage(packs, outputdirF,
                        tmpl_args);


                generator.doGenerate(new BasicMonitor());
            } catch (IOException e) {
                this.e = e;
            }
        }
    }

    @Override
    public BackendStatus generateFromPackage(final BipPackage pack) {
        EPackage.Registry.INSTANCE.put(Bip2Package.eNS_URI,
                Bip2Package.eINSTANCE);

        // FIXME:
        // /!\ introduced for running the compiler from Eclipse
        // but in principle it should not be necessary
        EPackage.Registry.INSTANCE.put("platform:/resource/ujf.verimag.bip.metamodel/model/bip2.ecore",
                Bip2Package.eINSTANCE);

        final Stack<BipPackage> to_generate = new Stack<BipPackage>();

        final File outputdirF = new File(this.outputdir);
        if (!outputdirF.exists() || !outputdirF.isDirectory()){
            logger.log(Level.SEVERE, "Output directory does not exist (or not a directory) : " + outputdir);
            return new BackendStatus(BackendStatusEnum.FAIL);
        }

        to_generate.add(pack);
        this.the_root_package = pack;

        try {
            logger.log(Level.FINEST, "Executing acceleo generator...");
            while (!to_generate.isEmpty()){
                final BipPackage bp = to_generate.pop();

                if (generated_packages.contains(bp))
                    continue;

                // /!\ WARNING: the following policy does not
                // for complex includes, an ordering policy has
                // been added to the generation of the link
                // in file 'cmake.mtl'.
                
                // prepend: list contains the leaves first
                // that better for cmake because link will 
                // be in order compatible with hierarchy
                generated_packages.add(0, bp);

                if (this.follow_used_package){
                    to_generate.addAll(bp.getUsed_packages());
                }
            }

            sync_fifo_package = new ArrayBlockingQueue<BipPackage>(generated_packages.size());
            sync_fifo_package.addAll(generated_packages);
            
            // The following code is an attempt to copy the model
            // to avoid concurrency bottle-neck & error
            // But it's not working. Leaving for later devs...
            
//            for (BipPackage bp: generated_packages){
////                sync_fifo_package.add(EcoreUtil.copy(bp));
////                sync_fifo_package.add(bp);
//                Collection<BipPackage> clone = EcoreUtil.copyAll(generated_packages);
//                for (BipPackage cbp : clone){
//                    if (bp.getName().equals(cbp.getName()))
//                        sync_fifo_package.add(cbp);
//                }
//            }
            List<PackageWorker> workers = new ArrayList<PackageWorker>();

            for (int i=0; i< this.threads; i++){
                logger.log(Level.INFO, "Starting thread " + i);
                PackageWorker w = new PackageWorker(outputdirF, i);
                w.start();
                workers.add(w);
            }

            for (PackageWorker w : workers){
                logger.log(Level.INFO, "Waiting thread...");
                w.join();
                if (w.e != null){
                    w.e.printStackTrace();
                    return new BackendStatus(BackendStatusEnum.FAIL);
                }
            }

            final List<Object> tmpl_arguments = new ArrayList<Object>();
            tmpl_arguments.add(this.outputdir);
            tmpl_arguments.add(generated_packages);
            tmpl_arguments.add(false); // specify that we are building from types only.
            tmpl_arguments.add(this.user_include_dirs);
            tmpl_arguments.add(this.user_libs); //useless when compiling only types, but needed for calling template
            tmpl_arguments.add(this.user_lib_dirs); //useless when compiling only types, but needed for calling template
            tmpl_arguments.add(this.user_extra_src); //useless when compiling only types, but needed for calling template
            tmpl_arguments.add(this.user_extra_obj); //useless when compiling only types, but needed for calling template
            tmpl_arguments.add(this.user_extra_cc_opt); //useless when compiling only types, but needed for calling template
            tmpl_arguments.add(this.user_extra_ld_opt); //useless when compiling only types, but needed for calling template

            Cmake master_cmakegen = new Cmake(this.the_root_package, outputdirF, tmpl_arguments);
            master_cmakegen.doGenerate(new BasicMonitor());
            logger.log(Level.FINEST, "Executed acceleo generator.");
        } catch (IOException e) {
            e.printStackTrace();
            return new BackendStatus(BackendStatusEnum.FAIL);
        } catch (InterruptedException e) {
            e.printStackTrace();
            return new BackendStatus(BackendStatusEnum.FAIL);
        }

        return new BackendStatus(BackendStatusEnum.SUCCESS);
    }

    @Override
    public BackendStatus generateFromInstance(final ComponentInstance instance) {
        final List<Object> tmpl_args = new ArrayList<Object>();
        tmpl_args.add(no_main);
        final File outputdirF = new File(this.outputdir, "Deploy");

        try {
            final GenerateDeploy generator= new GenerateDeploy(instance, outputdirF,
                    tmpl_args);
            generator.doGenerate(new BasicMonitor());

            List<Object> tmpl_arguments = new ArrayList<Object>();
            tmpl_arguments.add(this.outputdir);
            tmpl_arguments.add(generated_packages);
            tmpl_arguments.add(true); // specify that we are building from instances.
            tmpl_arguments.add(this.user_include_dirs);
            tmpl_arguments.add(this.user_libs);
            tmpl_arguments.add(this.user_lib_dirs);
            tmpl_arguments.add(this.user_extra_src);
            tmpl_arguments.add(this.user_extra_obj);
            tmpl_arguments.add(this.user_extra_cc_opt);
            tmpl_arguments.add(this.user_extra_ld_opt);

            Cmake master_cmakegen = new Cmake(this.the_root_package, new File(this.outputdir), tmpl_arguments);
            master_cmakegen.doGenerate(new BasicMonitor());
        } catch (IOException e) {
            e.printStackTrace();
            return new BackendStatus(BackendStatusEnum.FAIL);
        }

        return new BackendStatus(BackendStatusEnum.SUCCESS);
    }

    @Override
    public boolean isEnabled() {
        // enabled if the outputfile has been set.
        return (this.outputdir != null);
    }

    @Override
    public GenericError[] configure(final OptionSet options,
            final Map<String, OptionSpec<String>> ospecs) {

        if (options.has(ospecs.get(GENCPP_OUTPUT_DIR))){
            this.outputdir= options.valueOf(ospecs.get(GENCPP_OUTPUT_DIR));
        }

        if (options.has(GENCPP_FOLLOW_USED_PACKAGES)){
            this.follow_used_package = true;
        }

        if (options.has(GENCPP_NO_SERIALIZATION)){
            this.no_serialization = true;
        }

        if (options.has(GENCPP_NO_MAIN)){
            this.no_main = true;
        }

        if (options.has(GENCPP_ENABLE_BIP_LEVEL_DEBUG)){
            // the local boolean is "useless". The use of system property is
            // a "hack" that easily lets us drive backend without
            // bloating its interface.
            this.enable_bip_level_debug = true;
            System.setProperty("bipc_gencpp-enable_bip_level_debug", "true");
        }

        if (options.has(GENCPP_ENABLE_MARSHALLING)){
            // the local boolean is "useless". The use of system property is
            // a "hack" that easily lets us drive backend without
            // bloating its interface.
            this.enable_marshalling = true;
            System.setProperty("bipc_gencpp-enable_marshalling", "true");
        }

        if (options.has(ospecs.get(GENCPP_CC_I))){
            for (String dir : options.valuesOf(ospecs.get(GENCPP_CC_I))){
                final File d = new File (dir);
                if (!d.exists()){
                    logger.log(Level.WARNING, "Directory: " + dir + " does not exist.");
                } else if (!d.isDirectory()){
                    logger.log(Level.WARNING, dir + " is not a directory.");
                }
                dir = d.getAbsolutePath();
                this.user_include_dirs.add(dir);
            }
        }

        if (options.has(ospecs.get(GENCPP_LD_l))){
            this.user_libs.addAll(options.valuesOf(ospecs.get(GENCPP_LD_l)));
        }

        if (options.has(ospecs.get(GENCPP_LD_L))){
            for (String dir : options.valuesOf(ospecs.get(GENCPP_LD_L))){
                File d = new File (dir);
                if (!d.exists()){
                    logger.log(Level.WARNING, "Directory: " + dir + " does not exist.");
                } else if (!d.isDirectory()){
                    logger.log(Level.WARNING, dir + " is not a directory.");
                }
                dir = d.getAbsolutePath();
                this.user_lib_dirs.add(dir);
            }
        }

        if (options.has(ospecs.get(GENCPP_CC_EXTRA_SRC))){
            for (String src : options.valuesOf(ospecs.get(GENCPP_CC_EXTRA_SRC))){
                File d = new File (src);
                if (!d.exists()){
                    logger.log(Level.WARNING, "File: " + src + " does not exist.");
                } else if (!d.isFile()){
                    logger.log(Level.WARNING, src + " is not a file.");
                }
                src= d.getAbsolutePath();
                this.user_extra_src.add(src);
            }
        }

        if (options.has(ospecs.get(GENCPP_LD_EXTRA_OBJ))){
            for (String obj : options.valuesOf(ospecs.get(GENCPP_LD_EXTRA_OBJ))){
                File d = new File (obj);
                if (!d.exists()){
                    logger.log(Level.WARNING, "File: " + obj + " does not exist.");
                } else if (d.isFile()){
                    logger.log(Level.WARNING, obj+ " is not a file.");
                }
                obj = d.getAbsolutePath();
                this.user_extra_obj.add(obj);
            }
        }
        
        if (options.has(ospecs.get(GENCPP_CC_EXTRA_OPT))){
            for (String obj : options.valuesOf(ospecs.get(GENCPP_CC_EXTRA_OPT))){                
                this.user_extra_cc_opt.add(obj);
            }
        }
        
        if (options.has(ospecs.get(GENCPP_LD_EXTRA_OPT))){
            for (String obj : options.valuesOf(ospecs.get(GENCPP_LD_EXTRA_OPT))){                
                this.user_extra_ld_opt.add(obj);
            }
        }

//        if (options.has(ospecs.get(GENCPP_CONCURRENT_THREAD))){
//            this.threads = Integer.parseInt(options.valueOf(ospecs.get(GENCPP_CONCURRENT_THREAD)));
//            if (this.threads <= 0)
//                this.threads = 1;
//        }
 
        // get to-be-enabled optim
        if (options.has(ospecs.get(GENCPP_ENABLE_OPTIM))){
            for (final String optim: options.valuesOf(ospecs.get(GENCPP_ENABLE_OPTIM))){
                if (! optimisationExists(optim)){
                    return new GenericError[]{new BackendGenericError("Can't enable unknown optimisation: " + optim) };
                }
            this.enabled_opts.add(optim);
            }
        }

        if (options.has(ospecs.get(GENCPP_OPTIM_LVL))){
            this.optim_lvl = Integer.parseInt(options.valueOf(ospecs.get(GENCPP_OPTIM_LVL)));
            if (this.optim_lvl < 0)
                return new GenericError[]{new BackendGenericError("Optimization level must be >= 0.") };
            for (int i = 0 ; i <= optim_lvl && i<OptimizationLevels.length; i++){
                for (final String opt_to_enable: OptimizationLevels[i]){
                    this.enabled_opts.add(opt_to_enable);
                }
            }
        }
        // pass argument to acceleo via System properties. That's better tan nothing.
        System.setProperty("bipc_gencpp-optim_lvl", Integer.toString(this.optim_lvl));

        // get to-be-disabled optim
        if (options.has(ospecs.get(GENCPP_DISABLE_OPTIM))){
            for (final String optim: options.valuesOf(ospecs.get(GENCPP_DISABLE_OPTIM))){
                if (! optimisationExists(optim)){
                    return new GenericError[]{new BackendGenericError("Can't disable unknown optimisation: " + optim) };
                }
                this.disabled_opts.add(optim);
            }
        }

        for (final String enable_opt: this.enabled_opts){
            if (!this.disabled_opts.contains(enable_opt)){
                logger.log(Level.INFO, "Enabling optimization:" + enable_opt);
                System.setProperty("bipc_gencpp-optim__" + enable_opt, "1");
            } else {
                logger.log(Level.INFO, "Not enabling optimization because it is disabled:" + enable_opt);
            }
        }
        if (options.has(ospecs.get(GENCPP_SET_OPTIM_PARAM))){
            for (final String optim_param: options.valuesOf(ospecs.get(GENCPP_SET_OPTIM_PARAM))){
                final String[] params = optim_param.split(":");
                if (params.length != 3){
                    return new GenericError[]{new BackendGenericError("Invalid optimization parameter: " + optim_param) };
                }

                final String opt_name = params[0];
                final String param_name = params[1];
                final String param_val = params[2];
                if (! optimisationExists(opt_name)){
                    return new GenericError[]{new BackendGenericError("Can't set parameter for unknown optimisation: " + opt_name) };
                }
                System.setProperty("bipc_gencpp-optim__" + opt_name + "__" + param_name, param_val);
            }
        }

        // CPP backend needs root declaration.
        if (isEnabled() && ! options.has(ospecs.get("d"))){
            return new GenericError[]{new BackendGenericError("CPP back-end requires a root component declaration.") };
        } else {
            return new GenericError[0];
        }
    }
}
