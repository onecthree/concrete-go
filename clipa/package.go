package clipa

import (
	// . "github.com/onecthree/concrete/typeof"
	// "fmt"
	"log"
	"github.com/onecthree/concrete/utils"
)

type Init struct {
	Debug			bool
	UseArgs			[]string
	rootArgs		[]string
	emptyArgs		bool
	subOfPos		int
	undefinedArgs	bool
}

func (this *Init) parseMainArgs(getTrueArgs map[string]func([]string, func(int)string)) map[string]bool {
	result := make(map[string]bool);

	for index, _ := range getTrueArgs {
		result[index] = true;
	}

	return result;
}

func (this *Init) On(callback func([]string, int)) {
	this.undefinedArgs = true;
	this.emptyArgs = true;

	if(len(this.UseArgs) > 1) {
		this.emptyArgs = false;
		this.rootArgs = this.UseArgs[1:];
	}

	// if(!this.emptyArgs) {
	callback(this.rootArgs, len(this.rootArgs));
	// }
}

func (this *Init) bindContext(pos int) string {
	return this.rootArgs[this.subOfPos + pos];
}

func (this *Init) Bind(args []string, callback map[string]func([]string, func(int)string), errorHandler map[string]func()) {
	mainArgsList := this.parseMainArgs(callback);

	if(len(args) < 1) {
		this.undefinedArgs = false;
		errorHandler["empty"]();
		return
	}

	if _, ok := mainArgsList[args[0]]; ok {
		log.Println(args[0]);
		this.undefinedArgs = false;
		ofPos := utils.GetIndex(this.rootArgs, args[0]);
		this.subOfPos = ofPos;
		callback[args[0]](args[1:], this.bindContext);
	} else {
		this.undefinedArgs = false;
		errorHandler["undefined"]();
	}
}

func (this *Init) RetUndefined() {
	this.undefinedArgs = false;
}

func (this *Init) Undefined(callback func()) {
	if(this.undefinedArgs && !this.emptyArgs) {
		callback();
	}
}

func (this *Init) Empty(callback func()) {
	if(this.emptyArgs) {
		callback();
	}
}
