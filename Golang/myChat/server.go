package main

import(
	"fmt"
	"time"
	"net"
	"strings"
	"bytes"
	"encoding/json"
)

const dateFormat = "02/01/2006 15:04"

type Client struct{
	username string
	conn net.Conn
}

var ClientList = make([]Client, 0)
var MessageLog = make([]string, 0)

func main() {
	service := "127.0.0.1:9999"
	tcpAddr, err := net.ResolveTCPAddr("tcp", service)
	checkError(err)
	listener, err := net.ListenTCP("tcp", tcpAddr)
	checkError(err)
	fmt.Println("Server up and running...")
	for {
		conn, _ := listener.Accept()
		go ClientHandler(conn)
		fmt.Println(conn.RemoteAddr().String(), " connected")
	}
}

func ClientHandler(conn net.Conn) {
	client := Client{"", conn}

	for {
		fromClient := make([]byte, 1024)
		_,err := conn.Read(fromClient)
		if err != nil {
			fmt.Println(conn.RemoteAddr().String(), " disconnected")
			Logout(&client)
			break
		}
		fromClient = bytes.Trim(fromClient, "\x00")
		request := map[string]string{}
		json.Unmarshal(fromClient, &request)
		sendThis := ParseMessage(request, &client)
		if sendThis == nil {
			continue
		}
		sendToClient, _ := json.Marshal(sendThis)
		conn.Write(sendToClient)
	}
}

func ParseMessage(request map[string]string, client *Client) (map[string]string) {
	if request["request"] == "login" {
		return Login(request["username"], client)
	} else if request["request"] == "logout" {
		return Logout(client)
	} else if request["request"] == "message" {
		return PushMessage(request["message"], *client)
	} else {
		return nil
	}
}

func Login(username string, client *Client) (map[string]string) {
	response := map[string]string{"response": "login", "username": username}
	if UsernameExists(username) {
		response["error"] = "Name already taken!"
		fmt.Println("Failed login: ", response["error"], username)
		return response
	}
	if InvalidUsername(username) || username == "" || username == " "{
		response["error"] = "Invalid username!"
		fmt.Println("Failed login: ", response["error"], username)
		return response
	}
	if UserLoggedIn(client.conn) {
		response["error"] = "Already logged in as " + client.username + "!"
		fmt.Println("Failed login: ", response["error"])
		return response
	}
	client.username = username
	ClientList = append(ClientList, *client)
	response["messages"] = StringifyMessagelog()
	fmt.Println(username, "has logged in")
	fmt.Println("Clients: ", ClientList)

	notify := map[string]string{"response": "message", "message": username + " has logged in!"}
	sendToClient, _ := json.Marshal(notify)
	MessageLog = append(MessageLog, client.username + " has logged in!")
	for _, y := range(ClientList) {
		if y.conn != client.conn {
			y.conn.Write(sendToClient)	
		}
	}

	return response
}

func Logout(client *Client) (map[string]string) {
	response := map[string]string{"response": "logout", "username": client.username}
	if !(UserLoggedIn(client.conn)) {
		response["error"] = "Not logged in!"
		return response
	}
	for i, y := range(ClientList) {
		if y.username == client.username {
			ClientList = ClientList[:i+copy(ClientList[i:], ClientList[i+1:])]
			fmt.Println("Clients: ", ClientList)
			y.username = ""
		}
	}
	notify := map[string]string{"response": "message", "message": client.username + " has logged out!"}
	sendToClient, _ := json.Marshal(notify)
	MessageLog = append(MessageLog, client.username + " has logged out!")
	for _, y := range(ClientList) {
		if y.conn != client.conn {
			y.conn.Write(sendToClient)	
		}
	}

	return response
}

func PushMessage(message string, client Client) (map[string]string) {
	response := map[string]string{"response": "message"}
	if !(UserLoggedIn(client.conn)) {
		response["error"] = "You are not logged in!"
		return response
	}
	time := time.Now().Format(dateFormat)
	msg := client.username + " said @ " + time + " " + message
	MessageLog = append(MessageLog, msg)
	response["message"] = msg
	sendToClient, _ := json.Marshal(response)
	for _, y := range(ClientList) {
		if y.conn != client.conn {
			y.conn.Write(sendToClient)	
		}
	}
	return nil
}

func UserLoggedIn(conn net.Conn) (bool) {
	for _, y := range(ClientList) {
		if y.conn == conn {
			return true
		}
	}
	return false
}

func UsernameExists(username string) (bool) {
	for _, y := range(ClientList) {
		if y.username == username {
			return true
		}
	}
	return false
}

func InvalidUsername(username string) (bool) {
	nonAlphanumeric := " !+<>[]()%,.=&-|'~*/@;\n:¨ \"§½¥{}±´?#£"

	return strings.ContainsAny(username, nonAlphanumeric)
}

func StringifyMessagelog() (string){
	str := "Previous messages:"
	for _, y := range MessageLog {
		str = str + "\n" + y
	}

	return str
}

func checkError(err error) {
	if err != nil {
		fmt.Println("Fatal error ", err.Error())
	}
}