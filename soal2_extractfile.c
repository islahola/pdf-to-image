/*Program :
    • Melakukan ekstraksi berkas PDF per halaman, seperti yang telah dicontohkan
    • Berkas-berkas PDF dikonversi menjadi berkas-berkas berformat JPEG
    • Berkas-berkas berformat JPEG tersebut kemudian diambil huruf-hurufnya, dan dijadikan berkas-berkas yang berformat teks
    • Perintah-perintah yang anda lakukan wajib menggunakan pemanggilan systems.
    • Berkas-berkas pdf harus diletakkan pada direktori yang berisi seluruh berkas pdf
    • Berkas-berkas JPEG harus diletakkan pada direktori yang berisi seluruh berkas JPEG
    • Berkas-berkas teks harus diletakkan pada direktori yang berisi seluruh berkas teks
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int ikn_argc, char *ikn_argv[]){
	if(ikn_argc!=4) printf("%s", "harap masukan nama.pdf jumlah halaman pertama dan jumlah halaman akhir");
	char ikn_com[100];
	char ikn_page[4];
	int ikn_begin = atoi(ikn_argv[2]);
	int ikn_end = atoi(ikn_argv[3]);
	ikn_com[0]=0;
	ikn_page[0]=0;
	system("clear");
   	for (int i=ikn_begin; i<=ikn_end;i++){		
   		strcat(ikn_com, "pdftk");
   		strcat(ikn_com, ikn_argv[1]);
   		strcat(ikn_com, "cat");
   		sprintf(ikn_page, "%d", i);
   		strcat(ikn_com, ikn_page);
   		strcat(ikn_com, "output");
   		strcat(ikn_com, ikn_page);
   		strcat(ikn_com, ".pdf uncompress");
   		printf("%s \n", ikn_com);
   		system(ikn_com);
   		ikn_com[0]=0;
		ikn_page[0]=0;
   		}
   	for (int i=ikn_begin; i<=ikn_end;i++){	
   		// Berkas-berkas berformat JPEG tersebut kemudian diambil huruf-hurufnya, dan dijadikan berkas-berkas yang berformat teks
   		strcat(ikn_com, "convert  -density 900 -quality 100");
   		sprintf(ikn_page, "%d", i);
   		strcat(ikn_com, ikn_page);
   		strcat(ikn_com, ".pdf");
   		strcat(ikn_com, ikn_page);
   		strcat(ikn_com, ".jpeg");   
   		printf("%s \n", ikn_com);		
   		system(ikn_com);
   		ikn_com[0]=0;
		ikn_page[0]=0;
   		}
   	for (int i=ikn_begin; i<=ikn_end;i++){	
   		//Berkas-berkas teks harus diletakkan pada direktori yang berisi seluruh berkas teks
   		strcat(ikn_com, "tesseract ");
   		sprintf(ikn_page, "%d", i);
   		strcat(ikn_com, ikn_page);
   		strcat(ikn_com, ".jpeg ");
   		strcat(ikn_com, ikn_page);
   		strcat(ikn_com, "t");
   		printf("%s \n", ikn_com);
   		system(ikn_com);
   		ikn_com[0]=0;
		ikn_page[0]=0;
   		}
    return 0;
}

