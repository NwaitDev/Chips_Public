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

package bip2.ujf.verimag.bip.types.impl;

import bip2.ujf.verimag.bip.annotation.AnnotatedElement;
import bip2.ujf.verimag.bip.annotation.AnnotationPackage;
import bip2.ujf.verimag.bip.annotation.BipAnnotation;
import bip2.ujf.verimag.bip.annotation.impl.StringToAnnotationMapEntryImpl;
import bip2.ujf.verimag.bip.annotation.impl.AnnotatedElementImpl;
import bip2.ujf.verimag.bip.component.ComponentDataParameterDeclaration;
import bip2.ujf.verimag.bip.component.ComponentDeclaration;
import bip2.ujf.verimag.bip.component.compound.CompoundExportDataDeclaration;
import bip2.ujf.verimag.bip.component.compound.CompoundExportPortDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.port.PortDeclaration;
import bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration;
import bip2.ujf.verimag.bip.types.AtomType;
import bip2.ujf.verimag.bip.types.CompoundType;
import bip2.ujf.verimag.bip.types.Type;
import bip2.ujf.verimag.bip.types.TypesPackage;
import java.util.Collection;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;
import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.common.util.EMap;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EStructuralFeature;
import org.eclipse.emf.ecore.InternalEObject;
import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.EObjectResolvingEList;
import org.eclipse.emf.ecore.util.EcoreEMap;
import org.eclipse.emf.ecore.util.InternalEList;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

public class CompoundTypeImpl extends TypeImpl implements CompoundType {

    /**
     * The cached value of the '{@link #getExportedPortDeclarations() <em>Exported Port Declarations</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getExportedPortDeclarations()
     * @generated
     * @ordered
     */
    protected EList<PortDeclaration> exportedPortDeclarations;
    /**
     * The cached value of the '{@link #getExportedDataDeclarations() <em>Exported Data Declarations</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getExportedDataDeclarations()
     * @generated
     * @ordered
     */
    protected EList<DataDeclaration> exportedDataDeclarations;
    /**
     * The cached value of the '{@link #getDataParameterDeclarations() <em>Data Parameter Declarations</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDataParameterDeclarations()
     * @generated
     * @ordered
     */
    protected EList<ComponentDataParameterDeclaration> dataParameterDeclarations;
    /**
     * The cached value of the '{@link #getComponentDeclarations() <em>Component Declarations</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getComponentDeclarations()
     * @generated
     * @ordered
     */
    protected EList<ComponentDeclaration> componentDeclarations;
    /**
     * The cached value of the '{@link #getConnectorDeclarations() <em>Connector Declarations</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getConnectorDeclarations()
     * @generated
     * @ordered
     */
    protected EList<ConnectorDeclaration> connectorDeclarations;
    /**
     * The cached value of the '{@link #getExportPortDeclarations() <em>Export Port Declarations</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getExportPortDeclarations()
     * @generated
     * @ordered
     */
    protected EList<CompoundExportPortDeclaration> exportPortDeclarations;

    /**
     * The cached value of the '{@link #getExportDataDeclarations() <em>Export Data Declarations</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getExportDataDeclarations()
     * @generated
     * @ordered
     */
    protected EList<CompoundExportDataDeclaration> exportDataDeclarations;

    /**
     * The cached value of the '{@link #getPriorities() <em>Priorities</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPriorities()
     * @generated
     * @ordered
     */
    protected EList<CompoundPriorityDeclaration> priorities;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected CompoundTypeImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return TypesPackage.Literals.COMPOUND_TYPE;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<PortDeclaration> getExportedPortDeclarations() {
        if (exportedPortDeclarations == null) {
            exportedPortDeclarations = new EObjectResolvingEList<PortDeclaration>(
                    PortDeclaration.class, this,
                    TypesPackage.COMPOUND_TYPE__EXPORTED_PORT_DECLARATIONS);
        }
        return exportedPortDeclarations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<DataDeclaration> getExportedDataDeclarations() {
        if (exportedDataDeclarations == null) {
            exportedDataDeclarations = new EObjectResolvingEList<DataDeclaration>(
                    DataDeclaration.class, this,
                    TypesPackage.COMPOUND_TYPE__EXPORTED_DATA_DECLARATIONS);
        }
        return exportedDataDeclarations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<ComponentDataParameterDeclaration> getDataParameterDeclarations() {
        if (dataParameterDeclarations == null) {
            dataParameterDeclarations = new EObjectContainmentEList<ComponentDataParameterDeclaration>(
                    ComponentDataParameterDeclaration.class, this,
                    TypesPackage.COMPOUND_TYPE__DATA_PARAMETER_DECLARATIONS);
        }
        return dataParameterDeclarations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<ComponentDeclaration> getComponentDeclarations() {
        if (componentDeclarations == null) {
            componentDeclarations = new EObjectContainmentEList<ComponentDeclaration>(
                    ComponentDeclaration.class, this,
                    TypesPackage.COMPOUND_TYPE__COMPONENT_DECLARATIONS);
        }
        return componentDeclarations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<ConnectorDeclaration> getConnectorDeclarations() {
        if (connectorDeclarations == null) {
            connectorDeclarations = new EObjectContainmentEList<ConnectorDeclaration>(
                    ConnectorDeclaration.class, this,
                    TypesPackage.COMPOUND_TYPE__CONNECTOR_DECLARATIONS);
        }
        return connectorDeclarations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<CompoundExportPortDeclaration> getExportPortDeclarations() {
        if (exportPortDeclarations == null) {
            exportPortDeclarations = new EObjectContainmentEList<CompoundExportPortDeclaration>(
                    CompoundExportPortDeclaration.class, this,
                    TypesPackage.COMPOUND_TYPE__EXPORT_PORT_DECLARATIONS);
        }
        return exportPortDeclarations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<CompoundExportDataDeclaration> getExportDataDeclarations() {
        if (exportDataDeclarations == null) {
            exportDataDeclarations = new EObjectContainmentEList<CompoundExportDataDeclaration>(
                    CompoundExportDataDeclaration.class, this,
                    TypesPackage.COMPOUND_TYPE__EXPORT_DATA_DECLARATIONS);
        }
        return exportDataDeclarations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<CompoundPriorityDeclaration> getPriorities() {
        if (priorities == null) {
            priorities = new EObjectContainmentEList<CompoundPriorityDeclaration>(
                    CompoundPriorityDeclaration.class, this,
                    TypesPackage.COMPOUND_TYPE__PRIORITIES);
        }
        return priorities;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public ComponentDeclaration getComponentDeclaration(String name) {
        for (ComponentDeclaration cd : getComponentDeclarations()) {
            if (cd.getName().equals(name)) {
                return cd;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public ConnectorDeclaration getConnectorDeclaration(String name) {
        for (ConnectorDeclaration cd : getConnectorDeclarations()) {
            if (cd.getName().equals(name)) {
                return cd;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public CompoundExportPortDeclaration getExportPortDeclaration(String name) {
        for (CompoundExportPortDeclaration cepd : getExportPortDeclarations()) {
            if (cepd.getName().equals(name)) {
                return cepd;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public CompoundExportDataDeclaration getExportDataDeclaration(String name) {
        for (CompoundExportDataDeclaration cedd : getExportDataDeclarations()) {
            if (cedd.getName().equals(name)) {
                return cedd;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public CompoundPriorityDeclaration getPriorityDeclaration(String name) {
        for (CompoundPriorityDeclaration pd : getPriorities()) {
            if (pd.getName().equals(name)) {
                return pd;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public PortDeclaration getExportedPortDeclaration(String name) {
        return getExportPortDeclaration(name);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public DataDeclaration getExportedDataDeclaration(String name) {
        return getExportDataDeclaration(name);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public ComponentDataParameterDeclaration getDataParameterDeclaration(
            String name) {
        for (ComponentDataParameterDeclaration cdpd : getDataParameterDeclarations()) {
            if (cdpd.getName().equals(name)) {
                return cdpd;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean isKindOf(Type type) {
        return this == type;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean isSubTypeOf(Type type) {
        return false; // subtyping of bip types not supported yet!
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
        case TypesPackage.COMPOUND_TYPE__DATA_PARAMETER_DECLARATIONS:
            return ((InternalEList<?>) getDataParameterDeclarations())
                    .basicRemove(otherEnd, msgs);
        case TypesPackage.COMPOUND_TYPE__COMPONENT_DECLARATIONS:
            return ((InternalEList<?>) getComponentDeclarations())
                    .basicRemove(otherEnd, msgs);
        case TypesPackage.COMPOUND_TYPE__CONNECTOR_DECLARATIONS:
            return ((InternalEList<?>) getConnectorDeclarations())
                    .basicRemove(otherEnd, msgs);
        case TypesPackage.COMPOUND_TYPE__EXPORT_PORT_DECLARATIONS:
            return ((InternalEList<?>) getExportPortDeclarations())
                    .basicRemove(otherEnd, msgs);
        case TypesPackage.COMPOUND_TYPE__EXPORT_DATA_DECLARATIONS:
            return ((InternalEList<?>) getExportDataDeclarations())
                    .basicRemove(otherEnd, msgs);
        case TypesPackage.COMPOUND_TYPE__PRIORITIES:
            return ((InternalEList<?>) getPriorities()).basicRemove(otherEnd,
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
        case TypesPackage.COMPOUND_TYPE__EXPORTED_PORT_DECLARATIONS:
            return getExportedPortDeclarations();
        case TypesPackage.COMPOUND_TYPE__EXPORTED_DATA_DECLARATIONS:
            return getExportedDataDeclarations();
        case TypesPackage.COMPOUND_TYPE__DATA_PARAMETER_DECLARATIONS:
            return getDataParameterDeclarations();
        case TypesPackage.COMPOUND_TYPE__COMPONENT_DECLARATIONS:
            return getComponentDeclarations();
        case TypesPackage.COMPOUND_TYPE__CONNECTOR_DECLARATIONS:
            return getConnectorDeclarations();
        case TypesPackage.COMPOUND_TYPE__EXPORT_PORT_DECLARATIONS:
            return getExportPortDeclarations();
        case TypesPackage.COMPOUND_TYPE__EXPORT_DATA_DECLARATIONS:
            return getExportDataDeclarations();
        case TypesPackage.COMPOUND_TYPE__PRIORITIES:
            return getPriorities();
        }
        return super.eGet(featureID, resolve, coreType);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    @SuppressWarnings("unchecked")
    public void eSet(int featureID, Object newValue) {
        switch (featureID) {
        case TypesPackage.COMPOUND_TYPE__EXPORTED_PORT_DECLARATIONS:
            getExportedPortDeclarations().clear();
            getExportedPortDeclarations()
                    .addAll((Collection<? extends PortDeclaration>) newValue);
            return;
        case TypesPackage.COMPOUND_TYPE__EXPORTED_DATA_DECLARATIONS:
            getExportedDataDeclarations().clear();
            getExportedDataDeclarations()
                    .addAll((Collection<? extends DataDeclaration>) newValue);
            return;
        case TypesPackage.COMPOUND_TYPE__DATA_PARAMETER_DECLARATIONS:
            getDataParameterDeclarations().clear();
            getDataParameterDeclarations().addAll(
                    (Collection<? extends ComponentDataParameterDeclaration>) newValue);
            return;
        case TypesPackage.COMPOUND_TYPE__COMPONENT_DECLARATIONS:
            getComponentDeclarations().clear();
            getComponentDeclarations().addAll(
                    (Collection<? extends ComponentDeclaration>) newValue);
            return;
        case TypesPackage.COMPOUND_TYPE__CONNECTOR_DECLARATIONS:
            getConnectorDeclarations().clear();
            getConnectorDeclarations().addAll(
                    (Collection<? extends ConnectorDeclaration>) newValue);
            return;
        case TypesPackage.COMPOUND_TYPE__EXPORT_PORT_DECLARATIONS:
            getExportPortDeclarations().clear();
            getExportPortDeclarations().addAll(
                    (Collection<? extends CompoundExportPortDeclaration>) newValue);
            return;
        case TypesPackage.COMPOUND_TYPE__EXPORT_DATA_DECLARATIONS:
            getExportDataDeclarations().clear();
            getExportDataDeclarations().addAll(
                    (Collection<? extends CompoundExportDataDeclaration>) newValue);
            return;
        case TypesPackage.COMPOUND_TYPE__PRIORITIES:
            getPriorities().clear();
            getPriorities().addAll(
                    (Collection<? extends CompoundPriorityDeclaration>) newValue);
            return;
        }
        super.eSet(featureID, newValue);
    }

    //    /**
    //     * <!-- begin-user-doc -->
    //     * <!-- end-user-doc -->
    //     * @generated NOT
    //     */
    //    @SuppressWarnings("unchecked")
    //    @Override
    //    public void eSet(int featureID, Object newValue) {
    //        switch (featureID) {
    //        case TypesPackage.COMPOUND_TYPE__EXPORT_PORT_DECLARATIONS:
    //            getExportedPortDeclarations().clear();
    //            getExportedPortDeclarations()
    //                    .addAll((Collection<? extends CompoundExportPortDeclaration>) newValue);
    //            return;
    //        case TypesPackage.COMPOUND_TYPE__EXPORT_DATA_DECLARATIONS:
    //            getExportedDataDeclarations().clear();
    //            getExportedDataDeclarations()
    //                    .addAll((Collection<? extends CompoundExportDataDeclaration>) newValue);
    //            return;
    //        }
    //        eSetGen(featureID, newValue);
    //    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void eUnset(int featureID) {
        switch (featureID) {
        case TypesPackage.COMPOUND_TYPE__EXPORTED_PORT_DECLARATIONS:
            getExportedPortDeclarations().clear();
            return;
        case TypesPackage.COMPOUND_TYPE__EXPORTED_DATA_DECLARATIONS:
            getExportedDataDeclarations().clear();
            return;
        case TypesPackage.COMPOUND_TYPE__DATA_PARAMETER_DECLARATIONS:
            getDataParameterDeclarations().clear();
            return;
        case TypesPackage.COMPOUND_TYPE__COMPONENT_DECLARATIONS:
            getComponentDeclarations().clear();
            return;
        case TypesPackage.COMPOUND_TYPE__CONNECTOR_DECLARATIONS:
            getConnectorDeclarations().clear();
            return;
        case TypesPackage.COMPOUND_TYPE__EXPORT_PORT_DECLARATIONS:
            getExportPortDeclarations().clear();
            return;
        case TypesPackage.COMPOUND_TYPE__EXPORT_DATA_DECLARATIONS:
            getExportDataDeclarations().clear();
            return;
        case TypesPackage.COMPOUND_TYPE__PRIORITIES:
            getPriorities().clear();
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
        case TypesPackage.COMPOUND_TYPE__EXPORTED_PORT_DECLARATIONS:
            return exportedPortDeclarations != null
                    && !exportedPortDeclarations.isEmpty();
        case TypesPackage.COMPOUND_TYPE__EXPORTED_DATA_DECLARATIONS:
            return exportedDataDeclarations != null
                    && !exportedDataDeclarations.isEmpty();
        case TypesPackage.COMPOUND_TYPE__DATA_PARAMETER_DECLARATIONS:
            return dataParameterDeclarations != null
                    && !dataParameterDeclarations.isEmpty();
        case TypesPackage.COMPOUND_TYPE__COMPONENT_DECLARATIONS:
            return componentDeclarations != null
                    && !componentDeclarations.isEmpty();
        case TypesPackage.COMPOUND_TYPE__CONNECTOR_DECLARATIONS:
            return connectorDeclarations != null
                    && !connectorDeclarations.isEmpty();
        case TypesPackage.COMPOUND_TYPE__EXPORT_PORT_DECLARATIONS:
            return exportPortDeclarations != null
                    && !exportPortDeclarations.isEmpty();
        case TypesPackage.COMPOUND_TYPE__EXPORT_DATA_DECLARATIONS:
            return exportDataDeclarations != null
                    && !exportDataDeclarations.isEmpty();
        case TypesPackage.COMPOUND_TYPE__PRIORITIES:
            return priorities != null && !priorities.isEmpty();
        }
        return super.eIsSet(featureID);
    }

} //CompoundTypeImpl
