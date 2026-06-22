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
import bip2.ujf.verimag.bip.actionlang.IfThenElseExpression;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;

import bip2.ujf.verimag.bip.data.DataDeclaration;
import java.util.Collection;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.BasicEList;
import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.InternalEList;

import ujf.verimag.bip.metamodel.AnnotatedEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>If Then Else Expression</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.IfThenElseExpressionImpl#getCondition <em>Condition</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.IfThenElseExpressionImpl#getThen <em>Then</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.impl.IfThenElseExpressionImpl#getElse <em>Else</em>}</li>
 * </ul>
 *
 * @generated
 */
public class IfThenElseExpressionImpl extends AnnotatedEObjectImpl
        implements IfThenElseExpression {
    /**
     * The cached value of the '{@link #getCondition() <em>Condition</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getCondition()
     * @generated
     * @ordered
     */
    protected ValuedExpression condition;

    /**
     * The cached value of the '{@link #getThen() <em>Then</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getThen()
     * @generated
     * @ordered
     */
    protected EList<Expression> then;

    /**
     * The cached value of the '{@link #getElse() <em>Else</em>}' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getElse()
     * @generated
     * @ordered
     */
    protected EList<Expression> else_;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected IfThenElseExpressionImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return ActionlangPackage.Literals.IF_THEN_ELSE_EXPRESSION;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public ValuedExpression getCondition() {
        return condition;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetCondition(ValuedExpression newCondition,
            NotificationChain msgs) {
        ValuedExpression oldCondition = condition;
        condition = newCondition;
        if (eNotificationRequired()) {
            ENotificationImpl notification = new ENotificationImpl(this,
                    Notification.SET,
                    ActionlangPackage.IF_THEN_ELSE_EXPRESSION__CONDITION,
                    oldCondition, newCondition);
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
    public void setCondition(ValuedExpression newCondition) {
        if (newCondition != condition) {
            NotificationChain msgs = null;
            if (condition != null)
                msgs = ((InternalEObject) condition).eInverseRemove(this,
                        EOPPOSITE_FEATURE_BASE
                                - ActionlangPackage.IF_THEN_ELSE_EXPRESSION__CONDITION,
                        null, msgs);
            if (newCondition != null)
                msgs = ((InternalEObject) newCondition).eInverseAdd(this,
                        EOPPOSITE_FEATURE_BASE
                                - ActionlangPackage.IF_THEN_ELSE_EXPRESSION__CONDITION,
                        null, msgs);
            msgs = basicSetCondition(newCondition, msgs);
            if (msgs != null)
                msgs.dispatch();
        } else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET,
                    ActionlangPackage.IF_THEN_ELSE_EXPRESSION__CONDITION,
                    newCondition, newCondition));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<Expression> getThen() {
        if (then == null) {
            then = new EObjectContainmentEList<Expression>(Expression.class,
                    this, ActionlangPackage.IF_THEN_ELSE_EXPRESSION__THEN);
        }
        return then;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<Expression> getElse() {
        if (else_ == null) {
            else_ = new EObjectContainmentEList<Expression>(Expression.class,
                    this, ActionlangPackage.IF_THEN_ELSE_EXPRESSION__ELSE);
        }
        return else_;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getReadVariables() {
        // variables read in the then part
        EList<DataDeclaration> thenVars = new BasicEList<DataDeclaration>();

        for (Expression expr : getThen()) {
            EList<DataDeclaration> exprVars = expr.getReadVariables();

            // perform thenVars := thenVars union exprVars        
            exprVars.removeAll(thenVars);
            thenVars.addAll(exprVars);
        }

        // variables read in the else part
        EList<DataDeclaration> elseVars = new BasicEList<DataDeclaration>();

        for (Expression expr : getElse()) {
            EList<DataDeclaration> exprVars = expr.getReadVariables();

            // perform elseVars := elseVars union exprVars        
            exprVars.removeAll(elseVars);
            elseVars.addAll(exprVars);
        }

        // perform the intersection between thenVars and elseVars
        thenVars.retainAll(elseVars);

        return thenVars;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getMayReadVariables() {
        // variables read in the then part
        EList<DataDeclaration> thenVars = new BasicEList<DataDeclaration>();

        for (Expression expr : getThen()) {
            EList<DataDeclaration> exprVars = expr.getMayReadVariables();

            // perform thenVars := thenVars union exprVars        
            exprVars.removeAll(thenVars);
            thenVars.addAll(exprVars);
        }

        // variables read in the else part
        EList<DataDeclaration> elseVars = new BasicEList<DataDeclaration>();

        for (Expression expr : getElse()) {
            EList<DataDeclaration> exprVars = expr.getMayReadVariables();

            // perform elseVars := elseVars union exprVars        
            exprVars.removeAll(elseVars);
            elseVars.addAll(exprVars);
        }

        // perform the thenVars := thenVars union exprVars
        elseVars.removeAll(thenVars);
        thenVars.addAll(thenVars);

        return thenVars;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getWriteVariables() {
        // variables read in the then part
        EList<DataDeclaration> thenVars = new BasicEList<DataDeclaration>();

        for (Expression expr : getThen()) {
            EList<DataDeclaration> exprVars = expr.getWriteVariables();

            // perform thenVars := thenVars union exprVars        
            exprVars.removeAll(thenVars);
            thenVars.addAll(exprVars);
        }

        // variables read in the else part
        EList<DataDeclaration> elseVars = new BasicEList<DataDeclaration>();

        for (Expression expr : getElse()) {
            EList<DataDeclaration> exprVars = expr.getWriteVariables();

            // perform elseVars := elseVars union exprVars        
            exprVars.removeAll(elseVars);
            elseVars.addAll(exprVars);
        }

        // perform the intersection between thenVars and elseVars
        thenVars.retainAll(elseVars);

        return thenVars;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @Override
     * @generated NOT
     */
    public EList<DataDeclaration> getMayWriteVariables() {
        // variables read in the then part
        EList<DataDeclaration> thenVars = new BasicEList<DataDeclaration>();

        for (Expression expr : getThen()) {
            EList<DataDeclaration> exprVars = expr.getMayWriteVariables();

            // perform thenVars := thenVars union exprVars        
            exprVars.removeAll(thenVars);
            thenVars.addAll(exprVars);
        }

        // variables read in the else part
        EList<DataDeclaration> elseVars = new BasicEList<DataDeclaration>();

        for (Expression expr : getElse()) {
            EList<DataDeclaration> exprVars = expr.getMayWriteVariables();

            // perform elseVars := elseVars union exprVars        
            exprVars.removeAll(elseVars);
            elseVars.addAll(exprVars);
        }

        // perform the thenVars := thenVars union exprVars
        elseVars.removeAll(thenVars);
        thenVars.addAll(thenVars);

        return thenVars;
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

        // variables initialized by the then part
        EList<DataDeclaration> thenUninit = new BasicEList<DataDeclaration>(
                uninitialized);

        for (Expression expr : getThen()) {
            EList<Expression> exprUninit = expr
                    .getMayReadUninitializedVariables(thenUninit);

            ret.addAll(exprUninit);
        }

        // variables initialized by the else part
        EList<DataDeclaration> elseUninit = new BasicEList<DataDeclaration>(
                uninitialized);

        for (Expression expr : getElse()) {
            EList<Expression> exprUninit = expr
                    .getMayReadUninitializedVariables(elseUninit);

            ret.addAll(exprUninit);
        }

        // thenUninit := thenUninit union elseUninit
        thenUninit.removeAll(elseUninit);
        thenUninit.addAll(elseUninit);

        // update uninitialized variables
        uninitialized.retainAll(thenUninit);

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
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__CONDITION:
            return basicSetCondition(null, msgs);
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__THEN:
            return ((InternalEList<?>) getThen()).basicRemove(otherEnd, msgs);
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__ELSE:
            return ((InternalEList<?>) getElse()).basicRemove(otherEnd, msgs);
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
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__CONDITION:
            return getCondition();
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__THEN:
            return getThen();
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__ELSE:
            return getElse();
        }
        return super.eGet(featureID, resolve, coreType);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @SuppressWarnings("unchecked")
    @Override
    public void eSet(int featureID, Object newValue) {
        switch (featureID) {
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__CONDITION:
            setCondition((ValuedExpression) newValue);
            return;
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__THEN:
            getThen().clear();
            getThen().addAll((Collection<? extends Expression>) newValue);
            return;
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__ELSE:
            getElse().clear();
            getElse().addAll((Collection<? extends Expression>) newValue);
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
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__CONDITION:
            setCondition((ValuedExpression) null);
            return;
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__THEN:
            getThen().clear();
            return;
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__ELSE:
            getElse().clear();
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
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__CONDITION:
            return condition != null;
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__THEN:
            return then != null && !then.isEmpty();
        case ActionlangPackage.IF_THEN_ELSE_EXPRESSION__ELSE:
            return else_ != null && !else_.isEmpty();
        }
        return super.eIsSet(featureID);
    }

} //IfThenElseExpressionImpl
