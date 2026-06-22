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

import bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration;
import bip2.ujf.verimag.bip.priority.ConnectorInteraction;
import bip2.ujf.verimag.bip.priority.PriorityPackage;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Compound Priority Declaration</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.priority.impl.CompoundPriorityDeclarationImpl#getLow <em>Low</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.priority.impl.CompoundPriorityDeclarationImpl#getHigh <em>High</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.priority.impl.CompoundPriorityDeclarationImpl#getGuard <em>Guard</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.priority.impl.CompoundPriorityDeclarationImpl#getName <em>Name</em>}</li>
 * </ul>
 *
 * @generated
 */
public class CompoundPriorityDeclarationImpl extends AnnotatedEObjectImpl
        implements CompoundPriorityDeclaration {
    /**
     * The cached value of the '{@link #getLow() <em>Low</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getLow()
     * @generated
     * @ordered
     */
    protected ConnectorInteraction low;

    /**
     * The cached value of the '{@link #getHigh() <em>High</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getHigh()
     * @generated
     * @ordered
     */
    protected ConnectorInteraction high;

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
    protected CompoundPriorityDeclarationImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return PriorityPackage.Literals.COMPOUND_PRIORITY_DECLARATION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorInteraction getLow() {
        return low;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetLow(ConnectorInteraction newLow,
            NotificationChain msgs) {
        ConnectorInteraction oldLow = low;
        low = newLow;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    PriorityPackage.COMPOUND_PRIORITY_DECLARATION__LOW, oldLow,
                    newLow);
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
    public void setLow(ConnectorInteraction newLow) {
        if (newLow != low) {
            NotificationChain msgs = null;
            if (low != null)
                msgs = ((InternalEObject) low).eInverseRemove(this,
                        EOPPOSITE_FEATURE_BASE
                                - PriorityPackage.COMPOUND_PRIORITY_DECLARATION__LOW,
                        null, msgs);
            if (newLow != null)
                msgs = ((InternalEObject) newLow).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - PriorityPackage.COMPOUND_PRIORITY_DECLARATION__LOW,
                        null, msgs);
            msgs = basicSetLow(newLow, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PriorityPackage.COMPOUND_PRIORITY_DECLARATION__LOW, newLow,
                    newLow));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorInteraction getHigh() {
        return high;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetHigh(ConnectorInteraction newHigh,
            NotificationChain msgs) {
        ConnectorInteraction oldHigh = high;
        high = newHigh;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    PriorityPackage.COMPOUND_PRIORITY_DECLARATION__HIGH,
                    oldHigh, newHigh);
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
    public void setHigh(ConnectorInteraction newHigh) {
        if (newHigh != high) {
            NotificationChain msgs = null;
            if (high != null)
                msgs = ((InternalEObject) high).eInverseRemove(this,
                        EOPPOSITE_FEATURE_BASE
                                - PriorityPackage.COMPOUND_PRIORITY_DECLARATION__HIGH,
                        null, msgs);
            if (newHigh != null)
                msgs = ((InternalEObject) newHigh).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - PriorityPackage.COMPOUND_PRIORITY_DECLARATION__HIGH,
                        null, msgs);
            msgs = basicSetHigh(newHigh, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PriorityPackage.COMPOUND_PRIORITY_DECLARATION__HIGH,
                    newHigh, newHigh));
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
                    PriorityPackage.COMPOUND_PRIORITY_DECLARATION__GUARD,
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
                                - PriorityPackage.COMPOUND_PRIORITY_DECLARATION__GUARD,
                        null, msgs);
            if (newGuard != null)
                msgs = ((InternalEObject) newGuard).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - PriorityPackage.COMPOUND_PRIORITY_DECLARATION__GUARD,
                        null, msgs);
            msgs = basicSetGuard(newGuard, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PriorityPackage.COMPOUND_PRIORITY_DECLARATION__GUARD,
                    newGuard, newGuard));
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
                    PriorityPackage.COMPOUND_PRIORITY_DECLARATION__NAME,
                    oldName, name));
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
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__LOW:
            return basicSetLow(null, msgs);
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__HIGH:
            return basicSetHigh(null, msgs);
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__GUARD:
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
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__LOW:
            return getLow();
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__HIGH:
            return getHigh();
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__GUARD:
            return getGuard();
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__NAME:
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
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__LOW:
            setLow((ConnectorInteraction) newValue);
            return;
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__HIGH:
            setHigh((ConnectorInteraction) newValue);
            return;
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__GUARD:
            setGuard((ValuedExpression) newValue);
            return;
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__NAME:
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
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__LOW:
            setLow((ConnectorInteraction) null);
            return;
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__HIGH:
            setHigh((ConnectorInteraction) null);
            return;
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__GUARD:
            setGuard((ValuedExpression) null);
            return;
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__NAME:
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
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__LOW:
            return low != null;
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__HIGH:
            return high != null;
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__GUARD:
            return guard != null;
        case PriorityPackage.COMPOUND_PRIORITY_DECLARATION__NAME:
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

} //CompoundPriorityDeclarationImpl
