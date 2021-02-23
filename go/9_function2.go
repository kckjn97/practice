package main

import "fmt"

func h(x int) {
	fmt.Println("hello: ", x)
}

func hh(myH func(int) int) {
	fmt.Println(myH(9))
}

func returnH(x string) func() {
	return func() { fmt.Println(x) }
}

func main() {
	// 일급함수 :  함수를 변수에 할당이 가능하며 함수의 인자나 리턴 값이 될 수 있음
	x := h
	x(1)

	// 익명함수
	h2 := func(x int) {
		fmt.Println("hello2:", x)
	}
	h2(10)

	h3 := func(x int) int {
		return x * -1
	}(7)
	fmt.Println(h3)

	h4 := func(x int) int {
		return x * -1
	}
	hh(h4)

	h5 := func(x int) int {
		return x * 9
	}

	hh(h5)

	// 클로저(Closure): 함수안에서 함수를 선언/정의할 수 있고
	// 바깥쪽 함수에 선언된 변수에도 접근할 수 있는 함수
	returnH("hi")()

	a := returnH("a func")
	b := returnH("b func")

	a()
	b()
}
