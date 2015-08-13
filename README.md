# IFBattleship
IFBattleship is a navy battle puzzle for arduino


jogo: usar uma matriz de char [8][8] para mapear o tabuleiro.
		caracteres usados:

		A = agua
		B = barco
		C = Tiro_certo
		E = Tiro_errado


		- inicialmente a matriz contem apenas A's, pois ainda nao foram adcionados os barcos nem foram disparados os tiros;
		- O jogador vai acionar o método adcionarBarco() passando os parametros:
				OPÇAO 1:  passar posicao inicial do barco na matriz, tamanho do barco e direção;
				OPÇAO 2: usar o algoritmo definido nos requisitos do trabalho: definir posicao inicial(x0,y0) e final(x1,y1);
			# posicao inicial: referencial sempre da esquerda para a direita e de cima para baixo;
			# tamanho do barco: um, dois ou tres espaços;
			# direcao: barco na horizontal ou na vertical do tabuleiro;

			validações:	
			$ checar se barco pode ser alocado no espaço desejado, se nao está sobrepondo outro barco ou ultrapassando o limite do tabuleiro;
			$ checar se o jogador, quando tentar adicionar um barco, ainda tem barco do tamanho desejado disponivel. Ex: se ele ja tiver 2 hidroavioes no tabuleiro ele nao 	pode adcionar outro barco de tamanho 1.
			$ checar se o jogador ja adcionou todos os 7 avioes;

		- terminado os dois jogadores de adcionar seus barcos, devemos escolher quem ataca primeiro;
			# definir algoritmo para escolha de quem joga primeiro. random? sugestao, um display mostrando numeros bem rapido e o jogador aperta o botao, 
				quem tirar o numero maior começa.

		- escolhido quem começa, inicia-se a batalha;
			# alternadamente cada jogador seleciona uma posicao no tabuleiro e atira;
			
			validações:
			$ acertou um barco? altera o valor na matriz de A para C; apaga os leds referentes ao barco atingido
			$ errou o tiro? altera o valor de B para D;
			$ checar se o jogo acabou. 
				DEFINIR ALGORITMO:
					1) Ainda existe algum A na matriz?
					2) usar contadores pra a quantidade de barcos e decrementar esse contador a cada acerto( + eficiente); 
			$ se jogo nao acabou, passa a vez para o outro jogador
			S se jogo terminou, exibir mensagem de fim e vencedor;

			%%DUVIDA: vamos usar duas matrizes? se sim, a segunda matriz vai mostrar aonde o player ja atirou, informando:
				* led aceso: tiro já efetuado naquele local e acertou um barco
				* led piscando: tiro já efetuado naquele local e atingiu a água (arduino suporta thread???)
				* led apagado: ainda nao foi disparado um tiro naquele local


		Comunicação entre os players:
		- usar transmissor para trafegar informacoes: adcionado todos os barcos do player, aonde o player atirou


		diferenciais que podemos adcionar:
		acertou um barco? led referente ao barco pisca antes de apagar e emite um som;
		errou o tiro? o led do local aonde foi atirado acende e apaga lentamente(fade, usar a funcao analogWrite!)
		
