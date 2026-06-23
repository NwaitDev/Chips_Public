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

import bip2.ujf.verimag.bip.actionlang.ActionlangPackage;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;
import bip2.ujf.verimag.bip.actionlang.ValuedReferenceExpression;

import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.types.Type;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

import org.eclipse.emf.ecore.impl.EObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Valued Reference Expression</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.ValuedReferenceExpressionImpl#getExpressionReference <em>Expression Reference</em>}</li>
 * </ul>
 *
 * @generated
 */
public class ValuedReferenceExpressionImpl extends ValuedExpressionImpl
        implements ValuedReferenceExpression {
    /**
     * The cached value of the '{@link #getExpressionReference() <em>Expression Reference</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getExpressionReference()
     * @generated
     * @ordered
     */
    protected ValuedExpression expressionReference;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected ValuedReferenceExpressionImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return ActionlangPackage.Literals.VALUED_REFERENCE_EXPRESSION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ValuedExpression getExpressionReference() {
        if (expressionReference != null
                && ((EObject) expressionReference).eIsProxy()) {
            InternalEObject oldExpressionReference = (InternalEObject) expressionReference;
            expressionReference = (ValuedExpression) eResolveProxy(
                    oldExpressionReference);
            if (expressionReference != oldExpressionReference) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            ActionlangPackage.VALUED_REFERENCE_EXPRESSION__EXPRESSION_REFERENCE,
                            oldExpressionReference, expressionReference));
            }
        }
        return expressionReference;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ValuedExpression basicGetExpressionReference() {
        return expressionReference;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setExpressionReference(
            ValuedExpression newExpressionReference) {
        ValuedExpression oldExpressionReference = expressionReference;
        expressionReference = newExpressionReference;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ActionlangPackage.VALUED_REFERENCE_EXPRESSION__EXPRESSION_REFERENCE,
                    oldExpressionReference, expressionReference));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public Type getType() {
        return getExpressionReference().getType();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean isConst() {
        return getExpressionReference().isConst();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case ActionlangPackage.VALUED_REFERENCE_EXPRESSION__EXPRESSION_REFERENCE:
            if (resolve)
                return getExpressionReference();
            return basicGetExpressionReference();
        }
        return super.eGet(featureID, resolve, coreType);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void eSet(int featureID, Object newValue) {
        switch (featureID) {
        case ActionlangPackage.VALUED_REFERENCE_EXPRESSION__EXPRESSION_REFERENCE:
            setExpressionReference((ValuedExpression) newValue);
            return;
        }
        super.eSet(featureID, newValue);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void eUnset(int featureID) {
        switch (featureID) {
        case ActionlangPackage.VALUED_REFERENCE_EXPRESSION__EXPRESSION_REFERENCE:
            setExpressionReference((ValuedExpression) null);
            return;
        }
        super.eUnset(featureID);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public boolean eIsSet(int featureID) {
        switch (featureID) {
        case ActionlangPackage.VALUED_REFERENCE_EXPRESSION__EXPRESSION_REFERENCE:
            return expressionReference != null;
        }
        return super.eIsSet(featureID);
    }

} //ValuedReferenceExpressionImpl
