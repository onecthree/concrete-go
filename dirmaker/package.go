package dirmaker

import (
	"os"
	"path/filepath"
)

func Path(root string, path string) string {
	return filepath.Join(root, path);
}

func New(dirList []string) {
	for _, val := range dirList {
		os.MkdirAll(val, os.ModePerm);
	}
}