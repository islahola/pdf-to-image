/*Program :
1. Ekstraksi berkas pdf
2. Hasil ekstraksi dirubah menjadi jpg
3. Hasil konversi menjadi jpg dirubah menjadi teks
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	if(argc!=4) printf("%s", "anda tidak memasukkan nama berkas pdf, halaman awal, halaman akhir dengan lengkap");
	char com[100];
	char page[5];
	int begin = atoi(argv[2]);
	int end = atoi(argv[3]);
	com[0]=0;
	page[0]=0;
	system("clear");
   	for (int i=begin; i<=end;i++){		
   		strcat(com, "pdftk ");
   		strcat(com, argv[1]);
   		strcat(com, " cat ");
   		sprintf(page, "%d", i);
   		strcat(com, page);
   		strcat(com, " output ");
   		strcat(com, page);
   		strcat(com, ".pdf uncompress");
   		printf("%s \n", com);
   		system(com);
   		com[0]=0;
		page[0]=0;
   		}
   	for (int i=begin; i<=end;i++){	
   		//convert input.pdf output.jpg	
   		strcat(com, "convert  -density 900 -quality 100 ");
   		sprintf(page, "%d", i);
   		strcat(com, page);
   		strcat(com, ".pdf ");
   		strcat(com, page);
   		strcat(com, ".jpg ");   
   		printf("%s \n", com);		
   		system(com);
   		com[0]=0;
		page[0]=0;
   		}
   	for (int i=begin; i<=end;i++){	
   		//convert input.jpg output.txt	
   		strcat(com, "tesseract ");
   		sprintf(page, "%d", i);
   		strcat(com, page);
   		strcat(com, ".jpg ");
   		strcat(com, page);
   		strcat(com, "t");
   		printf("%s \n", com);
   		system(com);
   		com[0]=0;
		page[0]=0;
   		}
    return 0;
}

