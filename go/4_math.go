package main

import (
	"fmt"
	"math"
)

func main() {
	num1 := 3.2 // float32
	num2 := 4   // int
	//fmt.Println(num1 + num2)	//Error
	answer := num1 + float64(num2)
	fmt.Printf("%g\n", answer)

	fmt.Println(math.Sqrt(answer))
}
