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

package bip2.ujf.verimag.bip.data;

import bip2.ujf.verimag.bip.annotation.AnnotationPackage;
import bip2.ujf.verimag.bip.types.TypesPackage;
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
 * @see bip2.ujf.verimag.bip.data.DataFactory
 * @model kind="package"
 * @generated
 */
public interface DataPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "data";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/data/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.data";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    DataPackage eINSTANCE = bip2.ujf.verimag.bip.data.impl.DataPackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.data.impl.DataTypeImpl <em>Type</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.data.impl.DataTypeImpl
     * @see bip2.ujf.verimag.bip.data.impl.DataPackageImpl#getDataType()
     * @generated
     */
    int DATA_TYPE = 0;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_TYPE__BIP_ANNOTATIONS = TypesPackage.TYPE__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_TYPE__NAME = TypesPackage.TYPE__NAME;

    /**
     * The feature id for the '<em><b>Native</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_TYPE__NATIVE = TypesPackage.TYPE__NATIVE;

    /**
     * The feature id for the '<em><b>Super Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_TYPE__SUPER_TYPES = TypesPackage.TYPE__SUPER_TYPES;

    /**
     * The feature id for the '<em><b>Castable Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_TYPE__CASTABLE_TYPES = TypesPackage.TYPE__CASTABLE_TYPES;

    /**
     * The feature id for the '<em><b>Backend Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_TYPE__BACKEND_NAME = TypesPackage.TYPE_FEATURE_COUNT + 0;

    /**
     * The number of structural features of the '<em>Type</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_TYPE_FEATURE_COUNT = TypesPackage.TYPE_FEATURE_COUNT + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.data.DataDeclaration <em>Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.data.DataDeclaration
     * @see bip2.ujf.verimag.bip.data.impl.DataPackageImpl#getDataDeclaration()
     * @generated
     */
    int DATA_DECLARATION = 1;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_DECLARATION__BIP_ANNOTATIONS = AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Data Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_DECLARATION__DATA_TYPE = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_DECLARATION__NAME = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 1;

    /**
     * The feature id for the '<em><b>Value</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_DECLARATION__VALUE = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 2;

    /**
     * The feature id for the '<em><b>Const</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_DECLARATION__CONST = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 3;

    /**
     * The number of structural features of the '<em>Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_DECLARATION_FEATURE_COUNT = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 4;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.data.ExplicitDataDeclaration <em>Explicit Data Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.data.ExplicitDataDeclaration
     * @see bip2.ujf.verimag.bip.data.impl.DataPackageImpl#getExplicitDataDeclaration()
     * @generated
     */
    int EXPLICIT_DATA_DECLARATION = 2;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int EXPLICIT_DATA_DECLARATION__BIP_ANNOTATIONS = DATA_DECLARATION__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Data Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int EXPLICIT_DATA_DECLARATION__DATA_TYPE = DATA_DECLARATION__DATA_TYPE;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int EXPLICIT_DATA_DECLARATION__NAME = DATA_DECLARATION__NAME;

    /**
     * The feature id for the '<em><b>Value</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int EXPLICIT_DATA_DECLARATION__VALUE = DATA_DECLARATION__VALUE;

    /**
     * The feature id for the '<em><b>Const</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int EXPLICIT_DATA_DECLARATION__CONST = DATA_DECLARATION__CONST;

    /**
     * The number of structural features of the '<em>Explicit Data Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int EXPLICIT_DATA_DECLARATION_FEATURE_COUNT = DATA_DECLARATION_FEATURE_COUNT
            + 0;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.data.impl.SubDataDeclarationReferenceImpl <em>Sub Data Declaration Reference</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.data.impl.SubDataDeclarationReferenceImpl
     * @see bip2.ujf.verimag.bip.data.impl.DataPackageImpl#getSubDataDeclarationReference()
     * @generated
     */
    int SUB_DATA_DECLARATION_REFERENCE = 3;

    /**
     * The feature id for the '<em><b>Forward Data Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int SUB_DATA_DECLARATION_REFERENCE__FORWARD_DATA_DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Component Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int SUB_DATA_DECLARATION_REFERENCE__COMPONENT_DECLARATION = 1;

    /**
     * The feature id for the '<em><b>Port Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int SUB_DATA_DECLARATION_REFERENCE__PORT_DECLARATION = 2;

    /**
     * The number of structural features of the '<em>Sub Data Declaration Reference</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int SUB_DATA_DECLARATION_REFERENCE_FEATURE_COUNT = 3;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.data.DataParameter <em>Parameter</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.data.DataParameter
     * @see bip2.ujf.verimag.bip.data.impl.DataPackageImpl#getDataParameter()
     * @generated
     */
    int DATA_PARAMETER = 4;

    /**
     * The feature id for the '<em><b>Parameter Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_PARAMETER__PARAMETER_DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_PARAMETER__TYPE = 1;

    /**
     * The number of structural features of the '<em>Parameter</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_PARAMETER_FEATURE_COUNT = 2;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.data.impl.DataDeclarationReferenceDataParameterImpl <em>Declaration Reference Data Parameter</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.data.impl.DataDeclarationReferenceDataParameterImpl
     * @see bip2.ujf.verimag.bip.data.impl.DataPackageImpl#getDataDeclarationReferenceDataParameter()
     * @generated
     */
    int DATA_DECLARATION_REFERENCE_DATA_PARAMETER = 5;

    /**
     * The feature id for the '<em><b>Parameter Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_DECLARATION_REFERENCE_DATA_PARAMETER__PARAMETER_DECLARATION = DATA_PARAMETER__PARAMETER_DECLARATION;

    /**
     * The feature id for the '<em><b>Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_DECLARATION_REFERENCE_DATA_PARAMETER__TYPE = DATA_PARAMETER__TYPE;

    /**
     * The feature id for the '<em><b>Data Declaration Reference</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_DECLARATION_REFERENCE_DATA_PARAMETER__DATA_DECLARATION_REFERENCE = DATA_PARAMETER_FEATURE_COUNT
            + 0;

    /**
     * The number of structural features of the '<em>Declaration Reference Data Parameter</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_DECLARATION_REFERENCE_DATA_PARAMETER_FEATURE_COUNT = DATA_PARAMETER_FEATURE_COUNT
            + 1;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.data.DataType <em>Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Type</em>'.
     * @see bip2.ujf.verimag.bip.data.DataType
     * @generated
     */
    EClass getDataType();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.data.DataType#getBackendName <em>Backend Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Backend Name</em>'.
     * @see bip2.ujf.verimag.bip.data.DataType#getBackendName()
     * @see #getDataType()
     * @generated
     */
    EAttribute getDataType_BackendName();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.data.DataDeclaration <em>Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Declaration</em>'.
     * @see bip2.ujf.verimag.bip.data.DataDeclaration
     * @generated
     */
    EClass getDataDeclaration();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.data.DataDeclaration#getDataType <em>Data Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Data Type</em>'.
     * @see bip2.ujf.verimag.bip.data.DataDeclaration#getDataType()
     * @see #getDataDeclaration()
     * @generated
     */
    EReference getDataDeclaration_DataType();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.data.DataDeclaration#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see bip2.ujf.verimag.bip.data.DataDeclaration#getName()
     * @see #getDataDeclaration()
     * @generated
     */
    EAttribute getDataDeclaration_Name();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.data.DataDeclaration#getValue <em>Value</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Value</em>'.
     * @see bip2.ujf.verimag.bip.data.DataDeclaration#getValue()
     * @see #getDataDeclaration()
     * @generated
     */
    EReference getDataDeclaration_Value();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.data.DataDeclaration#isConst <em>Const</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Const</em>'.
     * @see bip2.ujf.verimag.bip.data.DataDeclaration#isConst()
     * @see #getDataDeclaration()
     * @generated
     */
    EAttribute getDataDeclaration_Const();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.data.ExplicitDataDeclaration <em>Explicit Data Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Explicit Data Declaration</em>'.
     * @see bip2.ujf.verimag.bip.data.ExplicitDataDeclaration
     * @generated
     */
    EClass getExplicitDataDeclaration();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.data.SubDataDeclarationReference <em>Sub Data Declaration Reference</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Sub Data Declaration Reference</em>'.
     * @see bip2.ujf.verimag.bip.data.SubDataDeclarationReference
     * @generated
     */
    EClass getSubDataDeclarationReference();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.data.SubDataDeclarationReference#getForwardDataDeclaration <em>Forward Data Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Forward Data Declaration</em>'.
     * @see bip2.ujf.verimag.bip.data.SubDataDeclarationReference#getForwardDataDeclaration()
     * @see #getSubDataDeclarationReference()
     * @generated
     */
    EReference getSubDataDeclarationReference_ForwardDataDeclaration();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.data.SubDataDeclarationReference#getComponentDeclaration <em>Component Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Component Declaration</em>'.
     * @see bip2.ujf.verimag.bip.data.SubDataDeclarationReference#getComponentDeclaration()
     * @see #getSubDataDeclarationReference()
     * @generated
     */
    EReference getSubDataDeclarationReference_ComponentDeclaration();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.data.SubDataDeclarationReference#getPortDeclaration <em>Port Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Port Declaration</em>'.
     * @see bip2.ujf.verimag.bip.data.SubDataDeclarationReference#getPortDeclaration()
     * @see #getSubDataDeclarationReference()
     * @generated
     */
    EReference getSubDataDeclarationReference_PortDeclaration();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.data.DataParameter <em>Parameter</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Parameter</em>'.
     * @see bip2.ujf.verimag.bip.data.DataParameter
     * @generated
     */
    EClass getDataParameter();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.data.DataParameter#getParameterDeclaration <em>Parameter Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Parameter Declaration</em>'.
     * @see bip2.ujf.verimag.bip.data.DataParameter#getParameterDeclaration()
     * @see #getDataParameter()
     * @generated
     */
    EReference getDataParameter_ParameterDeclaration();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.data.DataParameter#getType <em>Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Type</em>'.
     * @see bip2.ujf.verimag.bip.data.DataParameter#getType()
     * @see #getDataParameter()
     * @generated
     */
    EReference getDataParameter_Type();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter <em>Declaration Reference Data Parameter</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Declaration Reference Data Parameter</em>'.
     * @see bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter
     * @generated
     */
    EClass getDataDeclarationReferenceDataParameter();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter#getDataDeclarationReference <em>Data Declaration Reference</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Data Declaration Reference</em>'.
     * @see bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter#getDataDeclarationReference()
     * @see #getDataDeclarationReferenceDataParameter()
     * @generated
     */
    EReference getDataDeclarationReferenceDataParameter_DataDeclarationReference();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    DataFactory getDataFactory();

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
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.data.impl.DataTypeImpl <em>Type</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.data.impl.DataTypeImpl
         * @see bip2.ujf.verimag.bip.data.impl.DataPackageImpl#getDataType()
         * @generated
         */
        EClass DATA_TYPE = eINSTANCE.getDataType();

        /**
         * The meta object literal for the '<em><b>Backend Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute DATA_TYPE__BACKEND_NAME = eINSTANCE
                .getDataType_BackendName();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.data.DataDeclaration <em>Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.data.DataDeclaration
         * @see bip2.ujf.verimag.bip.data.impl.DataPackageImpl#getDataDeclaration()
         * @generated
         */
        EClass DATA_DECLARATION = eINSTANCE.getDataDeclaration();

        /**
         * The meta object literal for the '<em><b>Data Type</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference DATA_DECLARATION__DATA_TYPE = eINSTANCE
                .getDataDeclaration_DataType();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute DATA_DECLARATION__NAME = eINSTANCE.getDataDeclaration_Name();

        /**
         * The meta object literal for the '<em><b>Value</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference DATA_DECLARATION__VALUE = eINSTANCE
                .getDataDeclaration_Value();

        /**
         * The meta object literal for the '<em><b>Const</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute DATA_DECLARATION__CONST = eINSTANCE
                .getDataDeclaration_Const();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.data.ExplicitDataDeclaration <em>Explicit Data Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.data.ExplicitDataDeclaration
         * @see bip2.ujf.verimag.bip.data.impl.DataPackageImpl#getExplicitDataDeclaration()
         * @generated
         */
        EClass EXPLICIT_DATA_DECLARATION = eINSTANCE
                .getExplicitDataDeclaration();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.data.impl.SubDataDeclarationReferenceImpl <em>Sub Data Declaration Reference</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.data.impl.SubDataDeclarationReferenceImpl
         * @see bip2.ujf.verimag.bip.data.impl.DataPackageImpl#getSubDataDeclarationReference()
         * @generated
         */
        EClass SUB_DATA_DECLARATION_REFERENCE = eINSTANCE
                .getSubDataDeclarationReference();

        /**
         * The meta object literal for the '<em><b>Forward Data Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference SUB_DATA_DECLARATION_REFERENCE__FORWARD_DATA_DECLARATION = eINSTANCE
                .getSubDataDeclarationReference_ForwardDataDeclaration();

        /**
         * The meta object literal for the '<em><b>Component Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference SUB_DATA_DECLARATION_REFERENCE__COMPONENT_DECLARATION = eINSTANCE
                .getSubDataDeclarationReference_ComponentDeclaration();

        /**
         * The meta object literal for the '<em><b>Port Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference SUB_DATA_DECLARATION_REFERENCE__PORT_DECLARATION = eINSTANCE
                .getSubDataDeclarationReference_PortDeclaration();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.data.DataParameter <em>Parameter</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.data.DataParameter
         * @see bip2.ujf.verimag.bip.data.impl.DataPackageImpl#getDataParameter()
         * @generated
         */
        EClass DATA_PARAMETER = eINSTANCE.getDataParameter();

        /**
         * The meta object literal for the '<em><b>Parameter Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference DATA_PARAMETER__PARAMETER_DECLARATION = eINSTANCE
                .getDataParameter_ParameterDeclaration();

        /**
         * The meta object literal for the '<em><b>Type</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference DATA_PARAMETER__TYPE = eINSTANCE.getDataParameter_Type();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.data.impl.DataDeclarationReferenceDataParameterImpl <em>Declaration Reference Data Parameter</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.data.impl.DataDeclarationReferenceDataParameterImpl
         * @see bip2.ujf.verimag.bip.data.impl.DataPackageImpl#getDataDeclarationReferenceDataParameter()
         * @generated
         */
        EClass DATA_DECLARATION_REFERENCE_DATA_PARAMETER = eINSTANCE
                .getDataDeclarationReferenceDataParameter();

        /**
         * The meta object literal for the '<em><b>Data Declaration Reference</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference DATA_DECLARATION_REFERENCE_DATA_PARAMETER__DATA_DECLARATION_REFERENCE = eINSTANCE
                .getDataDeclarationReferenceDataParameter_DataDeclarationReference();

    }

} //DataPackage
