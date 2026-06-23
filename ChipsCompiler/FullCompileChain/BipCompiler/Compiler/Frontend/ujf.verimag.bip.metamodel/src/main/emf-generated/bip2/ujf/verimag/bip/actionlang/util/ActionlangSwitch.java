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

package bip2.ujf.verimag.bip.actionlang.util;

import bip2.ujf.verimag.bip.actionlang.*;

import java.util.List;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.util.Switch;

/**
 * <!-- begin-user-doc -->
 * The <b>Switch</b> for the model's inheritance hierarchy.
 * It supports the call {@link #doSwitch(EObject) doSwitch(object)}
 * to invoke the <code>caseXXX</code> method for each class of the model,
 * starting with the actual class of the object
 * and proceeding up the inheritance hierarchy
 * until a non-null result is returned,
 * which is the result of the switch.
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.actionlang.ActionlangPackage
 * @generated
 */
public class ActionlangSwitch<T> extends Switch<T> {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected static ActionlangPackage modelPackage;

    /**
     * Creates an instance of the switch.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ActionlangSwitch() {
        if (modelPackage == null) {
            modelPackage = ActionlangPackage.eINSTANCE;
        }
    }

    /**
     * Checks whether this is a switch for the given package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param ePackage the package in question.
     * @return whether this is a switch for the given package.
     * @generated
     */
    @Override
    protected boolean isSwitchFor(EPackage ePackage) {
        return ePackage == modelPackage;
    }

    /**
     * Calls <code>caseXXX</code> for each class of the model until one returns a non null result; it yields that result.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the first non-null result returned by a <code>caseXXX</code> call.
     * @generated
     */
    @Override
    protected T doSwitch(int classifierID, EObject theEObject) {
        switch (classifierID) {
        case ActionlangPackage.BINARY_OP_EXPRESSION: {
            BinaryOpExpression binaryOpExpression = (BinaryOpExpression) theEObject;
            T result = caseBinaryOpExpression(binaryOpExpression);
            if (result == null)
                result = caseValuedExpression(binaryOpExpression);
            if (result == null)
                result = caseExpression(binaryOpExpression);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ActionlangPackage.UNARY_OP_EXPRESSION: {
            UnaryOpExpression unaryOpExpression = (UnaryOpExpression) theEObject;
            T result = caseUnaryOpExpression(unaryOpExpression);
            if (result == null)
                result = caseValuedExpression(unaryOpExpression);
            if (result == null)
                result = caseExpression(unaryOpExpression);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ActionlangPackage.VALUED_EXPRESSION: {
            ValuedExpression valuedExpression = (ValuedExpression) theEObject;
            T result = caseValuedExpression(valuedExpression);
            if (result == null)
                result = caseExpression(valuedExpression);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ActionlangPackage.SUB_DATA_DECLARATION_REFERENCE_EXPRESSION: {
            SubDataDeclarationReferenceExpression subDataDeclarationReferenceExpression = (SubDataDeclarationReferenceExpression) theEObject;
            T result = caseSubDataDeclarationReferenceExpression(
                    subDataDeclarationReferenceExpression);
            if (result == null)
                result = caseValuedExpression(
                        subDataDeclarationReferenceExpression);
            if (result == null)
                result = caseExpression(subDataDeclarationReferenceExpression);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ActionlangPackage.DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION: {
            DirectDataDeclarationReferenceExpression directDataDeclarationReferenceExpression = (DirectDataDeclarationReferenceExpression) theEObject;
            T result = caseDirectDataDeclarationReferenceExpression(
                    directDataDeclarationReferenceExpression);
            if (result == null)
                result = caseValuedExpression(
                        directDataDeclarationReferenceExpression);
            if (result == null)
                result = caseExpression(
                        directDataDeclarationReferenceExpression);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ActionlangPackage.ASSIGNMENT_EXPRESSION: {
            AssignmentExpression assignmentExpression = (AssignmentExpression) theEObject;
            T result = caseAssignmentExpression(assignmentExpression);
            if (result == null)
                result = caseExpression(assignmentExpression);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ActionlangPackage.FUNCTION_CALL_EXPRESSION: {
            FunctionCallExpression functionCallExpression = (FunctionCallExpression) theEObject;
            T result = caseFunctionCallExpression(functionCallExpression);
            if (result == null)
                result = caseValuedExpression(functionCallExpression);
            if (result == null)
                result = caseExpression(functionCallExpression);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ActionlangPackage.EXPRESSION: {
            Expression expression = (Expression) theEObject;
            T result = caseExpression(expression);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ActionlangPackage.VALUED_REFERENCE_EXPRESSION: {
            ValuedReferenceExpression valuedReferenceExpression = (ValuedReferenceExpression) theEObject;
            T result = caseValuedReferenceExpression(valuedReferenceExpression);
            if (result == null)
                result = caseValuedExpression(valuedReferenceExpression);
            if (result == null)
                result = caseExpression(valuedReferenceExpression);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ActionlangPackage.DIRECT_BOOLEAN_EXPRESSION: {
            DirectBooleanExpression directBooleanExpression = (DirectBooleanExpression) theEObject;
            T result = caseDirectBooleanExpression(directBooleanExpression);
            if (result == null)
                result = caseValuedExpression(directBooleanExpression);
            if (result == null)
                result = caseExpression(directBooleanExpression);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION: {
            IfThenElseExpression ifThenElseExpression = (IfThenElseExpression) theEObject;
            T result = caseIfThenElseExpression(ifThenElseExpression);
            if (result == null)
                result = caseExpression(ifThenElseExpression);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ActionlangPackage.DIRECT_INTEGER_EXPRESSION: {
            DirectIntegerExpression directIntegerExpression = (DirectIntegerExpression) theEObject;
            T result = caseDirectIntegerExpression(directIntegerExpression);
            if (result == null)
                result = caseValuedExpression(directIntegerExpression);
            if (result == null)
                result = caseExpression(directIntegerExpression);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ActionlangPackage.DIRECT_FLOAT_EXPRESSION: {
            DirectFloatExpression directFloatExpression = (DirectFloatExpression) theEObject;
            T result = caseDirectFloatExpression(directFloatExpression);
            if (result == null)
                result = caseValuedExpression(directFloatExpression);
            if (result == null)
                result = caseExpression(directFloatExpression);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ActionlangPackage.DIRECT_STRING_EXPRESSION: {
            DirectStringExpression directStringExpression = (DirectStringExpression) theEObject;
            T result = caseDirectStringExpression(directStringExpression);
            if (result == null)
                result = caseValuedExpression(directStringExpression);
            if (result == null)
                result = caseExpression(directStringExpression);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        default:
            return defaultCase(theEObject);
        }
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Binary Op Expression</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Binary Op Expression</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseBinaryOpExpression(BinaryOpExpression object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Unary Op Expression</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Unary Op Expression</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseUnaryOpExpression(UnaryOpExpression object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Valued Expression</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Valued Expression</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseValuedExpression(ValuedExpression object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Sub Data Declaration Reference Expression</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Sub Data Declaration Reference Expression</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseSubDataDeclarationReferenceExpression(
            SubDataDeclarationReferenceExpression object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Direct Data Declaration Reference Expression</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Direct Data Declaration Reference Expression</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseDirectDataDeclarationReferenceExpression(
            DirectDataDeclarationReferenceExpression object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Assignment Expression</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Assignment Expression</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseAssignmentExpression(AssignmentExpression object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Function Call Expression</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Function Call Expression</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseFunctionCallExpression(FunctionCallExpression object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Expression</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Expression</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseExpression(Expression object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Valued Reference Expression</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Valued Reference Expression</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseValuedReferenceExpression(ValuedReferenceExpression object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Direct Boolean Expression</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Direct Boolean Expression</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseDirectBooleanExpression(DirectBooleanExpression object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>If Then Else Expression</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>If Then Else Expression</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseIfThenElseExpression(IfThenElseExpression object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Direct Integer Expression</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Direct Integer Expression</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseDirectIntegerExpression(DirectIntegerExpression object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Direct Float Expression</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Direct Float Expression</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseDirectFloatExpression(DirectFloatExpression object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Direct String Expression</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Direct String Expression</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseDirectStringExpression(DirectStringExpression object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>EObject</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch, but this is the last case anyway.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>EObject</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject)
     * @generated
     */
    @Override
    public T defaultCase(EObject object) {
        return null;
    }

} //ActionlangSwitch
