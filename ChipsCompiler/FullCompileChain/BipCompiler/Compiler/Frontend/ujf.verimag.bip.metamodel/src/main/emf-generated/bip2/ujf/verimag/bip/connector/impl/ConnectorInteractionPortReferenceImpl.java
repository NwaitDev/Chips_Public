/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
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

import bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference;
import bip2.ujf.verimag.bip.connector.ConnectorPackage;
import bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.common.notify.NotificationChain;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Interaction Port Reference</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionPortReferenceImpl#getPort <em>Port</em>}</li>
 * </ul>
 *
 * @generated
 */
public class ConnectorInteractionPortReferenceImpl
        extends ConnectorInteractionDefinitionImpl
        implements ConnectorInteractionPortReference {
    /**
     * The cached value of the '{@link #getPort() <em>Port</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPort()
     * @generated
     * @ordered
     */
    protected ConnectorPortParameterDeclaration port;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected ConnectorInteractionPortReferenceImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return ConnectorPackage.Literals.CONNECTOR_INTERACTION_PORT_REFERENCE;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorPortParameterDeclaration getPort() {
        if (port != null && ((EObject) port).eIsProxy()) {
            InternalEObject oldPort = (InternalEObject) port;
            port = (ConnectorPortParameterDeclaration) eResolveProxy(oldPort);
            if (port != oldPort) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            ConnectorPackage.CONNECTOR_INTERACTION_PORT_REFERENCE__PORT,
                            oldPort, port));
            }
        }
        return port;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorPortParameterDeclaration basicGetPort() {
        return port;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setPort(ConnectorPortParameterDeclaration newPort) {
        ConnectorPortParameterDeclaration oldPort = port;
        port = newPort;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ConnectorPackage.CONNECTOR_INTERACTION_PORT_REFERENCE__PORT,
                    oldPort, port));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case ConnectorPackage.CONNECTOR_INTERACTION_PORT_REFERENCE__PORT:
            if (resolve)
                return getPort();
            return basicGetPort();
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
        case ConnectorPackage.CONNECTOR_INTERACTION_PORT_REFERENCE__PORT:
            setPort((ConnectorPortParameterDeclaration) newValue);
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
        case ConnectorPackage.CONNECTOR_INTERACTION_PORT_REFERENCE__PORT:
            setPort((ConnectorPortParameterDeclaration) null);
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
        case ConnectorPackage.CONNECTOR_INTERACTION_PORT_REFERENCE__PORT:
            return port != null;
        }
        return super.eIsSet(featureID);
    }

} //ConnectorInteractionPortReferenceImpl
