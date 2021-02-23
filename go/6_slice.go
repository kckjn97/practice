package main

import (
	"fmt"
)

func main() {
	var x [5]int = [5]int{1, 2, 3, 4, 5}

	var s []int = x[:]
	fmt.Println(s)
	fmt.Println(len(s)) // 5
	fmt.Println(cap(s)) // 5

	var s2 []int = x[1:3]
	fmt.Println(s2)      // [2 3]
	fmt.Println(len(s2)) // 2
	fmt.Println(cap(s2)) // 4

	var s3 []int = x[:3]
	fmt.Println(s3)      // [1 2 3]
	fmt.Println(len(s3)) // 3
	fmt.Println(cap(s3)) // 5

	s4 := append(s3, 7, 9, 10)
	fmt.Println(s4)
	fmt.Println(len(s4)) // 6
	fmt.Println(cap(s4)) // 10

	s5 := make([]int, 3, 4) // len: 3, cap: 4인 slice 생성
	fmt.Println(len(s5))    // 3
	fmt.Println(cap(s5))    // 4

	fmt.Printf("%T\n", s5)

	var a []int = []int{1, 2, 3, 4, 5, 6, 7, 8, 9}

	for i := 0; i < len(a); i++ {
		fmt.Println(a[i])
	}

	for i, v := range a { // index, value
		fmt.Println(i, v)
	}

	for _, v := range a { // 사용하지 않는 변수는 _(anonymous) 로 지정
		fmt.Println(v)
	}
}
