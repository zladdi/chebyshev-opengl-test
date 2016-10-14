#ifndef _BMP_H_
#define _BMP_H_

//http://stackoverflow.com/questions/9296059/read-pixel-value-in-bmp-file
typedef struct bmp_file_s
{
	int width, height;
	unsigned char* data;
}
bmp_file;

bmp_file readBMP(char* filename);

#endif /* _BMP_H_ */
