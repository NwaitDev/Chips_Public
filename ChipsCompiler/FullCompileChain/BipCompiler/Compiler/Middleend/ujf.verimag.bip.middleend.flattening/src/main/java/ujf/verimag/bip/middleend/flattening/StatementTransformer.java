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

public class StatementTransformer {
	protected ExpressionTreeTransformer transformer;

	public void setExpressionTransformer(ExpressionTreeTransformer transformer) {
		this.transformer = transformer;
	}

	protected void checkArgument(Expression ex) {
		if (ex == null) {
			throw new IllegalArgumentException("The provided argument is null!");
		}
	}

	/**
	 * Applies a transormation on each element of the provided
	 * list. After the method completes, the list contains all
	 * elements for which traverseExpression returned a value.
	 * @param statements a list of statements
	 * @return a list of transformed statements
	 */
	public List<Expression> traverseExpressionList(List<Expression> statements) {
		List<Expression> result = new ArrayList<Expression>();
		for (Expression e : statements) {
			Expression res = traverseExpression(e);
			if (res != null) {
				result.add(res);
			}
		}
		return result;
	}		

	/**
	 * Probagates the traversal of an Expression to the method
	 * responsible for handling the specific expression class.
	 * @return the value returned by the method handling the concrete
	 * expression type.
	 * @throws IllegalArgumentException if the expression class is
	 * unknown or the expression object is null
	 */
	public Expression traverseExpression(Expression ex) {
		checkArgument(ex);
		if (ex instanceof ValuedExpression) {
			return transformer.traverseValued((ValuedExpression) ex);
		}
		if (ex instanceof IfThenElseExpression) {
			return traverseIf((IfThenElseExpression) ex);
		}
		if (ex instanceof AssignmentExpression) {
			return traverseAssignement((AssignmentExpression) ex);
		}
		throw new IllegalArgumentException("Unknown class:" + ex.getClass().getName());
	}

	/**
	 * Applies a transormation on the if condition and statements.
	 * @return null if the condition transormation results to null or
	 * a new if statement with the condition and statements
	 * transormed.
	 */
	public Expression traverseIf(IfThenElseExpression ife) {
		ValuedExpression guard = transformer.traverseValued(ife.getCondition());
		if (guard == null) {
			return null;
		}
		IfThenElseExpression result = ActionlangFactory.eINSTANCE.createIfThenElseExpression();
		result.setCondition(guard);
		result.getThen().addAll(traverseExpressionList(ife.getThen()));
		result.getElse().addAll(traverseExpressionList(ife.getElse()));
		return result;
	}

	/**
	 * Transorms an assignment statement.
	 * @return A function call if one of the transformed operands is
	 * null and the other is a function call. If both operands result
	 * to null, the method returns null. Finally, when both
	 * transofrmations are non null, it returns a new
	 * AssignmentExpression object with both operands transformed.
	 * @throws IllegalArgumentException if the transformation produces
	 * an invalid statement or if the left operand doesn;t have an
	 * associated value.
	 */
	public Expression traverseAssignement(AssignmentExpression aex) {
		ValuedExpression left =
			transformer.traverseValued(aex.getLhs());
		ValuedExpression right = transformer.traverseValued(aex.getRhs());
		if (left == null) {
			if (right instanceof FunctionCallExpression) {
				return right;
			} else if (right == null) {
				return null;
			} else {
				throw new IllegalArgumentException("Transformation is not a function.");
			}
		}
		AssignmentExpression result = ActionlangFactory.eINSTANCE.createAssignmentExpression();
		result.setRhs(right);

		if (!(left instanceof SubDataDeclarationReferenceExpression ||
				left instanceof DirectDataDeclarationReferenceExpression)) {
			throw new IllegalArgumentException("Left operand doesn't have a value.");
		}
		
		result.setLhs(left);
		
		return result;
	}
}
