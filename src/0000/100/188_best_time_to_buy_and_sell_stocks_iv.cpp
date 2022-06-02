// func Max(x int, y int) int {
// 	if x > y {
// 		return x
// 	} else {
// 		return y
// 	}
// }

// func maxProfit(k int, prices []int) int {
// 	buy := make([]int, k+1) // Initializes to 0
// 	sell := make([]int, k+1)
// 	for i := range buy {
// 		buy[i] = -500000
// 	}

// 	for _, p := range prices {
// 		for i := k; i > 0; i-- {
// 			sell[i] = Max(sell[i], buy[i]+p)
// 			buy[i] = Max(buy[i], sell[i-1]-p)
// 		}
// 	}
// 	return sell[k]
// }
