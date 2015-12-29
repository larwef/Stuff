package main

import (
	"fmt"
	"time"
	"syscall"
	"./sendlist"
	"./queue"
)

var orders []queue.Order
var orders1 []queue.Order
var orders2 []queue.Order
var orders3 []queue.Order

func main() {
	fmt.Println("Choose mode:")
	fmt.Println("Sender: s")
	fmt.Println("Reciever: r")

	var mode string
    _, err := fmt.Scanln(&mode)
    checkError(err)

    for mode != "s" && mode != "r" {
    	fmt.Println("Invalid input")
    	_, err := fmt.Scanln(&mode)
    	checkError(err)
    }
    // Sender Mode
    if mode == "s" {
    	fmt.Println("In sender mode...")

    	orders1 = []queue.Order{
    	queue.Order{1,1,1},
    	queue.Order{2,2,2},
    	queue.Order{3,3,3},
    	queue.Order{4,4,4},
    	queue.Order{5,5,5},
    	queue.Order{6,6,6},
    	queue.Order{7,7,7}}

    	orders2 = []queue.Order{}

    	orders3 = []queue.Order{
    	queue.Order{1,1,1},
    	queue.Order{2,2,2},
    	queue.Order{3,3,3},
    	queue.Order{4,4,4}}

    	for {
    		sendlist.UDPSendList(orders1, "192.168.1.182")
    		time.Sleep(100*time.Millisecond)
    	}
    }

    //Reciever Mode
    if mode == "r" {
    	fmt.Println("In reciever mode...")
    	for {
    		temp := sendlist.UDPRecieveList()
    		if temp != nil {
    			orders = temp
    		}
    		fmt.Println("List: ", orders)
    	}
    }
}

func checkError(err error) {
	if err != nil {
    	fmt.Println("Error: ", err)
    	syscall.Exit(1)
    }
}