package main

import (
	"flag"
	"fmt"
	"strconv"
	"time"
)

func main() {
	flag.Parse() //実行引数をとる
	if flag.NArg() != 1 {
		fmt.Print("usage: matrix N\n")
		return
	}

	n, _ := strconv.Atoi(flag.Arg(0))

	a := make([]int, n*n) // Matrix A
	b := make([]int, n*n) // Matrix B
	c := make([]int, n*n) // Matrix C

	// Initialize the matrices to some values.
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			a[i*n+j] = i*n + j // A[i][j]
			b[i*n+j] = j*n + i // B[i][j]
			c[i*n+j] = 0       // C[i][j]
		}
	}

	begin := time.Now()
	/**************************************/
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			for k := 0; k < n; k++ {
				c[i*n+j] += a[i*n+k] * b[k*n+j] // C[i][j]
			}
		}
	}
	/**************************************/

	end := time.Now()
	fmt.Printf("time: %v sec\n", end.Sub(begin).Nanoseconds())

	var sum int64
	sum = 0
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			sum += c[i*n+j]
			// fmt.printf("c[%d][%d]=%lf\n", i, j, c[i * n + j]);
		}
	}
	// Print out the sum of all values in C.
	// This should be 450 for N=3, 3680 for N=4, and 18250 for N=5.
	fmt.Printf("sum: %v\n", sum)

}
