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

import org.eclipse.emf.common.notify.Adapter;
import org.eclipse.emf.common.notify.Notifier;

import org.eclipse.emf.common.notify.impl.AdapterFactoryImpl;

import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * The <b>Adapter Factory</b> for the model.
 * It provides an adapter <code>createXXX</code> method for each class of the model.
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.actionlang.ActionlangPackage
 * @generated
 */
public class ActionlangAdapterFactory extends AdapterFactoryImpl {
    /**
     * The cached model package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected static ActionlangPackage modelPackage;

    /**
     * Creates an instance of the adapter factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ActionlangAdapterFactory() {
        if (modelPackage == null) {
            modelPackage = ActionlangPackage.eINSTANCE;
        }
    }

    /**
     * Returns whether this factory is applicable for the type of the object.
     * <!-- begin-user-doc -->
     * This implementation returns <code>true</code> if the object is either the model's package or is an instance object of the model.
     * <!-- end-user-doc -->
     * @return whether this factory is applicable for the type of the object.
     * @generated
     */
    @Override
    public boolean isFactoryForType(Object object) {
        if (object == modelPackage) {
            return true;
        }
        if (object instanceof EObject) {
            return ((EObject) object).eClass().getEPackage() == modelPackage;
        }
        return false;
    }

    /**
     * The switch that delegates to the <code>createXXX</code> methods.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected ActionlangSwitch<Adapter> modelSwitch = new ActionlangSwitch<Adapter>() {
        @Override
        public Adapter caseBinaryOpExpression(BinaryOpExpression object) {
            return createBinaryOpExpressionAdapter();
        }

        @Override
        public Adapter caseUnaryOpExpression(UnaryOpExpression object) {
            return createUnaryOpExpressionAdapter();
        }

        @Override
        public Adapter caseValuedExpression(ValuedExpression object) {
            return createValuedExpressionAdapter();
        }

        @Override
        public Adapter caseSubDataDeclarationReferenceExpression(
                SubDataDeclarationReferenceExpression object) {
            return createSubDataDeclarationReferenceExpressionAdapter();
        }

        @Override
        public Adapter caseDirectDataDeclarationReferenceExpression(
                DirectDataDeclarationReferenceExpression object) {
            return createDirectDataDeclarationReferenceExpressionAdapter();
        }

        @Override
        public Adapter caseAssignmentExpression(AssignmentExpression object) {
            return createAssignmentExpressionAdapter();
        }

        @Override
        public Adapter caseFunctionCallExpression(
                FunctionCallExpression object) {
            return createFunctionCallExpressionAdapter();
        }

        @Override
        public Adapter caseExpression(Expression object) {
            return createExpressionAdapter();
        }

        @Override
        public Adapter caseValuedReferenceExpression(
                ValuedReferenceExpression object) {
            return createValuedReferenceExpressionAdapter();
        }

        @Override
        public Adapter caseDirectBooleanExpression(
                DirectBooleanExpression object) {
            return createDirectBooleanExpressionAdapter();
        }

        @Override
        public Adapter caseIfThenElseExpression(IfThenElseExpression object) {
            return createIfThenElseExpressionAdapter();
        }

        @Override
        public Adapter caseDirectIntegerExpression(
                DirectIntegerExpression object) {
            return createDirectIntegerExpressionAdapter();
        }

        @Override
        public Adapter caseDirectFloatExpression(DirectFloatExpression object) {
            return createDirectFloatExpressionAdapter();
        }

        @Override
        public Adapter caseDirectStringExpression(
                DirectStringExpression object) {
            return createDirectStringExpressionAdapter();
        }

        @Override
        public Adapter defaultCase(EObject object) {
            return createEObjectAdapter();
        }
    };

    /**
     * Creates an adapter for the <code>target</code>.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param target the object to adapt.
     * @return the adapter for the <code>target</code>.
     * @generated
     */
    @Override
    public Adapter createAdapter(Notifier target) {
        return modelSwitch.doSwitch((EObject) target);
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.actionlang.BinaryOpExpression <em>Binary Op Expression</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.actionlang.BinaryOpExpression
     * @generated
     */
    public Adapter createBinaryOpExpressionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.actionlang.UnaryOpExpression <em>Unary Op Expression</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.actionlang.UnaryOpExpression
     * @generated
     */
    public Adapter createUnaryOpExpressionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.actionlang.ValuedExpression <em>Valued Expression</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.actionlang.ValuedExpression
     * @generated
     */
    public Adapter createValuedExpressionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression <em>Sub Data Declaration Reference Expression</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression
     * @generated
     */
    public Adapter createSubDataDeclarationReferenceExpressionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression <em>Direct Data Declaration Reference Expression</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression
     * @generated
     */
    public Adapter createDirectDataDeclarationReferenceExpressionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.actionlang.AssignmentExpression <em>Assignment Expression</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.actionlang.AssignmentExpression
     * @generated
     */
    public Adapter createAssignmentExpressionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.actionlang.FunctionCallExpression <em>Function Call Expression</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.actionlang.FunctionCallExpression
     * @generated
     */
    public Adapter createFunctionCallExpressionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.actionlang.Expression <em>Expression</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.actionlang.Expression
     * @generated
     */
    public Adapter createExpressionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.actionlang.ValuedReferenceExpression <em>Valued Reference Expression</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.actionlang.ValuedReferenceExpression
     * @generated
     */
    public Adapter createValuedReferenceExpressionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.actionlang.DirectBooleanExpression <em>Direct Boolean Expression</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.actionlang.DirectBooleanExpression
     * @generated
     */
    public Adapter createDirectBooleanExpressionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.actionlang.IfThenElseExpression <em>If Then Else Expression</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.actionlang.IfThenElseExpression
     * @generated
     */
    public Adapter createIfThenElseExpressionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.actionlang.DirectIntegerExpression <em>Direct Integer Expression</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.actionlang.DirectIntegerExpression
     * @generated
     */
    public Adapter createDirectIntegerExpressionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.actionlang.DirectFloatExpression <em>Direct Float Expression</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.actionlang.DirectFloatExpression
     * @generated
     */
    public Adapter createDirectFloatExpressionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for an object of class '{@link bip2.ujf.verimag.bip.actionlang.DirectStringExpression <em>Direct String Expression</em>}'.
     * <!-- begin-user-doc -->
     * This default implementation returns null so that we can easily ignore cases;
     * it's useful to ignore a case when inheritance will catch all the cases anyway.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @see bip2.ujf.verimag.bip.actionlang.DirectStringExpression
     * @generated
     */
    public Adapter createDirectStringExpressionAdapter() {
        return null;
    }

    /**
     * Creates a new adapter for the default case.
     * <!-- begin-user-doc -->
     * This default implementation returns null.
     * <!-- end-user-doc -->
     * @return the new adapter.
     * @generated
     */
    public Adapter createEObjectAdapter() {
        return null;
    }

} //ActionlangAdapterFactory
