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

package bip2.ujf.verimag.bip.component.compound;

import bip2.ujf.verimag.bip.data.DataPackage;
import bip2.ujf.verimag.bip.port.PortPackage;

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
 * @see bip2.ujf.verimag.bip.component.compound.CompoundFactory
 * @model kind="package"
 * @generated
 */
public interface CompoundPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "compound";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "http://bip2/ujf/verimag/bip/component/compound/1.0";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "bip2.ujf.verimag.bip.component.compound";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    CompoundPackage eINSTANCE = bip2.ujf.verimag.bip.component.compound.impl.CompoundPackageImpl
            .init();

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.component.compound.impl.CompoundExportPortDeclarationImpl <em>Export Port Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.component.compound.impl.CompoundExportPortDeclarationImpl
     * @see bip2.ujf.verimag.bip.component.compound.impl.CompoundPackageImpl#getCompoundExportPortDeclaration()
     * @generated
     */
    int COMPOUND_EXPORT_PORT_DECLARATION = 0;

    /**
     * The feature id for the '<em><b>Port Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_EXPORT_PORT_DECLARATION__PORT_TYPE = PortPackage.PORT_DECLARATION__PORT_TYPE;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_EXPORT_PORT_DECLARATION__NAME = PortPackage.PORT_DECLARATION__NAME;

    /**
     * The feature id for the '<em><b>Data Parameters</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_EXPORT_PORT_DECLARATION__DATA_PARAMETERS = PortPackage.PORT_DECLARATION__DATA_PARAMETERS;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_EXPORT_PORT_DECLARATION__BIP_ANNOTATIONS = PortPackage.PORT_DECLARATION_FEATURE_COUNT
            + 0;

    /**
     * The feature id for the '<em><b>Port Declaration References</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_EXPORT_PORT_DECLARATION__PORT_DECLARATION_REFERENCES = PortPackage.PORT_DECLARATION_FEATURE_COUNT
            + 1;

    /**
     * The number of structural features of the '<em>Export Port Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_EXPORT_PORT_DECLARATION_FEATURE_COUNT = PortPackage.PORT_DECLARATION_FEATURE_COUNT
            + 2;

    /**
     * The meta object id for the '{@link bip2.ujf.verimag.bip.component.compound.impl.CompoundExportDataDeclarationImpl <em>Export Data Declaration</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see bip2.ujf.verimag.bip.component.compound.impl.CompoundExportDataDeclarationImpl
     * @see bip2.ujf.verimag.bip.component.compound.impl.CompoundPackageImpl#getCompoundExportDataDeclaration()
     * @generated
     */
    int COMPOUND_EXPORT_DATA_DECLARATION = 1;

    /**
     * The feature id for the '<em><b>Bip Annotations</b></em>' map.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_EXPORT_DATA_DECLARATION__BIP_ANNOTATIONS = DataPackage.DATA_DECLARATION__BIP_ANNOTATIONS;

    /**
     * The feature id for the '<em><b>Data Type</b></em>' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_EXPORT_DATA_DECLARATION__DATA_TYPE = DataPackage.DATA_DECLARATION__DATA_TYPE;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_EXPORT_DATA_DECLARATION__NAME = DataPackage.DATA_DECLARATION__NAME;

    /**
     * The feature id for the '<em><b>Value</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_EXPORT_DATA_DECLARATION__VALUE = DataPackage.DATA_DECLARATION__VALUE;

    /**
     * The feature id for the '<em><b>Const</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_EXPORT_DATA_DECLARATION__CONST = DataPackage.DATA_DECLARATION__CONST;

    /**
     * The feature id for the '<em><b>Data Declaration Reference</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_EXPORT_DATA_DECLARATION__DATA_DECLARATION_REFERENCE = DataPackage.DATA_DECLARATION_FEATURE_COUNT
            + 0;

    /**
     * The number of structural features of the '<em>Export Data Declaration</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int COMPOUND_EXPORT_DATA_DECLARATION_FEATURE_COUNT = DataPackage.DATA_DECLARATION_FEATURE_COUNT
            + 1;

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.component.compound.CompoundExportPortDeclaration <em>Export Port Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Export Port Declaration</em>'.
     * @see bip2.ujf.verimag.bip.component.compound.CompoundExportPortDeclaration
     * @generated
     */
    EClass getCompoundExportPortDeclaration();

    /**
     * Returns the meta object for the containment reference list '{@link bip2.ujf.verimag.bip.component.compound.CompoundExportPortDeclaration#getPortDeclarationReferences <em>Port Declaration References</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Port Declaration References</em>'.
     * @see bip2.ujf.verimag.bip.component.compound.CompoundExportPortDeclaration#getPortDeclarationReferences()
     * @see #getCompoundExportPortDeclaration()
     * @generated
     */
    EReference getCompoundExportPortDeclaration_PortDeclarationReferences();

    /**
     * Returns the meta object for class '{@link bip2.ujf.verimag.bip.component.compound.CompoundExportDataDeclaration <em>Export Data Declaration</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Export Data Declaration</em>'.
     * @see bip2.ujf.verimag.bip.component.compound.CompoundExportDataDeclaration
     * @generated
     */
    EClass getCompoundExportDataDeclaration();

    /**
     * Returns the meta object for the containment reference '{@link bip2.ujf.verimag.bip.component.compound.CompoundExportDataDeclaration#getDataDeclarationReference <em>Data Declaration Reference</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference '<em>Data Declaration Reference</em>'.
     * @see bip2.ujf.verimag.bip.component.compound.CompoundExportDataDeclaration#getDataDeclarationReference()
     * @see #getCompoundExportDataDeclaration()
     * @generated
     */
    EReference getCompoundExportDataDeclaration_DataDeclarationReference();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    CompoundFactory getCompoundFactory();

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
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.component.compound.impl.CompoundExportPortDeclarationImpl <em>Export Port Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.component.compound.impl.CompoundExportPortDeclarationImpl
         * @see bip2.ujf.verimag.bip.component.compound.impl.CompoundPackageImpl#getCompoundExportPortDeclaration()
         * @generated
         */
        EClass COMPOUND_EXPORT_PORT_DECLARATION = eINSTANCE
                .getCompoundExportPortDeclaration();

        /**
         * The meta object literal for the '<em><b>Port Declaration References</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_EXPORT_PORT_DECLARATION__PORT_DECLARATION_REFERENCES = eINSTANCE
                .getCompoundExportPortDeclaration_PortDeclarationReferences();

        /**
         * The meta object literal for the '{@link bip2.ujf.verimag.bip.component.compound.impl.CompoundExportDataDeclarationImpl <em>Export Data Declaration</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see bip2.ujf.verimag.bip.component.compound.impl.CompoundExportDataDeclarationImpl
         * @see bip2.ujf.verimag.bip.component.compound.impl.CompoundPackageImpl#getCompoundExportDataDeclaration()
         * @generated
         */
        EClass COMPOUND_EXPORT_DATA_DECLARATION = eINSTANCE
                .getCompoundExportDataDeclaration();

        /**
         * The meta object literal for the '<em><b>Data Declaration Reference</b></em>' containment reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference COMPOUND_EXPORT_DATA_DECLARATION__DATA_DECLARATION_REFERENCE = eINSTANCE
                .getCompoundExportDataDeclaration_DataDeclarationReference();

    }

} //CompoundPackage
