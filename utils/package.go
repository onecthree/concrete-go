package utils


func GetIndex(slice []string, subject string) int {
	for index, val := range slice {
		if val == subject {
            return index;
        }
	}

	return -1;
}
