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

package bip2.ujf.verimag.bip.port.impl;

import bip2.ujf.verimag.bip.actionlang.ValuedExpression;
import bip2.ujf.verimag.bip.annotation.impl.AnnotatedElementImpl;
import bip2.ujf.verimag.bip.data.DataType;

import bip2.ujf.verimag.bip.port.PortDataParameterDeclaration;
import bip2.ujf.verimag.bip.port.PortPackage;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.common.notify.NotificationChain;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

import org.eclipse.emf.ecore.impl.EObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Data Parameter Declaration</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.port.impl.PortDataParameterDeclarationImpl#getDataType <em>Data Type</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.port.impl.PortDataParameterDeclarationImpl#getName <em>Name</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.port.impl.PortDataParameterDeclarationImpl#getValue <em>Value</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.port.impl.PortDataParameterDeclarationImpl#isConst <em>Const</em>}</li>
 * </ul>
 *
 * @generated
 */
public class PortDataParameterDeclarationImpl extends AnnotatedElementImpl
        implements PortDataParameterDeclaration {
    /**
     * The cached value of the '{@link #getDataType() <em>Data Type</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDataType()
     * @generated
     * @ordered
     */
    protected DataType dataType;
    /**
     * The default value of the '{@link #getName() <em>Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getName()
     * @generated
     * @ordered
     */
    protected static final String NAME_EDEFAULT = null;
    /**
     * The cached value of the '{@link #getName() <em>Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getName()
     * @generated
     * @ordered
     */
    protected String name = NAME_EDEFAULT;
    /**
     * The cached value of the '{@link #getValue() <em>Value</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getValue()
     * @generated
     * @ordered
     */
    protected ValuedExpression value;
    /**
     * The default value of the '{@link #isConst() <em>Const</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #isConst()
     * @generated
     * @ordered
     */
    protected static final boolean CONST_EDEFAULT = false;
    /**
     * The cached value of the '{@link #isConst() <em>Const</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #isConst()
     * @generated
     * @ordered
     */
    protected boolean const_ = CONST_EDEFAULT;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected PortDataParameterDeclarationImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return PortPackage.Literals.PORT_DATA_PARAMETER_DECLARATION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataType getDataType() {
        if (dataType != null && ((EObject) dataType).eIsProxy()) {
            InternalEObject oldDataType = (InternalEObject) dataType;
            dataType = (DataType) eResolveProxy(oldDataType);
            if (dataType != oldDataType) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            PortPackage.PORT_DATA_PARAMETER_DECLARATION__DATA_TYPE,
                            oldDataType, dataType));
            }
        }
        return dataType;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataType basicGetDataType() {
        return dataType;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setDataType(DataType newDataType) {
        DataType oldDataType = dataType;
        dataType = newDataType;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PortPackage.PORT_DATA_PARAMETER_DECLARATION__DATA_TYPE,
                    oldDataType, dataType));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String getName() {
        return name;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setName(String newName) {
        String oldName = name;
        name = newName;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PortPackage.PORT_DATA_PARAMETER_DECLARATION__NAME, oldName,
                    name));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ValuedExpression getValue() {
        return value;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetValue(ValuedExpression newValue,
            NotificationChain msgs) {
        ValuedExpression oldValue = value;
        value = newValue;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    PortPackage.PORT_DATA_PARAMETER_DECLARATION__VALUE,
                    oldValue, newValue);
            if (msgs == null)
                msgs = notification;
            else
                msgs.add(notification);
        }
        return msgs;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setValue(ValuedExpression newValue) {
        if (newValue != value) {
            NotificationChain msgs = null;
            if (value != null)
                msgs = ((InternalEObject) value).eInverseRemove(this,
                        EOPPOSITE_FEATURE_BASE
                                - PortPackage.PORT_DATA_PARAMETER_DECLARATION__VALUE,
                        null, msgs);
            if (newValue != null)
                msgs = ((InternalEObject) newValue).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - PortPackage.PORT_DATA_PARAMETER_DECLARATION__VALUE,
                        null, msgs);
            msgs = basicSetValue(newValue, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PortPackage.PORT_DATA_PARAMETER_DECLARATION__VALUE,
                    newValue, newValue));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public boolean isConst() {
        return const_;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setConst(boolean newConst) {
        boolean oldConst = const_;
        const_ = newConst;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    PortPackage.PORT_DATA_PARAMETER_DECLARATION__CONST,
                    oldConst, const_));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public NotificationChain eInverseRemove(InternalEObject otherEnd,
            int featureID, NotificationChain msgs) {
        switch (featureID) {
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__VALUE:
            return basicSetValue(null, msgs);
        }
        return super.eInverseRemove(otherEnd, featureID, msgs);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__DATA_TYPE:
            if (resolve)
                return getDataType();
            return basicGetDataType();
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__NAME:
            return getName();
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__VALUE:
            return getValue();
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__CONST:
            return isConst();
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
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__DATA_TYPE:
            setDataType((DataType) newValue);
            return;
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__NAME:
            setName((String) newValue);
            return;
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__VALUE:
            setValue((ValuedExpression) newValue);
            return;
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__CONST:
            setConst((Boolean) newValue);
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
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__DATA_TYPE:
            setDataType((DataType) null);
            return;
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__NAME:
            setName(NAME_EDEFAULT);
            return;
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__VALUE:
            setValue((ValuedExpression) null);
            return;
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__CONST:
            setConst(CONST_EDEFAULT);
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
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__DATA_TYPE:
            return dataType != null;
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__NAME:
            return NAME_EDEFAULT == null ? name != null
                    : !NAME_EDEFAULT.equals(name);
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__VALUE:
            return value != null;
        case PortPackage.PORT_DATA_PARAMETER_DECLARATION__CONST:
            return const_ != CONST_EDEFAULT;
        }
        return super.eIsSet(featureID);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public String toString() {
        if (eIsProxy())
            return super.toString();

        StringBuffer result = new StringBuffer(super.toString());
        result.append(" (name: ");
        result.append(name);
        result.append(", const: ");
        result.append(const_);
        result.append(')');
        return result.toString();
    }

} //PortDataParameterDeclarationImpl
