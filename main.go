package main

import (
	cli "github.com/onecthree/concrete/clipa"
	. "github.com/onecthree/concrete/typeof"
	"github.com/onecthree/concrete/dirm"
	"github.com/onecthree/concrete/utils"
	"github.com/onecthree/concrete/system/pkgdl"
	"os"
	"os/exec"
	"log"
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
			"install": func(subArgs []string, ctx func(int)string) {
				if ctx(1) == "fusion" {

					fusionPackage := pkgdl.PackageDl{}
					fusionPackage.Filename("fusion.zip");
					fusionPackage.PackageUri("http://onecthr.ee/fusion.zip");
					fusionPackage.Download(func() {
						err := utils.Unzip("fusion.zip", "fusion");

						if err != nil {
							log.Fatal(err);
						}

						fmt.Println("fuzion.zip extracted");
						fmt.Println("Installing fusion extension");

						cmd, err := exec.Command("bash", "-c", "cd fusion && ./build").Output()
					
						if err != nil {
						fmt.Printf("error %s", err)
						}
						
						output := string(cmd)
						fmt.Println(output)
						
					});
				}
			},
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