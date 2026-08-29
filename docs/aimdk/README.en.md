# QuickStart of AgiBot X2 AimDK

## Documentation

The docs for secondary development are published in 2 modes:
- [Local Docs](docs/cn/_build/html) - static, distributed with this SDK package.
- [Online Docs](https://x2-aimdk.agibot.com) - dynamic, always up to date.

### Local Docs Usage

To access local docs (assuming port 5789 is available):

1. Start a local webserver:

```bash
sh ./run_docs.sh 5789
```

2. Then visit <http://127.0.0.1:5789> in your browser

**Note: up-to-date online docs are always preferred**

### Online Docs Usage (recommended)

Please visit <https://x2-aimdk.agibot.com> in your browser and select
the docs with matching version


## AimDK interfaces & examples

Please refer to the docs.

## Non-volatile User Data

The disks in the robot would be reformatted during firmware upgrade/downgrade.

To make your data survive:
1. Put your data under `$HOME`(/agibot/data/home/agi), where data are non-volatile by default, except:
   + DO NOT save data into `$HOME/aimdk*`, these are reserved and maintained by the system.
   + All data under `$HOME` would be moved to `$HOME/.old_agi_home.bak` (**specific to v1.0 firmware flashing**)
   + BE CAREFUL of features like factory reset, which would force erasing all data.
2. Backup is always recommended, at least before firmware upgrade/downgrade
