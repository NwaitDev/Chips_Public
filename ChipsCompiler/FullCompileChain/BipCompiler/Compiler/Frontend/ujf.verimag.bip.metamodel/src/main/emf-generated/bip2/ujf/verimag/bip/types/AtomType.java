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

import bip2.ujf.verimag.bip.behavior.PetriNet;

import bip2.ujf.verimag.bip.component.atom.AtomExportPortDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomExternalPortDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomInternalDataDeclaration;
import bip2.ujf.verimag.bip.component.atom.AtomInternalPortDeclaration;

import bip2.ujf.verimag.bip.invariant.AtomInvariant;
import bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration;
import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Atom Type</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.types.AtomType#getInternalPortDeclarations <em>Internal Port Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.AtomType#getExternalPortDeclarations <em>External Port Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.AtomType#getBehavior <em>Behavior</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.AtomType#getInternalDataDeclarations <em>Internal Data Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.AtomType#getExportPortDeclarations <em>Export Port Declarations</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.AtomType#getPriorities <em>Priorities</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.types.AtomType#getInvariants <em>Invariants</em>}</li>
 * </ul>
 *
 * @see bip2.ujf.verimag.bip.types.TypesPackage#getAtomType()
 * @model annotation="http://www.eclipse.org/emf/2002/Ecore constraints='InternalDataSynchronizedWithExportedData checkForCyclesInPrioritiesInAtom checkUninitializedVariablesInAtomInternalDataDeclaration'"
 * @generated
 */
public interface AtomType extends ComponentType {
    /**
     * Returns the value of the '<em><b>Internal Port Declarations</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.component.atom.AtomInternalPortDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Internal Port Declarations</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Internal Port Declarations</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getAtomType_InternalPortDeclarations()
     * @model containment="true"
     * @generated
     */
    EList<AtomInternalPortDeclaration> getInternalPortDeclarations();

    /**
     * Returns the value of the '<em><b>External Port Declarations</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.component.atom.AtomExternalPortDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>External Port Declarations</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>External Port Declarations</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getAtomType_ExternalPortDeclarations()
     * @model containment="true"
     * @generated
     */
    EList<AtomExternalPortDeclaration> getExternalPortDeclarations();

    /**
     * Returns the value of the '<em><b>Behavior</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Behavior</em>' containment reference isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Behavior</em>' containment reference.
     * @see #setBehavior(PetriNet)
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getAtomType_Behavior()
     * @model containment="true" required="true"
     * @generated
     */
    PetriNet getBehavior();

    /**
     * Sets the value of the '{@link bip2.ujf.verimag.bip.types.AtomType#getBehavior <em>Behavior</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Behavior</em>' containment reference.
     * @see #getBehavior()
     * @generated
     */
    void setBehavior(PetriNet value);

    /**
     * Returns the value of the '<em><b>Internal Data Declarations</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.component.atom.AtomInternalDataDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Internal Data Declarations</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Internal Data Declarations</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getAtomType_InternalDataDeclarations()
     * @model containment="true"
     * @generated
     */
    EList<AtomInternalDataDeclaration> getInternalDataDeclarations();

    /**
     * Returns the value of the '<em><b>Export Port Declarations</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.component.atom.AtomExportPortDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Export Port Declarations</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Export Port Declarations</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getAtomType_ExportPortDeclarations()
     * @model containment="true"
     * @generated
     */
    EList<AtomExportPortDeclaration> getExportPortDeclarations();

    /**
     * Returns the value of the '<em><b>Priorities</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Priorities</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Priorities</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getAtomType_Priorities()
     * @model containment="true"
     * @generated
     */
    EList<AtomPriorityDeclaration> getPriorities();

    /**
     * Returns the value of the '<em><b>Invariants</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.invariant.AtomInvariant}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Invariants</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Invariants</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.types.TypesPackage#getAtomType_Invariants()
     * @model containment="true"
     * @generated
     */
    EList<AtomInvariant> getInvariants();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    AtomInternalPortDeclaration getInternalPortDeclaration(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    AtomExternalPortDeclaration getExternalPortDeclaration(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    AtomInternalDataDeclaration getInternalDataDeclaration(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    AtomPriorityDeclaration getPriorityDeclaration(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    AtomInvariant getInvariantDeclaration(String name);

} // AtomType
