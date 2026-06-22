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

package bip2.ujf.verimag.bip.packaging.impl;

import bip2.ujf.verimag.bip.packaging.*;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.impl.EFactoryImpl;

import org.eclipse.emf.ecore.plugin.EcorePlugin;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Factory</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class PackagingFactoryImpl extends EFactoryImpl
        implements PackagingFactory {
    /**
     * Creates the default factory implementation.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static PackagingFactory init() {
        try {
            PackagingFactory thePackagingFactory = (PackagingFactory) EPackage.Registry.INSTANCE
                    .getEFactory(PackagingPackage.eNS_URI);
            if (thePackagingFactory != null) {
                return thePackagingFactory;
            }
        } catch (Exception exception) {
            EcorePlugin.INSTANCE.log(exception);
        }
        return new PackagingFactoryImpl();
    }

    /**
     * Creates an instance of the factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PackagingFactoryImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EObject create(EClass eClass) {
        switch (eClass.getClassifierID()) {
        case PackagingPackage.BIP_PACKAGE:
            return (EObject) createBipPackage();
        case PackagingPackage.BIP_PACKAGE_SET:
            return (EObject) createBipPackageSet();
        case PackagingPackage.CONST_DATA_DECLARATION:
            return (EObject) createConstDataDeclaration();
        case PackagingPackage.FUNCTION_CALL_PROTOTYPE:
            return (EObject) createFunctionCallPrototype();
        case PackagingPackage.BINARY_OP_PROTOTYPE:
            return (EObject) createBinaryOpPrototype();
        case PackagingPackage.UNARY_OP_PROTOTYPE:
            return (EObject) createUnaryOpPrototype();
        case PackagingPackage.PROTOTYPE_PARAMETER_DECLARATION:
            return (EObject) createPrototypeParameterDeclaration();
        default:
            throw new IllegalArgumentException("The class '" + eClass.getName()
                    + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public BipPackage createBipPackage() {
        BipPackageImpl bipPackage = new BipPackageImpl();
        return bipPackage;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public BipPackageSet createBipPackageSet() {
        BipPackageSetImpl bipPackageSet = new BipPackageSetImpl();
        return bipPackageSet;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ConstDataDeclaration createConstDataDeclaration() {
        ConstDataDeclarationImpl constDataDeclaration = new ConstDataDeclarationImpl();
        return constDataDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public FunctionCallPrototype createFunctionCallPrototype() {
        FunctionCallPrototypeImpl functionCallPrototype = new FunctionCallPrototypeImpl();
        return functionCallPrototype;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public BinaryOpPrototype createBinaryOpPrototype() {
        BinaryOpPrototypeImpl binaryOpPrototype = new BinaryOpPrototypeImpl();
        return binaryOpPrototype;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public UnaryOpPrototype createUnaryOpPrototype() {
        UnaryOpPrototypeImpl unaryOpPrototype = new UnaryOpPrototypeImpl();
        return unaryOpPrototype;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PrototypeParameterDeclaration createPrototypeParameterDeclaration() {
        PrototypeParameterDeclarationImpl prototypeParameterDeclaration = new PrototypeParameterDeclarationImpl();
        return prototypeParameterDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public PackagingPackage getPackagingPackage() {
        return (PackagingPackage) getEPackage();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @deprecated
     * @generated
     */
    @Deprecated
    public static PackagingPackage getPackage() {
        return PackagingPackage.eINSTANCE;
    }

} //PackagingFactoryImpl
