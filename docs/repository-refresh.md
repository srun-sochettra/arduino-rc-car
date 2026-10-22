# Repository refresh

## Recommended identity

- Current repository slug: `arp-rc-car`.
- Recommended slug: `arduino-rc-car`.
- Display name: **Arduino RC Car**.
- Suggested description: **Arduino firmware for a two-motor RC car, with single-character serial commands and four digital motor-driver outputs.**
- Suggested topics: `arduino`, `cpp`, `embedded`, `robotics`, `rc-car`, `serial`.

This is a naming recommendation, not a completed GitHub rename. The course acronym is less descriptive to an outside reader than the platform name. No repository settings, remotes, topics, or descriptions were changed.

## Apply the files

Extract the ZIP into the existing repository root, replacing README.md and adding the other documentation files. Keep RC_Car.ino, Git history, and any local files. This is a documentation overlay, not a complete repository replacement.

The source file is deliberately not renamed or moved. For Arduino IDE use, the primary sketch filename must match its sketch folder; use a local RC_Car/RC_Car.ino working copy as described in the README.

If adopting the recommended remote name, rename the repository in GitHub's repository settings and update existing clones to the new clone URL. Review any external links or integrations. This archive does not perform that action.

[GitHub repository-renaming documentation](https://docs.github.com/en/repositories/creating-and-managing-repositories/renaming-a-repository)

[Arduino sketch-folder specification](https://docs.arduino.cc/arduino-cli/sketch-specification/)

## Editorial changes

The README now leads with the actual controller behaviour rather than unsupported performance claims. It records exact channel states, ignored commands, line-ending behaviour, and the distinction between serial firmware and an external Bluetooth transport.

The refresh removes the incorrect timeout claim, universal wiring/voltage/pairing instructions, guaranteed upload-error claim, and short-circuit-prevention claim. No schematic or hardware test evidence was supplied to support those statements. No licence, author attribution, performance result, or hardware compatibility guarantee has been invented.

No generic community code of conduct, CI workflow, dependency manifest, or release history was added: they would not improve this small documentation task without further requirements.

## Verification and recovery

Both supplied text files were inspected. Documentation links and command mappings were checked against the sketch; ZIP integrity and source exclusion were checked. The firmware is not included in the overlay and remains unchanged.

No Arduino compilation, upload, serial-device test, Bluetooth test, or powered hardware test was performed. No safety or security fix is claimed. To undo this refresh, restore the original README and remove the newly added documentation files using version control.
