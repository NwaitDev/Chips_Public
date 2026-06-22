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

package bip2.ujf.verimag.bip.types.impl;

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
import bip2.ujf.verimag.bip.instance.InstancePackage;
import bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl;
import bip2.ujf.verimag.bip.invariant.InvariantPackage;
import bip2.ujf.verimag.bip.invariant.impl.InvariantPackageImpl;
import bip2.ujf.verimag.bip.packaging.PackagingPackage;

import bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl;

import bip2.ujf.verimag.bip.port.PortPackage;

import bip2.ujf.verimag.bip.port.impl.PortPackageImpl;

import bip2.ujf.verimag.bip.priority.PriorityPackage;
import bip2.ujf.verimag.bip.priority.impl.PriorityPackageImpl;
import bip2.ujf.verimag.bip.types.AtomType;
import bip2.ujf.verimag.bip.types.BipType;
import bip2.ujf.verimag.bip.types.ComponentType;
import bip2.ujf.verimag.bip.types.CompoundType;
import bip2.ujf.verimag.bip.types.ConnectorType;
import bip2.ujf.verimag.bip.types.PortType;
import bip2.ujf.verimag.bip.types.Type;
import bip2.ujf.verimag.bip.types.TypesFactory;
import bip2.ujf.verimag.bip.types.TypesPackage;

import bip2.ujf.verimag.bip.types.util.TypesValidator;
import bip2.ujf.verimag.impl.VerimagPackageImpl;
import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EDataType;
import org.eclipse.emf.ecore.EGenericType;
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
public class TypesPackageImpl extends EPackageImpl implements TypesPackage {
    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass typeEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass atomTypeEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass componentTypeEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass compoundTypeEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass connectorTypeEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass portTypeEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass bipTypeEClass = null;

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
     * @see bip2.ujf.verimag.bip.types.TypesPackage#eNS_URI
     * @see #init()
     * @generated
     */
    private TypesPackageImpl() {
        super(eNS_URI, TypesFactory.eINSTANCE);
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
     * <p>This method is used to initialize {@link TypesPackage#eINSTANCE} when that field is accessed.
     * Clients should not invoke it directly. Instead, they should simply access that field to obtain the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #eNS_URI
     * @see #createPackageContents()
     * @see #initializePackageContents()
     * @generated
     */
    public static TypesPackage init() {
        if (isInited)
            return (TypesPackage) EPackage.Registry.INSTANCE
                    .getEPackage(TypesPackage.eNS_URI);

        // Obtain or create and register package
        TypesPackageImpl theTypesPackage = (TypesPackageImpl) (EPackage.Registry.INSTANCE
                .get(eNS_URI) instanceof TypesPackageImpl
                        ? EPackage.Registry.INSTANCE.get(eNS_URI)
                        : new TypesPackageImpl());

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
        InstancePackageImpl theInstancePackage = (InstancePackageImpl) (EPackage.Registry.INSTANCE
                .getEPackage(
                        InstancePackage.eNS_URI) instanceof InstancePackageImpl
                                ? EPackage.Registry.INSTANCE
                                        .getEPackage(InstancePackage.eNS_URI)
                                : InstancePackage.eINSTANCE);
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
        theTypesPackage.createPackageContents();
        theBip2Package.createPackageContents();
        theUjfPackage.createPackageContents();
        theVerimagPackage.createPackageContents();
        theBipPackage.createPackageContents();
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
        theInstancePackage.createPackageContents();
        theAnnotationPackage.createPackageContents();
        theInvariantPackage.createPackageContents();

        // Initialize created meta-data
        theTypesPackage.initializePackageContents();
        theBip2Package.initializePackageContents();
        theUjfPackage.initializePackageContents();
        theVerimagPackage.initializePackageContents();
        theBipPackage.initializePackageContents();
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
        theInstancePackage.initializePackageContents();
        theAnnotationPackage.initializePackageContents();
        theInvariantPackage.initializePackageContents();

        // Register package validator
        EValidator.Registry.INSTANCE.put(theTypesPackage,
                new EValidator.Descriptor() {
                    public EValidator getEValidator() {
                        return TypesValidator.INSTANCE;
                    }
                });

        // Mark meta-data to indicate it can't be changed
        theTypesPackage.freeze();

        // Update the registry and return the package
        EPackage.Registry.INSTANCE.put(TypesPackage.eNS_URI, theTypesPackage);
        return theTypesPackage;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getType() {
        return typeEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getType_Name() {
        return (EAttribute) typeEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getType_Native() {
        return (EAttribute) typeEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getType_SuperTypes() {
        return (EReference) typeEClass.getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getType_CastableTypes() {
        return (EReference) typeEClass.getEStructuralFeatures().get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getAtomType() {
        return atomTypeEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getAtomType_InternalPortDeclarations() {
        return (EReference) atomTypeEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getAtomType_ExternalPortDeclarations() {
        return (EReference) atomTypeEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getAtomType_Behavior() {
        return (EReference) atomTypeEClass.getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getAtomType_InternalDataDeclarations() {
        return (EReference) atomTypeEClass.getEStructuralFeatures().get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getAtomType_ExportPortDeclarations() {
        return (EReference) atomTypeEClass.getEStructuralFeatures().get(4);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getAtomType_Priorities() {
        return (EReference) atomTypeEClass.getEStructuralFeatures().get(5);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getAtomType_Invariants() {
        return (EReference) atomTypeEClass.getEStructuralFeatures().get(6);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getComponentType() {
        return componentTypeEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getComponentType_ExportedPortDeclarations() {
        return (EReference) componentTypeEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getComponentType_ExportedDataDeclarations() {
        return (EReference) componentTypeEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getComponentType_DataParameterDeclarations() {
        return (EReference) componentTypeEClass.getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getCompoundType() {
        return compoundTypeEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundType_ComponentDeclarations() {
        return (EReference) compoundTypeEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundType_ConnectorDeclarations() {
        return (EReference) compoundTypeEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundType_ExportPortDeclarations() {
        return (EReference) compoundTypeEClass.getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundType_ExportDataDeclarations() {
        return (EReference) compoundTypeEClass.getEStructuralFeatures().get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCompoundType_Priorities() {
        return (EReference) compoundTypeEClass.getEStructuralFeatures().get(4);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getConnectorType() {
        return connectorTypeEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorType_ExportedPortDeclaration() {
        return (EReference) connectorTypeEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorType_DataDeclarations() {
        return (EReference) connectorTypeEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorType_Interactions() {
        return (EReference) connectorTypeEClass.getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorType_InteractionDefinition() {
        return (EReference) connectorTypeEClass.getEStructuralFeatures().get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getConnectorType_Ports() {
        return (EReference) connectorTypeEClass.getEStructuralFeatures().get(4);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getPortType() {
        return portTypeEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getPortType_DataParameterDeclarations() {
        return (EReference) portTypeEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getBipType() {
        return bipTypeEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public TypesFactory getTypesFactory() {
        return (TypesFactory) getEFactoryInstance();
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
        typeEClass = createEClass(TYPE);
        createEAttribute(typeEClass, TYPE__NAME);
        createEAttribute(typeEClass, TYPE__NATIVE);
        createEReference(typeEClass, TYPE__SUPER_TYPES);
        createEReference(typeEClass, TYPE__CASTABLE_TYPES);

        bipTypeEClass = createEClass(BIP_TYPE);

        componentTypeEClass = createEClass(COMPONENT_TYPE);
        createEReference(componentTypeEClass,
                COMPONENT_TYPE__EXPORTED_PORT_DECLARATIONS);
        createEReference(componentTypeEClass,
                COMPONENT_TYPE__EXPORTED_DATA_DECLARATIONS);
        createEReference(componentTypeEClass,
                COMPONENT_TYPE__DATA_PARAMETER_DECLARATIONS);

        atomTypeEClass = createEClass(ATOM_TYPE);
        createEReference(atomTypeEClass, ATOM_TYPE__INTERNAL_PORT_DECLARATIONS);
        createEReference(atomTypeEClass, ATOM_TYPE__EXTERNAL_PORT_DECLARATIONS);
        createEReference(atomTypeEClass, ATOM_TYPE__BEHAVIOR);
        createEReference(atomTypeEClass, ATOM_TYPE__INTERNAL_DATA_DECLARATIONS);
        createEReference(atomTypeEClass, ATOM_TYPE__EXPORT_PORT_DECLARATIONS);
        createEReference(atomTypeEClass, ATOM_TYPE__PRIORITIES);
        createEReference(atomTypeEClass, ATOM_TYPE__INVARIANTS);

        compoundTypeEClass = createEClass(COMPOUND_TYPE);
        createEReference(compoundTypeEClass,
                COMPOUND_TYPE__COMPONENT_DECLARATIONS);
        createEReference(compoundTypeEClass,
                COMPOUND_TYPE__CONNECTOR_DECLARATIONS);
        createEReference(compoundTypeEClass,
                COMPOUND_TYPE__EXPORT_PORT_DECLARATIONS);
        createEReference(compoundTypeEClass,
                COMPOUND_TYPE__EXPORT_DATA_DECLARATIONS);
        createEReference(compoundTypeEClass, COMPOUND_TYPE__PRIORITIES);

        connectorTypeEClass = createEClass(CONNECTOR_TYPE);
        createEReference(connectorTypeEClass,
                CONNECTOR_TYPE__EXPORTED_PORT_DECLARATION);
        createEReference(connectorTypeEClass,
                CONNECTOR_TYPE__DATA_DECLARATIONS);
        createEReference(connectorTypeEClass, CONNECTOR_TYPE__INTERACTIONS);
        createEReference(connectorTypeEClass,
                CONNECTOR_TYPE__INTERACTION_DEFINITION);
        createEReference(connectorTypeEClass, CONNECTOR_TYPE__PORTS);

        portTypeEClass = createEClass(PORT_TYPE);
        createEReference(portTypeEClass,
                PORT_TYPE__DATA_PARAMETER_DECLARATIONS);
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
        AnnotationPackage theAnnotationPackage = (AnnotationPackage) EPackage.Registry.INSTANCE
                .getEPackage(AnnotationPackage.eNS_URI);
        PortPackage thePortPackage = (PortPackage) EPackage.Registry.INSTANCE
                .getEPackage(PortPackage.eNS_URI);
        DataPackage theDataPackage = (DataPackage) EPackage.Registry.INSTANCE
                .getEPackage(DataPackage.eNS_URI);
        ComponentPackage theComponentPackage = (ComponentPackage) EPackage.Registry.INSTANCE
                .getEPackage(ComponentPackage.eNS_URI);
        AtomPackage theAtomPackage = (AtomPackage) EPackage.Registry.INSTANCE
                .getEPackage(AtomPackage.eNS_URI);
        BehaviorPackage theBehaviorPackage = (BehaviorPackage) EPackage.Registry.INSTANCE
                .getEPackage(BehaviorPackage.eNS_URI);
        PriorityPackage thePriorityPackage = (PriorityPackage) EPackage.Registry.INSTANCE
                .getEPackage(PriorityPackage.eNS_URI);
        InvariantPackage theInvariantPackage = (InvariantPackage) EPackage.Registry.INSTANCE
                .getEPackage(InvariantPackage.eNS_URI);
        ConnectorPackage theConnectorPackage = (ConnectorPackage) EPackage.Registry.INSTANCE
                .getEPackage(ConnectorPackage.eNS_URI);
        CompoundPackage theCompoundPackage = (CompoundPackage) EPackage.Registry.INSTANCE
                .getEPackage(CompoundPackage.eNS_URI);

        // Create type parameters

        // Set bounds for type parameters

        // Add supertypes to classes
        typeEClass.getESuperTypes()
                .add(theAnnotationPackage.getAnnotatedElement());
        bipTypeEClass.getESuperTypes().add(this.getType());
        componentTypeEClass.getESuperTypes().add(this.getBipType());
        atomTypeEClass.getESuperTypes().add(this.getComponentType());
        compoundTypeEClass.getESuperTypes().add(this.getComponentType());
        connectorTypeEClass.getESuperTypes().add(this.getBipType());
        portTypeEClass.getESuperTypes().add(this.getBipType());

        // Initialize classes and features; add operations and parameters
        initEClass(typeEClass, Type.class, "Type", IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getType_Name(), ecorePackage.getEString(), "name", null,
                1, 1, Type.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE,
                !IS_UNSETTABLE, IS_ID, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getType_Native(), ecorePackage.getEBoolean(), "native",
                "false", 1, 1, Type.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getType_SuperTypes(), this.getType(), null, "superTypes",
                null, 0, -1, Type.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getType_CastableTypes(), this.getType(), null,
                "castableTypes", null, 0, -1, Type.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        EOperation op = addEOperation(typeEClass, ecorePackage.getEBoolean(),
                "isKindOf", 1, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, this.getType(), "type", 0, 1, IS_UNIQUE, IS_ORDERED);

        op = addEOperation(typeEClass, ecorePackage.getEBoolean(),
                "isSubTypeOf", 1, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, this.getType(), "type", 0, 1, IS_UNIQUE, IS_ORDERED);

        op = addEOperation(typeEClass, ecorePackage.getEBoolean(), "hasCastFor",
                1, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, this.getType(), "type", 0, 1, IS_UNIQUE, IS_ORDERED);

        initEClass(bipTypeEClass, BipType.class, "BipType", IS_ABSTRACT,
                IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);

        initEClass(componentTypeEClass, ComponentType.class, "ComponentType",
                IS_ABSTRACT, IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getComponentType_ExportedPortDeclarations(),
                thePortPackage.getPortDeclaration(), null,
                "exportedPortDeclarations", null, 0, -1, ComponentType.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE,
                IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getComponentType_ExportedDataDeclarations(),
                theDataPackage.getDataDeclaration(), null,
                "exportedDataDeclarations", null, 0, -1, ComponentType.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE,
                IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getComponentType_DataParameterDeclarations(),
                theComponentPackage.getComponentDataParameterDeclaration(),
                null, "dataParameterDeclarations", null, 0, -1,
                ComponentType.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE,
                IS_COMPOSITE, !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE,
                !IS_DERIVED, IS_ORDERED);

        op = addEOperation(componentTypeEClass,
                thePortPackage.getPortDeclaration(),
                "getExportedPortDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(componentTypeEClass,
                theDataPackage.getDataDeclaration(),
                "getExportedDataDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(componentTypeEClass,
                theComponentPackage.getComponentDataParameterDeclaration(),
                "getDataParameterDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 1, 1, IS_UNIQUE,
                IS_ORDERED);

        initEClass(atomTypeEClass, AtomType.class, "AtomType", !IS_ABSTRACT,
                !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getAtomType_InternalPortDeclarations(),
                theAtomPackage.getAtomInternalPortDeclaration(), null,
                "internalPortDeclarations", null, 0, -1, AtomType.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getAtomType_ExternalPortDeclarations(),
                theAtomPackage.getAtomExternalPortDeclaration(), null,
                "externalPortDeclarations", null, 0, -1, AtomType.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getAtomType_Behavior(), theBehaviorPackage.getPetriNet(),
                null, "behavior", null, 1, 1, AtomType.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getAtomType_InternalDataDeclarations(),
                theAtomPackage.getAtomInternalDataDeclaration(), null,
                "internalDataDeclarations", null, 0, -1, AtomType.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getAtomType_ExportPortDeclarations(),
                theAtomPackage.getAtomExportPortDeclaration(), null,
                "exportPortDeclarations", null, 0, -1, AtomType.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getAtomType_Priorities(),
                thePriorityPackage.getAtomPriorityDeclaration(), null,
                "priorities", null, 0, -1, AtomType.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getAtomType_Invariants(),
                theInvariantPackage.getAtomInvariant(), null, "invariants",
                null, 0, -1, AtomType.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        op = addEOperation(atomTypeEClass,
                theAtomPackage.getAtomInternalPortDeclaration(),
                "getInternalPortDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(atomTypeEClass,
                theAtomPackage.getAtomExternalPortDeclaration(),
                "getExternalPortDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(atomTypeEClass,
                theAtomPackage.getAtomInternalDataDeclaration(),
                "getInternalDataDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(atomTypeEClass,
                thePriorityPackage.getAtomPriorityDeclaration(),
                "getPriorityDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(atomTypeEClass,
                theInvariantPackage.getAtomInvariant(),
                "getInvariantDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        initEClass(compoundTypeEClass, CompoundType.class, "CompoundType",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getCompoundType_ComponentDeclarations(),
                theComponentPackage.getComponentDeclaration(), null,
                "componentDeclarations", null, 0, -1, CompoundType.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getCompoundType_ConnectorDeclarations(),
                theConnectorPackage.getConnectorDeclaration(), null,
                "connectorDeclarations", null, 0, -1, CompoundType.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getCompoundType_ExportPortDeclarations(),
                theCompoundPackage.getCompoundExportPortDeclaration(), null,
                "exportPortDeclarations", null, 0, -1, CompoundType.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getCompoundType_ExportDataDeclarations(),
                theCompoundPackage.getCompoundExportDataDeclaration(), null,
                "exportDataDeclarations", null, 0, -1, CompoundType.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getCompoundType_Priorities(),
                thePriorityPackage.getCompoundPriorityDeclaration(), null,
                "priorities", null, 0, -1, CompoundType.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        op = addEOperation(compoundTypeEClass,
                theComponentPackage.getComponentDeclaration(),
                "getComponentDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(compoundTypeEClass,
                theConnectorPackage.getConnectorDeclaration(),
                "getConnectorDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(compoundTypeEClass,
                theCompoundPackage.getCompoundExportPortDeclaration(),
                "getExportPortDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(compoundTypeEClass,
                theCompoundPackage.getCompoundExportDataDeclaration(),
                "getExportDataDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(compoundTypeEClass,
                thePriorityPackage.getCompoundPriorityDeclaration(),
                "getPriorityDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 1, 1, IS_UNIQUE,
                IS_ORDERED);

        initEClass(connectorTypeEClass, ConnectorType.class, "ConnectorType",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getConnectorType_ExportedPortDeclaration(),
                theConnectorPackage.getConnectorExportedPortDeclaration(), null,
                "exportedPortDeclaration", null, 0, 1, ConnectorType.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getConnectorType_DataDeclarations(),
                theConnectorPackage.getConnectorDataDeclaration(), null,
                "dataDeclarations", null, 0, -1, ConnectorType.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getConnectorType_Interactions(),
                theConnectorPackage.getConnectorInteractionAction(), null,
                "interactions", null, 0, -1, ConnectorType.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getConnectorType_InteractionDefinition(),
                theConnectorPackage.getConnectorInteractionDefinition(), null,
                "interactionDefinition", null, 1, 1, ConnectorType.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getConnectorType_Ports(),
                theConnectorPackage.getConnectorPortParameterDeclaration(),
                null, "ports", null, 1, -1, ConnectorType.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        op = addEOperation(connectorTypeEClass,
                theConnectorPackage.getConnectorDataDeclaration(),
                "getDataDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(connectorTypeEClass,
                theConnectorPackage.getConnectorPortParameterDeclaration(),
                "getPortParameterDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

        op = addEOperation(connectorTypeEClass, ecorePackage.getEBoolean(),
                "isDefined", 1, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op,
                theConnectorPackage.getConnectorPortParameterDeclaration(),
                "ports", 0, -1, !IS_UNIQUE, !IS_ORDERED);

        initEClass(portTypeEClass, PortType.class, "PortType", !IS_ABSTRACT,
                !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getPortType_DataParameterDeclarations(),
                thePortPackage.getPortDataParameterDeclaration(), null,
                "dataParameterDeclarations", null, 0, -1, PortType.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        op = addEOperation(portTypeEClass,
                thePortPackage.getPortDataParameterDeclaration(),
                "getDataParameterDeclaration", 0, 1, IS_UNIQUE, IS_ORDERED);
        addEParameter(op, ecorePackage.getEString(), "name", 0, 1, IS_UNIQUE,
                IS_ORDERED);

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
        addAnnotation(atomTypeEClass, source, new String[] { "constraints",
                "InternalDataSynchronizedWithExportedData checkForCyclesInPrioritiesInAtom checkUninitializedVariablesInAtomInternalDataDeclaration" });
        addAnnotation(compoundTypeEClass, source, new String[] { "constraints",
                "exportedPortsListsSynchronized exportedDataListsSynchronized checkForCyclesInPrioritiesInCompound\n" });
        addAnnotation(connectorTypeEClass, source, new String[] { "constraints",
                "interactionDefinedIfExportPortWithData noDuplicatedInteractionAction checkDownWhenNoDataInConnectorPort missingInteractionIfExportPortWithData checkUninitializedVariablesInConnectorDataDeclaration" });
    }

} //TypesPackageImpl
