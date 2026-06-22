/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
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

package bip2.ujf.verimag.bip.invariant;

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
 * @see bip2.ujf.verimag.bip.invariant.InvariantFactory
 * @model kind="package"
 * @generated
 */
public interface InvariantPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "invariant";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/invariant/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.invariant";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    InvariantPackage eINSTANCE = bip2.ujf.verimag.bip.invariant.impl.InvariantPackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.invariant.Invariant <em>Invariant</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.invariant.Invariant
     * @see bip2.ujf.verimag.bip.invariant.impl.InvariantPackageImpl#getInvariant()
     * @generated
     */
    int INVARIANT = 0;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int INVARIANT__NAME = 0;

    /**
     * The feature id for the '<em><b>Guard</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int INVARIANT__GUARD = 1;

    /**
     * The number of structural features of the '<em>Invariant</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int INVARIANT_FEATURE_COUNT = 2;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.invariant.impl.AtomInvariantImpl <em>Atom Invariant</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.invariant.impl.AtomInvariantImpl
     * @see bip2.ujf.verimag.bip.invariant.impl.InvariantPackageImpl#getAtomInvariant()
     * @generated
     */
    int ATOM_INVARIANT = 1;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INVARIANT__NAME = INVARIANT__NAME;

    /**
     * The feature id for the '<em><b>Guard</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INVARIANT__GUARD = INVARIANT__GUARD;

    /**
     * The feature id for the '<em><b>Exact State</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INVARIANT__EXACT_STATE = INVARIANT_FEATURE_COUNT + 0;

    /**
     * The feature id for the '<em><b>Sources</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INVARIANT__SOURCES = INVARIANT_FEATURE_COUNT + 1;

    /**
     * The number of structural features of the '<em>Atom Invariant</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INVARIANT_FEATURE_COUNT = INVARIANT_FEATURE_COUNT + 2;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.invariant.Invariant <em>Invariant</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Invariant</em>'.
     * @see bip2.ujf.verimag.bip.invariant.Invariant
     * @generated
     */
    EClass getInvariant();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.invariant.Invariant#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see bip2.ujf.verimag.bip.invariant.Invariant#getName()
     * @see #getInvariant()
     * @generated
     */
    EAttribute getInvariant_Name();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.invariant.Invariant#getGuard <em>Guard</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Guard</em>'.
     * @see bip2.ujf.verimag.bip.invariant.Invariant#getGuard()
     * @see #getInvariant()
     * @generated
     */
    EReference getInvariant_Guard();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.invariant.AtomInvariant <em>Atom Invariant</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Atom Invariant</em>'.
     * @see bip2.ujf.verimag.bip.invariant.AtomInvariant
     * @generated
     */
    EClass getAtomInvariant();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.invariant.AtomInvariant#isExactState <em>Exact State</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Exact State</em>'.
     * @see bip2.ujf.verimag.bip.invariant.AtomInvariant#isExactState()
     * @see #getAtomInvariant()
     * @generated
     */
    EAttribute getAtomInvariant_ExactState();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.invariant.AtomInvariant#getSources <em>Sources</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Sources</em>'.
     * @see bip2.ujf.verimag.bip.invariant.AtomInvariant#getSources()
     * @see #getAtomInvariant()
     * @generated
     */
    EReference getAtomInvariant_Sources();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    InvariantFactory getInvariantFactory();

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
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.invariant.Invariant <em>Invariant</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.invariant.Invariant
         * @see bip2.ujf.verimag.bip.invariant.impl.InvariantPackageImpl#getInvariant()
         * @generated
         */
        EClass INVARIANT = eINSTANCE.getInvariant();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute INVARIANT__NAME = eINSTANCE.getInvariant_Name();

        /**
         * The meta object literal for the '<em><b>Guard</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference INVARIANT__GUARD = eINSTANCE.getInvariant_Guard();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.invariant.impl.AtomInvariantImpl <em>Atom Invariant</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.invariant.impl.AtomInvariantImpl
         * @see bip2.ujf.verimag.bip.invariant.impl.InvariantPackageImpl#getAtomInvariant()
         * @generated
         */
        EClass ATOM_INVARIANT = eINSTANCE.getAtomInvariant();

        /**
         * The meta object literal for the '<em><b>Exact State</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute ATOM_INVARIANT__EXACT_STATE = eINSTANCE
                .getAtomInvariant_ExactState();

        /**
         * The meta object literal for the '<em><b>Sources</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_INVARIANT__SOURCES = eINSTANCE
                .getAtomInvariant_Sources();

    }

} //InvariantPackage
