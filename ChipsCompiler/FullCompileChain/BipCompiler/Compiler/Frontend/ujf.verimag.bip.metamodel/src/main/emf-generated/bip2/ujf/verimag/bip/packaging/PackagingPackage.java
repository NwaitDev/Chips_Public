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

package bip2.ujf.verimag.bip.packaging;

import bip2.ujf.verimag.bip.annotation.AnnotationPackage;
import bip2.ujf.verimag.bip.data.DataPackage;
import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EReference;

/**
 * <!-- begin-user-doc -->
 * The <b>Package</b> for the model.
 * It contains accessors for the meta objects to represent
 * <ul>
 *   <li>each class,</li>
 *   <li>each feature of each class,</li>
 *   <li>each enum,</li>
 *   <li>and each data type</li>
 * </ul>
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.packaging.PackagingFactory
 * @model kind="package"
 * @generated
 */
public interface PackagingPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "packaging";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/package/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.package";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    PackagingPackage eINSTANCE = bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.packaging.impl.BipPackageImpl <em>Bip Package</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.packaging.impl.BipPackageImpl
     * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getBipPackage()
     * @generated
     */
    int BIP_PACKAGE = 0;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_PACKAGE__BIP_ANNOTATIONS = AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_PACKAGE__NAME = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>Atom Types</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_PACKAGE__ATOM_TYPES = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 1;

    /**
     * The feature id for the '<em><b>Compound Types</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_PACKAGE__COMPOUND_TYPES = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 2;

    /**
     * The feature id for the '<em><b>Connector Types</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_PACKAGE__CONNECTOR_TYPES = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 3;

    /**
     * The feature id for the '<em><b>Port Types</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_PACKAGE__PORT_TYPES = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 4;

    /**
     * The feature id for the '<em><b>Data Types</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_PACKAGE__DATA_TYPES = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 5;

    /**
     * The feature id for the '<em><b>Used packages</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_PACKAGE__USED_PACKAGES = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 6;

    /**
     * The feature id for the '<em><b>Const Data</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_PACKAGE__CONST_DATA = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 7;

    /**
     * The feature id for the '<em><b>Prototypes</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_PACKAGE__PROTOTYPES = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 8;

    /**
     * The number of structural features of the '<em>Bip Package</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_PACKAGE_FEATURE_COUNT = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 9;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.packaging.impl.BipPackageSetImpl <em>Bip Package Set</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.packaging.impl.BipPackageSetImpl
     * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getBipPackageSet()
     * @generated
     */
    int BIP_PACKAGE_SET = 1;

    /**
     * The feature id for the '<em><b>Packages</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_PACKAGE_SET__PACKAGES = 0;

    /**
     * The number of structural features of the '<em>Bip Package Set</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_PACKAGE_SET_FEATURE_COUNT = 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.packaging.impl.ConstDataDeclarationImpl <em>Const Data Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.packaging.impl.ConstDataDeclarationImpl
     * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getConstDataDeclaration()
     * @generated
     */
    int CONST_DATA_DECLARATION = 2;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONST_DATA_DECLARATION__BIP_ANNOTATIONS = DataPackage.EXPLICIT_DATA_DECLARATION__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Data Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONST_DATA_DECLARATION__DATA_TYPE = DataPackage.EXPLICIT_DATA_DECLARATION__DATA_TYPE;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONST_DATA_DECLARATION__NAME = DataPackage.EXPLICIT_DATA_DECLARATION__NAME;

    /**
     * The feature id for the '<em><b>Value</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONST_DATA_DECLARATION__VALUE = DataPackage.EXPLICIT_DATA_DECLARATION__VALUE;

    /**
     * The feature id for the '<em><b>Const</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONST_DATA_DECLARATION__CONST = DataPackage.EXPLICIT_DATA_DECLARATION__CONST;

    /**
     * The number of structural features of the '<em>Const Data Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONST_DATA_DECLARATION_FEATURE_COUNT = DataPackage.EXPLICIT_DATA_DECLARATION_FEATURE_COUNT
            + 0;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.packaging.impl.PrototypeImpl <em>Prototype</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.packaging.impl.PrototypeImpl
     * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getPrototype()
     * @generated
     */
    int PROTOTYPE = 3;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROTOTYPE__BIP_ANNOTATIONS = AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Parameter Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROTOTYPE__PARAMETER_DECLARATIONS = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>Return Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROTOTYPE__RETURN_TYPE = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 1;

    /**
     * The feature id for the '<em><b>Native</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROTOTYPE__NATIVE = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 2;

    /**
     * The feature id for the '<em><b>Const</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROTOTYPE__CONST = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 3;

    /**
     * The number of structural features of the '<em>Prototype</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROTOTYPE_FEATURE_COUNT = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 4;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.packaging.impl.FunctionCallPrototypeImpl <em>Function Call Prototype</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.packaging.impl.FunctionCallPrototypeImpl
     * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getFunctionCallPrototype()
     * @generated
     */
    int FUNCTION_CALL_PROTOTYPE = 4;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int FUNCTION_CALL_PROTOTYPE__BIP_ANNOTATIONS = PROTOTYPE__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Parameter Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int FUNCTION_CALL_PROTOTYPE__PARAMETER_DECLARATIONS = PROTOTYPE__PARAMETER_DECLARATIONS;

    /**
     * The feature id for the '<em><b>Return Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int FUNCTION_CALL_PROTOTYPE__RETURN_TYPE = PROTOTYPE__RETURN_TYPE;

    /**
     * The feature id for the '<em><b>Native</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int FUNCTION_CALL_PROTOTYPE__NATIVE = PROTOTYPE__NATIVE;

    /**
     * The feature id for the '<em><b>Const</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int FUNCTION_CALL_PROTOTYPE__CONST = PROTOTYPE__CONST;

    /**
     * The feature id for the '<em><b>Function Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int FUNCTION_CALL_PROTOTYPE__FUNCTION_NAME = PROTOTYPE_FEATURE_COUNT + 0;

    /**
     * The number of structural features of the '<em>Function Call Prototype</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int FUNCTION_CALL_PROTOTYPE_FEATURE_COUNT = PROTOTYPE_FEATURE_COUNT + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.packaging.impl.BinaryOpPrototypeImpl <em>Binary Op Prototype</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.packaging.impl.BinaryOpPrototypeImpl
     * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getBinaryOpPrototype()
     * @generated
     */
    int BINARY_OP_PROTOTYPE = 5;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BINARY_OP_PROTOTYPE__BIP_ANNOTATIONS = PROTOTYPE__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Parameter Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BINARY_OP_PROTOTYPE__PARAMETER_DECLARATIONS = PROTOTYPE__PARAMETER_DECLARATIONS;

    /**
     * The feature id for the '<em><b>Return Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BINARY_OP_PROTOTYPE__RETURN_TYPE = PROTOTYPE__RETURN_TYPE;

    /**
     * The feature id for the '<em><b>Native</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BINARY_OP_PROTOTYPE__NATIVE = PROTOTYPE__NATIVE;

    /**
     * The feature id for the '<em><b>Const</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BINARY_OP_PROTOTYPE__CONST = PROTOTYPE__CONST;

    /**
     * The feature id for the '<em><b>Operator</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BINARY_OP_PROTOTYPE__OPERATOR = PROTOTYPE_FEATURE_COUNT + 0;

    /**
     * The number of structural features of the '<em>Binary Op Prototype</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BINARY_OP_PROTOTYPE_FEATURE_COUNT = PROTOTYPE_FEATURE_COUNT + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.packaging.impl.UnaryOpPrototypeImpl <em>Unary Op Prototype</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.packaging.impl.UnaryOpPrototypeImpl
     * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getUnaryOpPrototype()
     * @generated
     */
    int UNARY_OP_PROTOTYPE = 6;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int UNARY_OP_PROTOTYPE__BIP_ANNOTATIONS = PROTOTYPE__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Parameter Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int UNARY_OP_PROTOTYPE__PARAMETER_DECLARATIONS = PROTOTYPE__PARAMETER_DECLARATIONS;

    /**
     * The feature id for the '<em><b>Return Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int UNARY_OP_PROTOTYPE__RETURN_TYPE = PROTOTYPE__RETURN_TYPE;

    /**
     * The feature id for the '<em><b>Native</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int UNARY_OP_PROTOTYPE__NATIVE = PROTOTYPE__NATIVE;

    /**
     * The feature id for the '<em><b>Const</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int UNARY_OP_PROTOTYPE__CONST = PROTOTYPE__CONST;

    /**
     * The feature id for the '<em><b>Operator</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int UNARY_OP_PROTOTYPE__OPERATOR = PROTOTYPE_FEATURE_COUNT + 0;

    /**
     * The number of structural features of the '<em>Unary Op Prototype</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int UNARY_OP_PROTOTYPE_FEATURE_COUNT = PROTOTYPE_FEATURE_COUNT + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.packaging.impl.PrototypeParameterDeclarationImpl <em>Prototype Parameter Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.packaging.impl.PrototypeParameterDeclarationImpl
     * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getPrototypeParameterDeclaration()
     * @generated
     */
    int PROTOTYPE_PARAMETER_DECLARATION = 7;

    /**
     * The feature id for the '<em><b>Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROTOTYPE_PARAMETER_DECLARATION__TYPE = 0;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROTOTYPE_PARAMETER_DECLARATION__NAME = 1;

    /**
     * The feature id for the '<em><b>Const</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROTOTYPE_PARAMETER_DECLARATION__CONST = 2;

    /**
     * The number of structural features of the '<em>Prototype Parameter Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PROTOTYPE_PARAMETER_DECLARATION_FEATURE_COUNT = 3;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.packaging.BipPackage <em>Bip Package</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Bip Package</em>'.
     * @see bip2.ujf.verimag.bip.packaging.BipPackage
     * @generated
     */
    EClass getBipPackage();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.packaging.BipPackage#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see bip2.ujf.verimag.bip.packaging.BipPackage#getName()
     * @see #getBipPackage()
     * @generated
     */
    EAttribute getBipPackage_Name();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.packaging.BipPackage#getUsed_packages <em>Used packages</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Used packages</em>'.
     * @see bip2.ujf.verimag.bip.packaging.BipPackage#getUsed_packages()
     * @see #getBipPackage()
     * @generated
     */
    EReference getBipPackage_Used_packages();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.packaging.BipPackage#getConstData <em>Const Data</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Const Data</em>'.
     * @see bip2.ujf.verimag.bip.packaging.BipPackage#getConstData()
     * @see #getBipPackage()
     * @generated
     */
    EReference getBipPackage_ConstData();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.packaging.BipPackage#getPrototypes <em>Prototypes</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Prototypes</em>'.
     * @see bip2.ujf.verimag.bip.packaging.BipPackage#getPrototypes()
     * @see #getBipPackage()
     * @generated
     */
    EReference getBipPackage_Prototypes();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.packaging.BipPackageSet <em>Bip Package Set</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Bip Package Set</em>'.
     * @see bip2.ujf.verimag.bip.packaging.BipPackageSet
     * @generated
     */
    EClass getBipPackageSet();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.packaging.BipPackageSet#getPackages <em>Packages</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Packages</em>'.
     * @see bip2.ujf.verimag.bip.packaging.BipPackageSet#getPackages()
     * @see #getBipPackageSet()
     * @generated
     */
    EReference getBipPackageSet_Packages();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.packaging.ConstDataDeclaration <em>Const Data Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Const Data Declaration</em>'.
     * @see bip2.ujf.verimag.bip.packaging.ConstDataDeclaration
     * @generated
     */
    EClass getConstDataDeclaration();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.packaging.Prototype <em>Prototype</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Prototype</em>'.
     * @see bip2.ujf.verimag.bip.packaging.Prototype
     * @generated
     */
    EClass getPrototype();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.packaging.Prototype#getParameterDeclarations <em>Parameter Declarations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Parameter Declarations</em>'.
     * @see bip2.ujf.verimag.bip.packaging.Prototype#getParameterDeclarations()
     * @see #getPrototype()
     * @generated
     */
    EReference getPrototype_ParameterDeclarations();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.packaging.Prototype#getReturnType <em>Return Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Return Type</em>'.
     * @see bip2.ujf.verimag.bip.packaging.Prototype#getReturnType()
     * @see #getPrototype()
     * @generated
     */
    EReference getPrototype_ReturnType();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.packaging.Prototype#isNative <em>Native</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Native</em>'.
     * @see bip2.ujf.verimag.bip.packaging.Prototype#isNative()
     * @see #getPrototype()
     * @generated
     */
    EAttribute getPrototype_Native();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.packaging.Prototype#isConst <em>Const</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Const</em>'.
     * @see bip2.ujf.verimag.bip.packaging.Prototype#isConst()
     * @see #getPrototype()
     * @generated
     */
    EAttribute getPrototype_Const();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.packaging.FunctionCallPrototype <em>Function Call Prototype</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Function Call Prototype</em>'.
     * @see bip2.ujf.verimag.bip.packaging.FunctionCallPrototype
     * @generated
     */
    EClass getFunctionCallPrototype();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.packaging.FunctionCallPrototype#getFunctionName <em>Function Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Function Name</em>'.
     * @see bip2.ujf.verimag.bip.packaging.FunctionCallPrototype#getFunctionName()
     * @see #getFunctionCallPrototype()
     * @generated
     */
    EAttribute getFunctionCallPrototype_FunctionName();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.packaging.BinaryOpPrototype <em>Binary Op Prototype</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Binary Op Prototype</em>'.
     * @see bip2.ujf.verimag.bip.packaging.BinaryOpPrototype
     * @generated
     */
    EClass getBinaryOpPrototype();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.packaging.BinaryOpPrototype#getOperator <em>Operator</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Operator</em>'.
     * @see bip2.ujf.verimag.bip.packaging.BinaryOpPrototype#getOperator()
     * @see #getBinaryOpPrototype()
     * @generated
     */
    EAttribute getBinaryOpPrototype_Operator();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.packaging.UnaryOpPrototype <em>Unary Op Prototype</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Unary Op Prototype</em>'.
     * @see bip2.ujf.verimag.bip.packaging.UnaryOpPrototype
     * @generated
     */
    EClass getUnaryOpPrototype();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.packaging.UnaryOpPrototype#getOperator <em>Operator</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Operator</em>'.
     * @see bip2.ujf.verimag.bip.packaging.UnaryOpPrototype#getOperator()
     * @see #getUnaryOpPrototype()
     * @generated
     */
    EAttribute getUnaryOpPrototype_Operator();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration <em>Prototype Parameter Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Prototype Parameter Declaration</em>'.
     * @see bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration
     * @generated
     */
    EClass getPrototypeParameterDeclaration();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration#getType <em>Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Type</em>'.
     * @see bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration#getType()
     * @see #getPrototypeParameterDeclaration()
     * @generated
     */
    EReference getPrototypeParameterDeclaration_Type();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration#getName()
     * @see #getPrototypeParameterDeclaration()
     * @generated
     */
    EAttribute getPrototypeParameterDeclaration_Name();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration#isConst <em>Const</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Const</em>'.
     * @see bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration#isConst()
     * @see #getPrototypeParameterDeclaration()
     * @generated
     */
    EAttribute getPrototypeParameterDeclaration_Const();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.packaging.BipPackage#getAtomTypes <em>Atom Types</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Atom Types</em>'.
     * @see bip2.ujf.verimag.bip.packaging.BipPackage#getAtomTypes()
     * @see #getBipPackage()
     * @generated
     */
    EReference getBipPackage_AtomTypes();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.packaging.BipPackage#getCompoundTypes <em>Compound Types</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Compound Types</em>'.
     * @see bip2.ujf.verimag.bip.packaging.BipPackage#getCompoundTypes()
     * @see #getBipPackage()
     * @generated
     */
    EReference getBipPackage_CompoundTypes();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.packaging.BipPackage#getConnectorTypes <em>Connector Types</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Connector Types</em>'.
     * @see bip2.ujf.verimag.bip.packaging.BipPackage#getConnectorTypes()
     * @see #getBipPackage()
     * @generated
     */
    EReference getBipPackage_ConnectorTypes();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.packaging.BipPackage#getPortTypes <em>Port Types</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Port Types</em>'.
     * @see bip2.ujf.verimag.bip.packaging.BipPackage#getPortTypes()
     * @see #getBipPackage()
     * @generated
     */
    EReference getBipPackage_PortTypes();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.packaging.BipPackage#getDataTypes <em>Data Types</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Data Types</em>'.
     * @see bip2.ujf.verimag.bip.packaging.BipPackage#getDataTypes()
     * @see #getBipPackage()
     * @generated
     */
    EReference getBipPackage_DataTypes();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    PackagingFactory getPackagingFactory();

    /**
     * <!-- begin-user-doc -->
     * Defines literals for the meta objects that represent
     * <ul>
     *   <li>each class,</li>
     *   <li>each feature of each class,</li>
     *   <li>each enum,</li>
     *   <li>and each data type</li>
     * </ul>
     * <!-- end-user-doc -->
     * @generated
     */
    interface Literals {
        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.packaging.impl.BipPackageImpl <em>Bip Package</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.packaging.impl.BipPackageImpl
         * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getBipPackage()
         * @generated
         */
        EClass BIP_PACKAGE = eINSTANCE.getBipPackage();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute BIP_PACKAGE__NAME = eINSTANCE.getBipPackage_Name();

        /**
         * The meta object literal for the '<em><b>Used packages</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference BIP_PACKAGE__USED_PACKAGES = eINSTANCE
                .getBipPackage_Used_packages();

        /**
         * The meta object literal for the '<em><b>Const Data</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference BIP_PACKAGE__CONST_DATA = eINSTANCE
                .getBipPackage_ConstData();

        /**
         * The meta object literal for the '<em><b>Prototypes</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference BIP_PACKAGE__PROTOTYPES = eINSTANCE
                .getBipPackage_Prototypes();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.packaging.impl.BipPackageSetImpl <em>Bip Package Set</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.packaging.impl.BipPackageSetImpl
         * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getBipPackageSet()
         * @generated
         */
        EClass BIP_PACKAGE_SET = eINSTANCE.getBipPackageSet();

        /**
         * The meta object literal for the '<em><b>Packages</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference BIP_PACKAGE_SET__PACKAGES = eINSTANCE
                .getBipPackageSet_Packages();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.packaging.impl.ConstDataDeclarationImpl <em>Const Data Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.packaging.impl.ConstDataDeclarationImpl
         * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getConstDataDeclaration()
         * @generated
         */
        EClass CONST_DATA_DECLARATION = eINSTANCE.getConstDataDeclaration();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.packaging.impl.PrototypeImpl <em>Prototype</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.packaging.impl.PrototypeImpl
         * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getPrototype()
         * @generated
         */
        EClass PROTOTYPE = eINSTANCE.getPrototype();

        /**
         * The meta object literal for the '<em><b>Parameter Declarations</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PROTOTYPE__PARAMETER_DECLARATIONS = eINSTANCE
                .getPrototype_ParameterDeclarations();

        /**
         * The meta object literal for the '<em><b>Return Type</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PROTOTYPE__RETURN_TYPE = eINSTANCE.getPrototype_ReturnType();

        /**
         * The meta object literal for the '<em><b>Native</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute PROTOTYPE__NATIVE = eINSTANCE.getPrototype_Native();

        /**
         * The meta object literal for the '<em><b>Const</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute PROTOTYPE__CONST = eINSTANCE.getPrototype_Const();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.packaging.impl.FunctionCallPrototypeImpl <em>Function Call Prototype</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.packaging.impl.FunctionCallPrototypeImpl
         * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getFunctionCallPrototype()
         * @generated
         */
        EClass FUNCTION_CALL_PROTOTYPE = eINSTANCE.getFunctionCallPrototype();

        /**
         * The meta object literal for the '<em><b>Function Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute FUNCTION_CALL_PROTOTYPE__FUNCTION_NAME = eINSTANCE
                .getFunctionCallPrototype_FunctionName();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.packaging.impl.BinaryOpPrototypeImpl <em>Binary Op Prototype</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.packaging.impl.BinaryOpPrototypeImpl
         * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getBinaryOpPrototype()
         * @generated
         */
        EClass BINARY_OP_PROTOTYPE = eINSTANCE.getBinaryOpPrototype();

        /**
         * The meta object literal for the '<em><b>Operator</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute BINARY_OP_PROTOTYPE__OPERATOR = eINSTANCE
                .getBinaryOpPrototype_Operator();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.packaging.impl.UnaryOpPrototypeImpl <em>Unary Op Prototype</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.packaging.impl.UnaryOpPrototypeImpl
         * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getUnaryOpPrototype()
         * @generated
         */
        EClass UNARY_OP_PROTOTYPE = eINSTANCE.getUnaryOpPrototype();

        /**
         * The meta object literal for the '<em><b>Operator</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute UNARY_OP_PROTOTYPE__OPERATOR = eINSTANCE
                .getUnaryOpPrototype_Operator();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.packaging.impl.PrototypeParameterDeclarationImpl <em>Prototype Parameter Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.packaging.impl.PrototypeParameterDeclarationImpl
         * @see bip2.ujf.verimag.bip.packaging.impl.PackagingPackageImpl#getPrototypeParameterDeclaration()
         * @generated
         */
        EClass PROTOTYPE_PARAMETER_DECLARATION = eINSTANCE
                .getPrototypeParameterDeclaration();

        /**
         * The meta object literal for the '<em><b>Type</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PROTOTYPE_PARAMETER_DECLARATION__TYPE = eINSTANCE
                .getPrototypeParameterDeclaration_Type();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute PROTOTYPE_PARAMETER_DECLARATION__NAME = eINSTANCE
                .getPrototypeParameterDeclaration_Name();

        /**
         * The meta object literal for the '<em><b>Const</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute PROTOTYPE_PARAMETER_DECLARATION__CONST = eINSTANCE
                .getPrototypeParameterDeclaration_Const();

        /**
         * The meta object literal for the '<em><b>Atom Types</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference BIP_PACKAGE__ATOM_TYPES = eINSTANCE
                .getBipPackage_AtomTypes();

        /**
         * The meta object literal for the '<em><b>Compound Types</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference BIP_PACKAGE__COMPOUND_TYPES = eINSTANCE
                .getBipPackage_CompoundTypes();

        /**
         * The meta object literal for the '<em><b>Connector Types</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference BIP_PACKAGE__CONNECTOR_TYPES = eINSTANCE
                .getBipPackage_ConnectorTypes();

        /**
         * The meta object literal for the '<em><b>Port Types</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference BIP_PACKAGE__PORT_TYPES = eINSTANCE
                .getBipPackage_PortTypes();

        /**
         * The meta object literal for the '<em><b>Data Types</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference BIP_PACKAGE__DATA_TYPES = eINSTANCE
                .getBipPackage_DataTypes();

    }

} //PackagingPackage
