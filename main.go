package main

import (
	cli "github.com/onecthree/concrete/cliparser"
	. "github.com/onecthree/concrete/typeof"
	"github.com/onecthree/concrete/dirmaker"
	"os"
	"fmt"
)

var interf = cli.Cli{
	Debug: false,
}

func main() {

	interf.UseArgs(os.Args);

	interf.Listen(func(args []string, lenArgs int) {
		interf.Bind(args, map[string]func([]string, func(int)string) {

			"fusion": func(subArgs []string, ctx func(int)string) {
				interf.Bind(subArgs, map[string]func([]string, func(int)string) {
					"create-project": func(subArgs []string, ctx func(int)string) {
						rootPath := ctx(1);
						dirmaker.New([]string{
							dirmaker.Path(rootPath, "app/Controllers"),
							dirmaker.Path(rootPath, "app/Models"),
							dirmaker.Path(rootPath, "app/Views"),
							dirmaker.Path(rootPath, "public"),
							dirmaker.Path(rootPath, "storage"),
							dirmaker.Path(rootPath, "routes"),
						});
					},
				}, ErrorHandler { "undefined": fusionUndefined, "empty": fusionEmpty });
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