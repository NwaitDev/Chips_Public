/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
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

package ujf.verimag.bip.parser.error;

import java.util.Map;
import java.util.Set;

import org.eclipse.emf.common.util.Diagnostic;

import bip2.ujf.verimag.bip.annotation.AnnotatedElement;
import bip2.ujf.verimag.bip.annotation.BipAnnotation;

import ujf.verimag.bip.error.GenericError;
import ujf.verimag.bip.error.message.ErrorCodeEnum;
import ujf.verimag.bip.error.message.ErrorSeverity;
import ujf.verimag.bip.metamodel.AnnotatedEObject;
import org.eclipse.emf.ecore.EObject;

/**
 * This class describes error caused by a validation error from the validation
 * framework of EMF.
 */
public class DiagnosticError extends GenericError {

    /**
     * Maps Diagnostic severity to our own severity levels. Defaults to FATAL,
     * except for some cases (currently, WARNING)
     * 
     * @param diagSeverity
     *            diagnostic from a Diagnostic object
     * @return
     */
    private static ErrorSeverity diagnosticSeverityToErrorSeverity(
            int diagSeverity) {
        if (diagSeverity == Diagnostic.WARNING)
            return ErrorSeverity.WARNING;
        else
            return ErrorSeverity.FATAL;
    }

    /**
     * The diagnostic object returned by the EMF framework for describing the
     * validation error found.
     */
    private Diagnostic diagnostic;

    /**
     * Returns the diagnostic describing the error
     * 
     * @return the diagnostic
     */
    public Diagnostic getDiagnostic() {
        return diagnostic;
    }

    private static boolean shouldBeSilenced(AnnotatedEObject o, Diagnostic diagnostic){
        EObject objectToCheck = o;

        while (objectToCheck != null) {
            if (objectToCheck instanceof AnnotatedElement){
                AnnotatedElement ae = (AnnotatedElement) objectToCheck;
                BipAnnotation ba = ae.getBipAnnotations().get("SuppressWarning");

                if (ba != null){
                    final ErrorCodeEnum errorInternalCode = (ErrorCodeEnum) diagnostic.getData().get(1);

                    for (String userFriendlyName : ba.getParameters().keySet()){
                        final Set<ErrorCodeEnum> internalCodes = ErrorCodeEnum.userFriendlyNames.get(userFriendlyName);
                        
                        if (internalCodes != null) {
                            if (internalCodes.contains(errorInternalCode)) {
                                return true;
                            }
                        }
                    }
                }
            }

            // check also all containers recursively
            objectToCheck = objectToCheck.eContainer();
        }
        return false;
    }

    /**
     * Builds an error from a diagnostic
     * 
     * @param diagnostic
     *            the diagnostic describing the error
     */
    public DiagnosticError(Diagnostic diagnostic) {
        super(((AnnotatedEObject) diagnostic.getData().get(0)).getLineStart(), 
                ((AnnotatedEObject) diagnostic.getData().get(0)).getColStart(),
                ((AnnotatedEObject) diagnostic.getData().get(0)).getColStop(),
                (ErrorCodeEnum) diagnostic.getData().get(1),
                diagnosticSeverityToErrorSeverity(diagnostic.getSeverity()),
                shouldBeSilenced(((AnnotatedEObject) diagnostic.getData().get(0)), diagnostic));
        this.setSourceFile(((AnnotatedEObject) diagnostic.getData().get(0)).getSourceURL());
        this.setSourceStringBuffer(((AnnotatedEObject) diagnostic.getData().get(0)).getSourceStringBuffer());

        this.diagnostic = diagnostic;
    }

}
