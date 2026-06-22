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

package bip2.ujf.verimag.bip.types.util;

import bip2.ujf.verimag.bip.annotation.AnnotatedElement;
import bip2.ujf.verimag.bip.types.*;

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
 * @see bip2.ujf.verimag.bip.types.TypesPackage
 * @generated
 */
public class TypesSwitch<T> extends Switch<T> {
    /**
     * The cached model package
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected static TypesPackage modelPackage;

    /**
     * Creates an instance of the switch.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public TypesSwitch() {
        if (modelPackage == null) {
            modelPackage = TypesPackage.eINSTANCE;
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
        case TypesPackage.TYPE: {
            Type type = (Type) theEObject;
            T result = caseType(type);
            if (result == null)
                result = caseAnnotatedElement(type);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case TypesPackage.BIP_TYPE: {
            BipType bipType = (BipType) theEObject;
            T result = caseBipType(bipType);
            if (result == null)
                result = caseType(bipType);
            if (result == null)
                result = caseAnnotatedElement(bipType);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case TypesPackage.COMPONENT_TYPE: {
            ComponentType componentType = (ComponentType) theEObject;
            T result = caseComponentType(componentType);
            if (result == null)
                result = caseBipType(componentType);
            if (result == null)
                result = caseType(componentType);
            if (result == null)
                result = caseAnnotatedElement(componentType);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case TypesPackage.ATOM_TYPE: {
            AtomType atomType = (AtomType) theEObject;
            T result = caseAtomType(atomType);
            if (result == null)
                result = caseComponentType(atomType);
            if (result == null)
                result = caseBipType(atomType);
            if (result == null)
                result = caseType(atomType);
            if (result == null)
                result = caseAnnotatedElement(atomType);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case TypesPackage.COMPOUND_TYPE: {
            CompoundType compoundType = (CompoundType) theEObject;
            T result = caseCompoundType(compoundType);
            if (result == null)
                result = caseComponentType(compoundType);
            if (result == null)
                result = caseBipType(compoundType);
            if (result == null)
                result = caseType(compoundType);
            if (result == null)
                result = caseAnnotatedElement(compoundType);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case TypesPackage.CONNECTOR_TYPE: {
            ConnectorType connectorType = (ConnectorType) theEObject;
            T result = caseConnectorType(connectorType);
            if (result == null)
                result = caseBipType(connectorType);
            if (result == null)
                result = caseType(connectorType);
            if (result == null)
                result = caseAnnotatedElement(connectorType);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        case TypesPackage.PORT_TYPE: {
            PortType portType = (PortType) theEObject;
            T result = casePortType(portType);
            if (result == null)
                result = caseBipType(portType);
            if (result == null)
                result = caseType(portType);
            if (result == null)
                result = caseAnnotatedElement(portType);
            if (result == null)
                result = defaultCase(theEObject);
            return result;
        }
        default:
            return defaultCase(theEObject);
        }
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Type</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Type</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseType(Type object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Atom Type</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Atom Type</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseAtomType(AtomType object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Component Type</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Component Type</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseComponentType(ComponentType object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Compound Type</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Compound Type</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseCompoundType(CompoundType object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Connector Type</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Connector Type</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseConnectorType(ConnectorType object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Port Type</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Port Type</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T casePortType(PortType object) {
        return null;
    }

    /**
     * Returns the result of interpreting the object as an instance of '<em>Bip Type</em>'.
     * <!-- begin-user-doc -->
     * This implementation returns null;
     * returning a non-null result will terminate the switch.
     * <!-- end-user-doc -->
     * @param object the target of the switch.
     * @return the result of interpreting the object as an instance of '<em>Bip Type</em>'.
     * @see #doSwitch(org.eclipse.emf.ecore.EObject) doSwitch(EObject)
     * @generated
     */
    public T caseBipType(BipType object) {
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

} //TypesSwitch
