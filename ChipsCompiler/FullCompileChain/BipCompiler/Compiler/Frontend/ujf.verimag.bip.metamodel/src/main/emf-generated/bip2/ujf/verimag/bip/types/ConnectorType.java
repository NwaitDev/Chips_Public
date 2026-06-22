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

import bip2.ujf.verimag.bip.connector.ConnectorDataDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorExportedPortDeclaration;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionAction;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionDefinition;
import bip2.ujf.verimag.bip.connector.ConnectorInteractionPortReference;
import bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration;

import bip2.ujf.verimag.bip.port.PortDataParameterDeclaration;
import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Connector Type</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.types.ConnectorType#getExportedPortDeclaration <em>Exported Port Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.ConnectorType#getDataDeclarations <em>Data Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.ConnectorType#getInteractions <em>Interactions</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.ConnectorType#getInteractionDefinition <em>Interaction Definition</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.ConnectorType#getPorts <em>Ports</em>}</li>
 * </ul>
 *
 * @see bip2.ujf.verimag.bip.types.TypesPackage#getConnectorType()
 * @model annotation="http://www.eclipse.org/emf/2002/Ecore constraints='interactionDefinedIfExportPortWithData noDuplicatedInteractionAction checkDownWhenNoDataInConnectorPort missingInteractionIfExportPortWithData checkUninitializedVariablesInConnectorDataDeclaration'"
 * @generated
 */
public interface ConnectorType extends BipType {
    /**
     * Returns the value of the '<em><b>Exported Port Declaration</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Exported Port Declaration</em>' containment reference isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Exported Port Declaration</em>' containment reference.
     * @see #setExportedPortDeclaration(ConnectorExportedPortDeclaration)
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getConnectorType_ExportedPortDeclaration()
     * @model containment="true"
     * @generated
     */
    ConnectorExportedPortDeclaration getExportedPortDeclaration();

    /**
     * Sets the value of the '{@link bip2.ujf.verimag.bip.types.ConnectorType#getExportedPortDeclaration <em>Exported Port Declaration</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Exported Port Declaration</em>' containment reference.
     * @see #getExportedPortDeclaration()
     * @generated
     */
    void setExportedPortDeclaration(ConnectorExportedPortDeclaration value);

    /**
     * Returns the value of the '<em><b>Data Declarations</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.connector.ConnectorDataDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Data Declarations</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Data Declarations</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getConnectorType_DataDeclarations()
     * @model containment="true"
     * @generated
     */
    EList<ConnectorDataDeclaration> getDataDeclarations();

    /**
     * Returns the value of the '<em><b>Interactions</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.connector.ConnectorInteractionAction}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Interactions</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Interactions</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getConnectorType_Interactions()
     * @model containment="true"
     * @generated
     */
    EList<ConnectorInteractionAction> getInteractions();

    /**
     * Returns the value of the '<em><b>Interaction Definition</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Interaction Definition</em>' containment reference isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Interaction Definition</em>' containment reference.
     * @see #setInteractionDefinition(ConnectorInteractionDefinition)
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getConnectorType_InteractionDefinition()
     * @model containment="true" required="true"
     * @generated
     */
    ConnectorInteractionDefinition getInteractionDefinition();

    /**
     * Sets the value of the '{@link bip2.ujf.verimag.bip.types.ConnectorType#getInteractionDefinition <em>Interaction Definition</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Interaction Definition</em>' containment reference.
     * @see #getInteractionDefinition()
     * @generated
     */
    void setInteractionDefinition(ConnectorInteractionDefinition value);

    /**
     * Returns the value of the '<em><b>Ports</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.connector.ConnectorPortParameterDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Ports</em>' containment reference isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Ports</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getConnectorType_Ports()
     * @model containment="true" required="true"
     * @generated
     */
    EList<ConnectorPortParameterDeclaration> getPorts();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    ConnectorPortParameterDeclaration getPortParameterDeclaration(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model required="true" portsUnique="false" portsMany="true" portsOrdered="false"
     * @generated
     */
    boolean isDefined(EList<ConnectorPortParameterDeclaration> ports);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    ConnectorDataDeclaration getDataDeclaration(String name);

} // ConnectorType
