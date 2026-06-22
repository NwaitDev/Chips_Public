/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
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

import bip2.ujf.verimag.bip.connector.ConnectorPackage;
import bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration;

import bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter;

import bip2.ujf.verimag.bip.types.PortType;

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
 * An implementation of the model object '<em><b>Port Parameter Declaration</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.connector.impl.ConnectorPortParameterDeclarationImpl#getPortType <em>Port Type</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.connector.impl.ConnectorPortParameterDeclarationImpl#getName <em>Name</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.connector.impl.ConnectorPortParameterDeclarationImpl#getDataParameters <em>Data Parameters</em>}</li>
 * </ul>
 *
 * @generated
 */
public class ConnectorPortParameterDeclarationImpl extends AnnotatedEObjectImpl
        implements ConnectorPortParameterDeclaration {
    /**
     * The cached value of the '{@link #getPortType() <em>Port Type</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPortType()
     * @generated
     * @ordered
     */
    protected PortType portType;

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
     * The cached value of the '{@link #getDataParameters() <em>Data Parameters</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDataParameters()
     * @generated
     * @ordered
     */
    protected EList<DataDeclarationReferenceDataParameter> dataParameters;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected ConnectorPortParameterDeclarationImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return ConnectorPackage.Literals.CONNECTOR_PORT_PARAMETER_DECLARATION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PortType getPortType() {
        if (portType != null && ((EObject) portType).eIsProxy()) {
            InternalEObject oldPortType = (InternalEObject) portType;
            portType = (PortType) eResolveProxy(oldPortType);
            if (portType != oldPortType) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__PORT_TYPE,
                            oldPortType, portType));
            }
        }
        return portType;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PortType basicGetPortType() {
        return portType;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setPortType(PortType newPortType) {
        PortType oldPortType = portType;
        portType = newPortType;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__PORT_TYPE,
                    oldPortType, portType));
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
                    ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__NAME,
                    oldName, name));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<DataDeclarationReferenceDataParameter> getDataParameters() {
        if (dataParameters == null) {
            dataParameters = new EObjectContainmentEList<DataDeclarationReferenceDataParameter>(
                    DataDeclarationReferenceDataParameter.class, this,
                    ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__DATA_PARAMETERS);
        }
        return dataParameters;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public DataDeclarationReferenceDataParameter getDataParameter(String name) {
        for (DataDeclarationReferenceDataParameter ddrd : getDataParameters()) {
            if (ddrd.getParameterDeclaration().getName().equals(name)) {
                return ddrd;
            }
        }
        return null;
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
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__DATA_PARAMETERS:
            return ((InternalEList<?>) getDataParameters())
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
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__PORT_TYPE:
            if (resolve)
                return getPortType();
            return basicGetPortType();
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__NAME:
            return getName();
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__DATA_PARAMETERS:
            return getDataParameters();
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
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__PORT_TYPE:
            setPortType((PortType) newValue);
            return;
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__NAME:
            setName((String) newValue);
            return;
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__DATA_PARAMETERS:
            getDataParameters().clear();
            getDataParameters().addAll(
                    (Collection<? extends DataDeclarationReferenceDataParameter>) newValue);
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
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__PORT_TYPE:
            setPortType((PortType) null);
            return;
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__NAME:
            setName(NAME_EDEFAULT);
            return;
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__DATA_PARAMETERS:
            getDataParameters().clear();
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
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__PORT_TYPE:
            return portType != null;
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__NAME:
            return NAME_EDEFAULT == null ? name != null
                    : !NAME_EDEFAULT.equals(name);
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION__DATA_PARAMETERS:
            return dataParameters != null && !dataParameters.isEmpty();
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

} //ConnectorPortParameterDeclarationImpl
