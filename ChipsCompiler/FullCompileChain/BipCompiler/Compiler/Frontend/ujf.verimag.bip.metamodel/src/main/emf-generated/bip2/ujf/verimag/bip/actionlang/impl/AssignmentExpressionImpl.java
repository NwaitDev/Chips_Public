/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Anakreontas Mentis
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
import bip2.ujf.verimag.bip.actionlang.AssignmentExpression;
import bip2.ujf.verimag.bip.actionlang.DirectDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.Expression;
import bip2.ujf.verimag.bip.actionlang.SubDataDeclarationReferenceExpression;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;

import bip2.ujf.verimag.bip.data.DataDeclaration;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.BasicEList;
import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Assignment Expression</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.AssignmentExpressionImpl#getLhs <em>Lhs</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.AssignmentExpressionImpl#getRhs <em>Rhs</em>}</li>
 * </ul>
 *
 * @generated
 */
public class AssignmentExpressionImpl extends AnnotatedEObjectImpl
        implements AssignmentExpression {
    /**
     * The cached value of the '{@link #getLhs() <em>Lhs</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getLhs()
     * @generated
     * @ordered
     */
    protected ValuedExpression lhs;

    /**
     * The cached value of the '{@link #getRhs() <em>Rhs</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getRhs()
     * @generated
     * @ordered
     */
    protected ValuedExpression rhs;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected AssignmentExpressionImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return ActionlangPackage.Literals.ASSIGNMENT_EXPRESSION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ValuedExpression getLhs() {
        return lhs;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetLhs(ValuedExpression newLhs,
            NotificationChain msgs) {
        ValuedExpression oldLhs = lhs;
        lhs = newLhs;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    ActionlangPackage.ASSIGNMENT_EXPRESSION__LHS, oldLhs,
                    newLhs);
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
    public void setLhs(ValuedExpression newLhs) {
        if (newLhs != lhs) {
            NotificationChain msgs = null;
            if (lhs != null)
                msgs = ((InternalEObject) lhs).eInverseRemove(this,
                        EOPPOSITE_FEATURE_BASE
                                - ActionlangPackage.ASSIGNMENT_EXPRESSION__LHS,
                        null, msgs);
            if (newLhs != null)
                msgs = ((InternalEObject) newLhs).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - ActionlangPackage.ASSIGNMENT_EXPRESSION__LHS,
                        null, msgs);
            msgs = basicSetLhs(newLhs, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ActionlangPackage.ASSIGNMENT_EXPRESSION__LHS, newLhs,
                    newLhs));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ValuedExpression getRhs() {
        return rhs;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetRhs(ValuedExpression newRhs,
            NotificationChain msgs) {
        ValuedExpression oldRhs = rhs;
        rhs = newRhs;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    ActionlangPackage.ASSIGNMENT_EXPRESSION__RHS, oldRhs,
                    newRhs);
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
    public void setRhs(ValuedExpression newRhs) {
        if (newRhs != rhs) {
            NotificationChain msgs = null;
            if (rhs != null)
                msgs = ((InternalEObject) rhs).eInverseRemove(this,
                        EOPPOSITE_FEATURE_BASE
                                - ActionlangPackage.ASSIGNMENT_EXPRESSION__RHS,
                        null, msgs);
            if (newRhs != null)
                msgs = ((InternalEObject) newRhs).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - ActionlangPackage.ASSIGNMENT_EXPRESSION__RHS,
                        null, msgs);
            msgs = basicSetRhs(newRhs, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ActionlangPackage.ASSIGNMENT_EXPRESSION__RHS, newRhs,
                    newRhs));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getReadVariables() {
        return getRhs().getReadVariables();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getMayReadVariables() {
        return getRhs().getMayReadVariables();
    }

    private DataDeclaration getLhsDataDeclaration() {
        assert (getLhs() instanceof DirectDataDeclarationReferenceExpression
                || getLhs() instanceof SubDataDeclarationReferenceExpression);

        DataDeclaration ret = null;

        if (getLhs() instanceof DirectDataDeclarationReferenceExpression) {
            DirectDataDeclarationReferenceExpression expr = (DirectDataDeclarationReferenceExpression) getLhs();

            ret = expr.getDataDeclaration();
        } else if (getLhs() instanceof SubDataDeclarationReferenceExpression) {
            SubDataDeclarationReferenceExpression expr = (SubDataDeclarationReferenceExpression) getLhs();

            ret = expr.getSubDataDeclarationRef().getForwardDataDeclaration();
        } else {
            assert (false);
        }

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getWriteVariables() {
        EList<DataDeclaration> ret = getRhs().getWriteVariables();

        if (!ret.contains(getLhsDataDeclaration())) {
            ret.add(getLhsDataDeclaration());
        }

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getMayWriteVariables() {
        EList<DataDeclaration> ret = getRhs().getMayWriteVariables();

        if (!ret.contains(getLhsDataDeclaration())) {
            ret.add(getLhsDataDeclaration());
        }

        return ret;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<Expression> getMayReadUninitializedVariables(
            EList<DataDeclaration> uninitialized) {
        EList<Expression> ret = getRhs()
                .getMayReadUninitializedVariables(uninitialized);

        if (uninitialized.contains(getLhsDataDeclaration())) {
            uninitialized.remove(getLhsDataDeclaration());
        }

        return ret;
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
        case ActionlangPackage.ASSIGNMENT_EXPRESSION__LHS:
            return basicSetLhs(null, msgs);
        case ActionlangPackage.ASSIGNMENT_EXPRESSION__RHS:
            return basicSetRhs(null, msgs);
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
        case ActionlangPackage.ASSIGNMENT_EXPRESSION__LHS:
            return getLhs();
        case ActionlangPackage.ASSIGNMENT_EXPRESSION__RHS:
            return getRhs();
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
        case ActionlangPackage.ASSIGNMENT_EXPRESSION__LHS:
            setLhs((ValuedExpression) newValue);
            return;
        case ActionlangPackage.ASSIGNMENT_EXPRESSION__RHS:
            setRhs((ValuedExpression) newValue);
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
        case ActionlangPackage.ASSIGNMENT_EXPRESSION__LHS:
            setLhs((ValuedExpression) null);
            return;
        case ActionlangPackage.ASSIGNMENT_EXPRESSION__RHS:
            setRhs((ValuedExpression) null);
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
        case ActionlangPackage.ASSIGNMENT_EXPRESSION__LHS:
            return lhs != null;
        case ActionlangPackage.ASSIGNMENT_EXPRESSION__RHS:
            return rhs != null;
        }
        return super.eIsSet(featureID);
    }

} //AssignmentExpressionImpl
