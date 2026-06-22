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

package bip2.ujf.verimag.bip.component.atom;

import bip2.ujf.verimag.bip.data.DataPackage;

import bip2.ujf.verimag.bip.port.PortPackage;

import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EEnum;
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
 * @see bip2.ujf.verimag.bip.component.atom.AtomFactory
 * @model kind="package"
 * @generated
 */
public interface AtomPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "atom";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/component/atom/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.component.atom";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    AtomPackage eINSTANCE = bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.component.atom.AtomInternalExternalPortDeclaration <em>Internal External Port Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.component.atom.AtomInternalExternalPortDeclaration
     * @see bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl#getAtomInternalExternalPortDeclaration()
     * @generated
     */
    int ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Port Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION__PORT_TYPE = PortPackage.PORT_DECLARATION__PORT_TYPE;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION__NAME = PortPackage.PORT_DECLARATION__NAME;

    /**
     * The feature id for the '<em><b>Data Parameters</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION__DATA_PARAMETERS = PortPackage.PORT_DECLARATION__DATA_PARAMETERS;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION__BIP_ANNOTATIONS = PortPackage.PORT_DECLARATION_FEATURE_COUNT
            + 0;

    /**
     * The number of structural features of the '<em>Internal External Port Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION_FEATURE_COUNT = PortPackage.PORT_DECLARATION_FEATURE_COUNT
            + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.component.atom.impl.AtomInternalPortDeclarationImpl <em>Internal Port Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.component.atom.impl.AtomInternalPortDeclarationImpl
     * @see bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl#getAtomInternalPortDeclaration()
     * @generated
     */
    int ATOM_INTERNAL_PORT_DECLARATION = 1;

    /**
     * The feature id for the '<em><b>Port Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_PORT_DECLARATION__PORT_TYPE = ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION__PORT_TYPE;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_PORT_DECLARATION__NAME = ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION__NAME;

    /**
     * The feature id for the '<em><b>Data Parameters</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_PORT_DECLARATION__DATA_PARAMETERS = ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION__DATA_PARAMETERS;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_PORT_DECLARATION__BIP_ANNOTATIONS = ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION__BIP_ANNOTATIONS;

    /**
     * The number of structural features of the '<em>Internal Port Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_PORT_DECLARATION_FEATURE_COUNT = ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION_FEATURE_COUNT
            + 0;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.component.atom.impl.AtomExternalPortDeclarationImpl <em>External Port Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.component.atom.impl.AtomExternalPortDeclarationImpl
     * @see bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl#getAtomExternalPortDeclaration()
     * @generated
     */
    int ATOM_EXTERNAL_PORT_DECLARATION = 2;

    /**
     * The feature id for the '<em><b>Port Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXTERNAL_PORT_DECLARATION__PORT_TYPE = ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION__PORT_TYPE;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXTERNAL_PORT_DECLARATION__NAME = ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION__NAME;

    /**
     * The feature id for the '<em><b>Data Parameters</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXTERNAL_PORT_DECLARATION__DATA_PARAMETERS = ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION__DATA_PARAMETERS;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXTERNAL_PORT_DECLARATION__BIP_ANNOTATIONS = ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Backend Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXTERNAL_PORT_DECLARATION__BACKEND_NAME = ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>Policy</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXTERNAL_PORT_DECLARATION__POLICY = ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION_FEATURE_COUNT
            + 1;

    /**
     * The number of structural features of the '<em>External Port Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXTERNAL_PORT_DECLARATION_FEATURE_COUNT = ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION_FEATURE_COUNT
            + 2;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.component.atom.impl.AtomInternalDataDeclarationImpl <em>Internal Data Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.component.atom.impl.AtomInternalDataDeclarationImpl
     * @see bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl#getAtomInternalDataDeclaration()
     * @generated
     */
    int ATOM_INTERNAL_DATA_DECLARATION = 3;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_DATA_DECLARATION__BIP_ANNOTATIONS = DataPackage.EXPLICIT_DATA_DECLARATION__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Data Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_DATA_DECLARATION__DATA_TYPE = DataPackage.EXPLICIT_DATA_DECLARATION__DATA_TYPE;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_DATA_DECLARATION__NAME = DataPackage.EXPLICIT_DATA_DECLARATION__NAME;

    /**
     * The feature id for the '<em><b>Value</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_DATA_DECLARATION__VALUE = DataPackage.EXPLICIT_DATA_DECLARATION__VALUE;

    /**
     * The feature id for the '<em><b>Const</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_DATA_DECLARATION__CONST = DataPackage.EXPLICIT_DATA_DECLARATION__CONST;

    /**
     * The feature id for the '<em><b>Exported</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_DATA_DECLARATION__EXPORTED = DataPackage.EXPLICIT_DATA_DECLARATION_FEATURE_COUNT
            + 0;

    /**
     * The number of structural features of the '<em>Internal Data Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_INTERNAL_DATA_DECLARATION_FEATURE_COUNT = DataPackage.EXPLICIT_DATA_DECLARATION_FEATURE_COUNT
            + 1;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.component.atom.impl.AtomExportPortDeclarationImpl <em>Export Port Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.component.atom.impl.AtomExportPortDeclarationImpl
     * @see bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl#getAtomExportPortDeclaration()
     * @generated
     */
    int ATOM_EXPORT_PORT_DECLARATION = 4;

    /**
     * The feature id for the '<em><b>Port Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXPORT_PORT_DECLARATION__PORT_TYPE = PortPackage.PORT_DECLARATION__PORT_TYPE;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXPORT_PORT_DECLARATION__NAME = PortPackage.PORT_DECLARATION__NAME;

    /**
     * The feature id for the '<em><b>Data Parameters</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXPORT_PORT_DECLARATION__DATA_PARAMETERS = PortPackage.PORT_DECLARATION__DATA_PARAMETERS;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXPORT_PORT_DECLARATION__BIP_ANNOTATIONS = PortPackage.PORT_DECLARATION_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>Port Declaration References</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXPORT_PORT_DECLARATION__PORT_DECLARATION_REFERENCES = PortPackage.PORT_DECLARATION_FEATURE_COUNT
            + 1;

    /**
     * The number of structural features of the '<em>Export Port Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int ATOM_EXPORT_PORT_DECLARATION_FEATURE_COUNT = PortPackage.PORT_DECLARATION_FEATURE_COUNT
            + 2;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.component.atom.EventConsumptionPolicy <em>Event Consumption Policy</em>}' enum.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.component.atom.EventConsumptionPolicy
     * @see bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl#getEventConsumptionPolicy()
     * @generated
     */
    int EVENT_CONSUMPTION_POLICY = 5;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.component.atom.AtomInternalExternalPortDeclaration <em>Internal External Port Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Internal External Port Declaration</em>'.
     * @see bip2.ujf.verimag.bip.component.atom.AtomInternalExternalPortDeclaration
     * @generated
     */
    EClass getAtomInternalExternalPortDeclaration();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.component.atom.AtomInternalPortDeclaration <em>Internal Port Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Internal Port Declaration</em>'.
     * @see bip2.ujf.verimag.bip.component.atom.AtomInternalPortDeclaration
     * @generated
     */
    EClass getAtomInternalPortDeclaration();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.component.atom.AtomExternalPortDeclaration <em>External Port Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>External Port Declaration</em>'.
     * @see bip2.ujf.verimag.bip.component.atom.AtomExternalPortDeclaration
     * @generated
     */
    EClass getAtomExternalPortDeclaration();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.component.atom.AtomExternalPortDeclaration#getBackendName <em>Backend Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Backend Name</em>'.
     * @see bip2.ujf.verimag.bip.component.atom.AtomExternalPortDeclaration#getBackendName()
     * @see #getAtomExternalPortDeclaration()
     * @generated
     */
    EAttribute getAtomExternalPortDeclaration_BackendName();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.component.atom.AtomExternalPortDeclaration#getPolicy <em>Policy</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Policy</em>'.
     * @see bip2.ujf.verimag.bip.component.atom.AtomExternalPortDeclaration#getPolicy()
     * @see #getAtomExternalPortDeclaration()
     * @generated
     */
    EAttribute getAtomExternalPortDeclaration_Policy();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.component.atom.AtomInternalDataDeclaration <em>Internal Data Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Internal Data Declaration</em>'.
     * @see bip2.ujf.verimag.bip.component.atom.AtomInternalDataDeclaration
     * @generated
     */
    EClass getAtomInternalDataDeclaration();

    /**
     * Returns the meta object for the attribute '{@link bip2.ujf.verimag.bip.component.atom.AtomInternalDataDeclaration#isExported <em>Exported</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Exported</em>'.
     * @see bip2.ujf.verimag.bip.component.atom.AtomInternalDataDeclaration#isExported()
     * @see #getAtomInternalDataDeclaration()
     * @generated
     */
    EAttribute getAtomInternalDataDeclaration_Exported();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.component.atom.AtomExportPortDeclaration <em>Export Port Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Export Port Declaration</em>'.
     * @see bip2.ujf.verimag.bip.component.atom.AtomExportPortDeclaration
     * @generated
     */
    EClass getAtomExportPortDeclaration();

    /**
     * Returns the meta object for the reference list '{@link bip2.ujf.verimag.bip.component.atom.AtomExportPortDeclaration#getPortDeclarationReferences <em>Port Declaration References</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Port Declaration References</em>'.
     * @see bip2.ujf.verimag.bip.component.atom.AtomExportPortDeclaration#getPortDeclarationReferences()
     * @see #getAtomExportPortDeclaration()
     * @generated
     */
    EReference getAtomExportPortDeclaration_PortDeclarationReferences();

    /**
     * Returns the meta object for enum '{@link bip2.ujf.verimag.bip.component.atom.EventConsumptionPolicy <em>Event Consumption Policy</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for enum '<em>Event Consumption Policy</em>'.
     * @see bip2.ujf.verimag.bip.component.atom.EventConsumptionPolicy
     * @generated
     */
    EEnum getEventConsumptionPolicy();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    AtomFactory getAtomFactory();

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
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.component.atom.AtomInternalExternalPortDeclaration <em>Internal External Port Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.component.atom.AtomInternalExternalPortDeclaration
         * @see bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl#getAtomInternalExternalPortDeclaration()
         * @generated
         */
        EClass ATOM_INTERNAL_EXTERNAL_PORT_DECLARATION = eINSTANCE
                .getAtomInternalExternalPortDeclaration();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.component.atom.impl.AtomInternalPortDeclarationImpl <em>Internal Port Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.component.atom.impl.AtomInternalPortDeclarationImpl
         * @see bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl#getAtomInternalPortDeclaration()
         * @generated
         */
        EClass ATOM_INTERNAL_PORT_DECLARATION = eINSTANCE
                .getAtomInternalPortDeclaration();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.component.atom.impl.AtomExternalPortDeclarationImpl <em>External Port Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.component.atom.impl.AtomExternalPortDeclarationImpl
         * @see bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl#getAtomExternalPortDeclaration()
         * @generated
         */
        EClass ATOM_EXTERNAL_PORT_DECLARATION = eINSTANCE
                .getAtomExternalPortDeclaration();

        /**
         * The meta object literal for the '<em><b>Backend Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute ATOM_EXTERNAL_PORT_DECLARATION__BACKEND_NAME = eINSTANCE
                .getAtomExternalPortDeclaration_BackendName();

        /**
         * The meta object literal for the '<em><b>Policy</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute ATOM_EXTERNAL_PORT_DECLARATION__POLICY = eINSTANCE
                .getAtomExternalPortDeclaration_Policy();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.component.atom.impl.AtomInternalDataDeclarationImpl <em>Internal Data Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.component.atom.impl.AtomInternalDataDeclarationImpl
         * @see bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl#getAtomInternalDataDeclaration()
         * @generated
         */
        EClass ATOM_INTERNAL_DATA_DECLARATION = eINSTANCE
                .getAtomInternalDataDeclaration();

        /**
         * The meta object literal for the '<em><b>Exported</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute ATOM_INTERNAL_DATA_DECLARATION__EXPORTED = eINSTANCE
                .getAtomInternalDataDeclaration_Exported();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.component.atom.impl.AtomExportPortDeclarationImpl <em>Export Port Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.component.atom.impl.AtomExportPortDeclarationImpl
         * @see bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl#getAtomExportPortDeclaration()
         * @generated
         */
        EClass ATOM_EXPORT_PORT_DECLARATION = eINSTANCE
                .getAtomExportPortDeclaration();

        /**
         * The meta object literal for the '<em><b>Port Declaration References</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference ATOM_EXPORT_PORT_DECLARATION__PORT_DECLARATION_REFERENCES = eINSTANCE
                .getAtomExportPortDeclaration_PortDeclarationReferences();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.component.atom.EventConsumptionPolicy <em>Event Consumption Policy</em>}' enum.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.component.atom.EventConsumptionPolicy
         * @see bip2.ujf.verimag.bip.component.atom.impl.AtomPackageImpl#getEventConsumptionPolicy()
         * @generated
         */
        EEnum EVENT_CONSUMPTION_POLICY = eINSTANCE.getEventConsumptionPolicy();

    }

} //AtomPackage
