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

package bip2.ujf.verimag.bip.packaging;

import bip2.ujf.verimag.bip.actionlang.BinaryOperators;
import bip2.ujf.verimag.bip.actionlang.UnaryOperators;
import bip2.ujf.verimag.bip.annotation.AnnotatedElement;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataType;

import bip2.ujf.verimag.bip.types.AtomType;
import bip2.ujf.verimag.bip.types.CompoundType;
import bip2.ujf.verimag.bip.types.ConnectorType;
import bip2.ujf.verimag.bip.types.PortType;

import bip2.ujf.verimag.bip.types.Type;
import org.eclipse.emf.common.util.EList;

import ujf.verimag.bip.metamodel.AnnotatedEObject;
import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Bip Package</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.BipPackage#getName <em>Name</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.BipPackage#getAtomTypes <em>Atom Types</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.BipPackage#getCompoundTypes <em>Compound Types</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.BipPackage#getConnectorTypes <em>Connector Types</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.BipPackage#getPortTypes <em>Port Types</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.BipPackage#getDataTypes <em>Data Types</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.BipPackage#getUsed_packages <em>Used packages</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.BipPackage#getConstData <em>Const Data</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.packaging.BipPackage#getPrototypes <em>Prototypes</em>}</li>
 * </ul>
 *
 * @see bip2.ujf.verimag.bip.packaging.PackagingPackage#getBipPackage()
 * @model annotation="http://www.eclipse.org/emf/2002/Ecore constraints='checkForCyclesInSubTyping'"
 * @generated
 */
public interface BipPackage extends AnnotatedElement {
    /**
     * Returns the value of the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Name</em>' attribute isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Name</em>' attribute.
     * @see #setName(String)
     * @see bip2.ujf.verimag.bip.packaging.PackagingPackage#getBipPackage_Name()
     * @model required="true"
     * @generated
     */
    String getName();

    /**
     * Sets the value of the '{@link bip2.ujf.verimag.bip.packaging.BipPackage#getName <em>Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Name</em>' attribute.
     * @see #getName()
     * @generated
     */
    void setName(String value);

    /**
     * Returns the value of the '<em><b>Used packages</b></em>' reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.packaging.BipPackage}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Used packages</em>' attribute list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Used packages</em>' reference list.
     * @see bip2.ujf.verimag.bip.packaging.PackagingPackage#getBipPackage_Used_packages()
     * @model
     * @generated
     */
    EList<BipPackage> getUsed_packages();

    /**
     * Returns the value of the '<em><b>Const Data</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.packaging.ConstDataDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Const Data</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Const Data</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.packaging.PackagingPackage#getBipPackage_ConstData()
     * @model containment="true"
     * @generated
     */
    EList<ConstDataDeclaration> getConstData();

    /**
     * Returns the value of the '<em><b>Prototypes</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.packaging.Prototype}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Prototypes</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Prototypes</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.packaging.PackagingPackage#getBipPackage_Prototypes()
     * @model containment="true"
     * @generated
     */
    EList<Prototype> getPrototypes();

    /**
     * Returns the value of the '<em><b>Atom Types</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.types.AtomType}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Atom Types</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Atom Types</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.packaging.PackagingPackage#getBipPackage_AtomTypes()
     * @model containment="true"
     * @generated
     */
    EList<AtomType> getAtomTypes();

    /**
     * Returns the value of the '<em><b>Compound Types</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.types.CompoundType}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Compound Types</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Compound Types</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.packaging.PackagingPackage#getBipPackage_CompoundTypes()
     * @model containment="true"
     * @generated
     */
    EList<CompoundType> getCompoundTypes();

    /**
     * Returns the value of the '<em><b>Connector Types</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.types.ConnectorType}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Connector Types</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Connector Types</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.packaging.PackagingPackage#getBipPackage_ConnectorTypes()
     * @model containment="true"
     * @generated
     */
    EList<ConnectorType> getConnectorTypes();

    /**
     * Returns the value of the '<em><b>Port Types</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.types.PortType}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Port Types</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Port Types</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.packaging.PackagingPackage#getBipPackage_PortTypes()
     * @model containment="true"
     * @generated
     */
    EList<PortType> getPortTypes();

    /**
     * Returns the value of the '<em><b>Data Types</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.data.DataType}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Data Types</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Data Types</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.packaging.PackagingPackage#getBipPackage_DataTypes()
     * @model containment="true"
     * @generated
     */
    EList<DataType> getDataTypes();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    AtomType getAtomType(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    CompoundType getCompoundType(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    ConnectorType getConnectorType(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    PortType getPortType(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    DataType getDataType(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    ConstDataDeclaration getConstDataDeclaration(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    EList<FunctionCallPrototype> getFunctionCallPrototypes(String functionName);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model parametersTypesUnique="false" parametersTypesMany="true"
     * @generated
     */
    EList<FunctionCallPrototype> getFunctionCallPrototypes(String functionName,
            EList<Type> parametersTypes);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    EList<BinaryOpPrototype> getBinaryOpPrototypes(BinaryOperators operator);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model parametersTypesUnique="false" parametersTypesMany="true"
     * @generated
     */
    EList<BinaryOpPrototype> getBinaryOpPrototypes(BinaryOperators operator,
            EList<Type> parametersTypes);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    EList<UnaryOpPrototype> getUnaryOpPrototypes(UnaryOperators operator);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model parametersTypesUnique="false" parametersTypesMany="true"
     * @generated
     */
    EList<UnaryOpPrototype> getUnaryOpPrototypes(UnaryOperators operator,
            EList<Type> parametersTypes);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model kind="operation" required="true"
     * @generated
     */
    DataType getBoolDataType();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model kind="operation" required="true"
     * @generated
     */
    DataType getIntDataType();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model kind="operation" required="true"
     * @generated
     */
    DataType getFloatDataType();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model kind="operation" required="true"
     * @generated
     */
    DataType getStringDataType();

} // BipPackage
