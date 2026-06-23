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

import bip2.Bip2Package;
import bip2.impl.Bip2PackageImpl;
import bip2.ujf.UjfPackage;
import bip2.ujf.impl.UjfPackageImpl;
import bip2.ujf.verimag.VerimagPackage;
import bip2.ujf.verimag.bip.BipPackage;
import bip2.ujf.verimag.bip.actionlang.ActionlangPackage;

import bip2.ujf.verimag.bip.actionlang.impl.ActionlangPackageImpl;

import bip2.ujf.verimag.bip.annotation.AnnotationPackage;
import bip2.ujf.verimag.bip.annotation.impl.AnnotationPackageImpl;
import bip2.ujf.verimag.bip.behavior.BehaviorPackage;

import bip2.ujf.verimag.bip.behavior.impl.BehaviorPackageImpl;

import bip2.ujf.verimag.bip.component.ComponentPackage;

import bip2.ujf.verimag.bip.component.atom.AtomPackage;

import bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl;

import bip2.ujf.verimag.bip.component.compound.CompoundPackage;

import bip2.ujf.verimag.bip.component.compound.impl.CompoundPackageImpl;

import bip2.ujf.verimag.bip.component.impl.ComponentPackageImpl;

import bip2.ujf.verimag.bip.connector.ConnectorPackage;

import bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl;

import bip2.ujf.verimag.bip.data.DataPackage;

import bip2.ujf.verimag.bip.data.impl.DataPackageImpl;

import bip2.ujf.verimag.bip.impl.BipPackageImpl;
import bip2.ujf.verimag.bip.instance.AtomExternalPortInstance;
import bip2.ujf.verimag.bip.instance.AtomInstance;
import bip2.ujf.verimag.bip.instance.AtomInternalPortInstance;
import bip2.ujf.verimag.bip.instance.ComponentInstance;
import bip2.ujf.verimag.bip.instance.CompoundInstance;
import bip2.ujf.verimag.bip.instance.CompoundPriorityInstance;
import bip2.ujf.verimag.bip.instance.ConnectorInstance;
import bip2.ujf.verimag.bip.instance.ConnectorPortInstance;
import bip2.ujf.verimag.bip.instance.DataInstance;
import bip2.ujf.verimag.bip.instance.ExportedPortInstance;
import bip2.ujf.verimag.bip.instance.InstanceFactory;
import bip2.ujf.verimag.bip.instance.InstancePackage;
import bip2.ujf.verimag.bip.instance.PortInstance;

import bip2.ujf.verimag.bip.instance.util.InstanceValidator;
import bip2.ujf.verimag.bip.invariant.InvariantPackage;
import bip2.ujf.verimag.bip.invariant.impl.InvariantPackageImpl;
import bip2.ujf.verimag.bip.packaging.PackagingPackage;

import bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl;

import bip2.ujf.verimag.bip.port.PortPackage;

import bip2.ujf.verimag.bip.port.impl.PortPackageImpl;

import bip2.ujf.verimag.bip.priority.PriorityPackage;

import bip2.ujf.verimag.bip.priority.impl.PriorityPackageImpl;

import bip2.ujf.verimag.bip.types.TypesPackage;

import bip2.ujf.verimag.bip.types.impl.TypesPackageImpl;

import bip2.ujf.verimag.impl.VerimagPackageImpl;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EOperation;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EReference;

import org.eclipse.emf.ecore.EValidator;
import org.eclipse.emf.ecore.impl.EPackageImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Package</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class InstancePackageImpl extends EPackageImpl
        implements InstancePackage {
    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass connectorInstanceEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass portInstanceEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass exportedPortInstanceEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass atomInternalPortInstanceEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass atomExternalPortInstanceEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass connectorPortInstanceEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass dataInstanceEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass compoundPriorityInstanceEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass atomInstanceEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass compoundInstanceEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass componentInstanceEClass = null;

    /**
     * Creates an instance of the model <b>Package</b>, registered with
     * {@link org.eclipse.emf.ecore.EPackage.Registry EPackage.Registry} by the package
     * package URI value.
     * <p>Note: the correct way to create the package is via the static
     * factory method {@link #init init()}, which also performs
     * initialization of the package, or returns the registered package,
     * if one already exists.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.ecore.EPackage.Registry
     * @see bip2.ujf.verimag.bip.instance.InstancePackage#eNS_URI
     * @see #init()
     * @generated
     */
    private InstancePackageImpl() {
        super(eNS_URI, InstanceFactory.eINSTANCE);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private static boolean isInited = false;

    /**
     * Creates, registers, and initializes the <b>Package</b> for this model, and for any others upon which it depends.
     * 
     * <p>This method is used to initialize {@link InstancePackage#eINSTANCE} when that field is accessed.
     * Clients should not invoke it directly. Instead, they should simply access that field to obtain the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #eNS_URI
     * @see #createPackageContents()
     * @see #initializePackageContents()
     * @generated
     */
    public static InstancePackage init() {
        if (isInited)
            return (InstancePackage) EPackage.Registry.INSTANCE
                    .getEPackage(InstancePackage.eNS_URI);

        // Obtain or create and register package
        InstancePackageImpl theInstancePackage = (InstancePackageImpl) (EPackage.Registry.INSTANCE
                .get(eNS_URI) instanceof InstancePackageImpl
                        ? EPackage.Registry.INSTANCE.get(eNS_URI)
                        : new InstancePackageImpl());

        isInited = true;

        // Obtain or create and register interdependencies
        Bip2PackageImpl theBip2Package = (Bip2PackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(Bip2Package.eNS_URI) instanceof Bip2PackageImpl
                        ? EPackage.Registry.INSTANCE
                                .getEPackage(Bip2Package.eNS_URI)
                        : Bip2Package.eINSTANCE);
        UjfPackageImpl theUjfPackage = (UjfPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(UjfPackage.eNS_URI) instanceof UjfPackageImpl
                        ? EPackage.Registry.INSTANCE
                                .getEPackage(UjfPackage.eNS_URI)
                        : UjfPackage.eINSTANCE);
        VerimagPackageImpl theVerimagPackage = (VerimagPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(
                        VerimagPackage.eNS_URI) instanceof VerimagPackageImpl
                                ? EPackage.Registry.INSTANCE
                                        .getEPackage(VerimagPackage.eNS_URI)
                                : VerimagPackage.eINSTANCE);
        BipPackageImpl theBipPackage = (BipPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(BipPackage.eNS_URI) instanceof BipPackageImpl
                        ? EPackage.Registry.INSTANCE
                                .getEPackage(BipPackage.eNS_URI)
                        : BipPackage.eINSTANCE);
        TypesPackageImpl theTypesPackage = (TypesPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(TypesPackage.eNS_URI) instanceof TypesPackageImpl
                        ? EPackage.Registry.INSTANCE
                                .getEPackage(TypesPackage.eNS_URI)
                        : TypesPackage.eINSTANCE);
        DataPackageImpl theDataPackage = (DataPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(DataPackage.eNS_URI) instanceof DataPackageImpl
                        ? EPackage.Registry.INSTANCE
                                .getEPackage(DataPackage.eNS_URI)
                        : DataPackage.eINSTANCE);
        PortPackageImpl thePortPackage = (PortPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(PortPackage.eNS_URI) instanceof PortPackageImpl
                        ? EPackage.Registry.INSTANCE
                                .getEPackage(PortPackage.eNS_URI)
                        : PortPackage.eINSTANCE);
        BehaviorPackageImpl theBehaviorPackage = (BehaviorPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(
                        BehaviorPackage.eNS_URI) instanceof BehaviorPackageImpl
                                ? EPackage.Registry.INSTANCE
                                        .getEPackage(BehaviorPackage.eNS_URI)
                                : BehaviorPackage.eINSTANCE);
        PriorityPackageImpl thePriorityPackage = (PriorityPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(
                        PriorityPackage.eNS_URI) instanceof PriorityPackageImpl
                                ? EPackage.Registry.INSTANCE
                                        .getEPackage(PriorityPackage.eNS_URI)
                                : PriorityPackage.eINSTANCE);
        ConnectorPackageImpl theConnectorPackage = (ConnectorPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(
                        ConnectorPackage.eNS_URI) instanceof ConnectorPackageImpl
                                ? EPackage.Registry.INSTANCE
                                        .getEPackage(ConnectorPackage.eNS_URI)
                                : ConnectorPackage.eINSTANCE);
        ComponentPackageImpl theComponentPackage = (ComponentPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(
                        ComponentPackage.eNS_URI) instanceof ComponentPackageImpl
                                ? EPackage.Registry.INSTANCE
                                        .getEPackage(ComponentPackage.eNS_URI)
                                : ComponentPackage.eINSTANCE);
        AtomPackageImpl theAtomPackage = (AtomPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(AtomPackage.eNS_URI) instanceof AtomPackageImpl
                        ? EPackage.Registry.INSTANCE
                                .getEPackage(AtomPackage.eNS_URI)
                        : AtomPackage.eINSTANCE);
        CompoundPackageImpl theCompoundPackage = (CompoundPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(
                        CompoundPackage.eNS_URI) instanceof CompoundPackageImpl
                                ? EPackage.Registry.INSTANCE
                                        .getEPackage(CompoundPackage.eNS_URI)
                                : CompoundPackage.eINSTANCE);
        PackagingPackageImpl thePackagingPackage = (PackagingPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(
                        PackagingPackage.eNS_URI) instanceof PackagingPackageImpl
                                ? EPackage.Registry.INSTANCE
                                        .getEPackage(PackagingPackage.eNS_URI)
                                : PackagingPackage.eINSTANCE);
        ActionlangPackageImpl theActionlangPackage = (ActionlangPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(
                        ActionlangPackage.eNS_URI) instanceof ActionlangPackageImpl
                                ? EPackage.Registry.INSTANCE
                                        .getEPackage(ActionlangPackage.eNS_URI)
                                : ActionlangPackage.eINSTANCE);
        AnnotationPackageImpl theAnnotationPackage = (AnnotationPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(
                        AnnotationPackage.eNS_URI) instanceof AnnotationPackageImpl
                                ? EPackage.Registry.INSTANCE
                                        .getEPackage(AnnotationPackage.eNS_URI)
                                : AnnotationPackage.eINSTANCE);
        InvariantPackageImpl theInvariantPackage = (InvariantPackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(
                        InvariantPackage.eNS_URI) instanceof InvariantPackageImpl
                                ? EPackage.Registry.INSTANCE
                                        .getEPackage(InvariantPackage.eNS_URI)
                                : InvariantPackage.eINSTANCE);

        // Create package meta-data objects
        theInstancePackage.createPackageContents();
        theBip2Package.createPackageContents();
        theUjfPackage.createPackageContents();
        theVerimagPackage.createPackageContents();
        theBipPackage.createPackageContents();
        theTypesPackage.createPackageContents();
        theDataPackage.createPackageContents();
        thePortPackage.createPackageContents();
        theBehaviorPackage.createPackageContents();
        thePriorityPackage.createPackageContents();
        theConnectorPackage.createPackageContents();
        theComponentPackage.createPackageContents();
        theAtomPackage.createPackageContents();
        theCompoundPackage.createPackageContents();
        thePackagingPackage.createPackageContents();
        theActionlangPackage.createPackageContents();
        theAnnotationPackage.createPackageContents();
        theInvariantPackage.createPackageContents();

        // Initialize created meta-data
        theInstancePackage.initializePackageContents();
        theBip2Package.initializePackageContents();
        theUjfPackage.initializePackageContents();
        theVerimagPackage.initializePackageContents();
        theBipPackage.initializePackageContents();
        theTypesPackage.initializePackageContents();
        theDataPackage.initializePackageContents();
        thePortPackage.initializePackageContents();
        theBehaviorPackage.initializePackageContents();
        thePriorityPackage.initializePackageContents();
        theConnectorPackage.initializePackageContents();
        theComponentPackage.initializePackageContents();
        theAtomPackage.initializePackageContents();
        theCompoundPackage.initializePackageContents();
        thePackagingPackage.initializePackageContents();
        theActionlangPackage.initializePackageContents();
        theAnnotationPackage.initializePackageContents();
        theInvariantPackage.initializePackageContents();

        // Register package validator
        EValidator.Registry.INSTANCE.put(theInstancePackage,
                new EValidator.Descriptor() {
                    public EValidator getEValidator() {
                        return InstanceValidator.INSTANCE;
                    }
                });

        // Mark meta-data to indicate it can't be changed
        theInstancePackage.freeze();

        // Update the registry and return the package
        EPackage.Registry.INSTANCE.put(InstancePackage.eNS_URI,
                theInstancePackage);
        return theInstancePackage;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getConnectorInstance() {
        return connectorInstanceEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorInstance_Declaration() {
        return (EReference) connectorInstanceEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorInstance_SubDataInstances() {
        return (EReference) connectorInstanceEClass.getEStructuralFeatures()
                .get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorInstance_PortParamInstances() {
        return (EReference) connectorInstanceEClass.getEStructuralFeatures()
                .get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorInstance_ExportedPort() {
        return (EReference) connectorInstanceEClass.getEStructuralFeatures()
                .get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getPortInstance() {
        return portInstanceEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getPortInstance_Declaration() {
        return (EReference) portInstanceEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getExportedPortInstance() {
        return exportedPortInstanceEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getExportedPortInstance_ReferencedPorts() {
        return (EReference) exportedPortInstanceEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getAtomInternalPortInstance() {
        return atomInternalPortInstanceEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getAtomInternalPortInstance_DataParamInstances() {
        return (EReference) atomInternalPortInstanceEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getAtomExternalPortInstance() {
        return atomExternalPortInstanceEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getAtomExternalPortInstance_DataParamInstances() {
        return (EReference) atomExternalPortInstanceEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getConnectorPortInstance() {
        return connectorPortInstanceEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorPortInstance_DataParamInstances() {
        return (EReference) connectorPortInstanceEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getDataInstance() {
        return dataInstanceEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getDataInstance_Declaration() {
        return (EReference) dataInstanceEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getDataInstance_ProxyLink() {
        return (EReference) dataInstanceEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getCompoundPriorityInstance() {
        return compoundPriorityInstanceEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundPriorityInstance_Declaration() {
        return (EReference) compoundPriorityInstanceEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundPriorityInstance_LowConnector() {
        return (EReference) compoundPriorityInstanceEClass
                .getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundPriorityInstance_HighConnector() {
        return (EReference) compoundPriorityInstanceEClass
                .getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundPriorityInstance_LowPorts() {
        return (EReference) compoundPriorityInstanceEClass
                .getEStructuralFeatures().get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundPriorityInstance_HighPorts() {
        return (EReference) compoundPriorityInstanceEClass
                .getEStructuralFeatures().get(4);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getAtomInstance() {
        return atomInstanceEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getAtomInstance_SubDataInstances() {
        return (EReference) atomInstanceEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getAtomInstance_InternalPorts() {
        return (EReference) atomInstanceEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getAtomInstance_ExternalPorts() {
        return (EReference) atomInstanceEClass.getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getCompoundInstance() {
        return compoundInstanceEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundInstance_SubPriorities() {
        return (EReference) compoundInstanceEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundInstance_SubConnectorInstances() {
        return (EReference) compoundInstanceEClass.getEStructuralFeatures()
                .get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundInstance_SubAtomInstances() {
        return (EReference) compoundInstanceEClass.getEStructuralFeatures()
                .get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundInstance_SubCompoundInstances() {
        return (EReference) compoundInstanceEClass.getEStructuralFeatures()
                .get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundInstance_SubDataInstances() {
        return (EReference) compoundInstanceEClass.getEStructuralFeatures()
                .get(4);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getComponentInstance() {
        return componentInstanceEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getComponentInstance_Declaration() {
        return (EReference) componentInstanceEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getComponentInstance_ExportedPorts() {
        return (EReference) componentInstanceEClass.getEStructuralFeatures()
                .get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public InstanceFactory getInstanceFactory() {
        return (InstanceFactory) getEFactoryInstance();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private boolean isCreated = false;

    /**
     * Creates the meta-model objects for the package.  This method is
     * guarded to have no affect on any invocation but its first.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void createPackageContents() {
        if (isCreated)
            return;
        isCreated = true;

        // Create classes and their features
        connectorInstanceEClass = createEClass(CONNECTOR_INSTANCE);
        createEReference(connectorInstanceEClass,
                CONNECTOR_INSTANCE__DECLARATION);
        createEReference(connectorInstanceEClass,
                CONNECTOR_INSTANCE__SUB_DATA_INSTANCES);
        createEReference(connectorInstanceEClass,
                CONNECTOR_INSTANCE__PORT_PARAM_INSTANCES);
        createEReference(connectorInstanceEClass,
                CONNECTOR_INSTANCE__EXPORTED_PORT);

        dataInstanceEClass = createEClass(DATA_INSTANCE);
        createEReference(dataInstanceEClass, DATA_INSTANCE__DECLARATION);
        createEReference(dataInstanceEClass, DATA_INSTANCE__PROXY_LINK);

        compoundPriorityInstanceEClass = createEClass(
                COMPOUND_PRIORITY_INSTANCE);
        createEReference(compoundPriorityInstanceEClass,
                COMPOUND_PRIORITY_INSTANCE__DECLARATION);
        createEReference(compoundPriorityInstanceEClass,
                COMPOUND_PRIORITY_INSTANCE__LOW_CONNECTOR);
        createEReference(compoundPriorityInstanceEClass,
                COMPOUND_PRIORITY_INSTANCE__HIGH_CONNECTOR);
        createEReference(compoundPriorityInstanceEClass,
                COMPOUND_PRIORITY_INSTANCE__LOW_PORTS);
        createEReference(compoundPriorityInstanceEClass,
                COMPOUND_PRIORITY_INSTANCE__HIGH_PORTS);

        atomInstanceEClass = createEClass(ATOM_INSTANCE);
        createEReference(atomInstanceEClass, ATOM_INSTANCE__SUB_DATA_INSTANCES);
        createEReference(atomInstanceEClass, ATOM_INSTANCE__INTERNAL_PORTS);
        createEReference(atomInstanceEClass, ATOM_INSTANCE__EXTERNAL_PORTS);

        compoundInstanceEClass = createEClass(COMPOUND_INSTANCE);
        createEReference(compoundInstanceEClass,
                COMPOUND_INSTANCE__SUB_PRIORITIES);
        createEReference(compoundInstanceEClass,
                COMPOUND_INSTANCE__SUB_CONNECTOR_INSTANCES);
        createEReference(compoundInstanceEClass,
                COMPOUND_INSTANCE__SUB_ATOM_INSTANCES);
        createEReference(compoundInstanceEClass,
                COMPOUND_INSTANCE__SUB_COMPOUND_INSTANCES);
        createEReference(compoundInstanceEClass,
                COMPOUND_INSTANCE__SUB_DATA_INSTANCES);

        componentInstanceEClass = createEClass(COMPONENT_INSTANCE);
        createEReference(componentInstanceEClass,
                COMPONENT_INSTANCE__DECLARATION);
        createEReference(componentInstanceEClass,
                COMPONENT_INSTANCE__EXPORTED_PORTS);

        portInstanceEClass = createEClass(PORT_INSTANCE);
        createEReference(portInstanceEClass, PORT_INSTANCE__DECLARATION);

        exportedPortInstanceEClass = createEClass(EXPORTED_PORT_INSTANCE);
        createEReference(exportedPortInstanceEClass,
                EXPORTED_PORT_INSTANCE__REFERENCED_PORTS);

        atomInternalPortInstanceEClass = createEClass(
                ATOM_INTERNAL_PORT_INSTANCE);
        createEReference(atomInternalPortInstanceEClass,
                ATOM_INTERNAL_PORT_INSTANCE__DATA_PARAM_INSTANCES);

        atomExternalPortInstanceEClass = createEClass(
                ATOM_EXTERNAL_PORT_INSTANCE);
        createEReference(atomExternalPortInstanceEClass,
                ATOM_EXTERNAL_PORT_INSTANCE__DATA_PARAM_INSTANCES);

        connectorPortInstanceEClass = createEClass(CONNECTOR_PORT_INSTANCE);
        createEReference(connectorPortInstanceEClass,
                CONNECTOR_PORT_INSTANCE__DATA_PARAM_INSTANCES);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private boolean isInitialized = false;

    /**
     * Complete the initialization of the package and its meta-model.  This
     * method is guarded to have no affect on any invocation but its first.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void initializePackageContents() {
        if (isInitialized)
            return;
        isInitialized = true;

        // Initialize package
        setName(eNAME);
        setNsPrefix(eNS_PREFIX);
        setNsURI(eNS_URI);

        // Obtain other dependent packages
        ConnectorPackage theConnectorPackage = (ConnectorPackage) EPackage.Registry.INSTANCE
                .getEPackage(ConnectorPackage.eNS_URI);
        DataPackage theDataPackage = (DataPackage) EPackage.Registry.INSTANCE
                .getEPackage(DataPackage.eNS_URI);
        PriorityPackage thePriorityPackage = (PriorityPackage) EPackage.Registry.INSTANCE
                .getEPackage(PriorityPackage.eNS_URI);
        ComponentPackage theComponentPackage = (ComponentPackage) EPackage.Registry.INSTANCE
                .getEPackage(ComponentPackage.eNS_URI);
        PortPackage thePortPackage = (PortPackage) EPackage.Registry.INSTANCE
                .getEPackage(PortPackage.eNS_URI);

        // Create type parameters

        // Set bounds for type parameters

        // Add supertypes to classes
        atomInstanceEClass.getESuperTypes().add(this.getComponentInstance());
        compoundInstanceEClass.getESuperTypes()
                .add(this.getComponentInstance());
        exportedPortInstanceEClass.getESuperTypes().add(this.getPortInstance());
        atomInternalPortInstanceEClass.getESuperTypes()
                .add(this.getPortInstance());
        atomExternalPortInstanceEClass.getESuperTypes()
                .add(this.getPortInstance());
        connectorPortInstanceEClass.getESuperTypes()
                .add(this.getPortInstance());

        // Initialize classes and features; add operations and parameters
        initEClass(connectorInstanceEClass, ConnectorInstance.class,
                "ConnectorInstance", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEReference(getConnectorInstance_Declaration(),
                theConnectorPackage.getConnectorDeclaration(), null,
                "declaration", null, 1, 1, ConnectorInstance.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE,
                IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getConnectorInstance_SubDataInstances(),
                this.getDataInstance(), null, "subDataInstances", null, 0, -1,
                ConnectorInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getConnectorInstance_PortParamInstances(),
                this.getPortInstance(), null, "portParamInstances", null, 0, -1,
                ConnectorInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getConnectorInstance_ExportedPort(),
                this.getConnectorPortInstance(), null, "exportedPort", null, 0,
                1, ConnectorInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        EOperation op = addEOperation(connectorInstanceEClass,
                this.getDataInstance(), "getDataInstance", 0, 1, IS_UNIQUE,
                IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 1, 1, IS_UNIQUE,
                IS_ORDERED);

        initEClass(dataInstanceEClass, DataInstance.class, "DataInstance",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getDataInstance_Declaration(),
                theDataPackage.getDataDeclaration(), null, "declaration", null,
                1, 1, DataInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getDataInstance_ProxyLink(), this.getDataInstance(),
                null, "proxyLink", null, 0, 1, DataInstance.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE,
                IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        initEClass(compoundPriorityInstanceEClass,
                CompoundPriorityInstance.class, "CompoundPriorityInstance",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getCompoundPriorityInstance_Declaration(),
                thePriorityPackage.getCompoundPriorityDeclaration(), null,
                "declaration", null, 1, 1, CompoundPriorityInstance.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE,
                IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getCompoundPriorityInstance_LowConnector(),
                this.getConnectorInstance(), null, "lowConnector", null, 0, 1,
                CompoundPriorityInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getCompoundPriorityInstance_HighConnector(),
                this.getConnectorInstance(), null, "highConnector", null, 0, 1,
                CompoundPriorityInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getCompoundPriorityInstance_LowPorts(),
                this.getPortInstance(), null, "lowPorts", null, 0, -1,
                CompoundPriorityInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getCompoundPriorityInstance_HighPorts(),
                this.getPortInstance(), null, "highPorts", null, 0, -1,
                CompoundPriorityInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(atomInstanceEClass, AtomInstance.class, "AtomInstance",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getAtomInstance_SubDataInstances(),
                this.getDataInstance(), null, "subDataInstances", null, 0, -1,
                AtomInstance.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE,
                IS_COMPOSITE, !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE,
                !IS_DERIVED, IS_ORDERED);
        initEReference(getAtomInstance_InternalPorts(),
                this.getAtomInternalPortInstance(), null, "internalPorts", null,
                0, -1, AtomInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getAtomInstance_ExternalPorts(),
                this.getAtomExternalPortInstance(), null, "externalPorts", null,
                0, -1, AtomInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        op = addEOperation(atomInstanceEClass, this.getDataInstance(),
                "getInternalDataInstance", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(atomInstanceEClass,
                this.getAtomInternalPortInstance(), "getInternalPortInstance",
                0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        initEClass(compoundInstanceEClass, CompoundInstance.class,
                "CompoundInstance", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEReference(getCompoundInstance_SubPriorities(),
                this.getCompoundPriorityInstance(), null, "subPriorities", null,
                0, -1, CompoundInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getCompoundInstance_SubConnectorInstances(),
                this.getConnectorInstance(), null, "subConnectorInstances",
                null, 0, -1, CompoundInstance.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getCompoundInstance_SubAtomInstances(),
                this.getAtomInstance(), null, "subAtomInstances", null, 0, -1,
                CompoundInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getCompoundInstance_SubCompoundInstances(),
                this.getCompoundInstance(), null, "subCompoundInstances", null,
                0, -1, CompoundInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getCompoundInstance_SubDataInstances(),
                this.getDataInstance(), null, "subDataInstances", null, 0, -1,
                CompoundInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        op = addEOperation(compoundInstanceEClass, this.getComponentInstance(),
                "getComponentInstance", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(compoundInstanceEClass, this.getAtomInstance(),
                "getAtomInstance", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(compoundInstanceEClass, this.getCompoundInstance(),
                "getCompoundInstance", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(compoundInstanceEClass, this.getConnectorInstance(),
                "getConnectorInstance", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(compoundInstanceEClass,
                this.getCompoundPriorityInstance(),
                "getCompoundPriorityInstance", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        initEClass(componentInstanceEClass, ComponentInstance.class,
                "ComponentInstance", IS_ABSTRACT, IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEReference(getComponentInstance_Declaration(),
                theComponentPackage.getComponentDeclaration(), null,
                "declaration", null, 1, 1, ComponentInstance.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE,
                IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getComponentInstance_ExportedPorts(),
                this.getExportedPortInstance(), null, "exportedPorts", null, 0,
                -1, ComponentInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        op = addEOperation(componentInstanceEClass,
                this.getExportedPortInstance(), "getPortInstance", 0, 1,
                IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(componentInstanceEClass, this.getDataInstance(),
                "getDataInstance", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        initEClass(portInstanceEClass, PortInstance.class, "PortInstance",
                IS_ABSTRACT, IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getPortInstance_Declaration(),
                thePortPackage.getPortDeclaration(), null, "declaration", null,
                1, 1, PortInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(exportedPortInstanceEClass, ExportedPortInstance.class,
                "ExportedPortInstance", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEReference(getExportedPortInstance_ReferencedPorts(),
                this.getPortInstance(), null, "referencedPorts", null, 1, -1,
                ExportedPortInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(atomInternalPortInstanceEClass,
                AtomInternalPortInstance.class, "AtomInternalPortInstance",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getAtomInternalPortInstance_DataParamInstances(),
                this.getDataInstance(), null, "dataParamInstances", null, 0, -1,
                AtomInternalPortInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(atomExternalPortInstanceEClass,
                AtomExternalPortInstance.class, "AtomExternalPortInstance",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getAtomExternalPortInstance_DataParamInstances(),
                this.getDataInstance(), null, "dataParamInstances", null, 0, -1,
                AtomExternalPortInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(connectorPortInstanceEClass, ConnectorPortInstance.class,
                "ConnectorPortInstance", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEReference(getConnectorPortInstance_DataParamInstances(),
                this.getDataInstance(), null, "dataParamInstances", null, 0, -1,
                ConnectorPortInstance.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        // Create annotations
        // http://www.eclipse.org/emf/2002/Ecore
        createEcoreAnnotations();
    }

    /**
     * Initializes the annotations for <b>http://www.eclipse.org/emf/2002/Ecore</b>.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected void createEcoreAnnotations() {
        String source = "http://www.eclipse.org/emf/2002/Ecore";
        addAnnotation(connectorInstanceEClass, source,
                new String[] { "constraints",
                        "connectorDoesNotBindTheSameComponentMoreThanOnce" });
    }

} //InstancePackageImpl
