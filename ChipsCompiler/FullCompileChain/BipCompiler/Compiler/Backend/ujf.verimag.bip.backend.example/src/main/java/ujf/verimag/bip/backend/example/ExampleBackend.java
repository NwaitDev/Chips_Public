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

package ujf.verimag.bip.backend.example;


import java.util.Map;

import joptsimple.OptionSet;
import joptsimple.OptionSpec;

import bip2.ujf.verimag.bip.instance.ComponentInstance;
import bip2.ujf.verimag.bip.packaging.BipPackage;

import ujf.verimag.bip.backend.BackendStatus;
import ujf.verimag.bip.backend.Backendable;
import ujf.verimag.bip.backend.BackendStatusEnum;
import ujf.verimag.bip.error.GenericError;

public class ExampleBackend implements Backendable {


    public static String[][] backend_options_with_no_params={
        {"example1", "This is an example"},
    };

    public static String[][] backend_options_with_params={
        {"example3", "e", "Third example, with param!"},
    };

    @Override
    public boolean isEnabled(){
        return true;
    }

    @Override
    public BackendStatus generateFromPackage(BipPackage pack) {
        System.out.println("Generate package for " + pack.getName());
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
        System.out.println("Example get for a common arg: " + options.valueOf(ospecs.get("p")));
        System.out.println("Example get for a toggle private arg: " + options.has("example1"));
        if (options.has(ospecs.get("example3"))){
            System.out.println("Example get for a private arg with params" + options.valueOf(ospecs.get("example1")));
        }
        
        return new GenericError[0];
    }
}