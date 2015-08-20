#include <stdio.h>

#define HORIZONTAL 'h'
#define VERTICAL 'v'
#define DIM 8
typedef enum { false, true } boolean;

/* Tamanho do barco = indice + 1
a[0] = "Hidroaviao"; 	// 2 por player
a[1] = "Submarino";  	// 2 por player
a[2] = "Cruzador";   	// 1 por player
a[3] = "Encouracado";   // 1 por player
a[4] = "Porta Aviao";   // 1 por player
*/
const char *boatDetails[5] = {"Hidroaviao", "Submarino", "Cruzador", "Encouracado", "Porta Aviao"};   

// criando tipo booleano
typedef int bool;
#define true 1
#define false 0

struct Boat {
	int x;   //x e y sao as coordenadas iniciais do barco
	int y;
	int size;
	char direction;  //h: horizontal, v: vertical
	boolean sunken;     // true: navio afundado
};

struct Player{
	struct Boat boats[5];
	boolean currentPlayer;  //define qual o player que estÃ¡ atacando.
	char matrixBoats[8][8];   //matriz de barcos
	char matrixShots[8][8]; //usada quando adcionado a segunda matriz de led
	int playerIndex;	//p1 ou p2
	int countHidro;
        int countSub;
	int countCruz;
	int countEnc;
	int countPA;
	int countShots;  //pra sabermos quantos tiros o player efetuou
	int availableBoats;  //quantidade de barcos no tabuleiro
};

static const struct Boat emptyBoat;
static const struct Player emptyPlayer;
static const char emptyMatrix[8][8];

//function declaratioins
void fillEmptyPlayer(struct Player *player, int *playerIndex);
void  clearMatrix(char matrix[8][8]);
void printMatrix(char matrix[8][8]);
void printPlayerDetails(struct Player player);
void addBoat(struct Player *player,int x, int y, int size, char direction);
void printBoatDetails(struct Boat boat);
void incrementBoatCount(struct Player *player, int boatSize);
void decrementBoatCount(struct Player *player, int boatSize);
void fillBoatMatrix(char matrix[8][8], struct Boat boat);
boolean isBoatAvailable(struct Player player);

//variable declarations
int playerIndex = 1;

int main (int argc, char** argv)
{
    //struct Boat nullBoat = {-1,-1,0,HORIZONTAL,true};	
    //struct Player p1 =  {nullBoat, true, emptyMatrix,emptyMatrix, 1, 0, 0, 0, 0, 0, 0, 0};	
    //struct Player p1 = emptyPlayer;
    struct Player p1;
    //p1.currentPlayer = true;
    fillEmptyPlayer(&p1, &playerIndex);
    printPlayerDetails(p1);
    
    struct Player p2 = emptyPlayer;
    //p2.currentPlayer = false;
    fillEmptyPlayer(&p2, &playerIndex);
    /*printPlayerDetails(p2);*/
	   
    addBoat(&p1,1,1,2,VERTICAL);
    printBoatDetails(p1.boats[p1.availableBoats -1]);	
    printPlayerDetails(p1);
    isBoatAvailable(p1);
    return (0);
}


void addBoat(struct Player *player,int x, int y, int size, char direction){
    
    struct Boat boat = {x,y,size,direction,false};	
    player->boats[player->availableBoats] = boat;
    player->availableBoats ++;
    incrementBoatCount(player,size);
    fillBoatMatrix(player->matrixBoats, boat);
}


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
void fillEmptyPlayer(struct Player *player, int *playerIndex){

    if (*playerIndex == 1){
        player->currentPlayer = true; 
    } else {
        player->currentPlayer = false;    
    }
    clearMatrix(player->matrixBoats);
    clearMatrix(player->matrixShots);
    player->playerIndex = *playerIndex;
    player->countHidro = 0;
    player->countSub = 0;
    player->countCruz = 0;
    player->countEnc = 0;
    player->countPA = 0;
    player->countShots = 0;
    player->availableBoats = 0;
    *playerIndex = *playerIndex + 1; 	    
}

//testado
void clearMatrix(char matrix[8][8]){
  for (int row = 0; row < DIM; row++) {
    for (int col = 0; col < DIM ; col++) {  
      matrix[row][col] = 'A';
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
    printf("player.matrixShots: \n"); 
    printMatrix(player.matrixShots);
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
    printf("Direction: %s\n", boat.direction == 'h'? "Horizontal": "Vertical"); 
    printf("Is sunken? %s\n", boat.sunken == 1 ? "Yes" : "NO");   
}

//testado
//Imprime matriz após marcação dos barcos pelo jogador
void fillBoatMatrix(char matrix[8][8], struct Boat boat){
	if (boat.direction == HORIZONTAL){
		for (int i = boat.x; i<=boat.size+boat.x-1; i++ )
		{matrix[boat.y][i]='B';
		}
	}
	else if (boat.direction == VERTICAL){
		for (int i = boat.y; i<=boat.size+boat.y-1; i++ )
		{matrix[i][boat.x]='B';
		}
	}
}

//valida antes da inserção do barco se este pode ser inserido
boolean isBoatAvailable(struct Player player){
bool insert = false;

	if(player.availableBoats < 5){
		for (int i=0; i<5; i++){
				if ((player.boats[i].size==1) && ((player.countHidro >= 0)&&(player.countHidro <= 2))) { // valida se o jogador pode inserir hidroaviao
						printf("hidroaviao pode ser inserido");
						insert = true;
				}
				else if  ((player.boats[i].size==2) && ((player.countSub >= 0)&&(player.countSub <= 2))) { // valida se o jogador pode inserir submarino
					printf("submarino pode ser inserido");
					insert = true;
				}
				else if  ((player.boats[i].size==3) && (player.countCruz == 0)){ // valida se o jogador pode inserir cruzador
					printf("cruzador pode ser inserido");
					insert = true;
				}
				else if  ((player.boats[i].size==4) && (player.countEnc == 0)) { // valida se o jogador pode inserir encourado
					printf("encourados pode ser inserido");
					insert = true;
				}
				else if ((player.boats[i].size==5) && (player.countPA ==0)) { // valida se o jogador pode inserir porta aviao
					printf("porta aviao pode ser inserido");
					insert = true;
				}
				else {
					insert = false;
				}
		}
	}
	return insert;
}




