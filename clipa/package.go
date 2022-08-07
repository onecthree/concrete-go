package clipa

import (
	// . "github.com/onecthree/concrete/typeof"
	// "fmt"
	"github.com/onecthree/concrete/utils"
)

type Cli struct {
	Debug			bool
	rootArgs		[]string
	emptyArgs		bool
	subOfPos		int
	undefinedArgs	bool
}

func (this *Cli) UseArgs(args []string) {
	if(len(args) > 1) {
		this.emptyArgs = false;
		this.rootArgs = args[1:];
	} else {
		this.emptyArgs = true;
	}
}

func (this *Cli) parseMainArgs(getTrueArgs map[string]func([]string, func(int)string)) map[string]bool {
	result := make(map[string]bool);

	for index, _ := range getTrueArgs {
		result[index] = true;
	}

	return result;
}

func (this *Cli) Listen(callback func([]string, int)) {
	if(!this.emptyArgs) {
		callback(this.rootArgs, len(this.rootArgs));
	}
}

func (this *Cli) bindContext(pos int) string {
	return this.rootArgs[this.subOfPos + pos];
}

func (this *Cli) Bind(args []string, callback map[string]func([]string, func(int)string), errorHandler map[string]func()) {
	mainArgsList := this.parseMainArgs(callback);
	this.undefinedArgs = true;

	if(len(args) < 2) {
		this.undefinedArgs = false;
		errorHandler["empty"]();
		return
	}

	if _, ok := mainArgsList[args[0]]; ok {
		this.undefinedArgs = false;
		ofPos := utils.GetIndex(this.rootArgs, args[0]);
		this.subOfPos = ofPos;
		callback[args[0]](args[1:], this.bindContext);
	} else {
		this.undefinedArgs = false;
		errorHandler["undefined"]();
	}
}

func (this *Cli) Undefined(callback func()) {
	if(this.undefinedArgs) {
		callback();
	}
}

func (this *Cli) Empty(callback func()) {
	if(this.emptyArgs) {
		callback();
	}
}
