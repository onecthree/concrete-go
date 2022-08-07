package main

import "fmt"

func GetIndex(slice []string, subject string) int {
	for index, val := range slice {
		if val == subject {
            return index;
        }
	}

	return -1;
}

func main() {
	sliceDummy := []string{"foo", "bar", "foobar"};
	fmt.Println(GetIndex(sliceDummy, "foobar"))
}