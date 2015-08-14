#include "shell.h"

void shell_loop() {
	Command cmd;
	bool end = false;
	do {
		vga_terminal_puts("\n >: ");
		shell_get_command();
		//shell_exec_command(cmd);	
	} while (!end);
}

Command shell_get_command() {
	//Command cmd;
	char* cmdstr = vga_terminal_getstring();
	//return cmd;		
}

void shell_exec_command(Command cmd) {

}
