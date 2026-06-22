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

package bip2.ujf.verimag.bip.behavior;

import bip2.ujf.verimag.bip.annotation.AnnotationPackage;
import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EReference;

/**
 * <!-- begin-user-doc -->
 * The <b>Package</b> for the model.
 * It contains accessors for the meta objects to represent
 * <ul>
 *   <li>each class,</li>
 *   <li>each feature of each class,</li>
 *   <li>each enum,</li>
 *   <li>and each data type</li>
 * </ul>
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.behavior.BehaviorFactory
 * @model kind="package"
 * @generated
 */
public interface BehaviorPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "behavior";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/behavior/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.behavior";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    BehaviorPackage eINSTANCE = bip2.ujf.verimag.bip.behavior.impl.BehaviorPackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.behavior.impl.PetriNetImpl <em>Petri Net</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.behavior.impl.PetriNetImpl
     * @see bip2.ujf.verimag.bip.behavior.impl.BehaviorPackageImpl#getPetriNet()
     * @generated
     */
    int PETRI_NET = 0;

    /**
     * The feature id for the '<em><b>States</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PETRI_NET__STATES = 0;

    /**
     * The feature id for the '<em><b>Init States</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PETRI_NET__INIT_STATES = 1;

    /**
     * The feature id for the '<em><b>Transitions</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PETRI_NET__TRANSITIONS = 2;

    /**
     * The feature id for the '<em><b>Initial Actions</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PETRI_NET__INITIAL_ACTIONS = 3;

    /**
     * The number of structural features of the '<em>Petri Net</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int PETRI_NET_FEATURE_COUNT = 4;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.behavior.impl.StateImpl <em>State</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.behavior.impl.StateImpl
     * @see bip2.ujf.verimag.bip.behavior.impl.BehaviorPackageImpl#getState()
     * @generated
     */
    int STATE = 1;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STATE__NAME = 0;

    /**
     * The number of structural features of the '<em>State</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STATE_FEATURE_COUNT = 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.behavior.impl.TransitionImpl <em>Transition</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.behavior.impl.TransitionImpl
     * @see bip2.ujf.verimag.bip.behavior.impl.BehaviorPackageImpl#getTransition()
     * @generated
     */
    int TRANSITION = 2;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int TRANSITION__BIP_ANNOTATIONS = AnnotationPackage.ANNOTATED_ELEMENT__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Sources</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int TRANSITION__SOURCES = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>Destinations</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int TRANSITION__DESTINATIONS = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 1;

    /**
     * The feature id for the '<em><b>Trigger Port</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int TRANSITION__TRIGGER_PORT = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 2;

    /**
     * The feature id for the '<em><b>Actions</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int TRANSITION__ACTIONS = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 3;

    /**
     * The feature id for the '<em><b>Guard</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int TRANSITION__GUARD = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 4;

    /**
     * The number of structural features of the '<em>Transition</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int TRANSITION_FEATURE_COUNT = AnnotationPackage.ANNOTATED_ELEMENT_FEATURE_COUNT
            + 5;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.behavior.PetriNet <em>Petri Net</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Petri Net</em>'.
     * @see bip2.ujf.verimag.bip.behavior.PetriNet
     * @generated
     */
    EClass getPetriNet();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.behavior.PetriNet#getStates <em>States</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>States</em>'.
     * @see bip2.ujf.verimag.bip.behavior.PetriNet#getStates()
     * @see #getPetriNet()
     * @generated
     */
    EReference getPetriNet_States();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.behavior.PetriNet#getInitStates <em>Init States</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Init States</em>'.
     * @see bip2.ujf.verimag.bip.behavior.PetriNet#getInitStates()
     * @see #getPetriNet()
     * @generated
     */
    EReference getPetriNet_InitStates();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.behavior.PetriNet#getTransitions <em>Transitions</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Transitions</em>'.
     * @see bip2.ujf.verimag.bip.behavior.PetriNet#getTransitions()
     * @see #getPetriNet()
     * @generated
     */
    EReference getPetriNet_Transitions();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.behavior.PetriNet#getInitialActions <em>Initial Actions</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Initial Actions</em>'.
     * @see bip2.ujf.verimag.bip.behavior.PetriNet#getInitialActions()
     * @see #getPetriNet()
     * @generated
     */
    EReference getPetriNet_InitialActions();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.behavior.State <em>State</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>State</em>'.
     * @see bip2.ujf.verimag.bip.behavior.State
     * @generated
     */
    EClass getState();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.behavior.State#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see bip2.ujf.verimag.bip.behavior.State#getName()
     * @see #getState()
     * @generated
     */
    EAttribute getState_Name();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.behavior.Transition <em>Transition</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Transition</em>'.
     * @see bip2.ujf.verimag.bip.behavior.Transition
     * @generated
     */
    EClass getTransition();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.behavior.Transition#getSources <em>Sources</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Sources</em>'.
     * @see bip2.ujf.verimag.bip.behavior.Transition#getSources()
     * @see #getTransition()
     * @generated
     */
    EReference getTransition_Sources();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.behavior.Transition#getDestinations <em>Destinations</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Destinations</em>'.
     * @see bip2.ujf.verimag.bip.behavior.Transition#getDestinations()
     * @see #getTransition()
     * @generated
     */
    EReference getTransition_Destinations();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.behavior.Transition#getTriggerPort <em>Trigger Port</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Trigger Port</em>'.
     * @see bip2.ujf.verimag.bip.behavior.Transition#getTriggerPort()
     * @see #getTransition()
     * @generated
     */
    EReference getTransition_TriggerPort();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.behavior.Transition#getActions <em>Actions</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Actions</em>'.
     * @see bip2.ujf.verimag.bip.behavior.Transition#getActions()
     * @see #getTransition()
     * @generated
     */
    EReference getTransition_Actions();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.behavior.Transition#getGuard <em>Guard</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Guard</em>'.
     * @see bip2.ujf.verimag.bip.behavior.Transition#getGuard()
     * @see #getTransition()
     * @generated
     */
    EReference getTransition_Guard();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    BehaviorFactory getBehaviorFactory();

    /**
     * <!-- begin-user-doc -->
     * Defines literals for the meta objects that represent
     * <ul>
     *   <li>each class,</li>
     *   <li>each feature of each class,</li>
     *   <li>each enum,</li>
     *   <li>and each data type</li>
     * </ul>
     * <!-- end-user-doc -->
     * @generated
     */
    interface Literals {
        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.behavior.impl.PetriNetImpl <em>Petri Net</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.behavior.impl.PetriNetImpl
         * @see bip2.ujf.verimag.bip.behavior.impl.BehaviorPackageImpl#getPetriNet()
         * @generated
         */
        EClass PETRI_NET = eINSTANCE.getPetriNet();

        /**
         * The meta object literal for the '<em><b>States</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PETRI_NET__STATES = eINSTANCE.getPetriNet_States();

        /**
         * The meta object literal for the '<em><b>Init States</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PETRI_NET__INIT_STATES = eINSTANCE.getPetriNet_InitStates();

        /**
         * The meta object literal for the '<em><b>Transitions</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PETRI_NET__TRANSITIONS = eINSTANCE.getPetriNet_Transitions();

        /**
         * The meta object literal for the '<em><b>Initial Actions</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference PETRI_NET__INITIAL_ACTIONS = eINSTANCE
                .getPetriNet_InitialActions();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.behavior.impl.StateImpl <em>State</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.behavior.impl.StateImpl
         * @see bip2.ujf.verimag.bip.behavior.impl.BehaviorPackageImpl#getState()
         * @generated
         */
        EClass STATE = eINSTANCE.getState();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute STATE__NAME = eINSTANCE.getState_Name();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.behavior.impl.TransitionImpl <em>Transition</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.behavior.impl.TransitionImpl
         * @see bip2.ujf.verimag.bip.behavior.impl.BehaviorPackageImpl#getTransition()
         * @generated
         */
        EClass TRANSITION = eINSTANCE.getTransition();

        /**
         * The meta object literal for the '<em><b>Sources</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference TRANSITION__SOURCES = eINSTANCE.getTransition_Sources();

        /**
         * The meta object literal for the '<em><b>Destinations</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference TRANSITION__DESTINATIONS = eINSTANCE
                .getTransition_Destinations();

        /**
         * The meta object literal for the '<em><b>Trigger Port</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference TRANSITION__TRIGGER_PORT = eINSTANCE
                .getTransition_TriggerPort();

        /**
         * The meta object literal for the '<em><b>Actions</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference TRANSITION__ACTIONS = eINSTANCE.getTransition_Actions();

        /**
         * The meta object literal for the '<em><b>Guard</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference TRANSITION__GUARD = eINSTANCE.getTransition_Guard();

    }

} //BehaviorPackage
