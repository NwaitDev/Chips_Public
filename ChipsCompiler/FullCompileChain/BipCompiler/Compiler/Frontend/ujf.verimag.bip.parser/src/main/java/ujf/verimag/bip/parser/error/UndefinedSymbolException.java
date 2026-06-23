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

/**
 * Exception used when a symbol is unexpectedly undefined.
 */
public abstract class UndefinedSymbolException extends Bip2WalkerException {
    private static final long serialVersionUID = -1646640279620722882L;

    /**
     * The name that is not defined
     */
    private String undefinedName;
    
    /**
     * Creates a new Exception for a undefined symbol.
     * @param input the input at which the undefined symbol was found
     * @param start the start of the tree node where the symbol is undefined
     * @param name the name of the undefined symbol
     */
    public UndefinedSymbolException(TreeNodeStream input, CommonTree start, String name, ErrorCodeEnum errorcode) {
        super(input, start, errorcode);
        this.undefinedName = name;
    }

    /**
     * Get the undefined name
     * @return the undefined name
     */
    public String getUndefinedName() {
        return undefinedName;
    }
}
