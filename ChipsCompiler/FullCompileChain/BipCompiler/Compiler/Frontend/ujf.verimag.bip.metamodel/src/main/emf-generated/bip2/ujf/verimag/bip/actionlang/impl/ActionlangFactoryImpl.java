/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
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

package bip2.ujf.verimag.bip.actionlang.impl;

import bip2.ujf.verimag.bip.actionlang.*;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EDataType;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.impl.EFactoryImpl;

import org.eclipse.emf.ecore.plugin.EcorePlugin;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Factory</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class ActionlangFactoryImpl extends EFactoryImpl
        implements ActionlangFactory {
    /**
     * Creates the default factory implementation.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static ActionlangFactory init() {
        try {
            ActionlangFactory theActionlangFactory = (ActionlangFactory) EPackage.Registry.INSTANCE
                    .getEFactory(ActionlangPackage.eNS_URI);
            if (theActionlangFactory != null) {
                return theActionlangFactory;
            }
        } catch (Exception exception) {
            EcorePlugin.INSTANCE.log(exception);
        }
        return new ActionlangFactoryImpl();
    }

    /**
     * Creates an instance of the factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ActionlangFactoryImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EObject create(EClass eClass) {
        switch (eClass.getClassifierID()) {
        case ActionlangPackage.BINARY_OP_EXPRESSION:
            return (EObject) createBinaryOpExpression();
        case ActionlangPackage.UNARY_OP_EXPRESSION:
            return (EObject) createUnaryOpExpression();
        case ActionlangPackage.SUB_DATA_DECLARATION_REFERENCE_EXPRESSION:
            return (EObject) createSubDataDeclarationReferenceExpression();
        case ActionlangPackage.DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION:
            return (EObject) createDirectDataDeclarationReferenceExpression();
        case ActionlangPackage.ASSIGNMENT_EXPRESSION:
            return (EObject) createAssignmentExpression();
        case ActionlangPackage.FUNCTION_CALL_EXPRESSION:
            return (EObject) createFunctionCallExpression();
        case ActionlangPackage.VALUED_REFERENCE_EXPRESSION:
            return (EObject) createValuedReferenceExpression();
        case ActionlangPackage.DIRECT_BOOLEAN_EXPRESSION:
            return (EObject) createDirectBooleanExpression();
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION:
            return (EObject) createIfThenElseExpression();
        case ActionlangPackage.DIRECT_INTEGER_EXPRESSION:
            return (EObject) createDirectIntegerExpression();
        case ActionlangPackage.DIRECT_FLOAT_EXPRESSION:
            return (EObject) createDirectFloatExpression();
        case ActionlangPackage.DIRECT_STRING_EXPRESSION:
            return (EObject) createDirectStringExpression();
        default:
            throw new IllegalArgumentException("The class '" + eClass.getName()
                    + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object createFromString(EDataType eDataType, String initialValue) {
        switch (eDataType.getClassifierID()) {
        case ActionlangPackage.BINARY_OPERATORS:
            return createBinaryOperatorsFromString(eDataType, initialValue);
        case ActionlangPackage.UNARY_OPERATORS:
            return createUnaryOperatorsFromString(eDataType, initialValue);
        default:
            throw new IllegalArgumentException("The datatype '"
                    + eDataType.getName() + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public String convertToString(EDataType eDataType, Object instanceValue) {
        switch (eDataType.getClassifierID()) {
        case ActionlangPackage.BINARY_OPERATORS:
            return convertBinaryOperatorsToString(eDataType, instanceValue);
        case ActionlangPackage.UNARY_OPERATORS:
            return convertUnaryOperatorsToString(eDataType, instanceValue);
        default:
            throw new IllegalArgumentException("The datatype '"
                    + eDataType.getName() + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public BinaryOpExpression createBinaryOpExpression() {
        BinaryOpExpressionImpl binaryOpExpression = new BinaryOpExpressionImpl();
        return binaryOpExpression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public UnaryOpExpression createUnaryOpExpression() {
        UnaryOpExpressionImpl unaryOpExpression = new UnaryOpExpressionImpl();
        return unaryOpExpression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public SubDataDeclarationReferenceExpression createSubDataDeclarationReferenceExpression() {
        SubDataDeclarationReferenceExpressionImpl subDataDeclarationReferenceExpression = new SubDataDeclarationReferenceExpressionImpl();
        return subDataDeclarationReferenceExpression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DirectDataDeclarationReferenceExpression createDirectDataDeclarationReferenceExpression() {
        DirectDataDeclarationReferenceExpressionImpl directDataDeclarationReferenceExpression = new DirectDataDeclarationReferenceExpressionImpl();
        return directDataDeclarationReferenceExpression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AssignmentExpression createAssignmentExpression() {
        AssignmentExpressionImpl assignmentExpression = new AssignmentExpressionImpl();
        return assignmentExpression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public FunctionCallExpression createFunctionCallExpression() {
        FunctionCallExpressionImpl functionCallExpression = new FunctionCallExpressionImpl();
        return functionCallExpression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ValuedReferenceExpression createValuedReferenceExpression() {
        ValuedReferenceExpressionImpl valuedReferenceExpression = new ValuedReferenceExpressionImpl();
        return valuedReferenceExpression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DirectBooleanExpression createDirectBooleanExpression() {
        DirectBooleanExpressionImpl directBooleanExpression = new DirectBooleanExpressionImpl();
        return directBooleanExpression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public IfThenElseExpression createIfThenElseExpression() {
        IfThenElseExpressionImpl ifThenElseExpression = new IfThenElseExpressionImpl();
        return ifThenElseExpression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DirectIntegerExpression createDirectIntegerExpression() {
        DirectIntegerExpressionImpl directIntegerExpression = new DirectIntegerExpressionImpl();
        return directIntegerExpression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DirectFloatExpression createDirectFloatExpression() {
        DirectFloatExpressionImpl directFloatExpression = new DirectFloatExpressionImpl();
        return directFloatExpression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DirectStringExpression createDirectStringExpression() {
        DirectStringExpressionImpl directStringExpression = new DirectStringExpressionImpl();
        return directStringExpression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public BinaryOperators createBinaryOperatorsFromString(EDataType eDataType,
            String initialValue) {
        BinaryOperators result = BinaryOperators.get(initialValue);
        if (result == null)
            throw new IllegalArgumentException("The value '" + initialValue
                    + "' is not a valid enumerator of '" + eDataType.getName()
                    + "'");
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String convertBinaryOperatorsToString(EDataType eDataType,
            Object instanceValue) {
        return instanceValue == null ? null : instanceValue.toString();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public UnaryOperators createUnaryOperatorsFromString(EDataType eDataType,
            String initialValue) {
        UnaryOperators result = UnaryOperators.get(initialValue);
        if (result == null)
            throw new IllegalArgumentException("The value '" + initialValue
                    + "' is not a valid enumerator of '" + eDataType.getName()
                    + "'");
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String convertUnaryOperatorsToString(EDataType eDataType,
            Object instanceValue) {
        return instanceValue == null ? null : instanceValue.toString();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ActionlangPackage getActionlangPackage() {
        return (ActionlangPackage) getEPackage();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @deprecated
     * @generated
     */
    @Deprecated
    public static ActionlangPackage getPackage() {
        return ActionlangPackage.eINSTANCE;
    }

} //ActionlangFactoryImpl
