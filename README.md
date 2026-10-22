# Arduino RC Car

**A compact serial-command controller for a two-motor RC car.**

This Arduino sketch maps single-character commands to forward, reverse, and stop states for two motor-driver channels. It uses four digital outputs and the board's `Serial` interface at 9600 baud. A compatible serial Bluetooth module can provide the command transport; the sketch itself does not implement Bluetooth pairing or a wireless protocol.

Originally documented as an Arduino Programming coursework project. The repository focuses on the firmware rather than a complete, verified hardware kit.

> **Important:** there is no command timeout or disconnect failsafe. If input stops after a movement command, the last motor output remains set. Read [hardware safety and limitations](SAFETY.md) before powering a vehicle.

## What is implemented

- Independent forward, reverse, and stop output states for the left and right channels.
- Forward/reverse driving and single-motor steering commands.
- Stop commands and a stop response for unrecognised characters.
- Compatibility no-ops for speed and accessory command characters.
- Stopped outputs during `setup()`.
- No external library includes beyond `Arduino.h`.

There is no PWM speed control, autonomous navigation, obstacle detection, telemetry, authentication, or Bluetooth configuration in the supplied sketch.

## Control flow

```text
Serial input at 9600 baud
          |
      handle(char)
          |
   drive(left, right)
          |
   setMotor(a, b, direction)
          |
   Four digital control outputs
          |
   External motor driver and motors
```

## Output mapping

These are Arduino digital pin numbers, not physical package-pin numbers or motor-driver terminal numbers.

| Symbol | Digital pin | Logical role |
| --- | --- | --- |
| `L1` | 13 | Left channel forward input |
| `L2` | 12 | Left channel reverse input |
| `R1` | 11 | Right channel forward input |
| `R2` | 10 | Right channel reverse input |

For each channel, the sketch writes:

| Requested state | First input | Second input |
| --- | --- | --- |
| `FWD` | HIGH | LOW |
| `REV` | LOW | HIGH |
| `STOP` | LOW | LOW |

`STOP` describes the requested input pattern, not a verified braking mode. Electrical behaviour depends on the actual driver, enable configuration, wiring, and load. No driver enable pins are managed by this sketch.

## Command protocol

Commands are case-sensitive single characters. The table records exact channel states; physical steering direction depends on assembly and motor polarity.

| Character | Left channel | Right channel | Behaviour |
| --- | --- | --- | --- |
| `F` | FWD | FWD | Both channels forward |
| `B` | REV | REV | Both channels reverse |
| `L` | STOP | FWD | Right channel only, forward |
| `R` | FWD | STOP | Left channel only, forward |
| `G` | FWD | STOP | Same output as `R` |
| `I` | STOP | FWD | Same output as `L` |
| `H` | REV | STOP | Left channel only, reverse |
| `J` | STOP | REV | Right channel only, reverse |
| `S`, `D` | STOP | STOP | Stop both channels |
| `0`–`9`, `q` | Unchanged | Unchanged | Speed characters ignored |
| `W`, `w`, `U`, `u`, `V`, `v`, `X`, `x` | Unchanged | Unchanged | Accessory characters ignored |
| Any other character | STOP | STOP | Default stop |

Ignored commands do **not** stop an already moving car. Uppercase `Q` is not the lowercase `q` speed no-op; it reaches the default stop case.

### Serial line endings matter

Carriage return and newline are unrecognised characters, so either requests a stop. When testing single movement commands in a serial monitor, select **No line ending**. Sending `F` followed by a newline requests forward and then stop, which can look like an unresponsive controller.

The loop drains all available bytes in order. There is no acknowledgement message or status output.

## Opening and uploading

The supplied source is [RC_Car.ino](RC_Car.ino). Arduino requires the primary `.ino` filename to match its sketch folder. For local use, keep a working copy at:

```text
RC_Car/
  RC_Car.ino
```

This local sketch folder is independent of the recommended GitHub repository name, `arduino-rc-car`. The documentation refresh does not move or rename the source file.

1. Prepare the matching sketch folder and open `RC_Car.ino` in Arduino IDE.
2. Select the board/core and port for your actual hardware. No specific board or core version is verified by this repository.
3. Verify/compile before uploading. Keep motor power isolated during initial upload and inspection.
4. Upload, then test the serial protocol at 9600 baud with the vehicle restrained and wheels clear of the surface.
5. Confirm explicit stop behaviour and every channel direction before any floor test.

If external hardware shares the board's upload serial interface, consult that board and module's documentation before connecting or disconnecting it. The repository does not establish universal UART pins, supply voltages, pairing codes, or a guaranteed upload-error cause.

[Arduino sketch-folder specification](https://docs.arduino.cc/arduino-cli/sketch-specification/)

## Hardware scope

The previous README named Uno/Nano boards, HC-05/HC-06 modules, and L298N/L293D drivers as possible components. The export contains no schematic, bill of materials, board configuration, or hardware test evidence to establish an exact compatible assembly.

Use the actual board, driver, module, motor, and power-supply documentation to determine wiring, logic levels, enable inputs, protection, and ratings. Do not treat this README as a wiring schematic. See [SAFETY.md](SAFETY.md).

## Repository contents

| File | Purpose |
| --- | --- |
| [RC_Car.ino](RC_Car.ino) | Firmware and command dispatch |
| [SAFETY.md](SAFETY.md) | Hardware boundaries and missing failsafe |
| [CONTRIBUTING.md](CONTRIBUTING.md) | Focused changes and verification expectations |
| [SECURITY.md](SECURITY.md) | Security reporting and control boundary |

## Verification status

The documentation was checked against the supplied sketch. This refresh did not compile firmware, upload to a board, or test motors, Bluetooth, wiring, or power-loss behaviour. Source inspection is not hardware validation.

## Licence

No licence file is present in the supplied repository. The previous educational-use statement does not specify a complete licence. This refresh does not assign a licence or invent permissions; the owner should choose one explicitly before advertising reuse terms.
