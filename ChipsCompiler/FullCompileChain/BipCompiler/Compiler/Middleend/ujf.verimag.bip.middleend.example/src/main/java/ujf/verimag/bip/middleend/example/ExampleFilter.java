/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Anakreontas Mentis
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

package ujf.verimag.bip.middleend.example;

import java.util.Map;

import joptsimple.OptionSet;
import joptsimple.OptionSpec;
import bip2.ujf.verimag.bip.instance.ComponentInstance;
import bip2.ujf.verimag.bip.packaging.BipPackage;
import ujf.verimag.bip.error.GenericError;
import ujf.verimag.bip.middleend.FilterStatus;
import ujf.verimag.bip.middleend.FilterStatusEnum;
import ujf.verimag.bip.middleend.Filterable;

public class ExampleFilter implements Filterable {

    public static String[][] filter_options_with_no_params={
        {"example-filter-1", "This is an example"},
    };

    public static String[][] filter_options_with_params={
        {"example-filter-2", "Third example, with param!"},
    };

    public ExampleFilter(Map<String,String> parameters){
        System.out.println("Got :");

        for (Map.Entry<String,String> kv : parameters.entrySet()){
            System.out.println("  ->" + kv.getKey() + " = " + kv.getValue());
        }
    }

    @Override
    public GenericError[] configure(OptionSet options,
            Map<String, OptionSpec<String>> ospecs) {
        System.out.println("Example get for a toggle private arg: " + options.has("example-filter-1"));
        if (options.has(ospecs.get("example-filter-2"))){
            System.out.println("Example get for a private arg with params" + options.valueOf(ospecs.get("example-filter-2")));
        }
        
        return new GenericError[0];
    }

    @Override
    public FilterStatus filterPackage(BipPackage pack) {
        System.out.println("Filtering Package! ");
        return new FilterStatus(FilterStatusEnum.SUCCESS);
    }

    @Override
    public boolean isEnabled() {
        return true;
    }
}
