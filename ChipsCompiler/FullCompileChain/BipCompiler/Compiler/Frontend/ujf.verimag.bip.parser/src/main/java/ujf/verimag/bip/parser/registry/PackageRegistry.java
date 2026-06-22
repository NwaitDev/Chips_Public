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

package ujf.verimag.bip.parser.registry;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import bip2.ujf.verimag.bip.packaging.BipPackage;

/**
 * A package registry is a simple "dictionary" used to store loaded packages.
 * The underlying data structure is a map, as a package is identified by
 * its dotted name and is represented as a single model object (of type BipPackage)
 */
public class PackageRegistry {
    /**
     * The map used to store loaded packages associated with their unique names.
     */
    protected Map<String, BipPackage> packageMap = new HashMap<String, BipPackage>();

    /**
     * Register a new package
     * @param pack the package to register
     * @throws PackageAlreadyRegisteredException when a package with the same name is already registered
     */
    public void registerPackage(BipPackage pack)
            throws PackageAlreadyRegisteredException {
        String name = pack.getName();

        if (packageMap.containsKey(name)) {
            /*
             * Package is already in the registry. It should never happen, raise
             * an error.
             */
            throw new PackageAlreadyRegisteredException();
        }

        this.packageMap.put(name, pack);
    }
    
    /**
     * Get a package from its name
     * @param name the package name
     * @return the corresponding package if found, null if not
     */
    public BipPackage getPackage(String name){
        return this.packageMap.get(name);
    }
    
    /**
     * Get a list of all registered packages.
     * @return the list of all packages
     */
    public List<BipPackage> getPackages(){
        ArrayList<BipPackage> list = new ArrayList<BipPackage>();
        list.addAll(this.packageMap.values());
        return list;
    }
    
    /**
     * Tests if a package is already registered for a given name
     * @param name the name
     * @return true if there is already a package registered, false if not.
     */
    public boolean hasPackage(String name){
        return this.packageMap.containsKey(name);
    }
    
    /**
     * Get the number of registered packages
     * @return the number of packages
     */
    public int packageCount(){
        return this.packageMap.size();
    }
}
