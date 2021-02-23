package main

import "fmt"

// interface: 메서드들의 집합
// type 인터페이스명 interface { 메소드 반환형 }

type Duck struct{}

func (d Duck) sound() {
	fmt.Println("꽥꽥")
}
func (d Duck) taste() {
	fmt.Println("바삭바삭")
}

type Fish struct{}

func (f Fish) sound() {
	fmt.Println("파닥파닥")
}
func (f Fish) taste() {
	fmt.Println("지글지글")
}

type hunting interface {
	sound()
	taste()
}

func inTheRiver(h hunting) {
	h.sound()
	h.taste()
}

func main() {
	var McDonald Duck
	var Marine Fish

	inTheRiver(McDonald)
	inTheRiver(Marine)
}
