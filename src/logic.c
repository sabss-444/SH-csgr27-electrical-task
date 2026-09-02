// This is the only file you should edit.
// im assuming the home battery is using the same as the fsuk data sheet cos idk wherre to get the thresholds
// 32 cells in series, nominal pack voltage 102.4v
// max pack 116.8v per cell
// so divide by 32 
// nominal 102.4 / 32 = 3.2v (3200mV)
//max 116.8 / 32 = 3.65v (3650mV)
//google says minimum safe voltage is 2.5v 
// range 2500 - 3650 
#include "logic.h"
#include "mock_hw.h"

SystemOutputs evaluate_system_state(BmsData bms, BatteryTempData batt_temp,
                                     InverterData inverter, PvData pv,
                                     GridData grid, RelayState relay,
                                     DoorSwitchData door) {
  (void)bms; (void)batt_temp; (void)inverter;
  (void)pv; (void)grid; (void)relay; (void)door;

  
  SystemOutputs out = {0};
  out.state = SYSTEM_OFF; // this is gna be the fsil safe thing till the logic gets aded
    // TODO: implement
    return out;
}
