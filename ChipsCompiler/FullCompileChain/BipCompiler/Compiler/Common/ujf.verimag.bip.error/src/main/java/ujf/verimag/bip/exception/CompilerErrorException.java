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

package ujf.verimag.bip.exception;

import ujf.verimag.bip.error.GenericError;

/**
 * Exception used when a bug in the compiler has been found.
 * Instances of this class should not be catched but for
 * informing the user that the compiler has crashed !
 */
public class CompilerErrorException extends RuntimeException {
    private static final long serialVersionUID = 2018060003335214639L;
    
    public final GenericError error;
    public final Exception cause;
    
    public CompilerErrorException() {
        this (null, null);
    }

    public CompilerErrorException(Exception cause) {
        this(null, cause);
    }

    public CompilerErrorException(GenericError error) {
        this(error, null);
    }

    public CompilerErrorException(GenericError error, Exception cause) {
        this.error = error;
        this.cause = cause;
    }
}
