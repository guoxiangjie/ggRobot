#pragma once
#include <map>
#include <string>
#include <vector>

/**
 * @brief Robot model definition
 */
enum class JointArea
{
  HEAD,   // Head joints
  ARM,    // Arm joints
  WAIST,  // Waist joints
  LEG,    // Leg joints
};

/**
 * @brief Joint information structure
 */
struct JointInfo
{
  std::string name;         // Joint name
  double      lower_limit;  // Joint angle lower limit
  double      upper_limit;  // Joint angle upper limit
  double      kp;           // Position control gain
  double      kd;           // Velocity control gain
};

/**
 * @brief Robot model configuration
 * Contains parameters for all joints, enabling or disabling specific joints as
 * needed
 */
inline std::map<JointArea, std::vector<JointInfo>> robot_model = {
    {JointArea::LEG,
     {
         // Left leg joint configuration
         {"left_hip_pitch_joint", -2.4871, 2.4871, 40.0, 4.0},       // Left hip pitch
         {"left_hip_roll_joint", -0.12217, 2.9059, 40.0, 4.0},       // Left hip roll
         {"left_hip_yaw_joint", -1.6842, 3.4296, 30.0, 3.0},         // Left hip yaw
         {"left_knee_joint", 0.026179, 2.1206, 80.0, 8.0},           // Left knee
         {"left_ankle_pitch_joint", -0.80285, 0.45378, 40.0, 4.0},   // Left ankle pitch
         {"left_ankle_roll_joint", -0.2618, 0.2618, 20.0, 2.0},      // Left ankle roll
                                                                     // Right leg joint configuration
         {"right_hip_pitch_joint", -2.4871, 2.4871, 40.0, 4.0},      // Right hip pitch
         {"right_hip_roll_joint", -2.9059, 0.12217, 40.0, 4.0},      // Right hip roll
         {"right_hip_yaw_joint", -3.4296, 1.6842, 30.0, 3.0},        // Right hip yaw
         {"right_knee_joint", 0.026179, 2.1206, 80.0, 8.0},          // Right knee
         {"right_ankle_pitch_joint", -0.80285, 0.45378, 40.0, 4.0},  // Right ankle pitch
         {"right_ankle_roll_joint", -0.2618, 0.2618, 20.0, 2.0},     // Right ankle roll
     }},

    {JointArea::WAIST,
     {
         // Waist joint configuration
         {"waist_yaw_joint", -3.4296, 2.3824, 20.0, 4.0},      // Waist yaw
         {"waist_pitch_joint", -0.17453, 0.17453, 20.0, 4.0},  // Waist pitch
         {"waist_roll_joint", -0.48869, 0.48869, 20.0, 4.0},   // Waist roll
     }},
    {JointArea::ARM,
     {
         // Left arm joint configuration
         {"left_shoulder_pitch_joint", -2.5569, 2.5569, 20.0, 2.0},   // Left shoulder pitch
         {"left_shoulder_roll_joint", -0.06108, 3.3598, 20.0, 2.0},   // Left shoulder roll
         {"left_shoulder_yaw_joint", -2.5569, 2.5569, 20.0, 2.0},     // Left shoulder yaw
         {"left_elbow_joint", -2.4435, 0.0, 20.0, 2.0},               // Left elbow pitch
         {"left_wrist_roll_joint", -2.5569, 2.5569, 20.0, 2.0},       // Left elbow roll
         {"left_wrist_pitch_joint", -0.5585, 0.5585, 20.0, 2.0},      // Left wrist pitch
         {"left_wrist_yaw_joint", -1.5446, 1.5446, 20.0, 2.0},        // Left wrist yaw
                                                                      // Right arm joint configuration
         {"right_shoulder_pitch_joint", -2.5569, 2.5569, 20.0, 2.0},  // Right shoulder pitch
         {"right_shoulder_roll_joint", -3.3598, 0.06108, 20.0, 2.0},  // Right shoulder roll
         {"right_shoulder_yaw_joint", -2.5569, 2.5569, 20.0, 2.0},    // Right shoulder yaw
         {"right_elbow_joint", 0.0, 2.4435, 20.0, 2.0},               // Right elbow pitch
         {"right_wrist_roll_joint", -2.5569, 2.5569, 20.0, 2.0},      // Right elbow roll
         {"right_wrist_pitch_joint", -0.5585, 0.5585, 20.0, 2.0},     // Right wrist pitch
         {"right_wrist_yaw_joint", -1.5446, 1.5446, 20.0, 2.0},       // Right wrist yaw
     }},
    {JointArea::HEAD,
     {
         // Head joint configuration
         {"head_pitch_joint", -0.61087, 0.61087, 20.0, 2.0},  // Head pitch
         {"head_yaw_joint", -0.61087, 0.61087, 20.0, 2.0},    // Head yaw
     }},
};
