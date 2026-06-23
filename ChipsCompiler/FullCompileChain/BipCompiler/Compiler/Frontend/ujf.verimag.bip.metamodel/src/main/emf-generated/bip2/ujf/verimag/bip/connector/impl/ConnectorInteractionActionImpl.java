/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Anakreontas Mentis
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

package bip2.ujf.verimag.bip.connector.impl;

import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;

import bip2.ujf.verimag.bip.annotation.impl.AnnotatedElementImpl;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionAction;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference;
import bip2.ujf.verimag.bip.connector.ConnectorPackage;
import bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration;

import java.util.Collection;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.emf.ecore.impl.EObjectImpl;
import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.EObjectResolvingEList;
import org.eclipse.emf.ecore.util.InternalEList;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Interaction Action</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionActionImpl#getOnPorts <em>On Ports</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionActionImpl#getUp <em>Up</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionActionImpl#getDown <em>Down</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionActionImpl#getGuard <em>Guard</em>}</li>
 * </ul>
 *
 * @generated
 */
public class ConnectorInteractionActionImpl extends AnnotatedElementImpl
        implements ConnectorInteractionAction {
    /**
     * The cached value of the '{@link #getOnPorts() <em>On Ports</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getOnPorts()
     * @generated
     * @ordered
     */
    protected EList<ConnectorPortParameterDeclaration> onPorts;

    /**
     * The cached value of the '{@link #getUp() <em>Up</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getUp()
     * @generated
     * @ordered
     */
    protected EList<Expression> up;

    /**
     * The cached value of the '{@link #getDown() <em>Down</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDown()
     * @generated
     * @ordered
     */
    protected EList<Expression> down;

    /**
     * The cached value of the '{@link #getGuard() <em>Guard</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getGuard()
     * @generated
     * @ordered
     */
    protected ValuedExpression guard;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected ConnectorInteractionActionImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return ConnectorPackage.Literals.CONNECTOR_INTERACTION_ACTION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<ConnectorPortParameterDeclaration> getOnPorts() {
        if (onPorts == null) {
            onPorts = new EObjectResolvingEList<ConnectorPortParameterDeclaration>(
                    ConnectorPortParameterDeclaration.class, this,
                    ConnectorPackage.CONNECTOR_INTERACTION_ACTION__ON_PORTS);
        }
        return onPorts;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ValuedExpression getGuard() {
        return guard;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetGuard(ValuedExpression newGuard,
            NotificationChain msgs) {
        ValuedExpression oldGuard = guard;
        guard = newGuard;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    ConnectorPackage.CONNECTOR_INTERACTION_ACTION__GUARD,
                    oldGuard, newGuard);
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
    public void setGuard(ValuedExpression newGuard) {
        if (newGuard != guard) {
            NotificationChain msgs = null;
            if (guard != null)
                msgs = ((InternalEObject) guard).eInverseRemove(this,
                        EOPPOSITE_FEATURE_BASE
                                - ConnectorPackage.CONNECTOR_INTERACTION_ACTION__GUARD,
                        null, msgs);
            if (newGuard != null)
                msgs = ((InternalEObject) newGuard).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - ConnectorPackage.CONNECTOR_INTERACTION_ACTION__GUARD,
                        null, msgs);
            msgs = basicSetGuard(newGuard, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ConnectorPackage.CONNECTOR_INTERACTION_ACTION__GUARD,
                    newGuard, newGuard));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<Expression> getUp() {
        if (up == null) {
            up = new EObjectContainmentEList<Expression>(Expression.class, this,
                    ConnectorPackage.CONNECTOR_INTERACTION_ACTION__UP);
        }
        return up;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<Expression> getDown() {
        if (down == null) {
            down = new EObjectContainmentEList<Expression>(Expression.class,
                    this, ConnectorPackage.CONNECTOR_INTERACTION_ACTION__DOWN);
        }
        return down;
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
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__UP:
            return ((InternalEList<?>) getUp()).basicRemove(otherEnd, msgs);
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__DOWN:
            return ((InternalEList<?>) getDown()).basicRemove(otherEnd, msgs);
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__GUARD:
            return basicSetGuard(null, msgs);
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
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__ON_PORTS:
            return getOnPorts();
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__UP:
            return getUp();
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__DOWN:
            return getDown();
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__GUARD:
            return getGuard();
        }
        return super.eGet(featureID, resolve, coreType);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @SuppressWarnings("unchecked")
    @Override
    public void eSet(int featureID, Object newValue) {
        switch (featureID) {
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__ON_PORTS:
            getOnPorts().clear();
            getOnPorts().addAll(
                    (Collection<? extends ConnectorPortParameterDeclaration>) newValue);
            return;
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__UP:
            getUp().clear();
            getUp().addAll((Collection<? extends Expression>) newValue);
            return;
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__DOWN:
            getDown().clear();
            getDown().addAll((Collection<? extends Expression>) newValue);
            return;
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__GUARD:
            setGuard((ValuedExpression) newValue);
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
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__ON_PORTS:
            getOnPorts().clear();
            return;
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__UP:
            getUp().clear();
            return;
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__DOWN:
            getDown().clear();
            return;
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__GUARD:
            setGuard((ValuedExpression) null);
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
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__ON_PORTS:
            return onPorts != null && !onPorts.isEmpty();
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__UP:
            return up != null && !up.isEmpty();
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__DOWN:
            return down != null && !down.isEmpty();
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION__GUARD:
            return guard != null;
        }
        return super.eIsSet(featureID);
    }

} //ConnectorInteractionActionImpl
