#pragma once

/*
GameArea: aqui se desarrolla la partida cuando ya establecimos la conexion
previamente
Se administran, entre otras cosas, el tablero y los TokenContainer,
su interaccion entre si, lo que sucede cuando llegan packetes, lo  que sucede cuando 
se interactua con el TokenContainer y el tablero. Se consulta a el modelo (el game engine), 
la validez de los movimientos, lo que sucede cuando hay ataques, etc
*/
#include <game\model\stratego_engine\BasicToken.h>
#include <game\model\stratego_engine\Player.h>
#include <framework\controller\controller.h>
#include <framework\sysgame\sysgame.h>

class gameArea : Controller{
	private:
		string name,opponentName;
		int localStart;
		Widget *infoAreaA,*infoAreaB;
		string selectedItem;
		string status;
		string mode;
		int tokensToPlace;
		int halfPoint;
		int quarterPoint;
		int threeQuartersPoint;

		int startButtonPresent;
		int optionButtonPresent;

		int animationAdded;
		int waitingMsgAdded;
		int hasOk;

		Player *gameEngine;

		PosType current_src,current_dst;
	public:
		void setCurrentMov(PosType src, PosType dst);

		PosType getCurrentSrc();
		PosType getCurrentDst(); // administrar variables de movimiento (cuando se llama la accion de mover una ficha)

		gameArea(Sysgame *sys,string _name,string _opponentName,int _localStart,string mode); /// configurar el gameArea: necesitamos
		//saber si empezamos el nombre del jugador y su rival, el modo (cliente,servidor).

		void onCreate();
		void onNetPack(string &package,map<string,string> &data) ;  // handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev) ;

		void setSelectedItem(string value); // configurar cual es la ficha que esta en el MouseFollower
		void decTokens(); /// incrementar o decrementar fichas restantes (mostradas en el widget de fichas resantes)
		void incTokens();
		void updateTokenMsg(); // actualizar graficamente el mensaje de fichas restantes


		void addStartButton(); //agregar/sacar boton para empezar, botones de opciones (vaciar tablero, coloar fichas al azar)
		void removeStartButton();
		void addOptionsButtons();
		void removeOptionsButtons();

		bool getIStart(); // ver si comienzo yo
		void setTokenLeft(int value); // setear fichas restantes
		void setRandomPieces(); // colocar fichas al azar en el tablero
		void addAnimation(); // mostrar animaxion de espera
		void removeAnimation(); // sacarla
		void setStatus(string status); // configurar el estado de la maquina de estado
		void addWaitingMsg(string msg); // agregar mensaje de espera
		void removeWaitingMsg(); // sacarlo

		void loadEngineContent(vector <vector <string>> &content); // cargarle al motor del juego las fichas
		// que estan colocadas en el tablero
		Player *getGameEngine();
		string getStatus();
		void tokenReady();
		pair<int,int> convertPosToGeneralType(pair<int,int> original); // funcion adaptadora ya que 
		// ambos jugadores se ven del lado de abajo aunque para uno sea esto falso

		string getSelectedItem();

		~gameArea();
};

