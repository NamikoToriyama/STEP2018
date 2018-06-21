package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {

	// ファイルを読み出し用にオープン
	file, err := os.Open("./pagelank.txt")
	if err != nil {
		panic(err)
	}
	defer file.Close()

	// 一行ずつ読み出し
	scanner := bufio.NewScanner(file)
	var link = []string{}
	for scanner.Scan() {
		line := scanner.Text()
		link = append(link, line)
	}

	var all_link = []string{}
	// rangeにstringを渡すとpos,runeを順に返す
	for i, _ := range link {

		var from = []int32{}
		var to = []int32{}
		null_chack := 0

		for pos, r := range link[i] {
			fmt.Printf("character %c value %V starts at byte position %d \n", r, r, pos)

			if null_chack == 0 {
				 	if r == "" {
				null_chack = 1
					}
					else{
				from = append(from, r)
				 	}
			}
			else{
				to=append(to,r)
			}

			from_array := map[string]int{
				"go": 100,
			}
			factor := append(factor, from_array)
			factor = append(factor, to)
		}
		all_link = append(all_link, factor)
	}
	fmt.Println(all_link)
}
