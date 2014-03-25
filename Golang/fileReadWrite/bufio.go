package main

import (
	"fmt"
    "bufio"
    "io"
    "os"
)

func main() {
    readFile, err := os.Open("bufio.txt")
    if err != nil {
        os.Exit(1)
    }

    reader := bufio.NewReader(readFile)

    writeFile, err := os.Open("bufio2.txt")
    if err != nil {
    	fmt.Println("File does not exist")
    	writeFile, err = os.Create("bufio2.txt")
    	if err != nil {
    		os.Exit(1)
    	}
    	fmt.Println("File created")
    }

    writer := bufio.NewWriter(writeFile)

    buf := make([]byte, 8)

    for {
    	n, err := reader.Read(buf)
    	fmt.Println("buf = ", string(buf))
    	if err != nil && err != io.EOF {
    		os.Exit(1)
    	}
        if n == 0 {
        	fmt.Println("break")
        	break
        }
        if _, err := writer.Write(buf[:n]); err != nil {
            os.Exit(1)
        }
    }

    if err = writer.Flush(); err != nil {
    	os.Exit(1)
    }
}