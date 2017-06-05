#include <funcoes.hpp>

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
