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

import bip2.ujf.verimag.bip.connector.ConnectorDeclaration;

import bip2.ujf.verimag.bip.instance.ConnectorInstance;
import bip2.ujf.verimag.bip.instance.ConnectorPortInstance;
import bip2.ujf.verimag.bip.instance.DataInstance;
import bip2.ujf.verimag.bip.instance.InstancePackage;
import bip2.ujf.verimag.bip.instance.PortInstance;

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
import org.eclipse.emf.ecore.util.EObjectResolvingEList;
import org.eclipse.emf.ecore.util.InternalEList;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Connector Instance</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.ConnectorInstanceImpl#getDeclaration <em>Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.ConnectorInstanceImpl#getSubDataInstances <em>Sub Data Instances</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.ConnectorInstanceImpl#getPortParamInstances <em>Port Param Instances</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.ConnectorInstanceImpl#getExportedPort <em>Exported Port</em>}</li>
 * </ul>
 *
 * @generated
 */
public class ConnectorInstanceImpl extends AnnotatedEObjectImpl
        implements ConnectorInstance {
    /**
     * The cached value of the '{@link #getDeclaration() <em>Declaration</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDeclaration()
     * @generated
     * @ordered
     */
    protected ConnectorDeclaration declaration;

    /**
     * The cached value of the '{@link #getSubDataInstances() <em>Sub Data Instances</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getSubDataInstances()
     * @generated
     * @ordered
     */
    protected EList<DataInstance> subDataInstances;

    /**
     * The cached value of the '{@link #getPortParamInstances() <em>Port Param Instances</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPortParamInstances()
     * @generated
     * @ordered
     */
    protected EList<PortInstance> portParamInstances;

    /**
     * The cached value of the '{@link #getExportedPort() <em>Exported Port</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getExportedPort()
     * @generated
     * @ordered
     */
    protected ConnectorPortInstance exportedPort;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected ConnectorInstanceImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return InstancePackage.Literals.CONNECTOR_INSTANCE;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorDeclaration getDeclaration() {
        if (declaration != null && ((EObject) declaration).eIsProxy()) {
            InternalEObject oldDeclaration = (InternalEObject) declaration;
            declaration = (ConnectorDeclaration) eResolveProxy(oldDeclaration);
            if (declaration != oldDeclaration) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            InstancePackage.CONNECTOR_INSTANCE__DECLARATION,
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
    public ConnectorDeclaration basicGetDeclaration() {
        return declaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setDeclaration(ConnectorDeclaration newDeclaration) {
        ConnectorDeclaration oldDeclaration = declaration;
        declaration = newDeclaration;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    InstancePackage.CONNECTOR_INSTANCE__DECLARATION,
                    oldDeclaration, declaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<DataInstance> getSubDataInstances() {
        if (subDataInstances == null) {
            subDataInstances = new EObjectContainmentEList<DataInstance>(
                    DataInstance.class, this,
                    InstancePackage.CONNECTOR_INSTANCE__SUB_DATA_INSTANCES);
        }
        return subDataInstances;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<PortInstance> getPortParamInstances() {
        if (portParamInstances == null) {
            portParamInstances = new EObjectResolvingEList<PortInstance>(
                    PortInstance.class, this,
                    InstancePackage.CONNECTOR_INSTANCE__PORT_PARAM_INSTANCES);
        }
        return portParamInstances;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorPortInstance getExportedPort() {
        return exportedPort;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetExportedPort(
            ConnectorPortInstance newExportedPort, NotificationChain msgs) {
        ConnectorPortInstance oldExportedPort = exportedPort;
        exportedPort = newExportedPort;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    InstancePackage.CONNECTOR_INSTANCE__EXPORTED_PORT,
                    oldExportedPort, newExportedPort);
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
    public void setExportedPort(ConnectorPortInstance newExportedPort) {
        if (newExportedPort != exportedPort) {
            NotificationChain msgs = null;
            if (exportedPort != null)
                msgs = ((InternalEObject) exportedPort).eInverseRemove(this,
                        EOPPOSITE_FEATURE_BASE
                                - InstancePackage.CONNECTOR_INSTANCE__EXPORTED_PORT,
                        null, msgs);
            if (newExportedPort != null)
                msgs = ((InternalEObject) newExportedPort).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - InstancePackage.CONNECTOR_INSTANCE__EXPORTED_PORT,
                        null, msgs);
            msgs = basicSetExportedPort(newExportedPort, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    InstancePackage.CONNECTOR_INSTANCE__EXPORTED_PORT,
                    newExportedPort, newExportedPort));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public DataInstance getDataInstance(String name) {
        for (DataInstance di : getSubDataInstances()) {
            if (di.getDeclaration().getName().equals(name)) {
                return di;
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
        case InstancePackage.CONNECTOR_INSTANCE__SUB_DATA_INSTANCES:
            return ((InternalEList<?>) getSubDataInstances())
                    .basicRemove(otherEnd, msgs);
        case InstancePackage.CONNECTOR_INSTANCE__EXPORTED_PORT:
            return basicSetExportedPort(null, msgs);
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
        case InstancePackage.CONNECTOR_INSTANCE__DECLARATION:
            if (resolve)
                return getDeclaration();
            return basicGetDeclaration();
        case InstancePackage.CONNECTOR_INSTANCE__SUB_DATA_INSTANCES:
            return getSubDataInstances();
        case InstancePackage.CONNECTOR_INSTANCE__PORT_PARAM_INSTANCES:
            return getPortParamInstances();
        case InstancePackage.CONNECTOR_INSTANCE__EXPORTED_PORT:
            return getExportedPort();
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
        case InstancePackage.CONNECTOR_INSTANCE__DECLARATION:
            setDeclaration((ConnectorDeclaration) newValue);
            return;
        case InstancePackage.CONNECTOR_INSTANCE__SUB_DATA_INSTANCES:
            getSubDataInstances().clear();
            getSubDataInstances()
                    .addAll((Collection<? extends DataInstance>) newValue);
            return;
        case InstancePackage.CONNECTOR_INSTANCE__PORT_PARAM_INSTANCES:
            getPortParamInstances().clear();
            getPortParamInstances()
                    .addAll((Collection<? extends PortInstance>) newValue);
            return;
        case InstancePackage.CONNECTOR_INSTANCE__EXPORTED_PORT:
            setExportedPort((ConnectorPortInstance) newValue);
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
        case InstancePackage.CONNECTOR_INSTANCE__DECLARATION:
            setDeclaration((ConnectorDeclaration) null);
            return;
        case InstancePackage.CONNECTOR_INSTANCE__SUB_DATA_INSTANCES:
            getSubDataInstances().clear();
            return;
        case InstancePackage.CONNECTOR_INSTANCE__PORT_PARAM_INSTANCES:
            getPortParamInstances().clear();
            return;
        case InstancePackage.CONNECTOR_INSTANCE__EXPORTED_PORT:
            setExportedPort((ConnectorPortInstance) null);
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
        case InstancePackage.CONNECTOR_INSTANCE__DECLARATION:
            return declaration != null;
        case InstancePackage.CONNECTOR_INSTANCE__SUB_DATA_INSTANCES:
            return subDataInstances != null && !subDataInstances.isEmpty();
        case InstancePackage.CONNECTOR_INSTANCE__PORT_PARAM_INSTANCES:
            return portParamInstances != null && !portParamInstances.isEmpty();
        case InstancePackage.CONNECTOR_INSTANCE__EXPORTED_PORT:
            return exportedPort != null;
        }
        return super.eIsSet(featureID);
    }

} //ConnectorInstanceImpl
