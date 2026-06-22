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

package bip2.ujf.verimag.bip.actionlang.impl;

import bip2.Bip2Package;
import bip2.impl.Bip2PackageImpl;
import bip2.ujf.UjfPackage;
import bip2.ujf.impl.UjfPackageImpl;
import bip2.ujf.verimag.VerimagPackage;
import bip2.ujf.verimag.bip.BipPackage;
import bip2.ujf.verimag.bip.actionlang.ActionlangFactory;
import bip2.ujf.verimag.bip.actionlang.ActionlangPackage;
import bip2.ujf.verimag.bip.actionlang.AssignmentExpression;
import bip2.ujf.verimag.bip.actionlang.BinaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.BinaryOperators;
import bip2.ujf.verimag.bip.actionlang.DirectBooleanExpression;
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.DirectFloatExpression;
import bip2.ujf.verimag.bip.actionlang.DirectIntegerExpression;
import bip2.ujf.verimag.bip.actionlang.DirectStringExpression;
import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.FunctionCallExpression;
import bip2.ujf.verimag.bip.actionlang.IfThenElseExpression;
import bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.UnaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.UnaryOperators;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;

import bip2.ujf.verimag.bip.actionlang.ValuedReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.util.ActionlangValidator;

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
import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EEnum;
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
public class ActionlangPackageImpl extends EPackageImpl
        implements ActionlangPackage {
    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass binaryOpExpressionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass unaryOpExpressionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass valuedExpressionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass subDataDeclarationReferenceExpressionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass directDataDeclarationReferenceExpressionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass assignmentExpressionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass functionCallExpressionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass expressionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass valuedReferenceExpressionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass directBooleanExpressionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass ifThenElseExpressionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass directIntegerExpressionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass directFloatExpressionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass directStringExpressionEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EEnum binaryOperatorsEEnum = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EEnum unaryOperatorsEEnum = null;

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
     * @see bip2.ujf.verimag.bip.actionlang.ActionlangPackage#eNS_URI
     * @see #init()
     * @generated
     */
    private ActionlangPackageImpl() {
        super(eNS_URI, ActionlangFactory.eINSTANCE);
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
     * <p>This method is used to initialize {@link ActionlangPackage#eINSTANCE} when that field is accessed.
     * Clients should not invoke it directly. Instead, they should simply access that field to obtain the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #eNS_URI
     * @see #createPackageContents()
     * @see #initializePackageContents()
     * @generated
     */
    public static ActionlangPackage init() {
        if (isInited)
            return (ActionlangPackage) EPackage.Registry.INSTANCE
                    .getEPackage(ActionlangPackage.eNS_URI);

        // Obtain or create and register package
        ActionlangPackageImpl theActionlangPackage = (ActionlangPackageImpl) (EPackage.Registry.INSTANCE
                .get(eNS_URI) instanceof ActionlangPackageImpl
                        ? EPackage.Registry.INSTANCE.get(eNS_URI)
                        : new ActionlangPackageImpl());

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
        theActionlangPackage.createPackageContents();
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
        theInstancePackage.createPackageContents();
        theAnnotationPackage.createPackageContents();
        theInvariantPackage.createPackageContents();

        // Initialize created meta-data
        theActionlangPackage.initializePackageContents();
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
        theInstancePackage.initializePackageContents();
        theAnnotationPackage.initializePackageContents();
        theInvariantPackage.initializePackageContents();

        // Register package validator
        EValidator.Registry.INSTANCE.put(theActionlangPackage,
                new EValidator.Descriptor() {
                    public EValidator getEValidator() {
                        return ActionlangValidator.INSTANCE;
                    }
                });

        // Mark meta-data to indicate it can't be changed
        theActionlangPackage.freeze();

        // Update the registry and return the package
        EPackage.Registry.INSTANCE.put(ActionlangPackage.eNS_URI,
                theActionlangPackage);
        return theActionlangPackage;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getBinaryOpExpression() {
        return binaryOpExpressionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getBinaryOpExpression_Operator() {
        return (EAttribute) binaryOpExpressionEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getBinaryOpExpression_Left() {
        return (EReference) binaryOpExpressionEClass.getEStructuralFeatures()
                .get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getBinaryOpExpression_Right() {
        return (EReference) binaryOpExpressionEClass.getEStructuralFeatures()
                .get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getUnaryOpExpression() {
        return unaryOpExpressionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getUnaryOpExpression_Operator() {
        return (EAttribute) unaryOpExpressionEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getUnaryOpExpression_Operand() {
        return (EReference) unaryOpExpressionEClass.getEStructuralFeatures()
                .get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getValuedExpression() {
        return valuedExpressionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getSubDataDeclarationReferenceExpression() {
        return subDataDeclarationReferenceExpressionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getSubDataDeclarationReferenceExpression_SubDataDeclarationRef() {
        return (EReference) subDataDeclarationReferenceExpressionEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getDirectDataDeclarationReferenceExpression() {
        return directDataDeclarationReferenceExpressionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getDirectDataDeclarationReferenceExpression_DataDeclaration() {
        return (EReference) directDataDeclarationReferenceExpressionEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getAssignmentExpression() {
        return assignmentExpressionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getAssignmentExpression_Lhs() {
        return (EReference) assignmentExpressionEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getAssignmentExpression_Rhs() {
        return (EReference) assignmentExpressionEClass.getEStructuralFeatures()
                .get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getFunctionCallExpression() {
        return functionCallExpressionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getFunctionCallExpression_Parameters() {
        return (EReference) functionCallExpressionEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getFunctionCallExpression_FunctionName() {
        return (EAttribute) functionCallExpressionEClass
                .getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getExpression() {
        return expressionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getValuedReferenceExpression() {
        return valuedReferenceExpressionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getValuedReferenceExpression_ExpressionReference() {
        return (EReference) valuedReferenceExpressionEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getDirectBooleanExpression() {
        return directBooleanExpressionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getDirectBooleanExpression_Value() {
        return (EAttribute) directBooleanExpressionEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getIfThenElseExpression() {
        return ifThenElseExpressionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getIfThenElseExpression_Condition() {
        return (EReference) ifThenElseExpressionEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getIfThenElseExpression_Then() {
        return (EReference) ifThenElseExpressionEClass.getEStructuralFeatures()
                .get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getIfThenElseExpression_Else() {
        return (EReference) ifThenElseExpressionEClass.getEStructuralFeatures()
                .get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getDirectIntegerExpression() {
        return directIntegerExpressionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getDirectIntegerExpression_Value() {
        return (EAttribute) directIntegerExpressionEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getDirectFloatExpression() {
        return directFloatExpressionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getDirectFloatExpression_Value() {
        return (EAttribute) directFloatExpressionEClass.getEStructuralFeatures()
                .get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getDirectStringExpression() {
        return directStringExpressionEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getDirectStringExpression_Value() {
        return (EAttribute) directStringExpressionEClass
                .getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EEnum getBinaryOperators() {
        return binaryOperatorsEEnum;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EEnum getUnaryOperators() {
        return unaryOperatorsEEnum;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ActionlangFactory getActionlangFactory() {
        return (ActionlangFactory) getEFactoryInstance();
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
        binaryOpExpressionEClass = createEClass(BINARY_OP_EXPRESSION);
        createEAttribute(binaryOpExpressionEClass,
                BINARY_OP_EXPRESSION__OPERATOR);
        createEReference(binaryOpExpressionEClass, BINARY_OP_EXPRESSION__LEFT);
        createEReference(binaryOpExpressionEClass, BINARY_OP_EXPRESSION__RIGHT);

        unaryOpExpressionEClass = createEClass(UNARY_OP_EXPRESSION);
        createEAttribute(unaryOpExpressionEClass,
                UNARY_OP_EXPRESSION__OPERATOR);
        createEReference(unaryOpExpressionEClass, UNARY_OP_EXPRESSION__OPERAND);

        valuedExpressionEClass = createEClass(VALUED_EXPRESSION);

        subDataDeclarationReferenceExpressionEClass = createEClass(
                SUB_DATA_DECLARATION_REFERENCE_EXPRESSION);
        createEReference(subDataDeclarationReferenceExpressionEClass,
                SUB_DATA_DECLARATION_REFERENCE_EXPRESSION__SUB_DATA_DECLARATION_REF);

        directDataDeclarationReferenceExpressionEClass = createEClass(
                DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION);
        createEReference(directDataDeclarationReferenceExpressionEClass,
                DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION__DATA_DECLARATION);

        assignmentExpressionEClass = createEClass(ASSIGNMENT_EXPRESSION);
        createEReference(assignmentExpressionEClass,
                ASSIGNMENT_EXPRESSION__LHS);
        createEReference(assignmentExpressionEClass,
                ASSIGNMENT_EXPRESSION__RHS);

        functionCallExpressionEClass = createEClass(FUNCTION_CALL_EXPRESSION);
        createEReference(functionCallExpressionEClass,
                FUNCTION_CALL_EXPRESSION__PARAMETERS);
        createEAttribute(functionCallExpressionEClass,
                FUNCTION_CALL_EXPRESSION__FUNCTION_NAME);

        expressionEClass = createEClass(EXPRESSION);

        valuedReferenceExpressionEClass = createEClass(
                VALUED_REFERENCE_EXPRESSION);
        createEReference(valuedReferenceExpressionEClass,
                VALUED_REFERENCE_EXPRESSION__EXPRESSION_REFERENCE);

        directBooleanExpressionEClass = createEClass(DIRECT_BOOLEAN_EXPRESSION);
        createEAttribute(directBooleanExpressionEClass,
                DIRECT_BOOLEAN_EXPRESSION__VALUE);

        ifThenElseExpressionEClass = createEClass(IF_THEN_ELSE_EXPRESSION);
        createEReference(ifThenElseExpressionEClass,
                IF_THEN_ELSE_EXPRESSION__CONDITION);
        createEReference(ifThenElseExpressionEClass,
                IF_THEN_ELSE_EXPRESSION__THEN);
        createEReference(ifThenElseExpressionEClass,
                IF_THEN_ELSE_EXPRESSION__ELSE);

        directIntegerExpressionEClass = createEClass(DIRECT_INTEGER_EXPRESSION);
        createEAttribute(directIntegerExpressionEClass,
                DIRECT_INTEGER_EXPRESSION__VALUE);

        directFloatExpressionEClass = createEClass(DIRECT_FLOAT_EXPRESSION);
        createEAttribute(directFloatExpressionEClass,
                DIRECT_FLOAT_EXPRESSION__VALUE);

        directStringExpressionEClass = createEClass(DIRECT_STRING_EXPRESSION);
        createEAttribute(directStringExpressionEClass,
                DIRECT_STRING_EXPRESSION__VALUE);

        // Create enums
        binaryOperatorsEEnum = createEEnum(BINARY_OPERATORS);
        unaryOperatorsEEnum = createEEnum(UNARY_OPERATORS);
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
        PackagingPackage thePackagingPackage = (PackagingPackage) EPackage.Registry.INSTANCE
                .getEPackage(PackagingPackage.eNS_URI);
        TypesPackage theTypesPackage = (TypesPackage) EPackage.Registry.INSTANCE
                .getEPackage(TypesPackage.eNS_URI);
        DataPackage theDataPackage = (DataPackage) EPackage.Registry.INSTANCE
                .getEPackage(DataPackage.eNS_URI);

        // Create type parameters

        // Set bounds for type parameters

        // Add supertypes to classes
        binaryOpExpressionEClass.getESuperTypes()
                .add(this.getValuedExpression());
        unaryOpExpressionEClass.getESuperTypes()
                .add(this.getValuedExpression());
        valuedExpressionEClass.getESuperTypes().add(this.getExpression());
        subDataDeclarationReferenceExpressionEClass.getESuperTypes()
                .add(this.getValuedExpression());
        directDataDeclarationReferenceExpressionEClass.getESuperTypes()
                .add(this.getValuedExpression());
        assignmentExpressionEClass.getESuperTypes().add(this.getExpression());
        functionCallExpressionEClass.getESuperTypes()
                .add(this.getValuedExpression());
        valuedReferenceExpressionEClass.getESuperTypes()
                .add(this.getValuedExpression());
        directBooleanExpressionEClass.getESuperTypes()
                .add(this.getValuedExpression());
        ifThenElseExpressionEClass.getESuperTypes().add(this.getExpression());
        directIntegerExpressionEClass.getESuperTypes()
                .add(this.getValuedExpression());
        directFloatExpressionEClass.getESuperTypes()
                .add(this.getValuedExpression());
        directStringExpressionEClass.getESuperTypes()
                .add(this.getValuedExpression());

        // Initialize classes and features; add operations and parameters
        initEClass(binaryOpExpressionEClass, BinaryOpExpression.class,
                "BinaryOpExpression", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getBinaryOpExpression_Operator(),
                this.getBinaryOperators(), "operator", null, 1, 1,
                BinaryOpExpression.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getBinaryOpExpression_Left(), this.getValuedExpression(),
                null, "left", null, 1, 1, BinaryOpExpression.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getBinaryOpExpression_Right(),
                this.getValuedExpression(), null, "right", null, 1, 1,
                BinaryOpExpression.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        addEOperation(binaryOpExpressionEClass,
                thePackagingPackage.getBinaryOpPrototype(), "getPrototypes", 0,
                -1, IS_UNIQUE, IS_ORDERED);

        initEClass(unaryOpExpressionEClass, UnaryOpExpression.class,
                "UnaryOpExpression", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getUnaryOpExpression_Operator(),
                this.getUnaryOperators(), "operator", null, 1, 1,
                UnaryOpExpression.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getUnaryOpExpression_Operand(),
                this.getValuedExpression(), null, "operand", null, 1, 1,
                UnaryOpExpression.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        addEOperation(unaryOpExpressionEClass,
                thePackagingPackage.getUnaryOpPrototype(), "getPrototypes", 0,
                -1, IS_UNIQUE, IS_ORDERED);

        initEClass(valuedExpressionEClass, ValuedExpression.class,
                "ValuedExpression", IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);

        addEOperation(valuedExpressionEClass, theTypesPackage.getType(),
                "getType", 0, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(valuedExpressionEClass, theTypesPackage.getType(),
                "getExpectedType", 0, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(valuedExpressionEClass, ecorePackage.getEBoolean(),
                "isConst", 1, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(valuedExpressionEClass, ecorePackage.getEBoolean(),
                "expectedIsConst", 1, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(valuedExpressionEClass, ecorePackage.getEBoolean(),
                "isInConstantContext", 1, 1, IS_UNIQUE, IS_ORDERED);

        addEOperation(valuedExpressionEClass, ecorePackage.getEBoolean(),
                "hasSideEffect", 1, 1, IS_UNIQUE, IS_ORDERED);

        initEClass(subDataDeclarationReferenceExpressionEClass,
                SubDataDeclarationReferenceExpression.class,
                "SubDataDeclarationReferenceExpression", !IS_ABSTRACT,
                !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(
                getSubDataDeclarationReferenceExpression_SubDataDeclarationRef(),
                theDataPackage.getSubDataDeclarationReference(), null,
                "subDataDeclarationRef", null, 1, 1,
                SubDataDeclarationReferenceExpression.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(directDataDeclarationReferenceExpressionEClass,
                DirectDataDeclarationReferenceExpression.class,
                "DirectDataDeclarationReferenceExpression", !IS_ABSTRACT,
                !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(
                getDirectDataDeclarationReferenceExpression_DataDeclaration(),
                theDataPackage.getDataDeclaration(), null, "dataDeclaration",
                null, 1, 1, DirectDataDeclarationReferenceExpression.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE,
                IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        initEClass(assignmentExpressionEClass, AssignmentExpression.class,
                "AssignmentExpression", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEReference(getAssignmentExpression_Lhs(),
                this.getValuedExpression(), null, "lhs", null, 0, 1,
                AssignmentExpression.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getAssignmentExpression_Rhs(),
                this.getValuedExpression(), null, "rhs", null, 1, 1,
                AssignmentExpression.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(functionCallExpressionEClass, FunctionCallExpression.class,
                "FunctionCallExpression", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEReference(getFunctionCallExpression_Parameters(),
                this.getValuedExpression(), null, "parameters", null, 0, -1,
                FunctionCallExpression.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getFunctionCallExpression_FunctionName(),
                ecorePackage.getEString(), "functionName", null, 1, 1,
                FunctionCallExpression.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        addEOperation(functionCallExpressionEClass,
                thePackagingPackage.getFunctionCallPrototype(), "getPrototypes",
                0, -1, IS_UNIQUE, IS_ORDERED);

        initEClass(expressionEClass, Expression.class, "Expression",
                IS_ABSTRACT, IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);

        addEOperation(expressionEClass, theDataPackage.getDataDeclaration(),
                "getReadVariables", 0, -1, IS_UNIQUE, IS_ORDERED);

        addEOperation(expressionEClass, theDataPackage.getDataDeclaration(),
                "getMayReadVariables", 0, -1, IS_UNIQUE, IS_ORDERED);

        addEOperation(expressionEClass, theDataPackage.getDataDeclaration(),
                "getWriteVariables", 0, -1, IS_UNIQUE, IS_ORDERED);

        addEOperation(expressionEClass, theDataPackage.getDataDeclaration(),
                "getMayWriteVariables", 0, -1, IS_UNIQUE, IS_ORDERED);

        EOperation op = addEOperation(expressionEClass, this.getExpression(),
                "getMayReadUninitializedVariables", 0, -1, IS_UNIQUE,
                IS_ORDERED);
        addEParameter(op, theDataPackage.getDataDeclaration(), "uninitialized",
                0, -1, IS_UNIQUE, !IS_ORDERED);

        initEClass(valuedReferenceExpressionEClass,
                ValuedReferenceExpression.class, "ValuedReferenceExpression",
                !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getValuedReferenceExpression_ExpressionReference(),
                this.getValuedExpression(), null, "expressionReference", null,
                1, 1, ValuedReferenceExpression.class, !IS_TRANSIENT,
                !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(directBooleanExpressionEClass, DirectBooleanExpression.class,
                "DirectBooleanExpression", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getDirectBooleanExpression_Value(),
                ecorePackage.getEBoolean(), "value", null, 0, 1,
                DirectBooleanExpression.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        initEClass(ifThenElseExpressionEClass, IfThenElseExpression.class,
                "IfThenElseExpression", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEReference(getIfThenElseExpression_Condition(),
                this.getValuedExpression(), null, "condition", null, 1, 1,
                IfThenElseExpression.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES,
                !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getIfThenElseExpression_Then(), this.getExpression(),
                null, "then", null, 1, -1, IfThenElseExpression.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);
        initEReference(getIfThenElseExpression_Else(), this.getExpression(),
                null, "else", null, 0, -1, IfThenElseExpression.class,
                !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE,
                !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        initEClass(directIntegerExpressionEClass, DirectIntegerExpression.class,
                "DirectIntegerExpression", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getDirectIntegerExpression_Value(),
                ecorePackage.getEInt(), "value", null, 1, 1,
                DirectIntegerExpression.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        initEClass(directFloatExpressionEClass, DirectFloatExpression.class,
                "DirectFloatExpression", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getDirectFloatExpression_Value(),
                ecorePackage.getEFloat(), "value", null, 1, 1,
                DirectFloatExpression.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        initEClass(directStringExpressionEClass, DirectStringExpression.class,
                "DirectStringExpression", !IS_ABSTRACT, !IS_INTERFACE,
                IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getDirectStringExpression_Value(),
                ecorePackage.getEString(), "value", null, 1, 1,
                DirectStringExpression.class, !IS_TRANSIENT, !IS_VOLATILE,
                IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, IS_UNIQUE, !IS_DERIVED,
                IS_ORDERED);

        // Initialize enums and add enum literals
        initEEnum(binaryOperatorsEEnum, BinaryOperators.class,
                "BinaryOperators");
        addEEnumLiteral(binaryOperatorsEEnum, BinaryOperators.ADDITION);
        addEEnumLiteral(binaryOperatorsEEnum, BinaryOperators.SUBTRACTION);
        addEEnumLiteral(binaryOperatorsEEnum, BinaryOperators.MULTIPLICATION);
        addEEnumLiteral(binaryOperatorsEEnum, BinaryOperators.BWISE_AND);
        addEEnumLiteral(binaryOperatorsEEnum, BinaryOperators.BWISE_XOR);
        addEEnumLiteral(binaryOperatorsEEnum, BinaryOperators.BWISE_OR);
        addEEnumLiteral(binaryOperatorsEEnum, BinaryOperators.LOGICAL_AND);
        addEEnumLiteral(binaryOperatorsEEnum, BinaryOperators.LOGICAL_OR);
        addEEnumLiteral(binaryOperatorsEEnum, BinaryOperators.EQUAL);
        addEEnumLiteral(binaryOperatorsEEnum, BinaryOperators.NOT_EQUAL);
        addEEnumLiteral(binaryOperatorsEEnum, BinaryOperators.LESS_THAN);
        addEEnumLiteral(binaryOperatorsEEnum, BinaryOperators.GREATER_THAN);
        addEEnumLiteral(binaryOperatorsEEnum,
                BinaryOperators.LESS_THAN_OR_EQUAL);
        addEEnumLiteral(binaryOperatorsEEnum,
                BinaryOperators.GREATER_THAN_OR_EQUAL);
        addEEnumLiteral(binaryOperatorsEEnum, BinaryOperators.DIVISION);
        addEEnumLiteral(binaryOperatorsEEnum, BinaryOperators.MODULO);

        initEEnum(unaryOperatorsEEnum, UnaryOperators.class, "UnaryOperators");
        addEEnumLiteral(unaryOperatorsEEnum, UnaryOperators.PLUS);
        addEEnumLiteral(unaryOperatorsEEnum, UnaryOperators.MINUS);
        addEEnumLiteral(unaryOperatorsEEnum, UnaryOperators.LOGICAL_NOT);
        addEEnumLiteral(unaryOperatorsEEnum, UnaryOperators.BWISE_NOT);

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
        addAnnotation(binaryOpExpressionEClass, source,
                new String[] { "constraints", "hasOneMatchingPrototype" });
        addAnnotation(unaryOpExpressionEClass, source,
                new String[] { "constraints", "hasOneMatchingPrototype" });
        addAnnotation(valuedExpressionEClass, source, new String[] {
                "constraints",
                "hasCorrectType hasCorrectConst noSideEffectInGuards" });
        addAnnotation(subDataDeclarationReferenceExpressionEClass, source,
                new String[] { "constraints",
                        "dataIsExportedInComponent dataRefInConnectorActionToInvolvedPort" });
        addAnnotation(assignmentExpressionEClass, source,
                new String[] { "constraints",
                        "rhsIsADataDeclarationReference hasCorrectConst" });
        addAnnotation(functionCallExpressionEClass, source,
                new String[] { "constraints",
                        "hasOneMatchingPrototype hasValueInValuedContext" });
    }

} //ActionlangPackageImpl
