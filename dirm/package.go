package dirm

import (
	"os"
	"path/filepath"
	"embed"
	"log"
)

func Path(root string, path string) string {
	return filepath.Join(root, path);
}

func Embed(emb embed.FS, filaname string) string {
	content, _ := emb.ReadFile(filaname);
	return string(content);
}

func NewFile(fileList [][]string) {
	for _, val := range fileList {
		file, err := os.Create(val[0])
		
		if err != nil {
			log.Fatal(err);
		}

		_, err = file.WriteString(val[1]);

		if err != nil {
			log.Fatal(err);
		}

		defer file.Close();
	}
}

func NewDir(dirList []string) {
	for _, val := range dirList {
		os.MkdirAll(val, os.ModePerm);
	}
}