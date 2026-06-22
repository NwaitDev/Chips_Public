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

package ujf.verimag.bip.instantiator.error;

import ujf.verimag.bip.error.GenericError;
import ujf.verimag.bip.error.message.ErrorCodeEnum;
import ujf.verimag.bip.error.message.ErrorSeverity;
import ujf.verimag.bip.instantiator.InstantiatorException;

/**
 * Error class used to wrap an error that occurred within the instantiator.
 * Usually, denotes a bug in the instantiator.
 */
public class InstantiatorError extends GenericError {

    // keep it for potential future use.
    /**
     * This exception is, currently, only stored. It is the cause
     * of the error but is not used yet.
     */
    @SuppressWarnings("unused")
    private InstantiatorException exception;

    protected InstantiatorError(){
    }
    
    /**
     * Creates a new error
     * @param ie the exception that triggered the error.
     */
    public InstantiatorError(InstantiatorException ie) {
        super(ie.getNode().getLineStart(), ie.getNode().getColStart(),ie.getNode().getColStop(),
                ErrorCodeEnum.GenericDefault, ErrorSeverity.FATAL);
        this.setSourceFile(ie.getNode().getSourceURL());
        this.exception = ie;
    }

//    public InstantiatorError(int lineStart, int colStart, int colStop,
//            ErrorCodeEnum errorCodeEnum,
//            ErrorSeverity diagnosticSeverityToErrorSeverity) {
//        super(lineStart, colStart, colStop, errorCodeEnum, diagnosticSeverityToErrorSeverity);
//    }
//
//    public InstantiatorError(int lineStart, int colStart,
//            ErrorCodeEnum errorCodeEnum,
//            ErrorSeverity diagnosticSeverityToErrorSeverity) {
//        super(lineStart, colStart, errorCodeEnum, diagnosticSeverityToErrorSeverity);
//    }
//    /**
//     * Builds an error from a faulty AnnotatedEObject
//     * @param object the faulty object
//     * @param code the error code corresponding to the error
//     * @param severity the error severity
//     */
//    public InstantiatorError(AnnotatedEObject object, ErrorCodeEnum code, ErrorSeverity severity){
//       super(object, code, severity);
//    }
}
