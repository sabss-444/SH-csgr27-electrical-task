// This is the only file you should edit.

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
