package main

import (
	"fmt"
	"bufio"
	"os"
)

func main() {
	string[] inp
	reader := bufio.NewReader(os.Stdin)
	while(true){
		fmt.Println("Enter Input followed by enter key:")
		text, _ := reader.ReadString('\n')
		fmt.Println(text)
		if text == " " {
			break
		}
	}
}

