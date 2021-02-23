package main

import "fmt"

// func 함수이름 (매개변수이름 매개변수형) 반환형
// parameter 매개변수: x
// argument 전달인자: 5, 6 (넣어준 값)
func test() {
	fmt.Println("hello")
}
func add(x, y int) int {
	return x + y
}

func compute(x, y int) (int, int) {
	return x + y, x - y
}

func compute2(x, y int) (w1, w2 int) {
	w1 = x + y
	w2 = x - y
	return
}

func compute3(x, y int) (w1, w2 int) {
	defer fmt.Println("계산 완료") //반환 후 실행
	fmt.Println("계산중")
	w1 = x + y
	w2 = x - y
	return
}

func main() {
	test()
	z := add(1, 2)
	fmt.Println(z)
	z1, z2 := compute3(1, 2)
	fmt.Println(z1, z2)
}
