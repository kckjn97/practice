//hello.go
package main

import "fmt"

func main() {
	// 변수 선언
	var x = 1234
	fmt.Println(x)

	var str1 = "Hello"
	fmt.Println(str1)

	var str2 string = "Hello world3"
	fmt.Println(str2, x)

	str3 := "Hello world4"
	fmt.Println(str3)

	var f = 1.2
	fmt.Printf("f: %T\n", f)
	fmt.Printf("str3: %T\n", str3)

	// 타입이 바뀌면 에러
	// str3 := 123

	// 기본값이 할당
	var number uint64
	var boo bool
	fmt.Println(number, boo)
}
