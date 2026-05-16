# Arduino Obstacle Avoiding Robot 

A simple obstacle avoiding robot using:

- Arduino Uno R3
- L298N Motor Driver
- HC-SR04 Ultrasonic Sensor
- Servo Motor
- BO Motors

This robot:
- Moves forward normally
- Detects obstacles
- Scans left and right
- Chooses better path
- Remembers previous turns for a few seconds
- Avoids getting stuck in left-right loops

---

# Components Required

- Arduino Uno R3
- L298N Motor Driver
- HC-SR04 Ultrasonic Sensor
- Servo Motor (SG90 recommended)
- 2 BO Motors
- Robot Chassis
- Wheels
- Jumper Wires
- Battery Pack

---

# Wiring

## HC-SR04

| HC-SR04  | Arduino |
|--------- |---------|
| VCC      | 5v      |
| GND      | GND     |
| TRIG     | 10      |
| ECHO     | 11      |

---

## Servo Motor

| Servo | Arduino |
|------ |---------|
| Signal| 3       |
| VCC   | 5V      |
| GND   | GND     |

---

## L298N Motor Driver

| L298N | Arduino |
|---    |  -------|
| IN1   | 6       |
| IN2   | 7       |
| IN3   | 8       |
| IN4   | 9       |

---

## Motors

| Motor       | L298N       |
|-------------|-------------|
| Left Motor  | OUT1 + OUT2 |
| Right Motor | OUT3 + OUT4 |

---

# Power Connections

## Battery to L298N

| Battery  | L298N |
|---       |---    |
| Positive | 12V   |
| Negative | GND   |

---

# Important

All grounds MUST be connected together:

- Arduino GND
- L298N GND
- Servo GND
- Sensor GND
- Battery GND

Without common ground, the robot may behave randomly.

---

# Features

- Obstacle detection
- Left-right scanning
- Dead-end escape
- Simple memory system
- Automatic obstacle avoidance

---

# How Memory Works

The robot remembers the previous turn direction for 10 seconds.

Example:
- If robot recently turned LEFT
- It avoids instantly turning RIGHT again

This helps reduce:
- left-right loops
- getting stuck repeatedly
- obstacle ping-ponging

---

# Tips

## 1. Robot Moves Crooked

Cheap BO motors often rotate at slightly different speeds.

If robot moves left/right automatically:
- Use ENA/ENB PWM speed control
- Reduce speed of faster motor slightly

Example:

```cpp
analogWrite(ENA, 240);
```

---

## 2. Servo Not Moving

Possible reasons:
- weak battery
- wrong signal pin
- loose wiring
- not enough power

Try powering servo separately if needed.

---

## 3. Ultrasonic Sensor Gives Wrong Readings

Make sure:
- all grounds are connected
- sensor is mounted firmly
- no loose wires

---

## 4. Robot Hits Obstacles

Increase obstacle distance threshold.

Example:

```cpp
if(distance < 40)
```

instead of:

```cpp
if(distance < 20)
```

---

## 5. Robot Keeps Turning Forever

Increase:
- reverse delay
- turning delay

Small turns can trap the robot in loops.

---

# Future Improvements

Possible upgrades:
- IR side sensors
- Bluetooth control
- ESP32 camera
- Maze solving
- PID motor control
- Mapping and navigation
- Line following mode

---

# License

Free to use and modify.
