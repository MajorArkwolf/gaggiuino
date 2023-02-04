#include "eeprom_data/eeprom_data.h"

namespace
{
    eepromValues_t getEepromDefaults()
    {
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
}

void eepromInit()
{
}
bool eepromWrite(eepromValues_t eepromValuesNew)
{
    //TODO: Ark
    return true;
}
struct eepromValues_t eepromGetCurrentValues()
{
    return getEepromDefaults();
}