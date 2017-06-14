#include <iostream>
#include <opencv2/opencv.hpp>
#include <funcoes.hpp>

using namespace std;
using namespace cv;

int main(){
	/*Mat img = imread("./img/morf_test.png",CV_LOAD_IMAGE_GRAYSCALE);

	if (!img.data) {
		cout << "Imagem nao encontrada" << endl;
		exit(0);
	}

	Mat matFechada = Fechamento(img);

	Mat resultadobottom = matFechada - img; //Transformada Bottom-hat
	
	threshold(resultadobottom,resultadobottom,50,255,CV_THRESH_BINARY);//binarizacao da imagem

	Mat resultadofinal;
	medianBlur(resultadobottom,resultadofinal,1);//filtragem mediana da imagem

	threshold(resultadofinal,resultadofinal,50,255,CV_THRESH_BINARY_INV);//binarizacao inversa da imagem

	imshow("Original",img);
	imshow("Fundo",matFechada);
	imshow("bottom-hat",resultadobottom);
	imshow("Output Imagem binaria invertida",resultadofinal);
	waitKey(0);
	imwrite("imageFinal.png",resultadofinal);
	imwrite("imageBottomHat.png",resultadobottom);
	imwrite("fundo.png",matFechada);
	*/

	Mat img = imread("./img/img_cells.jpg",CV_LOAD_IMAGE_GRAYSCALE);

	medianBlur(img,img,1);
	
	Mat matFechada = Fechamento(img);

	Mat final = matFechada - img;


	threshold(final,final,50,255,CV_THRESH_BINARY);
	threshold(final,final,50,255,CV_THRESH_BINARY_INV);


	imshow("original",img);
	imshow("final",final);
	waitKey(0);

	return 0;
}