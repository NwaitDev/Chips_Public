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

package ujf.verimag.bip.error;

import java.net.URL;

import ujf.verimag.bip.error.message.ErrorCodeEnum;
import ujf.verimag.bip.error.message.ErrorSeverity;

/**
 * Describes an error in the source code of BIP packages/systems.
 * It is abstract and should be extending by concrete error.
 */
public abstract class GenericError {

    /**
     * The error code
     */
    public ErrorCodeEnum errorcode;

    /**
     * The severity of the error
     */
    public ErrorSeverity severity;

    /**
     * True when the error is silenced. Usually, only
     * applies to warnings.
     */
    public final boolean isSilenced;

    /**
     * The source of the error. It can be regular file, a file within a local
     * jar, a file within a remote jar, ...
     */
    protected URL sourceFile;

    /**
     * The source of the error as a StringBuffer. When there is no file tied
     * to the error, the source is searched in this buffer (if set).
     */
    protected StringBuffer sourceStringBuffer; 

    /**
     * The line number in which the error was found.
     */
    protected int line;
    /**
     * The column number in which the error was found (start).
     */
    protected int columnStart;

    /**
     * If true, then the real error is nested.
     * UI error display should go deeper to build
     * the message
     */
    protected boolean nested = false;
    protected GenericError[] nestedErrors;
    
    public GenericError[] getNestedErrors() {
        return nestedErrors;
    }

    public void setNestedErrors(GenericError[] nestedErrors) {
        this.nestedErrors = nestedErrors;
    }

    public boolean isNested() {
        return nested;
    }

    public void setNested(boolean nested) {
        this.nested = nested;
    }

    /**
     * The column number in which the error was found (end).
     */
    protected int columnEnd;

    protected GenericError(){
        isSilenced = false;
    }
//    
//    /**
//     * Builds an error from a faulty AnnotatedEObject
//     * @param object the faulty object
//     */
//    public GenericError(AnnotatedEObject object){
//        this(object.getLineStart(), object.getColStart(), ErrorCodeEnum.GenericDefault, ErrorSeverity.FATAL);
//        this.setSourceFile(object.getSourceURL());
//        this.setSourceStringBuffer(object.getSourceStringBuffer());
//    }
//    
//    /**
//     * Builds an error from a faulty AnnotatedEObject
//     * @param object the faulty object
//     * @param code the error code corresponding to the error
//     */
//    public GenericError(AnnotatedEObject object, ErrorCodeEnum code){
//        this(object.getLineStart(), object.getColStart(), code, ErrorSeverity.FATAL);
//        this.setSourceFile(object.getSourceURL());
//        this.setSourceStringBuffer(object.getSourceStringBuffer());
//    }
//    
//    /**
//     * Builds an error from a faulty AnnotatedEObject
//     * @param object the faulty object
//     * @param code the error code corresponding to the error
//     * @param severity the error severity
//     */
//    public GenericError(AnnotatedEObject object, ErrorCodeEnum code, ErrorSeverity severity){
//        this(object.getLineStart(), object.getColStart(), code, severity);
//        this.setSourceFile(object.getSourceURL());
//        this.setSourceStringBuffer(object.getSourceStringBuffer());
//    }
    
    /**
     * Builds a new error located at a given file location
     * @param line the line number
     * @param column the column number
     * @param code the error code corresponding to the error
     * @param severity the error severity
     */
    protected GenericError(int line, int column, ErrorCodeEnum code, ErrorSeverity severity){
        this.isSilenced = false;
        this.line = line;
        this.columnStart = column;
        this.columnEnd = -1;
        this.errorcode = code;
        this.severity = severity;
    }

    /**
     * Builds a new error located at a given file location
     * @param line the line number
     * @param columnStart the column number (start)
     * @param columnEnd the column number (end)
     * @param code the error code corresponding to the error
     * @param severity the error severity
     */
    protected GenericError(int line, int columnStart, int columnEnd, ErrorCodeEnum code, ErrorSeverity severity){
        this.isSilenced = false;
        this.line = line;
        this.columnStart = columnStart;
        this.columnEnd = columnEnd;
        this.errorcode = code;
        this.severity = severity;
    }

    /**
     * Builds a new error located at a given file location
     * @param line the line number
     * @param columnStart the column number (start)
     * @param columnEnd the column number (end)
     * @param code the error code corresponding to the error
     * @param severity the error severity
     * @param isSilenced true if error should be silenced
     */
    protected GenericError(int line, int columnStart, int columnEnd, ErrorCodeEnum code, ErrorSeverity severity, boolean isSilenced){
        this.isSilenced = isSilenced;
        this.line = line;
        this.columnStart = columnStart;
        this.columnEnd = columnEnd;
        this.errorcode = code;
        this.severity = severity;
    }

    /**
     * Sets the source file in which the error is located
     * @param sourceFile the source file
     */
    public void setSourceFile(URL sourceFile) {
        this.sourceFile = sourceFile;
    }
    
    /**
     * Returns the file in which this error is bound
     * @return the file
     */
    public URL getSourceFile() {
        return sourceFile;
    }
    
    /**
     * Sets the source buffer in which the error is located.
     * This is a fallback in case there is no source file set.
     * @param sourceStringBuffer the string buffer
     */
    public void setSourceStringBuffer(StringBuffer sourceStringBuffer) {
        this.sourceStringBuffer = sourceStringBuffer;
    }
    
    /**
     * Returns the string buffer in which this error is bound
     * @return the string buffer
     */
    public StringBuffer getSourceStringBuffer() {
        return this.sourceStringBuffer;
    }
    
    /**
     * Get the line number at which the error has been found
     * @return the line number
     */
    public int getLine() {
        return line;
    }
    
    /**
     * Get the column number at which the error has been found (start)
     * @return the column number
     */
    public int getColumnStart() {
        return columnStart;
    }

    /**
     * Get the column number at which the error has been found (end)
     * @return the column number
     */
    public int getColumnStop() {
        return columnEnd;
    }
}
