package main

import (
	"bufio"
	"fmt"
	"net"

	"os"
	"bytes"
	"strings"
	"encoding/json"
	"syscall"
)

func main() {
	host := "127.0.0.1:9999"
	conn, err := net.Dial("tcp", host)
	if err != nil {
		fmt.Println("The server is offline, try again later")
		syscall.Exit(0)
	}
	fmt.Println("Type:")
	fmt.Println("-login to log in")
	fmt.Println("-logout to log out")
	fmt.Println("-quit to exit the program")

	reader := bufio.NewReader(os.Stdin)

	go ListenForResponse(conn)

	for {
		line, err := reader.ReadString('\n')
		line = strings.TrimRight(line, " \t\r\n")
		if err != nil {
			conn.Close()
			break
		}
		if line == "-login" {
			Login(conn)
		} else if line == "-logout" {
			Logout(conn)
		} else if line == "-quit" {
			syscall.Exit(0)
		} else {
			Send(conn, line)
		}
	}
}

func ParseResponse(fromServer []byte) {
	response := map[string]string{}
	json.Unmarshal(fromServer, &response)
	if _, ok := response["error"]; ok {
		fmt.Println(response["error"])
	} else if _, ok := response["messages"]; ok {
		fmt.Println("Logged in as", response["username"])
		fmt.Println(response["messages"])
	} else if _, ok := response["message"]; ok {
		fmt.Println(response["message"])
	} else if response["message"] == "logout" {
		fmt.Println("Logged out", response["username"])
	} else {
		//Do nothing
	}
}

func Login(conn net.Conn) {
	reader := bufio.NewReader(os.Stdin)
	fmt.Printf("Username: ")
	nick, _ := reader.ReadString('\n')
	nick = strings.TrimRight(nick, " \t\r\n")
	data := map[string]string{"request": "login", "username": nick}
	request, _ := json.Marshal(data)
	conn.Write(request)
}

func Logout(conn net.Conn) {
	data := map[string]string{"request": "logout"}
	request, _ := json.Marshal(data)
	conn.Write(request)
}

func Send(conn net.Conn, message string) {
	data := map[string]string{"request": "message", "message": message}
	request, _ := json.Marshal(data)
	conn.Write(request)
}

func ListenForResponse(conn net.Conn) {
	for {
		fromServer := make([]byte, 1024)
		_, err := conn.Read(fromServer)
		if err != nil {
			conn.Close()
			fmt.Println("Server has gone offline or the connection has been closed")
			syscall.Exit(0)
		}
		fromServer = bytes.Trim(fromServer, "\x00")
		ParseResponse(fromServer)
	}
}