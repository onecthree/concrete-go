package cliparser

import (
	// . "github.com/onecthree/concrete/typeof"
	// "fmt"
)

type Cli struct {
	Debug			bool
	trueArgsList	[]string
	emptyArgs		bool
	undefinedArgs	bool
}

func (this *Cli) UseArgs(args []string) {
	if(len(args) > 1) {
		this.emptyArgs = false;
		this.trueArgsList = args[1:];
	} else {
		this.emptyArgs = true;
	}
}

func (this *Cli) parseMainArgs(getTrueArgs map[string]func([]string)) map[string]bool {
	result := make(map[string]bool);

	for index, _ := range getTrueArgs {
		result[index] = true;
	}

	return result;
}

func (this *Cli) Listen(callback func([]string, int)) {
	if(!this.emptyArgs) {
		callback(this.trueArgsList, len(this.trueArgsList));
	}
}

func (this *Cli) Bind(args []string, callback map[string]func([]string), errorHandler map[string]func()) {
	mainArgsList := this.parseMainArgs(callback);
	this.undefinedArgs = true;

	if(len(args) < 1) {
		this.undefinedArgs = false;
		errorHandler["empty"]();
		return
	}

	if _, ok := mainArgsList[args[0]]; ok {
		this.undefinedArgs = false;
		callback[args[0]](args[1:]);
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
