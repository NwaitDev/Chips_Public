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

package bip2.ujf.verimag.bip.data.impl;

import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataDeclarationReferenceDataParameter;
import bip2.ujf.verimag.bip.data.DataPackage;
import bip2.ujf.verimag.bip.data.DataType;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

import org.eclipse.emf.ecore.impl.EObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Declaration Reference Data Parameter</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.data.impl.DataDeclarationReferenceDataParameterImpl#getParameterDeclaration <em>Parameter Declaration</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.data.impl.DataDeclarationReferenceDataParameterImpl#getType <em>Type</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.data.impl.DataDeclarationReferenceDataParameterImpl#getDataDeclarationReference <em>Data Declaration Reference</em>}</li>
 * </ul>
 *
 * @generated
 */
public class DataDeclarationReferenceDataParameterImpl extends
        AnnotatedEObjectImpl implements DataDeclarationReferenceDataParameter {
    /**
     * The cached value of the '{@link #getParameterDeclaration() <em>Parameter Declaration</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getParameterDeclaration()
     * @generated
     * @ordered
     */
    protected DataDeclaration parameterDeclaration;

    /**
     * The cached value of the '{@link #getType() <em>Type</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getType()
     * @generated
     * @ordered
     */
    protected DataType type;

    /**
     * The cached value of the '{@link #getDataDeclarationReference() <em>Data Declaration Reference</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDataDeclarationReference()
     * @generated
     * @ordered
     */
    protected DataDeclaration dataDeclarationReference;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected DataDeclarationReferenceDataParameterImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return DataPackage.Literals.DATA_DECLARATION_REFERENCE_DATA_PARAMETER;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataDeclaration getParameterDeclaration() {
        if (parameterDeclaration != null
                && ((EObject) parameterDeclaration).eIsProxy()) {
            InternalEObject oldParameterDeclaration = (InternalEObject) parameterDeclaration;
            parameterDeclaration = (DataDeclaration) eResolveProxy(
                    oldParameterDeclaration);
            if (parameterDeclaration != oldParameterDeclaration) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__PARAMETER_DECLARATION,
                            oldParameterDeclaration, parameterDeclaration));
            }
        }
        return parameterDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataDeclaration basicGetParameterDeclaration() {
        return parameterDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setParameterDeclaration(
            DataDeclaration newParameterDeclaration) {
        DataDeclaration oldParameterDeclaration = parameterDeclaration;
        parameterDeclaration = newParameterDeclaration;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__PARAMETER_DECLARATION,
                    oldParameterDeclaration, parameterDeclaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataType getType() {
        if (type != null && ((EObject) type).eIsProxy()) {
            InternalEObject oldType = (InternalEObject) type;
            type = (DataType) eResolveProxy(oldType);
            if (type != oldType) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__TYPE,
                            oldType, type));
            }
        }
        return type;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataType basicGetType() {
        return type;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setType(DataType newType) {
        DataType oldType = type;
        type = newType;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__TYPE,
                    oldType, type));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataDeclaration getDataDeclarationReference() {
        if (dataDeclarationReference != null
                && ((EObject) dataDeclarationReference).eIsProxy()) {
            InternalEObject oldDataDeclarationReference = (InternalEObject) dataDeclarationReference;
            dataDeclarationReference = (DataDeclaration) eResolveProxy(
                    oldDataDeclarationReference);
            if (dataDeclarationReference != oldDataDeclarationReference) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__DATA_DECLARATION_REFERENCE,
                            oldDataDeclarationReference,
                            dataDeclarationReference));
            }
        }
        return dataDeclarationReference;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataDeclaration basicGetDataDeclarationReference() {
        return dataDeclarationReference;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setDataDeclarationReference(
            DataDeclaration newDataDeclarationReference) {
        DataDeclaration oldDataDeclarationReference = dataDeclarationReference;
        dataDeclarationReference = newDataDeclarationReference;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__DATA_DECLARATION_REFERENCE,
                    oldDataDeclarationReference, dataDeclarationReference));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__PARAMETER_DECLARATION:
            if (resolve)
                return getParameterDeclaration();
            return basicGetParameterDeclaration();
        case DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__TYPE:
            if (resolve)
                return getType();
            return basicGetType();
        case DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__DATA_DECLARATION_REFERENCE:
            if (resolve)
                return getDataDeclarationReference();
            return basicGetDataDeclarationReference();
        }
        return super.eGet(featureID, resolve, coreType);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void eSet(int featureID, Object newValue) {
        switch (featureID) {
        case DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__PARAMETER_DECLARATION:
            setParameterDeclaration((DataDeclaration) newValue);
            return;
        case DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__TYPE:
            setType((DataType) newValue);
            return;
        case DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__DATA_DECLARATION_REFERENCE:
            setDataDeclarationReference((DataDeclaration) newValue);
            return;
        }
        super.eSet(featureID, newValue);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void eUnset(int featureID) {
        switch (featureID) {
        case DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__PARAMETER_DECLARATION:
            setParameterDeclaration((DataDeclaration) null);
            return;
        case DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__TYPE:
            setType((DataType) null);
            return;
        case DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__DATA_DECLARATION_REFERENCE:
            setDataDeclarationReference((DataDeclaration) null);
            return;
        }
        super.eUnset(featureID);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public boolean eIsSet(int featureID) {
        switch (featureID) {
        case DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__PARAMETER_DECLARATION:
            return parameterDeclaration != null;
        case DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__TYPE:
            return type != null;
        case DataPackage.DATA_DECLARATION_REFERENCE_DATA_PARAMETER__DATA_DECLARATION_REFERENCE:
            return dataDeclarationReference != null;
        }
        return super.eIsSet(featureID);
    }

} //DataDeclarationReferenceDataParameterImpl
