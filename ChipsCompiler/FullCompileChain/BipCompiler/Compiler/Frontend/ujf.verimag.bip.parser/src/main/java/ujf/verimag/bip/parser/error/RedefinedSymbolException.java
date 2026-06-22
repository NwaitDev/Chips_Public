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

package ujf.verimag.bip.parser.error;

import org.antlr.runtime.tree.CommonTree;
import org.antlr.runtime.tree.TreeNodeStream;

import ujf.verimag.bip.error.message.ErrorCodeEnum;
import ujf.verimag.bip.metamodel.AnnotatedEObject;

/**
 * Exception used to describe a symbol redefinition in the BIP source code.
 */
public abstract class RedefinedSymbolException extends Bip2WalkerException {
    private static final long serialVersionUID = -2656864597688827617L;

    /**
     * The model object found guilty of redefinition
     */
    protected AnnotatedEObject previousDeclaration;
    
    /**
     * The symbol redefined
     */
    protected String symbol;
    
    /**
     * Get the redefined symbol name
     * @return the redefined symbol name
     */
    public String getSymbol() {
        return symbol;
    }

    /**
     * Get the previous declaration
     * @return the previous declaration
     */
    public AnnotatedEObject getPreviousDeclaration() {
        return previousDeclaration;
    }
    
    /**
     * An exception used to signal a generic symbol redefinition
     * @param input the input from the Tree Parser
     * @param start the tree node at which the error has been found 
     * @param previous the previous declaration found
     * @param symbol the type name redefined
     */
    public RedefinedSymbolException(TreeNodeStream input, CommonTree start,
            AnnotatedEObject previous, String symbol, ErrorCodeEnum errorcode) {
        super(input, start, errorcode);
        this.previousDeclaration = previous;
        this.symbol = symbol;
    }
}
