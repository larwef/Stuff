#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "gecko_bglib.h"
#include "uart.h"

/*
This aplication uses the BGM111 WSTK. It is a simple BLE application with two characteristics.
One characteristic is used to turn an LED on and off.
The other has a value assigned to it which can be read by a connected device. This value is set
by pressing a key on the keyboard and then enter.
Notifications can be turned on for the last characteristic. Then a timer will be activated and
the value will be pushed periodically to the device.
*/

// For documentation of functions, refer to http://www.silabs.com/Support%20Documents/RegisteredDocs/AN915.pdf

// Named attribute handles from "gatt_db.h" from bgbuild.exe firmware compile process
#define gattdb_device_name                      3
#define gattdb_gpio_control                    11
#define gattdb_indication_control              13


BGLIB_DEFINE();

uint8_t* uart_port = "COM5";
uint32_t baud_rate = 115200;

// Char used for read and indicate characteristic
char ch = '0';
// Connection handle variable
uint8_t connection_handle = 0;

// Subscription state variable. (0=not subscribed to indications, 1=subscribed to indications)
uint8_t subscription_state = 0;

/**
 * Function called when a message needs to be written to the serial port.
 * @param msg_len Length of the message.
 * @param msg_data Message data, including the header.
 * @param data_len Optional variable data length.
 * @param data Optional variable data.
 */
static void on_message_send(uint16 msg_len, uint8* msg_data){
    /** Variable for storing function return values. */
    int ret;

    ret = uart_tx(msg_len, msg_data);
    if (ret < 0) {
        printf("on_message_send() - failed to write to serial port %s, ret: %d, errno: %d\n", uart_port, ret, errno);
        exit(EXIT_FAILURE);
    }
}
// Handles input for char
DWORD WINAPI handle_input(void* data){
	while (1){
		scanf_s(" %c", &ch);
		printf("Variable ch is now: %c\n\n", ch);
	}
	return 0;
}

int main(int argc, char* argv[]){
	// Setup
    struct gecko_cmd_packet *evt, *rsp;

    BGLIB_INITIALIZE(on_message_send, uart_rx);
    
    // Init Hardware
    if (uart_open(uart_port, baud_rate) < 0){
        printf("Hardware initialization failure, check serial port and baud rate values\n");
        exit(EXIT_FAILURE);
    }

    // Appliction start
	printf("Starting TTK8 demo app\n\n");
	printf("If device doesn't reset automatically, reset it manually\n");
	// Start thred for handling input
	HANDLE thread = CreateThread(NULL, 0, handle_input, NULL, 0, NULL);
	// Reset BGM111
	rsp = (struct gecko_cmd_packet *)gecko_cmd_system_reset(0);

	while (1){
		evt = gecko_wait_event(); // Blocking wait

        switch (BGLIB_MSG_ID(evt -> header)) {
        	// Reset/Boot
        	case gecko_evt_system_boot_id:
        		printf("Device reset\n");
        		// Set device name
        		rsp = (struct gecko_cmd_packet *)gecko_cmd_gatt_server_write_attribute_value(gattdb_device_name, 0, 13, "TTK8 BLE Demo");
        		// Start advertising
        		rsp = (struct gecko_cmd_packet *)gecko_cmd_le_gap_set_mode(le_gap_general_discoverable, le_gap_undirected_connectable);
        		printf("Waiting for connection...\n");
				printf("\n");
        	break;

        	case gecko_evt_le_connection_opened_id:
        		printf("Connected to %02X:%02X:%02X:%02X:%02X:%02X\n\n",
        			evt->data.evt_le_connection_opened.address.addr[5],
					evt->data.evt_le_connection_opened.address.addr[4],
					evt->data.evt_le_connection_opened.address.addr[3],
					evt->data.evt_le_connection_opened.address.addr[2],
					evt->data.evt_le_connection_opened.address.addr[1],
					evt->data.evt_le_connection_opened.address.addr[0]);
				connection_handle = evt->data.evt_le_connection_opened.connection;
        	break;

        	case gecko_evt_le_connection_closed_id:
        		printf("\nDisconnected\n");
        		rsp = (struct gecko_cmd_packet *)gecko_cmd_le_gap_set_mode(le_gap_general_discoverable, le_gap_undirected_connectable);
				// Makes sure timer is off when disconnecting
				rsp = (struct gecko_cmd_packet *)gecko_cmd_hardware_set_soft_timer(0, 0, 0);
        		printf("Waiting for connection...\n\n");
        	break;

			case gecko_evt_gatt_server_user_read_request_id:
				printf("Read request\n");
				if (evt->data.evt_gatt_server_user_read_request.characteristic == gattdb_indication_control){
					printf("Sending ( %c ) to conected device\n", ch);
					rsp = (struct gecko_cmd_packet *)gecko_cmd_gatt_server_send_user_read_response(
						evt->data.evt_gatt_server_user_read_request.connection,
						evt->data.evt_gatt_server_user_read_request.characteristic,
						0x00, /* SUCCESS */
						0x01, /* length */
						&ch);
					if (!rsp->data.rsp_gatt_server_send_user_write_response.result){
						printf("Read successful\n");
					}
					else {
						printf("Read not successful\n");
					}
				}
				else {
					printf("Something went wrong\n"); // Request for characteristic which doesn't exist(in this application)
				}
				printf("\n");
			break;

			case gecko_evt_gatt_server_user_write_request_id:
				if (evt->data.evt_gatt_server_user_read_request.characteristic == gattdb_gpio_control){
					printf("Write request\n");
					if (evt->data.evt_gatt_server_user_write_request.value.len == 1){
						if (evt->data.evt_gatt_server_user_write_request.value.data[0] == 0x01){
							rsp = (struct gecko_cmd_packet *)gecko_cmd_hardware_write_gpio(5, 0x40, 0x00);
							printf("Led turned ON\n");
						}
						else if (evt->data.evt_gatt_server_user_write_request.value.data[0] == 0x00){
							rsp = (struct gecko_cmd_packet *)gecko_cmd_hardware_write_gpio(5, 0x40, 0x40);
							printf("Led turned OFF\n");
						}
					}
					// Sends success message back(the device might excpect a response)
					rsp = (struct gecko_cmd_packet *)gecko_cmd_gatt_server_send_user_write_response(
						evt->data.evt_gatt_server_user_write_request.connection,
						evt->data.evt_gatt_server_user_write_request.characteristic,
						0x00 /* SUCCESS */);
				}
				else {
					printf("Something went wrong"); // Request for characteristic which doesn't exist(in this application)
				}
				printf("\n");
			break;

			case gecko_evt_gatt_server_characteristic_status_id:
				//printf("Connection trying to change subscription\n");
				if (evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_indication_control){
					// 1 means changed subscition, 2 means confirmation has been received.
					if (evt->data.evt_gatt_server_characteristic_status.status_flags == gatt_server_client_config){
						if (evt->data.evt_gatt_server_characteristic_status.client_config_flags & gatt_indication){
							subscription_state = 1;
							printf("Indication enabled\n");
							printf("Starting timer...");
							// Start timer, 205 is said to be 50ms. Not sure how to set the timer to the right interval. This does not result in 1s.
							rsp = (struct gecko_cmd_packet *)gecko_cmd_hardware_set_soft_timer(205*2*10, 0, 0);
							if (rsp){
								printf("Timer started\n");
							}
							else {
								printf("Timer not started\n");
							}
							printf("Sending ( %c ) to conected device (indication)\n", ch);
							rsp = (struct gecko_cmd_packet *)gecko_cmd_gatt_server_send_characteristic_notification(
								evt->data.evt_gatt_server_characteristic_status.connection,
								gattdb_indication_control,
								1,
								&ch);
						}
						else {
							subscription_state = 0;
							printf("Indication disabled\n");
							// Stop timer
							rsp = (struct gecko_cmd_packet *)gecko_cmd_hardware_set_soft_timer(0, 0, 0);
						}
					}
					else {
						//printf("Confirmed\n");
						break;
					}
				}
				else {
					printf("Something went wrong\n"); // Request for characteristic which doesn't exist(in this application)
				}
				printf("\n");
			break;

			// Most printfs are disabled so the console wont be flooded
			case gecko_evt_hardware_soft_timer_id:
				//printf("Timer event\n");
				// Checks if its from the right timer, handle assigned earlier
				if (evt->data.evt_hardware_soft_timer.handle == 0){
					// This should be true when the program gets here
					if (subscription_state){
						//printf("Sending ( %c ) to conected device (indication)\n", ch);
						rsp = (struct gecko_cmd_packet *)gecko_cmd_gatt_server_send_characteristic_notification(
							connection_handle,
							gattdb_indication_control,
							1,
							&ch);
					}
					else {
						printf("Something went wrong\n");
					}
				}
				else {
					printf("Something went wrong\n");
				}
			break;
		}
    }
    return 0;
}