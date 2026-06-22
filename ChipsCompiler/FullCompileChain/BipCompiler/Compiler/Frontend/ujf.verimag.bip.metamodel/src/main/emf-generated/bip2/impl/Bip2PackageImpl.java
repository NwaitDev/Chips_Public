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

package bip2.impl;

import bip2.Bip2Factory;
import bip2.Bip2Package;
import bip2.PlaceHolder;

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

import bip2.ujf.verimag.bip.types.TypesPackage;

import bip2.ujf.verimag.bip.types.impl.TypesPackageImpl;

import bip2.ujf.verimag.impl.VerimagPackageImpl;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.impl.EPackageImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Package</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class Bip2PackageImpl extends EPackageImpl implements Bip2Package {
    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass placeHolderEClass = null;

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
     * @see bip2.Bip2Package#eNS_URI
     * @see #init()
     * @generated
     */
    private Bip2PackageImpl() {
        super(eNS_URI, Bip2Factory.eINSTANCE);
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
     * <p>This method is used to initialize {@link Bip2Package#eINSTANCE} when that field is accessed.
     * Clients should not invoke it directly. Instead, they should simply access that field to obtain the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #eNS_URI
     * @see #createPackageContents()
     * @see #initializePackageContents()
     * @generated
     */
    public static Bip2Package init() {
        if (isInited)
            return (Bip2Package) EPackage.Registry.INSTANCE
                    .getEPackage(Bip2Package.eNS_URI);

        // Obtain or create and register package
        Bip2PackageImpl theBip2Package = (Bip2PackageImpl) (EPackage.Registry.INSTANCE
                .get(eNS_URI) instanceof Bip2PackageImpl
                        ? EPackage.Registry.INSTANCE.get(eNS_URI)
                        : new Bip2PackageImpl());

        isInited = true;

        // Obtain or create and register interdependencies
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
        theInstancePackage.createPackageContents();
        theAnnotationPackage.createPackageContents();
        theInvariantPackage.createPackageContents();

        // Initialize created meta-data
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
        theInstancePackage.initializePackageContents();
        theAnnotationPackage.initializePackageContents();
        theInvariantPackage.initializePackageContents();

        // Mark meta-data to indicate it can't be changed
        theBip2Package.freeze();

        // Update the registry and return the package
        EPackage.Registry.INSTANCE.put(Bip2Package.eNS_URI, theBip2Package);
        return theBip2Package;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getPlaceHolder() {
        return placeHolderEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Bip2Factory getBip2Factory() {
        return (Bip2Factory) getEFactoryInstance();
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
        placeHolderEClass = createEClass(PLACE_HOLDER);
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
        UjfPackage theUjfPackage = (UjfPackage) EPackage.Registry.INSTANCE
                .getEPackage(UjfPackage.eNS_URI);

        // Add subpackages
        getESubpackages().add(theUjfPackage);

        // Create type parameters

        // Set bounds for type parameters

        // Add supertypes to classes

        // Initialize classes and features; add operations and parameters
        initEClass(placeHolderEClass, PlaceHolder.class, "PlaceHolder",
                IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);

        // Create resource
        createResource(eNS_URI);
    }

} //Bip2PackageImpl
