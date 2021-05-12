#ifndef __N_H__
#define __N_H__


struct mapa {
	int madeira ;
    int pedra ;
    int alimento;
    int ocupadoJogador; // mapa ocupado por 
	
};
struct posicoes {
	int posicaox; // 0 a 19
	int posicaoy; // de 0 a 24
};
struct recursos_jogadores
  {
    int casas;
    int construindoCasa; //turnos falta terminar
    int construindoQuartel; //turnos falat terminar
    int construindoMuralha; 
    int construindoTemplo;
    int habitantes;
	int posicaoxIni; //posicao inicial até 20
	int posicaoyIni; //posicao inicial até 25
    int madeira;
    int pedra;
    int alimento ; 
    
	int cidades; //tem 10 posicoes
	int posicoesConquistada ; // quantidade posicao consquistada no mapa ou numero de posicoes da cidade
	
    struct posicoes posicoes [499] ; // pode ter ate 500 posicoes de 0 a 499
	
    int templo;
    int muralha;
    int quartel;
	
    int soldadoCidade; //quantidade
    int soldadoGuerra;


    int foraJogo;		//1 - ainda jogando ; 0 fora do jogo
	int numeroJogador; // numero do jogador
  };

#endif
