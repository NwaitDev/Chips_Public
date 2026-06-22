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

package ujf.verimag.bip.error.message;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public enum ErrorCodeEnum {
    GenericDefault,
    /*
     * Error code for error from the Walker (ie. during model building)
     */
    invalidConnectorDefine,
    
    // importing old error codes from parser/lexer error
    Recognition,
    MismatchedToken,
    MismatchedTreeNode,
    NoViableAlt,
    EarlyExit,
    FailedPredicate,
    MismatchedRange,
    MismatchedSet,
    MismatchedNotSet,
    MissingToken,
    UnwantedToken,

    // following errors are used in the walker when
    // creating model objects.
    IncorrectParameters,
    LoadPackage,
    OperationInvalidOrNotSupported,
    RedefinedType,
    RedefinedVariable,
    RedefinedAnnotation,
    RedefinedAnnotationParameter,
    UndefinedType,
    UndefinedVariable,
    UndefinedState,
    AmbiguousType,
    AmbiguousVariable,
    IncorrectBipType,
    CycleIn,
    GenericWalkerError,
    // end of import from old parser/lexer error
    DuplicatedPlaceDeclaration,
    IncorrectNumberFormat,

    // following for Loader specific error code
    PackageNotFound,
    CycleFoundInPackageDep,
    PackageNameDoesNotMatchFileName,
    PackageNotLoaded,
    
    /*
     * Error code for error from EMF diagnostics.
     * 1 code corresponds to 1 constraints (in general. It is possible to share
     * code, but not a good idea, be careful) 
     */
    
    //Actionlang Constraints
    dataIsExportedInComponent,
    noRefToLocalDataInConnectorGuard,
    LHSnotComponentParameter,
    uninitializedConstData,
    invalidLHSOfAssignment,
    dataRefInConnectorActionToInvolvedPort,
    hasIncorrectType,
    hasIncorrectConst,
    noSideEffectInGuards,
    noMatchBinaryOp,
    noMatchUnaryOp,
    noMatchFunctionCall,
    ambiguousBinaryOp,
    ambiguousUnaryOp,
    ambiguousFunctionCall,
    matchingFunctionCallWithoutReturnValue,
    
    // PetriNet constraints
    checkDuplicatedTriggerPortFromSameState,
    variableModifiedBetweenProvidedAndDo,
    uninitializedVariableOfPetriNet,
    uninitializedVariableExportedByPortOfAtom,
    uninitializedVariableExportedByAtom,
    deadCode,
    isNotOneSafe,
    
    //Share between Atom and Compound constraints and Walker
    referencedPortsHaveTheSameType,
    noDuplicatedPortReference,
    noDuplicatedExport,
    
    // Compound constraints
    sameDataTypeAsPointedDeclaration,
    
    // Component constraints
    componentDeclarationHasCorrectNumberOfParam,
    dataTypeIsBasic,
    componentDeclarationHasNoUnconnectedPort,
    
    // Connector constraints
    hasCorrectNumberOfPortParameters,
    connectorDeclarationHasnoDuplicatedPortReferenceParameter,
    connectorHasExportPortBound,

//    hasCorrectTypeForPortParameters,
    onPortInConnectorParameters,
    upDoesNotContainExternalSubDataRefOnLHSAssignments,
    connectorActionNotEmpty,
    noUpIfNoExportedPort,
    missingUpForExportedPort,
    triggerPortsValidWrtDefine,
    noDuplicatedInteractionAction,
    checkDownWhenNoDataInConnectorPort,
    variableModifiedBetweenUpAndDown,
    uninitializedVariableOfConnectorInteractionAction,
    uninitializedVariableExportedByPortOfConnector,
    
    // Data constraints
    hasOneDeclaration,
    
    // Instance constraints
    instanceHasCorrectNumberOfParams,
    connectorDoesNotBindTheSameComponentMoreThanOnce, // for connector instance
    
    // Port constraints
    hasCorrectNumberOfDataParameters,
    hasCorrectTypeForDataParameters,
    subPortDeclarationReferenceHasOneDeclaration,
    portParameterHasCorrectPortType,
    
    // Priority constraints
    compoundPriorityHasAtMostOneWildcard,
    compoundPriorityInvolvesOnlyTopLevelConnectors,
    portReferencesOnCorrectConnectorDeclaration,
    noDuplicatedPortReferenceInConnectorInteraction,
    atomPriorityHasAtMostOneWildcard,
    interactionIsDefinedInConnector,
    priorityDuplicateMaximalProgress,
    
    // Type constraints
    InternalDataSynchronizedWithExportedData,
    exportedPortsListsSynchronized,
    exportedDataListsSynchronized,
    interactionDefinedIfExportPortWithData,
    missingInteractionIfExportPortWithData,
    checkForCyclesInPrioritiesInAtom, // Atom Type
    checkForCyclesInPrioritiesInCompound, // Compoud Type
    priorityContradictMaximalProgress,
    uninitializedVariableInAtomInternalDataDeclaration,
    uninitializedVariableInConnectorDataDeclaration,
    
    // BipPackage constraints
    checkForCyclesInSubTyping,
    incorrectConstForConstDataDeclaration;

    /**
     * This map contains the mapping between user friendly names for
     * error/warnings and their corresponding internal name.
     * This is used for SuppressWarning annotation
     */
    public static HashMap<String, Set<ErrorCodeEnum>> userFriendlyNames;
    private static void addUserFriendlyName(String name, ErrorCodeEnum code) {
        if (!userFriendlyNames.containsKey(name)) {
            userFriendlyNames.put(name, new HashSet<ErrorCodeEnum>());
        }
        
        userFriendlyNames.get(name).add(code);
    }
    
    static {
        userFriendlyNames = new HashMap<String, Set<ErrorCodeEnum>>();
        
        addUserFriendlyName("nondeterminism", checkDuplicatedTriggerPortFromSameState);
        addUserFriendlyName("unboundcomponentport", componentDeclarationHasNoUnconnectedPort);
        addUserFriendlyName("unboundconnectorport", connectorHasExportPortBound);
        addUserFriendlyName("missingup", missingUpForExportedPort);
        addUserFriendlyName("atomprioritycycle", checkForCyclesInPrioritiesInAtom);
        addUserFriendlyName("uselessdown", checkDownWhenNoDataInConnectorPort);
        addUserFriendlyName("nointeraction", interactionDefinedIfExportPortWithData);
        addUserFriendlyName("missinginteraction", missingInteractionIfExportPortWithData);
        addUserFriendlyName("modifiedvariable", variableModifiedBetweenProvidedAndDo);
        addUserFriendlyName("modifiedvariable", variableModifiedBetweenUpAndDown);
        addUserFriendlyName("uninitializedvariable", uninitializedVariableOfPetriNet);
        addUserFriendlyName("uninitializedvariable", uninitializedVariableExportedByPortOfAtom);
        addUserFriendlyName("uninitializedvariable", uninitializedVariableExportedByAtom);
        addUserFriendlyName("uninitializedvariable", uninitializedVariableOfConnectorInteractionAction);
        addUserFriendlyName("uninitializedvariable", uninitializedVariableExportedByPortOfConnector);
        addUserFriendlyName("deadcode", deadCode);
    }
}
