//描述：請使用 open() read() write() 實作簡單的copy commnad
//執行指令：./a.out argv1  argv2
//argv1：要被複製的檔案路徑
//argv2：要被貼上的檔案路徑，
//若檔案不存在，要自動create
//檔案內已有內容則直接覆蓋原始檔案內容
//結果：路徑argv1的檔案內容被複製到路徑argv2

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<fcntl.h>

int main(int argc, char **argv){
	int 	fd_in, fd_out;
	char	*buf;
	unsigned int 	fileSize;

	if(argc == 3){
		fd_in = open(argv[1], O_RDONLY);
		if(fd_in < 0){
			fprintf(stderr, "open error: %s\n",argv[1]);
			exit(1);
		}
		
		fd_out = open(argv[2], O_WRONLY);
		if(fd_out < 0){
			fprintf(stderr, "open error: %s\n", argv[2]);
			exit(1);
		}		
	}else if(argc == 2){
		fd_in = open(argv[1], O_RDONLY);
		if(fd_in < 0){
			fprintf(stderr, "open error: %s\n",argv[1]);
			exit(1);
		}
		fd_out = open("file", O_RDWR | O_CREAT, 0600); 	
	}else{
		fprintf(stderr, "usage: %s sourceFile targetFile\n", argv[0]);
		exit(1);
	}

	fileSize = lseek(fd_in, 0, SEEK_END);
	buf = (char *)malloc(fileSize+1);
	if(buf == NULL){
		fprintf(stderr, "malloc failed\n");
	}

	lseek(fd_in, 0, SEEK_SET);
	read(fd_in, buf, fileSize);
	buf[fileSize] = '\0';
	write(fd_out, buf, fileSize);
}
