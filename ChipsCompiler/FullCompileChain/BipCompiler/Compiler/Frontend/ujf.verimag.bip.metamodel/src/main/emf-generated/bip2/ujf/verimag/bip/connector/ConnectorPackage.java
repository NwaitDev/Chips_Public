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

package bip2.ujf.verimag.bip.connector;

import bip2.ujf.verimag.bip.annotation.AnnotationPackage;
import bip2.ujf.verimag.bip.data.DataPackage;

import bip2.ujf.verimag.bip.port.PortPackage;

import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EDataType;
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
 * @see bip2.ujf.verimag.bip.connector.ConnectorFactory
 * @model kind="package"
 * @generated
 */
public interface ConnectorPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "connector";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/connector/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.connector";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    ConnectorPackage eINSTANCE = bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorDeclarationImpl <em>Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorDeclarationImpl
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorDeclaration()
     * @generated
     */
    int CONNECTOR_DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_DECLARATION__BIP_ANNOTATIONS = AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_DECLARATION__TYPE = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>Port Parameters</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_DECLARATION__PORT_PARAMETERS = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 1;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_DECLARATION__NAME = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 2;

    /**
     * The number of structural features of the '<em>Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_DECLARATION_FEATURE_COUNT = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 3;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorPortParameterDeclarationImpl <em>Port Parameter Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPortParameterDeclarationImpl
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorPortParameterDeclaration()
     * @generated
     */
    int CONNECTOR_PORT_PARAMETER_DECLARATION = 1;

    /**
     * The feature id for the '<em><b>Port Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_PORT_PARAMETER_DECLARATION__PORT_TYPE = PortPackage.PORT_DECLARATION__PORT_TYPE;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_PORT_PARAMETER_DECLARATION__NAME = PortPackage.PORT_DECLARATION__NAME;

    /**
     * The feature id for the '<em><b>Data Parameters</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_PORT_PARAMETER_DECLARATION__DATA_PARAMETERS = PortPackage.PORT_DECLARATION__DATA_PARAMETERS;

    /**
     * The number of structural features of the '<em>Port Parameter Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_PORT_PARAMETER_DECLARATION_FEATURE_COUNT = PortPackage.PORT_DECLARATION_FEATURE_COUNT
            + 0;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorExportedPortDeclarationImpl <em>Exported Port Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorExportedPortDeclarationImpl
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorExportedPortDeclaration()
     * @generated
     */
    int CONNECTOR_EXPORTED_PORT_DECLARATION = 2;

    /**
     * The feature id for the '<em><b>Port Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_EXPORTED_PORT_DECLARATION__PORT_TYPE = PortPackage.PORT_DECLARATION__PORT_TYPE;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_EXPORTED_PORT_DECLARATION__NAME = PortPackage.PORT_DECLARATION__NAME;

    /**
     * The feature id for the '<em><b>Data Parameters</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_EXPORTED_PORT_DECLARATION__DATA_PARAMETERS = PortPackage.PORT_DECLARATION__DATA_PARAMETERS;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_EXPORTED_PORT_DECLARATION__BIP_ANNOTATIONS = PortPackage.PORT_DECLARATION_FEATURE_COUNT
            + 0;

    /**
     * The number of structural features of the '<em>Exported Port Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_EXPORTED_PORT_DECLARATION_FEATURE_COUNT = PortPackage.PORT_DECLARATION_FEATURE_COUNT
            + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorDataDeclarationImpl <em>Data Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorDataDeclarationImpl
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorDataDeclaration()
     * @generated
     */
    int CONNECTOR_DATA_DECLARATION = 3;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_DATA_DECLARATION__BIP_ANNOTATIONS = DataPackage.EXPLICIT_DATA_DECLARATION__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Data Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_DATA_DECLARATION__DATA_TYPE = DataPackage.EXPLICIT_DATA_DECLARATION__DATA_TYPE;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_DATA_DECLARATION__NAME = DataPackage.EXPLICIT_DATA_DECLARATION__NAME;

    /**
     * The feature id for the '<em><b>Value</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_DATA_DECLARATION__VALUE = DataPackage.EXPLICIT_DATA_DECLARATION__VALUE;

    /**
     * The feature id for the '<em><b>Const</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_DATA_DECLARATION__CONST = DataPackage.EXPLICIT_DATA_DECLARATION__CONST;

    /**
     * The number of structural features of the '<em>Data Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_DATA_DECLARATION_FEATURE_COUNT = DataPackage.EXPLICIT_DATA_DECLARATION_FEATURE_COUNT
            + 0;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionActionImpl <em>Interaction Action</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionActionImpl
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorInteractionAction()
     * @generated
     */
    int CONNECTOR_INTERACTION_ACTION = 4;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_ACTION__BIP_ANNOTATIONS = AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>On Ports</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_ACTION__ON_PORTS = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>Up</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_ACTION__UP = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 1;

    /**
     * The feature id for the '<em><b>Down</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_ACTION__DOWN = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 2;

    /**
     * The feature id for the '<em><b>Guard</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_ACTION__GUARD = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 3;

    /**
     * The number of structural features of the '<em>Interaction Action</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_ACTION_FEATURE_COUNT = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 4;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionDefinitionImpl <em>Interaction Definition</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionDefinitionImpl
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorInteractionDefinition()
     * @generated
     */
    int CONNECTOR_INTERACTION_DEFINITION = 5;

    /**
     * The feature id for the '<em><b>Quoted</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_DEFINITION__QUOTED = 0;

    /**
     * The number of structural features of the '<em>Interaction Definition</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_DEFINITION_FEATURE_COUNT = 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionPortReferenceImpl <em>Interaction Port Reference</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionPortReferenceImpl
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorInteractionPortReference()
     * @generated
     */
    int CONNECTOR_INTERACTION_PORT_REFERENCE = 6;

    /**
     * The feature id for the '<em><b>Quoted</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_PORT_REFERENCE__QUOTED = CONNECTOR_INTERACTION_DEFINITION__QUOTED;

    /**
     * The feature id for the '<em><b>Port</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_PORT_REFERENCE__PORT = CONNECTOR_INTERACTION_DEFINITION_FEATURE_COUNT
            + 0;

    /**
     * The number of structural features of the '<em>Interaction Port Reference</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_PORT_REFERENCE_FEATURE_COUNT = CONNECTOR_INTERACTION_DEFINITION_FEATURE_COUNT
            + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionNestedDefinitionImpl <em>Interaction Nested Definition</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionNestedDefinitionImpl
     * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorInteractionNestedDefinition()
     * @generated
     */
    int CONNECTOR_INTERACTION_NESTED_DEFINITION = 7;

    /**
     * The feature id for the '<em><b>Quoted</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_NESTED_DEFINITION__QUOTED = CONNECTOR_INTERACTION_DEFINITION__QUOTED;

    /**
     * The feature id for the '<em><b>Sub Interactions</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_NESTED_DEFINITION__SUB_INTERACTIONS = CONNECTOR_INTERACTION_DEFINITION_FEATURE_COUNT
            + 0;

    /**
     * The number of structural features of the '<em>Interaction Nested Definition</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_NESTED_DEFINITION_FEATURE_COUNT = CONNECTOR_INTERACTION_DEFINITION_FEATURE_COUNT
            + 1;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.connector.ConnectorDeclaration <em>Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Declaration</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorDeclaration
     * @generated
     */
    EClass getConnectorDeclaration();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.connector.ConnectorDeclaration#getType <em>Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Type</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorDeclaration#getType()
     * @see #getConnectorDeclaration()
     * @generated
     */
    EReference getConnectorDeclaration_Type();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.connector.ConnectorDeclaration#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorDeclaration#getName()
     * @see #getConnectorDeclaration()
     * @generated
     */
    EAttribute getConnectorDeclaration_Name();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.connector.ConnectorDeclaration#getPortParameters <em>Port Parameters</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Port Parameters</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorDeclaration#getPortParameters()
     * @see #getConnectorDeclaration()
     * @generated
     */
    EReference getConnectorDeclaration_PortParameters();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration <em>Port Parameter Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Port Parameter Declaration</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration
     * @generated
     */
    EClass getConnectorPortParameterDeclaration();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.connector.ConnectorExportedPortDeclaration <em>Exported Port Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Exported Port Declaration</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorExportedPortDeclaration
     * @generated
     */
    EClass getConnectorExportedPortDeclaration();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.connector.ConnectorDataDeclaration <em>Data Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Data Declaration</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorDataDeclaration
     * @generated
     */
    EClass getConnectorDataDeclaration();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionAction <em>Interaction Action</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Interaction Action</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionAction
     * @generated
     */
    EClass getConnectorInteractionAction();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionAction#getOnPorts <em>On Ports</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>On Ports</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionAction#getOnPorts()
     * @see #getConnectorInteractionAction()
     * @generated
     */
    EReference getConnectorInteractionAction_OnPorts();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionAction#getGuard <em>Guard</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Guard</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionAction#getGuard()
     * @see #getConnectorInteractionAction()
     * @generated
     */
    EReference getConnectorInteractionAction_Guard();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionAction#getUp <em>Up</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Up</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionAction#getUp()
     * @see #getConnectorInteractionAction()
     * @generated
     */
    EReference getConnectorInteractionAction_Up();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionAction#getDown <em>Down</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Down</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionAction#getDown()
     * @see #getConnectorInteractionAction()
     * @generated
     */
    EReference getConnectorInteractionAction_Down();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition <em>Interaction Definition</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Interaction Definition</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition
     * @generated
     */
    EClass getConnectorInteractionDefinition();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition#isQuoted <em>Quoted</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Quoted</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition#isQuoted()
     * @see #getConnectorInteractionDefinition()
     * @generated
     */
    EAttribute getConnectorInteractionDefinition_Quoted();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference <em>Interaction Port Reference</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Interaction Port Reference</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference
     * @generated
     */
    EClass getConnectorInteractionPortReference();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference#getPort <em>Port</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Port</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference#getPort()
     * @see #getConnectorInteractionPortReference()
     * @generated
     */
    EReference getConnectorInteractionPortReference_Port();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionNestedDefinition <em>Interaction Nested Definition</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Interaction Nested Definition</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionNestedDefinition
     * @generated
     */
    EClass getConnectorInteractionNestedDefinition();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.connector.ConnectorInteractionNestedDefinition#getSubInteractions <em>Sub Interactions</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Sub Interactions</em>'.
     * @see bip2.ujf.verimag.bip.connector.ConnectorInteractionNestedDefinition#getSubInteractions()
     * @see #getConnectorInteractionNestedDefinition()
     * @generated
     */
    EReference getConnectorInteractionNestedDefinition_SubInteractions();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    ConnectorFactory getConnectorFactory();

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
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorDeclarationImpl <em>Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorDeclarationImpl
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorDeclaration()
         * @generated
         */
        EClass CONNECTOR_DECLARATION = eINSTANCE.getConnectorDeclaration();

        /**
         * The meta object literal for the '<em><b>Type</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_DECLARATION__TYPE = eINSTANCE
                .getConnectorDeclaration_Type();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute CONNECTOR_DECLARATION__NAME = eINSTANCE
                .getConnectorDeclaration_Name();

        /**
         * The meta object literal for the '<em><b>Port Parameters</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_DECLARATION__PORT_PARAMETERS = eINSTANCE
                .getConnectorDeclaration_PortParameters();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorPortParameterDeclarationImpl <em>Port Parameter Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPortParameterDeclarationImpl
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorPortParameterDeclaration()
         * @generated
         */
        EClass CONNECTOR_PORT_PARAMETER_DECLARATION = eINSTANCE
                .getConnectorPortParameterDeclaration();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorExportedPortDeclarationImpl <em>Exported Port Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorExportedPortDeclarationImpl
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorExportedPortDeclaration()
         * @generated
         */
        EClass CONNECTOR_EXPORTED_PORT_DECLARATION = eINSTANCE
                .getConnectorExportedPortDeclaration();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorDataDeclarationImpl <em>Data Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorDataDeclarationImpl
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorDataDeclaration()
         * @generated
         */
        EClass CONNECTOR_DATA_DECLARATION = eINSTANCE
                .getConnectorDataDeclaration();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionActionImpl <em>Interaction Action</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionActionImpl
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorInteractionAction()
         * @generated
         */
        EClass CONNECTOR_INTERACTION_ACTION = eINSTANCE
                .getConnectorInteractionAction();

        /**
         * The meta object literal for the '<em><b>On Ports</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_INTERACTION_ACTION__ON_PORTS = eINSTANCE
                .getConnectorInteractionAction_OnPorts();

        /**
         * The meta object literal for the '<em><b>Guard</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_INTERACTION_ACTION__GUARD = eINSTANCE
                .getConnectorInteractionAction_Guard();

        /**
         * The meta object literal for the '<em><b>Up</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_INTERACTION_ACTION__UP = eINSTANCE
                .getConnectorInteractionAction_Up();

        /**
         * The meta object literal for the '<em><b>Down</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_INTERACTION_ACTION__DOWN = eINSTANCE
                .getConnectorInteractionAction_Down();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionDefinitionImpl <em>Interaction Definition</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionDefinitionImpl
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorInteractionDefinition()
         * @generated
         */
        EClass CONNECTOR_INTERACTION_DEFINITION = eINSTANCE
                .getConnectorInteractionDefinition();

        /**
         * The meta object literal for the '<em><b>Quoted</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute CONNECTOR_INTERACTION_DEFINITION__QUOTED = eINSTANCE
                .getConnectorInteractionDefinition_Quoted();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionPortReferenceImpl <em>Interaction Port Reference</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionPortReferenceImpl
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorInteractionPortReference()
         * @generated
         */
        EClass CONNECTOR_INTERACTION_PORT_REFERENCE = eINSTANCE
                .getConnectorInteractionPortReference();

        /**
         * The meta object literal for the '<em><b>Port</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_INTERACTION_PORT_REFERENCE__PORT = eINSTANCE
                .getConnectorInteractionPortReference_Port();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionNestedDefinitionImpl <em>Interaction Nested Definition</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorInteractionNestedDefinitionImpl
         * @see bip2.ujf.verimag.bip.connector.impl.ConnectorPackageImpl#getConnectorInteractionNestedDefinition()
         * @generated
         */
        EClass CONNECTOR_INTERACTION_NESTED_DEFINITION = eINSTANCE
                .getConnectorInteractionNestedDefinition();

        /**
         * The meta object literal for the '<em><b>Sub Interactions</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_INTERACTION_NESTED_DEFINITION__SUB_INTERACTIONS = eINSTANCE
                .getConnectorInteractionNestedDefinition_SubInteractions();

    }

} //ConnectorPackage
