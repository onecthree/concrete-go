package main

import (
	"github.com/onecthree/concrete/clipa"
	. "github.com/onecthree/concrete/typeof"
	"github.com/onecthree/concrete/dirm"
	"github.com/onecthree/concrete/utils"
	"github.com/onecthree/concrete/system/pkgdl"
	"github.com/onecthree/concrete/system/cmdinf"
	"log"
	"os"
	"fmt"
	"embed"
)

//go:embed embed/fusion/starter/*

var emb embed.FS

var cli = clipa.Init{
	UseArgs	: os.Args,
	Debug	: false,
}

func main() {

	// defer cli.Undefined(func() { fmt.Println("concrete: perintah undefined") });
	// defer cli.Empty(func() { fmt.Println("concrete: perintah kosong") });

	cli.On(func(args []string, lenArgs int) {

		cli.Bind(args, map[string]func([]string, func(int)string) {
			"install": func(subArgs []string, ctx func(int)string) {

				if ctx(1) == "fusion" {
					fusionPackage := pkgdl.PackageDl{}
					fusionPackage.Filename("fusion.zip");
					fusionPackage.PackageUri("http://onecthr.ee/fusion.zip");
					fmt.Println("fusion.zip downloaded")
					fusionPackage.Download(func() {
						err := utils.Unzip("fusion.zip", "fusion");

						if err != nil {
							log.Fatal(err);
						}

						fmt.Println("fuzion.zip extracted");
						fmt.Println("Installing fusion extension");

						cmdinf.Exec("cd fusion && ./build");

					});
				}

			},
			"fusion": func(subArgs []string, ctx func(int)string) {
				cli.Bind(subArgs, map[string]func([]string, func(int)string) {
					"create-project": func(subArgs []string, ctx func(int)string) {
						rootPath := ctx(1);

						dirm.NewDir([]string{
							dirm.Path(rootPath, "app/Controllers"),
							dirm.Path(rootPath, "app/Models"),
							dirm.Path(rootPath, "app/Views"),
							dirm.Path(rootPath, "public"),
							dirm.Path(rootPath, "storage"),
							dirm.Path(rootPath, "routes"),
							dirm.Path(rootPath, "storage/app"),
							dirm.Path(rootPath, "storage/fusion/cache"),
						});	

						dirm.NewFile([][]string{
							[]string{dirm.Path(rootPath, "public/index.php"), dirm.Embed(emb, "embed/fusion/starter/public/index.php")},
							[]string{dirm.Path(rootPath, "routes/web.php"), dirm.Embed(emb, "embed/fusion/starter/routes/routes.php")},
							[]string{dirm.Path(rootPath, "app/Controllers/IndexController.php"), dirm.Embed(emb, "embed/fusion/starter/app/Controllers/IndexController.php")},
						});

					},
				}, ErrorHandler { "undefined": fusionUndefined, "empty": fusionEmpty });
			},

		}, ErrorHandler{
			"undefined": func() {
				fmt.Println("master: undefined");
			},
			"empty": func() {
				fmt.Println("master: empty");
			},
		});

	});
}


func fusionUndefined() {
	fmt.Println("concrete: Perintah tidak ditemukan");
}

func fusionEmpty() {
	fmt.Println("concrete: Perintah kosong");
}