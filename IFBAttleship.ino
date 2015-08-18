#include <GameMatrix.h>


#define HORIZONTAL h
#define VERTICAL v

const char *boatDetails[5];   //tamanho do barco = indice + 1
a[0] = "Hidroaviao"; 	// 2 por player
a[1] = "Submarino";  	// 2 por player
a[2] = "Cruzador";   	// 1 por player
a[3] = "Encouracado";   // 1 por player
a[4] = "Porta Aviao";   // 1 por player


struct Boat {
	int x;   //x e y sao as coordenadas iniciais do barco
	int y;  
	int size;
	char direction;  //h: horizontal, v: vertical
	bool sunken;     // true: navio afundado
};

struct Player{
	struct Boat[5] boats;
	bool currentPlayer;
	char[8][8] matrix;
	int playerIndex;	//p1 ou p2
	int availableBoats;
};

/*variaveis do jogo
char[][] boardP1;
char[][] boardP2;
bool currentAtacker;  // true: player 1 , false: player 2
bool currentDefender; // true: player 1 , false: player 2
Boat[5] boatsP1;   //x= numero do barco, y=tamanho do barco, z = status do barco. 
Boat[5] boatsP2;
//criar classe para barco? atributos: tamanho do barco, coordenadas x,y e status;
*/


Player p1,p2;


void setup(){
  startGame();
  
}

void loop(){
  
}

//configura a inicializaço do jogo
void startGame(){
  p1 =  {null, true, getNewMatrix(), 1, 0};
  p2 =  {null, false, getNewMatrix(), 2, 0};
  startPlayer(P1); //inicializa as matrizes
  startPlayer(P2); 
}

char[8][8] getNewMatrix(){
	//retorna uma matriz 8x8 preenchidas com A's;
}



void startPlayer(Player player){
	startMatrix(Player.matrix); //inicializa as matrizes
}

// funcao que tenta adcionar um barco ao tabuleiro. 
//retorno: true, se barco adcionado com sucesso, false caso contrario
//x,y: posicao inicial, direct: horizontal,vertical, boatSize: tamanho
boolean addBoat(int x, int y, char direct ,int boatSize, Player player){
	if(player.availableBoats >= 5){
		//Print "Quantidade maxima de barcos atingida";
		return false;
	} else if (!isValidBoatSize(int size)){         //checa se o tamanho solicitado e valido
		//Print "tamanho do barco invalido";
		return false;
	} else if (!isBoatAvailable(player, boatSize)){    //checa se o player ainda pode adicionar um barco com o tamanho desejado
		//Print "erro! quantidade de barcos de tamanho boatsize atingida";
		return false;
	} else if (!isValidBoatPlace(x, y, direct , boatSize, player)) {  //checa se barco nao sobrepoe outro ou ultrapassa limites da matriz
		//Print "erro! Posicionamento do barco invalido";
		return false;
	} else {   //adcionar barco
		addBoatToMatrix(x, y, direct , boatSize, player.matrix);
		addBoatToPlayerBoats(x, y, direct , boatSize, player);
	}


}

//testa se o player ainda pode adcionar barcos e se o tamanho do barco desejado est disponivel
boolean isBoatAvailable(Player player, int boatSize){
	bool available = false; 
	if(player.availableBoats < 5){
		if ((boatSize < 3) && ((getCountBoardsBySize(player,boatSize)) < 2)) { //barcos de tamanho 1 ou 2: dois por player
			available = true;
		} else if ((boatSize >= 3) && ((getCountBoardsBySize(player,boatSize)) < 1)) { //barcos de tamanho  3,4 ou 5: um por player
			available = true;
		}
	}
	return available
}

bool isValidBoatSize(int size){
	return ((size > 0) && (size <= 5));
}

//checa se pode adcionar um barco na posicao desejada
// checa se nao ultrapassa os limites da matriz e se não sobrepoe outro barco
bool isValidBoatPlace(int x, int y, char direct ,int boatSize, Player player){
	
	if ((x < 1 ) || (x > 8 ) || (y < 1 ) || (y > 8 )) {
		return false;
	} 
	switch (direction){
		case 'h':
			for (int i = x; i < (x + boatSize -1); i++){
				if(player.matrix[i][y] == 'B'){  // sobrepondo um barco
					return false;
					break;	
				}
			}
			return true;
			break;
		case 'v':
			for (int i = y; i < (y + boatSize -1); i++){
				if(matrix[x][i] == 'B'){
					return false;   // sobrepondo um barco
					break;	
				}
			}
			return true;
			break;
	}
	return true;
}

void addBoatToMatrix(int x, int y, char direct ,int boatSize, char matrix[8][8]) {
	switch (direction){
		case 'h':
			for (int i = x; i < (x + boatSize -1); i++){
				matrix[i][y] = 'B')  // adcionando o barco a matriz
			}
			break;
		case 'v':
			for (int i = y; i < (y + boatSize -1); i++){
				matrix[x][i] = 'B')  // adcionando o barco a matriz
			}
			break;
	}
}

void addBoatToPlayerBoats(int x, int y, char direct ,int boatSize,  Player player){
	 player.boats[player.availableBoats] = {x, y, boatSize, direct, false} //adciona o barco ao player.boats
	 player.availableBoats ++;
}


//algoritmo para escolha de quem começa a jogar
int chooseFirstPlayer(){
	long p1Number = 0L;
	long p2Number = 0L;

	while (p1Number == p2Number) {
		escreve("player 1 ready?");
		while (digitalRead(buttonPlayer1) == LOW) {
			mostraNumeroDisplay(1,p1Number);
		}
		// mostra o numero obtido pelo p1:
		piscaNumeroDisplay(1, p1Number);

		escreve("player 2 ready?");
		while (digitalRead(buttonPlayer2) == LOW) {
			mostraNumeroDisplay(2,p2Number);
		}
		// mostra o numero obtido pelo p2:
		piscaNumeroDisplay(2, p2Number);

		if (p1Number == p2Number){
			escreve("Empate!");
		}
	}
	if (p1Number > p2Number) {
		escreve("player 1 comeca!");
		p1.currentPlayer = true;
		p2.currentPlayer = false;
	} else {
		escreve("player 2 comeca!");
		p2.currentPlayer = true;
		p1.currentPlayer = false;
	} 
}

void generateAndShowNumber(long number, int player){
	randomSeed(analogRead(0));
	number = random(10);
	//MOSTRA O NUMERO NO DISPLAY:
	mostraNumeroDisplay(player, number);
}

void mostraNumeroDisplay(int display, long numero){
	PrintDisplay(display,numero);
	delay(10);
	//clearDisplay();
}
void piscaNumeroDisplay(int display, long numero){
	for (int i = 0; i < 5; i++) {
		PrintDisplay(display,numero);
		delay(1000);
		clearDisplay();
	}
}

//funcao para ataque: retorna true se atingir um barco
boolean attack(int x, int y) {

}

//retorna true se o jogo terminou
boolean gameFinished(){

}

//funcao para mudar o jogador corrente
void changeCurrentPlayer(){

}
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX ESBOÇO 02: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX




//testa se o navio afundou
boolean isSunkenShip(Boat boat, char matrix[8][8]){
	if (!boat.sunken){
		switch (boat.direction){
			case 'h':
				for (int i = boat.x; i < (boat.x + boat.size); i++){
					if(matrix[i][boat.y] == 'B'){
						//boat.sunken = false;
						return false;
						break;	
					}
				}
				boat.sunken = true;
				return boat.sunken;
				break;
			case 'v':
				for (int i = boat.y; i < (boat.y + boat.size); i++){
					if(matrix[boat.x][i] == 'B'){
						//boat.sunken = false;
						return false;
						break;	
					}
				}
				boat.sunken = true;
				return boat.sunken;
				break;
		}
	}
	return boat.sunken;
}

// testa se o dado ponto x,y pertence a algum barco retornando o indice do mesmo. -1 se ponto nao pertence a nenhum barco
int getShipIndexByGivenPoint(int x, int y, Boat[5] boats) {
	for int (k =0; k < 5; k++){
		switch (boat[k].direction){
			case 'h':
				for (int i = boat[k].x; i < (boat[k].x + boat[k].size); i++){
					if((x == i) && (y == boat[k].y)){
						return k;
						break;	
					}
				}
				break;
			case 'v':
				for (int i = boat[k].y; i < (boat[k].y + boat[k].size); i++){
					if((x == boat[k].x) && (y == i)){
						return k;
						break;	
					}
				}
				break;
		}
	}
	return -1   //boat not found!
}


// testa se o tiro acertou um barco
boolean fire(int x, int y, char matrix[8][8]){
		bool fired = false;
		if (matrix[x][y] == 'B') {
			fired = true;
			matrix[x][y] == 'C';    //acertou o tiro!
		} else if (matrix[x][y] == 'A') {
			matrix[x][y] == 'E';    //errou o tiro!
		}

		return fired;
}

boolean noMoreBoats(Boat[5] boatsPX){
	for (int i = 0; i < 5; i++){
		if (boat[i].sunken == false) {   //se ainda ha barcos nao afundados, retorna false.
			return false;
		}
	}
	return true;   //todos os barcos foram afundados
}

 boolean isGameOver(Boat[5] boatsPX){
 	return noMoreBoats(boatsPX);
 }

 void changeCurrentPlayer(){
 	p1.currentPlayer = !p1.currentPlayer;
  	p2.currentPlayer = !p2.currentPlayer;	
 }

Player getCurrentPlayer(){
	return p1.currentPlayer ? p1 : p2; 
}

Player getCurrentDefender(){
	return p1.currentPlayer ? p2 : p1; 
}

// retorna a quantidade de barcos com tamanho igual ao passado como parametro
int getCountBoardsBySize(Player player, int boatSize){
	int count = 0;
	for (int i = 0; i < 5; i++) {
		if (player.boats[i].size == boatSize) {
			count ++;
		}
	} 
	return count;
}



// trecho do codigo
	/*   fire(x,y,matrixPX) testa se o tiro acertou um barco
	*	 getShipByGivenPoint(x,y,boatsPX) retorna o barco correspondente ao ponto
	*	 isSunkenShip(boat,matrixPX) testa se o barco afundou
	*/
     if ((fire(x,y,matrixPX)){
     	//Print "acertou o tiro!"
     	if (isSunkenShip(boatsPX[getShipByGivenPoint(x,y,boatsPX)])){
     		//Print "Navio afundou!"
     		if(isGameOver){

     		}
     	}
     } && ){

     }






