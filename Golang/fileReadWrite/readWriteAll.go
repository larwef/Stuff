package main

import(
	"fmt"
	"strings"
	"strconv"
	"io/ioutil"
	"os"
)

func main() {
	data, err := ioutil.ReadFile("test.txt")

	if err != nil {
		os.Exit(1)
	}

	stringData := string(data)

	stringArray := strings.Split(stringData, " ")

	intData := ""

	for _, y := range stringArray {
		number, _ := strconv.Atoi(y)
		intData = intData + strconv.Itoa(number + 1) + " "
	}

	err = ioutil.WriteFile("test.txt", []byte(strings.Trim(intData, " ")), 0644)
    if err != nil { 
    	panic(err)
    }

	fmt.Println(intData)
}