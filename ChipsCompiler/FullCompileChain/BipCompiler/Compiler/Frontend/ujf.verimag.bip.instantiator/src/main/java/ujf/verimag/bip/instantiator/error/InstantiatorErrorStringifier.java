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

import java.io.File;
import java.io.IOException;

import org.eclipse.emf.common.util.Diagnostic;

import ujf.verimag.bip.error.AbstractErrorStringifier;
import ujf.verimag.bip.error.GenericError;

public class InstantiatorErrorStringifier extends AbstractErrorStringifier {

    public InstantiatorErrorStringifier(File file) throws IOException {
        super(file);
    }

    public InstantiatorErrorStringifier(String string) throws IOException {
        super(string);
    }
    

    /**
     * Based on the error type, builds a human readable error message with
     * context from this diagnostic error
     * 
     * @param error
     *            the diagnostic error
     * @return the error message
     */
    public String stringify(InstantiatorDiagnosticError error){
        Diagnostic d = error.getDiagnostic();
        StringBuffer sb = new StringBuffer();

        if (error.getSourceFile() != null){
            sb.append("In " + error.getSourceFile().getPath() + ":\n");
        }

        String message = d.getMessage();
        String specific = getSpecificErrorMessage(error.errorcode);
        if (specific == null){
            // do not retrieve default message. Better force the correct classification of the error
            message = "[Error not correctly classified, defaulting to internal message, complain to devs]" + message;
        } else {
            message = specific;
        }
        
        sb.append(message + " :\n");
        sb.append(getContext(error));
        sb.append("\n");
        
        return sb.toString();
    }
    
    @Override
    public String stringify(GenericError error) {
        if (error instanceof InstantiatorDiagnosticError){
            return this.stringify((InstantiatorDiagnosticError)error);
        } else if (error instanceof InstantiatorError){
            return this.stringify((InstantiatorError)error);
        }
        return null;
    }

}
