# Source Code

## `main.c`
Implementation of the calculation of the calibrated sensor outputs for SHT4xI sensors.

## `utilities.c` and `utilities.h`
These contain utility methods for parsing, setting, and reporting
the usage of demo-specific command-line arguments of C/C++ demo applications.
These methods call similar methods from `common.c` for handling
command-line arguments common to all of our C/C++ demo applications.

## `common.c` and `common.h`
These contain utility methods for parsing, setting, and reporting
the usage of command-line arguments common to all of our C/C++ demo applications,
as well as other methods that we commonly make use across our
C/C++ demo applications, e.g., standard methods for I/O handling. These
source files are symlinks to the original files contained in the repository
[Signaloid-Demo-CommonUtilityRoutines](https://github.com/signaloid/Signaloid-Demo-CommonUtilityRoutines)
which is included as a submodule in `submodules/common`.

## `uxhw.c` and `uxhw.h`
These contain methods that implement the probabilistic versions of the methods
in the UxHw® API (e.g., `UxHwDoubleGaussDist`) and uses the GNU Scientific Library (GSL)
random number generators to achieve that. This allows building our C/C++ demo applications
natively (i.e., on conventional architectures) and running native Monte Carlo evaluations
of our C/C++ demo applications without modifying the source code.
These source files are symlinks to the original files and are contained in the repository
[Signaloid-Demo-UxHwCompatibilityForNativeExecution](https://github.com/signaloid/Signaloid-Demo-UxHwCompatibilityForNativeExecution)
which is included as a submodule in `submodules/compat`.

## `kernel.c` and `kernel.h`
The sensor calibration routines, the input distributions and the distributional and Monte Carlo kernels.

## config.mk
Signaloid cores use this file to identify the source codes they will use when
building the C/C++ demo application.

# To Build Natively on Non-Signaloid Platforms

Run `make local-build` from the top-level folder.
This builds the `demo-native-mc` executable.
It needs GSL, for example `libgsl-dev` and `libblas-dev` on Linux.
