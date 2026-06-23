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
 * Exception used when the error does not fit in any other class.
 * It is "low level". Abusing this exception prevents a correct interface
 * between compiler and UIs, as everything get encoded in the string message.
 * Only use this in last resort.
 */
public class GenericWalkerErrorException extends Bip2WalkerException {
    /**
     * The faulty model object that caused this exception.
     */
    final protected AnnotatedEObject faultyObject;
    
    /**
     * Get the object causing the error
     * @return the faulty object
     */
    public AnnotatedEObject getFaultyObject() {
        return faultyObject;
    }


    /**
     * 
     * @param input the input from the Tree Parser
     * @param start the tree node at which the error has been found
     * @param faulty the faulty object causing the error
     * @param message the message to be displayed somehow to the user
     */
    public GenericWalkerErrorException(TreeNodeStream input, CommonTree start, AnnotatedEObject faulty, ErrorCodeEnum errorcode) {
        super(input, start, errorcode);
        this.faultyObject = faulty;
    }

    private static final long serialVersionUID = 1L;
}
