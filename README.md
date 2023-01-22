# arduino-cli-commands
## To list the available boards, you can use the following command:
```
arduino-cli board list
```
## List all the boards that are supported by the tool, regardless of whether they are currently connected to the computer or not.

**The command is:**
```
arduino-cli board listall
```
## The basic command for compiling a  ESP32 sketch is:
```
arduino-cli compile --fqbn esp32:esp32:esp32 <path/to/sketch.ino>
```
## To upload the compiled sketch to the connected ESP32 board, you can use the following command:
```
arduino-cli upload -p <port> --fqbn esp32:esp32:esp32 <path/to/sketch.ino>
```
# To get package for esp8266 or esp32 you need to configure home/.arduino15 file 
```
board_manager:
  additional_urls: [ https://arduino.esp8266.com/stable/package_esp8266com_index.json,
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
]
daemon:
  port: "50051"
directories:
  data: /home/lastvirus/.arduino15
  downloads: /home/lastvirus/.arduino15/staging
  user: /home/lastvirus/Arduino
library:
  enable_unsafe_install: true
logging:
  file: ""
  format: text
  level: info
metrics:
  addr: :9090
  enabled: true
output:
  no_color: false
sketch:
  always_export_binaries: false
updater:
  enable_notification: true
```
## To search for a library, use the following command:
```
arduino-cli lib search <library name>
```
For example, to search for the "WiFi" library, you would use the following command:
```arduino
arduino-cli lib search WiFi
```
## To install a library, you can use the following command:
```
arduino-cli lib install <library name>
```

