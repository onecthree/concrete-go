package pkgdl

import (
	"log"
	"net/http"
	"io"
	"os"
)

type PackageDl struct {
	filename		string
	packageUri		string
}

func (this *PackageDl) Filename(filename string) {
	this.filename = filename;
}

func (this *PackageDl) PackageUri(packageUri string) {
	this.packageUri = packageUri;
}

func (this *PackageDl) Download(callback func()) {
	out, _ := os.Create(this.filename);
	defer out.Close();

	resp, _ := http.Get(this.packageUri)
	defer resp.Body.Close();	

	n, err := io.Copy(out, resp.Body)
	if err != nil {
		log.Fatal(err, n);
	}
	
	callback();
}