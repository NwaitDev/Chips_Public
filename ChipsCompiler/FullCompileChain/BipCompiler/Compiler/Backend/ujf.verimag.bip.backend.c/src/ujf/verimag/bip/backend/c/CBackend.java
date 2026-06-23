/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
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

package ujf.verimag.bip.backend.c;


import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.eclipse.emf.common.util.BasicMonitor;

import joptsimple.OptionSet;
import joptsimple.OptionSpec;

import bip2.ujf.verimag.bip.instance.ComponentInstance;
import bip2.ujf.verimag.bip.packaging.BipPackage;

import ujf.verimag.bip.backend.BackendStatus;
import ujf.verimag.bip.backend.Backendable;
import ujf.verimag.bip.backend.BackendStatusEnum;
import ujf.verimag.bip.backend.c.templates.GeneratePackage;
import ujf.verimag.bip.backend.error.BackendGenericError;
import ujf.verimag.bip.error.GenericError;

public class CBackend implements Backendable {
    
    private Logger logger = Logger.getLogger(this.getClass().getName());
    
    /**
     * Parameter for specifying where the files should be written
     */
    private static final String GENC_OUTPUT_DIR = "genc-output-dir";
    private String outputdir= null;
    
    /**
     * In case of used packages, should the backend also create code for them or assume
     * everything is already done.
     */
    private static final String GENC_FOLLOW_USED_PACKAGES = "genc-follow-used-packages";
    private boolean follow_used_package = false;

    /**
     * User can specify extra search paths for includes in the command line.
     * These paths will be added to other paths when calling
     * the C++ compiler
     */
    private static final String GENC_CC_I = "genc-cc-I";
    private final List<String> user_include_dirs = new ArrayList<String>();

    /**
     * User can specify extra search paths for libraries in the command line.
     * These paths will be added to other paths at link time by the linker
     */
    private static final String GENC_LD_L = "genc-ld-L";
    private final List<String> user_lib_dirs = new ArrayList<String>();

    /**
     * User can specify extra library in the command line.
     * These library will be used at link time by the linker
     */
    private static final String GENC_LD_l = "genc-ld-l";
    private final List<String> user_libs= new ArrayList<String>();

    /**
     * User can specify extra source files to compile along with the generated code
     */
    private static final String GENC_CC_EXTRA_SRC = "genc-cc-extra-src";
    private final List<String> user_extra_src= new ArrayList<String>();
    
    /**
     * User can specify extra objects files to link with the others parts
     */
    private static final String GENC_LD_EXTRA_OBJ = "genc-ld-extra-obj";
    private final List<String> user_extra_obj= new ArrayList<String>();
    
    public static String[][] backend_options_with_no_params={
        {GENC_FOLLOW_USED_PACKAGES, "Also generate code for used packages."}
    };

    public static String[][] backend_options_with_params={
        {GENC_OUTPUT_DIR, "Output directory for C backend"}, 
        {GENC_CC_I,"Add a path to the include search path (used when calling the C/C++ compiler)" },
        {GENC_LD_l,"Link with this library (use several times to add many libraries)" },
        {GENC_LD_L,"Add a path to the libraries search path (used when calling the linker)" },
        {GENC_CC_EXTRA_SRC,"Add an extra source file to the compilation list" },
        {GENC_LD_EXTRA_OBJ,"Add an extra object file to be linked with the other parts" }
    };

    @Override
    public boolean isEnabled(){
        // enabled if the outputfile has been set.
        return (this.outputdir != null);
    }

    @Override
    public BackendStatus generateFromPackage(BipPackage pack) {
        System.out.println("Generate package for " + pack.getName());
        
        File outputdirF = new File(this.outputdir, "c");

        try {
            List<String> tmpl_args = new ArrayList<String>();
            
            tmpl_args.add("xxx.C");
            
            outputdirF.mkdirs();
            
            GeneratePackage generator = new GeneratePackage(pack, outputdirF,
                    tmpl_args);

            generator.doGenerate(new BasicMonitor());
        }
        catch (IOException e) {
            e.printStackTrace();
            return new BackendStatus(BackendStatusEnum.FAIL);
        }
        
        return new BackendStatus(BackendStatusEnum.SUCCESS);
    }

    @Override
    public boolean canGenerateFromPackage() {
        return true;
    }

    @Override
    public boolean canGenerateFromInstance() {
        return true;
    }

    @Override
    public BackendStatus generateFromInstance(ComponentInstance instance) {
        System.out.println("Generate instance for " + instance.getDeclaration().getName());
        return new BackendStatus(BackendStatusEnum.SUCCESS);
    }

    @Override
    public GenericError[] configure(OptionSet options,
            Map<String, OptionSpec<String>> ospecs) {
        if (options.has(ospecs.get(GENC_OUTPUT_DIR))){
            this.outputdir= options.valueOf(ospecs.get(GENC_OUTPUT_DIR));
        }

        if (options.has(GENC_FOLLOW_USED_PACKAGES)){
            this.follow_used_package = true;
        }
        
        if (options.has(ospecs.get(GENC_CC_I))){
            for (String dir : options.valuesOf(ospecs.get(GENC_CC_I))){
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

        if (options.has(ospecs.get(GENC_LD_l))){
            this.user_libs.addAll(options.valuesOf(ospecs.get(GENC_LD_l)));
        }

        if (options.has(ospecs.get(GENC_LD_L))){
            for (String dir : options.valuesOf(ospecs.get(GENC_LD_L))){
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

        if (options.has(ospecs.get(GENC_CC_EXTRA_SRC))){
            for (String src : options.valuesOf(ospecs.get(GENC_CC_EXTRA_SRC))){
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

        if (options.has(ospecs.get(GENC_LD_EXTRA_OBJ))){
            for (String obj : options.valuesOf(ospecs.get(GENC_LD_EXTRA_OBJ))){
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

        // C backend needs root declaration.
        if (isEnabled() && ! options.has(ospecs.get("d"))){
            return new GenericError[]{new BackendGenericError("C back-end requires a root component declaration.") };
        } else {
            return new GenericError[0];
        }
    }
}