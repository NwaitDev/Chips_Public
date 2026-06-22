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

package bip2.ujf.verimag.bip.behavior;

import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import org.eclipse.emf.common.util.EList;

import ujf.verimag.bip.metamodel.AnnotatedEObject;
import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Petri Net</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.behavior.PetriNet#getStates <em>States</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.behavior.PetriNet#getInitStates <em>Init States</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.behavior.PetriNet#getTransitions <em>Transitions</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.behavior.PetriNet#getInitialActions <em>Initial Actions</em>}</li>
 * </ul>
 *
 * @see bip2.ujf.verimag.bip.behavior.BehaviorPackage#getPetriNet()
 * @model annotation="http://www.eclipse.org/emf/2002/Ecore constraints='checkIllFormed checkUninitializedVariablesOfPetriNet checkUninitializedVariablesExportedByPortOfAtom checkUninitializedVariablesExportedAtom'"
 * @extends AnnotatedEObject
 * @generated
 */
public interface PetriNet extends AnnotatedEObject {
    /**
     * Returns the value of the '<em><b>States</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.behavior.State}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>States</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>States</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.behavior.BehaviorPackage#getPetriNet_States()
     * @model containment="true" required="true"
     * @generated
     */
    EList<State> getStates();

    /**
     * Returns the value of the '<em><b>Init States</b></em>' reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.behavior.State}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Init States</em>' reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Init States</em>' reference list.
     * @see bip2.ujf.verimag.bip.behavior.BehaviorPackage#getPetriNet_InitStates()
     * @model required="true"
     * @generated
     */
    EList<State> getInitStates();

    /**
     * Returns the value of the '<em><b>Transitions</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.behavior.Transition}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Transitions</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Transitions</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.behavior.BehaviorPackage#getPetriNet_Transitions()
     * @model containment="true" required="true"
     * @generated
     */
    EList<Transition> getTransitions();

    /**
     * Returns the value of the '<em><b>Initial Actions</b></em>' containment reference list.
     * The list contents are of type {@link bip2.ujf.verimag.bip.actionlang.Expression}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Initial Actions</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Initial Actions</em>' containment reference list.
     * @see bip2.ujf.verimag.bip.behavior.BehaviorPackage#getPetriNet_InitialActions()
     * @model containment="true"
     * @generated
     */
    EList<Expression> getInitialActions();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model
     * @generated
     */
    State getState(String name);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model required="true" stateRequired="true"
     * @generated
     */
    Boolean isOneSafe(State state);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model required="true" stateRequired="true"
     * @generated
     */
    Boolean mayBeOneSafe(State state);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model required="true" statesUnique="false" statesMany="true" statesOrdered="false"
     * @generated
     */
    Boolean isCoverable(EList<State> states);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model required="true" statesUnique="false" statesMany="true" statesOrdered="false"
     * @generated
     */
    Boolean mayBeCoverable(EList<State> states);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model kind="operation"
     * @generated
     */
    EList<Expression> getUninitializedVariables();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model kind="operation" ordered="false"
     * @generated
     */
    EList<DataDeclaration> getUninitializedExportedVariables();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model ordered="false" transitionRequired="true"
     * @generated
     */
    EList<DataDeclaration> getUninitializedExportedVariables(
            Transition transition);

} // PetriNet
