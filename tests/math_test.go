package math

import "testing"
import "reflect"

func TestDo(t *testing.T){
    args := []string{"test", "hello"};
    want := []string{"test", "hello"};

    if(!reflect.DeepEqual(args[:1], want)) {
        t.Errorf("got: %q, want: %q", args[:1], want);
    }

}