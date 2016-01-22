Bluetooth Low Energy Application based on the Nordic ble_app_template project.
An nRF51 Development kit was used.

Bluetooth Developer Studio was used to make a custom service with two characteristics.
https://www.bluetooth.com/~/media/developer-studio/index
Link to the nRF plugin needed to generate the code:
https://developer.nordicsemi.com/nRF51_bluetooth_development_studio_plugin/

One of the characteristics are write only, and controls LED2 on the kit.
Write 1(0x01) to turn it on, or 0(0x00) to turn it off.

The other charateristic is read and notification.
The characteristic has one value, the value can be toggled by pressing BUTTON2 on the kit. The value alternates beween 0 and 1 when teh button is pressed. 

The application can be tested using a smartphone wit the nRF Master Control Panel app.
https://www.nordicsemi.com/eng/Products/Nordic-mobile-Apps/nRF-Master-Control-Panel-application