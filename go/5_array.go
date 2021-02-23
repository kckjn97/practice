package main

import "fmt"

func main() {
	// 배열 선언 (1)
	var arr [5]int
	fmt.Println(arr)
	arr[1] = 100
	fmt.Println(arr)

	// 배열 선언 (2)
	arr2 := []int{3, 4, 5}
	fmt.Println(arr2)

	sum := 0
	for i := 0; i < len(arr2); i++ {
		sum += arr2[i]
	}
	fmt.Println(sum)

	// 2중 배열
	arr3 := [3][2]int{{1, 2}, {3, 4}, {5, 6}}
	fmt.Println(arr3[2][1])

	fmt.Printf("%T\n", arr3)
}
