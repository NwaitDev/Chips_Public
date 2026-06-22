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

import org.eclipse.emf.common.util.Diagnostic;

import bip2.ujf.verimag.bip.instance.ComponentInstance;
import bip2.ujf.verimag.bip.instance.CompoundPriorityInstance;
import bip2.ujf.verimag.bip.instance.ConnectorInstance;
import bip2.ujf.verimag.bip.instance.DataInstance;
import bip2.ujf.verimag.bip.instance.PortInstance;
import bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration;

import ujf.verimag.bip.error.message.ErrorCodeEnum;
import ujf.verimag.bip.error.message.ErrorSeverity;
import ujf.verimag.bip.metamodel.AnnotatedEObject;


/**
 * In major part, this is a copy/paste from 
 * ujf.verimag.bip.parser.error.DiagnosticError;
 */
public class InstantiatorDiagnosticError extends InstantiatorError {

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
    /**
     * Builds an error from a diagnostic
     * 
     * @param diagnostic
     *            the diagnostic describing the error
     */
    public InstantiatorDiagnosticError(Diagnostic diagnostic) {
        this.errorcode = (ErrorCodeEnum) diagnostic.getData().get(1);
        this.severity = diagnosticSeverityToErrorSeverity(diagnostic.getSeverity());
        
        AnnotatedEObject o = (AnnotatedEObject)diagnostic.getData().get(0);
        
        if (o instanceof ComponentInstance){
            this.line = ((ComponentInstance) o).getDeclaration().getLineStart();
            this.columnStart = ((ComponentInstance) o).getDeclaration().getColStart();
            this.setSourceFile(((ComponentInstance) o).getDeclaration().getSourceURL());
        } else if (o instanceof DataInstance) {
            this.line = ((DataInstance) o).getDeclaration().getLineStart();
            this.columnStart = ((DataInstance) o).getDeclaration().getColStart();
            this.setSourceFile(((DataInstance) o).getDeclaration().getSourceURL());

        } else if (o instanceof PortInstance){
            this.line = ((PortInstance) o).getDeclaration().getLineStart();
            this.columnStart = ((PortInstance) o).getDeclaration().getColStart();
            this.setSourceFile(((PortInstance) o).getDeclaration().getSourceURL());

        } else if (o instanceof ConnectorInstance) {
            this.line = ((ConnectorInstance) o).getDeclaration().getLineStart();
            this.columnStart = ((ConnectorInstance) o).getDeclaration().getColStart();
            this.setSourceFile(((ConnectorInstance) o).getDeclaration().getSourceURL());

        } else if (o instanceof CompoundPriorityInstance){
            this.line = ((CompoundPriorityInstance) o).getDeclaration().getLineStart();
            this.columnStart = ((CompoundPriorityInstance) o).getDeclaration().getColStart();
            this.setSourceFile(((CompoundPriorityInstance) o).getDeclaration().getSourceURL());
        } else {
            this.line = -1;
            this.columnStart = -1;
            this.setSourceFile(null);
        }

        this.diagnostic = diagnostic;
    }
}
