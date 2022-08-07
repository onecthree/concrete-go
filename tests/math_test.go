package math

import "testing"
// import "reflect"

func GetIndex(slice []string, subject string) int {
	for index, val := range slice {
		if val == subject {
            return index;
        }
	}

	return -1
}

func TestDo(t *testing.T){
    sliceDummy := []string{"foo", "bar", "foobar"};

    if(GetIndex(sliceDummy, "bar") == 1) {
        t.Errorf("Error %q", GetIndex(sliceDummy, "bar"));
    }

}