package main

// concurrency을 구현하기 위해서 goroutine 사용
// go 키워드를 선언하면 goroutine으로 실행해서 동시성프로그램으로 작동
// go 함수명

// Wait Group
// sync.WaitGroup : 모든 goroutine이 끝날때까지 wait
// sync.WaitGroup을 할당 한 뒤에, Add / Wait / Done 함수로 사용

import "fmt"
import "time"
import "sync"

var wg sync.WaitGroup

func job(s string) {
	defer wg.Done()
	for i := 0; i < 3; i++ {
		time.Sleep(time.Millisecond * 100)
		fmt.Println(s)
	}
	// wg.Done()		// defer로 선언한 것과 동일
}

func main() {
	wg.Add(1)
	go job("육군에 출근")
	wg.Add(1)
	go job("해군에 출근")
	wg.Wait()

	// time.Sleep(time.Millisecond * 1000) // waitGroup 없을때는, Sleep하지 않으면 goroutine이 실행되기전에 프로그램이 종료
	wg.Wait()

}
