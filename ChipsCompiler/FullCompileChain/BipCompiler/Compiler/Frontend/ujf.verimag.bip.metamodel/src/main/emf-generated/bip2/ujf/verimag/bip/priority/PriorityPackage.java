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

package bip2.ujf.verimag.bip.priority;

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
 * @see bip2.ujf.verimag.bip.priority.PriorityFactory
 * @model kind="package"
 * @generated
 */
public interface PriorityPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "priority";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/priority/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.priority";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    PriorityPackage eINSTANCE = bip2.ujf.verimag.bip.priority.impl.PriorityPackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.priority.impl.CompoundPriorityDeclarationImpl <em>Compound Priority Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.priority.impl.CompoundPriorityDeclarationImpl
     * @see bip2.ujf.verimag.bip.priority.impl.PriorityPackageImpl#getCompoundPriorityDeclaration()
     * @generated
     */
    int COMPOUND_PRIORITY_DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Low</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_PRIORITY_DECLARATION__LOW = 0;

    /**
     * The feature id for the '<em><b>High</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_PRIORITY_DECLARATION__HIGH = 1;

    /**
     * The feature id for the '<em><b>Guard</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_PRIORITY_DECLARATION__GUARD = 2;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_PRIORITY_DECLARATION__NAME = 3;

    /**
     * The number of structural features of the '<em>Compound Priority Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_PRIORITY_DECLARATION_FEATURE_COUNT = 4;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.priority.impl.ConnectorInteractionImpl <em>Connector Interaction</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.priority.impl.ConnectorInteractionImpl
     * @see bip2.ujf.verimag.bip.priority.impl.PriorityPackageImpl#getConnectorInteraction()
     * @generated
     */
    int CONNECTOR_INTERACTION = 1;

    /**
     * The feature id for the '<em><b>Connector Declaration</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION__CONNECTOR_DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Port Declaration References</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION__PORT_DECLARATION_REFERENCES = 1;

    /**
     * The number of structural features of the '<em>Connector Interaction</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CONNECTOR_INTERACTION_FEATURE_COUNT = 2;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.priority.impl.AtomPriorityDeclarationImpl <em>Atom Priority Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.priority.impl.AtomPriorityDeclarationImpl
     * @see bip2.ujf.verimag.bip.priority.impl.PriorityPackageImpl#getAtomPriorityDeclaration()
     * @generated
     */
    int ATOM_PRIORITY_DECLARATION = 2;

    /**
     * The feature id for the '<em><b>Guard</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_PRIORITY_DECLARATION__GUARD = 0;

    /**
     * The feature id for the '<em><b>Low</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_PRIORITY_DECLARATION__LOW = 1;

    /**
     * The feature id for the '<em><b>High</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_PRIORITY_DECLARATION__HIGH = 2;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_PRIORITY_DECLARATION__NAME = 3;

    /**
     * The number of structural features of the '<em>Atom Priority Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_PRIORITY_DECLARATION_FEATURE_COUNT = 4;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration <em>Compound Priority Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Compound Priority Declaration</em>'.
     * @see bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration
     * @generated
     */
    EClass getCompoundPriorityDeclaration();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration#getLow <em>Low</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Low</em>'.
     * @see bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration#getLow()
     * @see #getCompoundPriorityDeclaration()
     * @generated
     */
    EReference getCompoundPriorityDeclaration_Low();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration#getHigh <em>High</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>High</em>'.
     * @see bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration#getHigh()
     * @see #getCompoundPriorityDeclaration()
     * @generated
     */
    EReference getCompoundPriorityDeclaration_High();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration#getGuard <em>Guard</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Guard</em>'.
     * @see bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration#getGuard()
     * @see #getCompoundPriorityDeclaration()
     * @generated
     */
    EReference getCompoundPriorityDeclaration_Guard();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration#getName()
     * @see #getCompoundPriorityDeclaration()
     * @generated
     */
    EAttribute getCompoundPriorityDeclaration_Name();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.priority.ConnectorInteraction <em>Connector Interaction</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Connector Interaction</em>'.
     * @see bip2.ujf.verimag.bip.priority.ConnectorInteraction
     * @generated
     */
    EClass getConnectorInteraction();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.priority.ConnectorInteraction#getConnectorDeclaration <em>Connector Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Connector Declaration</em>'.
     * @see bip2.ujf.verimag.bip.priority.ConnectorInteraction#getConnectorDeclaration()
     * @see #getConnectorInteraction()
     * @generated
     */
    EReference getConnectorInteraction_ConnectorDeclaration();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.priority.ConnectorInteraction#getPortDeclarationReferences <em>Port Declaration References</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Port Declaration References</em>'.
     * @see bip2.ujf.verimag.bip.priority.ConnectorInteraction#getPortDeclarationReferences()
     * @see #getConnectorInteraction()
     * @generated
     */
    EReference getConnectorInteraction_PortDeclarationReferences();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration <em>Atom Priority Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Atom Priority Declaration</em>'.
     * @see bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration
     * @generated
     */
    EClass getAtomPriorityDeclaration();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration#getGuard <em>Guard</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Guard</em>'.
     * @see bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration#getGuard()
     * @see #getAtomPriorityDeclaration()
     * @generated
     */
    EReference getAtomPriorityDeclaration_Guard();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration#getLow <em>Low</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>Low</em>'.
     * @see bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration#getLow()
     * @see #getAtomPriorityDeclaration()
     * @generated
     */
    EReference getAtomPriorityDeclaration_Low();

    /**
     * Returns the meta object for the reference '{@link bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration#getHigh <em>High</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference '<em>High</em>'.
     * @see bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration#getHigh()
     * @see #getAtomPriorityDeclaration()
     * @generated
     */
    EReference getAtomPriorityDeclaration_High();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration#getName()
     * @see #getAtomPriorityDeclaration()
     * @generated
     */
    EAttribute getAtomPriorityDeclaration_Name();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    PriorityFactory getPriorityFactory();

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
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.priority.impl.CompoundPriorityDeclarationImpl <em>Compound Priority Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.priority.impl.CompoundPriorityDeclarationImpl
         * @see bip2.ujf.verimag.bip.priority.impl.PriorityPackageImpl#getCompoundPriorityDeclaration()
         * @generated
         */
        EClass COMPOUND_PRIORITY_DECLARATION = eINSTANCE
                .getCompoundPriorityDeclaration();

        /**
         * The meta object literal for the '<em><b>Low</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_PRIORITY_DECLARATION__LOW = eINSTANCE
                .getCompoundPriorityDeclaration_Low();

        /**
         * The meta object literal for the '<em><b>High</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_PRIORITY_DECLARATION__HIGH = eINSTANCE
                .getCompoundPriorityDeclaration_High();

        /**
         * The meta object literal for the '<em><b>Guard</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_PRIORITY_DECLARATION__GUARD = eINSTANCE
                .getCompoundPriorityDeclaration_Guard();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute COMPOUND_PRIORITY_DECLARATION__NAME = eINSTANCE
                .getCompoundPriorityDeclaration_Name();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.priority.impl.ConnectorInteractionImpl <em>Connector Interaction</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.priority.impl.ConnectorInteractionImpl
         * @see bip2.ujf.verimag.bip.priority.impl.PriorityPackageImpl#getConnectorInteraction()
         * @generated
         */
        EClass CONNECTOR_INTERACTION = eINSTANCE.getConnectorInteraction();

        /**
         * The meta object literal for the '<em><b>Connector Declaration</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_INTERACTION__CONNECTOR_DECLARATION = eINSTANCE
                .getConnectorInteraction_ConnectorDeclaration();

        /**
         * The meta object literal for the '<em><b>Port Declaration References</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CONNECTOR_INTERACTION__PORT_DECLARATION_REFERENCES = eINSTANCE
                .getConnectorInteraction_PortDeclarationReferences();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.priority.impl.AtomPriorityDeclarationImpl <em>Atom Priority Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.priority.impl.AtomPriorityDeclarationImpl
         * @see bip2.ujf.verimag.bip.priority.impl.PriorityPackageImpl#getAtomPriorityDeclaration()
         * @generated
         */
        EClass ATOM_PRIORITY_DECLARATION = eINSTANCE
                .getAtomPriorityDeclaration();

        /**
         * The meta object literal for the '<em><b>Guard</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_PRIORITY_DECLARATION__GUARD = eINSTANCE
                .getAtomPriorityDeclaration_Guard();

        /**
         * The meta object literal for the '<em><b>Low</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_PRIORITY_DECLARATION__LOW = eINSTANCE
                .getAtomPriorityDeclaration_Low();

        /**
         * The meta object literal for the '<em><b>High</b></em>' reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_PRIORITY_DECLARATION__HIGH = eINSTANCE
                .getAtomPriorityDeclaration_High();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute ATOM_PRIORITY_DECLARATION__NAME = eINSTANCE
                .getAtomPriorityDeclaration_Name();

    }

} //PriorityPackage
