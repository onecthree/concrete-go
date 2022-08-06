package main

import (
	cli "github.com/onecthree/concrete/cliparser"
	. "github.com/onecthree/concrete/typeof"
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
			// command: concrete fusion create-project
			"fusion": func(subArgs []string) {
				interf.Bind(subArgs, map[string]func([]string) {
					"create-project": func(subArgs []string) {
						fmt.Println(subArgs);
					},
				}, ErrorHandler { "undefined": fusionUndefined, "empty": fusionEmpty });
			},
			"delete-project": func(subArgs []string) {
				fmt.Println("delete-project");
			},
			"help": func(subArgs []string) {
				fmt.Println("helper list");
			},
			"version": func(subArgs []string) {
				fmt.Println("concrete: self-package manager for Fusion. v1.0-b");
			},
		}, ErrorHandler { "undefined": fusionUndefined, "empty": fusionEmpty });
	});

	interf.Undefined(func() {
		fmt.Println("perintah tidak ditemukan")
	});

	interf.Empty(func() {
		fmt.Println("perintah kosong");
	});

}


func fusionUndefined() {
	fmt.Println("fusion: Perintah tidak ditemukan");
}

func fusionEmpty() {
	fmt.Println("fusion: Perintah kosong");
}