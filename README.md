
# ESP32 Racing Tank

This is my ESP32 based racing tank project made using an ESP32, FlySky FS-i6 transmitter and receiver, two BTS7960 motor drivers and two Johnson DC motors.

The tank uses a tracked/belt drive system, with one motor controlling each side. The ESP32 receives the control signals from the FS-i6 receiver and controls the left and right motors independently.

This allows the tank to move forward, backward, turn left and right, and also perform tank-style differential steering.

The project includes the CAD model, circuit connections, ESP32 code and the required setup to build and control the tank.

<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/3edc883a-2932-4535-95ff-ec60669f9fff" />

<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/ba45352c-04a1-4995-8dad-dfd3294adb78" />

<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/30ee5589-7f86-4ce0-ad7f-ee38c01ff3c2" />


## features

- ESP32 as the main controller
- FlySky FS-i6 transmitter
- FlySky receiver
- Two BTS7960 motor drivers
- Two Johnson DC motors
- Tank/belt drive system
- Independent left and right motor control
- Differential steering
- Forward and backward movement
- Left and right turning
- Variable motor speed
- Wireless RC control
- CAD model included

## BOM – bill of materials

| component | quantity | purpose |
|-----------|:--------:|---------|
| ESP32 development board | 1 | main controller |
| FlySky FS-i6 transmitter | 1 | wireless controller |
| FlySky receiver | 1 | receives transmitter signals |
| BTS7960 motor driver | 2 | controls the motors |
| Johnson DC motor | 2 | drives the left and right tracks |
| Tank/belt tracks | 2 | robot movement |
| Motor battery | 1 | powers the motors |
| 5V buck converter | 1 | powers the control electronics |
| jumper wires | as required | connections |
| 3D printed parts | as required | tank body and mounts |

## circuit connections

<img width="665" height="462" alt="image" src="https://github.com/user-attachments/assets/5c86d090-9339-448b-9809-868dd8464483" />

circuit diagram : https://app.cirkitdesigner.com/project/9e32e160-422e-4076-8aea-6d43e6693b43

The ESP32 receives the throttle and steering signals from the FlySky receiver.

The two BTS7960 motor drivers are used independently. One driver controls the left motor and the other controls the right motor.

### FS-iA6B receiver to ESP32

| FS-iA6B | ESP32 |
|----------|-------|
| CH1 | GPIO 18 |
| CH2 | GPIO 19 |
| VCC | 5V |
| GND | GND |

CH1 is used for steering and CH2 is used for throttle.

### Left BTS7960 to ESP32

| BTS7960 | ESP32 |
|----------|-------|
| RPWM | GPIO 25 |
| LPWM | GPIO 26 |
| R_EN | 5V |
| L_EN | 5V |
| VCC | 5V |
| GND | GND |

### Right BTS7960 to ESP32

| BTS7960 | ESP32 |
|----------|-------|
| RPWM | GPIO 27 |
| LPWM | GPIO 14 |
| R_EN | 5V |
| L_EN | 5V |
| VCC | 5V |
| GND | GND |

The R_IS and L_IS pins of both BTS7960 modules are not used.

### motors

| BTS7960 | motor |
|---------|-------|
| M+ / M- | left Johnson motor |
| M+ / M- | right Johnson motor |

One BTS7960 is used for the left motor and the other BTS7960 is used for the right motor.

If a motor rotates in the wrong direction, swap its motor wires or reverse the motor direction in the code.

## power connections

The motors are powered directly from the motor battery through the BTS7960 motor drivers.

The ESP32, receiver and BTS7960 logic are powered using a regulated 5V supply.

```text
Motor battery (+)
       |
       ├── Left BTS7960 B+
       |
       └── Right BTS7960 B+

Motor battery (-)
       |
       ├── Left BTS7960 B-
       |
       └── Right BTS7960 B-

5V buck converter
       |
       ├── ESP32 5V
       ├── Receiver VCC
       ├── Left BTS7960 VCC
       └── Right BTS7960 VCC
```

All grounds must be connected together.

```text
ESP32 GND
   |
   ├── Receiver GND
   ├── Left BTS7960 GND
   └── Right BTS7960 GND
```

Do not power the motors from the ESP32.

The BTS7960 motor power terminals and logic VCC are separate. The motor battery is connected to B+ and B-, while VCC is supplied with regulated 5V.

## how to build this

**step 1:** Get all the required components mentioned in the BOM.

**step 2:** Print or prepare the tank body using the CAD model included in this repository.

**step 3:** Mount the two Johnson motors and the track/belt mechanism on the chassis.

**step 4:** Install the left and right tracks and make sure they can move freely.

**step 5:** Mount the two BTS7960 motor drivers on the chassis.

**step 6:** Connect the left motor to the left BTS7960 and the right motor to the right BTS7960.

**step 7:** Connect the FS-iA6B receiver to the ESP32.

**step 8:** Connect the PWM and direction pins of both BTS7960 drivers to the ESP32.

**step 9:** Connect the motor battery and 5V buck converter according to the power connection diagram.

**step 10:** Make sure all grounds are connected together.

**step 11:** Bind the FS-i6 transmitter with the receiver.

**step 12:** Upload the ESP32 code.

**step 13:** Test the motor directions at low speed before running the tank at full speed.

## How the tank works????

The working of the tank is based on differential drive.

```text
FS-i6 transmitter
        ↓
FS-iA6B receiver
        ↓
ESP32
        ↓
Reads throttle + steering
        ↓
Motor mixing
        ↓
 ┌───────────────┐
 ↓               ↓
Left BTS7960   Right BTS7960
 ↓               ↓
Left motor     Right motor
 ↓               ↓
Left track     Right track
```

The receiver sends the throttle and steering values to the ESP32.

The ESP32 converts these values into left and right motor speeds.

The basic mixer is:

```text
Left motor  = Throttle + Steering
Right motor = Throttle - Steering
```

For example, when the throttle stick is pushed forward, both motors move forward.

When steering is applied, the speed of one motor is reduced while the other motor continues moving faster. This makes the tank turn.

The tank can also rotate in place by running the two tracks in opposite directions.

## motor mixing

The tank uses differential steering.

```text
Forward

Left track   →→→
Right track  →→→
```

```text
Backward

Left track   ←←←
Right track  ←←←
```

```text
Turn left

Left track   ←
Right track  →
```

```text
Turn right

Left track   →
Right track  ←
```

The exact motor direction depends on how the motors are physically mounted and connected.

If one side is moving in the opposite direction, swap the motor wires or invert that motor direction in the code.

## RC control

The FlySky FS-i6 is used as the wireless controller.

The receiver provides PWM signals to the ESP32.

```text
FS-i6
  ↓
Wireless signal
  ↓
FS-iA6B receiver
  ↓
CH1 + CH2
  ↓
ESP32
```

CH1 is used for steering and CH2 is used for throttle.

The ESP32 reads the pulse width from each channel and converts it into a motor control value.

The center value is approximately 1500 µs.

```text
1000 µs  → maximum one direction
1500 µs  → center / stop
2000 µs  → maximum opposite direction
```

The exact values can vary slightly depending on the transmitter and receiver settings.

## speed control

The ESP32 uses PWM to control the speed of the BTS7960 motor drivers.

The throttle determines the overall speed of the tank, while steering changes the speed difference between the two tracks.

The maximum speed can be limited in the code if the tank is too fast.

It is recommended to start with a lower speed and increase it gradually.

## Testing

Before driving the complete tank, test each part separately.

### 1. Receiver test

Check the CH1 and CH2 values in the serial monitor.

Move the FS-i6 sticks and make sure the values change correctly.

### 2. Left motor test

Test the left BTS7960 and left motor independently.

Check:

- forward direction
- backward direction
- speed control
- motor stopping

### 3. Right motor test

Repeat the same test for the right motor.

### 4. Differential drive test

After both motors work correctly, test:

- forward
- backward
- left
- right
- rotate left
- rotate right
- stop

Start with the tank lifted off the ground for the first motor test.

## CAD model

<img width="1200" height="805" alt="Screenshot 2026-09-23 at 9 23 01 PM" src="https://github.com/user-attachments/assets/c722c1a5-b56d-484d-b7c1-84de53899c71" />

<img width="1001" height="700" alt="image" src="https://github.com/user-attachments/assets/c5b48d2f-895f-4297-8115-5cc2050dc7e9" />

The CAD model contains the tank chassis, motor mounts, track system and mounting locations for the electronics.

The design can be modified depending on the motor size, battery and track dimensions.

## Things to keep in mind

1. All grounds should be connected together.
2. Do not power the motors from the ESP32.
3. Use a suitable battery for the Johnson motors.
4. Use a regulated 5V supply for the ESP32, receiver and BTS7960 logic.
5. Check both motor directions before installing the tracks.
6. Make sure the tracks can move freely.
7. Test the receiver before testing the motors.
8. Start with a low motor speed.
9. Keep the motor battery wiring thick enough for the motor current.
10. Make sure the BTS7960 modules have proper airflow.
11. Check the transmitter failsafe before driving the tank.
12. Stop the tank immediately if a motor or driver becomes excessively hot.
13. Make sure the battery voltage is suitable for the motors and BTS7960.
14. Secure the battery properly so it does not move while the tank is driving.

## Final result

This project was made to build a wireless RC racing tank using an ESP32 and a tracked drive system.

The two motors independently control the left and right tracks, allowing the tank to use differential steering. The FS-i6 provides wireless control while the ESP32 handles the receiver signals, motor mixing and speed control.

The main idea is simple:

```text
FS-i6
  ↓
Receiver
  ↓
ESP32
  ↓
Motor mixing
  ↓
2 × BTS7960
  ↓
2 × Johnson motors
  ↓
Left + right tracks
  ↓
Racing tank
```

## Demo

https://drive.google.com/file/d/1SPlf28peBSgvbxt1lPk7T9hTLhPETCV-/view?usp=sharing

This video shows the tank fully assembled and being controlled using the FS-i6 transmitter.

One correction from the earlier wiring: **R_EN and L_EN should not be treated as ESP32 3.3V outputs if your BTS7960 board requires 5V logic.** For in my case I've kept them at the regulated **5V** logic supply.
