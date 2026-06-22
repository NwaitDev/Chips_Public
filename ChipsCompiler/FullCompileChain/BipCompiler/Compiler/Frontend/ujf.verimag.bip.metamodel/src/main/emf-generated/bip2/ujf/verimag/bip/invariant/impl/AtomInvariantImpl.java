/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
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

package bip2.ujf.verimag.bip.invariant.impl;

import bip2.ujf.verimag.bip.actionlang.ValuedExpression;

import bip2.ujf.verimag.bip.behavior.State;

import bip2.ujf.verimag.bip.invariant.AtomInvariant;
import bip2.ujf.verimag.bip.invariant.InvariantPackage;

import java.util.Collection;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

import org.eclipse.emf.ecore.util.EObjectResolvingEList;

import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Atom Invariant</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.invariant.impl.AtomInvariantImpl#getName <em>Name</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.invariant.impl.AtomInvariantImpl#getGuard <em>Guard</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.invariant.impl.AtomInvariantImpl#isExactState <em>Exact State</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.invariant.impl.AtomInvariantImpl#getSources <em>Sources</em>}</li>
 * </ul>
 *
 * @generated
 */
public class AtomInvariantImpl extends AnnotatedEObjectImpl
        implements AtomInvariant {
    /**
     * The default value of the '{@link #getName() <em>Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getName()
     * @generated
     * @ordered
     */
    protected static final String NAME_EDEFAULT = null;

    /**
     * The cached value of the '{@link #getName() <em>Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getName()
     * @generated
     * @ordered
     */
    protected String name = NAME_EDEFAULT;

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
     * The default value of the '{@link #isExactState() <em>Exact State</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #isExactState()
     * @generated
     * @ordered
     */
    protected static final boolean EXACT_STATE_EDEFAULT = false;

    /**
     * The cached value of the '{@link #isExactState() <em>Exact State</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #isExactState()
     * @generated
     * @ordered
     */
    protected boolean exactState = EXACT_STATE_EDEFAULT;

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
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected AtomInvariantImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return InvariantPackage.Literals.ATOM_INVARIANT;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String getName() {
        return name;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setName(String newName) {
        String oldName = name;
        name = newName;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    InvariantPackage.ATOM_INVARIANT__NAME, oldName, name));
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
                    Notification.SET, InvariantPackage.ATOM_INVARIANT__GUARD,
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
                                - InvariantPackage.ATOM_INVARIANT__GUARD,
                        null, msgs);
            if (newGuard != null)
                msgs = ((InternalEObject) newGuard).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - InvariantPackage.ATOM_INVARIANT__GUARD,
                        null, msgs);
            msgs = basicSetGuard(newGuard, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    InvariantPackage.ATOM_INVARIANT__GUARD, newGuard,
                    newGuard));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean isExactState() {
        return exactState;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setExactState(boolean newExactState) {
        boolean oldExactState = exactState;
        exactState = newExactState;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    InvariantPackage.ATOM_INVARIANT__EXACT_STATE, oldExactState,
                    exactState));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<State> getSources() {
        if (sources == null) {
            sources = new EObjectResolvingEList<State>(State.class, this,
                    InvariantPackage.ATOM_INVARIANT__SOURCES);
        }
        return sources;
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
        case InvariantPackage.ATOM_INVARIANT__GUARD:
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
        case InvariantPackage.ATOM_INVARIANT__NAME:
            return getName();
        case InvariantPackage.ATOM_INVARIANT__GUARD:
            return getGuard();
        case InvariantPackage.ATOM_INVARIANT__EXACT_STATE:
            return isExactState();
        case InvariantPackage.ATOM_INVARIANT__SOURCES:
            return getSources();
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
        case InvariantPackage.ATOM_INVARIANT__NAME:
            setName((String) newValue);
            return;
        case InvariantPackage.ATOM_INVARIANT__GUARD:
            setGuard((ValuedExpression) newValue);
            return;
        case InvariantPackage.ATOM_INVARIANT__EXACT_STATE:
            setExactState((Boolean) newValue);
            return;
        case InvariantPackage.ATOM_INVARIANT__SOURCES:
            getSources().clear();
            getSources().addAll((Collection<? extends State>) newValue);
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
        case InvariantPackage.ATOM_INVARIANT__NAME:
            setName(NAME_EDEFAULT);
            return;
        case InvariantPackage.ATOM_INVARIANT__GUARD:
            setGuard((ValuedExpression) null);
            return;
        case InvariantPackage.ATOM_INVARIANT__EXACT_STATE:
            setExactState(EXACT_STATE_EDEFAULT);
            return;
        case InvariantPackage.ATOM_INVARIANT__SOURCES:
            getSources().clear();
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
        case InvariantPackage.ATOM_INVARIANT__NAME:
            return NAME_EDEFAULT == null ? name != null
                    : !NAME_EDEFAULT.equals(name);
        case InvariantPackage.ATOM_INVARIANT__GUARD:
            return guard != null;
        case InvariantPackage.ATOM_INVARIANT__EXACT_STATE:
            return exactState != EXACT_STATE_EDEFAULT;
        case InvariantPackage.ATOM_INVARIANT__SOURCES:
            return sources != null && !sources.isEmpty();
        }
        return super.eIsSet(featureID);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public String toString() {
        if (eIsProxy())
            return super.toString();

        StringBuffer result = new StringBuffer(super.toString());
        result.append(" (name: ");
        result.append(name);
        result.append(", exactState: ");
        result.append(exactState);
        result.append(')');
        return result.toString();
    }

} //AtomInvariantImpl
