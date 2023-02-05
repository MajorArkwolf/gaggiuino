#include "eeprom_data/eeprom_data.h"
#include "EEPROM.h"
#include "log.h"

namespace {
constexpr uint16_t CurrentEEPROMVersion = 6;

template <class T>
struct MetaData {
  uint16_t version = 0;
  unsigned long timestamp = {};
  T data = {};
  uint32_t versionTimestampXOR = {};

  static MetaData<T> GenerateNewMetaData(const T& dataIn) {
    auto output = MetaData{};
    output.timestamp = millis();
    output.version = CurrentEEPROMVersion;
    output.data = dataIn;
    output.versionTimestampXOR = output.timestamp ^ output.version;
    return output;
  }
};

constexpr auto MemoryRequired = sizeof(MetaData<eepromValues_t>);
static MetaData<eepromValues_t> eepromMetadata = {};

eepromValues_t getEepromDefaults(void) {
  eepromValues_t defaultData;

  defaultData.setpoint = 100;
  defaultData.steamSetPoint = 162;
  defaultData.offsetTemp = 7;
  defaultData.hpwr = 550;
  defaultData.mainDivider = 5;
  defaultData.brewDivider = 2;
  defaultData.pressureProfilingStart = 9;
  defaultData.pressureProfilingFinish = 6;
  defaultData.pressureProfilingHold = 5;
  defaultData.pressureProfilingLength = 15;
  defaultData.pressureProfilingState = true;
  defaultData.preinfusionState = true;
  defaultData.preinfusionSec = 10;
  defaultData.preinfusionBar = 2;
  defaultData.preinfusionSoak = 10;
  defaultData.preinfusionRamp = 0;
  defaultData.preinfusionFlowState = false;
  defaultData.preinfusionFlowVol = 3.5f;
  defaultData.preinfusionFlowTime = 10;
  defaultData.preinfusionFlowSoakTime = 5;
  defaultData.preinfusionFlowPressureTarget = 0;
  defaultData.flowProfileState = false;
  defaultData.flowProfileStart = 3.5f;
  defaultData.flowProfileEnd = 2.0f;
  defaultData.flowProfilePressureTarget = 7;
  defaultData.flowProfileCurveSpeed = 15;
  defaultData.powerLineFrequency = 50;
  defaultData.lcdSleep = 16;
  defaultData.warmupState = false;
  defaultData.homeOnShotFinish = true;
  defaultData.graphBrew = true;
  defaultData.brewDeltaState = true;
  defaultData.switchPhaseOnThreshold = false;
  defaultData.basketPrefill = false;
  defaultData.scalesF1 = 3920;
  defaultData.scalesF2 = 4210;
  defaultData.pumpFlowAtZero = 0.285f;
  defaultData.stopOnWeightState = false;
  defaultData.shotDose = 18.0f;
  defaultData.shotStopOnCustomWeight = 0.f;
  defaultData.shotPreset = 0;

  return defaultData;
}
}  // namespace

bool eepromWrite(const eepromValues_t& eepromValuesNew) {
  eepromMetadata =
      MetaData<eepromValues_t>::GenerateNewMetaData(eepromValuesNew);
  EEPROM.writeBytes(0, &eepromMetadata, MemoryRequired);
  EEPROM.commit();

  auto validateWriteData = MetaData<eepromValues_t>{};
  EEPROM.readBytes(0, &eepromMetadata, MemoryRequired);
  if (validateWriteData.versionTimestampXOR !=
      eepromMetadata.versionTimestampXOR) {
    LOG_ERROR("Write/Read on EEPROM Failed: Written XOR: %d, Read XOR: %d",
              eepromMetadata.versionTimestampXOR,
              validateWriteData.versionTimestampXOR);
    return false;
  }
  return true;
}

void eepromInit() {
  eepromMetadata =
      MetaData<eepromValues_t>::GenerateNewMetaData(getEepromDefaults());

  while (!EEPROM.begin(MemoryRequired)) {}
  LOG_DEBUG("EEPROM succesfully initiated, beginning loading data");
  uint16_t version = 0;
  EEPROM.get(0, version);
  if (version == CurrentEEPROMVersion) {
    LOG_DEBUG("EEPROM found a valid version in the EEPROM, loading data");
    EEPROM.readBytes(0, &eepromMetadata, MemoryRequired);
    auto xorOutput = eepromMetadata.timestamp ^ eepromMetadata.version;
    if (xorOutput != eepromMetadata.versionTimestampXOR) {
      LOG_ERROR(
          "Timestamp and Version XOR did not equal the expected output, "
          "adding fresh values to eeprom");
      LOG_DEBUG("Calculated XOR: %d, Expected XOR: %d", xorOutput,
                eepromMetadata.versionTimestampXOR);
      if (!eepromWrite(getEepromDefaults())) {
        LOG_ERROR("Failed to write to EEPROM");
      }
    }
  } else {
    LOG_INFO(
        "EEPROM did not find a valid version in the EEPROM, writing new data");
    if (!eepromWrite(getEepromDefaults())) {
      LOG_ERROR("Failed to write to EEPROM");
    }
  }
}

const eepromValues_t& eepromGetCurrentValues() {
  return eepromMetadata.data;
}
