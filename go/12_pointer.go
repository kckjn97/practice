package main

import "fmt"

func main() {
	x := 7
	ptr_x := &x
	fmt.Println(x, ptr_x)

	*ptr_x = 9
	fmt.Println(x, ptr_x)
}
