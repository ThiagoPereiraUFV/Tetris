using namespace std;

//	Funcao utilizada para rotacionar o tabuleiro no modo bebado
void spinDisplay(const int x) {
	spin = spin + 5.0;
	if(spin > 360.0)
		spin = spin - 360.0;
	glutTimerFunc(100, spinDisplay, x);
	glutPostRedisplay();
}

//	Funcao utilizada para desenhar um quadrado dada uma posicao e um caractere
void exibeObjeto(const GLint x, const GLint y, const char c) {
	if(c == ' ') {
		glColor3f(1.0-colors[cor]["Piece"][0], 1.0-colors[cor]["Piece"][1], 1.0-colors[cor]["Piece"][2]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glColor3f(colors[cor]["Piece"][0], colors[cor]["Piece"][1], colors[cor]["Piece"][2]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	glPushMatrix();
		if(option["BEBADO"])
			glRotatef(spin, 0.0, 0.0, 1.0);
		glTranslatef(-larguraJogo*view_h/alturaMaximaJogo + x*2*(GLfloat(view_h/alturaMaximaJogo)), -view_h + y*2*(GLfloat(view_h/alturaMaximaJogo)), 0);
		glRectf(0, 0, 2*view_h/alturaMaximaJogo, 2*view_h/alturaMaximaJogo);
	glPopMatrix();
}

//	Funcao utilizada para desenhar o estado atual do tabuleiro do jogo
void exibeJogo() {
	for(int i = 0; i < alturaMaximaJogo; i++)
		for(int j = 0; j < larguraJogo; j++)
			exibeObjeto(j, alturaMaximaJogo-i-1, jogoComPecaCaindo.get(j, alturaMaximaJogo-i-1));
}

//	Funcao utilizada para renderizar o frame atual do jogo e posicionar uma peca
void renderGameFrame() {
	glClear (GL_COLOR_BUFFER_BIT);
	if(jogoComPecaCaindo.getAltura() > alturaMaximaJogo) {
		const string p = "PONTUACAO: " + to_string(pontos);
		drawText(-(p0.first+p1.first)/2 - view_h*0.35, view_h*0.3, view_h*0.0008, view_h*0.0008, "VOCE PERDEU!");
		drawText(-(p0.first+p1.first)/2 - view_h*0.35, view_h*0.1, view_h*0.0008, view_h*0.0008, p);
		state = 2;
		gameRunning = 0;
		return;
	}
	jogoComPecaCaindo = jogo;

	if(ultimaTecla == 'l') { 			
		Tetris jogoTeste = jogoComPecaCaindo; 			
		if(jogoTeste.adicionaForma(posicaoPecaAtual-1, alturaPecaAtual, idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
			posicaoPecaAtual--;
	}
	else	if(ultimaTecla == 'r') {
				Tetris jogoTeste = jogoComPecaCaindo; 			
				if(jogoTeste.adicionaForma(posicaoPecaAtual+1, alturaPecaAtual, idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
					posicaoPecaAtual++;
			}
			else	if(ultimaTecla == 's') {
						Tetris jogoTeste = jogoComPecaCaindo; 			
						if(jogoTeste.adicionaForma(posicaoPecaAtual, alturaPecaAtual, idPecaAtual, possiveisRotacoes[(rotacaoPecaAtual+1)%4]))
							rotacaoPecaAtual = (rotacaoPecaAtual+1)%4;
			}

	if(jogoComPecaCaindo.adicionaForma(posicaoPecaAtual, alturaPecaAtual-1, idPecaAtual, possiveisRotacoes[rotacaoPecaAtual])) {
		alturaPecaAtual--;
	}
	else {
		jogo.adicionaForma(posicaoPecaAtual, alturaPecaAtual, idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]);
		jogoComPecaCaindo = jogo;
		idPecaAtual = "IJLOSTZ"[rand()%7];
		posicaoPecaAtual = larguraJogo/2-2;
		alturaPecaAtual = alturaMaximaJogo;
		rotacaoPecaAtual = rand()%4;
		alturaOld = jogoComPecaCaindo.getAltura();
		jogoComPecaCaindo.removeLinhasCompletas();
		altura = jogoComPecaCaindo.getAltura();
		if(altura != alturaOld)
			pontos++;	
		jogo = jogoComPecaCaindo;
	}
	exibeJogo();
	if(ultimaTecla == 'a')
		usleep(vel-vel*0.8);
	else
		usleep(vel);
	ultimaTecla = ' ';
}

//	Funcao utilizada para configurar inicializar o tamanho do tabuleiro
void configGame() {
	alturaMaximaJogo = tam.first;
	larguraJogo = tam.second;
	jogo = Tetris(larguraJogo);
	jogoComPecaCaindo = Tetris(larguraJogo);

	alturaPecaAtual = alturaMaximaJogo;
	idPecaAtual = "IJLOSTZ"[rand()%7];
	posicaoPecaAtual = larguraJogo/2-2;
	alturaPecaAtual = alturaMaximaJogo;
	rotacaoPecaAtual = 0;
	pontos = 0;
}

//	Funcao utilizada para determinar o tamanho desejado do tabuleiro, alem da velocidade e o modo bebado
void configVars() {
	if(option["20x10"]) {
		tam = make_pair(20, 10);
		if(option["NORMAL1"])
			vel = 200000;
		else	if(option["RAPIDO"])
					vel = 80000;
				else
					vel = 60000;
	}
	else	if(option["30x15"]) {
				tam = make_pair(30, 15);
				if(option["NORMAL1"])
					vel = 80000;
				else	if(option["RAPIDO"])
							vel = 40000;
						else
							vel = 30000;
					}
			else {
				tam = make_pair(50, 25);
				if(option["NORMAL1"])
					vel = 40000;
				else	if(option["RAPIDO"])
							vel = 20000;
						else
							vel = 15000;
			}
	if(option["BEBADO"]) {
		spin = 0.0;
		glutTimerFunc(100, spinDisplay, 0);
	}
}