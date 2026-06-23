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

package bip2.ujf.verimag.bip.actionlang;

import bip2.ujf.verimag.bip.packaging.BinaryOpPrototype;
import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Binary Op Expression</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.BinaryOpExpression#getOperator <em>Operator</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.BinaryOpExpression#getLeft <em>Left</em>}</li>
 *   <li>{@link bip2.ujf.verimag.bip.actionlang.BinaryOpExpression#getRight <em>Right</em>}</li>
 * </ul>
 *
 * @see bip2.ujf.verimag.bip.actionlang.ActionlangPackage#getBinaryOpExpression()
 * @model annotation="http://www.eclipse.org/emf/2002/Ecore constraints='hasOneMatchingPrototype'"
 * @generated
 */
public interface BinaryOpExpression extends ValuedExpression {
    /**
     * Returns the value of the '<em><b>Operator</b></em>' attribute.
     * The literals are from the enumeration {@link bip2.ujf.verimag.bip.actionlang.BinaryOperators}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Operator</em>' attribute isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Operator</em>' attribute.
     * @see bip2.ujf.verimag.bip.actionlang.BinaryOperators
     * @see #setOperator(BinaryOperators)
     * @see bip2.ujf.verimag.bip.actionlang.ActionlangPackage#getBinaryOpExpression_Operator()
     * @model required="true"
     * @generated
     */
    BinaryOperators getOperator();

    /**
     * Sets the value of the '{@link bip2.ujf.verimag.bip.actionlang.BinaryOpExpression#getOperator <em>Operator</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Operator</em>' attribute.
     * @see bip2.ujf.verimag.bip.actionlang.BinaryOperators
     * @see #getOperator()
     * @generated
     */
    void setOperator(BinaryOperators value);

    /**
     * Returns the value of the '<em><b>Left</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Left</em>' containment reference isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Left</em>' containment reference.
     * @see #setLeft(ValuedExpression)
     * @see bip2.ujf.verimag.bip.actionlang.ActionlangPackage#getBinaryOpExpression_Left()
     * @model containment="true" required="true"
     * @generated
     */
    ValuedExpression getLeft();

    /**
     * Sets the value of the '{@link bip2.ujf.verimag.bip.actionlang.BinaryOpExpression#getLeft <em>Left</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Left</em>' containment reference.
     * @see #getLeft()
     * @generated
     */
    void setLeft(ValuedExpression value);

    /**
     * Returns the value of the '<em><b>Right</b></em>' containment reference.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Right</em>' containment reference isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Right</em>' containment reference.
     * @see #setRight(ValuedExpression)
     * @see bip2.ujf.verimag.bip.actionlang.ActionlangPackage#getBinaryOpExpression_Right()
     * @model containment="true" required="true"
     * @generated
     */
    ValuedExpression getRight();

    /**
     * Sets the value of the '{@link bip2.ujf.verimag.bip.actionlang.BinaryOpExpression#getRight <em>Right</em>}' containment reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Right</em>' containment reference.
     * @see #getRight()
     * @generated
     */
    void setRight(ValuedExpression value);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model kind="operation"
     * @generated
     */
    EList<BinaryOpPrototype> getPrototypes();

} // BinaryOpExpression
