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
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression;

import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.data.SubDataDeclarationReference;
import bip2.ujf.verimag.bip.types.Type;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;
import org.eclipse.emf.common.util.BasicEList;
import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

import org.eclipse.emf.ecore.impl.EObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Sub Data Declaration Reference Expression</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.SubDataDeclarationReferenceExpressionImpl#getSubDataDeclarationRef <em>Sub Data Declaration Ref</em>}</li>
 * </ul>
 *
 * @generated
 */
public class SubDataDeclarationReferenceExpressionImpl extends
        ValuedExpressionImpl implements SubDataDeclarationReferenceExpression {
    /**
     * The cached value of the '{@link #getSubDataDeclarationRef() <em>Sub Data Declaration Ref</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getSubDataDeclarationRef()
     * @generated
     * @ordered
     */
    protected SubDataDeclarationReference subDataDeclarationRef;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected SubDataDeclarationReferenceExpressionImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return ActionlangPackage.Literals.SUB_DATA_DECLARATION_REFERENCE_EXPRESSION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public SubDataDeclarationReference getSubDataDeclarationRef() {
        return subDataDeclarationRef;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetSubDataDeclarationRef(
            SubDataDeclarationReference newSubDataDeclarationRef,
            NotificationChain msgs) {
        SubDataDeclarationReference oldSubDataDeclarationRef = subDataDeclarationRef;
        subDataDeclarationRef = newSubDataDeclarationRef;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    ActionlangPackage.SUB_DATA_DECLARATION_REFERENCE_EXPRESSION__SUB_DATA_DECLARATION_REF,
                    oldSubDataDeclarationRef, newSubDataDeclarationRef);
            if (msgs == null)
                msgs = notification;
            else
                msgs.add(notification);
        }
        return msgs;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setSubDataDeclarationRef(
            SubDataDeclarationReference newSubDataDeclarationRef) {
        if (newSubDataDeclarationRef != subDataDeclarationRef) {
            NotificationChain msgs = null;
            if (subDataDeclarationRef != null)
                msgs = ((InternalEObject) subDataDeclarationRef).eInverseRemove(
                        this,
                        EOPPOSITE_FEATURE_BASE
                                - ActionlangPackage.SUB_DATA_DECLARATION_REFERENCE_EXPRESSION__SUB_DATA_DECLARATION_REF,
                        null, msgs);
            if (newSubDataDeclarationRef != null)
                msgs = ((InternalEObject) newSubDataDeclarationRef).eInverseAdd(
                        this,
                        EOPPOSITE_FEATURE_BASE
                                - ActionlangPackage.SUB_DATA_DECLARATION_REFERENCE_EXPRESSION__SUB_DATA_DECLARATION_REF,
                        null, msgs);
            msgs = basicSetSubDataDeclarationRef(newSubDataDeclarationRef,
                    msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ActionlangPackage.SUB_DATA_DECLARATION_REFERENCE_EXPRESSION__SUB_DATA_DECLARATION_REF,
                    newSubDataDeclarationRef, newSubDataDeclarationRef));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public Type getType() {
        return getSubDataDeclarationRef().getForwardDataDeclaration()
                .getDataType();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean isConst() {
        return getSubDataDeclarationRef().getForwardDataDeclaration().isConst();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public NotificationChain eInverseRemove(InternalEObject otherEnd,
            int featureID, NotificationChain msgs) {
        switch (featureID) {
        case ActionlangPackage.SUB_DATA_DECLARATION_REFERENCE_EXPRESSION__SUB_DATA_DECLARATION_REF:
            return basicSetSubDataDeclarationRef(null, msgs);
        }
        return super.eInverseRemove(otherEnd, featureID, msgs);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case ActionlangPackage.SUB_DATA_DECLARATION_REFERENCE_EXPRESSION__SUB_DATA_DECLARATION_REF:
            return getSubDataDeclarationRef();
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
        case ActionlangPackage.SUB_DATA_DECLARATION_REFERENCE_EXPRESSION__SUB_DATA_DECLARATION_REF:
            setSubDataDeclarationRef((SubDataDeclarationReference) newValue);
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
        case ActionlangPackage.SUB_DATA_DECLARATION_REFERENCE_EXPRESSION__SUB_DATA_DECLARATION_REF:
            setSubDataDeclarationRef((SubDataDeclarationReference) null);
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
        case ActionlangPackage.SUB_DATA_DECLARATION_REFERENCE_EXPRESSION__SUB_DATA_DECLARATION_REF:
            return subDataDeclarationRef != null;
        }
        return super.eIsSet(featureID);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getReadVariables() {
        EList<DataDeclaration> ret = new BasicEList<DataDeclaration>();

        ret.add(getSubDataDeclarationRef().getForwardDataDeclaration());

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getMayReadVariables() {
        EList<DataDeclaration> ret = new BasicEList<DataDeclaration>();

        ret.add(getSubDataDeclarationRef().getForwardDataDeclaration());

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getWriteVariables() {
        return new BasicEList<DataDeclaration>();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getMayWriteVariables() {
        return new BasicEList<DataDeclaration>();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<Expression> getMayReadUninitializedVariables(
            EList<DataDeclaration> uninitialized) {
        EList<Expression> ret = new BasicEList<Expression>();

        if (uninitialized.contains(
                getSubDataDeclarationRef().getForwardDataDeclaration())) {
            ret.add(this);
        }

        return ret;
    }

} //SubDataDeclarationReferenceExpressionImpl
