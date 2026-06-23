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

package bip2.ujf.verimag.bip.instance.impl;

import bip2.ujf.verimag.bip.instance.CompoundPriorityInstance;
import bip2.ujf.verimag.bip.instance.ConnectorInstance;
import bip2.ujf.verimag.bip.instance.InstancePackage;

import bip2.ujf.verimag.bip.instance.PortInstance;
import bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration;

import java.util.Collection;
import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

import org.eclipse.emf.ecore.util.EObjectResolvingEList;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Compound Priority Instance</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.CompoundPriorityInstanceImpl#getDeclaration <em>Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.CompoundPriorityInstanceImpl#getLowConnector <em>Low Connector</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.CompoundPriorityInstanceImpl#getHighConnector <em>High Connector</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.CompoundPriorityInstanceImpl#getLowPorts <em>Low Ports</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.CompoundPriorityInstanceImpl#getHighPorts <em>High Ports</em>}</li>
 * </ul>
 *
 * @generated
 */
public class CompoundPriorityInstanceImpl extends AnnotatedEObjectImpl
        implements CompoundPriorityInstance {
    /**
     * The cached value of the '{@link #getDeclaration() <em>Declaration</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDeclaration()
     * @generated
     * @ordered
     */
    protected CompoundPriorityDeclaration declaration;

    /**
     * The cached value of the '{@link #getLowConnector() <em>Low Connector</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getLowConnector()
     * @generated
     * @ordered
     */
    protected ConnectorInstance lowConnector;
    /**
     * The cached value of the '{@link #getHighConnector() <em>High Connector</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getHighConnector()
     * @generated
     * @ordered
     */
    protected ConnectorInstance highConnector;
    /**
     * The cached value of the '{@link #getLowPorts() <em>Low Ports</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getLowPorts()
     * @generated
     * @ordered
     */
    protected EList<PortInstance> lowPorts;
    /**
     * The cached value of the '{@link #getHighPorts() <em>High Ports</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getHighPorts()
     * @generated
     * @ordered
     */
    protected EList<PortInstance> highPorts;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected CompoundPriorityInstanceImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return InstancePackage.Literals.COMPOUND_PRIORITY_INSTANCE;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public CompoundPriorityDeclaration getDeclaration() {
        if (declaration != null && ((EObject) declaration).eIsProxy()) {
            InternalEObject oldDeclaration = (InternalEObject) declaration;
            declaration = (CompoundPriorityDeclaration) eResolveProxy(
                    oldDeclaration);
            if (declaration != oldDeclaration) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            InstancePackage.COMPOUND_PRIORITY_INSTANCE__DECLARATION,
                            oldDeclaration, declaration));
            }
        }
        return declaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public CompoundPriorityDeclaration basicGetDeclaration() {
        return declaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setDeclaration(CompoundPriorityDeclaration newDeclaration) {
        CompoundPriorityDeclaration oldDeclaration = declaration;
        declaration = newDeclaration;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    InstancePackage.COMPOUND_PRIORITY_INSTANCE__DECLARATION,
                    oldDeclaration, declaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorInstance getLowConnector() {
        if (lowConnector != null && ((EObject) lowConnector).eIsProxy()) {
            InternalEObject oldLowConnector = (InternalEObject) lowConnector;
            lowConnector = (ConnectorInstance) eResolveProxy(oldLowConnector);
            if (lowConnector != oldLowConnector) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            InstancePackage.COMPOUND_PRIORITY_INSTANCE__LOW_CONNECTOR,
                            oldLowConnector, lowConnector));
            }
        }
        return lowConnector;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorInstance basicGetLowConnector() {
        return lowConnector;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setLowConnector(ConnectorInstance newLowConnector) {
        ConnectorInstance oldLowConnector = lowConnector;
        lowConnector = newLowConnector;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    InstancePackage.COMPOUND_PRIORITY_INSTANCE__LOW_CONNECTOR,
                    oldLowConnector, lowConnector));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorInstance getHighConnector() {
        if (highConnector != null && ((EObject) highConnector).eIsProxy()) {
            InternalEObject oldHighConnector = (InternalEObject) highConnector;
            highConnector = (ConnectorInstance) eResolveProxy(oldHighConnector);
            if (highConnector != oldHighConnector) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            InstancePackage.COMPOUND_PRIORITY_INSTANCE__HIGH_CONNECTOR,
                            oldHighConnector, highConnector));
            }
        }
        return highConnector;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorInstance basicGetHighConnector() {
        return highConnector;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setHighConnector(ConnectorInstance newHighConnector) {
        ConnectorInstance oldHighConnector = highConnector;
        highConnector = newHighConnector;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    InstancePackage.COMPOUND_PRIORITY_INSTANCE__HIGH_CONNECTOR,
                    oldHighConnector, highConnector));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<PortInstance> getLowPorts() {
        if (lowPorts == null) {
            lowPorts = new EObjectResolvingEList<PortInstance>(
                    PortInstance.class, this,
                    InstancePackage.COMPOUND_PRIORITY_INSTANCE__LOW_PORTS);
        }
        return lowPorts;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<PortInstance> getHighPorts() {
        if (highPorts == null) {
            highPorts = new EObjectResolvingEList<PortInstance>(
                    PortInstance.class, this,
                    InstancePackage.COMPOUND_PRIORITY_INSTANCE__HIGH_PORTS);
        }
        return highPorts;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__DECLARATION:
            if (resolve)
                return getDeclaration();
            return basicGetDeclaration();
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__LOW_CONNECTOR:
            if (resolve)
                return getLowConnector();
            return basicGetLowConnector();
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__HIGH_CONNECTOR:
            if (resolve)
                return getHighConnector();
            return basicGetHighConnector();
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__LOW_PORTS:
            return getLowPorts();
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__HIGH_PORTS:
            return getHighPorts();
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
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__DECLARATION:
            setDeclaration((CompoundPriorityDeclaration) newValue);
            return;
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__LOW_CONNECTOR:
            setLowConnector((ConnectorInstance) newValue);
            return;
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__HIGH_CONNECTOR:
            setHighConnector((ConnectorInstance) newValue);
            return;
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__LOW_PORTS:
            getLowPorts().clear();
            getLowPorts().addAll((Collection<? extends PortInstance>) newValue);
            return;
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__HIGH_PORTS:
            getHighPorts().clear();
            getHighPorts()
                    .addAll((Collection<? extends PortInstance>) newValue);
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
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__DECLARATION:
            setDeclaration((CompoundPriorityDeclaration) null);
            return;
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__LOW_CONNECTOR:
            setLowConnector((ConnectorInstance) null);
            return;
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__HIGH_CONNECTOR:
            setHighConnector((ConnectorInstance) null);
            return;
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__LOW_PORTS:
            getLowPorts().clear();
            return;
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__HIGH_PORTS:
            getHighPorts().clear();
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
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__DECLARATION:
            return declaration != null;
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__LOW_CONNECTOR:
            return lowConnector != null;
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__HIGH_CONNECTOR:
            return highConnector != null;
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__LOW_PORTS:
            return lowPorts != null && !lowPorts.isEmpty();
        case InstancePackage.COMPOUND_PRIORITY_INSTANCE__HIGH_PORTS:
            return highPorts != null && !highPorts.isEmpty();
        }
        return super.eIsSet(featureID);
    }

} //CompoundPriorityInstanceImpl
