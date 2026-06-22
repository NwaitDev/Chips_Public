/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
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

#include <Launcher.hpp>

#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>

#include <stack>
#include <queue>

#include <Component.hpp>
#include <Compound.hpp>

#include <Atom.hpp>
#include <PortValue.hpp>

#include <Port.hpp>
#include <AtomInternalPort.hpp>
#include <CompoundExportPort.hpp>
#include <ConnectorExportPort.hpp>

#include <Executer.hpp>

#include <Logger.hpp>

#include <engine-version.hpp>

// global method that instanciates the system found in the generated code
Component* deploy(int argc, char **argv);

// constructors
Launcher::Launcher(int argc, char **argv, Component &root) :
  LauncherItf(argc, argv, root),
  mLogger(NULL),
  mEngine(NULL),
  mExecuter(NULL) {
  /* implement your constructor here */
}

// destructor
Launcher::~Launcher() {
  /* implement your destructor here */
}

int Launcher::initialize() {
  bool verbose = true; // default value
  bool help = false;
  bool invalidOption = false;
  bool version = false;
  bool randomSeed = true;
  unsigned int seed = 0;
  unsigned int limit = 0;
  unsigned int threads = 8;

  int ret = EXIT_SUCCESS;

  string bipExecutableName = "<bip_executable>";

  // set the name of the bip executable
  if (mArgc > 0) {
    bipExecutableName = string(mArgv[0]);
  }

  // parse options
  for (int i = 1 ; i < mArgc ; ++i) {
    string option = mArgv[i];

    if (option == "-v" || option == "--verbose") {
      verbose = true;
    }
    else if (option == "-s" || option == "--silent") {
      verbose = false;
    }
    else if (option == "-h" || option == "--help") {
      help = true;
    }
    else if (option == "-V" || option == "--version") {
      version = true;
    }
    else if (option == "--seed") {
      randomSeed = false;

      // look for an integer argument
      if (i < mArgc - 1) {
        ++i;
        std::string argument = mArgv[i];
        std::stringstream iss(argument);
        iss >> seed;

        if (iss.fail()) {
          invalidOption = true;
          ret = EXIT_FAILURE;

          cout << bipExecutableName << ": invalid arguement for '" << option << "', waiting for an interger" << endl;
          cout << "Try `" << bipExecutableName << " --help' for more information." << endl;

          break;
        }
      }
      else {
        invalidOption = true;
        ret = EXIT_FAILURE;

        cout << bipExecutableName << ": missing integer argument for '" << option << "'" << endl;
        cout << "Try `" << bipExecutableName << " --help' for more information." << endl;

        break;
      }
    }
    else if (option == "-l" || option == "--limit") {
      // look for an integer argument
      if (i < mArgc - 1) {
        ++i;
        std::string argument = mArgv[i];
        std::stringstream iss(argument);
        iss >> limit;

        if (iss.fail() || limit <= 0) {
          invalidOption = true;
          ret = EXIT_FAILURE;

          cout << bipExecutableName << ": invalid arguement for '" << option << "', waiting for a positive interger" << endl;
          cout << "Try `" << bipExecutableName << " --help' for more information." << endl;

          break;
        }
      }
      else {
        invalidOption = true;
        ret = EXIT_FAILURE;

        cout << bipExecutableName << ": missing positive integer argument for '" << option << "'" << endl;
        cout << "Try `" << bipExecutableName << " --help' for more information." << endl;

        break;
      }
    }
    else if (option == "--threads") {
      // look for an integer argument
      if (i < mArgc - 1) {
        ++i;
	    std::string argument = mArgv[i];
        std::stringstream iss(argument);
        iss >> threads;

        if (iss.fail() || threads <= 0) {
          invalidOption = true;
          ret = EXIT_FAILURE;

          cout << bipExecutableName << ": invalid arguement for '" << option << "', waiting for a positive interger" << endl;
          cout << "Try `" << bipExecutableName << " --help' for more information." << endl;

          break;
        }
      }
      else {
        invalidOption = true;
        ret = EXIT_FAILURE;

        cout << bipExecutableName << ": missing non-negative integer argument for '" << option << "'" << endl;
        cout << "Try `" << bipExecutableName << " --help' for more information." << endl;

        break;
      }
    }
    else {
      invalidOption = true;
      ret = EXIT_FAILURE;

      cout << bipExecutableName << ": invalid option -- '" << option << "'" << endl;
      cout << "Try `" << bipExecutableName << " --help' for more information." << endl;

      break;
    }
  }

  if (help) {
    printHelp(bipExecutableName);
  }

  if (version) {
    cout << "Reference engine. Version: " ENGINE_VERSION << endl;
    return EXIT_SUCCESS;
  }

  if (!invalidOption && !help) {
    mLogger = new Logger(cout, verbose, limit);

    mExecuter = new Executer(dynamic_cast<Compound &>(root()), *mLogger, threads, randomSeed, seed);

    BipError &error = mExecuter->initialize();

    if (error.type() != NO_ERROR) {
      ret = error.type();
    }
  }

  return ret;
}

int Launcher::launch() {
  int ret = EXIT_SUCCESS;

  if (mExecuter != NULL) {  
    BipError &error = mExecuter->run();
  
    if (error.type() != NO_ERROR) {
      ret = error.type();
    }
  }
  
  return ret;
}

void Launcher::printHelp(const string &bipExecutableName) {
   cout << "Usage: " << bipExecutableName << " [options]" << endl;
   cout << endl;
   cout << "BIP Engine general options:" << endl;
   cout << "                    (i.e. executes interactions in parallel, if obs. equivalent)" << endl;
   cout << " -h, --help         display this help and exit" << endl;
   cout << " -l, --limit LIMIT  limits the execution to LIMIT interactions" << endl;
   cout << " --seed SEED        set the seed for random to SEED" << endl;
   cout << " --threads NB       set the number of threads (by default, use the maximal HW parallelism or 8)" << endl;
   cout << " -s, --silent       disables the display of the sequence of enabled/chosen interactions" << endl;
   cout << " -v, --verbose      enables the display of the sequence of enabled/chosen interactions (default)" << endl;
   cout << " -V, --version      displays engine version and exits" << endl;
}
