package main

import "fmt"

func main() {
	var zoo map[string]int = map[string]int{
		"코끼리": 31,
		"사자":  7,
		"범":   7, // 마지막에 콤마 반드시 추가
	}

	zoo["코알라"] = 90
	fmt.Println(zoo["코알라"])
	fmt.Println(zoo)
	delete(zoo, "코알라")
	fmt.Println(zoo["코알라"]) // 0
	fmt.Println(zoo)
	val, ok := zoo["킹콩"]
	fmt.Println(val, ok) // 0 False
	val2, ok2 := zoo["사자"]
	fmt.Println(val2, ok2) // 7 True
}
