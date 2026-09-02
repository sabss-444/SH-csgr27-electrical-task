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
#define CELL_MV_MIN 2500.0F
#define CELL_MV_MAX 3650.0F
#define PACK_TEMP_C_MAX 60.0F 
// max temp given was 60
#define VOLTAGE_CURRENT_FAULT?_PERSIST_MS 500u 
//8.7 -> AMS must trip if a critical volt/curent goes be;llow 500ms
#define TEMP_FAULT_PERSIST_MS 1000u
#define PACK_CURRENT_A_MAX 100.0F

static bool is_stale(uint32_t last_update_ms, uint32_t now_ms, uint32_t window_ms) {
  if (now_ms < last_update_ms) {
    return true;
  }
  return (now_ms - last_update_ms) > window_ms;
}



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
