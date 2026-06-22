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

package ujf.verimag.bip.parser.error;

import org.antlr.runtime.EarlyExitException;
import org.antlr.runtime.FailedPredicateException;
import org.antlr.runtime.MismatchedNotSetException;
import org.antlr.runtime.MismatchedRangeException;
import org.antlr.runtime.MismatchedSetException;
import org.antlr.runtime.MismatchedTokenException;
import org.antlr.runtime.MismatchedTreeNodeException;
import org.antlr.runtime.MissingTokenException;
import org.antlr.runtime.NoViableAltException;
import org.antlr.runtime.RecognitionException;
import org.antlr.runtime.UnwantedTokenException;

import ujf.verimag.bip.error.GenericError;
import ujf.verimag.bip.error.message.ErrorCodeEnum;
import ujf.verimag.bip.error.message.ErrorSeverity;

/**
 * Wrapper class for error class raised by the antlr lexer/parser/walker. Only
 * antlr problems must be wrapped by this class.
 */
public class ParserOrLexerError extends GenericError {

    // /**
    // * This enum type lists all types of errors possibly raised by antlr
    // * during the parsing (lexer+parser+walker).
    // * It includes errors built in antlr (first group, with parsing aspect)
    // and
    // * custom errors created for our specific compiler (second group, only
    // used
    // * in the walker when creating model objects).
    // */
    // public enum ParserLexerWalkerErrors {
    // Recognition,
    // MismatchedToken,
    // MismatchedTreeNode,
    // NoViableAlt,
    // EarlyExit,
    // FailedPredicate,
    // MismatchedRange,
    // MismatchedSet,
    // MismatchedNotSet,
    // MissingToken,
    // UnwantedToken,
    //
    // // following errors are used in the walker when
    // // creating model objects.
    // IncorrectParameters,
    // LoadPackage,
    // OperationInvalidOrNotSupported,
    // RedefinedType,
    // RedefinedVariable,
    // UndefinedType,
    // UndefinedVariable,
    // UndefinedState,
    // GenericWalkerError,
    // }

    /**
     * When the error relates to an antlr recognition exception, the exception
     * is stored here.
     */
    private RecognitionException antlrRecogException;

    /**
     * When possible, the faulty token is stored here.
     */
    private String errorToken;

    /**
     * Get the faulty token
     * 
     * @return the faulty token.
     */
    public String getErrorToken() {
        return errorToken;
    }

    /**
     * When applicable, get the underlying antlr exception that triggered this
     * error
     * 
     * @return the antlr exception that caused the error.
     */
    public RecognitionException getAntlrException() {
        return antlrRecogException;
    }

//    private void handle(Bip2WalkerException re) {
//        if (re instanceof LoadPackageException) {
//            this.errorcode = ErrorCodeEnum.LoadPackage;
//        } else if (re instanceof OperationInvalidOrNotSupportedException) {
//            this.errorcode = ErrorCodeEnum.OperationInvalidOrNotSupported;
//        } else if (re instanceof RedefinedTypeException) {
//            this.errorcode = ErrorCodeEnum.RedefinedType;
//        } else if (re instanceof RedefinedVariableException) {
//            this.errorcode = ErrorCodeEnum.RedefinedVariable;
//        } else if (re instanceof UndefinedTypeException) {
//            this.errorcode = ErrorCodeEnum.UndefinedType;
//        } else if (re instanceof UndefinedVariableException) {
//            this.errorcode = ErrorCodeEnum.UndefinedVariable;
//        } else if (re instanceof UndefinedStateException) {
//            this.errorcode = ErrorCodeEnum.UndefinedState;
//        } else if (re instanceof GenericWalkerErrorException) {
//            this.errorcode = ErrorCodeEnum.GenericWalkerError;
//        } else if (re instanceof IncorrectParametersException) {
//            this.errorcode = ErrorCodeEnum.IncorrectParameters;
//        }
//    }

    public ParserOrLexerError(Bip2WalkerException re) {
        super(re.start.getLine(), re.start.getCharPositionInLine(), 
                re.start.getToken() != null ? re.start.getCharPositionInLine() + re.start.getToken().getText().length() : -1,
                re.errorcode, ErrorSeverity.FATAL);
        this.antlrRecogException = re;

        /*
         * Yes, this is not uber nice, but that's the easiest way to do that.
         * You may have to add other cases if you need to nest errors.
         */
        if (re instanceof LoadPackageException){
            this.nested = true;
            this.nestedErrors = ((LoadPackageException) re).getLoaderException().getErrors();
        }
    }

    private void handle(RecognitionException re) {
        if (re instanceof MissingTokenException) {
            this.errorcode = ErrorCodeEnum.MissingToken;
        } else if (re instanceof UnwantedTokenException) {
            this.errorcode = ErrorCodeEnum.UnwantedToken;
        } else if (re instanceof MismatchedTokenException) {
            this.errorcode = ErrorCodeEnum.MismatchedToken;
        } else if (re instanceof MismatchedTreeNodeException) {
            this.errorcode = ErrorCodeEnum.MismatchedTreeNode;
        } else if (re instanceof NoViableAltException) {
            this.errorcode = ErrorCodeEnum.NoViableAlt;
        } else if (re instanceof EarlyExitException) {
            this.errorcode = ErrorCodeEnum.EarlyExit;
        } else if (re instanceof FailedPredicateException) {
            this.errorcode = ErrorCodeEnum.FailedPredicate;
        } else if (re instanceof MismatchedRangeException) {
            this.errorcode = ErrorCodeEnum.MismatchedRange;
        } else if (re instanceof MismatchedSetException) {
            this.errorcode = ErrorCodeEnum.MismatchedSet;
        } else if (re instanceof MismatchedNotSetException) {
            this.errorcode = ErrorCodeEnum.MismatchedNotSet;
        }
    }

    public ParserOrLexerError(RecognitionException re) {
        super(re.line, re.charPositionInLine, re.token != null ? (re.token.getType() != org.antlr.runtime.Token.EOF ? re.charPositionInLine + re.token.getText().length() : re.charPositionInLine + 1) : -1,
                ErrorCodeEnum.GenericDefault, ErrorSeverity.FATAL);
        if (re.token != null)
            this.errorToken = re.token.getText();
        this.antlrRecogException = re;
        handle(re);
    }
}
