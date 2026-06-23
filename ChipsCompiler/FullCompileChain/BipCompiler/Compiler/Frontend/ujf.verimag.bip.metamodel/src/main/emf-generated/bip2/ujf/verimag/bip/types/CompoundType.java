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

package bip2.ujf.verimag.bip.types;

import bip2.ujf.verimag.bip.component.ComponentDeclaration;

import bip2.ujf.verimag.bip.component.compound.CompoundExportDataDeclaration;
import bip2.ujf.verimag.bip.component.compound.CompoundExportPortDeclaration;

import bip2.ujf.verimag.bip.connector.ConnectorDeclaration;

import bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration;
import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Compound Type</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.types.CompoundType#getComponentDeclarations <em>Component Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.CompoundType#getConnectorDeclarations <em>Connector Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.CompoundType#getExportPortDeclarations <em>Export Port Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.CompoundType#getExportDataDeclarations <em>Export Data Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.CompoundType#getPriorities <em>Priorities</em>}</li>
 * </ul>
 *
 * @see bip2.ujf.verimag.bip.types.TypesPackage#getCompoundType()
 * @model annotation="http://www.eclipse.org/emf/2002/Ecore constraints='exportedPortsListsSynchronized exportedDataListsSynchronized checkForCyclesInPrioritiesInCompound\n'"
 * @generated
 */
public interface CompoundType extends ComponentType {
    /**
     * Returns the value of the '<em><b>Component Declarations</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.component.ComponentDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Component Declarations</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Component Declarations</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getCompoundType_ComponentDeclarations()
     * @model containment="true"
     * @generated
     */
    EList<ComponentDeclaration> getComponentDeclarations();

    /**
     * Returns the value of the '<em><b>Connector Declarations</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.connector.ConnectorDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Connector Declarations</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Connector Declarations</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getCompoundType_ConnectorDeclarations()
     * @model containment="true"
     * @generated
     */
    EList<ConnectorDeclaration> getConnectorDeclarations();

    /**
     * Returns the value of the '<em><b>Export Port Declarations</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.component.compound.CompoundExportPortDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Export Port Declarations</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Export Port Declarations</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getCompoundType_ExportPortDeclarations()
     * @model containment="true"
     * @generated
     */
    EList<CompoundExportPortDeclaration> getExportPortDeclarations();

    /**
     * Returns the value of the '<em><b>Export Data Declarations</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.component.compound.CompoundExportDataDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Export Data Declarations</em>' reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Export Data Declarations</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getCompoundType_ExportDataDeclarations()
     * @model containment="true"
     * @generated
     */
    EList<CompoundExportDataDeclaration> getExportDataDeclarations();

    /**
     * Returns the value of the '<em><b>Priorities</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Priorities</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Priorities</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getCompoundType_Priorities()
     * @model containment="true"
     * @generated
     */
    EList<CompoundPriorityDeclaration> getPriorities();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    ComponentDeclaration getComponentDeclaration(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    ConnectorDeclaration getConnectorDeclaration(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    CompoundExportPortDeclaration getExportPortDeclaration(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    CompoundExportDataDeclaration getExportDataDeclaration(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model nameRequired="true"
     * @generated
     */
    CompoundPriorityDeclaration getPriorityDeclaration(String name);

} // CompoundType
