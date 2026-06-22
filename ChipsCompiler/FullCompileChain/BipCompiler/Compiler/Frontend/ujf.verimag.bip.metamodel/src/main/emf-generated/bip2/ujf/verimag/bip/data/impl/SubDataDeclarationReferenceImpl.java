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

package bip2.ujf.verimag.bip.data.impl;

import bip2.ujf.verimag.bip.component.ComponentDeclaration;

import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataPackage;
import bip2.ujf.verimag.bip.data.SubDataDeclarationReference;

import bip2.ujf.verimag.bip.port.PortDeclaration;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

import org.eclipse.emf.ecore.impl.EObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Sub Data Declaration Reference</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.data.impl.SubDataDeclarationReferenceImpl#getForwardDataDeclaration <em>Forward Data Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.data.impl.SubDataDeclarationReferenceImpl#getComponentDeclaration <em>Component Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.data.impl.SubDataDeclarationReferenceImpl#getPortDeclaration <em>Port Declaration</em>}</li>
 * </ul>
 *
 * @generated
 */
public class SubDataDeclarationReferenceImpl extends AnnotatedEObjectImpl
        implements SubDataDeclarationReference {
    /**
     * The cached value of the '{@link #getForwardDataDeclaration() <em>Forward Data Declaration</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getForwardDataDeclaration()
     * @generated
     * @ordered
     */
    protected DataDeclaration forwardDataDeclaration;

    /**
     * The cached value of the '{@link #getComponentDeclaration() <em>Component Declaration</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getComponentDeclaration()
     * @generated
     * @ordered
     */
    protected ComponentDeclaration componentDeclaration;

    /**
     * The cached value of the '{@link #getPortDeclaration() <em>Port Declaration</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPortDeclaration()
     * @generated
     * @ordered
     */
    protected PortDeclaration portDeclaration;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected SubDataDeclarationReferenceImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return DataPackage.Literals.SUB_DATA_DECLARATION_REFERENCE;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataDeclaration getForwardDataDeclaration() {
        if (forwardDataDeclaration != null
                && ((EObject) forwardDataDeclaration).eIsProxy()) {
            InternalEObject oldForwardDataDeclaration = (InternalEObject) forwardDataDeclaration;
            forwardDataDeclaration = (DataDeclaration) eResolveProxy(
                    oldForwardDataDeclaration);
            if (forwardDataDeclaration != oldForwardDataDeclaration) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            DataPackage.SUB_DATA_DECLARATION_REFERENCE__FORWARD_DATA_DECLARATION,
                            oldForwardDataDeclaration, forwardDataDeclaration));
            }
        }
        return forwardDataDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataDeclaration basicGetForwardDataDeclaration() {
        return forwardDataDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setForwardDataDeclaration(
            DataDeclaration newForwardDataDeclaration) {
        DataDeclaration oldForwardDataDeclaration = forwardDataDeclaration;
        forwardDataDeclaration = newForwardDataDeclaration;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    DataPackage.SUB_DATA_DECLARATION_REFERENCE__FORWARD_DATA_DECLARATION,
                    oldForwardDataDeclaration, forwardDataDeclaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ComponentDeclaration getComponentDeclaration() {
        if (componentDeclaration != null
                && ((EObject) componentDeclaration).eIsProxy()) {
            InternalEObject oldComponentDeclaration = (InternalEObject) componentDeclaration;
            componentDeclaration = (ComponentDeclaration) eResolveProxy(
                    oldComponentDeclaration);
            if (componentDeclaration != oldComponentDeclaration) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            DataPackage.SUB_DATA_DECLARATION_REFERENCE__COMPONENT_DECLARATION,
                            oldComponentDeclaration, componentDeclaration));
            }
        }
        return componentDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ComponentDeclaration basicGetComponentDeclaration() {
        return componentDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setComponentDeclaration(
            ComponentDeclaration newComponentDeclaration) {
        ComponentDeclaration oldComponentDeclaration = componentDeclaration;
        componentDeclaration = newComponentDeclaration;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    DataPackage.SUB_DATA_DECLARATION_REFERENCE__COMPONENT_DECLARATION,
                    oldComponentDeclaration, componentDeclaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PortDeclaration getPortDeclaration() {
        if (portDeclaration != null && ((EObject) portDeclaration).eIsProxy()) {
            InternalEObject oldPortDeclaration = (InternalEObject) portDeclaration;
            portDeclaration = (PortDeclaration) eResolveProxy(
                    oldPortDeclaration);
            if (portDeclaration != oldPortDeclaration) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            DataPackage.SUB_DATA_DECLARATION_REFERENCE__PORT_DECLARATION,
                            oldPortDeclaration, portDeclaration));
            }
        }
        return portDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PortDeclaration basicGetPortDeclaration() {
        return portDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setPortDeclaration(PortDeclaration newPortDeclaration) {
        PortDeclaration oldPortDeclaration = portDeclaration;
        portDeclaration = newPortDeclaration;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    DataPackage.SUB_DATA_DECLARATION_REFERENCE__PORT_DECLARATION,
                    oldPortDeclaration, portDeclaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case DataPackage.SUB_DATA_DECLARATION_REFERENCE__FORWARD_DATA_DECLARATION:
            if (resolve)
                return getForwardDataDeclaration();
            return basicGetForwardDataDeclaration();
        case DataPackage.SUB_DATA_DECLARATION_REFERENCE__COMPONENT_DECLARATION:
            if (resolve)
                return getComponentDeclaration();
            return basicGetComponentDeclaration();
        case DataPackage.SUB_DATA_DECLARATION_REFERENCE__PORT_DECLARATION:
            if (resolve)
                return getPortDeclaration();
            return basicGetPortDeclaration();
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
        case DataPackage.SUB_DATA_DECLARATION_REFERENCE__FORWARD_DATA_DECLARATION:
            setForwardDataDeclaration((DataDeclaration) newValue);
            return;
        case DataPackage.SUB_DATA_DECLARATION_REFERENCE__COMPONENT_DECLARATION:
            setComponentDeclaration((ComponentDeclaration) newValue);
            return;
        case DataPackage.SUB_DATA_DECLARATION_REFERENCE__PORT_DECLARATION:
            setPortDeclaration((PortDeclaration) newValue);
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
        case DataPackage.SUB_DATA_DECLARATION_REFERENCE__FORWARD_DATA_DECLARATION:
            setForwardDataDeclaration((DataDeclaration) null);
            return;
        case DataPackage.SUB_DATA_DECLARATION_REFERENCE__COMPONENT_DECLARATION:
            setComponentDeclaration((ComponentDeclaration) null);
            return;
        case DataPackage.SUB_DATA_DECLARATION_REFERENCE__PORT_DECLARATION:
            setPortDeclaration((PortDeclaration) null);
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
        case DataPackage.SUB_DATA_DECLARATION_REFERENCE__FORWARD_DATA_DECLARATION:
            return forwardDataDeclaration != null;
        case DataPackage.SUB_DATA_DECLARATION_REFERENCE__COMPONENT_DECLARATION:
            return componentDeclaration != null;
        case DataPackage.SUB_DATA_DECLARATION_REFERENCE__PORT_DECLARATION:
            return portDeclaration != null;
        }
        return super.eIsSet(featureID);
    }

} //SubDataDeclarationReferenceImpl
