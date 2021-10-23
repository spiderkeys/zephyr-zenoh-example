# Example Zenoh Zephyr Project
This project demonstrates how to create an idiomatic Zephyr application that integrates Zenoh-Pico as an external module.

#### TODO:
This guide expects a working Openthread setup as the networking interface Zenoh is being used over.
In the near future, this aspect will be simplified to support generic IP networking in addition to OT.

## Pre-Requisites

### Development PC

#### Zenoh (Rust) Setup
On your development PC:
- Build, install, and run a Zenoh Router (zenohd) and an example Zenoh publisher:
```bash
# Install Rust 1.55 or later (stable)
curl https://sh.rustup.rs -sSf | sh
        
# Clone repo
git clone https://github.com/eclipse-zenoh/zenoh
cd zenoh

# Build
cargo build -j3 --all-targets
```
- Next, use the IPv6:MeshLocalAddress value obtained from wpanctl status to start a zenohd listener in a terminal:
```bash
# Choose appropriate IP address
# Port 7474 chosen as an example; use whatever you like.
./target/debug/zenohd -l udp/fd10:9b50:100e:0:60df:9983:d08a:c29f:7474
```
- In another terminal, run a zn_pub instance:
```bash
./target/debug/examples/zn_pub -e udp/fd10:9b50:100e:0:60df:9983:d08a:c29f:7474
```

### MCU Setup

#### Zephyr Requirements
Zephyr libraries and tools must be downloaded/installed. Instructions can be found here:
- https://docs.zephyrproject.org/latest/getting_started/index.html

#### Application Development
Basic steps are:
- Create a Zephyr workspace using `west` to automatically pull this repo and all it's Zephyr dependencies from git
- Build the current example application
 - The IP address in main.c needs to be configured to match the IP of your wpan0 interface on your desktop
- Flash the application
- Monitor app activity through serial port
```bash
# Create Zephyr Workspace and pull repo:
west init -m https://https://github.com/spiderkeys/zephyr-zenoh-example --mr master zephyr_ws
cd zephyr_ws

# Build app
west build -p always -b nrf52840_mdk -s zephyr-zenoh-example/app

# Flash app
west flash

# Monitor over serial port (specify appropriate serial device path)
picocom -b 115200 /dev/ttyACM0
```
If everything works, you should see something like the following:
```
[00:00:00.346,099] <inf> ieee802154_nrf5: nRF5 802154 r*** Booting Zephyr OS build zephyr-v2.7.0  ***
adio initialized
[00:00:00.367,706] <inf> fs_nvs: 8 Sectors of 4096 bytes
[00:00:00.367,736] <inf> fs_nvs: alloc wra: 4, fe0
[00:00:00.367,736] <inf> fs_nvs: data wra: 4, 10
[00:00:00.384,857] <inf> net_l2_openthread: State changed! Flags: 0x101fc300 Current role: 0
[00:00:00.389,343] <inf> net_config: Initializing network
[00:00:00.389,373] <inf> app: Starting Openthread with config:
[00:00:00.389,373] <inf> app: Network Name: Zenoh-Net
[00:00:00.389,404] <inf> app: Channel: 24
[00:00:00.389,404] <inf> app: PANID: 50665
[00:00:00.389,404] <inf> app: XPANID: 10:9B:50:10:0E:62:0D:10
[00:00:00.389,404] <inf> app: Network Key: 00:01:02:03:04:05:06:07:08:09:0a:0b:0c:0d:0e:0f
[00:00:00.399,078] <inf> net_l2_openthread: State changed! Flags: 0x00000010 Current role: 0
[00:00:00.399,139] <inf> net_l2_openthread: State changed! Flags: 0x00080000 Current role: 0
[00:00:00.400,543] <inf> net_l2_openthread: State changed! Flags: 0x10000000 Current role: 0
[00:00:00.401,916] <inf> net_l2_openthread: State changed! Flags: 0x10000000 Current role: 0
[00:00:00.401,947] <inf> net_l2_openthread: OpenThread version: OPENTHREAD/5d706547e; Zephyr; Oct 22 2021 16:53:04
[00:00:00.403,472] <inf> net_l2_openthread: OpenThread already commissioned.
[00:00:00.411,071] <inf> net_l2_openthread: State changed! Flags: 0x0100103d Current role: 1
[00:00:01.481,781] <inf> net_l2_openthread: State changed! Flags: 0x10000040 Current role: 1
[00:00:02.729,156] <inf> net_l2_openthread: State changed! Flags: 0x200012a4 Current role: 2
[00:00:05.412,048] <inf> app: Connecting!
[00:00:05.442,016] <inf> app: Connected
[00:00:05.442,260] <inf> app: Started read task
[00:00:05.443,084] <inf> app: Awaiting data
[00:00:06.212,677] <inf> app: >> [Subscription listener] Received msg
[00:00:07.213,684] <inf> app: >> [Subscription listener] Received msg
[00:00:08.213,836] <inf> app: >> [Subscription listener] Received msg
```