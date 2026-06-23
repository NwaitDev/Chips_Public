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

import bip2.ujf.verimag.bip.actionlang.*;
import bip2.ujf.verimag.bip.data.SubDataDeclarationReference;

public class StatementPrinter extends StatementWalker {
	private StringBuffer buffer;
	private static StatementPrinter printer;

	private  StatementPrinter() {
		walker = new ExpressionPrinter();
	}
	private class ExpressionPrinter extends ExpressionTreeWalker {
		protected void checkArgument(Expression ex) {
			if (ex == null) {
				throw new IllegalArgumentException("The provided argument is null!. So far produced:" + buffer);
			}
		}

		public void traverseValuedList(List<ValuedExpression> lst) {
			for (ValuedExpression e : lst) {
				traverseValued(e);
				buffer.append(", ");
			}
			buffer.setLength(buffer.length() - 2);
		}

		public void traverseFunction(FunctionCallExpression func) {
			buffer.append(func.getFunctionName()).append("(");
			traverseValuedList(func.getParameters());
			buffer.append(")");
		}

		public void traverseUnary(UnaryOpExpression uop) {
			buffer.append('(');
			switch (uop.getOperator()) {
			case PLUS: buffer.append("+"); break;
			case MINUS: buffer.append("-"); break;
			case LOGICAL_NOT: buffer.append("!"); break;
			case BWISE_NOT: buffer.append("~"); break;
			}
			traverseValued(uop.getOperand());
			buffer.append(')');
		}

		public void traverseBinary(BinaryOpExpression bop) {
			buffer.append('(');
			traverseValued(bop.getLeft());
			switch (bop.getOperator()) {
			case ADDITION: buffer.append(" + "); break;
			case SUBTRACTION: buffer.append(" - "); break;
			case MULTIPLICATION: buffer.append(" * "); break;
			case BWISE_AND: buffer.append(" & "); break;
			case BWISE_XOR: buffer.append(" ^ "); break;
			case BWISE_OR: buffer.append(" | "); break;
			case LOGICAL_AND: buffer.append(" && "); break;
			case LOGICAL_OR: buffer.append(" || "); break;
			case EQUAL: buffer.append(" == "); break;
			case NOT_EQUAL: buffer.append(" != "); break;
			case LESS_THAN: buffer.append(" < "); break;
			case GREATER_THAN: buffer.append(" > "); break;
			case LESS_THAN_OR_EQUAL: buffer.append(" <= "); break;
			case GREATER_THAN_OR_EQUAL: buffer.append(" >= "); break;
			case DIVISION: buffer.append(" / "); break;
			case MODULO: buffer.append(" % "); break;
			}
			traverseValued(bop.getRight());
			buffer.append(')');
		}

		public void traverseSubData(SubDataDeclarationReferenceExpression sub) {
			SubDataDeclarationReference ref = sub.getSubDataDeclarationRef();
			if (ref.getComponentDeclaration() != null) {
				buffer.append(ref.getComponentDeclaration().getName());
			} else {
				buffer.append(ref.getPortDeclaration().getName());
			}
			buffer.append(".");
			buffer.append(ref.getForwardDataDeclaration().getName());
		}
		
		public void traverseDirectBoolean(DirectBooleanExpression val) {
			if (val.isValue()) {
				buffer.append("true");
			}
			else {
				buffer.append("false");
			}
		}
		
		public void traverseDirectInteger(DirectIntegerExpression val) {
			buffer.append(val.getValue());
		}
		
		public void traverseDirectFloat(DirectFloatExpression val) {
			buffer.append(val.getValue());
		}
		
		public void traverseDirectString(DirectStringExpression val) {
			buffer.append(val.getValue());
		}
		
		public void traverseDirectData(DirectDataDeclarationReferenceExpression ex) {
			buffer.append(ex.getDataDeclaration().getName());
		}
	}

	public static String printExpression(Expression ex) {
		if (printer == null) {
			printer = new StatementPrinter();
		}
		printer.buffer = new StringBuffer();
		if (ex instanceof ValuedExpression) {
			printer.walker.traverseValued((ValuedExpression) ex);
		} else {
			printer.traverseExpression(ex);
		}
		return printer.buffer.toString();
	}

	public void traverseExpressionList(List<Expression> lst) {
        for (Expression e : lst) {
            traverseExpression(e);
			buffer.append(";\n");
        }
    }

    public void traverseIf(IfThenElseExpression ife) {
		buffer.append("if (");
        walker.traverseValued(ife.getCondition());
		buffer.append(") {\n");
        traverseExpressionList(ife.getThen());
		if (!ife.getElse().isEmpty()) {
			buffer.append("} else {\n");
			traverseExpressionList(ife.getElse());
		}
		buffer.append("\n}\n");
    }

    public void traverseAssignement(AssignmentExpression aex) {
		walker.traverseValued(aex.getLhs());
		buffer.append(" = ");
		walker.traverseValued(aex.getRhs());
    }

}
