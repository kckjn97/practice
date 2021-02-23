package main

import "fmt"

func main() {
	age := 5
	if age >= 10 {
		fmt.Println(">= 10")
	} else if age >= 5 {
		fmt.Println("< 10 and >=5")
	} else {
		fmt.Println("< 5")
	}

	num := 4
	switch num {
	case 1, 2:
		fmt.Println("num: 1 or 2")
	case 3:
		fmt.Println("num: 3")
	default:
		fmt.Println("num: default")
	}

	num2 := 2
	switch {
	case num2 > 1:
		fmt.Println("num2: > 1")
	case num2 < 1:
		fmt.Println("num2: < 1")
	default:
		fmt.Println("num2: default")
	}
}
