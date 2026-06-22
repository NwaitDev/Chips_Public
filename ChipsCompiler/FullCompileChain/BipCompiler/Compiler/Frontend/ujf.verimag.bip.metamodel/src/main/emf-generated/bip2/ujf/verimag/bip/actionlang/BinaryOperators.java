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

package bip2.ujf.verimag.bip.actionlang;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import org.eclipse.emf.common.util.Enumerator;

/**
 * <!-- begin-user-doc -->
 * A representation of the literals of the enumeration '<em><b>Binary Operators</b></em>',
 * and utility methods for working with them.
 * <!-- end-user-doc -->
 * @see bip2.ujf.verimag.bip.actionlang.ActionlangPackage#getBinaryOperators()
 * @model
 * @generated
 */
public enum BinaryOperators implements Enumerator {
    /**
     * The '<em><b>Addition</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #ADDITION_VALUE
     * @generated
     * @ordered
     */
    ADDITION(0, "addition", "+"),

    /**
     * The '<em><b>Subtraction</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #SUBTRACTION_VALUE
     * @generated
     * @ordered
     */
    SUBTRACTION(1, "subtraction", "-"),
    /**
    * The '<em><b>Multiplication</b></em>' literal object.
    * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
    * @see #MULTIPLICATION_VALUE
    * @generated
    * @ordered
    */
    MULTIPLICATION(2, "multiplication", "*"),

    /**
     * The '<em><b>Bwise and</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #BWISE_AND_VALUE
     * @generated
     * @ordered
     */
    BWISE_AND(3, "bwise_and", "&"),

    /**
     * The '<em><b>Bwise xor</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #BWISE_XOR_VALUE
     * @generated
     * @ordered
     */
    BWISE_XOR(4, "bwise_xor", "^"),

    /**
     * The '<em><b>Bwise or</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #BWISE_OR_VALUE
     * @generated
     * @ordered
     */
    BWISE_OR(5, "bwise_or", "|"),

    /**
     * The '<em><b>Logical and</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #LOGICAL_AND_VALUE
     * @generated
     * @ordered
     */
    LOGICAL_AND(6, "logical_and", "&&"),

    /**
     * The '<em><b>Logical or</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #LOGICAL_OR_VALUE
     * @generated
     * @ordered
     */
    LOGICAL_OR(7, "logical_or", "||"),

    /**
     * The '<em><b>Equal</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #EQUAL_VALUE
     * @generated
     * @ordered
     */
    EQUAL(8, "equal", "=="),

    /**
     * The '<em><b>Not equal</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #NOT_EQUAL_VALUE
     * @generated
     * @ordered
     */
    NOT_EQUAL(9, "not_equal", "!="),

    /**
     * The '<em><b>Less than</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #LESS_THAN_VALUE
     * @generated
     * @ordered
     */
    LESS_THAN(10, "less_than", "<"),

    /**
     * The '<em><b>Greater than</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #GREATER_THAN_VALUE
     * @generated
     * @ordered
     */
    GREATER_THAN(11, "greater_than", ">"),

    /**
     * The '<em><b>Less than or equal</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #LESS_THAN_OR_EQUAL_VALUE
     * @generated
     * @ordered
     */
    LESS_THAN_OR_EQUAL(12, "less_than_or_equal", "<="),

    /**
     * The '<em><b>Greater than or equal</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #GREATER_THAN_OR_EQUAL_VALUE
     * @generated
     * @ordered
     */
    GREATER_THAN_OR_EQUAL(13, "greater_than_or_equal", ">="),

    /**
     * The '<em><b>Division</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #DIVISION_VALUE
     * @generated
     * @ordered
     */
    DIVISION(14, "division", "/"),

    /**
     * The '<em><b>Modulo</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #MODULO_VALUE
     * @generated
     * @ordered
     */
    MODULO(15, "modulo", "%");

    /**
     * The '<em><b>Addition</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Addition</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #ADDITION
     * @model name="addition" literal="+"
     * @generated
     * @ordered
     */
    public static final int ADDITION_VALUE = 0;

    /**
     * The '<em><b>Subtraction</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Subtraction</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #SUBTRACTION
     * @model name="subtraction" literal="-"
     * @generated
     * @ordered
     */
    public static final int SUBTRACTION_VALUE = 1;

    /**
     * The '<em><b>Multiplication</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Multiplication</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #MULTIPLICATION
     * @model name="multiplication" literal="*"
     * @generated
     * @ordered
     */
    public static final int MULTIPLICATION_VALUE = 2;

    /**
     * The '<em><b>Bwise and</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Bwise and</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #BWISE_AND
     * @model name="bwise_and" literal="&amp;"
     * @generated
     * @ordered
     */
    public static final int BWISE_AND_VALUE = 3;

    /**
     * The '<em><b>Bwise xor</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Bwise xor</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #BWISE_XOR
     * @model name="bwise_xor" literal="^"
     * @generated
     * @ordered
     */
    public static final int BWISE_XOR_VALUE = 4;

    /**
     * The '<em><b>Bwise or</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Bwise or</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #BWISE_OR
     * @model name="bwise_or" literal="|"
     * @generated
     * @ordered
     */
    public static final int BWISE_OR_VALUE = 5;

    /**
     * The '<em><b>Logical and</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Logical and</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #LOGICAL_AND
     * @model name="logical_and" literal="&amp;&amp;"
     * @generated
     * @ordered
     */
    public static final int LOGICAL_AND_VALUE = 6;

    /**
     * The '<em><b>Logical or</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Logical or</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #LOGICAL_OR
     * @model name="logical_or" literal="||"
     * @generated
     * @ordered
     */
    public static final int LOGICAL_OR_VALUE = 7;

    /**
     * The '<em><b>Equal</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Equal</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #EQUAL
     * @model name="equal" literal="=="
     * @generated
     * @ordered
     */
    public static final int EQUAL_VALUE = 8;

    /**
     * The '<em><b>Not equal</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Not equal</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #NOT_EQUAL
     * @model name="not_equal" literal="!="
     * @generated
     * @ordered
     */
    public static final int NOT_EQUAL_VALUE = 9;

    /**
     * The '<em><b>Less than</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Less than</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #LESS_THAN
     * @model name="less_than" literal="&lt;"
     * @generated
     * @ordered
     */
    public static final int LESS_THAN_VALUE = 10;

    /**
     * The '<em><b>Greater than</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Greater than</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #GREATER_THAN
     * @model name="greater_than" literal="&gt;"
     * @generated
     * @ordered
     */
    public static final int GREATER_THAN_VALUE = 11;

    /**
     * The '<em><b>Less than or equal</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Less than or equal</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #LESS_THAN_OR_EQUAL
     * @model name="less_than_or_equal" literal="&lt;="
     * @generated
     * @ordered
     */
    public static final int LESS_THAN_OR_EQUAL_VALUE = 12;

    /**
     * The '<em><b>Greater than or equal</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Greater than or equal</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #GREATER_THAN_OR_EQUAL
     * @model name="greater_than_or_equal" literal="&gt;="
     * @generated
     * @ordered
     */
    public static final int GREATER_THAN_OR_EQUAL_VALUE = 13;

    /**
     * The '<em><b>Division</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Division</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #DIVISION
     * @model name="division" literal="/"
     * @generated
     * @ordered
     */
    public static final int DIVISION_VALUE = 14;

    /**
     * The '<em><b>Modulo</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Modulo</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #MODULO
     * @model name="modulo" literal="%"
     * @generated
     * @ordered
     */
    public static final int MODULO_VALUE = 15;

    /**
     * An array of all the '<em><b>Binary Operators</b></em>' enumerators.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private static final BinaryOperators[] VALUES_ARRAY = new BinaryOperators[] {
            ADDITION, SUBTRACTION, MULTIPLICATION, BWISE_AND, BWISE_XOR,
            BWISE_OR, LOGICAL_AND, LOGICAL_OR, EQUAL, NOT_EQUAL, LESS_THAN,
            GREATER_THAN, LESS_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL, DIVISION,
            MODULO, };

    /**
     * A public read-only list of all the '<em><b>Binary Operators</b></em>' enumerators.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final List<BinaryOperators> VALUES = Collections
            .unmodifiableList(Arrays.asList(VALUES_ARRAY));

    /**
     * Returns the '<em><b>Binary Operators</b></em>' literal with the specified literal value.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param literal the literal.
     * @return the matching enumerator or <code>null</code>.
     * @generated
     */
    public static BinaryOperators get(String literal) {
        for (int i = 0; i < VALUES_ARRAY.length; ++i) {
            BinaryOperators result = VALUES_ARRAY[i];
            if (result.toString().equals(literal)) {
                return result;
            }
        }
        return null;
    }

    /**
     * Returns the '<em><b>Binary Operators</b></em>' literal with the specified name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param name the name.
     * @return the matching enumerator or <code>null</code>.
     * @generated
     */
    public static BinaryOperators getByName(String name) {
        for (int i = 0; i < VALUES_ARRAY.length; ++i) {
            BinaryOperators result = VALUES_ARRAY[i];
            if (result.getName().equals(name)) {
                return result;
            }
        }
        return null;
    }

    /**
     * Returns the '<em><b>Binary Operators</b></em>' literal with the specified integer value.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the integer value.
     * @return the matching enumerator or <code>null</code>.
     * @generated
     */
    public static BinaryOperators get(int value) {
        switch (value) {
        case ADDITION_VALUE:
            return ADDITION;
        case SUBTRACTION_VALUE:
            return SUBTRACTION;
        case MULTIPLICATION_VALUE:
            return MULTIPLICATION;
        case BWISE_AND_VALUE:
            return BWISE_AND;
        case BWISE_XOR_VALUE:
            return BWISE_XOR;
        case BWISE_OR_VALUE:
            return BWISE_OR;
        case LOGICAL_AND_VALUE:
            return LOGICAL_AND;
        case LOGICAL_OR_VALUE:
            return LOGICAL_OR;
        case EQUAL_VALUE:
            return EQUAL;
        case NOT_EQUAL_VALUE:
            return NOT_EQUAL;
        case LESS_THAN_VALUE:
            return LESS_THAN;
        case GREATER_THAN_VALUE:
            return GREATER_THAN;
        case LESS_THAN_OR_EQUAL_VALUE:
            return LESS_THAN_OR_EQUAL;
        case GREATER_THAN_OR_EQUAL_VALUE:
            return GREATER_THAN_OR_EQUAL;
        case DIVISION_VALUE:
            return DIVISION;
        case MODULO_VALUE:
            return MODULO;
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private final int value;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private final String name;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private final String literal;

    /**
     * Only this class can construct instances.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private BinaryOperators(int value, String name, String literal) {
        this.value = value;
        this.name = name;
        this.literal = literal;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public int getValue() {
        return value;
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
    public String getLiteral() {
        return literal;
    }

    /**
     * Returns the literal value of the enumerator, which is its string representation.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public String toString() {
        return literal;
    }

} //BinaryOperators
