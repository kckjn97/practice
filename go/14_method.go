package main

import "fmt"

// func (리시버 인자) 메소드이름 (파라미터) 리턴타입

// 리시버: 객체와 함수를 연결하는 매개체
// 메소드: 객체에 연결된 함수

// value receiver
// pointer receiver

type Duck_Hunting struct {
	x, y int
}

// 리시버: Duck_Hunting, 메소드: duck_count
// pointer receiver
func (d *Duck_Hunting) duck_count(a int) {
	d.x += a
	d.y += a
}

// value receiver
func (d Duck_Hunting) duck_eat(a int) {
	d.x -= a
	d.y -= a
}

func main() {
	d := Duck_Hunting{3, 2}
	fmt.Println(d) // {3 2}

	d.duck_count(3)
	fmt.Println(d) // {6 5}

	d.duck_eat(2)
	fmt.Println(d) // {6 5}
}
