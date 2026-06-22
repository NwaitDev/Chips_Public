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
import bip2.ujf.verimag.bip.behavior.PetriNet;
import bip2.ujf.verimag.bip.component.ComponentDataParameterDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomExportPortDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomExternalPortDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomInternalDataDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomInternalPortDeclaration;

import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.invariant.AtomInvariant;
import bip2.ujf.verimag.bip.port.PortDeclaration;

import bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration;
import bip2.ujf.verimag.bip.types.AtomType;
import bip2.ujf.verimag.bip.types.Type;
import bip2.ujf.verimag.bip.types.TypesPackage;

import java.util.Collection;
import java.util.HashSet;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.common.util.EMap;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EStructuralFeature;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.emf.ecore.impl.EObjectImpl;

import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.EObjectResolvingEList;
import org.eclipse.emf.ecore.util.EcoreEMap;
import org.eclipse.emf.ecore.util.InternalEList;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Atom Type</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.AtomTypeImpl#getExportedPortDeclarations <em>Exported Port Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.AtomTypeImpl#getExportedDataDeclarations <em>Exported Data Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.AtomTypeImpl#getDataParameterDeclarations <em>Data Parameter Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.AtomTypeImpl#getInternalPortDeclarations <em>Internal Port Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.AtomTypeImpl#getExternalPortDeclarations <em>External Port Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.AtomTypeImpl#getBehavior <em>Behavior</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.AtomTypeImpl#getInternalDataDeclarations <em>Internal Data Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.AtomTypeImpl#getExportPortDeclarations <em>Export Port Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.AtomTypeImpl#getPriorities <em>Priorities</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.impl.AtomTypeImpl#getInvariants <em>Invariants</em>}</li>
 * </ul>
 *
 * @generated
 */
public class AtomTypeImpl extends TypeImpl implements AtomType {

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
     * The cached value of the '{@link #getInternalPortDeclarations() <em>Internal Port Declarations</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getInternalPortDeclarations()
     * @generated
     * @ordered
     */
    protected EList<AtomInternalPortDeclaration> internalPortDeclarations;
    /**
     * The cached value of the '{@link #getExternalPortDeclarations() <em>External Port Declarations</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getExternalPortDeclarations()
     * @generated
     * @ordered
     */
    protected EList<AtomExternalPortDeclaration> externalPortDeclarations;
    /**
     * The cached value of the '{@link #getBehavior() <em>Behavior</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getBehavior()
     * @generated
     * @ordered
     */
    protected PetriNet behavior;
    /**
     * The cached value of the '{@link #getInternalDataDeclarations() <em>Internal Data Declarations</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getInternalDataDeclarations()
     * @generated
     * @ordered
     */
    protected EList<AtomInternalDataDeclaration> internalDataDeclarations;

    /**
     * The cached value of the '{@link #getExportPortDeclarations() <em>Export Port Declarations</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getExportPortDeclarations()
     * @generated
     * @ordered
     */
    protected EList<AtomExportPortDeclaration> exportPortDeclarations;

    /**
     * The cached value of the '{@link #getPriorities() <em>Priorities</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPriorities()
     * @generated
     * @ordered
     */
    protected EList<AtomPriorityDeclaration> priorities;

    /**
     * The cached value of the '{@link #getInvariants() <em>Invariants</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getInvariants()
     * @generated
     * @ordered
     */
    protected EList<AtomInvariant> invariants;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected AtomTypeImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return TypesPackage.Literals.ATOM_TYPE;
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
                    TypesPackage.ATOM_TYPE__EXPORTED_PORT_DECLARATIONS);
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
                    TypesPackage.ATOM_TYPE__EXPORTED_DATA_DECLARATIONS);
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
                    TypesPackage.ATOM_TYPE__DATA_PARAMETER_DECLARATIONS);
        }
        return dataParameterDeclarations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<AtomInternalPortDeclaration> getInternalPortDeclarations() {
        if (internalPortDeclarations == null) {
            internalPortDeclarations = new EObjectContainmentEList<AtomInternalPortDeclaration>(
                    AtomInternalPortDeclaration.class, this,
                    TypesPackage.ATOM_TYPE__INTERNAL_PORT_DECLARATIONS);
        }
        return internalPortDeclarations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<AtomExternalPortDeclaration> getExternalPortDeclarations() {
        if (externalPortDeclarations == null) {
            externalPortDeclarations = new EObjectContainmentEList<AtomExternalPortDeclaration>(
                    AtomExternalPortDeclaration.class, this,
                    TypesPackage.ATOM_TYPE__EXTERNAL_PORT_DECLARATIONS);
        }
        return externalPortDeclarations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PetriNet getBehavior() {
        return behavior;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetBehavior(PetriNet newBehavior,
            NotificationChain msgs) {
        PetriNet oldBehavior = behavior;
        behavior = newBehavior;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET, TypesPackage.ATOM_TYPE__BEHAVIOR,
                    oldBehavior, newBehavior);
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
    public void setBehavior(PetriNet newBehavior) {
        if (newBehavior != behavior) {
            NotificationChain msgs = null;
            if (behavior != null)
                msgs = ((InternalEObject) behavior)
                        .eInverseRemove(this,
                                EOPPOSITE_FEATURE_BASE
                                        - TypesPackage.ATOM_TYPE__BEHAVIOR,
                                null, msgs);
            if (newBehavior != null)
                msgs = ((InternalEObject) newBehavior)
                        .eInverseAdd(this,
                                EOPPOSITE_FEATURE_BASE
                                        - TypesPackage.ATOM_TYPE__BEHAVIOR,
                                null, msgs);
            msgs = basicSetBehavior(newBehavior, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    TypesPackage.ATOM_TYPE__BEHAVIOR, newBehavior,
                    newBehavior));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<AtomInternalDataDeclaration> getInternalDataDeclarations() {
        if (internalDataDeclarations == null) {
            internalDataDeclarations = new EObjectContainmentEList<AtomInternalDataDeclaration>(
                    AtomInternalDataDeclaration.class, this,
                    TypesPackage.ATOM_TYPE__INTERNAL_DATA_DECLARATIONS);
        }
        return internalDataDeclarations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<AtomExportPortDeclaration> getExportPortDeclarations() {
        if (exportPortDeclarations == null) {
            exportPortDeclarations = new EObjectContainmentEList<AtomExportPortDeclaration>(
                    AtomExportPortDeclaration.class, this,
                    TypesPackage.ATOM_TYPE__EXPORT_PORT_DECLARATIONS);
        }
        return exportPortDeclarations;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<AtomPriorityDeclaration> getPriorities() {
        if (priorities == null) {
            priorities = new EObjectContainmentEList<AtomPriorityDeclaration>(
                    AtomPriorityDeclaration.class, this,
                    TypesPackage.ATOM_TYPE__PRIORITIES);
        }
        return priorities;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<AtomInvariant> getInvariants() {
        if (invariants == null) {
            invariants = new EObjectContainmentEList<AtomInvariant>(
                    AtomInvariant.class, this,
                    TypesPackage.ATOM_TYPE__INVARIANTS);
        }
        return invariants;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public AtomInternalPortDeclaration getInternalPortDeclaration(String name) {
        for (AtomInternalPortDeclaration p : getInternalPortDeclarations()) {
            if (p.getName().equals(name)) {
                return p;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public AtomExternalPortDeclaration getExternalPortDeclaration(String name) {
        // TODO: implement this method
        // Ensure that you remove @generated or mark it @generated NOT
        throw new UnsupportedOperationException();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public AtomInternalDataDeclaration getInternalDataDeclaration(String name) {
        for (AtomInternalDataDeclaration aid : getInternalDataDeclarations()) {
            if (aid.getName().equals(name)) {
                return aid;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public AtomPriorityDeclaration getPriorityDeclaration(String name) {
        for (AtomPriorityDeclaration apd : getPriorities()) {
            if (apd.getName().equals(name))
                return apd;
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public AtomInvariant getInvariantDeclaration(String name) {
        for (AtomInvariant inv : getInvariants()) {
            if (inv.getName().equals(name)) {
                return inv;
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
        for (PortDeclaration epd : getExportedPortDeclarations()) {
            if (epd.getName().equals(name)) {
                return epd;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public DataDeclaration getExportedDataDeclaration(String name) {
        AtomInternalDataDeclaration aidd = getInternalDataDeclaration(name);
        if (aidd != null && aidd.isExported())
            return aidd;
        return null;
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
     * @generated
     */
    @Override
    public NotificationChain eInverseRemove(InternalEObject otherEnd,
            int featureID, NotificationChain msgs) {
        switch (featureID) {
        case TypesPackage.ATOM_TYPE__DATA_PARAMETER_DECLARATIONS:
            return ((InternalEList<?>) getDataParameterDeclarations())
                    .basicRemove(otherEnd, msgs);
        case TypesPackage.ATOM_TYPE__INTERNAL_PORT_DECLARATIONS:
            return ((InternalEList<?>) getInternalPortDeclarations())
                    .basicRemove(otherEnd, msgs);
        case TypesPackage.ATOM_TYPE__EXTERNAL_PORT_DECLARATIONS:
            return ((InternalEList<?>) getExternalPortDeclarations())
                    .basicRemove(otherEnd, msgs);
        case TypesPackage.ATOM_TYPE__BEHAVIOR:
            return basicSetBehavior(null, msgs);
        case TypesPackage.ATOM_TYPE__INTERNAL_DATA_DECLARATIONS:
            return ((InternalEList<?>) getInternalDataDeclarations())
                    .basicRemove(otherEnd, msgs);
        case TypesPackage.ATOM_TYPE__EXPORT_PORT_DECLARATIONS:
            return ((InternalEList<?>) getExportPortDeclarations())
                    .basicRemove(otherEnd, msgs);
        case TypesPackage.ATOM_TYPE__PRIORITIES:
            return ((InternalEList<?>) getPriorities()).basicRemove(otherEnd,
                    msgs);
        case TypesPackage.ATOM_TYPE__INVARIANTS:
            return ((InternalEList<?>) getInvariants()).basicRemove(otherEnd,
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
        case TypesPackage.ATOM_TYPE__EXPORTED_PORT_DECLARATIONS:
            return getExportedPortDeclarations();
        case TypesPackage.ATOM_TYPE__EXPORTED_DATA_DECLARATIONS:
            return getExportedDataDeclarations();
        case TypesPackage.ATOM_TYPE__DATA_PARAMETER_DECLARATIONS:
            return getDataParameterDeclarations();
        case TypesPackage.ATOM_TYPE__INTERNAL_PORT_DECLARATIONS:
            return getInternalPortDeclarations();
        case TypesPackage.ATOM_TYPE__EXTERNAL_PORT_DECLARATIONS:
            return getExternalPortDeclarations();
        case TypesPackage.ATOM_TYPE__BEHAVIOR:
            return getBehavior();
        case TypesPackage.ATOM_TYPE__INTERNAL_DATA_DECLARATIONS:
            return getInternalDataDeclarations();
        case TypesPackage.ATOM_TYPE__EXPORT_PORT_DECLARATIONS:
            return getExportPortDeclarations();
        case TypesPackage.ATOM_TYPE__PRIORITIES:
            return getPriorities();
        case TypesPackage.ATOM_TYPE__INVARIANTS:
            return getInvariants();
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
        case TypesPackage.ATOM_TYPE__EXPORTED_PORT_DECLARATIONS:
            getExportedPortDeclarations().clear();
            getExportedPortDeclarations()
                    .addAll((Collection<? extends PortDeclaration>) newValue);
            return;
        case TypesPackage.ATOM_TYPE__EXPORTED_DATA_DECLARATIONS:
            getExportedDataDeclarations().clear();
            getExportedDataDeclarations()
                    .addAll((Collection<? extends DataDeclaration>) newValue);
            return;
        case TypesPackage.ATOM_TYPE__DATA_PARAMETER_DECLARATIONS:
            getDataParameterDeclarations().clear();
            getDataParameterDeclarations().addAll(
                    (Collection<? extends ComponentDataParameterDeclaration>) newValue);
            return;
        case TypesPackage.ATOM_TYPE__INTERNAL_PORT_DECLARATIONS:
            getInternalPortDeclarations().clear();
            getInternalPortDeclarations().addAll(
                    (Collection<? extends AtomInternalPortDeclaration>) newValue);
            return;
        case TypesPackage.ATOM_TYPE__EXTERNAL_PORT_DECLARATIONS:
            getExternalPortDeclarations().clear();
            getExternalPortDeclarations().addAll(
                    (Collection<? extends AtomExternalPortDeclaration>) newValue);
            return;
        case TypesPackage.ATOM_TYPE__BEHAVIOR:
            setBehavior((PetriNet) newValue);
            return;
        case TypesPackage.ATOM_TYPE__INTERNAL_DATA_DECLARATIONS:
            getInternalDataDeclarations().clear();
            getInternalDataDeclarations().addAll(
                    (Collection<? extends AtomInternalDataDeclaration>) newValue);
            return;
        case TypesPackage.ATOM_TYPE__EXPORT_PORT_DECLARATIONS:
            getExportPortDeclarations().clear();
            getExportPortDeclarations().addAll(
                    (Collection<? extends AtomExportPortDeclaration>) newValue);
            return;
        case TypesPackage.ATOM_TYPE__PRIORITIES:
            getPriorities().clear();
            getPriorities().addAll(
                    (Collection<? extends AtomPriorityDeclaration>) newValue);
            return;
        case TypesPackage.ATOM_TYPE__INVARIANTS:
            getInvariants().clear();
            getInvariants()
                    .addAll((Collection<? extends AtomInvariant>) newValue);
            return;
        }
        super.eSet(featureID, newValue);
    }

    //
    //    /**
    //     * <!-- begin-user-doc -->
    //     * <!-- end-user-doc -->
    //     * @generated NOT
    //     */
    //    @SuppressWarnings("unchecked")
    //    @Override
    //    public void eSet(int featureID, Object newValue) {
    //        switch (featureID) {
    //        case TypesPackage.ATOM_TYPE__INTERNAL_PORT_DECLARATIONS:
    //            getExportedPortDeclarations().clear();
    //            HashSet<AtomInternalPortDeclaration> exportPortSet = new HashSet<AtomInternalPortDeclaration>();
    //
    //            for (AtomInternalPortDeclaration aipd : (Collection<? extends AtomInternalPortDeclaration>) newValue) {
    //                if (aipd.isExported()) {
    //                    exportPortSet.add(aipd);
    //                }
    //            }
    //            getExportedPortDeclarations().addAll(exportPortSet);
    //            return;
    //
    //        case TypesPackage.ATOM_TYPE__INTERNAL_DATA_DECLARATIONS:
    //            getInternalDataDeclarations().clear();
    //            HashSet<AtomInternalDataDeclaration> exportDataSet = new HashSet<AtomInternalDataDeclaration>();
    //
    //            for (AtomInternalDataDeclaration aipd : (Collection<? extends AtomInternalDataDeclaration>) newValue) {
    //                if (aipd.isExported()) {
    //                    exportDataSet.add(aipd);
    //                }
    //            }
    //            getExportedDataDeclarations().addAll(exportDataSet);
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
        case TypesPackage.ATOM_TYPE__EXPORTED_PORT_DECLARATIONS:
            getExportedPortDeclarations().clear();
            return;
        case TypesPackage.ATOM_TYPE__EXPORTED_DATA_DECLARATIONS:
            getExportedDataDeclarations().clear();
            return;
        case TypesPackage.ATOM_TYPE__DATA_PARAMETER_DECLARATIONS:
            getDataParameterDeclarations().clear();
            return;
        case TypesPackage.ATOM_TYPE__INTERNAL_PORT_DECLARATIONS:
            getInternalPortDeclarations().clear();
            return;
        case TypesPackage.ATOM_TYPE__EXTERNAL_PORT_DECLARATIONS:
            getExternalPortDeclarations().clear();
            return;
        case TypesPackage.ATOM_TYPE__BEHAVIOR:
            setBehavior((PetriNet) null);
            return;
        case TypesPackage.ATOM_TYPE__INTERNAL_DATA_DECLARATIONS:
            getInternalDataDeclarations().clear();
            return;
        case TypesPackage.ATOM_TYPE__EXPORT_PORT_DECLARATIONS:
            getExportPortDeclarations().clear();
            return;
        case TypesPackage.ATOM_TYPE__PRIORITIES:
            getPriorities().clear();
            return;
        case TypesPackage.ATOM_TYPE__INVARIANTS:
            getInvariants().clear();
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
        case TypesPackage.ATOM_TYPE__EXPORTED_PORT_DECLARATIONS:
            return exportedPortDeclarations != null
                    && !exportedPortDeclarations.isEmpty();
        case TypesPackage.ATOM_TYPE__EXPORTED_DATA_DECLARATIONS:
            return exportedDataDeclarations != null
                    && !exportedDataDeclarations.isEmpty();
        case TypesPackage.ATOM_TYPE__DATA_PARAMETER_DECLARATIONS:
            return dataParameterDeclarations != null
                    && !dataParameterDeclarations.isEmpty();
        case TypesPackage.ATOM_TYPE__INTERNAL_PORT_DECLARATIONS:
            return internalPortDeclarations != null
                    && !internalPortDeclarations.isEmpty();
        case TypesPackage.ATOM_TYPE__EXTERNAL_PORT_DECLARATIONS:
            return externalPortDeclarations != null
                    && !externalPortDeclarations.isEmpty();
        case TypesPackage.ATOM_TYPE__BEHAVIOR:
            return behavior != null;
        case TypesPackage.ATOM_TYPE__INTERNAL_DATA_DECLARATIONS:
            return internalDataDeclarations != null
                    && !internalDataDeclarations.isEmpty();
        case TypesPackage.ATOM_TYPE__EXPORT_PORT_DECLARATIONS:
            return exportPortDeclarations != null
                    && !exportPortDeclarations.isEmpty();
        case TypesPackage.ATOM_TYPE__PRIORITIES:
            return priorities != null && !priorities.isEmpty();
        case TypesPackage.ATOM_TYPE__INVARIANTS:
            return invariants != null && !invariants.isEmpty();
        }
        return super.eIsSet(featureID);
    }

} //AtomTypeImpl
