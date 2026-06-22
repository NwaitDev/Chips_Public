/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
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

package ujf.verimag.bip.backend.aseba;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.logging.Logger;

import joptsimple.OptionSet;
import joptsimple.OptionSpec;

import org.eclipse.emf.common.util.BasicMonitor;

import bip2.ujf.verimag.bip.instance.ComponentInstance;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import ujf.verimag.bip.backend.BackendStatus;
import ujf.verimag.bip.backend.Backendable;
import ujf.verimag.bip.backend.BackendStatusEnum;
import ujf.verimag.bip.backend.aseba.templates.GenerateDeployed;
import ujf.verimag.bip.error.GenericError;

/**
 * ASEBA backend for BIP compiler.
 * 
 * This Backend makes strong asumptions on the input language (a subset of the
 * BIP language). It also heavily relies on the Send/Receive BIP constructs.
 * 
 * A set of annotations and naming conventions must be used in order for 
 * the backend to work:
 *  - variables with double '_' are mapped to dotted notation, '__' being replaced by a single dot.
 *    This is because aseba can use dotted notation but not BIP.
 *  - a variable with the 'system' aseba annotation denotes a variable that must
 *    not be declared in aseba as it's a builtin variable: '@aseba(system)'
 *  - a variable with the 'system' annotation and the 'map=FOO' will skip data
 *    declaration (system) and also rename reference to the variable to its corresponding
 *    value 'FOO' given in the annotation.
 *  - an exported port with the 'recv' annotation will be treated as a port by which
 *    something is received (data or simply an event).
 *  - an exported port with the 'send' annotation will be treated as a port by which
 *    something is sent (data or simply an event).
 *  - a component declaration must have a 'node="ASEBA NODE NAME"' annotation to guide the
 *    distribution of the generated code across available nodes.
 *  - a single component declaration may have the 'booter' annotation. It is used
 *    in case of delayed init, where all nodes are awaiting a 'start' event that the
 *    booter component will emit after a small delay (if --genaesl-start-delay is used).
 *  
 * This backend is responsible for generating ASEBA code from a BIP model.
 * It targets the Marxbot specifically by could be adapted to any platform
 * supporting ASEBA.
 */
public class AsebaBackend implements Backendable {

    @SuppressWarnings("unused")
    private Logger logger = Logger.getLogger(this.getClass().getName());

    /**
     * Parameter for specifying where the files should be written
     */
    private static final String GENAESL_OUTPUT_DIR = "genaesl-output-dir";
    private String outputdir= null;

    /**
     * Parameter for specifying where the output file name
     */
    private static final String GENAESL_OUTPUT_NAME = "genaesl-output-name";
    private String outputname = null;

    /**
     * If used, then the generated code will include the glue necessary
     * for a delayed start. The 'booter' annotation must be used on exactly
     * one component declaration in the system (or nothing will happen).
     */
    private static final String GENAESL_START_DELAY = "genaesl-start-delay";
    private int delay = -1;

    /**
     * This variable is part of the interface convention between the compiler
     * and the backend.
     * DO NOT CHANGE ITS TYPE OR NAME
     */
    public static String[][] backend_options_with_params={
        {GENAESL_OUTPUT_DIR, "Output directory for Aseba scripts"},
        {GENAESL_OUTPUT_NAME, "Output name for Aseba scripts"},
        {GENAESL_START_DELAY, "Use a timer with the given delay to delay the start of the system."}
    };

    @Override
    public boolean canGenerateFromPackage() {
        return false;
    }

    @Override
    public boolean canGenerateFromInstance() {
        return true;
    }

    @Override
    public BackendStatus generateFromPackage(BipPackage pack) {
        return new BackendStatus(BackendStatusEnum.FAIL);
    }

    @Override
    public BackendStatus generateFromInstance(ComponentInstance instance) {
        GenerateDeployed generator;
        List<String> tmpl_args = new ArrayList<String>();
        File outputdirF = new File(this.outputdir);
        tmpl_args.add(this.outputname);
        tmpl_args.add("" + this.delay);
        
        try {
            generator = new GenerateDeployed(instance, outputdirF,
                    tmpl_args);
            generator.doGenerate(new BasicMonitor());
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
    public GenericError[] configure(OptionSet options,
            Map<String, OptionSpec<String>> ospecs) {
        if (options.has(ospecs.get(GENAESL_OUTPUT_DIR))){
            this.outputdir= options.valueOf(ospecs.get(GENAESL_OUTPUT_DIR));
        }
        if (options.has(ospecs.get(GENAESL_OUTPUT_NAME))){
            this.outputname = options.valueOf(ospecs.get(GENAESL_OUTPUT_NAME));
        }
        
        if (options.has(ospecs.get(GENAESL_START_DELAY))){
            this.delay = Integer.parseInt(options.valueOf(ospecs.get(GENAESL_START_DELAY)));
        }
        
        return new GenericError[0];
    }
}
