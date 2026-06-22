/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
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

package bip2.ujf.verimag.bip.priority.impl;

import bip2.ujf.verimag.bip.actionlang.ValuedExpression;

import bip2.ujf.verimag.bip.component.atom.AtomInternalPortDeclaration;

import bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration;
import bip2.ujf.verimag.bip.priority.PriorityPackage;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Atom Priority Declaration</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.priority.impl.AtomPriorityDeclarationImpl#getGuard <em>Guard</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.priority.impl.AtomPriorityDeclarationImpl#getLow <em>Low</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.priority.impl.AtomPriorityDeclarationImpl#getHigh <em>High</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.priority.impl.AtomPriorityDeclarationImpl#getName <em>Name</em>}</li>
 * </ul>
 *
 * @generated
 */
public class AtomPriorityDeclarationImpl extends AnnotatedEObjectImpl
        implements AtomPriorityDeclaration {
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
     * The cached value of the '{@link #getLow() <em>Low</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getLow()
     * @generated
     * @ordered
     */
    protected AtomInternalPortDeclaration low;

    /**
     * The cached value of the '{@link #getHigh() <em>High</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getHigh()
     * @generated
     * @ordered
     */
    protected AtomInternalPortDeclaration high;

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
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected AtomPriorityDeclarationImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return PriorityPackage.Literals.ATOM_PRIORITY_DECLARATION;
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
                    PriorityPackage.ATOM_PRIORITY_DECLARATION__GUARD, oldGuard,
                    newGuard);
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
                                - PriorityPackage.ATOM_PRIORITY_DECLARATION__GUARD,
                        null, msgs);
            if (newGuard != null)
                msgs = ((InternalEObject) newGuard).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - PriorityPackage.ATOM_PRIORITY_DECLARATION__GUARD,
                        null, msgs);
            msgs = basicSetGuard(newGuard, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PriorityPackage.ATOM_PRIORITY_DECLARATION__GUARD, newGuard,
                    newGuard));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomInternalPortDeclaration getLow() {
        if (low != null && ((EObject) low).eIsProxy()) {
            InternalEObject oldLow = (InternalEObject) low;
            low = (AtomInternalPortDeclaration) eResolveProxy(oldLow);
            if (low != oldLow) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            PriorityPackage.ATOM_PRIORITY_DECLARATION__LOW,
                            oldLow, low));
            }
        }
        return low;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomInternalPortDeclaration basicGetLow() {
        return low;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setLow(AtomInternalPortDeclaration newLow) {
        AtomInternalPortDeclaration oldLow = low;
        low = newLow;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PriorityPackage.ATOM_PRIORITY_DECLARATION__LOW, oldLow,
                    low));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomInternalPortDeclaration getHigh() {
        if (high != null && ((EObject) high).eIsProxy()) {
            InternalEObject oldHigh = (InternalEObject) high;
            high = (AtomInternalPortDeclaration) eResolveProxy(oldHigh);
            if (high != oldHigh) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            PriorityPackage.ATOM_PRIORITY_DECLARATION__HIGH,
                            oldHigh, high));
            }
        }
        return high;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomInternalPortDeclaration basicGetHigh() {
        return high;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setHigh(AtomInternalPortDeclaration newHigh) {
        AtomInternalPortDeclaration oldHigh = high;
        high = newHigh;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PriorityPackage.ATOM_PRIORITY_DECLARATION__HIGH, oldHigh,
                    high));
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
                    PriorityPackage.ATOM_PRIORITY_DECLARATION__NAME, oldName,
                    name));
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
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__GUARD:
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
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__GUARD:
            return getGuard();
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__LOW:
            if (resolve)
                return getLow();
            return basicGetLow();
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__HIGH:
            if (resolve)
                return getHigh();
            return basicGetHigh();
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__NAME:
            return getName();
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
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__GUARD:
            setGuard((ValuedExpression) newValue);
            return;
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__LOW:
            setLow((AtomInternalPortDeclaration) newValue);
            return;
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__HIGH:
            setHigh((AtomInternalPortDeclaration) newValue);
            return;
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__NAME:
            setName((String) newValue);
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
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__GUARD:
            setGuard((ValuedExpression) null);
            return;
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__LOW:
            setLow((AtomInternalPortDeclaration) null);
            return;
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__HIGH:
            setHigh((AtomInternalPortDeclaration) null);
            return;
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__NAME:
            setName(NAME_EDEFAULT);
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
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__GUARD:
            return guard != null;
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__LOW:
            return low != null;
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__HIGH:
            return high != null;
        case PriorityPackage.ATOM_PRIORITY_DECLARATION__NAME:
            return NAME_EDEFAULT == null ? name != null
                    : !NAME_EDEFAULT.equals(name);
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
        result.append(')');
        return result.toString();
    }

} //AtomPriorityDeclarationImpl
