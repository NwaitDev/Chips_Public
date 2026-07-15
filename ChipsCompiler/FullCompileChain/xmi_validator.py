#!/usr/bin/env python3
"""
This programm validates that an XMI file conforms to a given Ecore metamodel.

Usage:
    python xmi_validator.py <ecore_file> <xmi_file>
    python xmi_validator.py <ecore_file> <xmi_file> -v to see the detailed information

"""

import sys
import os
import argparse
from pyecore.ecore import EPackage, EClass, EAttribute, EReference
from pyecore.resources import ResourceSet, URI
from pyecore.resources.xmi import XMIResource



def validate_xmi(ecore_path, xmi_path, verbose=False):
    """
    Validate an XMI file against an Ecore metamodel
    Args:
        ecore_path: Path to the Ecore metamodel file
        xmi_path: Path to the XMI instance file to validate
        verbose: Whether to print detailed information
    
    Returns:
        bool: True if validation successful, False otherwise
    """

    if not os.path.exists(ecore_path):
        print(f"\033[31m Ecore file not found: {ecore_path}\033[0m")
        return False
    
    if not os.path.exists(xmi_path):
        print(f"\033[31m XMI file not found: {xmi_path}\033[0m")
        return False
    
    if verbose:
        print(f"Loading Ecore metamodel from: {ecore_path}")
    
    try:
        rset = ResourceSet()
        
        ecore_resource = rset.get_resource(URI(ecore_path))
        ecore_root = ecore_resource.contents[0]

        if isinstance(ecore_root, EPackage):
            rset.metamodel_registry[ecore_root.nsURI] = ecore_root
            if verbose:
                print(f"Loaded metamodel: {ecore_root.name} (nsURI: {ecore_root.nsURI})")
                print(f"  Package contains {len(ecore_root.eClassifiers)} classifiers")
            
            def register_subpackages(package):
                for subpkg in package.eSubpackages:
                    rset.metamodel_registry[subpkg.nsURI] = subpkg
                    if verbose:
                        print(f"  Registered sub-package: {subpkg.name} (nsURI: {subpkg.nsURI})")
                        print(f"    Contains {len(subpkg.eClassifiers)} classifiers")
                    register_subpackages(subpkg)
            
            register_subpackages(ecore_root)
        else:
            print("\033[31m The Ecore file does not contain a valid EPackage\033[0m")
            return False
        
        if verbose:
            print(f"Loading XMI instance from: {xmi_path}")
        
        xmi_resource = rset.get_resource(URI(xmi_path))
        
        if not xmi_resource.contents:
            print("\033[31m XMI file is empty or could not be loaded!\033[0m")
            return False
        
        print("\033[32m XMI file is valid according to the Ecore metamodel!\033[0m")
        return True
        
    except Exception as e:
        print(f"\033[31m Validation failed: {str(e)}\033[0m")
        if verbose:
            import traceback
            print()
            print("Detailed error trace:")
            traceback.print_exc()
        return False


def main():
    parser = argparse.ArgumentParser()
    
    parser.add_argument('ecore_file', help='Path to the Ecore metamodel file')
    parser.add_argument('xmi_file', help='Path to the XMI instance file to validate')
    parser.add_argument('-v', '--verbose', action='store_true', 
                        help='Output with detailed information')
    
    args = parser.parse_args()
    
    print()
    print(f"XMI Validator")
    print("=" * 60)
    print()

    success = validate_xmi(args.ecore_file, args.xmi_file, args.verbose)
    
    print()
    print("=" * 60)

    sys.exit(0 if success else 1)


if __name__ == '__main__':
    main()
