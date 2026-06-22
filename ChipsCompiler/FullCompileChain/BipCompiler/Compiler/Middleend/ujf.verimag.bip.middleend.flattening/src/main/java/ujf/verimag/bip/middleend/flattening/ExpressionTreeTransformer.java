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
import org.eclipse.emf.ecore.util.EcoreUtil;

/**
 * Traverses and modifies an expression tree. This class defines the
 * traversal mechanism and modifications are performed in place,
 * e.g. the original expression object is modified by the
 * traversal. Defined methods return null if the argument
 * sub-expression should be removed from the expression tree.
 */
public class ExpressionTreeTransformer {
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
	public List<ValuedExpression> traverseValuedList(List<ValuedExpression> lst) {
		List<ValuedExpression> result = new ArrayList<ValuedExpression>();
		for (ValuedExpression e : lst) {
			ValuedExpression res = traverseValued(e);
			if (res != null) {
				result.add(res);
			}
		}
		return result;
	}

	/**
	 * Probagates the traversal of a ValuedExpression to the method
	 * responsible for handling the specific expression class.
	 * @return the value returned by the method handling the concrete
	 * expression type or fails with an assertion error if the
	 * expression type is unknown.
	 */
	public ValuedExpression traverseValued(ValuedExpression ex) {
		checkArgument(ex);
		if (ex instanceof UnaryOpExpression) {
			return traverseUnary((UnaryOpExpression) ex);
		}
		if (ex instanceof BinaryOpExpression) {
			return traverseBinary((BinaryOpExpression) ex);
		}
		if (ex instanceof DirectBooleanExpression) {
			return traverseDirectBoolean((DirectBooleanExpression) ex);
		}
		if (ex instanceof DirectIntegerExpression) {
			return traverseDirectInteger((DirectIntegerExpression) ex);
		}
		if (ex instanceof DirectFloatExpression) {
			return traverseDirectFloat((DirectFloatExpression) ex);
		}
		if (ex instanceof DirectStringExpression) {
			return traverseDirectString((DirectStringExpression) ex);
		}
		if (ex instanceof FunctionCallExpression) {
			return traverseFunction((FunctionCallExpression) ex);
		}
		if (ex instanceof DirectDataDeclarationReferenceExpression) {
			return traverseDirectData((DirectDataDeclarationReferenceExpression) ex);
		}
		if (ex instanceof SubDataDeclarationReferenceExpression) {
			return traverseSubData((SubDataDeclarationReferenceExpression) ex);
		}
		assert(false);
		return null;
	}


	public ValuedExpression traverseFunction(FunctionCallExpression func) {
		FunctionCallExpression result = ActionlangFactory.eINSTANCE.createFunctionCallExpression();
		result.setFunctionName(func.getFunctionName());
		result.getParameters().addAll(traverseValuedList(func.getParameters()));
		return result;
	}

	public ValuedExpression traverseUnary(UnaryOpExpression uop) {
		ValuedExpression res = traverseValued(uop.getOperand());
		if (res == null) {
			return null;
		}
		UnaryOpExpression result = ActionlangFactory.eINSTANCE.createUnaryOpExpression();
		result.setOperator(uop.getOperator());
		result.setOperand(res);
		return result;
	}

	public ValuedExpression traverseBinary(BinaryOpExpression bop) {
		ValuedExpression left = traverseValued(bop.getLeft());
		ValuedExpression right = traverseValued(bop.getRight());
		if (left != null && right != null) {
			BinaryOpExpression result = ActionlangFactory.eINSTANCE.createBinaryOpExpression();
			result.setOperator(bop.getOperator());
			result.setLeft(left);
			result.setRight(right);
			return result;
		} else if (left != null) {
			return left;
		} else {
			return right;
		}
	}

	public ValuedExpression traverseSubData(SubDataDeclarationReferenceExpression sub) {
		return EcoreUtil.copy(sub);
	}
	
	public ValuedExpression traverseDirectBoolean(DirectBooleanExpression sub) {
		return EcoreUtil.copy(sub);
	}

	public ValuedExpression traverseDirectInteger(DirectIntegerExpression sub) {
		return EcoreUtil.copy(sub);
	}
	
	public ValuedExpression traverseDirectFloat(DirectFloatExpression sub) {
		return EcoreUtil.copy(sub);
	}

	public ValuedExpression traverseDirectString(DirectStringExpression sub) {
		return EcoreUtil.copy(sub);
	}

	public ValuedExpression traverseDirectData(DirectDataDeclarationReferenceExpression ex) {
		DirectDataDeclarationReferenceExpression result =
			ActionlangFactory.eINSTANCE.createDirectDataDeclarationReferenceExpression();
		result.setDataDeclaration(EcoreUtil.copy(ex.getDataDeclaration()));
		return result;
	}
}
