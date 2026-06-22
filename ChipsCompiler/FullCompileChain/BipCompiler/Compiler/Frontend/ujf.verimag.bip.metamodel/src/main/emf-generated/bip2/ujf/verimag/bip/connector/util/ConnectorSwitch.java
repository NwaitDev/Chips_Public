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

package bip2.ujf.verimag.bip.connector.util;

import bip2.ujf.verimag.bip.annotation.AnnotatedElement;
import bip2.ujf.verimag.bip.connector.*;

import bip2.ujf.verimag.bip.data.DataDeclaration;

import bip2.ujf.verimag.bip.data.ExplicitDataDeclaration;
import bip2.ujf.verimag.bip.port.PortDeclaration;

import java.util.List;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.util.Switch;

/**
 * <!-- begin-user-doc -->
 * The <b>Switch</b> for the model's inheritance hierarchy.
 * It supports the call {@link #doSwitch(EObject) doSwitch(object)}
 * to invoke the <code>caseXXX</code> method for each class of the model,
 * starting with the actual class of the object
 * and proceeding up the inheritance hierarchy
 * until a non-null result is returned,
 * which is the result of the switch.
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.connector.ConnectorPackage
 * @generated
 */
public class ConnectorSwitch<T> extends Switch<T> {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected static ConnectorPackage modelPackage;

    /**
     * Creates an instance of the switch.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConnectorSwitch() {
        if (modelPackage == null) {
            modelPackage = ConnectorPackage.eINSTANCE;
        }
    }

    /**
     * Checks whether this is a switch for the given package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param ePackage the package in question.
     * @return whether this is a switch for the given package.
     * @generated
     */
    @Override
    protected boolean isSwitchFor(EPackage ePackage) {
        return ePackage == modelPackage;
    }

    /**
     * Calls <code>caseXXX</code> for each class of the model until one returns a non null result; it yields that result.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the first non-null result returned by a <code>caseXXX</code> call.
     * @generated
     */
    @Override
    protected T doSwitch(int classifierID, EObject theEObject) {
        switch (classifierID) {
        case ConnectorPackage.CONNECTOR_DECLARATION: {
            ConnectorDeclaration connectorDeclaration = (ConnectorDeclaration) theEObject;
            T result = caseConnectorDeclaration(connectorDeclaration);
            if (result == null)
                result = caseAnnotatedElement(connectorDeclaration);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ConnectorPackage.CONNECTOR_PORT_PARAMETER_DECLARATION: {
            ConnectorPortParameterDeclaration connectorPortParameterDeclaration = (ConnectorPortParameterDeclaration) theEObject;
            T result = caseConnectorPortParameterDeclaration(
                    connectorPortParameterDeclaration);
            if (result == null)
                result = casePortDeclaration(connectorPortParameterDeclaration);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ConnectorPackage.CONNECTOR_EXPORTED_PORT_DECLARATION: {
            ConnectorExportedPortDeclaration connectorExportedPortDeclaration = (ConnectorExportedPortDeclaration) theEObject;
            T result = caseConnectorExportedPortDeclaration(
                    connectorExportedPortDeclaration);
            if (result == null)
                result = casePortDeclaration(connectorExportedPortDeclaration);
            if (result == null)
                result = caseAnnotatedElement(connectorExportedPortDeclaration);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ConnectorPackage.CONNECTOR_DATA_DECLARATION: {
            ConnectorDataDeclaration connectorDataDeclaration = (ConnectorDataDeclaration) theEObject;
            T result = caseConnectorDataDeclaration(connectorDataDeclaration);
            if (result == null)
                result = caseExplicitDataDeclaration(connectorDataDeclaration);
            if (result == null)
                result = caseDataDeclaration(connectorDataDeclaration);
            if (result == null)
                result = caseAnnotatedElement(connectorDataDeclaration);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ConnectorPackage.CONNECTOR_INTERACTION_ACTION: {
            ConnectorInteractionAction connectorInteractionAction = (ConnectorInteractionAction) theEObject;
            T result = caseConnectorInteractionAction(
                    connectorInteractionAction);
            if (result == null)
                result = caseAnnotatedElement(connectorInteractionAction);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ConnectorPackage.CONNECTOR_INTERACTION_DEFINITION: {
            ConnectorInteractionDefinition connectorInteractionDefinition = (ConnectorInteractionDefinition) theEObject;
            T result = caseConnectorInteractionDefinition(
                    connectorInteractionDefinition);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ConnectorPackage.CONNECTOR_INTERACTION_PORT_REFERENCE: {
            ConnectorInteractionPortReference connectorInteractionPortReference = (ConnectorInteractionPortReference) theEObject;
            T result = caseConnectorInteractionPortReference(
                    connectorInteractionPortReference);
            if (result == null)
                result = caseConnectorInteractionDefinition(
                        connectorInteractionPortReference);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case ConnectorPackage.CONNECTOR_INTERACTION_NESTED_DEFINITION: {
            ConnectorInteractionNestedDefinition connectorInteractionNestedDefinition = (ConnectorInteractionNestedDefinition) theEObject;
            T result = caseConnectorInteractionNestedDefinition(
                    connectorInteractionNestedDefinition);
            if (result == null)
                result = caseConnectorInteractionDefinition(
                        connectorInteractionNestedDefinition);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        default:
            return defaultCase(theEObject);
        }
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseConnectorDeclaration(ConnectorDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Port Parameter Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Port Parameter Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseConnectorPortParameterDeclaration(
            ConnectorPortParameterDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Exported Port Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Exported Port Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseConnectorExportedPortDeclaration(
            ConnectorExportedPortDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Data Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Data Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseConnectorDataDeclaration(ConnectorDataDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Interaction Action</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Interaction Action</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseConnectorInteractionAction(ConnectorInteractionAction object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Interaction Definition</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Interaction Definition</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseConnectorInteractionDefinition(
            ConnectorInteractionDefinition object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Interaction Port Reference</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Interaction Port Reference</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseConnectorInteractionPortReference(
            ConnectorInteractionPortReference object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Interaction Nested Definition</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Interaction Nested Definition</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseConnectorInteractionNestedDefinition(
            ConnectorInteractionNestedDefinition object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T casePortDeclaration(PortDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseDataDeclaration(DataDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Explicit Data Declaration</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Explicit Data Declaration</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseExplicitDataDeclaration(ExplicitDataDeclaration object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Annotated Element</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Annotated Element</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseAnnotatedElement(AnnotatedElement object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>EObject</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch, but this is the last case anyway.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>EObject</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject)
     * @generated
     */
    @Override
    public T defaultCase(EObject object) {
        return null;
    }

} //ConnectorSwitch
