#include <stdio.h>
#include <ctype.h>

#define HORIZONTAL 'H'
#define VERTICAL 'V'
#define AGUA 'A' 
#define BARCO 'B'  
#define TIRO_CERTO 'C'
#define TIRO_ERRADO 'E'
#define DIM 8
#define QTD_PLAYERS 2
#define MAX_BOATS 2

//typedef int bool;
typedef enum { false, true } boolean;

// criando tipo bool
typedef int bool;
#define true 1
#define false 0

/* Tamanho do barco = indice + 1
a[0] = "Hidroaviao";     // 2 por player
a[1] = "Submarino";      // 2 por player
a[2] = "Cruzador";       // 1 por player
a[3] = "Encouracado";   // 1 por player
a[4] = "Porta Aviao";   // 1 por player
*/
const char *boatDetails[5] = {"Hidroaviao", "Submarino", "Cruzador", "Encouracado", "Porta Aviao"};   


struct Boat {
    int x;   //x e y sao as coordenadas iniciais do barco
    int y;
    int size;
    char direction;  //H: horizontal, V: vertical
    bool sunken;     // true: navio afundado
};

struct Player{
    struct Boat boats[MAX_BOATS];
    bool currentPlayer;  //define qual o player que est√° atacando.
    char matrixBoats[DIM][DIM];   //matriz de barcos
    char matrixShots[DIM][DIM]; //usada quando adcionado a segunda matriz de led
    int playerIndex;    //p1 ou p2
    int countHidro;
    int countSub;
    int countCruz;
    int countEnc;
    int countPA;
    int countShots;  //pra sabermos quantos tiros o player efetuou
    int availableBoats;  //quantidade de barcos no tabuleiro
};

//function declaratioins
void startGame();
void initializePlayer(struct Player *player, int *playerIndex);
bool addBoat(struct Player *player,int x, int y, int size, char direction, char **message);
bool isValidBoatSize(int boatSize);
bool isBoatAvailable(struct Player player, int boatSize);
bool isValidBoatPlace(int x, int y, int boatSize, char direction , struct Player player);
void addBoatToMatrix(char matrix[DIM][DIM], struct Boat boat);
void incrementBoatCount(struct Player *player, int boatSize);
void decrementBoatCount(struct Player *player, int boatSize);
void ResetMatrix(char matrix[DIM][DIM]);
void printMatrix(char matrix[DIM][DIM]);
void printPlayerDetails(struct Player player);
void printBoatDetails(struct Boat boat);
bool verifyDirection(char direction);
boolean fire(int x, int y, char matrix[8][8]);

//variable declarations
int playerIndex;
char *message;
struct Player players[QTD_PLAYERS]; //array de jogadores

int main (int argc, char** argv)
{
    playerIndex = 1;
    message = "";
    int x,y;
    startGame();
    printf("\nTodos os barcos foram adcionados! quantidade de players: %d. Hora de comecar o jogo!!!\n", playerIndex);
    
	printf("Player %d digite a posicao X do tiro: ",players[0].currentPlayer ? 1:2);
    scanf("%d", &x);
    printf("Player %d digite a posicao Y do tiro: ",players[0].currentPlayer ? 1:2);
    scanf("%d", &y);
    printf("[X: %d] [Y: %d] \n", x, y);
    if (fire(x,y, players[1].matrixBoats)){
    	printf("ACERTOU!!!!!!!!");
    	printPlayerDetails(players[1]);
	}
	else{
		printf("ERROU!!!!!!!!");
	}
    return (0);
}

//testado
void startGame(){
    for (int i = 0; i < QTD_PLAYERS; i++) {
        initializePlayer(&players[i], &playerIndex);
        printPlayerDetails(players[i]);    
        while (players[i].availableBoats < MAX_BOATS) {
            int x,y,boatSize;
            char direction;  
            printf("\nDigite a posicao X inicial do barco %d (0-%d): ", players[i].availableBoats + 1, MAX_BOATS);
            scanf("%d", &x);
            printf("Digite a posicao Y inicial do barco %d (0-%d): ", players[i].availableBoats + 1, MAX_BOATS );
            scanf("%d", &y);
            printf("Digite o tamanho do barco %d (1-5): ", players[i].availableBoats + 1);
            scanf("%d", &boatSize);
            printf("Digite a direcao do barco %d (H: horizontal,V: vertical): ", players[i].availableBoats + 1 );
            scanf(" %c", &direction);
            direction = toupper(direction);
            printf("[X: %d] [Y: %d] [size: %d] [direction: %s]\n", x, y, boatSize, direction == HORIZONTAL ? "Horizontal" : "Vertical");
			
            //add barco    
            bool add = addBoat(&players[i], x, y, boatSize, direction, &message);
            printf("message: %s\n", message); 
            if (add) {
                printBoatDetails(players[i].boats[players[i].availableBoats -1]);    
                printPlayerDetails(players[i]);
            }
        }
    } 
}

//testado
void initializePlayer(struct Player *player, int *playerIndex){

    if (*playerIndex == 1){
        player->currentPlayer = true; 
    } else {
        player->currentPlayer = false;    
    }
    ResetMatrix(player->matrixBoats);
    ResetMatrix(player->matrixShots);
    player->playerIndex = *playerIndex;
    player->countHidro = 0;
    player->countSub = 0;
    player->countCruz = 0;
    player->countEnc = 0;
    player->countPA = 0;
    player->countShots = 0;
    player->availableBoats = 0;
    if(*playerIndex < QTD_PLAYERS) {
        *playerIndex = *playerIndex + 1;         
    }
}

//testado
bool addBoat(struct Player *player,int x, int y, int boatSize, char direction, char **message) {
    bool add = false;
    if(player->availableBoats >= MAX_BOATS) {
        *message = "erro! Quantidade maxima de barcos atingida";
    } else if (!isValidBoatSize(boatSize)) {     
        *message = "erro! tamanho do barco invalido";
    } else if (!isBoatAvailable(*player, boatSize)) {     
        *message = "erro! Quantidade de boatDetails[size -1] atingida";
    } else if (!isValidBoatPlace(x, y, boatSize, direction, *player)) {  //checa se barco nao sobrepoe outro ou ultrapassa limites da matriz CRIAR ESSE METODO!!
        *message = "erro! Posicionamento do barco invalido";
    } else if (!verifyDirection(direction)){
    	*message = "erro! Direcao invalida!";
	}
	else{   //adcionar barco        
        struct Boat boat = {x,y,boatSize,direction,false};    
        player->boats[player->availableBoats] = boat;
        player->availableBoats ++;
        incrementBoatCount(player,boatSize);
        addBoatToMatrix(player->matrixBoats, boat);
        add = true;
        *message = "barco adcionado com sucesso!";
    }
    return add; 
}

bool verifyDirection(char direction){
	if ((direction!=HORIZONTAL) && (direction!=VERTICAL)){
		return false;
	}
	return true;
}

//testado
// testa se o tamanho do barco e valido
bool isValidBoatSize(int boatSize){
    return ((boatSize > 0) && (boatSize <= 5));
}
//testado
//testa se o player ainda pode adcionar barcos e se o tamanho do barco desejado est disponivel
bool isBoatAvailable(struct Player player, int boatSize){
    bool available = false;     
    switch(boatSize) {
        case 1:
              return (player.countHidro < 2);  //se o jogador tem menos que dois hidros, returna true!
              break;
        case 2:
              return (player.countSub < 2);  //se o jogador tem menos que dois Sub, returna true!
              break;
        case 3:
              return (player.countCruz < 1);  //se o jogador nao tem nenhum Cruzeiro, returna true! 
              break;
        case 4:
              return (player.countEnc < 1);  //se o jogador nao tem nenhum encouracado, returna true! 
              break;
        case 5:
              return (player.countPA < 1);  //se o jogador nao tem nenhum porta avioes, returna true! 
              break;
    }
    return available;
}

//testado
//checa se pode adcionar um barco na posicao desejada
// checa se nao ultrapassa os limites da matriz e se n„o sobrepoe outro barco
bool isValidBoatPlace(int x, int y, int boatSize, char direction , struct Player player){
    
    //checa se nao ultrapassa os limites da matriz
    if ((x < 0) || (x > 7) || (y < 0) || (y > 7)) {
        return false;
    } else if (((direction == HORIZONTAL) && (x + boatSize > 8)) || ((direction == VERTICAL) && (y + boatSize > 8))) {
        return false;
    } 
    //checa se nao sobrepoe outro barco 
    switch (direction){
        case HORIZONTAL:
            for (int i = x; i < (x + boatSize); i++){
                if(player.matrixBoats[y][i] == BARCO){  // sobrepondo um barco // if(player.matrixBoats[i][y] == 'B'){
                    return false;
                    break;    
                }
            }
            return true;
            break;
        case VERTICAL:
            for (int i = y; i < (y + boatSize); i++){
                if(player.matrixBoats[i][x] == BARCO){   //if(player.matrixBoats[x][i] == 'B'){
                    return false;   // sobrepondo um barco
                    break;    
                }
            }
            return true;
            break;
    }
    return true;
}


//testado
//Adciona na matriz, o barco. necessario fazer validacao se È possivel adcionar antes.
void addBoatToMatrix(char matrix[8][8], struct Boat boat) {
    if (boat.direction == HORIZONTAL){
        for (int i = boat.x; i <= boat.size+boat.x-1; i++ ) {
            matrix[boat.y][i] = BARCO;
        }
    }
    else if (boat.direction == VERTICAL){
        for (int i = boat.y; i <= boat.size+boat.y-1; i++ ) {
            matrix[i][boat.x] = BARCO;
        }
    }
}

//testado
void incrementBoatCount(struct Player *player, int boatSize){
    switch(boatSize){
       case 1:
             player->countHidro ++;
             break;

       case 2:
             player->countSub ++;
             break;

       case 3:
             player->countCruz ++;
             break;

       case 4:
             player->countEnc ++;
             break;

       case 5:
             player->countPA ++;
             break;
    }
}

void decrementBoatCount(struct Player *player, int boatSize){
    switch(boatSize){
       case 1:
             player->countHidro --;
             break;

       case 2:
             player->countSub --;
             break;

       case 3:
             player->countCruz --;
             break;

       case 4:
             player->countEnc --;
             break;

       case 5:
             player->countPA --;
             break;
    }
}

//testado
void ResetMatrix(char matrix[8][8]){
  for (int row = 0; row < DIM; row++) {
    for (int col = 0; col < DIM ; col++) {  
      matrix[row][col] = AGUA;
    }
  }
}

//testado
void printMatrix(char matrix[8][8]){
    printf("[ ");
    for (int row = 0; row < DIM; row++) {
      for (int col = 0; col < DIM ; col++) {  
          printf("%c", matrix[row][col]);
          if((row < DIM -1) || (col < DIM -1)){
              printf(",");
          }
      }
      if (row < DIM -1) {
          printf("\n  ");
      }
    }
    printf(" ]\n");  
}

//testado
void printPlayerDetails(struct Player player){

    printf("Player %d details: \n", player.playerIndex);
    printf("currentPlayer: %s\n", player.currentPlayer == 1 ? "Yes" : "NO");
    printf("player.playerIndex: %d\n", player.playerIndex);
    printf("player.matrixBoats: \n"); 
    printMatrix(player.matrixBoats);
   /* printf("player.matrixShots: \n"); 
    printMatrix(player.matrixShots);*/
    printf("player.countHidro: %d\n", player.countHidro);
    printf("player.countSub: %d\n", player.countSub);
    printf("player.countCruz: %d\n", player.countCruz);
    printf("player.countEnc: %d\n", player.countEnc);
    printf("player.countPA: %d\n", player.countPA);
    printf("player.countShots: %d\n", player.countShots);
    printf("player.availableBoats: %d\n", player.availableBoats);
}

//testado
void printBoatDetails(struct Boat boat){

    printf("Boat details: \n");
    printf("Position X0: %d\n", boat.x);
    printf("Position Y0: %d\n", boat.y);
    printf("Size: %d\n", boat.size); 
    printf("Tipe: %s\n", boatDetails[boat.size-1]); 
    printf("Direction: %s\n", boat.direction == HORIZONTAL ? "Horizontal" : "Vertical"); 
    printf("Is sunken? %s\n", boat.sunken == 1 ? "Yes" : "NO");   
}

//testa se acertou ou errou o tiro
boolean fire(int x, int y, char matrix[8][8]){
		bool fired = false;
		if (matrix[y][x] == 'B') {
			fired = true;
			matrix[y][x] = 'C';    //acertou o tiro!
		} else if (matrix[y][x] == 'A') {
			matrix[y][x] = 'E';    //errou o tiro!
		}
		printf("TESTE TIRO %c \n", matrix[y][x]);
  printPlayerDetails(players[1]);
		return fired;
}



