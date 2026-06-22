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

package bip2.ujf.verimag.bip.port;

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
 * @see bip2.ujf.verimag.bip.port.PortFactory
 * @model kind="package"
 * @generated
 */
public interface PortPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "port";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/port/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.port";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    PortPackage eINSTANCE = bip2.ujf.verimag.bip.port.impl.PortPackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.port.PortDeclaration <em>Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.port.PortDeclaration
     * @see bip2.ujf.verimag.bip.port.impl.PortPackageImpl#getPortDeclaration()
     * @generated
     */
    int PORT_DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Port Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_DECLARATION__PORT_TYPE = 0;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_DECLARATION__NAME = 1;

    /**
     * The feature id for the '<em><b>Data Parameters</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_DECLARATION__DATA_PARAMETERS = 2;

    /**
     * The number of structural features of the '<em>Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_DECLARATION_FEATURE_COUNT = 3;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.port.impl.SubPortDeclarationReferenceImpl <em>Sub Port Declaration Reference</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.port.impl.SubPortDeclarationReferenceImpl
     * @see bip2.ujf.verimag.bip.port.impl.PortPackageImpl#getSubPortDeclarationReference()
     * @generated
     */
    int SUB_PORT_DECLARATION_REFERENCE = 1;

    /**
     * The feature id for the '<em><b>Forward Port Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int SUB_PORT_DECLARATION_REFERENCE__FORWARD_PORT_DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Component Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int SUB_PORT_DECLARATION_REFERENCE__COMPONENT_DECLARATION = 1;

    /**
     * The feature id for the '<em><b>Connector Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int SUB_PORT_DECLARATION_REFERENCE__CONNECTOR_DECLARATION = 2;

    /**
     * The number of structural features of the '<em>Sub Port Declaration Reference</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int SUB_PORT_DECLARATION_REFERENCE_FEATURE_COUNT = 3;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.port.impl.PortDataParameterDeclarationImpl <em>Data Parameter Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.port.impl.PortDataParameterDeclarationImpl
     * @see bip2.ujf.verimag.bip.port.impl.PortPackageImpl#getPortDataParameterDeclaration()
     * @generated
     */
    int PORT_DATA_PARAMETER_DECLARATION = 2;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_DATA_PARAMETER_DECLARATION__BIP_ANNOTATIONS = DataPackage.DATA_DECLARATION__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Data Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_DATA_PARAMETER_DECLARATION__DATA_TYPE = DataPackage.DATA_DECLARATION__DATA_TYPE;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_DATA_PARAMETER_DECLARATION__NAME = DataPackage.DATA_DECLARATION__NAME;

    /**
     * The feature id for the '<em><b>Value</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_DATA_PARAMETER_DECLARATION__VALUE = DataPackage.DATA_DECLARATION__VALUE;

    /**
     * The feature id for the '<em><b>Const</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_DATA_PARAMETER_DECLARATION__CONST = DataPackage.DATA_DECLARATION__CONST;

    /**
     * The number of structural features of the '<em>Data Parameter Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_DATA_PARAMETER_DECLARATION_FEATURE_COUNT = DataPackage.DATA_DECLARATION_FEATURE_COUNT
            + 0;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.port.impl.PortDeclarationReferenceParameterImpl <em>Declaration Reference Parameter</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.port.impl.PortDeclarationReferenceParameterImpl
     * @see bip2.ujf.verimag.bip.port.impl.PortPackageImpl#getPortDeclarationReferenceParameter()
     * @generated
     */
    int PORT_DECLARATION_REFERENCE_PARAMETER = 3;

    /**
     * The feature id for the '<em><b>Parameter Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_DECLARATION_REFERENCE_PARAMETER__PARAMETER_DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Sub Port Declaration Reference</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_DECLARATION_REFERENCE_PARAMETER__SUB_PORT_DECLARATION_REFERENCE = 1;

    /**
     * The number of structural features of the '<em>Declaration Reference Parameter</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_DECLARATION_REFERENCE_PARAMETER_FEATURE_COUNT = 2;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.port.PortDeclaration <em>Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Declaration</em>'.
     * @see bip2.ujf.verimag.bip.port.PortDeclaration
     * @generated
     */
    EClass getPortDeclaration();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.port.PortDeclaration#getPortType <em>Port Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Port Type</em>'.
     * @see bip2.ujf.verimag.bip.port.PortDeclaration#getPortType()
     * @see #getPortDeclaration()
     * @generated
     */
    EReference getPortDeclaration_PortType();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.port.PortDeclaration#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see bip2.ujf.verimag.bip.port.PortDeclaration#getName()
     * @see #getPortDeclaration()
     * @generated
     */
    EAttribute getPortDeclaration_Name();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.port.PortDeclaration#getDataParameters <em>Data Parameters</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Data Parameters</em>'.
     * @see bip2.ujf.verimag.bip.port.PortDeclaration#getDataParameters()
     * @see #getPortDeclaration()
     * @generated
     */
    EReference getPortDeclaration_DataParameters();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.port.SubPortDeclarationReference <em>Sub Port Declaration Reference</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Sub Port Declaration Reference</em>'.
     * @see bip2.ujf.verimag.bip.port.SubPortDeclarationReference
     * @generated
     */
    EClass getSubPortDeclarationReference();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.port.SubPortDeclarationReference#getForwardPortDeclaration <em>Forward Port Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Forward Port Declaration</em>'.
     * @see bip2.ujf.verimag.bip.port.SubPortDeclarationReference#getForwardPortDeclaration()
     * @see #getSubPortDeclarationReference()
     * @generated
     */
    EReference getSubPortDeclarationReference_ForwardPortDeclaration();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.port.SubPortDeclarationReference#getComponentDeclaration <em>Component Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Component Declaration</em>'.
     * @see bip2.ujf.verimag.bip.port.SubPortDeclarationReference#getComponentDeclaration()
     * @see #getSubPortDeclarationReference()
     * @generated
     */
    EReference getSubPortDeclarationReference_ComponentDeclaration();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.port.SubPortDeclarationReference#getConnectorDeclaration <em>Connector Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Connector Declaration</em>'.
     * @see bip2.ujf.verimag.bip.port.SubPortDeclarationReference#getConnectorDeclaration()
     * @see #getSubPortDeclarationReference()
     * @generated
     */
    EReference getSubPortDeclarationReference_ConnectorDeclaration();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.port.PortDataParameterDeclaration <em>Data Parameter Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Data Parameter Declaration</em>'.
     * @see bip2.ujf.verimag.bip.port.PortDataParameterDeclaration
     * @generated
     */
    EClass getPortDataParameterDeclaration();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter <em>Declaration Reference Parameter</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Declaration Reference Parameter</em>'.
     * @see bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter
     * @generated
     */
    EClass getPortDeclarationReferenceParameter();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter#getParameterDeclaration <em>Parameter Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Parameter Declaration</em>'.
     * @see bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter#getParameterDeclaration()
     * @see #getPortDeclarationReferenceParameter()
     * @generated
     */
    EReference getPortDeclarationReferenceParameter_ParameterDeclaration();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter#getSubPortDeclarationReference <em>Sub Port Declaration Reference</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Sub Port Declaration Reference</em>'.
     * @see bip2.ujf.verimag.bip.port.PortDeclarationReferenceParameter#getSubPortDeclarationReference()
     * @see #getPortDeclarationReferenceParameter()
     * @generated
     */
    EReference getPortDeclarationReferenceParameter_SubPortDeclarationReference();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    PortFactory getPortFactory();

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
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.port.PortDeclaration <em>Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.port.PortDeclaration
         * @see bip2.ujf.verimag.bip.port.impl.PortPackageImpl#getPortDeclaration()
         * @generated
         */
        EClass PORT_DECLARATION = eINSTANCE.getPortDeclaration();

        /**
         * The meta object literal for the '<em><b>Port Type</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PORT_DECLARATION__PORT_TYPE = eINSTANCE
                .getPortDeclaration_PortType();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute PORT_DECLARATION__NAME = eINSTANCE.getPortDeclaration_Name();

        /**
         * The meta object literal for the '<em><b>Data Parameters</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PORT_DECLARATION__DATA_PARAMETERS = eINSTANCE
                .getPortDeclaration_DataParameters();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.port.impl.SubPortDeclarationReferenceImpl <em>Sub Port Declaration Reference</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.port.impl.SubPortDeclarationReferenceImpl
         * @see bip2.ujf.verimag.bip.port.impl.PortPackageImpl#getSubPortDeclarationReference()
         * @generated
         */
        EClass SUB_PORT_DECLARATION_REFERENCE = eINSTANCE
                .getSubPortDeclarationReference();

        /**
         * The meta object literal for the '<em><b>Forward Port Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference SUB_PORT_DECLARATION_REFERENCE__FORWARD_PORT_DECLARATION = eINSTANCE
                .getSubPortDeclarationReference_ForwardPortDeclaration();

        /**
         * The meta object literal for the '<em><b>Component Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference SUB_PORT_DECLARATION_REFERENCE__COMPONENT_DECLARATION = eINSTANCE
                .getSubPortDeclarationReference_ComponentDeclaration();

        /**
         * The meta object literal for the '<em><b>Connector Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference SUB_PORT_DECLARATION_REFERENCE__CONNECTOR_DECLARATION = eINSTANCE
                .getSubPortDeclarationReference_ConnectorDeclaration();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.port.impl.PortDataParameterDeclarationImpl <em>Data Parameter Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.port.impl.PortDataParameterDeclarationImpl
         * @see bip2.ujf.verimag.bip.port.impl.PortPackageImpl#getPortDataParameterDeclaration()
         * @generated
         */
        EClass PORT_DATA_PARAMETER_DECLARATION = eINSTANCE
                .getPortDataParameterDeclaration();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.port.impl.PortDeclarationReferenceParameterImpl <em>Declaration Reference Parameter</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.port.impl.PortDeclarationReferenceParameterImpl
         * @see bip2.ujf.verimag.bip.port.impl.PortPackageImpl#getPortDeclarationReferenceParameter()
         * @generated
         */
        EClass PORT_DECLARATION_REFERENCE_PARAMETER = eINSTANCE
                .getPortDeclarationReferenceParameter();

        /**
         * The meta object literal for the '<em><b>Parameter Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PORT_DECLARATION_REFERENCE_PARAMETER__PARAMETER_DECLARATION = eINSTANCE
                .getPortDeclarationReferenceParameter_ParameterDeclaration();

        /**
         * The meta object literal for the '<em><b>Sub Port Declaration Reference</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PORT_DECLARATION_REFERENCE_PARAMETER__SUB_PORT_DECLARATION_REFERENCE = eINSTANCE
                .getPortDeclarationReferenceParameter_SubPortDeclarationReference();

    }

} //PortPackage
