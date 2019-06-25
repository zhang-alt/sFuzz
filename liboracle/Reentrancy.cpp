#include "Reentrancy.h"

using namespace dev;
using namespace eth;
using namespace std;

namespace fuzzer {
  bool Reentrancy::analyze(CallLog callLog) {
      for (auto callLogItem : callLog) {
      auto data = callLogItem.payload.data;
      auto level = callLogItem.level;
      if (level >= 4 && toHex(data) == "000000ff") {
        testData = callLog[0].payload.testData;
        issuePayloadPc = callLogItem.payload.pc;
        return true;
      }
    }
    return false;
  }
}

