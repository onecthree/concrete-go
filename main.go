package main

import (
	cli "github.com/onecthree/concrete/clipa"
	. "github.com/onecthree/concrete/typeof"
	"github.com/onecthree/concrete/dirm"
	"os"
	"fmt"
	"embed"
)

//go:embed embed/fusion/starter/*

var emb embed.FS

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

						dirm.NewDir([]string{
							dirm.Path(rootPath, "app/Controllers"),
							dirm.Path(rootPath, "app/Models"),
							dirm.Path(rootPath, "app/Views"),
							dirm.Path(rootPath, "public"),
							dirm.Path(rootPath, "storage"),
							dirm.Path(rootPath, "routes"),
						});

						dirm.NewFile([][]string{
							[]string{dirm.Path(rootPath, "routes/web.php"), dirm.Embed(emb, "embed/fusion/starter/routes.php")},
						});
					},
					"test": func(subArgs []string, ctx func(int)string) {

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