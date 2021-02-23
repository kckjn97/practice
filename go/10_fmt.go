package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	var string = fmt.Sprintf("%T %d %t", 10, 10, true)
	fmt.Println(string)

	fmt.Print("input: ")
	scan1 := bufio.NewScanner(os.Stdin)
	scan1.Scan()
	input := scan1.Text()
	fmt.Println("echo: ", input)

	fmt.Print("input number: ")
	scan2 := bufio.NewScanner(os.Stdin)
	scan2.Scan()
	input2, _ := strconv.ParseInt(scan2.Text(), 10, 64) //10진수, 64bit
	fmt.Println(": ", 100-input2)
}
