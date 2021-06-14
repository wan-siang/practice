//請開發一個簡單的reverse程式對檔案內容進行反轉
//執行指令：reverse argv1
//argv1：要處理的檔案
//結果：路徑argv1的檔案內容中完全反轉並寫回argv1檔案中

#include	<stdio.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<unistd.h>

int main(int argc, char **argv){
	int	fd;
	char	*buf;
	char	*line;
	unsigned int	fileSize;
	int	i;

	if(argc!=2){
		fprintf(stderr, "%s inputfile\n", argv[0]);
		exit(1);
	}	
	fd = open(argv[1], O_RDWR);		
	if(fd < 0){
		fprintf(stderr, "open error. filename: %s\n", argv[1]);
		exit(1);
	}

	fileSize = lseek(fd, 0, SEEK_END);
	buf = (char *)malloc(fileSize+1);
	line = (char *)malloc(fileSize+1);

	if(buf == NULL){
		fprintf(stderr, "mallocfailed\n");
		exit(1);
	}

	lseek(fd, 0, SEEK_SET);
	read(fd, buf, fileSize);
	buf[fileSize] = '\0';	
	
	for(i = 0; i < fileSize; i++){
		line[i] = buf[fileSize-1-i];
	}
	line[i] = '\0';
	
	lseek(fd, 0, SEEK_SET);
	write(fd, line, fileSize);
	
}
