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

package bip2.ujf.verimag.bip.actionlang.impl;

import bip2.ujf.verimag.bip.actionlang.ActionlangPackage;
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression;

import bip2.ujf.verimag.bip.data.DataDeclaration;

import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.types.Type;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.util.BasicEList;
import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;
import org.eclipse.emf.ecore.impl.EObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Direct Data Declaration Reference Expression</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.DirectDataDeclarationReferenceExpressionImpl#getDataDeclaration <em>Data Declaration</em>}</li>
 * </ul>
 *
 * @generated
 */
public class DirectDataDeclarationReferenceExpressionImpl
        extends ValuedExpressionImpl
        implements DirectDataDeclarationReferenceExpression {
    /**
     * The cached value of the '{@link #getDataDeclaration() <em>Data Declaration</em>}' reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getDataDeclaration()
     * @generated
     * @ordered
     */
    protected DataDeclaration dataDeclaration;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected DirectDataDeclarationReferenceExpressionImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return ActionlangPackage.Literals.DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataDeclaration getDataDeclaration() {
        if (dataDeclaration != null && ((EObject) dataDeclaration).eIsProxy()) {
            InternalEObject oldDataDeclaration = (InternalEObject) dataDeclaration;
            dataDeclaration = (DataDeclaration) eResolveProxy(
                    oldDataDeclaration);
            if (dataDeclaration != oldDataDeclaration) {
                if (eNotificationRequired())
                    eNotify(new ENotificationImpl(this, Notification.RESOLVE,
                            ActionlangPackage.DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION__DATA_DECLARATION,
                            oldDataDeclaration, dataDeclaration));
            }
        }
        return dataDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public DataDeclaration basicGetDataDeclaration() {
        return dataDeclaration;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setDataDeclaration(DataDeclaration newDataDeclaration) {
        DataDeclaration oldDataDeclaration = dataDeclaration;
        dataDeclaration = newDataDeclaration;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ActionlangPackage.DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION__DATA_DECLARATION,
                    oldDataDeclaration, dataDeclaration));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public Type getType() {
        return getDataDeclaration().getDataType();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated NOT
     */
    public boolean isConst() {
        return getDataDeclaration().isConst();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
        case ActionlangPackage.DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION__DATA_DECLARATION:
            if (resolve)
                return getDataDeclaration();
            return basicGetDataDeclaration();
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
        case ActionlangPackage.DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION__DATA_DECLARATION:
            setDataDeclaration((DataDeclaration) newValue);
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
        case ActionlangPackage.DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION__DATA_DECLARATION:
            setDataDeclaration((DataDeclaration) null);
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
        case ActionlangPackage.DIRECT_DATA_DECLARATION_REFERENCE_EXPRESSION__DATA_DECLARATION:
            return dataDeclaration != null;
        }
        return super.eIsSet(featureID);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getReadVariables() {
        EList<DataDeclaration> ret = new BasicEList<DataDeclaration>();

        ret.add(getDataDeclaration());

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getMayReadVariables() {
        EList<DataDeclaration> ret = new BasicEList<DataDeclaration>();

        ret.add(getDataDeclaration());

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getWriteVariables() {
        return new BasicEList<DataDeclaration>();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getMayWriteVariables() {
        return new BasicEList<DataDeclaration>();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<Expression> getMayReadUninitializedVariables(
            EList<DataDeclaration> uninitialized) {
        EList<Expression> ret = new BasicEList<Expression>();

        if (uninitialized.contains(getDataDeclaration())) {
            ret.add(this);
        }

        return ret;
    }

} //DirectDataDeclarationReferenceExpressionImpl
