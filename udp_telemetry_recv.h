#ifndef UDP_TELEMETRY_RECV_H
#define UDP_TELEMETRY_RECV_H

typedef union
{
  uint8_t binary[264];
  struct
  {
    float total_time;
    float lap_time;
    float lap_distance;
    float total_distance;
    float position_x;
    float position_y;
    float position_z;
    float speed;
    float velocity_x;
    float velocity_y;
    float velocity_z;
    float left_dir_x;
    float left_dir_y;
    float left_dir_z;
    float forward_dir_x;
    float forward_dir_y;
    float forward_dir_z;
    float suspension_position_bl;
    float suspension_position_br;
    float suspension_position_fl;
    float suspension_position_fr;
    float suspension_velocity_bl;
    float suspension_velocity_br;
    float suspension_velocity_fl;
    float suspension_velocity_fr;
    float wheel_patch_speed_bl;
    float wheel_patch_speed_br;
    float wheel_patch_speed_fl;
    float wheel_patch_speed_fr;
    float throttle_input;
    float steering_input;
    float break_input;
    float clutch_input;
    float gear;
    float gforce_lateral;
    float gforce_longitudinal;
    float lap;
    float engine_rate;
    float native_sli_support;
    float race_position;
    float kers_level;
    float kers_level_max;
    float drs;
    float traction_control;
    float abs;
    float fuel_in_tank;
    float fuel_capacity;
    float in_pits;
    float race_sector;
    float sector_time_1;
    float sector_time_2;
    float break_temp_bl;
    float break_temp_br;
    float break_temp_fl;
    float break_temp_fr;
    float tyre_pressure_bl;
    float tyre_pressure_br;
    float tyre_pressure_fl;
    float tyre_pressure_fr;
    float laps_completed;
    float total_laps;
    float track_length;
    float last_lap_time;
    float max_rpm;
  };
} Telemetry;

#endif // UDP_TELEMETRY_RECV_H