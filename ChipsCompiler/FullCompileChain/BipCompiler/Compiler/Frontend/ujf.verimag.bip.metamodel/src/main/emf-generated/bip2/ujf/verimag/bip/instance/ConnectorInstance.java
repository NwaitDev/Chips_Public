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

package bip2.ujf.verimag.bip.instance;

import bip2.ujf.verimag.bip.connector.ConnectorDeclaration;

import org.eclipse.emf.common.util.EList;

import ujf.verimag.bip.metamodel.AnnotatedEObject;
import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Connector Instance</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.instance.ConnectorInstance#getDeclaration <em>Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.ConnectorInstance#getSubDataInstances <em>Sub Data Instances</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.ConnectorInstance#getPortParamInstances <em>Port Param Instances</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.instance.ConnectorInstance#getExportedPort <em>Exported Port</em>}</li>
 * </ul>
 *
 * @see bip2.ujf.verimag.bip.instance.InstancePackage#getConnectorInstance()
 * @model annotation="http://www.eclipse.org/emf/2002/Ecore constraints='connectorDoesNotBindTheSameComponentMoreThanOnce'"
 * @extends AnnotatedEObject
 * @generated
 */
public interface ConnectorInstance extends AnnotatedEObject {
    /**
     * Returns the value of the '<em><b>Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Declaration</em>' reference isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Declaration</em>' reference.
     * @see #setDeclaration(ConnectorDeclaration)
     * @see bip2.ujf.verimag.bip.instance.InstancePackage#getConnectorInstance_Declaration()
     * @model required="true"
     * @generated
     */
    ConnectorDeclaration getDeclaration();

    /**
     * Sets the value of the '{@link bip2.ujf.verimag.bip.instance.ConnectorInstance#getDeclaration <em>Declaration</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Declaration</em>' reference.
     * @see #getDeclaration()
     * @generated
     */
    void setDeclaration(ConnectorDeclaration value);

    /**
     * Returns the value of the '<em><b>Sub Data Instances</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.instance.DataInstance}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Sub Data Instances</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Sub Data Instances</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.instance.InstancePackage#getConnectorInstance_SubDataInstances()
     * @model containment="true"
     * @generated
     */
    EList<DataInstance> getSubDataInstances();

    /**
     * Returns the value of the '<em><b>Port Param Instances</b></em>' reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.instance.PortInstance}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Port Param Instances</em>' reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Port Param Instances</em>' reference list.
     * @see bip2.ujf.verimag.bip.instance.InstancePackage#getConnectorInstance_PortParamInstances()
     * @model
     * @generated
     */
    EList<PortInstance> getPortParamInstances();

    /**
     * Returns the value of the '<em><b>Exported Port</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Exported Port</em>' containment reference isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Exported Port</em>' containment reference.
     * @see #setExportedPort(ConnectorPortInstance)
     * @see bip2.ujf.verimag.bip.instance.InstancePackage#getConnectorInstance_ExportedPort()
     * @model containment="true"
     * @generated
     */
    ConnectorPortInstance getExportedPort();

    /**
     * Sets the value of the '{@link bip2.ujf.verimag.bip.instance.ConnectorInstance#getExportedPort <em>Exported Port</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Exported Port</em>' containment reference.
     * @see #getExportedPort()
     * @generated
     */
    void setExportedPort(ConnectorPortInstance value);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model nameRequired="true"
     * @generated
     */
    DataInstance getDataInstance(String name);

} // ConnectorInstance
