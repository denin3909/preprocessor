mypreprocessor: main.c comment_removal.c file_inclusion.c macro_handler.c preprocessor.h
	gcc -Wall main.c comment_removal.c file_inclusion.c macro_handler.c -o mypreprocessor
clean:
	rm -f mypreprocessor *.o *.i *.tmp	
