package main

import (
	cli "github.com/onecthree/concrete/cliparser"
	// . "github.com/onecthree/concrete/typeof"
	"os"
	"fmt"
)

var interf = cli.Cli{
	Debug: false,
}

func main() {

	interf.UseArgs(os.Args);

	interf.Listen(func(args []string, lenArgs int) {
		interf.Bind(args, map[string]func([]string) {
			"fusion": func(subArgs []string) {
					interf.Bind(subArgs, map[string]func([]string) {
						"create-project": func(subArgs []string) {
							fmt.Println("fusion create-project");
						},
					});
			},
			"delete-project": func(subArgs []string) {
				fmt.Println("delete-project");
			},
			"version": func(subArgs []string) {
				fmt.Println("concrete: self-package manager for Fusion. v1.0-b");
			},
		});
	});

	interf.Undefined(func() {
		fmt.Println("Perintah tidak ditemukan")
	});

	interf.Empty(func() {
		fmt.Println("Perintah kosong");
	});

}