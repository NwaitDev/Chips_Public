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

package ujf.verimag.bip.backend.bip;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.Stack;
import java.util.logging.Level;
import java.util.logging.Logger;

import joptsimple.OptionSet;
import joptsimple.OptionSpec;

import org.eclipse.emf.common.util.BasicMonitor;
import org.eclipse.emf.ecore.EPackage;

import bip2.Bip2Package;
import bip2.ujf.verimag.bip.instance.ComponentInstance;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import ujf.verimag.bip.backend.BackendStatus;
import ujf.verimag.bip.backend.Backendable;
import ujf.verimag.bip.backend.BackendStatusEnum;
import ujf.verimag.bip.backend.bip.templates.GeneratePackage;
import ujf.verimag.bip.error.GenericError;

/**
 * BIP backend for BIP compiler.
 * 
 * This backend is responsible for generating BIP code from a BIP model.
 */
public class BipBackend implements Backendable {

    private Logger logger = Logger.getLogger(this.getClass().getName());
    
    /**
     * Parameter for specifying where the files should be written
     */
    private static final String GENBIP_OUTPUT_DIR = "genbip-output-dir";
    private String outputdir= null;
    
    /**
     * In case of used packages, should the backend also create code for them or assume
     * everything is already done.
     */
    private static final String GENBIP_FOLLOW_USED_PACKAGES = "genbip-follow-used-packages";
    private boolean follow_used_package = false;

    /**
     * This variable is part of the interface convention between the compiler
     * and the backend.
     * DO NOT CHANGE ITS TYPE OR NAME
     */
    public static String[][] backend_options_with_params={
        {GENBIP_OUTPUT_DIR, "Output directory for BIP backend"},
    };
    
    /**
     * This variable is part of the interface convention between the compiler
     * and the backend.
     * DO NOT CHANGE ITS TYPE OR NAME
     */
    public static String[][] backend_options_with_no_params={
        {GENBIP_FOLLOW_USED_PACKAGES, "Also generate code for used packages."},
    };
    
    @Override
    public boolean canGenerateFromPackage() {
        return true;
    }

    @Override
    public boolean canGenerateFromInstance() {
        // BIP language only describes types, nothing to do with instances.
        return false;
    }

    @Override
    public BackendStatus generateFromPackage(BipPackage pack) {
        EPackage.Registry.INSTANCE.put(Bip2Package.eNS_URI,
                Bip2Package.eINSTANCE);
        
        // FIXME:
        // /!\ introduced for running the compiler from Eclipse
        // but in principle it should not be necessary
        EPackage.Registry.INSTANCE.put("platform:/resource/ujf.verimag.bip.metamodel/model/bip2.ecore",
                Bip2Package.eINSTANCE);
        
        Stack<BipPackage> to_generate = new Stack<BipPackage>();
        Set<BipPackage> already_generated = new HashSet<BipPackage>();
        
        File outputdirF = new File(this.outputdir);
        if (!outputdirF.exists() || !outputdirF.isDirectory()){
            logger.log(Level.SEVERE, "Output directory does not exist (or not a directory) : " + outputdir);
            return new BackendStatus(BackendStatusEnum.FAIL);
        }
        
        to_generate.add(pack);
        
        try {
            GeneratePackage generator;
            logger.log(Level.FINEST, "Executing acceleo generator...");
            while (!to_generate.isEmpty()){
                BipPackage bp = to_generate.pop();
                
                if (already_generated.contains(bp))
                    continue;
                
                File this_pack_output_dir;
                // check output path (create it if needed).
                String pname = bp.getName();
                int didx = pname.lastIndexOf('.'); // is it a nested package ?
                if (didx != -1){
                    String ppath = pname.substring(0, didx).replace('.', File.separatorChar);
                    pname = pname.substring(didx + 1);
                    String fpath = this.outputdir + File.separatorChar + ppath;
                    this_pack_output_dir = new File(fpath);
                    if (!(this_pack_output_dir.exists() && this_pack_output_dir.isDirectory()) && !this_pack_output_dir.mkdirs()){
                        logger.log(Level.SEVERE, "Error with nested package directory (already exists with bad perms or error when creating it) : " + fpath);
                        return new BackendStatus(BackendStatusEnum.FAIL);
                    }
                } else {
                    this_pack_output_dir = outputdirF;
                }
                
                List<String> tmpl_args = new ArrayList<String>();
                tmpl_args.add(pname + ".bip");
                
                generator = new GeneratePackage(bp, this_pack_output_dir,
                        tmpl_args);

                generator.doGenerate(new BasicMonitor());
                already_generated.add(bp);
                
                if (this.follow_used_package){
                    to_generate.addAll(bp.getUsed_packages());
                }
            }
            logger.log(Level.FINEST, "Executed acceleo generator.");
            
        } catch (IOException e) {
            e.printStackTrace();
            return new BackendStatus(BackendStatusEnum.FAIL);
        }

        return new BackendStatus(BackendStatusEnum.SUCCESS);
    }

    @Override
    public BackendStatus generateFromInstance(ComponentInstance instance) {
        return new BackendStatus(BackendStatusEnum.FAIL);
    }

    @Override
    public boolean isEnabled() {
        // enabled if the outputfile has been set.
        return (this.outputdir != null);
    }

    @Override
    public GenericError[] configure(OptionSet options,
            Map<String, OptionSpec<String>> ospecs) {
        if (options.has(ospecs.get(GENBIP_OUTPUT_DIR))){
            this.outputdir= options.valueOf(ospecs.get(GENBIP_OUTPUT_DIR));
        }
        if (options.has(GENBIP_FOLLOW_USED_PACKAGES)){
            this.follow_used_package = true;
        }
        
        return new GenericError[0];
    }
}
