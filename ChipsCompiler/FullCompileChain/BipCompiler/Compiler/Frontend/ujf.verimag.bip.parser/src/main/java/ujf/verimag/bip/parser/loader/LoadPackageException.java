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

package ujf.verimag.bip.parser.loader;

import ujf.verimag.bip.error.GenericError;

/**
 * Exception used by the Package Loader when an error is encountered
 */
public class LoadPackageException extends Exception {
    private static final long serialVersionUID = 1L;

    /**
     * Creates a new exception with the given error message
     * @param message the error message
     */
    public LoadPackageException(String message) {
        super(message);
    }

    /**
     * Creates a new exception and use the given throwable as the cause
     * @param cause the throwable that caused the error
     */
    public LoadPackageException(Throwable cause){
        super(cause);
    }
    
    /**
     * Creates a new exception with a given message and throwable cause
     * @param message the message
     * @param cause the cause
     */
    public LoadPackageException(String message,
            Throwable cause){
        super(message,cause);
    }
    
    /**
     * The array of errors that caused this exception
     */
    private GenericError[] errors;
    
    /**
     * Get the errors that caused this exception
     * @return the array of errors
     */
    public GenericError[] getErrors() {
        if (errors == null) errors = new GenericError[0];
        return errors;
    }

    /**
     * Creates an exception and attaches the error array as the cause.
     * @param errors the errors causing the exception.
     */
    public LoadPackageException(GenericError[] errors){
        this.errors = errors;
    }
}