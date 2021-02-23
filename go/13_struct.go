package main

import "fmt"

// Go언어에서는 class 대신 struct 를 사용
//
// type 구조체 struct{
//	...
//}

type Dog struct {
	name string
	age  int
}

func main() {
	dog1 := Dog{}
	dog2 := Dog{"Lex", 3}
	dog3 := Dog{name: "Ark"}

	dog1.name = "Amy"
	dog1.age = 1

	fmt.Println(dog1, dog2, dog3) //	{Amy 1} {Lex 3} {Ark, 0}
}
