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

package bip2.ujf.verimag.bip.instance;

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
 * @see bip2.ujf.verimag.bip.instance.InstanceFactory
 * @model kind="package"
 * @generated
 */
public interface InstancePackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "instance";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/instance/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.instance";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    InstancePackage eINSTANCE = bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.instance.impl.ConnectorInstanceImpl <em>Connector Instance</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.instance.impl.ConnectorInstanceImpl
     * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getConnectorInstance()
     * @generated
     */
    int CONNECTOR_INSTANCE = 0;

    /**
     * The feature id for the '<em><b>Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INSTANCE__DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Sub Data Instances</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INSTANCE__SUB_DATA_INSTANCES = 1;

    /**
     * The feature id for the '<em><b>Port Param Instances</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INSTANCE__PORT_PARAM_INSTANCES = 2;

    /**
     * The feature id for the '<em><b>Exported Port</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INSTANCE__EXPORTED_PORT = 3;

    /**
     * The number of structural features of the '<em>Connector Instance</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INSTANCE_FEATURE_COUNT = 4;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.instance.PortInstance <em>Port Instance</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.instance.PortInstance
     * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getPortInstance()
     * @generated
     */
    int PORT_INSTANCE = 6;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.instance.impl.ExportedPortInstanceImpl <em>Exported Port Instance</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.instance.impl.ExportedPortInstanceImpl
     * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getExportedPortInstance()
     * @generated
     */
    int EXPORTED_PORT_INSTANCE = 7;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.instance.impl.AtomInternalPortInstanceImpl <em>Atom Internal Port Instance</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.instance.impl.AtomInternalPortInstanceImpl
     * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getAtomInternalPortInstance()
     * @generated
     */
    int ATOM_INTERNAL_PORT_INSTANCE = 8;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.instance.impl.ConnectorPortInstanceImpl <em>Connector Port Instance</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.instance.impl.ConnectorPortInstanceImpl
     * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getConnectorPortInstance()
     * @generated
     */
    int CONNECTOR_PORT_INSTANCE = 10;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.instance.impl.DataInstanceImpl <em>Data Instance</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.instance.impl.DataInstanceImpl
     * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getDataInstance()
     * @generated
     */
    int DATA_INSTANCE = 1;

    /**
     * The feature id for the '<em><b>Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_INSTANCE__DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Proxy Link</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_INSTANCE__PROXY_LINK = 1;

    /**
     * The number of structural features of the '<em>Data Instance</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int DATA_INSTANCE_FEATURE_COUNT = 2;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.instance.impl.CompoundPriorityInstanceImpl <em>Compound Priority Instance</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.instance.impl.CompoundPriorityInstanceImpl
     * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getCompoundPriorityInstance()
     * @generated
     */
    int COMPOUND_PRIORITY_INSTANCE = 2;

    /**
     * The feature id for the '<em><b>Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_PRIORITY_INSTANCE__DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Low Connector</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_PRIORITY_INSTANCE__LOW_CONNECTOR = 1;

    /**
     * The feature id for the '<em><b>High Connector</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_PRIORITY_INSTANCE__HIGH_CONNECTOR = 2;

    /**
     * The feature id for the '<em><b>Low Ports</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_PRIORITY_INSTANCE__LOW_PORTS = 3;

    /**
     * The feature id for the '<em><b>High Ports</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_PRIORITY_INSTANCE__HIGH_PORTS = 4;

    /**
     * The number of structural features of the '<em>Compound Priority Instance</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_PRIORITY_INSTANCE_FEATURE_COUNT = 5;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.instance.ComponentInstance <em>Component Instance</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.instance.ComponentInstance
     * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getComponentInstance()
     * @generated
     */
    int COMPONENT_INSTANCE = 5;

    /**
     * The feature id for the '<em><b>Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_INSTANCE__DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Exported Ports</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_INSTANCE__EXPORTED_PORTS = 1;

    /**
     * The number of structural features of the '<em>Component Instance</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPONENT_INSTANCE_FEATURE_COUNT = 2;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.instance.impl.AtomInstanceImpl <em>Atom Instance</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.instance.impl.AtomInstanceImpl
     * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getAtomInstance()
     * @generated
     */
    int ATOM_INSTANCE = 3;

    /**
     * The feature id for the '<em><b>Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INSTANCE__DECLARATION = COMPONENT_INSTANCE__DECLARATION;

    /**
     * The feature id for the '<em><b>Exported Ports</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INSTANCE__EXPORTED_PORTS = COMPONENT_INSTANCE__EXPORTED_PORTS;

    /**
     * The feature id for the '<em><b>Sub Data Instances</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INSTANCE__SUB_DATA_INSTANCES = COMPONENT_INSTANCE_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>Internal Ports</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INSTANCE__INTERNAL_PORTS = COMPONENT_INSTANCE_FEATURE_COUNT + 1;

    /**
     * The feature id for the '<em><b>External Ports</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INSTANCE__EXTERNAL_PORTS = COMPONENT_INSTANCE_FEATURE_COUNT + 2;

    /**
     * The number of structural features of the '<em>Atom Instance</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INSTANCE_FEATURE_COUNT = COMPONENT_INSTANCE_FEATURE_COUNT + 3;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.instance.impl.CompoundInstanceImpl <em>Compound Instance</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.instance.impl.CompoundInstanceImpl
     * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getCompoundInstance()
     * @generated
     */
    int COMPOUND_INSTANCE = 4;

    /**
     * The feature id for the '<em><b>Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_INSTANCE__DECLARATION = COMPONENT_INSTANCE__DECLARATION;

    /**
     * The feature id for the '<em><b>Exported Ports</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_INSTANCE__EXPORTED_PORTS = COMPONENT_INSTANCE__EXPORTED_PORTS;

    /**
     * The feature id for the '<em><b>Sub Priorities</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_INSTANCE__SUB_PRIORITIES = COMPONENT_INSTANCE_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>Sub Connector Instances</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_INSTANCE__SUB_CONNECTOR_INSTANCES = COMPONENT_INSTANCE_FEATURE_COUNT
            + 1;

    /**
     * The feature id for the '<em><b>Sub Atom Instances</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_INSTANCE__SUB_ATOM_INSTANCES = COMPONENT_INSTANCE_FEATURE_COUNT
            + 2;

    /**
     * The feature id for the '<em><b>Sub Compound Instances</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_INSTANCE__SUB_COMPOUND_INSTANCES = COMPONENT_INSTANCE_FEATURE_COUNT
            + 3;

    /**
     * The feature id for the '<em><b>Sub Data Instances</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_INSTANCE__SUB_DATA_INSTANCES = COMPONENT_INSTANCE_FEATURE_COUNT
            + 4;

    /**
     * The number of structural features of the '<em>Compound Instance</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_INSTANCE_FEATURE_COUNT = COMPONENT_INSTANCE_FEATURE_COUNT + 5;

    /**
     * The feature id for the '<em><b>Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_INSTANCE__DECLARATION = 0;

    /**
     * The number of structural features of the '<em>Port Instance</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PORT_INSTANCE_FEATURE_COUNT = 1;

    /**
     * The feature id for the '<em><b>Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int EXPORTED_PORT_INSTANCE__DECLARATION = PORT_INSTANCE__DECLARATION;

    /**
     * The feature id for the '<em><b>Referenced Ports</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int EXPORTED_PORT_INSTANCE__REFERENCED_PORTS = PORT_INSTANCE_FEATURE_COUNT
            + 0;

    /**
     * The number of structural features of the '<em>Exported Port Instance</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int EXPORTED_PORT_INSTANCE_FEATURE_COUNT = PORT_INSTANCE_FEATURE_COUNT + 1;

    /**
     * The feature id for the '<em><b>Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_PORT_INSTANCE__DECLARATION = PORT_INSTANCE__DECLARATION;

    /**
     * The feature id for the '<em><b>Data Param Instances</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_PORT_INSTANCE__DATA_PARAM_INSTANCES = PORT_INSTANCE_FEATURE_COUNT
            + 0;

    /**
     * The number of structural features of the '<em>Atom Internal Port Instance</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_PORT_INSTANCE_FEATURE_COUNT = PORT_INSTANCE_FEATURE_COUNT
            + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.instance.impl.AtomExternalPortInstanceImpl <em>Atom External Port Instance</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.instance.impl.AtomExternalPortInstanceImpl
     * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getAtomExternalPortInstance()
     * @generated
     */
    int ATOM_EXTERNAL_PORT_INSTANCE = 9;

    /**
     * The feature id for the '<em><b>Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXTERNAL_PORT_INSTANCE__DECLARATION = PORT_INSTANCE__DECLARATION;

    /**
     * The feature id for the '<em><b>Data Param Instances</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXTERNAL_PORT_INSTANCE__DATA_PARAM_INSTANCES = PORT_INSTANCE_FEATURE_COUNT
            + 0;

    /**
     * The number of structural features of the '<em>Atom External Port Instance</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXTERNAL_PORT_INSTANCE_FEATURE_COUNT = PORT_INSTANCE_FEATURE_COUNT
            + 1;

    /**
     * The feature id for the '<em><b>Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_PORT_INSTANCE__DECLARATION = PORT_INSTANCE__DECLARATION;

    /**
     * The feature id for the '<em><b>Data Param Instances</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_PORT_INSTANCE__DATA_PARAM_INSTANCES = PORT_INSTANCE_FEATURE_COUNT
            + 0;

    /**
     * The number of structural features of the '<em>Connector Port Instance</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_PORT_INSTANCE_FEATURE_COUNT = PORT_INSTANCE_FEATURE_COUNT + 1;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.instance.ConnectorInstance <em>Connector Instance</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Connector Instance</em>'.
     * @see bip2.ujf.verimag.bip.instance.ConnectorInstance
     * @generated
     */
    EClass getConnectorInstance();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.instance.ConnectorInstance#getDeclaration <em>Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Declaration</em>'.
     * @see bip2.ujf.verimag.bip.instance.ConnectorInstance#getDeclaration()
     * @see #getConnectorInstance()
     * @generated
     */
    EReference getConnectorInstance_Declaration();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.instance.ConnectorInstance#getSubDataInstances <em>Sub Data Instances</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Sub Data Instances</em>'.
     * @see bip2.ujf.verimag.bip.instance.ConnectorInstance#getSubDataInstances()
     * @see #getConnectorInstance()
     * @generated
     */
    EReference getConnectorInstance_SubDataInstances();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.instance.ConnectorInstance#getPortParamInstances <em>Port Param Instances</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Port Param Instances</em>'.
     * @see bip2.ujf.verimag.bip.instance.ConnectorInstance#getPortParamInstances()
     * @see #getConnectorInstance()
     * @generated
     */
    EReference getConnectorInstance_PortParamInstances();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.instance.ConnectorInstance#getExportedPort <em>Exported Port</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Exported Port</em>'.
     * @see bip2.ujf.verimag.bip.instance.ConnectorInstance#getExportedPort()
     * @see #getConnectorInstance()
     * @generated
     */
    EReference getConnectorInstance_ExportedPort();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.instance.PortInstance <em>Port Instance</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Port Instance</em>'.
     * @see bip2.ujf.verimag.bip.instance.PortInstance
     * @generated
     */
    EClass getPortInstance();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.instance.PortInstance#getDeclaration <em>Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Declaration</em>'.
     * @see bip2.ujf.verimag.bip.instance.PortInstance#getDeclaration()
     * @see #getPortInstance()
     * @generated
     */
    EReference getPortInstance_Declaration();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.instance.ExportedPortInstance <em>Exported Port Instance</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Exported Port Instance</em>'.
     * @see bip2.ujf.verimag.bip.instance.ExportedPortInstance
     * @generated
     */
    EClass getExportedPortInstance();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.instance.ExportedPortInstance#getReferencedPorts <em>Referenced Ports</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Referenced Ports</em>'.
     * @see bip2.ujf.verimag.bip.instance.ExportedPortInstance#getReferencedPorts()
     * @see #getExportedPortInstance()
     * @generated
     */
    EReference getExportedPortInstance_ReferencedPorts();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.instance.AtomInternalPortInstance <em>Atom Internal Port Instance</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Atom Internal Port Instance</em>'.
     * @see bip2.ujf.verimag.bip.instance.AtomInternalPortInstance
     * @generated
     */
    EClass getAtomInternalPortInstance();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.instance.AtomInternalPortInstance#getDataParamInstances <em>Data Param Instances</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Data Param Instances</em>'.
     * @see bip2.ujf.verimag.bip.instance.AtomInternalPortInstance#getDataParamInstances()
     * @see #getAtomInternalPortInstance()
     * @generated
     */
    EReference getAtomInternalPortInstance_DataParamInstances();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.instance.AtomExternalPortInstance <em>Atom External Port Instance</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Atom External Port Instance</em>'.
     * @see bip2.ujf.verimag.bip.instance.AtomExternalPortInstance
     * @generated
     */
    EClass getAtomExternalPortInstance();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.instance.AtomExternalPortInstance#getDataParamInstances <em>Data Param Instances</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Data Param Instances</em>'.
     * @see bip2.ujf.verimag.bip.instance.AtomExternalPortInstance#getDataParamInstances()
     * @see #getAtomExternalPortInstance()
     * @generated
     */
    EReference getAtomExternalPortInstance_DataParamInstances();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.instance.ConnectorPortInstance <em>Connector Port Instance</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Connector Port Instance</em>'.
     * @see bip2.ujf.verimag.bip.instance.ConnectorPortInstance
     * @generated
     */
    EClass getConnectorPortInstance();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.instance.ConnectorPortInstance#getDataParamInstances <em>Data Param Instances</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Data Param Instances</em>'.
     * @see bip2.ujf.verimag.bip.instance.ConnectorPortInstance#getDataParamInstances()
     * @see #getConnectorPortInstance()
     * @generated
     */
    EReference getConnectorPortInstance_DataParamInstances();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.instance.DataInstance <em>Data Instance</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Data Instance</em>'.
     * @see bip2.ujf.verimag.bip.instance.DataInstance
     * @generated
     */
    EClass getDataInstance();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.instance.DataInstance#getDeclaration <em>Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Declaration</em>'.
     * @see bip2.ujf.verimag.bip.instance.DataInstance#getDeclaration()
     * @see #getDataInstance()
     * @generated
     */
    EReference getDataInstance_Declaration();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.instance.DataInstance#getProxyLink <em>Proxy Link</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Proxy Link</em>'.
     * @see bip2.ujf.verimag.bip.instance.DataInstance#getProxyLink()
     * @see #getDataInstance()
     * @generated
     */
    EReference getDataInstance_ProxyLink();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.instance.CompoundPriorityInstance <em>Compound Priority Instance</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Compound Priority Instance</em>'.
     * @see bip2.ujf.verimag.bip.instance.CompoundPriorityInstance
     * @generated
     */
    EClass getCompoundPriorityInstance();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.instance.CompoundPriorityInstance#getDeclaration <em>Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Declaration</em>'.
     * @see bip2.ujf.verimag.bip.instance.CompoundPriorityInstance#getDeclaration()
     * @see #getCompoundPriorityInstance()
     * @generated
     */
    EReference getCompoundPriorityInstance_Declaration();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.instance.CompoundPriorityInstance#getLowConnector <em>Low Connector</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Low Connector</em>'.
     * @see bip2.ujf.verimag.bip.instance.CompoundPriorityInstance#getLowConnector()
     * @see #getCompoundPriorityInstance()
     * @generated
     */
    EReference getCompoundPriorityInstance_LowConnector();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.instance.CompoundPriorityInstance#getHighConnector <em>High Connector</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>High Connector</em>'.
     * @see bip2.ujf.verimag.bip.instance.CompoundPriorityInstance#getHighConnector()
     * @see #getCompoundPriorityInstance()
     * @generated
     */
    EReference getCompoundPriorityInstance_HighConnector();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.instance.CompoundPriorityInstance#getLowPorts <em>Low Ports</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Low Ports</em>'.
     * @see bip2.ujf.verimag.bip.instance.CompoundPriorityInstance#getLowPorts()
     * @see #getCompoundPriorityInstance()
     * @generated
     */
    EReference getCompoundPriorityInstance_LowPorts();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.instance.CompoundPriorityInstance#getHighPorts <em>High Ports</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>High Ports</em>'.
     * @see bip2.ujf.verimag.bip.instance.CompoundPriorityInstance#getHighPorts()
     * @see #getCompoundPriorityInstance()
     * @generated
     */
    EReference getCompoundPriorityInstance_HighPorts();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.instance.AtomInstance <em>Atom Instance</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Atom Instance</em>'.
     * @see bip2.ujf.verimag.bip.instance.AtomInstance
     * @generated
     */
    EClass getAtomInstance();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.instance.AtomInstance#getSubDataInstances <em>Sub Data Instances</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Sub Data Instances</em>'.
     * @see bip2.ujf.verimag.bip.instance.AtomInstance#getSubDataInstances()
     * @see #getAtomInstance()
     * @generated
     */
    EReference getAtomInstance_SubDataInstances();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.instance.AtomInstance#getInternalPorts <em>Internal Ports</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Internal Ports</em>'.
     * @see bip2.ujf.verimag.bip.instance.AtomInstance#getInternalPorts()
     * @see #getAtomInstance()
     * @generated
     */
    EReference getAtomInstance_InternalPorts();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.instance.AtomInstance#getExternalPorts <em>External Ports</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>External Ports</em>'.
     * @see bip2.ujf.verimag.bip.instance.AtomInstance#getExternalPorts()
     * @see #getAtomInstance()
     * @generated
     */
    EReference getAtomInstance_ExternalPorts();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.instance.CompoundInstance <em>Compound Instance</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Compound Instance</em>'.
     * @see bip2.ujf.verimag.bip.instance.CompoundInstance
     * @generated
     */
    EClass getCompoundInstance();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.instance.CompoundInstance#getSubPriorities <em>Sub Priorities</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Sub Priorities</em>'.
     * @see bip2.ujf.verimag.bip.instance.CompoundInstance#getSubPriorities()
     * @see #getCompoundInstance()
     * @generated
     */
    EReference getCompoundInstance_SubPriorities();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.instance.CompoundInstance#getSubConnectorInstances <em>Sub Connector Instances</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Sub Connector Instances</em>'.
     * @see bip2.ujf.verimag.bip.instance.CompoundInstance#getSubConnectorInstances()
     * @see #getCompoundInstance()
     * @generated
     */
    EReference getCompoundInstance_SubConnectorInstances();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.instance.CompoundInstance#getSubAtomInstances <em>Sub Atom Instances</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Sub Atom Instances</em>'.
     * @see bip2.ujf.verimag.bip.instance.CompoundInstance#getSubAtomInstances()
     * @see #getCompoundInstance()
     * @generated
     */
    EReference getCompoundInstance_SubAtomInstances();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.instance.CompoundInstance#getSubCompoundInstances <em>Sub Compound Instances</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Sub Compound Instances</em>'.
     * @see bip2.ujf.verimag.bip.instance.CompoundInstance#getSubCompoundInstances()
     * @see #getCompoundInstance()
     * @generated
     */
    EReference getCompoundInstance_SubCompoundInstances();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.instance.CompoundInstance#getSubDataInstances <em>Sub Data Instances</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Sub Data Instances</em>'.
     * @see bip2.ujf.verimag.bip.instance.CompoundInstance#getSubDataInstances()
     * @see #getCompoundInstance()
     * @generated
     */
    EReference getCompoundInstance_SubDataInstances();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.instance.ComponentInstance <em>Component Instance</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Component Instance</em>'.
     * @see bip2.ujf.verimag.bip.instance.ComponentInstance
     * @generated
     */
    EClass getComponentInstance();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.instance.ComponentInstance#getDeclaration <em>Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Declaration</em>'.
     * @see bip2.ujf.verimag.bip.instance.ComponentInstance#getDeclaration()
     * @see #getComponentInstance()
     * @generated
     */
    EReference getComponentInstance_Declaration();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.instance.ComponentInstance#getExportedPorts <em>Exported Ports</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Exported Ports</em>'.
     * @see bip2.ujf.verimag.bip.instance.ComponentInstance#getExportedPorts()
     * @see #getComponentInstance()
     * @generated
     */
    EReference getComponentInstance_ExportedPorts();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    InstanceFactory getInstanceFactory();

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
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.instance.impl.ConnectorInstanceImpl <em>Connector Instance</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.instance.impl.ConnectorInstanceImpl
         * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getConnectorInstance()
         * @generated
         */
        EClass CONNECTOR_INSTANCE = eINSTANCE.getConnectorInstance();

        /**
         * The meta object literal for the '<em><b>Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_INSTANCE__DECLARATION = eINSTANCE
                .getConnectorInstance_Declaration();

        /**
         * The meta object literal for the '<em><b>Sub Data Instances</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_INSTANCE__SUB_DATA_INSTANCES = eINSTANCE
                .getConnectorInstance_SubDataInstances();

        /**
         * The meta object literal for the '<em><b>Port Param Instances</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_INSTANCE__PORT_PARAM_INSTANCES = eINSTANCE
                .getConnectorInstance_PortParamInstances();

        /**
         * The meta object literal for the '<em><b>Exported Port</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_INSTANCE__EXPORTED_PORT = eINSTANCE
                .getConnectorInstance_ExportedPort();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.instance.PortInstance <em>Port Instance</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.instance.PortInstance
         * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getPortInstance()
         * @generated
         */
        EClass PORT_INSTANCE = eINSTANCE.getPortInstance();

        /**
         * The meta object literal for the '<em><b>Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PORT_INSTANCE__DECLARATION = eINSTANCE
                .getPortInstance_Declaration();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.instance.impl.ExportedPortInstanceImpl <em>Exported Port Instance</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.instance.impl.ExportedPortInstanceImpl
         * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getExportedPortInstance()
         * @generated
         */
        EClass EXPORTED_PORT_INSTANCE = eINSTANCE.getExportedPortInstance();

        /**
         * The meta object literal for the '<em><b>Referenced Ports</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference EXPORTED_PORT_INSTANCE__REFERENCED_PORTS = eINSTANCE
                .getExportedPortInstance_ReferencedPorts();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.instance.impl.AtomInternalPortInstanceImpl <em>Atom Internal Port Instance</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.instance.impl.AtomInternalPortInstanceImpl
         * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getAtomInternalPortInstance()
         * @generated
         */
        EClass ATOM_INTERNAL_PORT_INSTANCE = eINSTANCE
                .getAtomInternalPortInstance();

        /**
         * The meta object literal for the '<em><b>Data Param Instances</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_INTERNAL_PORT_INSTANCE__DATA_PARAM_INSTANCES = eINSTANCE
                .getAtomInternalPortInstance_DataParamInstances();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.instance.impl.AtomExternalPortInstanceImpl <em>Atom External Port Instance</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.instance.impl.AtomExternalPortInstanceImpl
         * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getAtomExternalPortInstance()
         * @generated
         */
        EClass ATOM_EXTERNAL_PORT_INSTANCE = eINSTANCE
                .getAtomExternalPortInstance();

        /**
         * The meta object literal for the '<em><b>Data Param Instances</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_EXTERNAL_PORT_INSTANCE__DATA_PARAM_INSTANCES = eINSTANCE
                .getAtomExternalPortInstance_DataParamInstances();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.instance.impl.ConnectorPortInstanceImpl <em>Connector Port Instance</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.instance.impl.ConnectorPortInstanceImpl
         * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getConnectorPortInstance()
         * @generated
         */
        EClass CONNECTOR_PORT_INSTANCE = eINSTANCE.getConnectorPortInstance();

        /**
         * The meta object literal for the '<em><b>Data Param Instances</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_PORT_INSTANCE__DATA_PARAM_INSTANCES = eINSTANCE
                .getConnectorPortInstance_DataParamInstances();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.instance.impl.DataInstanceImpl <em>Data Instance</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.instance.impl.DataInstanceImpl
         * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getDataInstance()
         * @generated
         */
        EClass DATA_INSTANCE = eINSTANCE.getDataInstance();

        /**
         * The meta object literal for the '<em><b>Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference DATA_INSTANCE__DECLARATION = eINSTANCE
                .getDataInstance_Declaration();

        /**
         * The meta object literal for the '<em><b>Proxy Link</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference DATA_INSTANCE__PROXY_LINK = eINSTANCE
                .getDataInstance_ProxyLink();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.instance.impl.CompoundPriorityInstanceImpl <em>Compound Priority Instance</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.instance.impl.CompoundPriorityInstanceImpl
         * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getCompoundPriorityInstance()
         * @generated
         */
        EClass COMPOUND_PRIORITY_INSTANCE = eINSTANCE
                .getCompoundPriorityInstance();

        /**
         * The meta object literal for the '<em><b>Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_PRIORITY_INSTANCE__DECLARATION = eINSTANCE
                .getCompoundPriorityInstance_Declaration();

        /**
         * The meta object literal for the '<em><b>Low Connector</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_PRIORITY_INSTANCE__LOW_CONNECTOR = eINSTANCE
                .getCompoundPriorityInstance_LowConnector();

        /**
         * The meta object literal for the '<em><b>High Connector</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_PRIORITY_INSTANCE__HIGH_CONNECTOR = eINSTANCE
                .getCompoundPriorityInstance_HighConnector();

        /**
         * The meta object literal for the '<em><b>Low Ports</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_PRIORITY_INSTANCE__LOW_PORTS = eINSTANCE
                .getCompoundPriorityInstance_LowPorts();

        /**
         * The meta object literal for the '<em><b>High Ports</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_PRIORITY_INSTANCE__HIGH_PORTS = eINSTANCE
                .getCompoundPriorityInstance_HighPorts();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.instance.impl.AtomInstanceImpl <em>Atom Instance</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.instance.impl.AtomInstanceImpl
         * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getAtomInstance()
         * @generated
         */
        EClass ATOM_INSTANCE = eINSTANCE.getAtomInstance();

        /**
         * The meta object literal for the '<em><b>Sub Data Instances</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_INSTANCE__SUB_DATA_INSTANCES = eINSTANCE
                .getAtomInstance_SubDataInstances();

        /**
         * The meta object literal for the '<em><b>Internal Ports</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_INSTANCE__INTERNAL_PORTS = eINSTANCE
                .getAtomInstance_InternalPorts();

        /**
         * The meta object literal for the '<em><b>External Ports</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_INSTANCE__EXTERNAL_PORTS = eINSTANCE
                .getAtomInstance_ExternalPorts();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.instance.impl.CompoundInstanceImpl <em>Compound Instance</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.instance.impl.CompoundInstanceImpl
         * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getCompoundInstance()
         * @generated
         */
        EClass COMPOUND_INSTANCE = eINSTANCE.getCompoundInstance();

        /**
         * The meta object literal for the '<em><b>Sub Priorities</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_INSTANCE__SUB_PRIORITIES = eINSTANCE
                .getCompoundInstance_SubPriorities();

        /**
         * The meta object literal for the '<em><b>Sub Connector Instances</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_INSTANCE__SUB_CONNECTOR_INSTANCES = eINSTANCE
                .getCompoundInstance_SubConnectorInstances();

        /**
         * The meta object literal for the '<em><b>Sub Atom Instances</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_INSTANCE__SUB_ATOM_INSTANCES = eINSTANCE
                .getCompoundInstance_SubAtomInstances();

        /**
         * The meta object literal for the '<em><b>Sub Compound Instances</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_INSTANCE__SUB_COMPOUND_INSTANCES = eINSTANCE
                .getCompoundInstance_SubCompoundInstances();

        /**
         * The meta object literal for the '<em><b>Sub Data Instances</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_INSTANCE__SUB_DATA_INSTANCES = eINSTANCE
                .getCompoundInstance_SubDataInstances();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.instance.ComponentInstance <em>Component Instance</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.instance.ComponentInstance
         * @see bip2.ujf.verimag.bip.instance.impl.InstancePackageImpl#getComponentInstance()
         * @generated
         */
        EClass COMPONENT_INSTANCE = eINSTANCE.getComponentInstance();

        /**
         * The meta object literal for the '<em><b>Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPONENT_INSTANCE__DECLARATION = eINSTANCE
                .getComponentInstance_Declaration();

        /**
         * The meta object literal for the '<em><b>Exported Ports</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPONENT_INSTANCE__EXPORTED_PORTS = eINSTANCE
                .getComponentInstance_ExportedPorts();

    }

} //InstancePackage
