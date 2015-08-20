#include <stdio.h>

#define HORIZONTAL 'h'
#define VERTICAL 'v'
#define DIM 8

//typedef int bool;
typedef enum { false, true } boolean;

// criando tipo boolo
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
    char direction;  //h: horizontal, v: vertical
    bool sunken;     // true: navio afundado
};

struct Player{
    struct Boat boats[5];
    bool currentPlayer;  //define qual o player que estÃ¡ atacando.
    char matrixBoats[8][8];   //matriz de barcos
    char matrixShots[8][8]; //usada quando adcionado a segunda matriz de led
    int playerIndex;    //p1 ou p2
    int countHidro;
    int countSub;
    int countCruz;
    int countEnc;
    int countPA;
    int countShots;  //pra sabermos quantos tiros o player efetuou
    int availableBoats;  //quantidade de barcos no tabuleiro
};
/*
static const struct Boat emptyBoat;
static const struct Player emptyPlayer;
static const char emptyMatrix[8][8];*/

//function declaratioins
void fillEmptyPlayer(struct Player *player, int *playerIndex);
void ResetMatrix(char matrix[8][8]);
void printMatrix(char matrix[8][8]);
void printPlayerDetails(struct Player player);
void printBoatDetails(struct Boat boat);
bool addBoat(struct Player *player,int x, int y, int size, char direction, char **mensagem);
bool isValidBoatSize(int boatSize);
bool isBoatAvailable(struct Player player, int boatSize);
bool isValidBoatPlace(int x, int y, int boatSize, char direction , struct Player player);
void addBoatToMatrix(char matrix[8][8], struct Boat boat);
void incrementBoatCount(struct Player *player, int boatSize);
void decrementBoatCount(struct Player *player, int boatSize);
//bool isBoatAvailable(struct Player player);
//variable declarations
int playerIndex;
char *mensagem;

int main (int argc, char** argv)
{
    playerIndex = 1;
    mensagem = "";
    //struct Boat nullBoat = {-1,-1,0,HORIZONTAL,true};    
    //struct Player p1 =  {nullBoat, true, emptyMatrix,emptyMatrix, 1, 0, 0, 0, 0, 0, 0, 0};    
    //struct Player p1 = emptyPlayer;
    struct Player p1;
    //p1.currentPlayer = true;
    fillEmptyPlayer(&p1, &playerIndex);
    printPlayerDetails(p1);
    
    //struct Player p2 = emptyPlayer;
    struct Player p2;
    //p2.currentPlayer = false;
    fillEmptyPlayer(&p2, &playerIndex);
    /*printPlayerDetails(p2);*/
     
    //add barco 1   
    bool add = addBoat(&p1,0,3,3,HORIZONTAL, &mensagem);
    printf("mensagem: %s\n", mensagem); 
    if (add) {
        printBoatDetails(p1.boats[p1.availableBoats -1]);    
        printPlayerDetails(p1);
    }
    //add barco 2
    add = addBoat(&p1,5,3,3,VERTICAL, &mensagem);
    printf("mensagem: %s\n", mensagem); 
    if (add) {
        printBoatDetails(p1.boats[p1.availableBoats -1]);    
        printPlayerDetails(p1);
    }
    return (0);
}

//testado
bool addBoat(struct Player *player,int x, int y, int boatSize, char direction, char **mensagem){
    bool add = false;
    if(player->availableBoats >= 5) {
        *mensagem = "erro! Quantidade maxima de barcos atingida";
    } else if (!isValidBoatSize(boatSize)) {     
        *mensagem = "erro! tamanho do barco invalido";
    } else if (!isBoatAvailable(*player, boatSize)) {     
        *mensagem = "erro! Quantidade de boatDetails[size -1] atingida";
    } else if (!isValidBoatPlace(x, y, boatSize, direction, *player)) {  //checa se barco nao sobrepoe outro ou ultrapassa limites da matriz CRIAR ESSE METODO!!
        *mensagem = "erro! Posicionamento do barco invalido";
    } else {   //adcionar barco        
        struct Boat boat = {x,y,boatSize,direction,false};    
        player->boats[player->availableBoats] = boat;
        player->availableBoats ++;
        incrementBoatCount(player,boatSize);
        addBoatToMatrix(player->matrixBoats, boat);
        add = true;
        *mensagem = "barco adcionado com sucesso!";
    }
    return add; 
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
// checa se nao ultrapassa os limites da matriz e se não sobrepoe outro barco
bool isValidBoatPlace(int x, int y, int boatSize, char direction , struct Player player){
    
    //checa se nao ultrapassa os limites da matriz
    if ((x < 0) || (x > 7) || (y < 0) || (y > 7)) {
        return false;
    } else if (((direction == HORIZONTAL) && (x + boatSize > 8)) || ((direction == VERTICAL) && (y + boatSize > 8))) {
        return false;
    } 
    //checa se nao sobrepoe outro barco 
    switch (direction){
        case 'h':
            for (int i = x; i < (x + boatSize); i++){
                printf("ENTROU NO FOR H!\n"); 
                printf("---------------\n");
                printf("[X: %d], [Y: %d], [i: %d], {player.matrixBoats[x][i] = %c}\n", x, y, i, player.matrixBoats[x][i]);
                printf("[X: %d], [Y: %d], [i: %d], {player.matrixBoats[i][x] = %c}\n", x, y, i, player.matrixBoats[i][x]);
                printf("[X: %d], [Y: %d], [i: %d], {player.matrixBoats[y][i] = %c}\n", x, y, i, player.matrixBoats[x][i]);
                printf("[X: %d], [Y: %d], [i: %d], {player.matrixBoats[i][y] = %c}\n", x, y, i, player.matrixBoats[i][x]);
                printf("[X: %d], [Y: %d], [i: %d], {player.matrixBoats[x][y] = %c}\n", x, y, i, player.matrixBoats[x][i]);
                printf("[X: %d], [Y: %d], [i: %d], {player.matrixBoats[y][x] = %c}\n", x, y, i, player.matrixBoats[i][x]);
                printf("---------------\n");
                if(player.matrixBoats[y][i] == 'B'){  // sobrepondo um barco // if(player.matrixBoats[i][y] == 'B'){
                   printf("Sobrepoe! x=%d, y=%d, i=%d \n", x,y,i); 
                    return false;
                    break;    
                }
            }
            printf("Passou H!\n"); 
            return true;
            break;
        case 'v':
            for (int i = y; i < (y + boatSize); i++){
                printf("ENTROU NO FOR V!\n"); 
                printf("---------------\n");
                printf("[X: %d], [Y: %d], [i: %d], {player.matrixBoats[x][i] = %c}\n", x, y, i, player.matrixBoats[x][i]);
                printf("[X: %d], [Y: %d], [i: %d], {player.matrixBoats[i][x] = %c}\n", x, y, i, player.matrixBoats[i][x]);
                printf("[X: %d], [Y: %d], [i: %d], {player.matrixBoats[y][i] = %c}\n", x, y, i, player.matrixBoats[x][i]);
                printf("[X: %d], [Y: %d], [i: %d], {player.matrixBoats[i][y] = %c}\n", x, y, i, player.matrixBoats[i][x]);
                printf("[X: %d], [Y: %d], [i: %d], {player.matrixBoats[x][y] = %c}\n", x, y, i, player.matrixBoats[x][i]);
                printf("[X: %d], [Y: %d], [i: %d], {player.matrixBoats[y][x] = %c}\n", x, y, i, player.matrixBoats[i][x]);
                printf("---------------\n");
                if(player.matrixBoats[i][x] == 'B'){   //if(player.matrixBoats[x][i] == 'B'){
                    printf("Sobrepoe! x=%d, y=%d, i=%d \n", x,y,i); 
                    return false;   // sobrepondo um barco
                    break;    
                }
            }
            printf("Passou V!\n"); 
            return true;
            break;
    }
    printf("TERMINOU SWITCH!\n"); 
    return true;
}


//testado
//Adciona na matriz, o barco. necessario fazer validacao se é possivel adcionar antes.
void addBoatToMatrix(char matrix[8][8], struct Boat boat) {
    if (boat.direction == HORIZONTAL){
        for (int i = boat.x; i<=boat.size+boat.x-1; i++ ) {
            matrix[boat.y][i] = 'B';
        }
    }
    else if (boat.direction == VERTICAL){
        for (int i = boat.y; i<=boat.size+boat.y-1; i++ ) {
            matrix[i][boat.x]='B';
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
void fillEmptyPlayer(struct Player *player, int *playerIndex){

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
    *playerIndex = *playerIndex + 1;         
}

//testado
void ResetMatrix(char matrix[8][8]){
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
    printf("Direction: %s\n", boat.direction == 'h'? "Horizontal": "Vertical"); 
    printf("Is sunken? %s\n", boat.sunken == 1 ? "Yes" : "NO");   
}



//valida antes da inserção do barco se este pode ser inserido
/*bool isBoatAvailable(struct Player player){
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
}*/

