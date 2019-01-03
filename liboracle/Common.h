#pragma once
#include <iostream>
#include <libdevcore/CommonIO.h>
#include <libevm/LegacyVM.h>

using namespace dev;
using namespace eth;
using namespace std;

namespace fuzzer {
  struct CallLogItemPayload {
    u256 wei = 0;
    u256 gas = 0;
    u256 pc = 0;
    Instruction inst;
    bytes data;
    bytes testData;
    bool isOverflow = false;
    bool isUnderflow = false;
  };
  struct CallLogItem {
    CallLogItemPayload payload;
    u256 level;
    CallLogItem(u256 _level, CallLogItemPayload _payload): payload(_payload), level(_level) {}
  };
  
  struct OracleResult {
    u256 gaslessSend = 0;
    u256 exceptionDisorder = 0;
    u256 timestampDependency = 0;
    u256 blockNumDependency = 0;
    u256 dangerDelegateCall = 0;
    u256 reentrancy = 0;
    u256 freezingEther = 0;
    u256 integerOverflow = 0;
    u256 integerUnderflow = 0;
  };
  
  using CallLogs = vector<vector<CallLogItem>>;
  using CallLog = vector<CallLogItem>;
  
  class Oracle {
    protected:
      bytes testData;
    public:
      virtual bool analyze(CallLog callLog) = 0;
      bytes getTestData() { return testData; }
  };
}