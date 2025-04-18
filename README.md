# PUMA Robot Simulation

An interactive robotic arm simulation based on the **PUMA** (Programmable Universal Machine for Assembly) architecture, written in **C++** using **Raylib** for real-time 3D visualization. The simulation focuses on solving and visualizing **inverse kinematics**, allowing users to set a target and observe the robot dynamically adjusting its joints to reach it.

---

## Simulation Overview

- Developed in **C++** using the **Raylib** graphics library
- Simulates a 6-DOF PUMA robotic arm
- Calculates joint configurations using **inverse kinematics**
- Features a **movable target sphere** as the end-effector goal
- Real-time 3D rendering of the robot and its motion

---

## Features

- **Inverse Kinematics**  
  Computes joint angles to reach a user-defined 3D target

- **Real-Time Visualization**  
  Rendered with **Raylib** in a 3D environment

- **Movable Target**  
  Set a new position by interacting with the target sphere — the robot adapts instantly

- **Modular Design**  
  Each part of the robot (joints, arms) is represented as a separate class

- **Test Suite**  
  Includes validation tests for inverse kinematics math

---

## GUI Layout

- **Main window** renders the 3D robotic arm
- **Target sphere** can be repositioned (e.g., mouse drag or keyboard input)
- The robot attempts to match the sphere’s position with its end effector
- Joint rotations update in real time as part of IK solution

---

## How to Run

### Requirements

- C++17-compatible compiler (Visual Studio recommended)
- [Raylib](https://www.raylib.com/) installed and linked (v4.0+)
