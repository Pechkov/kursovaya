#include "cformat.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    FILE* file = NULL;
    if (argc < 2){
        printf("write the file name after 'cformat'\n");
    }
    else if (argc == 2) {
        if ((file = fopen(argv[1], "r")) == NULL) {
            printf("Error: can't open file \e[1;35m\"%s\"\e[0m\n", argv[1]);
            fclose(file);
	}
	else {
            fclose(file);
	    file = fopen(argv[1], "r");
            char fileText[65563] = "";
    	    char line[65563];
   	    while (fgets(line, 65563, file)){
        	strcat(fileText, line);
	    }
	    
	    if (check_brackets(fileText) == 0){
		printf("error brackets");
	    }
	    else{
	        fclose(file);
	        char *result = formatFigureBrackets(fileText);
	        FILE *file_res = fopen(argv[1], "w");
	        fputs(result, file_res);
      	        fclose(file_res);
	    }
	}
    }
    return 0;
}
