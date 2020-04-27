This folder contains CSMA/CA unit tests developed for the legacy, genproject-based framework.
They have not been ported to CMake-based framework that is present in NCS, because the CSMA/CA
module depends on software components that became closed-source, namely RSCH and Timer Scheduler.
Currently it is unclear how these unit tests should be approached, so they were moved out of the
common unit tests folder.
