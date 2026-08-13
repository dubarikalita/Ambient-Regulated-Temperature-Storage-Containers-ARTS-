# Ambient-Regulated Temperature Storage Containers (ARTS)

An Arduino-based **automatic temperature control system** designed for real-time temperature monitoring and regulation. The system uses an NTC temperature sensor to measure temperature, PWM-based fan control for temperature regulation, an LCD for displaying system information, and push buttons for adjusting the desired temperature.

## Project Overview

The system continuously monitors the temperature and automatically adjusts the fan speed according to the measured temperature and user-defined target temperature.

Users can increase or decrease the target temperature using the **UP** and **DOWN** buttons and confirm the setting using the **SET** button. A buzzer provides an alert when the temperature reaches a critical level.

The project was implemented and tested as an **Arduino-based simulation using Wokwi**, eliminating the need for physical hardware during development and testing.

## Features

- Real-time temperature monitoring using an **NTC thermistor**
- Automatic **PWM-based fan-speed control**
- Real-time temperature and fan-speed display on a **16×2 LCD**
- User-controlled temperature adjustment using **UP/DOWN buttons**
- **SET button** for confirming the desired temperature
- High-temperature warning using a **buzzer**
- LED-based fan-speed indication in the simulation
- Fully simulated using **Wokwi**

## System Architecture

```text
          NTC Temperature Sensor
                   │
                   ▼
              Arduino UNO
                   │
        ┌──────────┼──────────┐
        │          │          │
        ▼          ▼          ▼
      LCD       PWM Fan     Buzzer
    Display     Control      Alert
                   │
                   ▼
              Temperature
                Regulation

       UP / DOWN / SET Buttons
                   │
                   ▼
              Arduino UNO
