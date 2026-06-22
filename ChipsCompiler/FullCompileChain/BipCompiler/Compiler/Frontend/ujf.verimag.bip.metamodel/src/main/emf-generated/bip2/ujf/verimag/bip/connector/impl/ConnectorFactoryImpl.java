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

package bip2.ujf.verimag.bip.connector.impl;

import bip2.ujf.verimag.bip.connector.*;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EDataType;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.impl.EFactoryImpl;

import org.eclipse.emf.ecore.plugin.EcorePlugin;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Factory</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class ConnectorFactoryImpl extends EFactoryImpl
        implements ConnectorFactory {
    /**
     * Creates the default factory implementation.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static ConnectorFactory init() {
        try {
            ConnectorFactory theConnectorFactory = (ConnectorFactory) EPackage.Registry.INSTANCE
                    .getEFactory(ConnectorPackage.eNS_URI);
            if (theConnectorFactory != null) {
                return theConnectorFactory;
            }
        } catch (Exception exception) {
            EcorePlugin.INSTANCE.log(exception);
        }
        return new ConnectorFactoryImpl();
    }

    /**
     * Creates an instance of the factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorFactoryImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EObject create(EClass eClass) {
        switch (eClass.getClassifierID()) {
        case ConnectorPackage.CONNECTOR_DECLARATION:
            return (EObject) createConnectorDeclaration();
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION:
            return (EObject) createConnectorPortParameterDeclaration();
        case ConnectorPackage.CONNECTOR_EXPORTED_PORT_DECLARATION:
            return (EObject) createConnectorExportedPortDeclaration();
        case ConnectorPackage.CONNECTOR_DATA_DECLARATION:
            return (EObject) createConnectorDataDeclaration();
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION:
            return (EObject) createConnectorInteractionAction();
        case ConnectorPackage.CONNECTOR_INTERACTION_DEFINITION:
            return (EObject) createConnectorInteractionDefinition();
        case ConnectorPackage.CONNECTOR_INTERACTION_PORT_REFERENCE:
            return (EObject) createConnectorInteractionPortReference();
        case ConnectorPackage.CONNECTOR_INTERACTION_NESTED_DEFINITION:
            return (EObject) createConnectorInteractionNestedDefinition();
        default:
            throw new IllegalArgumentException("The class '" + eClass.getName()
                    + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorDeclaration createConnectorDeclaration() {
        ConnectorDeclarationImpl connectorDeclaration = new ConnectorDeclarationImpl();
        return connectorDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorPortParameterDeclaration createConnectorPortParameterDeclaration() {
        ConnectorPortParameterDeclarationImpl connectorPortParameterDeclaration = new ConnectorPortParameterDeclarationImpl();
        return connectorPortParameterDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorExportedPortDeclaration createConnectorExportedPortDeclaration() {
        ConnectorExportedPortDeclarationImpl connectorExportedPortDeclaration = new ConnectorExportedPortDeclarationImpl();
        return connectorExportedPortDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorDataDeclaration createConnectorDataDeclaration() {
        ConnectorDataDeclarationImpl connectorDataDeclaration = new ConnectorDataDeclarationImpl();
        return connectorDataDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorInteractionAction createConnectorInteractionAction() {
        ConnectorInteractionActionImpl connectorInteractionAction = new ConnectorInteractionActionImpl();
        return connectorInteractionAction;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorInteractionDefinition createConnectorInteractionDefinition() {
        ConnectorInteractionDefinitionImpl connectorInteractionDefinition = new ConnectorInteractionDefinitionImpl();
        return connectorInteractionDefinition;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorInteractionPortReference createConnectorInteractionPortReference() {
        ConnectorInteractionPortReferenceImpl connectorInteractionPortReference = new ConnectorInteractionPortReferenceImpl();
        return connectorInteractionPortReference;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorInteractionNestedDefinition createConnectorInteractionNestedDefinition() {
        ConnectorInteractionNestedDefinitionImpl connectorInteractionNestedDefinition = new ConnectorInteractionNestedDefinitionImpl();
        return connectorInteractionNestedDefinition;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorPackage getConnectorPackage() {
        return (ConnectorPackage) getEPackage();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @deprecated
     * @generated
     */
    @Deprecated
    public static ConnectorPackage getPackage() {
        return ConnectorPackage.eINSTANCE;
    }

} //ConnectorFactoryImpl
