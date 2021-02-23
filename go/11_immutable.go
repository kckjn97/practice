package main

import "fmt"

func main() {
	var x int = 5 // 5는 imumutable
	z := x
	z = 7
	fmt.Println(x, z)

	var y []int = []int{1, 2, 3}
	z2 := y
	z2[0] = 0
	fmt.Println(z2, y) // 출력 [0 2 3] [0 2 3]
}
