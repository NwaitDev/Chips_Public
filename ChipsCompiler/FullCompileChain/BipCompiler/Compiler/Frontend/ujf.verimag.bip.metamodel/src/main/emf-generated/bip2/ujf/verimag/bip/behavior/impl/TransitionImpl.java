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

package bip2.ujf.verimag.bip.behavior.impl;

import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;
import bip2.ujf.verimag.bip.annotation.impl.AnnotatedElementImpl;
import bip2.ujf.verimag.bip.behavior.BehaviorPackage;
import bip2.ujf.verimag.bip.behavior.State;
import bip2.ujf.verimag.bip.behavior.Transition;

import bip2.ujf.verimag.bip.component.atom.AtomInternalExternalPortDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomInternalPortDeclaration;

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
 * An implementation of the model object '<em><b>Transition</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.behavior.impl.TransitionImpl#getSources <em>Sources</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.behavior.impl.TransitionImpl#getDestinations <em>Destinations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.behavior.impl.TransitionImpl#getTriggerPort <em>Trigger Port</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.behavior.impl.TransitionImpl#getActions <em>Actions</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.behavior.impl.TransitionImpl#getGuard <em>Guard</em>}</li>
 * </ul>
 *
 * @generated
 */
public class TransitionImpl extends AnnotatedElementImpl implements Transition {
    /**
     * The cached value of the '{@link #getSources() <em>Sources</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getSources()
     * @generated
     * @ordered
     */
    protected EList<State> sources;

    /**
     * The cached value of the '{@link #getDestinations() <em>Destinations</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDestinations()
     * @generated
     * @ordered
     */
    protected EList<State> destinations;

    /**
     * The cached value of the '{@link #getTriggerPort() <em>Trigger Port</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getTriggerPort()
     * @generated
     * @ordered
     */
    protected AtomInternalExternalPortDeclaration triggerPort;

    /**
     * The cached value of the '{@link #getActions() <em>Actions</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getActions()
     * @generated
     * @ordered
     */
    protected EList<Expression> actions;

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
    protected TransitionImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return BehaviorPackage.Literals.TRANSITION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<State> getSources() {
        if (sources == null) {
            sources = new EObjectResolvingEList<State>(State.class, this,
                    BehaviorPackage.TRANSITION__SOURCES);
        }
        return sources;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<State> getDestinations() {
        if (destinations == null) {
            destinations = new EObjectResolvingEList<State>(State.class, this,
                    BehaviorPackage.TRANSITION__DESTINATIONS);
        }
        return destinations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomInternalExternalPortDeclaration getTriggerPort() {
        if (triggerPort != null && ((EObject) triggerPort).eIsProxy()) {
            InternalEObject oldTriggerPort = (InternalEObject) triggerPort;
            triggerPort = (AtomInternalExternalPortDeclaration) eResolveProxy(
                    oldTriggerPort);
            if (triggerPort != oldTriggerPort) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            BehaviorPackage.TRANSITION__TRIGGER_PORT,
                            oldTriggerPort, triggerPort));
            }
        }
        return triggerPort;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomInternalExternalPortDeclaration basicGetTriggerPort() {
        return triggerPort;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setTriggerPort(
            AtomInternalExternalPortDeclaration newTriggerPort) {
        AtomInternalExternalPortDeclaration oldTriggerPort = triggerPort;
        triggerPort = newTriggerPort;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    BehaviorPackage.TRANSITION__TRIGGER_PORT, oldTriggerPort,
                    triggerPort));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<Expression> getActions() {
        if (actions == null) {
            actions = new EObjectContainmentEList<Expression>(Expression.class,
                    this, BehaviorPackage.TRANSITION__ACTIONS);
        }
        return actions;
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
                    Notification.SET, BehaviorPackage.TRANSITION__GUARD,
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
                                - BehaviorPackage.TRANSITION__GUARD,
                        null, msgs);
            if (newGuard != null)
                msgs = ((InternalEObject) newGuard).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - BehaviorPackage.TRANSITION__GUARD,
                        null, msgs);
            msgs = basicSetGuard(newGuard, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    BehaviorPackage.TRANSITION__GUARD, newGuard, newGuard));
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
        case BehaviorPackage.TRANSITION__ACTIONS:
            return ((InternalEList<?>) getActions()).basicRemove(otherEnd,
                    msgs);
        case BehaviorPackage.TRANSITION__GUARD:
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
        case BehaviorPackage.TRANSITION__SOURCES:
            return getSources();
        case BehaviorPackage.TRANSITION__DESTINATIONS:
            return getDestinations();
        case BehaviorPackage.TRANSITION__TRIGGER_PORT:
            if (resolve)
                return getTriggerPort();
            return basicGetTriggerPort();
        case BehaviorPackage.TRANSITION__ACTIONS:
            return getActions();
        case BehaviorPackage.TRANSITION__GUARD:
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
        case BehaviorPackage.TRANSITION__SOURCES:
            getSources().clear();
            getSources().addAll((Collection<? extends State>) newValue);
            return;
        case BehaviorPackage.TRANSITION__DESTINATIONS:
            getDestinations().clear();
            getDestinations().addAll((Collection<? extends State>) newValue);
            return;
        case BehaviorPackage.TRANSITION__TRIGGER_PORT:
            setTriggerPort((AtomInternalExternalPortDeclaration) newValue);
            return;
        case BehaviorPackage.TRANSITION__ACTIONS:
            getActions().clear();
            getActions().addAll((Collection<? extends Expression>) newValue);
            return;
        case BehaviorPackage.TRANSITION__GUARD:
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
        case BehaviorPackage.TRANSITION__SOURCES:
            getSources().clear();
            return;
        case BehaviorPackage.TRANSITION__DESTINATIONS:
            getDestinations().clear();
            return;
        case BehaviorPackage.TRANSITION__TRIGGER_PORT:
            setTriggerPort((AtomInternalExternalPortDeclaration) null);
            return;
        case BehaviorPackage.TRANSITION__ACTIONS:
            getActions().clear();
            return;
        case BehaviorPackage.TRANSITION__GUARD:
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
        case BehaviorPackage.TRANSITION__SOURCES:
            return sources != null && !sources.isEmpty();
        case BehaviorPackage.TRANSITION__DESTINATIONS:
            return destinations != null && !destinations.isEmpty();
        case BehaviorPackage.TRANSITION__TRIGGER_PORT:
            return triggerPort != null;
        case BehaviorPackage.TRANSITION__ACTIONS:
            return actions != null && !actions.isEmpty();
        case BehaviorPackage.TRANSITION__GUARD:
            return guard != null;
        }
        return super.eIsSet(featureID);
    }

} //TransitionImpl
