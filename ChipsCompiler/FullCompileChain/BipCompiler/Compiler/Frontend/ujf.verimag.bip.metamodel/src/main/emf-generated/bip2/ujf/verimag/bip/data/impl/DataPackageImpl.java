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

package bip2.ujf.verimag.bip.data.impl;

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

import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter;
import bip2.ujf.verimag.bip.data.DataFactory;
import bip2.ujf.verimag.bip.data.DataPackage;
import bip2.ujf.verimag.bip.data.DataParameter;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.data.ExplicitDataDeclaration;
import bip2.ujf.verimag.bip.data.SubDataDeclarationReference;

import bip2.ujf.verimag.bip.data.util.DataValidator;

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
import bip2.ujf.verimag.bip.types.TypesPackage;

import bip2.ujf.verimag.bip.types.impl.TypesPackageImpl;

import bip2.ujf.verimag.impl.VerimagPackageImpl;
import org.eclipse.emf.ecore.EAttribute;
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
public class DataPackageImpl extends EPackageImpl implements DataPackage {
    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass dataTypeEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass dataDeclarationEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass explicitDataDeclarationEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass subDataDeclarationReferenceEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass dataParameterEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass dataDeclarationReferenceDataParameterEClass = null;

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
     * @see bip2.ujf.verimag.bip.data.DataPackage#eNS_URI
     * @see #init()
     * @generated
     */
    private DataPackageImpl() {
        super(eNS_URI, DataFactory.eINSTANCE);
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
     * <p>This method is used to initialize {@link DataPackage#eINSTANCE} when that field is accessed.
     * Clients should not invoke it directly. Instead, they should simply access that field to obtain the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #eNS_URI
     * @see #createPackageContents()
     * @see #initializePackageContents()
     * @generated
     */
    public static DataPackage init() {
        if (isInited)
            return (DataPackage) EPackage.Registry.INSTANCE
                    .getEPackage(DataPackage.eNS_URI);

        // Obtain or create and register package
        DataPackageImpl theDataPackage = (DataPackageImpl) (EPackage.Registry.INSTANCE
                .get(eNS_URI) instanceof DataPackageImpl
                        ? EPackage.Registry.INSTANCE.get(eNS_URI)
                        : new DataPackageImpl());

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
        theDataPackage.createPackageContents();
        theBip2Package.createPackageContents();
        theUjfPackage.createPackageContents();
        theVerimagPackage.createPackageContents();
        theBipPackage.createPackageContents();
        theTypesPackage.createPackageContents();
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
        theDataPackage.initializePackageContents();
        theBip2Package.initializePackageContents();
        theUjfPackage.initializePackageContents();
        theVerimagPackage.initializePackageContents();
        theBipPackage.initializePackageContents();
        theTypesPackage.initializePackageContents();
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
        EValidator.Registry.INSTANCE.put(theDataPackage,
                new EValidator.Descriptor() {
                    public EValidator getEValidator() {
                        return DataValidator.INSTANCE;
                    }
                });

        // Mark meta-data to indicate it can't be changed
        theDataPackage.freeze();

        // Update the registry and return the package
        EPackage.Registry.INSTANCE.put(DataPackage.eNS_URI, theDataPackage);
        return theDataPackage;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getDataType() {
        return dataTypeEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getDataType_BackendName() {
        return (EAttribute) dataTypeEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getDataDeclaration() {
        return dataDeclarationEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getDataDeclaration_DataType() {
        return (EReference) dataDeclarationEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getDataDeclaration_Name() {
        return (EAttribute) dataDeclarationEClass.getEStructuralFeatures()
                .get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getDataDeclaration_Value() {
        return (EReference) dataDeclarationEClass.getEStructuralFeatures()
                .get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getDataDeclaration_Const() {
        return (EAttribute) dataDeclarationEClass.getEStructuralFeatures()
                .get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getExplicitDataDeclaration() {
        return explicitDataDeclarationEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getSubDataDeclarationReference() {
        return subDataDeclarationReferenceEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getSubDataDeclarationReference_ForwardDataDeclaration() {
        return (EReference) subDataDeclarationReferenceEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getSubDataDeclarationReference_ComponentDeclaration() {
        return (EReference) subDataDeclarationReferenceEClass
                .getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getSubDataDeclarationReference_PortDeclaration() {
        return (EReference) subDataDeclarationReferenceEClass
                .getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getDataParameter() {
        return dataParameterEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getDataParameter_ParameterDeclaration() {
        return (EReference) dataParameterEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getDataParameter_Type() {
        return (EReference) dataParameterEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getDataDeclarationReferenceDataParameter() {
        return dataDeclarationReferenceDataParameterEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getDataDeclarationReferenceDataParameter_DataDeclarationReference() {
        return (EReference) dataDeclarationReferenceDataParameterEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataFactory getDataFactory() {
        return (DataFactory) getEFactoryInstance();
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
        dataTypeEClass = createEClass(DATA_TYPE);
        createEAttribute(dataTypeEClass, DATA_TYPE__BACKEND_NAME);

        dataDeclarationEClass = createEClass(DATA_DECLARATION);
        createEReference(dataDeclarationEClass, DATA_DECLARATION__DATA_TYPE);
        createEAttribute(dataDeclarationEClass, DATA_DECLARATION__NAME);
        createEReference(dataDeclarationEClass, DATA_DECLARATION__VALUE);
        createEAttribute(dataDeclarationEClass, DATA_DECLARATION__CONST);

        explicitDataDeclarationEClass = createEClass(EXPLICIT_DATA_DECLARATION);

        subDataDeclarationReferenceEClass = createEClass(
                SUB_DATA_DECLARATION_REFERENCE);
        createEReference(subDataDeclarationReferenceEClass,
                SUB_DATA_DECLARATION_REFERENCE__FORWARD_DATA_DECLARATION);
        createEReference(subDataDeclarationReferenceEClass,
                SUB_DATA_DECLARATION_REFERENCE__COMPONENT_DECLARATION);
        createEReference(subDataDeclarationReferenceEClass,
                SUB_DATA_DECLARATION_REFERENCE__PORT_DECLARATION);

        dataParameterEClass = createEClass(DATA_PARAMETER);
        createEReference(dataParameterEClass,
                DATA_PARAMETER__PARAMETER_DECLARATION);
        createEReference(dataParameterEClass, DATA_PARAMETER__TYPE);

        dataDeclarationReferenceDataParameterEClass = createEClass(
                DATA_DECLARATION_REFERENCE_DATA_PARAMETER);
        createEReference(dataDeclarationReferenceDataParameterEClass,
                DATA_DECLARATION_REFERENCE_DATA_PARAMETER__DATA_DECLARATION_REFERENCE);
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
        TypesPackage theTypesPackage = (TypesPackage) EPackage.Registry.INSTANCE
                .getEPackage(TypesPackage.eNS_URI);
        AnnotationPackage theAnnotationPackage = (AnnotationPackage) EPackage.Registry.INSTANCE
                .getEPackage(AnnotationPackage.eNS_URI);
        ActionlangPackage theActionlangPackage = (ActionlangPackage) EPackage.Registry.INSTANCE
                .getEPackage(ActionlangPackage.eNS_URI);
        ComponentPackage theComponentPackage = (ComponentPackage) EPackage.Registry.INSTANCE
                .getEPackage(ComponentPackage.eNS_URI);
        PortPackage thePortPackage = (PortPackage) EPackage.Registry.INSTANCE
                .getEPackage(PortPackage.eNS_URI);

        // Create type parameters

        // Set bounds for type parameters

        // Add supertypes to classes
        dataTypeEClass.getESuperTypes().add(theTypesPackage.getType());
        dataDeclarationEClass.getESuperTypes()
                .add(theAnnotationPackage.getAnnotatedElement());
        explicitDataDeclarationEClass.getESuperTypes()
                .add(this.getDataDeclaration());
        dataDeclarationReferenceDataParameterEClass.getESuperTypes()
                .add(this.getDataParameter());

        // Initialize classes and features; add operations and parameters
        initEClass(dataTypeEClass, DataType.class, "DataType", !IS_ABSTRACT,
                !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getDataType_BackendName(), ecorePackage.getEString(),
                "backendName", null, 0, 1, DataType.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE,
                !IS_DERIVED, IS_ORDERED);

        initEClass(dataDeclarationEClass, DataDeclaration.class,
                "DataDeclaration", IS_ABSTRACT, IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEReference(getDataDeclaration_DataType(), this.getDataType(), null,
                "dataType", null, 1, 1, DataDeclaration.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getDataDeclaration_Name(), ecorePackage.getEString(),
                "name", null, 1, 1, DataDeclaration.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, IS_ID, IS_UNIQUE,
                !IS_DERIVED, IS_ORDERED);
        initEReference(getDataDeclaration_Value(),
                theActionlangPackage.getValuedExpression(), null, "value", null,
                0, 1, DataDeclaration.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getDataDeclaration_Const(), ecorePackage.getEBoolean(),
                "const", null, 1, 1, DataDeclaration.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE,
                !IS_DERIVED, IS_ORDERED);

        initEClass(explicitDataDeclarationEClass, ExplicitDataDeclaration.class,
                "ExplicitDataDeclaration", IS_ABSTRACT, IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);

        initEClass(subDataDeclarationReferenceEClass,
                SubDataDeclarationReference.class,
                "SubDataDeclarationReference", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEReference(getSubDataDeclarationReference_ForwardDataDeclaration(),
                this.getDataDeclaration(), null, "forwardDataDeclaration", null,
                1, 1, SubDataDeclarationReference.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getSubDataDeclarationReference_ComponentDeclaration(),
                theComponentPackage.getComponentDeclaration(), null,
                "componentDeclaration", null, 0, 1,
                SubDataDeclarationReference.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getSubDataDeclarationReference_PortDeclaration(),
                thePortPackage.getPortDeclaration(), null, "portDeclaration",
                null, 0, 1, SubDataDeclarationReference.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(dataParameterEClass, DataParameter.class, "DataParameter",
                IS_ABSTRACT, IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getDataParameter_ParameterDeclaration(),
                this.getDataDeclaration(), null, "parameterDeclaration", null,
                1, 1, DataParameter.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getDataParameter_Type(), this.getDataType(), null,
                "type", null, 1, 1, DataParameter.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(dataDeclarationReferenceDataParameterEClass,
                DataDeclarationReferenceDataParameter.class,
                "DataDeclarationReferenceDataParameter", !IS_ABSTRACT,
                !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(
                getDataDeclarationReferenceDataParameter_DataDeclarationReference(),
                this.getDataDeclaration(), null, "dataDeclarationReference",
                null, 1, 1, DataDeclarationReferenceDataParameter.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE,
                IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
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
        addAnnotation(explicitDataDeclarationEClass, source,
                new String[] { "constraints", "hasInitializationIfConst" });
        addAnnotation(subDataDeclarationReferenceEClass, source,
                new String[] { "constraints", "hasOneDeclaration" });
        addAnnotation(dataDeclarationReferenceDataParameterEClass, source,
                new String[] { "constraints",
                        "hasCorrectType hasCorrectConst" });
    }

} //DataPackageImpl
