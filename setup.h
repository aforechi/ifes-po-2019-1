#ifndef __SETUP_ORTOOLS_H__
#define __SETUP_ORTOOLS_H__

#define USE_GLOP
#define USE_CBC
#define USE_SCIP

#pragma cling add_include_path("ortools/include")
#pragma cling add_library_path("ortools/lib")

#pragma cling load("ortools")
#pragma cling load("CbcSolver")
#pragma cling load("Cbc")
#pragma cling load("OsiCbc")
#pragma cling load("Cgl")
#pragma cling load("ClpSolver")
#pragma cling load("Clp")
#pragma cling load("OsiClp")
#pragma cling load("Osi")
#pragma cling load("CoinUtils")
#pragma cling load("protobuf")
#pragma cling load("glog")
#pragma cling load("gflags")


#endif
