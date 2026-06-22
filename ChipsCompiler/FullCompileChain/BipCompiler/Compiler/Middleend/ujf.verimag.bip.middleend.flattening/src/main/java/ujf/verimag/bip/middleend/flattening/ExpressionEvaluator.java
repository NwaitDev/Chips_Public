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

import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Set;
import java.util.HashSet;
import bip2.ujf.verimag.bip.actionlang.*;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import org.eclipse.emf.ecore.util.EcoreUtil;

public class ExpressionEvaluator extends StatementWalker {
	Map<String, ValuedExpression> context;
	ValuedExpression condition = null;
	Set<ExpressionEvaluator> children;
	private ExpressionTreeTransformer transformer;

	public ExpressionEvaluator() {
		this(null);
	};

	public ExpressionEvaluator(Map<String, ValuedExpression> papa) {
		transformer = new ExpressionTreeTransformer() {
				public ValuedExpression traverseDirectData(DirectDataDeclarationReferenceExpression ex) {
					ValuedExpression result =  context.get(ex.getDataDeclaration().getName());
					if (result == null) {
						StringBuffer sb = new StringBuffer();
						for (String key : context.keySet()) {
							sb.append(", ").append(key);
						}
						String msg = "Variable:"
							+ ex.getDataDeclaration().getName()
							+ " has no assigned value.";
						if (sb.length() == 0) {
							msg += " There are no defined variables";
						} else {
							msg += " The known variables are:"
								+ sb.substring(2);
						}
						throw new IllegalArgumentException(msg);
					}
					return result;
				}
			};
		context = new HashMap<String, ValuedExpression>();
		if (papa != null) {
			for (String key : papa.keySet()) {
				context.put(key, EcoreUtil.copy(papa.get(key)));
			}
		}
		this.children = new HashSet<ExpressionEvaluator>();
	}

	public Set<ExpressionEvaluator> getPaths() {
		if (children.isEmpty()) {
			Set<ExpressionEvaluator> result = new HashSet<ExpressionEvaluator>();
			result.add(this);
			return result;
		}
		return children;
	}

	public void traverseExpressionList(List<Expression> lst) {
		for (Expression ex : lst) {
			if (children.isEmpty()) {
				traverseExpression(ex);
			} else {
				for (ExpressionEvaluator ev : new HashSet<ExpressionEvaluator>(children)) {
					ev.traverseExpression(ex);
					if (!ev.children.isEmpty()) {
						children.addAll(ev.children);
						children.remove(ev);
					}
				}
			}
		}
	}

	public void traverseExpression(Expression ex) {
		if (ex instanceof ValuedExpression) {
			transformer.traverseValued((ValuedExpression) ex);
		} else {
			super.traverseExpression(ex);
		}
	}
		
	public void  traverseAssignement(AssignmentExpression aex) {
		if (aex.getLhs() instanceof DirectDataDeclarationReferenceExpression) {
			DirectDataDeclarationReferenceExpression left =
					(DirectDataDeclarationReferenceExpression) aex.getLhs();
			DataDeclaration data = left.getDataDeclaration();
			ValuedExpression last = transformer.traverseValued(aex.getRhs());
			context.put(data.getName(), last);
		}
	}


	private void  evalPart(ValuedExpression guard, boolean negate,
						   List<Expression> statements) {
		if (statements.isEmpty()) {
			return;
		}
		ExpressionEvaluator evaluator = new ExpressionEvaluator(context);
		children.add(evaluator);
		if (negate) {
			UnaryOpExpression neg = 
				ActionlangFactory.eINSTANCE.createUnaryOpExpression();
			neg.setOperator(UnaryOperators.LOGICAL_NOT);
			neg.setOperand(EcoreUtil.copy(guard));
			guard = neg;
		}
		if (condition != null) {
			BinaryOpExpression bop =
				ActionlangFactory.eINSTANCE.createBinaryOpExpression();
			bop.setOperator(BinaryOperators.LOGICAL_AND);
			//need to copy the condition because left is a containment
			//and the same condition may be composed with other
			//sub-evaluators (e.g else part or an other if)
			bop.setLeft(EcoreUtil.copy(condition));
			bop.setRight(guard);
			evaluator.condition = bop;
		} else {
			evaluator.condition = guard;
		}
		evaluator.traverseExpressionList(statements);
	}

	public void traverseIf(IfThenElseExpression ife) {
		ValuedExpression guard = transformer.traverseValued(ife.getCondition());
		if (ife.getThen().isEmpty() && ife.getElse().isEmpty()) {
			return;
		}
		evalPart(guard, false, ife.getThen());
		evalPart(guard, true, ife.getElse());
	}
}
