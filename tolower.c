//請開發一個簡單的tolower程式對檔案內容大寫的部分轉為小寫，並直接寫回原本的檔案
//執行指令：tolower argv1
//argv1：要處理的檔案
//結果：路徑argv1的檔案內容中大寫的部分變為小寫

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>
#include	<fcntl.h>
#include	<unistd.h>
#define		MaxFileName	256
#define		BlockSize	4096
	
int main(int argc, char **argv){
	char	inputFile[MaxFileName];
	int	fd;
	int	readSize;
	char	*buf;
	int 	offset;
	int 	blockSize = BlockSize;
	unsigned int 	fileSize;

	strcpy(inputFile, argv[1]);

	fd = open(inputFile, O_RDONLY);		
	if(fd < 0){
		fprintf(stderr, "open error. filename: %s\n", inputFile);
		exit(1);
	}

	fileSize = lseek(fd, 0, SEEK_END);
	buf = (char *)malloc(fileSize+1);

	if(buf == NULL){
		fprintf(stderr, "malloc failed\n");
	}

	lseek(fd, 0, SEEK_SET);

	offset = 0;

	while((readSize = read(fd, buf+offset, blockSize)) > 0){
		for(int i = 0; i < readSize; i++){
			if(isupper(buf[offset+i])){
				buf[offset+i] = buf[offset+i] - 'A' + 'a';
			}
		}
		offset += readSize;
	}
	buf[offset] = '\0';
	fd = open(inputFile, O_WRONLY);		
	write(fd, buf, fileSize);
	
}
