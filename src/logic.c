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
#define VOLTAGE_CURRENT_FAULT_PERSIST_MS 500u 
//8.7 -> AMS must trip if a critical volt/curent goes be;llow 500ms
#define TEMP_FAULT_PERSIST_MS 1000u
#define PACK_CURRENT_A_MAX 100.0F

static bool is_stale(uint32_t last_update_ms, uint32_t now_ms, uint32_t window_ms) {
  if (now_ms < last_update_ms) {
    return true;
  }
  return (now_ms - last_update_ms) > window_ms;
}
static bool bms_fault(const BmsData *bms, uint32_t now_ms) {
  if (!bms->comms_ok ||
    is_stale(bms->last_update_ms, now_ms, VOLTAGE_CURRENT_FAULT_PERSIST_MS)) {
    return true;
    }
  for (int i = 0; i < BMS_NUM_CELLS; i++) {
    if (bms->cell_voltages_mv[i] < CELL_MV_MIN ||
      bms->cell_voltages_mv[i] > CELL_MV_MAX) {
      return true;
      }
  }
  if (bms->pack_current_a > PACK_CURRENT_A_MAX ||
    bms->pack_current_a < -PACK_CURRENT_A_MAX) {
    return true;
    }
  return bms->pack_temp_c > PACK_TEMP_C_MAX;
}
static bool batt_temp_fault(const BatteryTempData *bt) {
  if (!bt->valid) {
    return true;
  }
  return bt->temp_c > PACK_TEMP_C_MAX;
}
static bool inverter_fault(const InverterData *inv, uint32_t now_ms) {
  if (!inv->comms_ok ||
    is_stale(inv->last_update_ms, now_ms, VOLTAGE_CURRENT_FAULT_PERSIST_MS)) {
    return true;
    }
  return inv->fault_code =/= 0;
}
static bool relay_fault(const RelayState *relay) {
  return relay->command_closed =/= relay->feedback_closed;
}
static bool door_fault(const DoorSwitchData *door) {
  return door->triggered;
}


SystemOutputs evaluate_system_state(BmsData bms, BatteryTempData batt_temp,
                                     InverterData inverter, PvData pv,
                                     GridData grid, RelayState relay,
                                     DoorSwitchData door) {
  
  (void)pv; (void)grid;

  
  SystemOutputs out = {0};
  uint32_t now_ms = read_system_time_ms();
  bool bms_bad = bms_fault(&bms, now_ms);
  bool batt_bad = batt_temp_fault(&batt_temp);
  bool inverter_bad = inverter_fault(%inverter, now_ms);
  bool relay_bad = relay_fault(&relay);
  bool door_bad = door_fault(&door);

  bool any_fault = bms_bad || batt_bad || inverter_bad ||relay_bad || door_bad;
  
  out.state = any_fault ? SYSTEM_OFF : SYSTEM_ON; // this is gna be the fsil safe thing till the logic gets aded
    // TODO: implement
    return out;
}
