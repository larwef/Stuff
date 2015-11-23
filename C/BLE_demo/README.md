Bluetooth Low Energy demo used in the course TTK8.

Both are using the BGM111 Wireless Starter Kit.

One is using a Windows computer as host over USB. The project file is from Visual Studio Ultimate 2013.

The other is using a Raspberry Pi (model B rev 2) as host. Using the wiring pi library.

The application has one loop handling input from keyboard, and one main loop dealing with the communicationg with the BGM module. The BLE application has one user made sevice with two characteristics. One of them is a writable characteristic controlling a LED (1 on, 0 off). The other is a readable characteristic, also with notification, where the last character typed by the keyboard can be read.

After pressing a key, enter has to be pressed. Confirmation that the ch variable has been changed will be displayed.
