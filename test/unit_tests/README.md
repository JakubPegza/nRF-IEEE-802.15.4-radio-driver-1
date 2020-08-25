# Unit tests

## Dependencies
To run unit tests following dependencies are required

### Tools
* ceedling v0.30.0

### Packages
* nrfx
* nrf-802154-sl

## Quick start
Call following command in the main directory of this repo:
```
$ SL_PATH=~/git/nrf-802.15.4-sl NRFX_PATH=~/git/nrfx ceedling options:nrf52840 test:all
```
Replace paths stored in `SL_PATH` and `NRFX_PATH` with paths to actual packages present in your filesystem.

### Options
Exactly one option must be used to run unit tests. Options are used to run unit tests for selected chip version. Available options are:
* `options:nrf52840`
* `options:nrf52833`
* `options:nrf52820`
* `options:nrf52811`
