/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
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

package bip2.ujf.verimag.bip.instance.impl;

import bip2.ujf.verimag.bip.actionlang.ValuedExpression;
import bip2.ujf.verimag.bip.component.ComponentDataParameterDeclaration;
import bip2.ujf.verimag.bip.component.ComponentDeclaration;

import bip2.ujf.verimag.bip.instance.AtomExternalPortInstance;
import bip2.ujf.verimag.bip.instance.AtomInstance;
import bip2.ujf.verimag.bip.instance.AtomInternalPortInstance;
import bip2.ujf.verimag.bip.instance.DataInstance;
import bip2.ujf.verimag.bip.instance.ExportedPortInstance;
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
import org.eclipse.emf.ecore.util.InternalEList;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Atom Instance</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.AtomInstanceImpl#getDeclaration <em>Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.AtomInstanceImpl#getExportedPorts <em>Exported Ports</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.AtomInstanceImpl#getSubDataInstances <em>Sub Data Instances</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.AtomInstanceImpl#getInternalPorts <em>Internal Ports</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.AtomInstanceImpl#getExternalPorts <em>External Ports</em>}</li>
 * </ul>
 *
 * @generated
 */
public class AtomInstanceImpl extends AnnotatedEObjectImpl
        implements AtomInstance {
    /**
     * The cached value of the '{@link #getDeclaration() <em>Declaration</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDeclaration()
     * @generated
     * @ordered
     */
    protected ComponentDeclaration declaration;

    /**
     * The cached value of the '{@link #getExportedPorts() <em>Exported Ports</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getExportedPorts()
     * @generated
     * @ordered
     */
    protected EList<ExportedPortInstance> exportedPorts;

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
     * The cached value of the '{@link #getInternalPorts() <em>Internal Ports</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getInternalPorts()
     * @generated
     * @ordered
     */
    protected EList<AtomInternalPortInstance> internalPorts;

    /**
     * The cached value of the '{@link #getExternalPorts() <em>External Ports</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getExternalPorts()
     * @generated
     * @ordered
     */
    protected EList<AtomExternalPortInstance> externalPorts;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected AtomInstanceImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return InstancePackage.Literals.ATOM_INSTANCE;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ComponentDeclaration getDeclaration() {
        if (declaration != null && ((EObject) declaration).eIsProxy()) {
            InternalEObject oldDeclaration = (InternalEObject) declaration;
            declaration = (ComponentDeclaration) eResolveProxy(oldDeclaration);
            if (declaration != oldDeclaration) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            InstancePackage.ATOM_INSTANCE__DECLARATION,
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
    public ComponentDeclaration basicGetDeclaration() {
        return declaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setDeclaration(ComponentDeclaration newDeclaration) {
        ComponentDeclaration oldDeclaration = declaration;
        declaration = newDeclaration;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    InstancePackage.ATOM_INSTANCE__DECLARATION, oldDeclaration,
                    declaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<ExportedPortInstance> getExportedPorts() {
        if (exportedPorts == null) {
            exportedPorts = new EObjectContainmentEList<ExportedPortInstance>(
                    ExportedPortInstance.class, this,
                    InstancePackage.ATOM_INSTANCE__EXPORTED_PORTS);
        }
        return exportedPorts;
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
                    InstancePackage.ATOM_INSTANCE__SUB_DATA_INSTANCES);
        }
        return subDataInstances;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<AtomInternalPortInstance> getInternalPorts() {
        if (internalPorts == null) {
            internalPorts = new EObjectContainmentEList<AtomInternalPortInstance>(
                    AtomInternalPortInstance.class, this,
                    InstancePackage.ATOM_INSTANCE__INTERNAL_PORTS);
        }
        return internalPorts;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<AtomExternalPortInstance> getExternalPorts() {
        if (externalPorts == null) {
            externalPorts = new EObjectContainmentEList<AtomExternalPortInstance>(
                    AtomExternalPortInstance.class, this,
                    InstancePackage.ATOM_INSTANCE__EXTERNAL_PORTS);
        }
        return externalPorts;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public DataInstance getInternalDataInstance(String name) {
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
     * @generated NOT
     */
    public AtomInternalPortInstance getInternalPortInstance(String name) {
        for (AtomInternalPortInstance pi : getInternalPorts()) {
            if (pi.getDeclaration().getName().equals(name)) {
                return pi;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public ExportedPortInstance getPortInstance(String name) {
        for (ExportedPortInstance epi : getExportedPorts()) {
            if (epi.getDeclaration().getName().equals(name)) {
                return epi;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public DataInstance getDataInstance(String name) {
        return getInternalDataInstance(name);
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
        case InstancePackage.ATOM_INSTANCE__EXPORTED_PORTS:
            return ((InternalEList<?>) getExportedPorts()).basicRemove(otherEnd,
                    msgs);
        case InstancePackage.ATOM_INSTANCE__SUB_DATA_INSTANCES:
            return ((InternalEList<?>) getSubDataInstances())
                    .basicRemove(otherEnd, msgs);
        case InstancePackage.ATOM_INSTANCE__INTERNAL_PORTS:
            return ((InternalEList<?>) getInternalPorts()).basicRemove(otherEnd,
                    msgs);
        case InstancePackage.ATOM_INSTANCE__EXTERNAL_PORTS:
            return ((InternalEList<?>) getExternalPorts()).basicRemove(otherEnd,
                    msgs);
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
        case InstancePackage.ATOM_INSTANCE__DECLARATION:
            if (resolve)
                return getDeclaration();
            return basicGetDeclaration();
        case InstancePackage.ATOM_INSTANCE__EXPORTED_PORTS:
            return getExportedPorts();
        case InstancePackage.ATOM_INSTANCE__SUB_DATA_INSTANCES:
            return getSubDataInstances();
        case InstancePackage.ATOM_INSTANCE__INTERNAL_PORTS:
            return getInternalPorts();
        case InstancePackage.ATOM_INSTANCE__EXTERNAL_PORTS:
            return getExternalPorts();
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
        case InstancePackage.ATOM_INSTANCE__DECLARATION:
            setDeclaration((ComponentDeclaration) newValue);
            return;
        case InstancePackage.ATOM_INSTANCE__EXPORTED_PORTS:
            getExportedPorts().clear();
            getExportedPorts().addAll(
                    (Collection<? extends ExportedPortInstance>) newValue);
            return;
        case InstancePackage.ATOM_INSTANCE__SUB_DATA_INSTANCES:
            getSubDataInstances().clear();
            getSubDataInstances()
                    .addAll((Collection<? extends DataInstance>) newValue);
            return;
        case InstancePackage.ATOM_INSTANCE__INTERNAL_PORTS:
            getInternalPorts().clear();
            getInternalPorts().addAll(
                    (Collection<? extends AtomInternalPortInstance>) newValue);
            return;
        case InstancePackage.ATOM_INSTANCE__EXTERNAL_PORTS:
            getExternalPorts().clear();
            getExternalPorts().addAll(
                    (Collection<? extends AtomExternalPortInstance>) newValue);
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
        case InstancePackage.ATOM_INSTANCE__DECLARATION:
            setDeclaration((ComponentDeclaration) null);
            return;
        case InstancePackage.ATOM_INSTANCE__EXPORTED_PORTS:
            getExportedPorts().clear();
            return;
        case InstancePackage.ATOM_INSTANCE__SUB_DATA_INSTANCES:
            getSubDataInstances().clear();
            return;
        case InstancePackage.ATOM_INSTANCE__INTERNAL_PORTS:
            getInternalPorts().clear();
            return;
        case InstancePackage.ATOM_INSTANCE__EXTERNAL_PORTS:
            getExternalPorts().clear();
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
        case InstancePackage.ATOM_INSTANCE__DECLARATION:
            return declaration != null;
        case InstancePackage.ATOM_INSTANCE__EXPORTED_PORTS:
            return exportedPorts != null && !exportedPorts.isEmpty();
        case InstancePackage.ATOM_INSTANCE__SUB_DATA_INSTANCES:
            return subDataInstances != null && !subDataInstances.isEmpty();
        case InstancePackage.ATOM_INSTANCE__INTERNAL_PORTS:
            return internalPorts != null && !internalPorts.isEmpty();
        case InstancePackage.ATOM_INSTANCE__EXTERNAL_PORTS:
            return externalPorts != null && !externalPorts.isEmpty();
        }
        return super.eIsSet(featureID);
    }

} //AtomInstanceImpl
