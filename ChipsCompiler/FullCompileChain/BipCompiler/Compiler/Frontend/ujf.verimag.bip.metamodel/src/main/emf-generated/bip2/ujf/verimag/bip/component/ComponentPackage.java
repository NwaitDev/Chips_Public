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

package bip2.ujf.verimag.bip.component;

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
 * @see bip2.ujf.verimag.bip.component.ComponentFactory
 * @model kind="package"
 * @generated
 */
public interface ComponentPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "component";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/component/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.component";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    ComponentPackage eINSTANCE = bip2.ujf.verimag.bip.component.impl.ComponentPackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.component.impl.ComponentDeclarationImpl <em>Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.component.impl.ComponentDeclarationImpl
     * @see bip2.ujf.verimag.bip.component.impl.ComponentPackageImpl#getComponentDeclaration()
     * @generated
     */
    int COMPONENT_DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_DECLARATION__BIP_ANNOTATIONS = AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_DECLARATION__TYPE = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>Parameters</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_DECLARATION__PARAMETERS = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 1;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_DECLARATION__NAME = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 2;

    /**
     * The number of structural features of the '<em>Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_DECLARATION_FEATURE_COUNT = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 3;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.component.impl.ComponentDataParameterDeclarationImpl <em>Data Parameter Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.component.impl.ComponentDataParameterDeclarationImpl
     * @see bip2.ujf.verimag.bip.component.impl.ComponentPackageImpl#getComponentDataParameterDeclaration()
     * @generated
     */
    int COMPONENT_DATA_PARAMETER_DECLARATION = 1;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_DATA_PARAMETER_DECLARATION__BIP_ANNOTATIONS = DataPackage.DATA_DECLARATION__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Data Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_DATA_PARAMETER_DECLARATION__DATA_TYPE = DataPackage.DATA_DECLARATION__DATA_TYPE;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_DATA_PARAMETER_DECLARATION__NAME = DataPackage.DATA_DECLARATION__NAME;

    /**
     * The feature id for the '<em><b>Value</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_DATA_PARAMETER_DECLARATION__VALUE = DataPackage.DATA_DECLARATION__VALUE;

    /**
     * The feature id for the '<em><b>Const</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_DATA_PARAMETER_DECLARATION__CONST = DataPackage.DATA_DECLARATION__CONST;

    /**
     * The number of structural features of the '<em>Data Parameter Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_DATA_PARAMETER_DECLARATION_FEATURE_COUNT = DataPackage.DATA_DECLARATION_FEATURE_COUNT
            + 0;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.component.ComponentDeclaration <em>Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Declaration</em>'.
     * @see bip2.ujf.verimag.bip.component.ComponentDeclaration
     * @generated
     */
    EClass getComponentDeclaration();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.component.ComponentDeclaration#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see bip2.ujf.verimag.bip.component.ComponentDeclaration#getName()
     * @see #getComponentDeclaration()
     * @generated
     */
    EAttribute getComponentDeclaration_Name();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.component.ComponentDeclaration#getType <em>Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Type</em>'.
     * @see bip2.ujf.verimag.bip.component.ComponentDeclaration#getType()
     * @see #getComponentDeclaration()
     * @generated
     */
    EReference getComponentDeclaration_Type();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.component.ComponentDeclaration#getParameters <em>Parameters</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Parameters</em>'.
     * @see bip2.ujf.verimag.bip.component.ComponentDeclaration#getParameters()
     * @see #getComponentDeclaration()
     * @generated
     */
    EReference getComponentDeclaration_Parameters();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.component.ComponentDataParameterDeclaration <em>Data Parameter Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Data Parameter Declaration</em>'.
     * @see bip2.ujf.verimag.bip.component.ComponentDataParameterDeclaration
     * @generated
     */
    EClass getComponentDataParameterDeclaration();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    ComponentFactory getComponentFactory();

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
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.component.impl.ComponentDeclarationImpl <em>Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.component.impl.ComponentDeclarationImpl
         * @see bip2.ujf.verimag.bip.component.impl.ComponentPackageImpl#getComponentDeclaration()
         * @generated
         */
        EClass COMPONENT_DECLARATION = eINSTANCE.getComponentDeclaration();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute COMPONENT_DECLARATION__NAME = eINSTANCE
                .getComponentDeclaration_Name();

        /**
         * The meta object literal for the '<em><b>Type</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPONENT_DECLARATION__TYPE = eINSTANCE
                .getComponentDeclaration_Type();

        /**
         * The meta object literal for the '<em><b>Parameters</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPONENT_DECLARATION__PARAMETERS = eINSTANCE
                .getComponentDeclaration_Parameters();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.component.impl.ComponentDataParameterDeclarationImpl <em>Data Parameter Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.component.impl.ComponentDataParameterDeclarationImpl
         * @see bip2.ujf.verimag.bip.component.impl.ComponentPackageImpl#getComponentDataParameterDeclaration()
         * @generated
         */
        EClass COMPONENT_DATA_PARAMETER_DECLARATION = eINSTANCE
                .getComponentDataParameterDeclaration();

    }

} //ComponentPackage
