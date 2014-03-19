package main

import (
	"fmt"
	"net"
	"syscall"
	"os/exec"
	"time"
)

func main() {
	fmt.Println("Setting upp....")	
	adress, err := net.ResolveUDPAddr("udp", ":20021")
	checkError(err)
	
	listener, err := net.ListenUDP("udp", adress)
	checkError(err)
	
	number := 0
	buf := make([]byte, 1)
	
	fmt.Println("Backup mode...")
	
	for {
		listener.SetReadDeadline(time.Now().Add(2 * time.Second))
		_, _, err := listener.ReadFromUDP(buf)
		
		if nerr, ok := err.(net.Error); ok && nerr.Timeout() {
    		fmt.Println("I am master")
    		listener.Close()
    		cmd := exec.Command("gnome-terminal","-x","go","run","ov6.go")
			err := cmd.Start()
			checkError(err)
    		break
		}
		checkError(err)
		number = int(buf[0]) + 1
	}
	
	conn, err := net.Dial("udp", "127.0.0.1:20021")
	checkError(err)
	
	for {
		conn.Write([]byte(string(number)))
		fmt.Println(number)
		number++
		time.Sleep(500*time.Millisecond)
	}
}

func checkError(err error) {
	if err != nil {
		fmt.Println("Error: ", err)
		syscall.Exit(1)
	}
}
