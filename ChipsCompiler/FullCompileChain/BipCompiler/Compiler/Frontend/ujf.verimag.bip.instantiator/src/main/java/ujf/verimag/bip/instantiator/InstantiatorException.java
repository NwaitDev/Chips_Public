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

package ujf.verimag.bip.instantiator;

import ujf.verimag.bip.instantiator.error.InstantiatorError;
import ujf.verimag.bip.metamodel.AnnotatedEObject;

/**
 * Exception class raised when the instantiator makes an error.
 */
public class InstantiatorException extends Exception {

    private static final long serialVersionUID = 1L;

    /**
     * A simple string message for the reason.
     */
    private String reason;
    
    /**
     * The model object whose treatment triggered the exception.
     */
    private AnnotatedEObject node;

    private InstantiatorError[] errors;

    /**
     * Get the model object whose treatment triggered the exception
     * @return the model object
     */
    public AnnotatedEObject getNode(){
        return this.node;
    }
    
    /**
     * Get the reason (as a string) for this exception
     * @return the reason
     */
    public String getReason() {
        return reason;
    }

    /**
     * Get the errors that caused this exception
     * @return the array of errors
     */
    public InstantiatorError[] getErrors() {
        if (errors == null) errors = new InstantiatorError[0];
        return errors;
    }
    
    /**
     * Creates a new Exception object
     * @param node the model object whose treatment causes the problem
     * @param reason the reason
     */
    public InstantiatorException(AnnotatedEObject node, String reason){
        this.node = node;
        this.reason = reason;
    }
    
    public InstantiatorException(InstantiatorError[] errors){
        this.errors = errors;
    }
}
