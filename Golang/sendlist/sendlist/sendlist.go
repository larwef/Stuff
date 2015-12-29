package sendlist

import (
	"fmt"
	"syscall"
	"net"
	"time"
	"strings"
	"strconv"
	"../queue"
)

var port = "50030"

func UDPSendList(list []queue.Order, adress string) {
	conn := InitUDPConnection(adress, port)
	conn.Write([]byte("start"))
	length := len(list)
	conn.Write([]byte(strconv.Itoa(length)))
	for _, y := range list {
		msg := strconv.Itoa(y.OrderFloor) + "." + strconv.Itoa(y.OrderType) + "." + strconv.Itoa(y.OrderDir)
		conn.Write([]byte(msg))
		time.Sleep(10*time.Millisecond)
	}
	conn.Close()
}

func UDPRecieveList() ([]queue.Order){
	tempList := make([]queue.Order, 0)
	listener := InitUDPListener(port)
	buf := make([]byte, 1024)
	n, _, _ := listener.ReadFromUDP(buf)
	cmp := strings.Trim(string(buf[:n]), "\x00")
	if cmp == "start" {
		n, _, _ := listener.ReadFromUDP(buf)
		length, _ := strconv.Atoi(string(buf[:n]))
		for i := 0; i < length; i++ {
			n, _, _ := listener.ReadFromUDP(buf)
			cmp := strings.Trim(string(buf[:n]), "\x00")
				if cmp == "start" {
					listener.Close()
					return nil
				}
			orderElements := strings.Split(string(buf[:n]), ".")
			element1, _ := strconv.Atoi(orderElements[0])
			element2, _ := strconv.Atoi(orderElements[1])
			element3, _ := strconv.Atoi(orderElements[2])
			order := queue.Order{element1, element2, element3}
			tempList = append(tempList, order)
		}
		if len(tempList) != length {
			listener.Close()
			return nil
		}
	} else {
		listener.Close()
		return nil
	}
	listener.Close()
	//fmt.Println("Temp: ",tempList)
	return tempList
}

//Hjelpefunksjoner
func InitUDPConnection(IP string, port string) (net.Conn){
	destination := IP + ":" + port
	connection, err := net.Dial("udp", destination)
	if err != nil {
		fmt.Println("Error originating in InitUDPConnection")
		syscall.Exit(1)
	}
	
	return connection
}

func InitUDPListener(port string) (*net.UDPConn){
	adress, err := net.ResolveUDPAddr("udp", ":" + port)
	listener, err := net.ListenUDP("udp", adress)
	if err != nil {
		fmt.Println("Error originating in InitUDPListener", err)
		syscall.Exit(1)
	}
	
	return listener
}

func checkError(err error) {
	if err != nil {
    	fmt.Println("Error: ", err)
    	syscall.Exit(1)
    }
}