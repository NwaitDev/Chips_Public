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

package bip2.ujf.verimag.bip.port.impl;

import bip2.ujf.verimag.bip.component.ComponentDeclaration;

import bip2.ujf.verimag.bip.connector.ConnectorDeclaration;

import bip2.ujf.verimag.bip.port.PortDeclaration;
import bip2.ujf.verimag.bip.port.PortPackage;
import bip2.ujf.verimag.bip.port.SubPortDeclarationReference;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

import org.eclipse.emf.ecore.impl.EObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Sub Port Declaration Reference</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.port.impl.SubPortDeclarationReferenceImpl#getForwardPortDeclaration <em>Forward Port Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.port.impl.SubPortDeclarationReferenceImpl#getComponentDeclaration <em>Component Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.port.impl.SubPortDeclarationReferenceImpl#getConnectorDeclaration <em>Connector Declaration</em>}</li>
 * </ul>
 *
 * @generated
 */
public class SubPortDeclarationReferenceImpl extends AnnotatedEObjectImpl
        implements SubPortDeclarationReference {
    /**
     * The cached value of the '{@link #getForwardPortDeclaration() <em>Forward Port Declaration</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getForwardPortDeclaration()
     * @generated
     * @ordered
     */
    protected PortDeclaration forwardPortDeclaration;

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
     * The cached value of the '{@link #getConnectorDeclaration() <em>Connector Declaration</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getConnectorDeclaration()
     * @generated
     * @ordered
     */
    protected ConnectorDeclaration connectorDeclaration;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected SubPortDeclarationReferenceImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return PortPackage.Literals.SUB_PORT_DECLARATION_REFERENCE;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PortDeclaration getForwardPortDeclaration() {
        if (forwardPortDeclaration != null
                && ((EObject) forwardPortDeclaration).eIsProxy()) {
            InternalEObject oldForwardPortDeclaration = (InternalEObject) forwardPortDeclaration;
            forwardPortDeclaration = (PortDeclaration) eResolveProxy(
                    oldForwardPortDeclaration);
            if (forwardPortDeclaration != oldForwardPortDeclaration) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            PortPackage.SUB_PORT_DECLARATION_REFERENCE__FORWARD_PORT_DECLARATION,
                            oldForwardPortDeclaration, forwardPortDeclaration));
            }
        }
        return forwardPortDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PortDeclaration basicGetForwardPortDeclaration() {
        return forwardPortDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setForwardPortDeclaration(
            PortDeclaration newForwardPortDeclaration) {
        PortDeclaration oldForwardPortDeclaration = forwardPortDeclaration;
        forwardPortDeclaration = newForwardPortDeclaration;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PortPackage.SUB_PORT_DECLARATION_REFERENCE__FORWARD_PORT_DECLARATION,
                    oldForwardPortDeclaration, forwardPortDeclaration));
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
                            PortPackage.SUB_PORT_DECLARATION_REFERENCE__COMPONENT_DECLARATION,
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
                    PortPackage.SUB_PORT_DECLARATION_REFERENCE__COMPONENT_DECLARATION,
                    oldComponentDeclaration, componentDeclaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorDeclaration getConnectorDeclaration() {
        if (connectorDeclaration != null
                && ((EObject) connectorDeclaration).eIsProxy()) {
            InternalEObject oldConnectorDeclaration = (InternalEObject) connectorDeclaration;
            connectorDeclaration = (ConnectorDeclaration) eResolveProxy(
                    oldConnectorDeclaration);
            if (connectorDeclaration != oldConnectorDeclaration) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            PortPackage.SUB_PORT_DECLARATION_REFERENCE__CONNECTOR_DECLARATION,
                            oldConnectorDeclaration, connectorDeclaration));
            }
        }
        return connectorDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorDeclaration basicGetConnectorDeclaration() {
        return connectorDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setConnectorDeclaration(
            ConnectorDeclaration newConnectorDeclaration) {
        ConnectorDeclaration oldConnectorDeclaration = connectorDeclaration;
        connectorDeclaration = newConnectorDeclaration;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PortPackage.SUB_PORT_DECLARATION_REFERENCE__CONNECTOR_DECLARATION,
                    oldConnectorDeclaration, connectorDeclaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case PortPackage.SUB_PORT_DECLARATION_REFERENCE__FORWARD_PORT_DECLARATION:
            if (resolve)
                return getForwardPortDeclaration();
            return basicGetForwardPortDeclaration();
        case PortPackage.SUB_PORT_DECLARATION_REFERENCE__COMPONENT_DECLARATION:
            if (resolve)
                return getComponentDeclaration();
            return basicGetComponentDeclaration();
        case PortPackage.SUB_PORT_DECLARATION_REFERENCE__CONNECTOR_DECLARATION:
            if (resolve)
                return getConnectorDeclaration();
            return basicGetConnectorDeclaration();
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
        case PortPackage.SUB_PORT_DECLARATION_REFERENCE__FORWARD_PORT_DECLARATION:
            setForwardPortDeclaration((PortDeclaration) newValue);
            return;
        case PortPackage.SUB_PORT_DECLARATION_REFERENCE__COMPONENT_DECLARATION:
            setComponentDeclaration((ComponentDeclaration) newValue);
            return;
        case PortPackage.SUB_PORT_DECLARATION_REFERENCE__CONNECTOR_DECLARATION:
            setConnectorDeclaration((ConnectorDeclaration) newValue);
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
        case PortPackage.SUB_PORT_DECLARATION_REFERENCE__FORWARD_PORT_DECLARATION:
            setForwardPortDeclaration((PortDeclaration) null);
            return;
        case PortPackage.SUB_PORT_DECLARATION_REFERENCE__COMPONENT_DECLARATION:
            setComponentDeclaration((ComponentDeclaration) null);
            return;
        case PortPackage.SUB_PORT_DECLARATION_REFERENCE__CONNECTOR_DECLARATION:
            setConnectorDeclaration((ConnectorDeclaration) null);
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
        case PortPackage.SUB_PORT_DECLARATION_REFERENCE__FORWARD_PORT_DECLARATION:
            return forwardPortDeclaration != null;
        case PortPackage.SUB_PORT_DECLARATION_REFERENCE__COMPONENT_DECLARATION:
            return componentDeclaration != null;
        case PortPackage.SUB_PORT_DECLARATION_REFERENCE__CONNECTOR_DECLARATION:
            return connectorDeclaration != null;
        }
        return super.eIsSet(featureID);
    }

} //SubPortDeclarationReferenceImpl
