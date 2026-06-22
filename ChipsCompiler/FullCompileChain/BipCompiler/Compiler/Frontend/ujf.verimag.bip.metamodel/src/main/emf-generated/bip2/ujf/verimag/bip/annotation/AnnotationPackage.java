/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
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

package bip2.ujf.verimag.bip.annotation;

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
 * @see bip2.ujf.verimag.bip.annotation.AnnotationFactory
 * @model kind="package"
 * @generated
 */
public interface AnnotationPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "annotation";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/annotation/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.annotation";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    AnnotationPackage eINSTANCE = bip2.ujf.verimag.bip.annotation.impl.AnnotationPackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.annotation.impl.AnnotatedElementImpl <em>Annotated Element</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.annotation.impl.AnnotatedElementImpl
     * @see bip2.ujf.verimag.bip.annotation.impl.AnnotationPackageImpl#getAnnotatedElement()
     * @generated
     */
    int ANNOTATED_ELEMENT = 0;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ANNOTATED_ELEMENT__BIP_ANNOTATIONS = 0;

    /**
     * The number of structural features of the '<em>Annotated Element</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ANNOTATED_ELEMENT_FEATURE_COUNT = 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.annotation.impl.BipAnnotationImpl <em>Bip Annotation</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.annotation.impl.BipAnnotationImpl
     * @see bip2.ujf.verimag.bip.annotation.impl.AnnotationPackageImpl#getBipAnnotation()
     * @generated
     */
    int BIP_ANNOTATION = 1;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_ANNOTATION__NAME = 0;

    /**
     * The feature id for the '<em><b>Parameters</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_ANNOTATION__PARAMETERS = 1;

    /**
     * The number of structural features of the '<em>Bip Annotation</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_ANNOTATION_FEATURE_COUNT = 2;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.annotation.impl.StringToAnnotationMapEntryImpl <em>String To Annotation Map Entry</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.annotation.impl.StringToAnnotationMapEntryImpl
     * @see bip2.ujf.verimag.bip.annotation.impl.AnnotationPackageImpl#getStringToAnnotationMapEntry()
     * @generated
     */
    int STRING_TO_ANNOTATION_MAP_ENTRY = 2;

    /**
     * The feature id for the '<em><b>Key</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STRING_TO_ANNOTATION_MAP_ENTRY__KEY = 0;

    /**
     * The feature id for the '<em><b>Value</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STRING_TO_ANNOTATION_MAP_ENTRY__VALUE = 1;

    /**
     * The number of structural features of the '<em>String To Annotation Map Entry</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STRING_TO_ANNOTATION_MAP_ENTRY_FEATURE_COUNT = 2;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.annotation.impl.StringToStringMapEntryImpl <em>String To String Map Entry</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.annotation.impl.StringToStringMapEntryImpl
     * @see bip2.ujf.verimag.bip.annotation.impl.AnnotationPackageImpl#getStringToStringMapEntry()
     * @generated
     */
    int STRING_TO_STRING_MAP_ENTRY = 3;

    /**
     * The feature id for the '<em><b>Key</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STRING_TO_STRING_MAP_ENTRY__KEY = 0;

    /**
     * The feature id for the '<em><b>Value</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STRING_TO_STRING_MAP_ENTRY__VALUE = 1;

    /**
     * The number of structural features of the '<em>String To String Map Entry</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STRING_TO_STRING_MAP_ENTRY_FEATURE_COUNT = 2;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.annotation.AnnotatedElement <em>Annotated Element</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Annotated Element</em>'.
     * @see bip2.ujf.verimag.bip.annotation.AnnotatedElement
     * @generated
     */
    EClass getAnnotatedElement();

    /**
     * Returns the meta object for the map '{@link bip2.ujf.verimag.bip.annotation.AnnotatedElement#getBipAnnotations <em>Bip Annotations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the map '<em>Bip Annotations</em>'.
     * @see bip2.ujf.verimag.bip.annotation.AnnotatedElement#getBipAnnotations()
     * @see #getAnnotatedElement()
     * @generated
     */
    EReference getAnnotatedElement_BipAnnotations();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.annotation.BipAnnotation <em>Bip Annotation</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Bip Annotation</em>'.
     * @see bip2.ujf.verimag.bip.annotation.BipAnnotation
     * @generated
     */
    EClass getBipAnnotation();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.annotation.BipAnnotation#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see bip2.ujf.verimag.bip.annotation.BipAnnotation#getName()
     * @see #getBipAnnotation()
     * @generated
     */
    EAttribute getBipAnnotation_Name();

    /**
     * Returns the meta object for the map '{@link bip2.ujf.verimag.bip.annotation.BipAnnotation#getParameters <em>Parameters</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the map '<em>Parameters</em>'.
     * @see bip2.ujf.verimag.bip.annotation.BipAnnotation#getParameters()
     * @see #getBipAnnotation()
     * @generated
     */
    EReference getBipAnnotation_Parameters();

    /**
     * Returns the meta object for class '{@link java.util.Map.Entry <em>String To Annotation Map Entry</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>String To Annotation Map Entry</em>'.
     * @see java.util.Map.Entry
     * @model keyDataType="org.eclipse.emf.ecore.EString" keyRequired="true"
     *        valueType="bip2.ujf.verimag.bip.annotation.BipAnnotation" valueContainment="true" valueRequired="true"
     * @generated
     */
    EClass getStringToAnnotationMapEntry();

    /**
     * Returns the meta object for the attribute '{@link java.util.Map.Entry <em>Key</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Key</em>'.
     * @see java.util.Map.Entry
     * @see #getStringToAnnotationMapEntry()
     * @generated
     */
    EAttribute getStringToAnnotationMapEntry_Key();

    /**
     * Returns the meta object for the containment reference '{@link java.util.Map.Entry <em>Value</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Value</em>'.
     * @see java.util.Map.Entry
     * @see #getStringToAnnotationMapEntry()
     * @generated
     */
    EReference getStringToAnnotationMapEntry_Value();

    /**
     * Returns the meta object for class '{@link java.util.Map.Entry <em>String To String Map Entry</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>String To String Map Entry</em>'.
     * @see java.util.Map.Entry
     * @model keyDataType="org.eclipse.emf.ecore.EString" keyRequired="true"
     *        valueDataType="org.eclipse.emf.ecore.EString" valueRequired="true"
     * @generated
     */
    EClass getStringToStringMapEntry();

    /**
     * Returns the meta object for the attribute '{@link java.util.Map.Entry <em>Key</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Key</em>'.
     * @see java.util.Map.Entry
     * @see #getStringToStringMapEntry()
     * @generated
     */
    EAttribute getStringToStringMapEntry_Key();

    /**
     * Returns the meta object for the attribute '{@link java.util.Map.Entry <em>Value</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Value</em>'.
     * @see java.util.Map.Entry
     * @see #getStringToStringMapEntry()
     * @generated
     */
    EAttribute getStringToStringMapEntry_Value();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    AnnotationFactory getAnnotationFactory();

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
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.annotation.impl.AnnotatedElementImpl <em>Annotated Element</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.annotation.impl.AnnotatedElementImpl
         * @see bip2.ujf.verimag.bip.annotation.impl.AnnotationPackageImpl#getAnnotatedElement()
         * @generated
         */
        EClass ANNOTATED_ELEMENT = eINSTANCE.getAnnotatedElement();

        /**
         * The meta object literal for the '<em><b>Bip Annotations</b></em>' map feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ANNOTATED_ELEMENT__BIP_ANNOTATIONS = eINSTANCE
                .getAnnotatedElement_BipAnnotations();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.annotation.impl.BipAnnotationImpl <em>Bip Annotation</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.annotation.impl.BipAnnotationImpl
         * @see bip2.ujf.verimag.bip.annotation.impl.AnnotationPackageImpl#getBipAnnotation()
         * @generated
         */
        EClass BIP_ANNOTATION = eINSTANCE.getBipAnnotation();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute BIP_ANNOTATION__NAME = eINSTANCE.getBipAnnotation_Name();

        /**
         * The meta object literal for the '<em><b>Parameters</b></em>' map feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference BIP_ANNOTATION__PARAMETERS = eINSTANCE
                .getBipAnnotation_Parameters();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.annotation.impl.StringToAnnotationMapEntryImpl <em>String To Annotation Map Entry</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.annotation.impl.StringToAnnotationMapEntryImpl
         * @see bip2.ujf.verimag.bip.annotation.impl.AnnotationPackageImpl#getStringToAnnotationMapEntry()
         * @generated
         */
        EClass STRING_TO_ANNOTATION_MAP_ENTRY = eINSTANCE
                .getStringToAnnotationMapEntry();

        /**
         * The meta object literal for the '<em><b>Key</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute STRING_TO_ANNOTATION_MAP_ENTRY__KEY = eINSTANCE
                .getStringToAnnotationMapEntry_Key();

        /**
         * The meta object literal for the '<em><b>Value</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference STRING_TO_ANNOTATION_MAP_ENTRY__VALUE = eINSTANCE
                .getStringToAnnotationMapEntry_Value();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.annotation.impl.StringToStringMapEntryImpl <em>String To String Map Entry</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.annotation.impl.StringToStringMapEntryImpl
         * @see bip2.ujf.verimag.bip.annotation.impl.AnnotationPackageImpl#getStringToStringMapEntry()
         * @generated
         */
        EClass STRING_TO_STRING_MAP_ENTRY = eINSTANCE
                .getStringToStringMapEntry();

        /**
         * The meta object literal for the '<em><b>Key</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute STRING_TO_STRING_MAP_ENTRY__KEY = eINSTANCE
                .getStringToStringMapEntry_Key();

        /**
         * The meta object literal for the '<em><b>Value</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute STRING_TO_STRING_MAP_ENTRY__VALUE = eINSTANCE
                .getStringToStringMapEntry_Value();

    }

} //AnnotationPackage
