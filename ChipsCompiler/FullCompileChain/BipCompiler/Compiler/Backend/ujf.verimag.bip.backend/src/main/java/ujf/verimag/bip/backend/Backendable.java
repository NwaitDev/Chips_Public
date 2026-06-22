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

package ujf.verimag.bip.backend;

import ujf.verimag.bip.Configurable;
import bip2.ujf.verimag.bip.instance.ComponentInstance;
import bip2.ujf.verimag.bip.packaging.BipPackage;

/***
 * This interface describes what a Backend must provide. A Backend is the
 * end-part of the compiler. Its role is to generate a <it>final</it> product.
 * By final, it means that this product is the last one seen by the bip
 * compiler.
 * 
 * A backend must not be used to apply transformations on the provided models.
 * If transformations are needed, a filter must be used.
 * 
 * @author poulhies
 * 
 */
public interface Backendable extends Configurable {
    /**
     * Tests the backend's capability for the generation from a BipPackage (type graph)
     * @return true if the backend can generate something out of a BipPackage, false if not.
     */
    public boolean canGenerateFromPackage();
    
    /**
     * Tests the backend's capability for the generation from a ComponentInstance (instance tree)
     * @return true if the backend can generate something out of a ComponentInstance, false if not.
     */
    public boolean canGenerateFromInstance();
    
    /**
     * Executes the generation from a BipPackage
     * @param pack the package
     * @return a BackendStatus indicating the status of the generation.
     */
    public BackendStatus generateFromPackage(BipPackage pack);
    
    /**
     * Executes the generation from a ComponentInstance
     * @param instance the instance
     * @return a BackendStatus indicating the status of the generation.
     */
    public BackendStatus generateFromInstance(ComponentInstance instance);
    
    /**
     * Tests if the backend is enabled or not
     * @return true if the backend is enabled, false if not.
     */
    public boolean isEnabled();
}
