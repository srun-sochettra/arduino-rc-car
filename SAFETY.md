# Hardware safety and limitations

This is a small coursework controller, not a safety-rated vehicle control system. Documentation changes do not add electrical protection or firmware failsafes.

## Most important limitation: movement persists

The sketch changes motor outputs only during setup or when it processes a command. It has no elapsed-time check, heartbeat, or connection-loss handler. After `F`, for example, an empty serial input buffer does not request a stop.

`S` and `D` request stop. Unrecognised characters also request stop. Speed and accessory no-ops preserve the current output. Do not rely on a Bluetooth disconnect or a closed controller application to stop the vehicle.

**Recommendation:** do not operate an unrestrained vehicle until an appropriate, verified loss-of-command strategy and independent way to remove motor power are in place.

## Electrical boundaries

The export contains no schematic or verified hardware specification. It does not establish supply voltages, motor current limits, logic-level compatibility, driver protection, enable configuration, or safe grounding and power distribution.

Before energising an assembly, verify its grounding/reference connections, supply isolation and distribution, and protection against faults using the actual component documentation. Do not copy the previous README's generic voltage and UART wiring claims as a circuit design. Motor power and digital control signals are different parts of the system; the four pin definitions specify only logical control outputs.

`setMotor` requests HIGH/LOW, LOW/HIGH, or LOW/LOW states. That is not proof of short-circuit prevention, safe direction reversal, electrical braking, or a driver's transient behaviour. The two output writes occur sequentially, and the sketch provides no deliberate reversal delay.

## Restrained verification checklist

Suggested checks, not completed tests:

- Inspect the real wiring, driver enable state, supply ratings, and protection before applying power.
- Start with motor power isolated and check the intended control signals.
- For powered tests, restrain the vehicle and keep wheels clear of the surface and people.
- Verify setup outputs, `S`, `D`, unknown characters, and every movement command.
- Verify that ignored characters preserve state and that CR/LF request stop.
- Check actual motor polarity rather than assuming a character name guarantees a turn direction.
- Observe loss of serial input under restraint; expect no software timeout in the current source.
- Verify any proposed failsafe and recovery behaviour separately before unrestricted operation.

These checks are not a complete electrical or mechanical safety assessment. Board compilation, a host-side logic test, and a successful upload each establish different things; none alone proves safe operation.
