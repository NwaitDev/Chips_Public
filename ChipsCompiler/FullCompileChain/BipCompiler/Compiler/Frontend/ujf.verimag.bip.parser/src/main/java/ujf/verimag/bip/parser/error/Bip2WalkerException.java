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

import org.antlr.runtime.RecognitionException;
import org.antlr.runtime.tree.CommonTree;
import org.antlr.runtime.tree.TreeNodeStream;

import ujf.verimag.bip.error.message.ErrorCodeEnum;

/**
 * Super Exception raised by the walker. It must extends RecognitionException from
 * antlr to be usable within antlr.
 */
public abstract class Bip2WalkerException extends RecognitionException {
    /**
     * Stores the start of the error. Not to be used directly.
     */
    protected CommonTree start;
	
    private static final long serialVersionUID = 3635521266005380297L;
    
    protected final ErrorCodeEnum errorcode;
    
    /**
     * Creates a new Exception object
     * @param input the tree input which caused the problem
     * @param start the tree node denoting the start of the error.
     */
    public Bip2WalkerException(TreeNodeStream input, CommonTree start, ErrorCodeEnum errorcode){
        super(input);
        this.errorcode = errorcode;
        this.start = start;
    }
}
