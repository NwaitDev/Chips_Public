/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
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

package bip2.ujf.verimag.bip.actionlang;

import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EEnum;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EReference;

/**
 * <!-- begin-user-doc -->
 * The <b>Package</b> for the model.
 * It contains accessors for the meta objects to represent
 * <ul>
 *   <li>each class,</li>
 *   <li>each feature of each class,</li>
 *   <li>each enum,</li>
 *   <li>and each data type</li>
 * </ul>
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.actionlang.ActionlangFactory
 * @model kind="package"
 * @generated
 */
public interface ActionlangPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "actionlang";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/actionlang/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.actionlang";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    ActionlangPackage eINSTANCE = bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.Expression <em>Expression</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.Expression
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getExpression()
     * @generated
     */
    int EXPRESSION = 7;

    /**
     * The number of structural features of the '<em>Expression</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int EXPRESSION_FEATURE_COUNT = 0;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.impl.ValuedExpressionImpl <em>Valued Expression</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.impl.ValuedExpressionImpl
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getValuedExpression()
     * @generated
     */
    int VALUED_EXPRESSION = 2;

    /**
     * The number of structural features of the '<em>Valued Expression</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int VALUED_EXPRESSION_FEATURE_COUNT = EXPRESSION_FEATURE_COUNT + 0;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.impl.BinaryOpExpressionImpl <em>Binary Op Expression</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.impl.BinaryOpExpressionImpl
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getBinaryOpExpression()
     * @generated
     */
    int BINARY_OP_EXPRESSION = 0;

    /**
     * The feature id for the '<em><b>Operator</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BINARY_OP_EXPRESSION__OPERATOR = VALUED_EXPRESSION_FEATURE_COUNT + 0;

    /**
     * The feature id for the '<em><b>Left</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BINARY_OP_EXPRESSION__LEFT = VALUED_EXPRESSION_FEATURE_COUNT + 1;

    /**
     * The feature id for the '<em><b>Right</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BINARY_OP_EXPRESSION__RIGHT = VALUED_EXPRESSION_FEATURE_COUNT + 2;

    /**
     * The number of structural features of the '<em>Binary Op Expression</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BINARY_OP_EXPRESSION_FEATURE_COUNT = VALUED_EXPRESSION_FEATURE_COUNT
            + 3;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.impl.UnaryOpExpressionImpl <em>Unary Op Expression</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.impl.UnaryOpExpressionImpl
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getUnaryOpExpression()
     * @generated
     */
    int UNARY_OP_EXPRESSION = 1;

    /**
     * The feature id for the '<em><b>Operator</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int UNARY_OP_EXPRESSION__OPERATOR = VALUED_EXPRESSION_FEATURE_COUNT + 0;

    /**
     * The feature id for the '<em><b>Operand</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int UNARY_OP_EXPRESSION__OPERAND = VALUED_EXPRESSION_FEATURE_COUNT + 1;

    /**
     * The number of structural features of the '<em>Unary Op Expression</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int UNARY_OP_EXPRESSION_FEATURE_COUNT = VALUED_EXPRESSION_FEATURE_COUNT + 2;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.impl.SubDataDeclarationReferenceExpressionImpl <em>Sub Data Declaration Reference Expression</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.impl.SubDataDeclarationReferenceExpressionImpl
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getSubDataDeclarationReferenceExpression()
     * @generated
     */
    int SUB_DATA_DECLARATION_REFERENCE_EXPRESSION = 3;

    /**
     * The feature id for the '<em><b>Sub Data Declaration Ref</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int SUB_DATA_DECLARATION_REFERENCE_EXPRESSION__SUB_DATA_DECLARATION_REF = VALUED_EXPRESSION_FEATURE_COUNT
            + 0;

    /**
     * The number of structural features of the '<em>Sub Data Declaration Reference Expression</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int SUB_DATA_DECLARATION_REFERENCE_EXPRESSION_FEATURE_COUNT = VALUED_EXPRESSION_FEATURE_COUNT
            + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.impl.DirectDataDeclarationReferenceExpressionImpl <em>Direct Data Declaration Reference Expression</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.impl.DirectDataDeclarationReferenceExpressionImpl
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getDirectDataDeclarationReferenceExpression()
     * @generated
     */
    int DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION = 4;

    /**
     * The feature id for the '<em><b>Data Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION__DATA_DECLARATION = VALUED_EXPRESSION_FEATURE_COUNT
            + 0;

    /**
     * The number of structural features of the '<em>Direct Data Declaration Reference Expression</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION_FEATURE_COUNT = VALUED_EXPRESSION_FEATURE_COUNT
            + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.impl.AssignmentExpressionImpl <em>Assignment Expression</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.impl.AssignmentExpressionImpl
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getAssignmentExpression()
     * @generated
     */
    int ASSIGNMENT_EXPRESSION = 5;

    /**
     * The feature id for the '<em><b>Lhs</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ASSIGNMENT_EXPRESSION__LHS = EXPRESSION_FEATURE_COUNT + 0;

    /**
     * The feature id for the '<em><b>Rhs</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ASSIGNMENT_EXPRESSION__RHS = EXPRESSION_FEATURE_COUNT + 1;

    /**
     * The number of structural features of the '<em>Assignment Expression</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ASSIGNMENT_EXPRESSION_FEATURE_COUNT = EXPRESSION_FEATURE_COUNT + 2;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.impl.FunctionCallExpressionImpl <em>Function Call Expression</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.impl.FunctionCallExpressionImpl
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getFunctionCallExpression()
     * @generated
     */
    int FUNCTION_CALL_EXPRESSION = 6;

    /**
     * The feature id for the '<em><b>Parameters</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int FUNCTION_CALL_EXPRESSION__PARAMETERS = VALUED_EXPRESSION_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>Function Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int FUNCTION_CALL_EXPRESSION__FUNCTION_NAME = VALUED_EXPRESSION_FEATURE_COUNT
            + 1;

    /**
     * The number of structural features of the '<em>Function Call Expression</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int FUNCTION_CALL_EXPRESSION_FEATURE_COUNT = VALUED_EXPRESSION_FEATURE_COUNT
            + 2;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.impl.ValuedReferenceExpressionImpl <em>Valued Reference Expression</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.impl.ValuedReferenceExpressionImpl
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getValuedReferenceExpression()
     * @generated
     */
    int VALUED_REFERENCE_EXPRESSION = 8;

    /**
     * The feature id for the '<em><b>Expression Reference</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int VALUED_REFERENCE_EXPRESSION__EXPRESSION_REFERENCE = VALUED_EXPRESSION_FEATURE_COUNT
            + 0;

    /**
     * The number of structural features of the '<em>Valued Reference Expression</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int VALUED_REFERENCE_EXPRESSION_FEATURE_COUNT = VALUED_EXPRESSION_FEATURE_COUNT
            + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.impl.DirectBooleanExpressionImpl <em>Direct Boolean Expression</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.impl.DirectBooleanExpressionImpl
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getDirectBooleanExpression()
     * @generated
     */
    int DIRECT_BOOLEAN_EXPRESSION = 9;

    /**
     * The feature id for the '<em><b>Value</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DIRECT_BOOLEAN_EXPRESSION__VALUE = VALUED_EXPRESSION_FEATURE_COUNT + 0;

    /**
     * The number of structural features of the '<em>Direct Boolean Expression</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DIRECT_BOOLEAN_EXPRESSION_FEATURE_COUNT = VALUED_EXPRESSION_FEATURE_COUNT
            + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.impl.IfThenElseExpressionImpl <em>If Then Else Expression</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.impl.IfThenElseExpressionImpl
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getIfThenElseExpression()
     * @generated
     */
    int IF_THEN_ELSE_EXPRESSION = 10;

    /**
     * The feature id for the '<em><b>Condition</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int IF_THEN_ELSE_EXPRESSION__CONDITION = EXPRESSION_FEATURE_COUNT + 0;

    /**
     * The feature id for the '<em><b>Then</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int IF_THEN_ELSE_EXPRESSION__THEN = EXPRESSION_FEATURE_COUNT + 1;

    /**
     * The feature id for the '<em><b>Else</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int IF_THEN_ELSE_EXPRESSION__ELSE = EXPRESSION_FEATURE_COUNT + 2;

    /**
     * The number of structural features of the '<em>If Then Else Expression</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int IF_THEN_ELSE_EXPRESSION_FEATURE_COUNT = EXPRESSION_FEATURE_COUNT + 3;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.impl.DirectIntegerExpressionImpl <em>Direct Integer Expression</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.impl.DirectIntegerExpressionImpl
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getDirectIntegerExpression()
     * @generated
     */
    int DIRECT_INTEGER_EXPRESSION = 11;

    /**
     * The feature id for the '<em><b>Value</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DIRECT_INTEGER_EXPRESSION__VALUE = VALUED_EXPRESSION_FEATURE_COUNT + 0;

    /**
     * The number of structural features of the '<em>Direct Integer Expression</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DIRECT_INTEGER_EXPRESSION_FEATURE_COUNT = VALUED_EXPRESSION_FEATURE_COUNT
            + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.impl.DirectFloatExpressionImpl <em>Direct Float Expression</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.impl.DirectFloatExpressionImpl
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getDirectFloatExpression()
     * @generated
     */
    int DIRECT_FLOAT_EXPRESSION = 12;

    /**
     * The feature id for the '<em><b>Value</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DIRECT_FLOAT_EXPRESSION__VALUE = VALUED_EXPRESSION_FEATURE_COUNT + 0;

    /**
     * The number of structural features of the '<em>Direct Float Expression</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DIRECT_FLOAT_EXPRESSION_FEATURE_COUNT = VALUED_EXPRESSION_FEATURE_COUNT
            + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.impl.DirectStringExpressionImpl <em>Direct String Expression</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.impl.DirectStringExpressionImpl
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getDirectStringExpression()
     * @generated
     */
    int DIRECT_STRING_EXPRESSION = 13;

    /**
     * The feature id for the '<em><b>Value</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DIRECT_STRING_EXPRESSION__VALUE = VALUED_EXPRESSION_FEATURE_COUNT + 0;

    /**
     * The number of structural features of the '<em>Direct String Expression</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DIRECT_STRING_EXPRESSION_FEATURE_COUNT = VALUED_EXPRESSION_FEATURE_COUNT
            + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.BinaryOperators <em>Binary Operators</em>}' enum.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.BinaryOperators
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getBinaryOperators()
     * @generated
     */
    int BINARY_OPERATORS = 14;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.actionlang.UnaryOperators <em>Unary Operators</em>}' enum.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.actionlang.UnaryOperators
     * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getUnaryOperators()
     * @generated
     */
    int UNARY_OPERATORS = 15;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.actionlang.BinaryOpExpression <em>Binary Op Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Binary Op Expression</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.BinaryOpExpression
     * @generated
     */
    EClass getBinaryOpExpression();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.actionlang.BinaryOpExpression#getOperator <em>Operator</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Operator</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.BinaryOpExpression#getOperator()
     * @see #getBinaryOpExpression()
     * @generated
     */
    EAttribute getBinaryOpExpression_Operator();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.actionlang.BinaryOpExpression#getLeft <em>Left</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Left</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.BinaryOpExpression#getLeft()
     * @see #getBinaryOpExpression()
     * @generated
     */
    EReference getBinaryOpExpression_Left();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.actionlang.BinaryOpExpression#getRight <em>Right</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Right</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.BinaryOpExpression#getRight()
     * @see #getBinaryOpExpression()
     * @generated
     */
    EReference getBinaryOpExpression_Right();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.actionlang.UnaryOpExpression <em>Unary Op Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Unary Op Expression</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.UnaryOpExpression
     * @generated
     */
    EClass getUnaryOpExpression();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.actionlang.UnaryOpExpression#getOperator <em>Operator</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Operator</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.UnaryOpExpression#getOperator()
     * @see #getUnaryOpExpression()
     * @generated
     */
    EAttribute getUnaryOpExpression_Operator();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.actionlang.UnaryOpExpression#getOperand <em>Operand</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Operand</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.UnaryOpExpression#getOperand()
     * @see #getUnaryOpExpression()
     * @generated
     */
    EReference getUnaryOpExpression_Operand();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.actionlang.ValuedExpression <em>Valued Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Valued Expression</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.ValuedExpression
     * @generated
     */
    EClass getValuedExpression();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression <em>Sub Data Declaration Reference Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Sub Data Declaration Reference Expression</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression
     * @generated
     */
    EClass getSubDataDeclarationReferenceExpression();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression#getSubDataDeclarationRef <em>Sub Data Declaration Ref</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Sub Data Declaration Ref</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression#getSubDataDeclarationRef()
     * @see #getSubDataDeclarationReferenceExpression()
     * @generated
     */
    EReference getSubDataDeclarationReferenceExpression_SubDataDeclarationRef();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression <em>Direct Data Declaration Reference Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Direct Data Declaration Reference Expression</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression
     * @generated
     */
    EClass getDirectDataDeclarationReferenceExpression();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression#getDataDeclaration <em>Data Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Data Declaration</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression#getDataDeclaration()
     * @see #getDirectDataDeclarationReferenceExpression()
     * @generated
     */
    EReference getDirectDataDeclarationReferenceExpression_DataDeclaration();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.actionlang.AssignmentExpression <em>Assignment Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Assignment Expression</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.AssignmentExpression
     * @generated
     */
    EClass getAssignmentExpression();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.actionlang.AssignmentExpression#getLhs <em>Lhs</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Lhs</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.AssignmentExpression#getLhs()
     * @see #getAssignmentExpression()
     * @generated
     */
    EReference getAssignmentExpression_Lhs();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.actionlang.AssignmentExpression#getRhs <em>Rhs</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Rhs</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.AssignmentExpression#getRhs()
     * @see #getAssignmentExpression()
     * @generated
     */
    EReference getAssignmentExpression_Rhs();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.actionlang.FunctionCallExpression <em>Function Call Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Function Call Expression</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.FunctionCallExpression
     * @generated
     */
    EClass getFunctionCallExpression();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.actionlang.FunctionCallExpression#getParameters <em>Parameters</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Parameters</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.FunctionCallExpression#getParameters()
     * @see #getFunctionCallExpression()
     * @generated
     */
    EReference getFunctionCallExpression_Parameters();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.actionlang.FunctionCallExpression#getFunctionName <em>Function Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Function Name</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.FunctionCallExpression#getFunctionName()
     * @see #getFunctionCallExpression()
     * @generated
     */
    EAttribute getFunctionCallExpression_FunctionName();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.actionlang.Expression <em>Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Expression</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.Expression
     * @generated
     */
    EClass getExpression();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.actionlang.ValuedReferenceExpression <em>Valued Reference Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Valued Reference Expression</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.ValuedReferenceExpression
     * @generated
     */
    EClass getValuedReferenceExpression();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.actionlang.ValuedReferenceExpression#getExpressionReference <em>Expression Reference</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Expression Reference</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.ValuedReferenceExpression#getExpressionReference()
     * @see #getValuedReferenceExpression()
     * @generated
     */
    EReference getValuedReferenceExpression_ExpressionReference();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.actionlang.DirectBooleanExpression <em>Direct Boolean Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Direct Boolean Expression</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.DirectBooleanExpression
     * @generated
     */
    EClass getDirectBooleanExpression();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.actionlang.DirectBooleanExpression#isValue <em>Value</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Value</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.DirectBooleanExpression#isValue()
     * @see #getDirectBooleanExpression()
     * @generated
     */
    EAttribute getDirectBooleanExpression_Value();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.actionlang.IfThenElseExpression <em>If Then Else Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>If Then Else Expression</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.IfThenElseExpression
     * @generated
     */
    EClass getIfThenElseExpression();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.actionlang.IfThenElseExpression#getCondition <em>Condition</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Condition</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.IfThenElseExpression#getCondition()
     * @see #getIfThenElseExpression()
     * @generated
     */
    EReference getIfThenElseExpression_Condition();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.actionlang.IfThenElseExpression#getThen <em>Then</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Then</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.IfThenElseExpression#getThen()
     * @see #getIfThenElseExpression()
     * @generated
     */
    EReference getIfThenElseExpression_Then();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.actionlang.IfThenElseExpression#getElse <em>Else</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Else</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.IfThenElseExpression#getElse()
     * @see #getIfThenElseExpression()
     * @generated
     */
    EReference getIfThenElseExpression_Else();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.actionlang.DirectIntegerExpression <em>Direct Integer Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Direct Integer Expression</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.DirectIntegerExpression
     * @generated
     */
    EClass getDirectIntegerExpression();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.actionlang.DirectIntegerExpression#getValue <em>Value</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Value</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.DirectIntegerExpression#getValue()
     * @see #getDirectIntegerExpression()
     * @generated
     */
    EAttribute getDirectIntegerExpression_Value();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.actionlang.DirectFloatExpression <em>Direct Float Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Direct Float Expression</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.DirectFloatExpression
     * @generated
     */
    EClass getDirectFloatExpression();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.actionlang.DirectFloatExpression#getValue <em>Value</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Value</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.DirectFloatExpression#getValue()
     * @see #getDirectFloatExpression()
     * @generated
     */
    EAttribute getDirectFloatExpression_Value();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.actionlang.DirectStringExpression <em>Direct String Expression</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Direct String Expression</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.DirectStringExpression
     * @generated
     */
    EClass getDirectStringExpression();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.actionlang.DirectStringExpression#getValue <em>Value</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Value</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.DirectStringExpression#getValue()
     * @see #getDirectStringExpression()
     * @generated
     */
    EAttribute getDirectStringExpression_Value();

    /**
     * Returns the meta object for enum '{@link bip2.ujf.verimag.bip.actionlang.BinaryOperators <em>Binary Operators</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for enum '<em>Binary Operators</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.BinaryOperators
     * @generated
     */
    EEnum getBinaryOperators();

    /**
     * Returns the meta object for enum '{@link bip2.ujf.verimag.bip.actionlang.UnaryOperators <em>Unary Operators</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for enum '<em>Unary Operators</em>'.
     * @see bip2.ujf.verimag.bip.actionlang.UnaryOperators
     * @generated
     */
    EEnum getUnaryOperators();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    ActionlangFactory getActionlangFactory();

    /**
     * <!-- begin-user-doc -->
     * Defines literals for the meta objects that represent
     * <ul>
     *   <li>each class,</li>
     *   <li>each feature of each class,</li>
     *   <li>each enum,</li>
     *   <li>and each data type</li>
     * </ul>
     * <!-- end-user-doc -->
     * @generated
     */
    interface Literals {
        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.impl.BinaryOpExpressionImpl <em>Binary Op Expression</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.impl.BinaryOpExpressionImpl
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getBinaryOpExpression()
         * @generated
         */
        EClass BINARY_OP_EXPRESSION = eINSTANCE.getBinaryOpExpression();

        /**
         * The meta object literal for the '<em><b>Operator</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute BINARY_OP_EXPRESSION__OPERATOR = eINSTANCE
                .getBinaryOpExpression_Operator();

        /**
         * The meta object literal for the '<em><b>Left</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference BINARY_OP_EXPRESSION__LEFT = eINSTANCE
                .getBinaryOpExpression_Left();

        /**
         * The meta object literal for the '<em><b>Right</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference BINARY_OP_EXPRESSION__RIGHT = eINSTANCE
                .getBinaryOpExpression_Right();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.impl.UnaryOpExpressionImpl <em>Unary Op Expression</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.impl.UnaryOpExpressionImpl
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getUnaryOpExpression()
         * @generated
         */
        EClass UNARY_OP_EXPRESSION = eINSTANCE.getUnaryOpExpression();

        /**
         * The meta object literal for the '<em><b>Operator</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute UNARY_OP_EXPRESSION__OPERATOR = eINSTANCE
                .getUnaryOpExpression_Operator();

        /**
         * The meta object literal for the '<em><b>Operand</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference UNARY_OP_EXPRESSION__OPERAND = eINSTANCE
                .getUnaryOpExpression_Operand();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.impl.ValuedExpressionImpl <em>Valued Expression</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.impl.ValuedExpressionImpl
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getValuedExpression()
         * @generated
         */
        EClass VALUED_EXPRESSION = eINSTANCE.getValuedExpression();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.impl.SubDataDeclarationReferenceExpressionImpl <em>Sub Data Declaration Reference Expression</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.impl.SubDataDeclarationReferenceExpressionImpl
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getSubDataDeclarationReferenceExpression()
         * @generated
         */
        EClass SUB_DATA_DECLARATION_REFERENCE_EXPRESSION = eINSTANCE
                .getSubDataDeclarationReferenceExpression();

        /**
         * The meta object literal for the '<em><b>Sub Data Declaration Ref</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference SUB_DATA_DECLARATION_REFERENCE_EXPRESSION__SUB_DATA_DECLARATION_REF = eINSTANCE
                .getSubDataDeclarationReferenceExpression_SubDataDeclarationRef();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.impl.DirectDataDeclarationReferenceExpressionImpl <em>Direct Data Declaration Reference Expression</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.impl.DirectDataDeclarationReferenceExpressionImpl
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getDirectDataDeclarationReferenceExpression()
         * @generated
         */
        EClass DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION = eINSTANCE
                .getDirectDataDeclarationReferenceExpression();

        /**
         * The meta object literal for the '<em><b>Data Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION__DATA_DECLARATION = eINSTANCE
                .getDirectDataDeclarationReferenceExpression_DataDeclaration();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.impl.AssignmentExpressionImpl <em>Assignment Expression</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.impl.AssignmentExpressionImpl
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getAssignmentExpression()
         * @generated
         */
        EClass ASSIGNMENT_EXPRESSION = eINSTANCE.getAssignmentExpression();

        /**
         * The meta object literal for the '<em><b>Lhs</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ASSIGNMENT_EXPRESSION__LHS = eINSTANCE
                .getAssignmentExpression_Lhs();

        /**
         * The meta object literal for the '<em><b>Rhs</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ASSIGNMENT_EXPRESSION__RHS = eINSTANCE
                .getAssignmentExpression_Rhs();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.impl.FunctionCallExpressionImpl <em>Function Call Expression</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.impl.FunctionCallExpressionImpl
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getFunctionCallExpression()
         * @generated
         */
        EClass FUNCTION_CALL_EXPRESSION = eINSTANCE.getFunctionCallExpression();

        /**
         * The meta object literal for the '<em><b>Parameters</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference FUNCTION_CALL_EXPRESSION__PARAMETERS = eINSTANCE
                .getFunctionCallExpression_Parameters();

        /**
         * The meta object literal for the '<em><b>Function Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute FUNCTION_CALL_EXPRESSION__FUNCTION_NAME = eINSTANCE
                .getFunctionCallExpression_FunctionName();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.Expression <em>Expression</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.Expression
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getExpression()
         * @generated
         */
        EClass EXPRESSION = eINSTANCE.getExpression();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.impl.ValuedReferenceExpressionImpl <em>Valued Reference Expression</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.impl.ValuedReferenceExpressionImpl
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getValuedReferenceExpression()
         * @generated
         */
        EClass VALUED_REFERENCE_EXPRESSION = eINSTANCE
                .getValuedReferenceExpression();

        /**
         * The meta object literal for the '<em><b>Expression Reference</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference VALUED_REFERENCE_EXPRESSION__EXPRESSION_REFERENCE = eINSTANCE
                .getValuedReferenceExpression_ExpressionReference();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.impl.DirectBooleanExpressionImpl <em>Direct Boolean Expression</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.impl.DirectBooleanExpressionImpl
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getDirectBooleanExpression()
         * @generated
         */
        EClass DIRECT_BOOLEAN_EXPRESSION = eINSTANCE
                .getDirectBooleanExpression();

        /**
         * The meta object literal for the '<em><b>Value</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute DIRECT_BOOLEAN_EXPRESSION__VALUE = eINSTANCE
                .getDirectBooleanExpression_Value();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.impl.IfThenElseExpressionImpl <em>If Then Else Expression</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.impl.IfThenElseExpressionImpl
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getIfThenElseExpression()
         * @generated
         */
        EClass IF_THEN_ELSE_EXPRESSION = eINSTANCE.getIfThenElseExpression();

        /**
         * The meta object literal for the '<em><b>Condition</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference IF_THEN_ELSE_EXPRESSION__CONDITION = eINSTANCE
                .getIfThenElseExpression_Condition();

        /**
         * The meta object literal for the '<em><b>Then</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference IF_THEN_ELSE_EXPRESSION__THEN = eINSTANCE
                .getIfThenElseExpression_Then();

        /**
         * The meta object literal for the '<em><b>Else</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference IF_THEN_ELSE_EXPRESSION__ELSE = eINSTANCE
                .getIfThenElseExpression_Else();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.impl.DirectIntegerExpressionImpl <em>Direct Integer Expression</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.impl.DirectIntegerExpressionImpl
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getDirectIntegerExpression()
         * @generated
         */
        EClass DIRECT_INTEGER_EXPRESSION = eINSTANCE
                .getDirectIntegerExpression();

        /**
         * The meta object literal for the '<em><b>Value</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute DIRECT_INTEGER_EXPRESSION__VALUE = eINSTANCE
                .getDirectIntegerExpression_Value();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.impl.DirectFloatExpressionImpl <em>Direct Float Expression</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.impl.DirectFloatExpressionImpl
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getDirectFloatExpression()
         * @generated
         */
        EClass DIRECT_FLOAT_EXPRESSION = eINSTANCE.getDirectFloatExpression();

        /**
         * The meta object literal for the '<em><b>Value</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute DIRECT_FLOAT_EXPRESSION__VALUE = eINSTANCE
                .getDirectFloatExpression_Value();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.impl.DirectStringExpressionImpl <em>Direct String Expression</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.impl.DirectStringExpressionImpl
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getDirectStringExpression()
         * @generated
         */
        EClass DIRECT_STRING_EXPRESSION = eINSTANCE.getDirectStringExpression();

        /**
         * The meta object literal for the '<em><b>Value</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute DIRECT_STRING_EXPRESSION__VALUE = eINSTANCE
                .getDirectStringExpression_Value();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.BinaryOperators <em>Binary Operators</em>}' enum.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.BinaryOperators
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getBinaryOperators()
         * @generated
         */
        EEnum BINARY_OPERATORS = eINSTANCE.getBinaryOperators();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.actionlang.UnaryOperators <em>Unary Operators</em>}' enum.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.actionlang.UnaryOperators
         * @see bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl#getUnaryOperators()
         * @generated
         */
        EEnum UNARY_OPERATORS = eINSTANCE.getUnaryOperators();

    }

} //ActionlangPackage
