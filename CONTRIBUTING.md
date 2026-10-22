# Contributing

Keep changes small and appropriate to a single-sketch RC-car controller. Read the [README](README.md) and [safety notes](SAFETY.md) first. Use the [security policy](SECURITY.md) for sensitive concerns.

## Before changing firmware

Describe the problem and identify the affected command or output transition. Preserve the existing command mapping unless a deliberate protocol change is requested. Do not rename steering commands based on assumptions about physical motor polarity.

Do not add a Bluetooth library, dependency, or framework when the existing serial interface is sufficient. Changes involving PWM, reversal timing, driver enable pins, or failsafes need explicit hardware assumptions and a verification plan.

## Verification

No build configuration, pinned board/core, automated test suite, or hardware test record is included in the supplied export. Report your actual board, core version, tooling, and checks rather than claiming universal compatibility.

For a firmware change:

1. Compile for the actual target board and report the result.
2. Check each movement command, both explicit stops, default stop, speed no-ops, and accessory no-ops.
3. Check command sequences, CR/LF handling, and absence of new input.
4. Test changed physical behaviour only with the vehicle restrained and an independent way to remove motor power.
5. For a timeout change, verify its trigger, timing, stop output, and recovery after fresh commands. Do not call it a disconnect detector unless that behaviour is actually established.

Distinguish source review, host-side logic tests, board compilation, upload, and powered hardware testing. Only claim checks actually performed.

## Pull requests

Explain the problem, focused change, compatibility impact, checks run, and remaining gaps. Include a wiring diagram and component references when proposing hardware-specific guidance. Avoid unrelated formatting or documentation churn.

No licence is added by these contribution guidelines. The owner must establish the project's licence explicitly.
