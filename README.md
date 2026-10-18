# Transporter ZMK Module

This is the ZMK module for the Transporter, a 51-key row-staggered keyboard with an on-board CH32X035 (USB-C, wired only).

It needs [zmk-wch](https://github.com/carrefinho/zmk-wch) for the CH32X035 support, and builds on ZMK's Zephyr 4.1 version.

> [!NOTE]
>
> ZMK Studio is not supported. It doesn't fit in the chip's 62 KB of flash alongside the rest of the firmware.

# Usage

This repo builds its own firmware in GitHub Actions; download `firmware.zip` from the latest run. To build from your own `zmk-config` instead, add these lines to `config/west.yml`:

```yaml
manifest:
  remotes:
    - name: zmkfirmware
      url-base: https://github.com/zmkfirmware
    - name: carrefinho                            # <---
      url-base: https://github.com/carrefinho     # <---
  projects:
    - name: zmk
      remote: zmkfirmware
      revision: 4dd95d7840eb3d5a3f59bb29fbf1ab054715ef85  # Zephyr 4.1
      import: app/west.yml
    - name: zmk-wch                               # <---
      remote: carrefinho                          # <---
      revision: main                              # <---
    - name: transporter-zmk-module                # <---
      remote: carrefinho                          # <---
      revision: main                              # <---
  self:
    path: config
```

Add the board to your `build.yaml`. The `toolchain` line selects the RISC-V build image:

```yaml
---
include:
  - board: transporter/ch32x035/zmk
    toolchain: riscv64
```

Then point `.github/workflows/build.yml` at the zmk-wch workflow, which knows about `toolchain`:

```yaml
on: [push, pull_request, workflow_dispatch]

jobs:
  build:
    uses: carrefinho/zmk-wch/.github/workflows/build-user-config.yml@main
```

The default keymap is in [`boards/carrefinho/transporter/transporter.keymap`](boards/carrefinho/transporter/transporter.keymap). Copy it to `config/transporter.keymap` in your `zmk-config` to customize it.

# Flashing

The firmware is a `.bin` file. Hold Raise and press right Shift to enter the WCH bootloader, then flash it with [wchisp](https://github.com/ch32-rs/wchisp):

```sh
wchisp flash transporter_ch32x035_zmk-zmk.bin
```

The LED shows Caps Lock. Esc is Escape on tap and Caps Lock on hold.
