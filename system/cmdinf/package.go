package cmdinf

import (
	"os/exec"
	"os"
	"bufio"
	"fmt"
)

func Exec(commands string) {
	cmd := exec.Command("bash", "-c", commands);
										
	cmdReader, err := cmd.StdoutPipe()

	if err != nil {
		fmt.Fprintln(os.Stderr, "Error creating StdoutPipe for cmdinf:", err);
		return
	}

	scanner := bufio.NewScanner(cmdReader)
	go func() {
		for scanner.Scan() {
			fmt.Printf("concrete: %s\n", scanner.Text());
		}
	}();

	err = cmd.Start()
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error starting cmdinf:", err);
		return
	}

	err = cmd.Wait()
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error waiting for cmdinf:", err);
		return
	}
}