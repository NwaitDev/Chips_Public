/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Anakreontas Mentis
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

package ujf.verimag.bip.middleend.flattening;

import bip2.ujf.verimag.bip.actionlang.*;
import java.util.List;
import java.util.ArrayList;

/**
 * Traverses and modifies an expression tree. This class defines the
 * traversal mechanism and modifications are performed in place,
 * e.g. the original expression object is modified by the
 * traversal. Defined methods return null if the argument
 * sub-expression should be removed from the expression tree.
 */
public class ExpressionTreeWalker {
	protected void checkArgument(Expression ex) {
		if (ex == null) {
			throw new IllegalArgumentException("The provided argument is null!");
		}
	}

	/**
	 * Applies a transormation on each element of the provided
	 * list. After the method completes, the list contains all
	 * elements for which traverseValued did not return null.
	 */
	public void traverseValuedList(List<ValuedExpression> lst) {
		for (ValuedExpression e : lst) {
			traverseValued(e);
		}
	}

	/**
	 * Probagates the traversal of a ValuedExpression to the method
	 * responsible for handling the specific expression class.
	 * @return the value returned by the method handling the concrete
	 * expression type or fails with an assertion error if the
	 * expression type is unknown.
	 */
	public void traverseValued(ValuedExpression ex) {
		checkArgument(ex);
		if (ex instanceof UnaryOpExpression) {
			traverseUnary((UnaryOpExpression) ex);
		} else if (ex instanceof BinaryOpExpression) {
			traverseBinary((BinaryOpExpression) ex);
		} else if (ex instanceof DirectBooleanExpression) {
			traverseDirectBoolean((DirectBooleanExpression) ex);
		} else if (ex instanceof DirectIntegerExpression) {
			traverseDirectInteger((DirectIntegerExpression) ex);
		} else if (ex instanceof DirectFloatExpression) {
			traverseDirectFloat((DirectFloatExpression) ex);
		} else if (ex instanceof DirectStringExpression) {
			traverseDirectString((DirectStringExpression) ex);
		} else if (ex instanceof FunctionCallExpression) {
			traverseFunction((FunctionCallExpression) ex);
		} else if (ex instanceof DirectDataDeclarationReferenceExpression) {
			traverseDirectData((DirectDataDeclarationReferenceExpression) ex);
		} else if (ex instanceof SubDataDeclarationReferenceExpression) {
			traverseSubData((SubDataDeclarationReferenceExpression) ex);
		} else {
			assert(false);
		}
	}


	public void traverseFunction(FunctionCallExpression func) {
		traverseValuedList(func.getParameters());
	}

	public void traverseUnary(UnaryOpExpression uop) {
		traverseValued(uop.getOperand());
	}

	public void traverseBinary(BinaryOpExpression bop) {
		traverseValued(bop.getLeft());
		traverseValued(bop.getRight());
	}

	public void traverseSubData(SubDataDeclarationReferenceExpression sub) {}
	
	public void traverseDirectBoolean(DirectBooleanExpression val) {}
	
	public void traverseDirectInteger(DirectIntegerExpression val) {}
	
	public void traverseDirectFloat(DirectFloatExpression val) {}
	
	public void traverseDirectString(DirectStringExpression val) {}
	
	public void traverseDirectData(DirectDataDeclarationReferenceExpression ex) {}
}
