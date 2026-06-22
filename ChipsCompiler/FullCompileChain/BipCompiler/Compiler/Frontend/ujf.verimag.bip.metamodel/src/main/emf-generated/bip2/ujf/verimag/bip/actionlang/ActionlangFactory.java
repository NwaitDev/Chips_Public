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

package bip2.ujf.verimag.bip.actionlang;

import org.eclipse.emf.ecore.EFactory;

/**
 * <!-- begin-user-doc -->
 * The <b>Factory</b> for the model.
 * It provides a create method for each non-abstract class of the model.
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.actionlang.ActionlangPackage
 * @generated
 */
public interface ActionlangFactory extends EFactory {
    /**
     * The singleton instance of the factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    ActionlangFactory eINSTANCE = bip2.ujf.verimag.bip.actionlang.impl.ActionlangFactoryImpl
            .init();

    /**
     * Returns a new object of class '<em>Binary Op Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Binary Op Expression</em>'.
     * @generated
     */
    BinaryOpExpression createBinaryOpExpression();

    /**
     * Returns a new object of class '<em>Unary Op Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Unary Op Expression</em>'.
     * @generated
     */
    UnaryOpExpression createUnaryOpExpression();

    /**
     * Returns a new object of class '<em>Sub Data Declaration Reference Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Sub Data Declaration Reference Expression</em>'.
     * @generated
     */
    SubDataDeclarationReferenceExpression createSubDataDeclarationReferenceExpression();

    /**
     * Returns a new object of class '<em>Direct Data Declaration Reference Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Direct Data Declaration Reference Expression</em>'.
     * @generated
     */
    DirectDataDeclarationReferenceExpression createDirectDataDeclarationReferenceExpression();

    /**
     * Returns a new object of class '<em>Assignment Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Assignment Expression</em>'.
     * @generated
     */
    AssignmentExpression createAssignmentExpression();

    /**
     * Returns a new object of class '<em>Function Call Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Function Call Expression</em>'.
     * @generated
     */
    FunctionCallExpression createFunctionCallExpression();

    /**
     * Returns a new object of class '<em>Valued Reference Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Valued Reference Expression</em>'.
     * @generated
     */
    ValuedReferenceExpression createValuedReferenceExpression();

    /**
     * Returns a new object of class '<em>Direct Boolean Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Direct Boolean Expression</em>'.
     * @generated
     */
    DirectBooleanExpression createDirectBooleanExpression();

    /**
     * Returns a new object of class '<em>If Then Else Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>If Then Else Expression</em>'.
     * @generated
     */
    IfThenElseExpression createIfThenElseExpression();

    /**
     * Returns a new object of class '<em>Direct Integer Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Direct Integer Expression</em>'.
     * @generated
     */
    DirectIntegerExpression createDirectIntegerExpression();

    /**
     * Returns a new object of class '<em>Direct Float Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Direct Float Expression</em>'.
     * @generated
     */
    DirectFloatExpression createDirectFloatExpression();

    /**
     * Returns a new object of class '<em>Direct String Expression</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Direct String Expression</em>'.
     * @generated
     */
    DirectStringExpression createDirectStringExpression();

    /**
     * Returns the package supported by this factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the package supported by this factory.
     * @generated
     */
    ActionlangPackage getActionlangPackage();

} //ActionlangFactory
