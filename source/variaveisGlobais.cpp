using namespace std;

// -------- Tamanho inicial da janela --------

#define WINDOW_WIDTH 500	//	Largura inicial
#define WINDOW_HEIGHT 600	//	Altura inicial

// -------- Variaveis de menu --------

int state = 0;	//	0 representa o menu, 1 representa jogo, 2 representa derrota no jogo e qualquer outro representa encerramento do jogo
int selec = 0;  //  Os valores de 0 a 12 representam qual botao esta selecionado
bool gameRunning = 0;   //  Determina se o jogo ja foi iniciado, 0 nao, 1 sim
GLfloat view_w = WINDOW_WIDTH/2, view_h = WINDOW_HEIGHT/2;  //  Os valores representam a metade do tamanho atual da janela
const GLfloat sxmenu = view_h*0.0003;	//	Escala do texto do menu em x
const GLfloat symenu = view_h*0.0004;	//	Escala do texto do menu em y
pair<GLfloat, GLfloat> p0(-view_h*0.1, -view_h*0.1);	//	Ponto inferior esquerdo retangulo do menu
pair<GLfloat, GLfloat> p1(view_h*0.3, view_h*0.03);		//	Ponto superior direito retangulo do menu
//	Map usado para determinar a opcao selecionada que ira configurar o jogo
unordered_map<string, bool> option({
{"NORMAL1", 1}, {"RAPIDO", 0}, {"TURBO", 0},
{"20x10", 1}, {"30x15", 0}, {"50x25", 0},
{"Cores1", 1}, {"Cores2", 0}, {"Cores3", 0},
{"NORMAL2", 1}, {"BEBADO", 0}});
// Map usado para mapear o nome do botao ao seu numero e se esta selecionado
unordered_map<string, pair<int, bool>> selecN({
{"INICIAR", make_pair(0, 1)},
{"NORMAL1", make_pair(1, 0)}, {"RAPIDO", make_pair(2, 0)}, {"TURBO", make_pair(3, 0)},
{"20x10", make_pair(4, 0)}, {"30x15", make_pair(5, 0)}, {"50x25", make_pair(6, 0)},
{"Cores1", make_pair(7, 0)}, {"Cores2", make_pair(8, 0)}, {"Cores3", make_pair(9, 0)},
{"NORMAL2", make_pair(10, 0)}, {"BEBADO", make_pair(11, 0)}, {"SAIR", make_pair(12, 0)}});
//  Map usado para mapear o numero do botao ao nome
unordered_map<int, string> selecI({
{0, "INICIAR"},
{1, "NORMAL1"}, {2, "RAPIDO"}, {3, "TURBO"},
{4, "20x10"}, {5, "30x15"}, {6, "50x25"},
{7, "Cores1"}, {8, "Cores2"}, {9, "Cores3"},
{10, "NORMAL2"}, {11, "BEBADO"},
{12, "SAIR"}});
//	Map usado para determinar a posicao dos botoes no menu
unordered_map<string, pair<GLfloat, GLfloat>> boxPos({
{"INICIAR", make_pair(-(p0.first+p1.first)/2, view_h*0.8)},
{"NORMAL1", make_pair(-(p0.first+p1.first)/2 - view_h*0.45, view_h*0.5)}, {"RAPIDO", make_pair(-(p0.first+p1.first)/2, view_h*0.5)}, {"TURBO", make_pair(-1*((p0.first+p1.first)/2 - view_h*0.45), view_h*0.5)},
{"20x10", make_pair(-(p0.first+p1.first)/2 - view_h*0.45, view_h*0.2)}, {"30x15", make_pair(-(p0.first+p1.first)/2, view_h*0.2)}, {"50x25", make_pair(-1*((p0.first+p1.first)/2 - view_h*0.45), view_h*0.2)},
{"Cores1", make_pair(-(p0.first+p1.first)/2 - view_h*0.45, -view_h*0.1)}, {"Cores2", make_pair(-(p0.first+p1.first)/2, -view_h*0.1)}, {"Cores3", make_pair(-1*((p0.first+p1.first)/2 - view_h*0.45), -view_h*0.1)},
{"NORMAL2", make_pair(-(p0.first+p1.first)/2 - view_h*0.25, -view_h*0.4)}, {"BEBADO", make_pair(-1*((p0.first+p1.first)/2 - view_h*0.25), -view_h*0.4)},
{"SAIR", make_pair(-(p0.first+p1.first)/2, -view_h*0.7)}});
//  Vetor com o nome dos botoes, NORMAL1 e NORMAL2 sao excecoes pois causam conflito ao usar um map
const vector<string> optNames{
"INICIAR", "NORMAL1", "RAPIDO", "TURBO",
"20x10", "30x15", "50x25", "Cores1", "Cores2",
"Cores3", "NORMAL2", "BEBADO", "SAIR"};
//	Map usado para representar o esquema de cores selecionado
unordered_map<string, unordered_map<string, vector<GLfloat>>> colors({
{"Cores1", {{"Box", {0.0, 0.0, 0.0}}, {"BoxBack", {0.0, 0.0, 0.0}}, {"Text", {1.0, 0.0, 0.0}}, {"Background", {1.0, 1.0, 0.0}}, {"Piece", {0.0, 0.0, 0.0}}}},
{"Cores2", {{"Box", {0.015, 0.34, 0.87}}, {"BoxBack", {0.0, 0.0, 0.0}}, {"Text", {0.0, 1.0, 0.0}}, {"Background", {1.0, 1.0, 1.0}}, {"Piece", {0.015, 0.34, 0.87}}}},
{"Cores3", {{"Box", {0.0, 0.0, 0.0}}, {"BoxBack", {0.0, 0.0, 0.0}}, {"Text", {1.0, 1.0, 0.0}}, {"Background", {1.0, 0.0, 0.0}}, {"Piece", {0.0, 0.0, 0.0}}}}
});
//	String que define qual esquema de cores foi selecionado
string cor = (option["Cores1"]) ? "Cores1" : (option["Cores2"]) ? "Cores2" : "Cores3";

// -------- Variaveis do jogo --------

GLfloat spin = 0.0;	//	Define a rotacao do tabuleiro durante o modo bebado
pair<int, int> tam;	//	Define o tamanho do tabuleiro
int vel, altura, alturaOld, pontos;	//	Define a velocidade, altura, altura anterior e pontos respectivamente
Tetris jogo(0), jogoComPecaCaindo(0);	//	Define dois objetos do Tetris
const int possiveisRotacoes[] = {0, 90, 180, 270};	//	Define as rotacoes disponiveis
int larguraJogo, alturaMaximaJogo, alturaPecaAtual, posicaoPecaAtual, rotacaoPecaAtual;	//	Auxiliares
char idPecaAtual, ultimaTecla;	//	Auxiliares