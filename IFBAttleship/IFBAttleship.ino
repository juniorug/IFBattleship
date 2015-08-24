#include <LedControl.h>
#include <ScrollTest4MAX2.h>
#include <SPI.h>
#include <SD.h>  
#include <TMRpcm.h> 
#include "charLibrary.h"
#include "messages.h"

//DEFINES
#define DIM 8
#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SPEAKER_PIN 46   //pino de saida para autofalante
#define HORIZONTAL 'H'
#define VERTICAL 'V'
#define AGUA 'A' 
#define BARCO 'B'  
#define TIRO_CERTO 'C'
#define TIRO_ERRADO 'E'
#define QTD_PLAYERS 2
#define MAX_BOATS 2




// *CONSTANTS
const int DIN_1 = 12;            //DataIn pin (18)
const int CLK_1 = 11;            //Clock pin (17)
const int CS_1 = 10;           //Load pin (16)
const int DEVICES_PLAYER_1 = 2;      //duas matrizes para o player 1
//definir os pinos da matriz do player 2:
const int DIN_2 = 9; //TESTAR?           //DataIn pin (18)
const int CLK_2 = 8; //TESTAR?          //Clock pin (17)
const int CS_2 = 7; //TESTAR??          //Load pin (16)
const int DEVICES_PLAYER_2 = 2;      //duas matrizes para o player 2

const long scrollDelay = 100;
const char *boatDetails[5] = {"Hidroaviao", "Submarino", "Cruzador", "Encouracado", "Porta Aviao"};   

// STRUCTS
struct Boat {
    int x;   //x e y sao as coordenadas iniciais do barco
    int y;
    int size;
    char direction;  //H: horizontal, V: vertical
    bool sunken;     // true: navio afundado
};

struct Player{
    struct Boat boats[MAX_BOATS];
    bool currentPlayer;  //define qual o player que está atacando.
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

//VARIAVEIS DO JOGO
//LedControl lc_player1 = LedControl(DIN_1,CLK_1,CS_1,DEVICES_PLAYER_1);
//ScrollTest4MAX2 sc_player1 = ScrollTest4MAX2(&lc_player1,scrollDelay);
//LedControl lc_player2 = LedControl(DIN_2,CLK_2,CS_2,DEVICES_PLAYER_2);
//ScrollTest4MAX2 sc_player2 = ScrollTest4MAX2(&lc_player2,scrollDelay);

LedControl lc_players[2] = {LedControl(DIN_1,CLK_1,CS_1,DEVICES_PLAYER_1),LedControl(DIN_2,CLK_2,CS_2,DEVICES_PLAYER_2)};
ScrollTest4MAX2 sc_players[2] = {ScrollTest4MAX2(&lc_players[0],scrollDelay),ScrollTest4MAX2(&lc_players[1],scrollDelay)};
TMRpcm tmrpcm;   // objeto de manipulacao de audio
char mychar;
int playerIndex;
char *message;
struct Player players[QTD_PLAYERS]; //array de jogadores


void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 2; i++){
       lc_players[i].shutdown(0,false);
       lc_players[i].clearDisplay(0);
    }    
    randomSeed(analogRead(A0));  
    tmrpcm.speakerPin = SPEAKER_PIN; //
    if (!SD.begin(SD_ChipSelectPin)) {  // inicializando o SDcard
        Serial.println("SD fail");
    } else {
      Serial.println("Initialization Done!");  
    }
    tmrpcm.setVolume(5);
    tmrpcm.play("pacman.wav"); //the sound file "music" will play each time the arduino powers up, or is reset
}

void loop() {
  //sc.scrollMessage(scrollText);   //TESTANDO SCROOL MESSAGE
  //tmrpcm.play("pacman.wav");    TESTANDO AUDIO
  int choosed = chooseFirstPlayer();
  if (choosed ==1){
    Serial.println(PLAYER_1_COMECA);
  }else {
    Serial.println(PLAYER_2_COMECA);
  }
}

//################  METODOS PARA ESCOLHA DO FIRST PLAYER (RETIRADOD DE TESTRANDOM.INO) ################ 

//algoritmo para escolha de quem começa a jogar
//int chooseFirstPlayer(){
int chooseFirstPlayer(){
  long p1Number = 0L;
  long p2Number = 0L;
  int choosedplayer = 1;
  while (p1Number == p2Number) {
    Serial.println(PLAYER_1_READY);
    //while (digitalRead(buttonPlayer1) == LOW) {
    for (int i = 0; i < 30; i++){
      generateAndShowNumber(1,&p1Number);
    }
    // mostra o numero obtido pelo p1:
    Serial.println(PLAYER_1_NUMBER_CHOOSED);
    Serial.println(p1Number);
    piscaNumeroDisplay(1, p1Number);

    Serial.println(PLAYER_2_READY);
    //while (digitalRead(buttonPlayer2) == LOW) {
    for (int i = 0; i < 30; i++){
      generateAndShowNumber(2,&p2Number);
    }
    // mostra o numero obtido pelo p2:
    Serial.println(PLAYER_2_NUMBER_CHOOSED);
    Serial.println(p2Number);
    piscaNumeroDisplay(2, p2Number);

    if (p1Number == p2Number){
      Serial.println(EMPATE);
    }
  }
  if (p1Number > p2Number) {
    Serial.println(PLAYER_1_COMECA);
   // p1.currentPlayer = true;
   // p2.currentPlayer = false;
     choosedplayer = 1;
  } else {
    Serial.println(PLAYER_1_COMECA);
   // p2.currentPlayer = true;
    //p1.currentPlayer = false;
    choosedplayer = 2;
  } 
  delay(1000);
  return choosedplayer;
}

void generateAndShowNumber(int player, long *number){ 
  *number = random(10);
  Serial.println("random: ");
  Serial.println(*number);
  mostraNumeroDisplay( 1,*number);
}

void mostraNumeroDisplay(int display, long numero){
  printLetter(numbers[((int)numero)]);
  delay(50);
}

void piscaNumeroDisplay(int display, long numero){
  for (int i = 0; i < 5; i++) {
    printLetter(numbers[((int)numero)]);
    delay(500);
    lc_players[0].clearDisplay(0);
    lc_players[1].clearDisplay(0);
    delay(500);
  }
}

void printLetter(const byte letter[7]){
  for (int i = 0; i < 7; i++) {    
      lc_players[0].setRow(0,i,letter[i]);
      lc_players[1].setRow(0,i,letter[i]);
  }
}


//################ METODOS PARA IMPRIMIR A MATRIZ DE BARCOS (RETIRADOD DE TESTLEDMATRIX2.INO) ################ 

int intPow(int x, int pow)
{
    int ret = 1;
    while ( pow != 0 )
    {
        if ( (pow & 1) == 1 )
            ret *= x;
        x *= x;
        pow >>= 1;
    }
    return ret;
}

void setLCMatrix(char matrix[DIM][DIM], LedControl lc){
  for (int row = 0; row < DIM; row++){
    int rowValue = 0;
    for (int col = 0; col < DIM ; col++){
      if(matrix[row][col] == 'B') {
        rowValue += intPow(2, (7-col));  //calcula o valor decimal correspondente à linha.
      }
    }
    lc.setRow(0,row,rowValue); //ligando os leds correspondentes à linha 'row'
  } 
}

// ################ METODOS DO JOGO (RETIRADOD DE TESTLEDMATRIX2.INO) ################ 
// VAI PARA DENTRO DO LOOP
void mainGame ()
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
    bool fired = fire(x,y, players[1].matrixBoats);
    if (fired){
        int k =  getShipIndexByGivenPoint(x, y, players[1].boats);
        
        printf("ACERTOU!!!!!!!!  Barco index: %d\n", k);
        if (isSunkenShip(&players[1].boats[k], players[1].matrixBoats)){
            printf("Barco AFUNDOU!!!!!!!!\n");
            printBoatDetails(players[1].boats[k]);
            decrementBoatCount(&players[1], players[1].boats[k].size);
            players[1].availableBoats --;
            if(noMoreBoats(players[1])){
                printf("JOGO ACABOU!! Player %d ganhou\n", players[0].currentPlayer ? 1:2);
            } else {
                printf("Jogo continua, agora e a vez do player %d\n", players[0].currentPlayer ? 2:1);
                changeCurrentPlayer(players);
            }
        } else {
            printf("Barco NAO afundou!!!!!!!!\n");
            printBoatDetails(players[1].boats[k]);
            printf("Jogo continua, agora e a vez do player %d\n", players[0].currentPlayer ? 2:1);
            changeCurrentPlayer(players);
        }
        printPlayerDetails(players[1]);
    }
    else{
        printf("ERROU!!!!!!!!");
    }
    fillMatrixShots(x,y,players[0].matrixShots, fired);
    printPlayerDetails(players[0]);
}


//testado   //ALTERAR PARA USAR OS BOTOES
void startGame(){
 /*   for (int i = 0; i < QTD_PLAYERS; i++) {
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
    } */
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

//testado
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
// checa se nao ultrapassa os limites da matriz e se nao sobrepoe outro barco
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
//Adciona na matriz, o barco. necessario fazer validacao se eh possivel adcionar antes.
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

//testado
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
    Serial.print("[ ");
    for (int row = 0; row < DIM; row++) {
        for (int col = 0; col < DIM ; col++) {  
            Serial.print(matrix[row][col]);
            if((row < DIM -1) || (col < DIM -1)){
                Serial.print(",");
            }
        }
        if (row < DIM -1) {
            Serial.print("\n  ");
        }
    }
    Serial.println(" ]");   
}

//testado   //ALTERAR PARA SERIAL!!
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

//testado //ALTERAR PARA SERIAL!!
void printBoatDetails(struct Boat boat){

    printf("Boat details: \n");
    printf("Position X0: %d\n", boat.x);
    printf("Position Y0: %d\n", boat.y);
    printf("Size: %d\n", boat.size); 
    printf("Tipe: %s\n", boatDetails[boat.size-1]); 
    printf("Direction: %s\n", boat.direction == HORIZONTAL ? "Horizontal" : "Vertical"); 
    printf("Is sunken? %s\n", boat.sunken == 1 ? "Yes" : "NO");   
}

//testado
//testa se acertou ou errou o tiro
boolean fire(int x, int y, char matrix[8][8]){
    bool fired = false;
    if (matrix[y][x] == 'B') {
        fired = true;
        matrix[y][x] = 'C';    //acertou o tiro!
    } else if (matrix[y][x] == 'A') {
        matrix[y][x] = 'E';    //errou o tiro!
    }
    // printf("TESTE TIRO %c \n", matrix[y][x]);
    printPlayerDetails(players[1]);
    return fired;
}

//testado
void fillMatrixShots(int x, int y, char matrix[8][8], bool fired){
    if ((matrix[y][x] == 'A') && (fired)){
      matrix[y][x] = 'C';    //acertou o tiro!
    } else if (matrix[y][x] == 'A') {
      matrix[y][x] = 'E';    //errou o tiro!
    }
}




//testado
// testa se o dado ponto x,y pertence a algum barco retornando o indice do mesmo. -1 se ponto nao pertence a nenhum barco
int getShipIndexByGivenPoint(int x, int y, struct Boat boats[7]) {
    for (int k = 0; k < 7; k++){
        switch (boats[k].direction){
            case HORIZONTAL:
                for (int i = boats[k].x; i < (boats[k].x + boats[k].size); i++){
                    if((x == i) && (y == boats[k].y)){
                        return k;
                        break;    
                    }
                }
                break;
            case VERTICAL:
                for (int i = boats[k].y; i < (boats[k].y + boats[k].size); i++){
                    if((x == boats[k].x) && (y == i)){
                        return k;
                        break;    
                    }
                }
                break;
        }
    }
    return -1;   //boat not found!
}


//testa se o navio afundou
//testado
bool isSunkenShip(struct Boat *boat, char matrix[8][8]){
    if (!boat->sunken){
        switch (boat->direction){
            case HORIZONTAL:
                for (int i = boat->x; i < (boat->x + boat->size); i++){
                    if(matrix[boat->y][i] == 'B'){
                        //boat.sunken = false;
                        return false;
                        break;    
                    }
                }
                boat->sunken = true;
                return boat->sunken;
                break;
            case VERTICAL:
                for (int i = boat->y; i < (boat->y + boat->size); i++){
                    if(matrix[i][boat->x] == 'B'){
                        //boat.sunken = false;
                        return false;
                        break;    
                    }
                }
                boat->sunken = true;
                return boat->sunken;
                break;
        }
    }
    return boat->sunken;
}
//testado
bool noMoreBoats(struct Player player){
    return player.availableBoats < 1;   //todos os barcos foram afundados
}

//testado
void changeCurrentPlayer(struct Player players[2]){
    players[0].currentPlayer = !players[0].currentPlayer;
    players[1].currentPlayer = !players[1].currentPlayer;    
}

