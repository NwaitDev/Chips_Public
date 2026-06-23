/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Anakreontas Mentis
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

import org.eclipse.emf.ecore.EFactory;

/**
 * <!-- begin-user-doc -->
 * The <b>Factory</b> for the model.
 * It provides a create method for each non-abstract class of the model.
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.connector.ConnectorPackage
 * @generated
 */
public interface ConnectorFactory extends EFactory {
    /**
     * The singleton instance of the factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    ConnectorFactory eINSTANCE = bip2.ujf.verimag.bip.connector.impl.ConnectorFactoryImpl
            .init();

    /**
     * Returns a new object of class '<em>Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Declaration</em>'.
     * @generated
     */
    ConnectorDeclaration createConnectorDeclaration();

    /**
     * Returns a new object of class '<em>Port Parameter Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Port Parameter Declaration</em>'.
     * @generated
     */
    ConnectorPortParameterDeclaration createConnectorPortParameterDeclaration();

    /**
     * Returns a new object of class '<em>Exported Port Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Exported Port Declaration</em>'.
     * @generated
     */
    ConnectorExportedPortDeclaration createConnectorExportedPortDeclaration();

    /**
     * Returns a new object of class '<em>Data Declaration</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Data Declaration</em>'.
     * @generated
     */
    ConnectorDataDeclaration createConnectorDataDeclaration();

    /**
     * Returns a new object of class '<em>Interaction Action</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Interaction Action</em>'.
     * @generated
     */
    ConnectorInteractionAction createConnectorInteractionAction();

    /**
     * Returns a new object of class '<em>Interaction Definition</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Interaction Definition</em>'.
     * @generated
     */
    ConnectorInteractionDefinition createConnectorInteractionDefinition();

    /**
     * Returns a new object of class '<em>Interaction Port Reference</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Interaction Port Reference</em>'.
     * @generated
     */
    ConnectorInteractionPortReference createConnectorInteractionPortReference();

    /**
     * Returns a new object of class '<em>Interaction Nested Definition</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Interaction Nested Definition</em>'.
     * @generated
     */
    ConnectorInteractionNestedDefinition createConnectorInteractionNestedDefinition();

    /**
     * Returns the package supported by this factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the package supported by this factory.
     * @generated
     */
    ConnectorPackage getConnectorPackage();

} //ConnectorFactory
