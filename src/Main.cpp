#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int rEstruturante = 3;
int cEstruturante = 3;

//gera elemento estruturante
Mat elementoEstruturante(){
	return getStructuringElement( MORPH_RECT,
								  Size( 2*rEstruturante + 1, 2*cEstruturante+1 ),
								  Point( rEstruturante, cEstruturante )); // elemento estruturante  retangulo 3x3

}

//cria a imagem com abertura
Mat Abertura(Mat img){
	Mat matAberta;

	Mat element = elementoEstruturante();

	dilate(img,matAberta,element);
	erode(img,matAberta,element);

	return matAberta;
}

//cria a imagem com fechamento
Mat Fechamento(Mat img){
	Mat matFechada;

	Mat element = elementoEstruturante();

	erode(img,matFechada,element);
	dilate(img,matFechada,element);

	return matFechada;
}

//cria a iamgem com erosao
Mat Erosao(Mat img){
	Mat erosao;

	Mat element = elementoEstruturante();

	erode(img,erosao,element);

	return erosao;
}

//cria a imagem com dilatacao
Mat Dilatacao(Mat img){
	Mat dilatacao;

	Mat element = elementoEstruturante();

	dilate(img,dilatacao,element);

	return dilatacao;
}

int main(){
	Mat img = imread("./img/morf_test.png",CV_LOAD_IMAGE_GRAYSCALE);

	if (!img.data) {
		cout << "Imagem nao encontrada" << endl;
		exit(0);//refazer isso aqui, eh feio
	}

	Mat matFechada = Fechamento(img);

	Mat resultadobottom = matFechada - img; //bottom-hat
	
	threshold(resultadobottom,resultadobottom,50,255,CV_THRESH_BINARY);//binarizacao da imagem

	Mat resultadofinal;
	medianBlur(resultadobottom,resultadofinal,1);//filtragem mediana da imagem

	threshold(resultadofinal,resultadofinal,50,255,CV_THRESH_BINARY_INV);	


	imshow("Original",img);
	imshow("Fundo",matFechada);
	imshow("bottom-hat",resultadobottom);
	imshow("Output Imagem binaria invertida",resultadofinal);
	waitKey(0);
	
	return 0;
}