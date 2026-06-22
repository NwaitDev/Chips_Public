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
import bip2.ujf.verimag.bip.component.compound.CompoundExportDataDeclaration;
import bip2.ujf.verimag.bip.component.compound.CompoundExportPortDeclaration;
import bip2.ujf.verimag.bip.data.SubDataDeclarationReference;

import bip2.ujf.verimag.bip.instance.AtomInstance;
import bip2.ujf.verimag.bip.instance.ComponentInstance;
import bip2.ujf.verimag.bip.instance.CompoundInstance;
import bip2.ujf.verimag.bip.instance.CompoundPriorityInstance;
import bip2.ujf.verimag.bip.instance.ConnectorInstance;
import bip2.ujf.verimag.bip.instance.DataInstance;
import bip2.ujf.verimag.bip.instance.ExportedPortInstance;
import bip2.ujf.verimag.bip.instance.InstancePackage;
import bip2.ujf.verimag.bip.instance.PortInstance;
import bip2.ujf.verimag.bip.port.SubPortDeclarationReference;
import bip2.ujf.verimag.bip.types.CompoundType;

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
 * An implementation of the model object '<em><b>Compound Instance</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.CompoundInstanceImpl#getDeclaration <em>Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.CompoundInstanceImpl#getExportedPorts <em>Exported Ports</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.CompoundInstanceImpl#getSubPriorities <em>Sub Priorities</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.CompoundInstanceImpl#getSubConnectorInstances <em>Sub Connector Instances</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.CompoundInstanceImpl#getSubAtomInstances <em>Sub Atom Instances</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.CompoundInstanceImpl#getSubCompoundInstances <em>Sub Compound Instances</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.impl.CompoundInstanceImpl#getSubDataInstances <em>Sub Data Instances</em>}</li>
 * </ul>
 *
 * @generated
 */
public class CompoundInstanceImpl extends AnnotatedEObjectImpl
        implements CompoundInstance {
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
     * The cached value of the '{@link #getSubPriorities() <em>Sub Priorities</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getSubPriorities()
     * @generated
     * @ordered
     */
    protected EList<CompoundPriorityInstance> subPriorities;

    /**
     * The cached value of the '{@link #getSubConnectorInstances() <em>Sub Connector Instances</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getSubConnectorInstances()
     * @generated
     * @ordered
     */
    protected EList<ConnectorInstance> subConnectorInstances;

    /**
     * The cached value of the '{@link #getSubAtomInstances() <em>Sub Atom Instances</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getSubAtomInstances()
     * @generated
     * @ordered
     */
    protected EList<AtomInstance> subAtomInstances;

    /**
     * The cached value of the '{@link #getSubCompoundInstances() <em>Sub Compound Instances</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getSubCompoundInstances()
     * @generated
     * @ordered
     */
    protected EList<CompoundInstance> subCompoundInstances;

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
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected CompoundInstanceImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return InstancePackage.Literals.COMPOUND_INSTANCE;
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
                            InstancePackage.COMPOUND_INSTANCE__DECLARATION,
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
                    InstancePackage.COMPOUND_INSTANCE__DECLARATION,
                    oldDeclaration, declaration));
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
                    InstancePackage.COMPOUND_INSTANCE__EXPORTED_PORTS);
        }
        return exportedPorts;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<CompoundPriorityInstance> getSubPriorities() {
        if (subPriorities == null) {
            subPriorities = new EObjectContainmentEList<CompoundPriorityInstance>(
                    CompoundPriorityInstance.class, this,
                    InstancePackage.COMPOUND_INSTANCE__SUB_PRIORITIES);
        }
        return subPriorities;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<ConnectorInstance> getSubConnectorInstances() {
        if (subConnectorInstances == null) {
            subConnectorInstances = new EObjectContainmentEList<ConnectorInstance>(
                    ConnectorInstance.class, this,
                    InstancePackage.COMPOUND_INSTANCE__SUB_CONNECTOR_INSTANCES);
        }
        return subConnectorInstances;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<AtomInstance> getSubAtomInstances() {
        if (subAtomInstances == null) {
            subAtomInstances = new EObjectContainmentEList<AtomInstance>(
                    AtomInstance.class, this,
                    InstancePackage.COMPOUND_INSTANCE__SUB_ATOM_INSTANCES);
        }
        return subAtomInstances;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<CompoundInstance> getSubCompoundInstances() {
        if (subCompoundInstances == null) {
            subCompoundInstances = new EObjectContainmentEList<CompoundInstance>(
                    CompoundInstance.class, this,
                    InstancePackage.COMPOUND_INSTANCE__SUB_COMPOUND_INSTANCES);
        }
        return subCompoundInstances;
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
                    InstancePackage.COMPOUND_INSTANCE__SUB_DATA_INSTANCES);
        }
        return subDataInstances;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public ComponentInstance getComponentInstance(String name) {
        for (ComponentInstance ci : getSubAtomInstances()) {
            if (ci.getDeclaration().getName().equals(name)) {
                return ci;
            }
        }
        for (ComponentInstance ci : getSubCompoundInstances()) {
            if (ci.getDeclaration().getName().equals(name)) {
                return ci;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public AtomInstance getAtomInstance(String name) {
        for (AtomInstance ci : getSubAtomInstances()) {
            if (ci.getDeclaration().getName().equals(name)) {
                return ci;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public CompoundInstance getCompoundInstance(String name) {
        for (CompoundInstance ci : getSubCompoundInstances()) {
            if (ci.getDeclaration().getName().equals(name)) {
                return ci;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public ConnectorInstance getConnectorInstance(String name) {
        for (ConnectorInstance ci : getSubConnectorInstances()) {
            if (ci.getDeclaration().getName().equals(name)) {
                return ci;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public CompoundPriorityInstance getCompoundPriorityInstance(String name) {
        for (CompoundPriorityInstance cpi : getSubPriorities()) {
            if (cpi.getDeclaration().getName().equals(name)) {
                return cpi;
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
        // do not resolve proxy link, let the caller handle that.
        for (DataInstance di : this.getSubDataInstances()) {
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
        case InstancePackage.COMPOUND_INSTANCE__EXPORTED_PORTS:
            return ((InternalEList<?>) getExportedPorts()).basicRemove(otherEnd,
                    msgs);
        case InstancePackage.COMPOUND_INSTANCE__SUB_PRIORITIES:
            return ((InternalEList<?>) getSubPriorities()).basicRemove(otherEnd,
                    msgs);
        case InstancePackage.COMPOUND_INSTANCE__SUB_CONNECTOR_INSTANCES:
            return ((InternalEList<?>) getSubConnectorInstances())
                    .basicRemove(otherEnd, msgs);
        case InstancePackage.COMPOUND_INSTANCE__SUB_ATOM_INSTANCES:
            return ((InternalEList<?>) getSubAtomInstances())
                    .basicRemove(otherEnd, msgs);
        case InstancePackage.COMPOUND_INSTANCE__SUB_COMPOUND_INSTANCES:
            return ((InternalEList<?>) getSubCompoundInstances())
                    .basicRemove(otherEnd, msgs);
        case InstancePackage.COMPOUND_INSTANCE__SUB_DATA_INSTANCES:
            return ((InternalEList<?>) getSubDataInstances())
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
        case InstancePackage.COMPOUND_INSTANCE__DECLARATION:
            if (resolve)
                return getDeclaration();
            return basicGetDeclaration();
        case InstancePackage.COMPOUND_INSTANCE__EXPORTED_PORTS:
            return getExportedPorts();
        case InstancePackage.COMPOUND_INSTANCE__SUB_PRIORITIES:
            return getSubPriorities();
        case InstancePackage.COMPOUND_INSTANCE__SUB_CONNECTOR_INSTANCES:
            return getSubConnectorInstances();
        case InstancePackage.COMPOUND_INSTANCE__SUB_ATOM_INSTANCES:
            return getSubAtomInstances();
        case InstancePackage.COMPOUND_INSTANCE__SUB_COMPOUND_INSTANCES:
            return getSubCompoundInstances();
        case InstancePackage.COMPOUND_INSTANCE__SUB_DATA_INSTANCES:
            return getSubDataInstances();
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
        case InstancePackage.COMPOUND_INSTANCE__DECLARATION:
            setDeclaration((ComponentDeclaration) newValue);
            return;
        case InstancePackage.COMPOUND_INSTANCE__EXPORTED_PORTS:
            getExportedPorts().clear();
            getExportedPorts().addAll(
                    (Collection<? extends ExportedPortInstance>) newValue);
            return;
        case InstancePackage.COMPOUND_INSTANCE__SUB_PRIORITIES:
            getSubPriorities().clear();
            getSubPriorities().addAll(
                    (Collection<? extends CompoundPriorityInstance>) newValue);
            return;
        case InstancePackage.COMPOUND_INSTANCE__SUB_CONNECTOR_INSTANCES:
            getSubConnectorInstances().clear();
            getSubConnectorInstances()
                    .addAll((Collection<? extends ConnectorInstance>) newValue);
            return;
        case InstancePackage.COMPOUND_INSTANCE__SUB_ATOM_INSTANCES:
            getSubAtomInstances().clear();
            getSubAtomInstances()
                    .addAll((Collection<? extends AtomInstance>) newValue);
            return;
        case InstancePackage.COMPOUND_INSTANCE__SUB_COMPOUND_INSTANCES:
            getSubCompoundInstances().clear();
            getSubCompoundInstances()
                    .addAll((Collection<? extends CompoundInstance>) newValue);
            return;
        case InstancePackage.COMPOUND_INSTANCE__SUB_DATA_INSTANCES:
            getSubDataInstances().clear();
            getSubDataInstances()
                    .addAll((Collection<? extends DataInstance>) newValue);
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
        case InstancePackage.COMPOUND_INSTANCE__DECLARATION:
            setDeclaration((ComponentDeclaration) null);
            return;
        case InstancePackage.COMPOUND_INSTANCE__EXPORTED_PORTS:
            getExportedPorts().clear();
            return;
        case InstancePackage.COMPOUND_INSTANCE__SUB_PRIORITIES:
            getSubPriorities().clear();
            return;
        case InstancePackage.COMPOUND_INSTANCE__SUB_CONNECTOR_INSTANCES:
            getSubConnectorInstances().clear();
            return;
        case InstancePackage.COMPOUND_INSTANCE__SUB_ATOM_INSTANCES:
            getSubAtomInstances().clear();
            return;
        case InstancePackage.COMPOUND_INSTANCE__SUB_COMPOUND_INSTANCES:
            getSubCompoundInstances().clear();
            return;
        case InstancePackage.COMPOUND_INSTANCE__SUB_DATA_INSTANCES:
            getSubDataInstances().clear();
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
        case InstancePackage.COMPOUND_INSTANCE__DECLARATION:
            return declaration != null;
        case InstancePackage.COMPOUND_INSTANCE__EXPORTED_PORTS:
            return exportedPorts != null && !exportedPorts.isEmpty();
        case InstancePackage.COMPOUND_INSTANCE__SUB_PRIORITIES:
            return subPriorities != null && !subPriorities.isEmpty();
        case InstancePackage.COMPOUND_INSTANCE__SUB_CONNECTOR_INSTANCES:
            return subConnectorInstances != null
                    && !subConnectorInstances.isEmpty();
        case InstancePackage.COMPOUND_INSTANCE__SUB_ATOM_INSTANCES:
            return subAtomInstances != null && !subAtomInstances.isEmpty();
        case InstancePackage.COMPOUND_INSTANCE__SUB_COMPOUND_INSTANCES:
            return subCompoundInstances != null
                    && !subCompoundInstances.isEmpty();
        case InstancePackage.COMPOUND_INSTANCE__SUB_DATA_INSTANCES:
            return subDataInstances != null && !subDataInstances.isEmpty();
        }
        return super.eIsSet(featureID);
    }

} //CompoundInstanceImpl
