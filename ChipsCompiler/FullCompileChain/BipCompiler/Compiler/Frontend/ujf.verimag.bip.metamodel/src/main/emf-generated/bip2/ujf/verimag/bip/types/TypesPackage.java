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

package bip2.ujf.verimag.bip.types;

import bip2.ujf.verimag.bip.annotation.AnnotationPackage;
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
 * @see bip2.ujf.verimag.bip.types.TypesFactory
 * @model kind="package"
 * @generated
 */
public interface TypesPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "types";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/types/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.types";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    TypesPackage eINSTANCE = bip2.ujf.verimag.bip.types.impl.TypesPackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.types.impl.TypeImpl <em>Type</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.types.impl.TypeImpl
     * @see bip2.ujf.verimag.bip.types.impl.TypesPackageImpl#getType()
     * @generated
     */
    int TYPE = 0;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int TYPE__BIP_ANNOTATIONS = AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int TYPE__NAME = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT + 0;

    /**
     * The feature id for the '<em><b>Native</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int TYPE__NATIVE = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT + 1;

    /**
     * The feature id for the '<em><b>Super Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int TYPE__SUPER_TYPES = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 2;

    /**
     * The feature id for the '<em><b>Castable Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int TYPE__CASTABLE_TYPES = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 3;

    /**
     * The number of structural features of the '<em>Type</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int TYPE_FEATURE_COUNT = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 4;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.types.BipType <em>Bip Type</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.types.BipType
     * @see bip2.ujf.verimag.bip.types.impl.TypesPackageImpl#getBipType()
     * @generated
     */
    int BIP_TYPE = 1;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_TYPE__BIP_ANNOTATIONS = TYPE__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_TYPE__NAME = TYPE__NAME;

    /**
     * The feature id for the '<em><b>Native</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_TYPE__NATIVE = TYPE__NATIVE;

    /**
     * The feature id for the '<em><b>Super Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_TYPE__SUPER_TYPES = TYPE__SUPER_TYPES;

    /**
     * The feature id for the '<em><b>Castable Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_TYPE__CASTABLE_TYPES = TYPE__CASTABLE_TYPES;

    /**
     * The number of structural features of the '<em>Bip Type</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int BIP_TYPE_FEATURE_COUNT = TYPE_FEATURE_COUNT + 0;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.types.ComponentType <em>Component Type</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.types.ComponentType
     * @see bip2.ujf.verimag.bip.types.impl.TypesPackageImpl#getComponentType()
     * @generated
     */
    int COMPONENT_TYPE = 2;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_TYPE__BIP_ANNOTATIONS = BIP_TYPE__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_TYPE__NAME = BIP_TYPE__NAME;

    /**
     * The feature id for the '<em><b>Native</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_TYPE__NATIVE = BIP_TYPE__NATIVE;

    /**
     * The feature id for the '<em><b>Super Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_TYPE__SUPER_TYPES = BIP_TYPE__SUPER_TYPES;

    /**
     * The feature id for the '<em><b>Castable Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_TYPE__CASTABLE_TYPES = BIP_TYPE__CASTABLE_TYPES;

    /**
     * The feature id for the '<em><b>Exported Port Declarations</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_TYPE__EXPORTED_PORT_DECLARATIONS = BIP_TYPE_FEATURE_COUNT + 0;

    /**
     * The feature id for the '<em><b>Exported Data Declarations</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_TYPE__EXPORTED_DATA_DECLARATIONS = BIP_TYPE_FEATURE_COUNT + 1;

    /**
     * The feature id for the '<em><b>Data Parameter Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_TYPE__DATA_PARAMETER_DECLARATIONS = BIP_TYPE_FEATURE_COUNT
            + 2;

    /**
     * The number of structural features of the '<em>Component Type</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_TYPE_FEATURE_COUNT = BIP_TYPE_FEATURE_COUNT + 3;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.types.impl.AtomTypeImpl <em>Atom Type</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.types.impl.AtomTypeImpl
     * @see bip2.ujf.verimag.bip.types.impl.TypesPackageImpl#getAtomType()
     * @generated
     */
    int ATOM_TYPE = 3;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__BIP_ANNOTATIONS = COMPONENT_TYPE__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__NAME = COMPONENT_TYPE__NAME;

    /**
     * The feature id for the '<em><b>Native</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__NATIVE = COMPONENT_TYPE__NATIVE;

    /**
     * The feature id for the '<em><b>Super Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__SUPER_TYPES = COMPONENT_TYPE__SUPER_TYPES;

    /**
     * The feature id for the '<em><b>Castable Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__CASTABLE_TYPES = COMPONENT_TYPE__CASTABLE_TYPES;

    /**
     * The feature id for the '<em><b>Exported Port Declarations</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__EXPORTED_PORT_DECLARATIONS = COMPONENT_TYPE__EXPORTED_PORT_DECLARATIONS;

    /**
     * The feature id for the '<em><b>Exported Data Declarations</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__EXPORTED_DATA_DECLARATIONS = COMPONENT_TYPE__EXPORTED_DATA_DECLARATIONS;

    /**
     * The feature id for the '<em><b>Data Parameter Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__DATA_PARAMETER_DECLARATIONS = COMPONENT_TYPE__DATA_PARAMETER_DECLARATIONS;

    /**
     * The feature id for the '<em><b>Internal Port Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__INTERNAL_PORT_DECLARATIONS = COMPONENT_TYPE_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>External Port Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__EXTERNAL_PORT_DECLARATIONS = COMPONENT_TYPE_FEATURE_COUNT
            + 1;

    /**
     * The feature id for the '<em><b>Behavior</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__BEHAVIOR = COMPONENT_TYPE_FEATURE_COUNT + 2;

    /**
     * The feature id for the '<em><b>Internal Data Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__INTERNAL_DATA_DECLARATIONS = COMPONENT_TYPE_FEATURE_COUNT
            + 3;

    /**
     * The feature id for the '<em><b>Export Port Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__EXPORT_PORT_DECLARATIONS = COMPONENT_TYPE_FEATURE_COUNT + 4;

    /**
     * The feature id for the '<em><b>Priorities</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__PRIORITIES = COMPONENT_TYPE_FEATURE_COUNT + 5;

    /**
     * The feature id for the '<em><b>Invariants</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE__INVARIANTS = COMPONENT_TYPE_FEATURE_COUNT + 6;

    /**
     * The number of structural features of the '<em>Atom Type</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_TYPE_FEATURE_COUNT = COMPONENT_TYPE_FEATURE_COUNT + 7;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.types.impl.CompoundTypeImpl <em>Compound Type</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.types.impl.CompoundTypeImpl
     * @see bip2.ujf.verimag.bip.types.impl.TypesPackageImpl#getCompoundType()
     * @generated
     */
    int COMPOUND_TYPE = 4;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_TYPE__BIP_ANNOTATIONS = COMPONENT_TYPE__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_TYPE__NAME = COMPONENT_TYPE__NAME;

    /**
     * The feature id for the '<em><b>Native</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_TYPE__NATIVE = COMPONENT_TYPE__NATIVE;

    /**
     * The feature id for the '<em><b>Super Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_TYPE__SUPER_TYPES = COMPONENT_TYPE__SUPER_TYPES;

    /**
     * The feature id for the '<em><b>Castable Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_TYPE__CASTABLE_TYPES = COMPONENT_TYPE__CASTABLE_TYPES;

    /**
     * The feature id for the '<em><b>Exported Port Declarations</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_TYPE__EXPORTED_PORT_DECLARATIONS = COMPONENT_TYPE__EXPORTED_PORT_DECLARATIONS;

    /**
     * The feature id for the '<em><b>Exported Data Declarations</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_TYPE__EXPORTED_DATA_DECLARATIONS = COMPONENT_TYPE__EXPORTED_DATA_DECLARATIONS;

    /**
     * The feature id for the '<em><b>Data Parameter Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_TYPE__DATA_PARAMETER_DECLARATIONS = COMPONENT_TYPE__DATA_PARAMETER_DECLARATIONS;

    /**
     * The feature id for the '<em><b>Component Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_TYPE__COMPONENT_DECLARATIONS = COMPONENT_TYPE_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>Connector Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_TYPE__CONNECTOR_DECLARATIONS = COMPONENT_TYPE_FEATURE_COUNT
            + 1;

    /**
     * The feature id for the '<em><b>Export Port Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_TYPE__EXPORT_PORT_DECLARATIONS = COMPONENT_TYPE_FEATURE_COUNT
            + 2;

    /**
     * The feature id for the '<em><b>Export Data Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_TYPE__EXPORT_DATA_DECLARATIONS = COMPONENT_TYPE_FEATURE_COUNT
            + 3;

    /**
     * The feature id for the '<em><b>Priorities</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_TYPE__PRIORITIES = COMPONENT_TYPE_FEATURE_COUNT + 4;

    /**
     * The number of structural features of the '<em>Compound Type</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_TYPE_FEATURE_COUNT = COMPONENT_TYPE_FEATURE_COUNT + 5;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.types.impl.ConnectorTypeImpl <em>Connector Type</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.types.impl.ConnectorTypeImpl
     * @see bip2.ujf.verimag.bip.types.impl.TypesPackageImpl#getConnectorType()
     * @generated
     */
    int CONNECTOR_TYPE = 5;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_TYPE__BIP_ANNOTATIONS = BIP_TYPE__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_TYPE__NAME = BIP_TYPE__NAME;

    /**
     * The feature id for the '<em><b>Native</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_TYPE__NATIVE = BIP_TYPE__NATIVE;

    /**
     * The feature id for the '<em><b>Super Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_TYPE__SUPER_TYPES = BIP_TYPE__SUPER_TYPES;

    /**
     * The feature id for the '<em><b>Castable Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_TYPE__CASTABLE_TYPES = BIP_TYPE__CASTABLE_TYPES;

    /**
     * The feature id for the '<em><b>Exported Port Declaration</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_TYPE__EXPORTED_PORT_DECLARATION = BIP_TYPE_FEATURE_COUNT + 0;

    /**
     * The feature id for the '<em><b>Data Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_TYPE__DATA_DECLARATIONS = BIP_TYPE_FEATURE_COUNT + 1;

    /**
     * The feature id for the '<em><b>Interactions</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_TYPE__INTERACTIONS = BIP_TYPE_FEATURE_COUNT + 2;

    /**
     * The feature id for the '<em><b>Interaction Definition</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_TYPE__INTERACTION_DEFINITION = BIP_TYPE_FEATURE_COUNT + 3;

    /**
     * The feature id for the '<em><b>Ports</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_TYPE__PORTS = BIP_TYPE_FEATURE_COUNT + 4;

    /**
     * The number of structural features of the '<em>Connector Type</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_TYPE_FEATURE_COUNT = BIP_TYPE_FEATURE_COUNT + 5;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.types.impl.PortTypeImpl <em>Port Type</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.types.impl.PortTypeImpl
     * @see bip2.ujf.verimag.bip.types.impl.TypesPackageImpl#getPortType()
     * @generated
     */
    int PORT_TYPE = 6;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_TYPE__BIP_ANNOTATIONS = BIP_TYPE__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_TYPE__NAME = BIP_TYPE__NAME;

    /**
     * The feature id for the '<em><b>Native</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_TYPE__NATIVE = BIP_TYPE__NATIVE;

    /**
     * The feature id for the '<em><b>Super Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_TYPE__SUPER_TYPES = BIP_TYPE__SUPER_TYPES;

    /**
     * The feature id for the '<em><b>Castable Types</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_TYPE__CASTABLE_TYPES = BIP_TYPE__CASTABLE_TYPES;

    /**
     * The feature id for the '<em><b>Data Parameter Declarations</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_TYPE__DATA_PARAMETER_DECLARATIONS = BIP_TYPE_FEATURE_COUNT + 0;

    /**
     * The number of structural features of the '<em>Port Type</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_TYPE_FEATURE_COUNT = BIP_TYPE_FEATURE_COUNT + 1;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.types.Type <em>Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Type</em>'.
     * @see bip2.ujf.verimag.bip.types.Type
     * @generated
     */
    EClass getType();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.types.Type#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see bip2.ujf.verimag.bip.types.Type#getName()
     * @see #getType()
     * @generated
     */
    EAttribute getType_Name();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.types.Type#isNative <em>Native</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Native</em>'.
     * @see bip2.ujf.verimag.bip.types.Type#isNative()
     * @see #getType()
     * @generated
     */
    EAttribute getType_Native();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.types.Type#getSuperTypes <em>Super Types</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Super Types</em>'.
     * @see bip2.ujf.verimag.bip.types.Type#getSuperTypes()
     * @see #getType()
     * @generated
     */
    EReference getType_SuperTypes();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.types.Type#getCastableTypes <em>Castable Types</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Castable Types</em>'.
     * @see bip2.ujf.verimag.bip.types.Type#getCastableTypes()
     * @see #getType()
     * @generated
     */
    EReference getType_CastableTypes();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.types.AtomType <em>Atom Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Atom Type</em>'.
     * @see bip2.ujf.verimag.bip.types.AtomType
     * @generated
     */
    EClass getAtomType();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.AtomType#getInternalPortDeclarations <em>Internal Port Declarations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Internal Port Declarations</em>'.
     * @see bip2.ujf.verimag.bip.types.AtomType#getInternalPortDeclarations()
     * @see #getAtomType()
     * @generated
     */
    EReference getAtomType_InternalPortDeclarations();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.AtomType#getExternalPortDeclarations <em>External Port Declarations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>External Port Declarations</em>'.
     * @see bip2.ujf.verimag.bip.types.AtomType#getExternalPortDeclarations()
     * @see #getAtomType()
     * @generated
     */
    EReference getAtomType_ExternalPortDeclarations();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.types.AtomType#getBehavior <em>Behavior</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Behavior</em>'.
     * @see bip2.ujf.verimag.bip.types.AtomType#getBehavior()
     * @see #getAtomType()
     * @generated
     */
    EReference getAtomType_Behavior();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.AtomType#getInternalDataDeclarations <em>Internal Data Declarations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Internal Data Declarations</em>'.
     * @see bip2.ujf.verimag.bip.types.AtomType#getInternalDataDeclarations()
     * @see #getAtomType()
     * @generated
     */
    EReference getAtomType_InternalDataDeclarations();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.AtomType#getExportPortDeclarations <em>Export Port Declarations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Export Port Declarations</em>'.
     * @see bip2.ujf.verimag.bip.types.AtomType#getExportPortDeclarations()
     * @see #getAtomType()
     * @generated
     */
    EReference getAtomType_ExportPortDeclarations();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.AtomType#getPriorities <em>Priorities</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Priorities</em>'.
     * @see bip2.ujf.verimag.bip.types.AtomType#getPriorities()
     * @see #getAtomType()
     * @generated
     */
    EReference getAtomType_Priorities();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.AtomType#getInvariants <em>Invariants</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Invariants</em>'.
     * @see bip2.ujf.verimag.bip.types.AtomType#getInvariants()
     * @see #getAtomType()
     * @generated
     */
    EReference getAtomType_Invariants();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.types.ComponentType <em>Component Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Component Type</em>'.
     * @see bip2.ujf.verimag.bip.types.ComponentType
     * @generated
     */
    EClass getComponentType();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.types.ComponentType#getExportedPortDeclarations <em>Exported Port Declarations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Exported Port Declarations</em>'.
     * @see bip2.ujf.verimag.bip.types.ComponentType#getExportedPortDeclarations()
     * @see #getComponentType()
     * @generated
     */
    EReference getComponentType_ExportedPortDeclarations();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.types.ComponentType#getExportedDataDeclarations <em>Exported Data Declarations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Exported Data Declarations</em>'.
     * @see bip2.ujf.verimag.bip.types.ComponentType#getExportedDataDeclarations()
     * @see #getComponentType()
     * @generated
     */
    EReference getComponentType_ExportedDataDeclarations();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.ComponentType#getDataParameterDeclarations <em>Data Parameter Declarations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Data Parameter Declarations</em>'.
     * @see bip2.ujf.verimag.bip.types.ComponentType#getDataParameterDeclarations()
     * @see #getComponentType()
     * @generated
     */
    EReference getComponentType_DataParameterDeclarations();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.types.CompoundType <em>Compound Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Compound Type</em>'.
     * @see bip2.ujf.verimag.bip.types.CompoundType
     * @generated
     */
    EClass getCompoundType();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.CompoundType#getComponentDeclarations <em>Component Declarations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Component Declarations</em>'.
     * @see bip2.ujf.verimag.bip.types.CompoundType#getComponentDeclarations()
     * @see #getCompoundType()
     * @generated
     */
    EReference getCompoundType_ComponentDeclarations();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.CompoundType#getConnectorDeclarations <em>Connector Declarations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Connector Declarations</em>'.
     * @see bip2.ujf.verimag.bip.types.CompoundType#getConnectorDeclarations()
     * @see #getCompoundType()
     * @generated
     */
    EReference getCompoundType_ConnectorDeclarations();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.CompoundType#getExportPortDeclarations <em>Export Port Declarations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Export Port Declarations</em>'.
     * @see bip2.ujf.verimag.bip.types.CompoundType#getExportPortDeclarations()
     * @see #getCompoundType()
     * @generated
     */
    EReference getCompoundType_ExportPortDeclarations();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.CompoundType#getExportDataDeclarations <em>Export Data Declarations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Export Data Declarations</em>'.
     * @see bip2.ujf.verimag.bip.types.CompoundType#getExportDataDeclarations()
     * @see #getCompoundType()
     * @generated
     */
    EReference getCompoundType_ExportDataDeclarations();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.CompoundType#getPriorities <em>Priorities</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Priorities</em>'.
     * @see bip2.ujf.verimag.bip.types.CompoundType#getPriorities()
     * @see #getCompoundType()
     * @generated
     */
    EReference getCompoundType_Priorities();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.types.ConnectorType <em>Connector Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Connector Type</em>'.
     * @see bip2.ujf.verimag.bip.types.ConnectorType
     * @generated
     */
    EClass getConnectorType();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.types.ConnectorType#getExportedPortDeclaration <em>Exported Port Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Exported Port Declaration</em>'.
     * @see bip2.ujf.verimag.bip.types.ConnectorType#getExportedPortDeclaration()
     * @see #getConnectorType()
     * @generated
     */
    EReference getConnectorType_ExportedPortDeclaration();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.ConnectorType#getDataDeclarations <em>Data Declarations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Data Declarations</em>'.
     * @see bip2.ujf.verimag.bip.types.ConnectorType#getDataDeclarations()
     * @see #getConnectorType()
     * @generated
     */
    EReference getConnectorType_DataDeclarations();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.ConnectorType#getInteractions <em>Interactions</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Interactions</em>'.
     * @see bip2.ujf.verimag.bip.types.ConnectorType#getInteractions()
     * @see #getConnectorType()
     * @generated
     */
    EReference getConnectorType_Interactions();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.types.ConnectorType#getInteractionDefinition <em>Interaction Definition</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Interaction Definition</em>'.
     * @see bip2.ujf.verimag.bip.types.ConnectorType#getInteractionDefinition()
     * @see #getConnectorType()
     * @generated
     */
    EReference getConnectorType_InteractionDefinition();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.ConnectorType#getPorts <em>Ports</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Ports</em>'.
     * @see bip2.ujf.verimag.bip.types.ConnectorType#getPorts()
     * @see #getConnectorType()
     * @generated
     */
    EReference getConnectorType_Ports();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.types.PortType <em>Port Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Port Type</em>'.
     * @see bip2.ujf.verimag.bip.types.PortType
     * @generated
     */
    EClass getPortType();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.types.PortType#getDataParameterDeclarations <em>Data Parameter Declarations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Data Parameter Declarations</em>'.
     * @see bip2.ujf.verimag.bip.types.PortType#getDataParameterDeclarations()
     * @see #getPortType()
     * @generated
     */
    EReference getPortType_DataParameterDeclarations();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.types.BipType <em>Bip Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Bip Type</em>'.
     * @see bip2.ujf.verimag.bip.types.BipType
     * @generated
     */
    EClass getBipType();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    TypesFactory getTypesFactory();

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
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.types.impl.TypeImpl <em>Type</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.types.impl.TypeImpl
         * @see bip2.ujf.verimag.bip.types.impl.TypesPackageImpl#getType()
         * @generated
         */
        EClass TYPE = eINSTANCE.getType();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute TYPE__NAME = eINSTANCE.getType_Name();

        /**
         * The meta object literal for the '<em><b>Native</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute TYPE__NATIVE = eINSTANCE.getType_Native();

        /**
         * The meta object literal for the '<em><b>Super Types</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference TYPE__SUPER_TYPES = eINSTANCE.getType_SuperTypes();

        /**
         * The meta object literal for the '<em><b>Castable Types</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference TYPE__CASTABLE_TYPES = eINSTANCE.getType_CastableTypes();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.types.impl.AtomTypeImpl <em>Atom Type</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.types.impl.AtomTypeImpl
         * @see bip2.ujf.verimag.bip.types.impl.TypesPackageImpl#getAtomType()
         * @generated
         */
        EClass ATOM_TYPE = eINSTANCE.getAtomType();

        /**
         * The meta object literal for the '<em><b>Internal Port Declarations</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_TYPE__INTERNAL_PORT_DECLARATIONS = eINSTANCE
                .getAtomType_InternalPortDeclarations();

        /**
         * The meta object literal for the '<em><b>External Port Declarations</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_TYPE__EXTERNAL_PORT_DECLARATIONS = eINSTANCE
                .getAtomType_ExternalPortDeclarations();

        /**
         * The meta object literal for the '<em><b>Behavior</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_TYPE__BEHAVIOR = eINSTANCE.getAtomType_Behavior();

        /**
         * The meta object literal for the '<em><b>Internal Data Declarations</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_TYPE__INTERNAL_DATA_DECLARATIONS = eINSTANCE
                .getAtomType_InternalDataDeclarations();

        /**
         * The meta object literal for the '<em><b>Export Port Declarations</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_TYPE__EXPORT_PORT_DECLARATIONS = eINSTANCE
                .getAtomType_ExportPortDeclarations();

        /**
         * The meta object literal for the '<em><b>Priorities</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_TYPE__PRIORITIES = eINSTANCE.getAtomType_Priorities();

        /**
         * The meta object literal for the '<em><b>Invariants</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_TYPE__INVARIANTS = eINSTANCE.getAtomType_Invariants();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.types.ComponentType <em>Component Type</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.types.ComponentType
         * @see bip2.ujf.verimag.bip.types.impl.TypesPackageImpl#getComponentType()
         * @generated
         */
        EClass COMPONENT_TYPE = eINSTANCE.getComponentType();

        /**
         * The meta object literal for the '<em><b>Exported Port Declarations</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPONENT_TYPE__EXPORTED_PORT_DECLARATIONS = eINSTANCE
                .getComponentType_ExportedPortDeclarations();

        /**
         * The meta object literal for the '<em><b>Exported Data Declarations</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPONENT_TYPE__EXPORTED_DATA_DECLARATIONS = eINSTANCE
                .getComponentType_ExportedDataDeclarations();

        /**
         * The meta object literal for the '<em><b>Data Parameter Declarations</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPONENT_TYPE__DATA_PARAMETER_DECLARATIONS = eINSTANCE
                .getComponentType_DataParameterDeclarations();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.types.impl.CompoundTypeImpl <em>Compound Type</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.types.impl.CompoundTypeImpl
         * @see bip2.ujf.verimag.bip.types.impl.TypesPackageImpl#getCompoundType()
         * @generated
         */
        EClass COMPOUND_TYPE = eINSTANCE.getCompoundType();

        /**
         * The meta object literal for the '<em><b>Component Declarations</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_TYPE__COMPONENT_DECLARATIONS = eINSTANCE
                .getCompoundType_ComponentDeclarations();

        /**
         * The meta object literal for the '<em><b>Connector Declarations</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_TYPE__CONNECTOR_DECLARATIONS = eINSTANCE
                .getCompoundType_ConnectorDeclarations();

        /**
         * The meta object literal for the '<em><b>Export Port Declarations</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_TYPE__EXPORT_PORT_DECLARATIONS = eINSTANCE
                .getCompoundType_ExportPortDeclarations();

        /**
         * The meta object literal for the '<em><b>Export Data Declarations</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_TYPE__EXPORT_DATA_DECLARATIONS = eINSTANCE
                .getCompoundType_ExportDataDeclarations();

        /**
         * The meta object literal for the '<em><b>Priorities</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_TYPE__PRIORITIES = eINSTANCE
                .getCompoundType_Priorities();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.types.impl.ConnectorTypeImpl <em>Connector Type</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.types.impl.ConnectorTypeImpl
         * @see bip2.ujf.verimag.bip.types.impl.TypesPackageImpl#getConnectorType()
         * @generated
         */
        EClass CONNECTOR_TYPE = eINSTANCE.getConnectorType();

        /**
         * The meta object literal for the '<em><b>Exported Port Declaration</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_TYPE__EXPORTED_PORT_DECLARATION = eINSTANCE
                .getConnectorType_ExportedPortDeclaration();

        /**
         * The meta object literal for the '<em><b>Data Declarations</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_TYPE__DATA_DECLARATIONS = eINSTANCE
                .getConnectorType_DataDeclarations();

        /**
         * The meta object literal for the '<em><b>Interactions</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_TYPE__INTERACTIONS = eINSTANCE
                .getConnectorType_Interactions();

        /**
         * The meta object literal for the '<em><b>Interaction Definition</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_TYPE__INTERACTION_DEFINITION = eINSTANCE
                .getConnectorType_InteractionDefinition();

        /**
         * The meta object literal for the '<em><b>Ports</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_TYPE__PORTS = eINSTANCE.getConnectorType_Ports();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.types.impl.PortTypeImpl <em>Port Type</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.types.impl.PortTypeImpl
         * @see bip2.ujf.verimag.bip.types.impl.TypesPackageImpl#getPortType()
         * @generated
         */
        EClass PORT_TYPE = eINSTANCE.getPortType();

        /**
         * The meta object literal for the '<em><b>Data Parameter Declarations</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PORT_TYPE__DATA_PARAMETER_DECLARATIONS = eINSTANCE
                .getPortType_DataParameterDeclarations();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.types.BipType <em>Bip Type</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.types.BipType
         * @see bip2.ujf.verimag.bip.types.impl.TypesPackageImpl#getBipType()
         * @generated
         */
        EClass BIP_TYPE = eINSTANCE.getBipType();

    }

} //TypesPackage
