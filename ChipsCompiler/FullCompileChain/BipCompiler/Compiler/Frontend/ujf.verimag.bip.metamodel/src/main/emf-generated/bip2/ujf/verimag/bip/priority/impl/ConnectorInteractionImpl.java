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

import bip2.ujf.verimag.bip.connector.ConnectorDeclaration;

import bip2.ujf.verimag.bip.port.SubPortDeclarationReference;

import bip2.ujf.verimag.bip.priority.ConnectorInteraction;
import bip2.ujf.verimag.bip.priority.PriorityPackage;

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
import org.eclipse.emf.ecore.util.InternalEList;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Connector Interaction</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.priority.impl.ConnectorInteractionImpl#getConnectorDeclaration <em>Connector Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.priority.impl.ConnectorInteractionImpl#getPortDeclarationReferences <em>Port Declaration References</em>}</li>
 * </ul>
 *
 * @generated
 */
public class ConnectorInteractionImpl extends AnnotatedEObjectImpl
        implements ConnectorInteraction {
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
     * The cached value of the '{@link #getPortDeclarationReferences() <em>Port Declaration References</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPortDeclarationReferences()
     * @generated
     * @ordered
     */
    protected EList<SubPortDeclarationReference> portDeclarationReferences;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected ConnectorInteractionImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return PriorityPackage.Literals.CONNECTOR_INTERACTION;
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
                            PriorityPackage.CONNECTOR_INTERACTION__CONNECTOR_DECLARATION,
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
                    PriorityPackage.CONNECTOR_INTERACTION__CONNECTOR_DECLARATION,
                    oldConnectorDeclaration, connectorDeclaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<SubPortDeclarationReference> getPortDeclarationReferences() {
        if (portDeclarationReferences == null) {
            portDeclarationReferences = new EObjectContainmentEList<SubPortDeclarationReference>(
                    SubPortDeclarationReference.class, this,
                    PriorityPackage.CONNECTOR_INTERACTION__PORT_DECLARATION_REFERENCES);
        }
        return portDeclarationReferences;
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
        case PriorityPackage.CONNECTOR_INTERACTION__PORT_DECLARATION_REFERENCES:
            return ((InternalEList<?>) getPortDeclarationReferences())
                    .basicRemove(otherEnd, msgs);
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
        case PriorityPackage.CONNECTOR_INTERACTION__CONNECTOR_DECLARATION:
            if (resolve)
                return getConnectorDeclaration();
            return basicGetConnectorDeclaration();
        case PriorityPackage.CONNECTOR_INTERACTION__PORT_DECLARATION_REFERENCES:
            return getPortDeclarationReferences();
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
        case PriorityPackage.CONNECTOR_INTERACTION__CONNECTOR_DECLARATION:
            setConnectorDeclaration((ConnectorDeclaration) newValue);
            return;
        case PriorityPackage.CONNECTOR_INTERACTION__PORT_DECLARATION_REFERENCES:
            getPortDeclarationReferences().clear();
            getPortDeclarationReferences().addAll(
                    (Collection<? extends SubPortDeclarationReference>) newValue);
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
        case PriorityPackage.CONNECTOR_INTERACTION__CONNECTOR_DECLARATION:
            setConnectorDeclaration((ConnectorDeclaration) null);
            return;
        case PriorityPackage.CONNECTOR_INTERACTION__PORT_DECLARATION_REFERENCES:
            getPortDeclarationReferences().clear();
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
        case PriorityPackage.CONNECTOR_INTERACTION__CONNECTOR_DECLARATION:
            return connectorDeclaration != null;
        case PriorityPackage.CONNECTOR_INTERACTION__PORT_DECLARATION_REFERENCES:
            return portDeclarationReferences != null
                    && !portDeclarationReferences.isEmpty();
        }
        return super.eIsSet(featureID);
    }

} //ConnectorInteractionImpl
