# Security policy

This repository contains an Arduino serial-command sketch. It does not implement a network service, authentication, encryption, sender validation, or a supported-release programme. No response deadline or continuous security monitoring is promised.

## Control boundary

The firmware processes bytes arriving through `Serial` without identifying their sender. If a Bluetooth or other transport is attached, its pairing, access controls, and configuration are outside this sketch. Do not describe the firmware as authenticated or secure merely because a module supports pairing.

The missing loss-of-command failsafe is documented in [SAFETY.md](SAFETY.md). A transport disconnect is not a firmware stop command.

## Reporting a concern

Do not publish credentials, private device details, or actionable exploit details affecting someone else's setup in an issue.

For a sensitive report, request a private contact from the repository owner without posting the details. No dedicated reporting email or private reporting feature is confirmed by the supplied repository. For a non-sensitive firmware defect, an issue with a minimal reproduction is appropriate.

Include the affected commit, exact board/core and transport where relevant, command sequence, expected and observed behaviour, and redacted evidence. Test only equipment you control or have permission to test, with the vehicle restrained and a means to remove motor power.

This document is a reporting guide, not a security certification or a remediation of the current firmware's limitations.
