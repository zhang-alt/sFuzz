#include "OracleFactory.h"

using namespace dev;
using namespace eth;
using namespace std;

namespace fuzzer  {
  OracleFactory::OracleFactory() {
    remove("contracts/log.txt");
  }
  
  void OracleFactory::initialize() {
    callLog.clear();
  }
  
  void OracleFactory::finalize() {
    callLogs.push_back(callLog);
    callLog.clear();
  }
  
  void OracleFactory::save(CallLogItem fc) {
    callLog.push_back(fc);
  }
  
  vector<tuple<string, bytes>> OracleFactory::analyze() {
    vector<tuple<string, bytes>> result;
    for (auto callLog : callLogs) {
      if (!oracleResult.gaslessSend) {
        oracleResult.gaslessSend += gaslessSend.analyze(callLog) ? 1 : 0;
        if (oracleResult.gaslessSend) {
          result.push_back(make_tuple("GASLESS_SEND", gaslessSend.getTestData()));
        }
      }
      if (!oracleResult.exceptionDisorder) {
        oracleResult.exceptionDisorder += exceptionDisorder.analyze(callLog) ? 1 : 0;
        if (oracleResult.exceptionDisorder) {
          result.push_back(make_tuple("EXCEPTION_DISORDER", exceptionDisorder.getTestData()));
        }
      }
      if (!oracleResult.timestampDependency) {
        oracleResult.timestampDependency += timestampDependency.analyze(callLog) ? 1 : 0;
        if (oracleResult.timestampDependency) {
          result.push_back(make_tuple("TIMESTAMP", timestampDependency.getTestData()));
        }
      }
      if (!oracleResult.blockNumDependency) {
        oracleResult.blockNumDependency += blockNumberDependency.analyze(callLog) ? 1 : 0;
        if (oracleResult.blockNumDependency) {
          result.push_back(make_tuple("BLOCK_NUMBER", blockNumberDependency.getTestData()));
        }
      }
      if (!oracleResult.dangerDelegateCall) {
        oracleResult.dangerDelegateCall += dangerDelegateCall.analyze(callLog) ? 1 : 0;
        if (oracleResult.dangerDelegateCall) {
          result.push_back(make_tuple("DELEGATE", dangerDelegateCall.getTestData()));
        }
      }
      if (!oracleResult.integerOverflow) {
        oracleResult.integerOverflow += integerOverflow.analyze(callLog) ? 1 : 0;
        if (oracleResult.integerOverflow) {
          result.push_back(make_tuple("INTEGER_OVERFLOW", integerOverflow.getTestData()));
        }
      }
      if (!oracleResult.integerUnderflow) {
        oracleResult.integerUnderflow += integerUnderflow.analyze(callLog) ? 1 : 0;
        if (oracleResult.integerUnderflow) {
          result.push_back(make_tuple("INTEGER_UNDERFLOW", integerUnderflow.getTestData()));
        }
      }
      if (!oracleResult.freezingEther) {
        oracleResult.freezingEther += freezingEther.analyze(callLog) ? 1 : 0;
        if (oracleResult.freezingEther) {
          result.push_back(make_tuple("FREEZING", freezingEther.getTestData()));
        }
      }
    }
    callLogs.clear();
    return result;
  }
}