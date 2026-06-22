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

import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Set;
import java.util.Comparator;

import org.antlr.runtime.MismatchedTokenException;
import org.eclipse.emf.common.util.Diagnostic;
import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.ecore.EObject;

import bip2.ujf.verimag.bip.actionlang.AssignmentExpression;
import bip2.ujf.verimag.bip.actionlang.BinaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.UnaryOpExpression;
import bip2.ujf.verimag.bip.actionlang.FunctionCallExpression;
import bip2.ujf.verimag.bip.actionlang.ValuedExpression;
import bip2.ujf.verimag.bip.behavior.State;
import bip2.ujf.verimag.bip.behavior.Transition;
import bip2.ujf.verimag.bip.data.DataDeclaration;
import bip2.ujf.verimag.bip.data.DataType;
import bip2.ujf.verimag.bip.packaging.BinaryOpPrototype;
import bip2.ujf.verimag.bip.packaging.FunctionCallPrototype;
import bip2.ujf.verimag.bip.packaging.Prototype;
import bip2.ujf.verimag.bip.packaging.PrototypeParameterDeclaration;
import bip2.ujf.verimag.bip.packaging.UnaryOpPrototype;
import bip2.ujf.verimag.bip.port.PortDeclaration;
import bip2.ujf.verimag.bip.priority.AtomPriorityDeclaration;
import bip2.ujf.verimag.bip.priority.CompoundPriorityDeclaration;
import bip2.ujf.verimag.bip.types.Type;

import ujf.verimag.bip.error.AbstractErrorStringifier;
import ujf.verimag.bip.error.GenericError;
import ujf.verimag.bip.metamodel.AnnotatedEObject;
import ujf.verimag.bip.parser.Bip2Parser;
import ujf.verimag.bip.parser.loader.error.LoaderError;
import ujf.verimag.bip.parser.loader.error.PackageNameDoesNotMatchFileName;

/**
 * The error stringifier is used to create a textual representation of error
 * encountered in the frontend. It is mainly used for the command line
 * interface and is currently only speaking english.
 * If the compiler was to be localized, then this is the starting point for
 * such work.
 */
public class LoaderErrorStringifier extends AbstractErrorStringifier {

    public LoaderErrorStringifier(File file) throws IOException {
        super(file);
    }


    public LoaderErrorStringifier(String string) throws IOException {
        super(string);
    }

    public LoaderErrorStringifier() {
    }


    class SourceOrderComparator implements Comparator<AnnotatedEObject> {
        @Override
        public int compare(AnnotatedEObject o1, AnnotatedEObject o2) {
            int ret = 0;
            
            if (o1.getLineStart() < o2.getLineStart()) {
                ret = -1;
            }
            else if (o1.getLineStart() == o2.getLineStart()) {
                if (o1.getColStart() < o2.getColStart()) {
                    ret = -1;
                }
                else if (o1.getColStart() == o2.getColStart()) {
                   ret = 0;
                }
                else {
                    ret = 1;
                }
            }
            else {
                ret = 1;
            }
            
            return ret;
        }
    }

    /**
     * Creates a string representation for a generic object
     * @param error the generic object
     * @return the string representing the error
     */
    public String stringify(GenericError error) {
        
        if (error instanceof ParserOrLexerError){
            return this.stringify((ParserOrLexerError) error);
        } else if (error instanceof DiagnosticError){
            return this.stringify((DiagnosticError) error);
        } else if (error instanceof LoaderError){
            return this.stringify((LoaderError)error);
        }
        
        assert(false); // this should never happen.
        return null;
    }
    
    
    /**
     * Based on the error type, builds a human readable error message with
     * context from this loader error
     * 
     * @param error
     *            the loader error
     * @return the error message
     */
    public String stringify(LoaderError error){
        
        String message = getSpecificErrorMessage(error.errorcode);
        StringBuffer sb = new StringBuffer();

        switch(error.errorcode){
        case CycleFoundInPackageDep:
        case PackageNotFound:
        case PackageNotLoaded:
            message = String.format(message, error.packageName);
            break;
        case PackageNameDoesNotMatchFileName:
            message = String.format(message, error.packageName, ((PackageNameDoesNotMatchFileName)error).fileName);
            break;
        }
        
        sb.append(message + "\n");
        
        return sb.toString();
    }
    
    private String getDisplayName(Type type) {
        String ret = "???";
        
        if (type != null) {
            ret = type.getName();
        }
        
        return ret;
    }
    
    private String getDisplayNames(List<Type> types) {
        String ret = "";
        
        boolean first = true;
        
        for (Type type : types) {
            if (!first) ret += ", ";
            ret += getDisplayName(type);
            if (first) first = false;
        }
        
        return ret;
    }
    
    private String getDisplay(Prototype prototype) {
        String ret = "";
        
        if (prototype.getSourceURL() != null) {            
            ret += "In " + prototype.getSourceURL().getPath() + ":\n";
            
            ret += getContext(prototype.getSourceURL(),
                    prototype.getLineStart(),
                    prototype.getColStart());
        }
        else {
            String operationName = null;
            
            if (prototype instanceof FunctionCallPrototype) {
                operationName = ((FunctionCallPrototype) prototype).getFunctionName();
            }
            else if (prototype instanceof BinaryOpPrototype) {
                operationName = ((BinaryOpPrototype) prototype).getOperator().getLiteral();
            }
            else if (prototype instanceof UnaryOpPrototype) {
                operationName = ((UnaryOpPrototype) prototype).getOperator().getLiteral();
            }
            else {
                operationName = "INTERNAL ERROR OF THE COMPILER: unsupported prototype " + prototype;
            }
        
            if (prototype.getReturnType() != null) {
                ret += getDisplayName(prototype.getReturnType()) + " ";
            }
            
            List<Type> types= new ArrayList<Type>();
            
            for (PrototypeParameterDeclaration param : prototype.getParameterDeclarations()) {
                types.add(param.getType());
            }
            
            ret += (operationName + "(" + getDisplayNames(types) + ")\n");
        }
        
        return ret;
    }
    
    private String getDisplay(List<Prototype> prototypes) {
        String ret = "";
        
        for (Prototype prototype : prototypes) {
            ret += getDisplay(prototype);
        }
        
        return ret;
    }
    
    
    /**
     * Based on the error type, builds a human readable error message with
     * context from this diagnostic error
     * 
     * @param error
     *            the diagnostic error
     * @return the error message
     */
    public String stringify(DiagnosticError error){
        Diagnostic d = error.getDiagnostic();
        StringBuffer sb = new StringBuffer();

        if (error.getSourceFile() != null){
            sb.append("In " + error.getSourceFile().getPath() + ":\n");
        }

        String message = d.getMessage();
        String specific = getSpecificErrorMessage(error.errorcode);
        if (specific == null){
            // do not retrieve default message. Better force the correct classification of the error
            message = "[Error not correctly classified, defaulting to internal message, complain to devs]" + message;
        } else {
            message = specific;
            
            switch (error.errorcode) {
            case hasIncorrectType:
                String orSubType = "";
                if (error.getDiagnostic().getData().get(0) instanceof ValuedExpression) {
                    orSubType = " (or a sub-type)";
                }
                sb.append(String.format(message,
                        getDisplayName((Type) error.getDiagnostic().getData().get(2)),
                        orSubType,
                        getDisplayName((Type) error.getDiagnostic().getData().get(3)),
                        getContext(error)));
                break;
                
            case noMatchBinaryOp:
                sb.append(String.format(message,
                        ((BinaryOpExpression) error.getDiagnostic().getData().get(0)).getOperator().getLiteral(),
                        getDisplayName((Type) error.getDiagnostic().getData().get(2)),
                        getDisplayName((Type) error.getDiagnostic().getData().get(3)),
                        getContext(error)));
                break;
                
            case noMatchUnaryOp:
                sb.append(String.format(message,
                        ((UnaryOpExpression) error.getDiagnostic().getData().get(0)).getOperator().getLiteral(),
                        getDisplayName((Type) error.getDiagnostic().getData().get(2)),
                        getContext(error)));
                break;
                
            case noMatchFunctionCall:                
                sb.append(String.format(message,
                        ((FunctionCallExpression) error.getDiagnostic().getData().get(0)).getFunctionName(),
                        getDisplayNames((EList<Type>) error.getDiagnostic().getData().get(2)),
                        getContext(error)));
                break;
                
            case ambiguousBinaryOp:
                sb.append(String.format(message,
                        ((BinaryOpExpression) error.getDiagnostic().getData().get(0)).getOperator().getLiteral(),
                        getDisplayName((Type) error.getDiagnostic().getData().get(2)),
                        getDisplayName((Type) error.getDiagnostic().getData().get(3)),
                        getContext(error),
                        getDisplay((EList<Prototype>) error.getDiagnostic().getData().get(4))));
                break;
                
            case ambiguousUnaryOp:
                sb.append(String.format(message,
                        ((UnaryOpExpression) error.getDiagnostic().getData().get(0)).getOperator().getLiteral(),
                        getDisplayName((Type) error.getDiagnostic().getData().get(2)),
                        getContext(error),
                        getDisplay((EList<Prototype>) error.getDiagnostic().getData().get(3))));
                break;
                
            case ambiguousFunctionCall:
                sb.append(String.format(message,
                        ((FunctionCallExpression) error.getDiagnostic().getData().get(0)).getFunctionName(),
                        getDisplayNames((EList<Type>) error.getDiagnostic().getData().get(2)),
                        getContext(error),
                        getDisplay((EList<Prototype>) error.getDiagnostic().getData().get(3))));
                break;
                
            case matchingFunctionCallWithoutReturnValue:
                sb.append(String.format(message,
                        ((FunctionCallExpression) error.getDiagnostic().getData().get(0)).getFunctionName(),
                        getContext(error),
                        getDisplay((FunctionCallPrototype) error.getDiagnostic().getData().get(2))));
                break;
                
            case checkDuplicatedTriggerPortFromSameState:
                Transition transition = (Transition) error.getDiagnostic().getData().get(0);
                Transition previousTransition = (Transition) error.getDiagnostic().getData().get(2);
                
                sb.append(String.format(message,
                        getContext(error),
                        getContext(previousTransition.getSourceURL(),
                                previousTransition.getLineStart(),
                                previousTransition.getColStart())));
                break;
                
            case variableModifiedBetweenProvidedAndDo:
            case variableModifiedBetweenUpAndDown:
                PortDeclaration port = (PortDeclaration) error.getDiagnostic().getData().get(2);
                
                sb.append(String.format(message,
                        port.getName(),
                        getContext(error)));
                break;
                
            case uninitializedVariableExportedByPortOfAtom:
            case uninitializedVariableExportedByPortOfConnector:
                String variablesNames = "";
                Set<DataDeclaration> decls = (Set<DataDeclaration>) error.getDiagnostic().getData().get(3);
                
                boolean firstVar = true;
                
                for (DataDeclaration decl : decls) {
                    if (firstVar) firstVar = false;
                    else variablesNames += ",";
                    
                    variablesNames += "'" + decl.getName() + "'";
                }
                
                sb.append(String.format(message,
                        variablesNames,
                        ((PortDeclaration) error.getDiagnostic().getData().get(2)).getName(),
                        getContext(error)));
                break;
                
            case checkForCyclesInPrioritiesInAtom:
            case checkForCyclesInPrioritiesInCompound:
                List<AnnotatedEObject> cycle = (List<AnnotatedEObject>) error.getDiagnostic().getData().get(2);
                String cycleTxt = "";
                boolean firstPrio = true;
                
                if (cycle.size() > 1) cycleTxt = "priorities ";
                else cycleTxt = "priority ";
                
                for (AnnotatedEObject o : cycle) {
                    if (firstPrio) firstPrio = false;
                    else cycleTxt += ", ";
                    
                    String name = null;
                    
                    if (o instanceof AtomPriorityDeclaration) {
                        name = ((AtomPriorityDeclaration) o).getName();
                    }
                    else if (o instanceof CompoundPriorityDeclaration) {
                        name = ((CompoundPriorityDeclaration) o).getName();
                    }
                    else { assert(false); }
                    
                    cycleTxt += "'" + name + "'";
                }
                
                sb.append(String.format(message,
                        cycleTxt,
                        getContext(error)));
                break;

            default:
                sb.append(message + ":\n");
                sb.append(getContext(error));
            }
            
            sb.append("\n");
        }
        
        return sb.toString();
    }
    
    /**
     * Based on the error type, builds a human readable error message with context.
     * @param error the error
     * @return the error message
     */
    public String stringify(ParserOrLexerError error) {
        StringBuffer sb = new StringBuffer();
        String message;

        if (error.isNested()){
            if (error.getSourceFile() != null){
                sb.append("From " + error.getSourceFile().getPath() + ":\n");
            } else {
                sb.append("Nested error: \n");
            }
        } else {
            if (error.getSourceFile() != null){
                sb.append("In " + error.getSourceFile().getPath() + ":\n");
            }
        }
      
        String specific = getSpecificErrorMessage(error.errorcode);
        if (specific == null){
            // do not retrieve default message. Better force the correct classification of the error
            message = "[Error not correctly classified, defaulting to internal message, complain to devs] " + error.errorcode;
        } else {
            message = specific;
        }

        switch (error.errorcode) {

        case NoViableAlt:
            if (error.getErrorToken() != null)
                sb.append(String.format(message, "'" + error.getErrorToken() + "'") + "\n");
            else
                sb.append(String.format(message, "") + "\n");
            sb.append(getContext(error));
            break;

        case EarlyExit:
            sb.append(String.format(message, "'" + error.getErrorToken() + "'") + "\n");
            sb.append(getContext(error));
            break;

        case FailedPredicate:
        case MismatchedRange:
        case MismatchedSet:
        case MismatchedNotSet:
        case Recognition:
            sb.append(String.format(message, "'" + error.getErrorToken() + "'") + "\n");
            sb.append(getContext(error));
            break;

        case MissingToken:
        case UnwantedToken:
        case MismatchedToken:
            MismatchedTokenException mte = (MismatchedTokenException) error
                    .getAntlrException();
            String expected = Bip2Parser.tokenNames[mte.expecting];
            String errorToken;
            if (error.getErrorToken() == null) errorToken = "EOF";
            else errorToken = "'" + error.getErrorToken() + "'";

            sb.append(String.format(message, errorToken, expected) + "\n");
            sb.append(getContext(error));
            break;

        case RedefinedVariable:
        case RedefinedType:
        case RedefinedAnnotation:
            RedefinedSymbolException rse = (RedefinedSymbolException) error.getAntlrException();
            sb.append(String.format(message, rse.getSymbol(), getContext(error),
                    getContext(rse.getPreviousDeclaration().getSourceURL(),
                            rse.getPreviousDeclaration().getLineStart(),
                            rse.previousDeclaration.getColStart())) + "\n");
            break;

        case RedefinedAnnotationParameter:
            RedefinedAnnotationParameterException rape = (RedefinedAnnotationParameterException) error.getAntlrException();
            sb.append(String.format(message, rape.getSymbol(), getContext(error)));
            break;

        case UndefinedType:
            UndefinedTypeException ute = (UndefinedTypeException) error.getAntlrException();
            sb.append(String.format(message, ute.getUndefinedName()) + "\n");
            sb.append(getContext(error) + "\n");
            break;

        case UndefinedVariable:
            UndefinedVariableException uve = (UndefinedVariableException) error.getAntlrException();
            sb.append(String.format(message, uve.getUndefinedName()) + "\n");
            sb.append(getContext(error) + "\n");
            break;

        case UndefinedState:
            UndefinedStateException use = (UndefinedStateException) error.getAntlrException();
            sb.append(String.format(message, use.getUndefinedName()) + "\n");
            sb.append(getContext(error) + "\n");
            break;

        case AmbiguousType:
            AmbiguousTypeException ate = (AmbiguousTypeException) error.getAntlrException();
            String ateDecl = "";
            for (AnnotatedEObject declaration : ate.getDeclarations()) {
                ateDecl += "In " + declaration.getSourceURL().getPath() + ":\n";
                ateDecl += getContext(declaration.getSourceURL(),
                            declaration.getLineStart(),
                            declaration.getColStart());
            }
            
            sb.append(String.format(message, ate.getSymbol(), getContext(error), ateDecl) + "\n");
            break;

        case AmbiguousVariable:
            AmbiguousVariableException ave = (AmbiguousVariableException) error.getAntlrException();
            String aveDecl = "";
            for (AnnotatedEObject declaration : ave.getDeclarations()) {
                aveDecl += "In " + declaration.getSourceURL().getPath() + ":\n";
                aveDecl += getContext(declaration.getSourceURL(),
                            declaration.getLineStart(),
                            declaration.getColStart());
            }
            sb.append(String.format(message, ave.getSymbol(), getContext(error), aveDecl) + "\n");
            break;

        case IncorrectBipType:
            IncorrectBipTypeException ibte = (IncorrectBipTypeException) error.getAntlrException();
            sb.append(String.format(message, ibte.getSymbol(), ibte.getExpectedBipType()) + "\n");
            sb.append(getContext(error) + "\n");
            break;

        case GenericWalkerError:
            GenericWalkerErrorException gwee = (GenericWalkerErrorException) error.getAntlrException();
            sb.append("Error: " + gwee.getMessage() + ":\n");
            sb.append(String.format(message, gwee.getMessage()));
            
            sb.append(getContext(gwee.getFaultyObject().getSourceURL(),
                    gwee.getFaultyObject().getLineStart(),
                    gwee.getFaultyObject().getColStart()));
            break;

        case MismatchedTreeNode:
        case invalidConnectorDefine:
        case noDuplicatedPortReference:
        case OperationInvalidOrNotSupported:
        case IncorrectParameters:
        case LoadPackage:
        case DuplicatedPlaceDeclaration:
        case IncorrectNumberFormat:
            sb.append(message +"\n");
            sb.append(getContext(error) + "\n");
            break;

        default:
            sb.append("Error message not ready yet.\n");
            sb.append(getContext(error) + "\n");
        }

        if (error.isNested()){
            sb.append("Nested error: \n");
            for (GenericError ge: error.getNestedErrors())
                sb.append(stringify(ge));
        }

        return sb.toString();
    }
}
