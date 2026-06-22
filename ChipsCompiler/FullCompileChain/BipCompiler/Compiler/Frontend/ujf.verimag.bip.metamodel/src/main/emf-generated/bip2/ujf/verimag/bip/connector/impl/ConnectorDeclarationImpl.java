/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Anakreontas Mentis
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

package bip2.ujf.verimag.bip.connector.impl;

import bip2.ujf.verimag.bip.annotation.impl.AnnotatedElementImpl;
import bip2.ujf.verimag.bip.connector.ConnectorDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorPackage;

import bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter;

import bip2.ujf.verimag.bip.types.ConnectorType;

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
 * An implementation of the model object '<em><b>Declaration</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.connector.impl.ConnectorDeclarationImpl#getType <em>Type</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.connector.impl.ConnectorDeclarationImpl#getPortParameters <em>Port Parameters</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.connector.impl.ConnectorDeclarationImpl#getName <em>Name</em>}</li>
 * </ul>
 *
 * @generated
 */
public class ConnectorDeclarationImpl extends AnnotatedElementImpl
        implements ConnectorDeclaration {
    /**
     * The cached value of the '{@link #getType() <em>Type</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getType()
     * @generated
     * @ordered
     */
    protected ConnectorType type;

    /**
     * The cached value of the '{@link #getPortParameters() <em>Port Parameters</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPortParameters()
     * @generated
     * @ordered
     */
    protected EList<PortDeclarationReferenceParameter> portParameters;

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
    protected ConnectorDeclarationImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return ConnectorPackage.Literals.CONNECTOR_DECLARATION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorType getType() {
        if (type != null && ((EObject) type).eIsProxy()) {
            InternalEObject oldType = (InternalEObject) type;
            type = (ConnectorType) eResolveProxy(oldType);
            if (type != oldType) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            ConnectorPackage.CONNECTOR_DECLARATION__TYPE,
                            oldType, type));
            }
        }
        return type;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorType basicGetType() {
        return type;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setType(ConnectorType newType) {
        ConnectorType oldType = type;
        type = newType;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ConnectorPackage.CONNECTOR_DECLARATION__TYPE, oldType,
                    type));
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
                    ConnectorPackage.CONNECTOR_DECLARATION__NAME, oldName,
                    name));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<PortDeclarationReferenceParameter> getPortParameters() {
        if (portParameters == null) {
            portParameters = new EObjectContainmentEList<PortDeclarationReferenceParameter>(
                    PortDeclarationReferenceParameter.class, this,
                    ConnectorPackage.CONNECTOR_DECLARATION__PORT_PARAMETERS);
        }
        return portParameters;
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
        case ConnectorPackage.CONNECTOR_DECLARATION__PORT_PARAMETERS:
            return ((InternalEList<?>) getPortParameters())
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
        case ConnectorPackage.CONNECTOR_DECLARATION__TYPE:
            if (resolve)
                return getType();
            return basicGetType();
        case ConnectorPackage.CONNECTOR_DECLARATION__PORT_PARAMETERS:
            return getPortParameters();
        case ConnectorPackage.CONNECTOR_DECLARATION__NAME:
            return getName();
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
        case ConnectorPackage.CONNECTOR_DECLARATION__TYPE:
            setType((ConnectorType) newValue);
            return;
        case ConnectorPackage.CONNECTOR_DECLARATION__PORT_PARAMETERS:
            getPortParameters().clear();
            getPortParameters().addAll(
                    (Collection<? extends PortDeclarationReferenceParameter>) newValue);
            return;
        case ConnectorPackage.CONNECTOR_DECLARATION__NAME:
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
        case ConnectorPackage.CONNECTOR_DECLARATION__TYPE:
            setType((ConnectorType) null);
            return;
        case ConnectorPackage.CONNECTOR_DECLARATION__PORT_PARAMETERS:
            getPortParameters().clear();
            return;
        case ConnectorPackage.CONNECTOR_DECLARATION__NAME:
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
        case ConnectorPackage.CONNECTOR_DECLARATION__TYPE:
            return type != null;
        case ConnectorPackage.CONNECTOR_DECLARATION__PORT_PARAMETERS:
            return portParameters != null && !portParameters.isEmpty();
        case ConnectorPackage.CONNECTOR_DECLARATION__NAME:
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

} //ConnectorDeclarationImpl
