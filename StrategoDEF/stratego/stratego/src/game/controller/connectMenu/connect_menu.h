#pragma once

/*
Este controller (ConnectMenu) administra la interfaz grafica, el modelo (network) para conectarse con otro jugador
*/

#include <framework\controller\controller.h>
#include <framework\view\widgets\text_button.h>
#include <framework\view\widgets\TextInput.h>
#include <framework\view\widgets\Animation.h>
#include <framework\view\widgets\screen_text.h>
#include <framework\sysgame\sysgame.h>

class ConnectMenu : public Controller{
	private:
		int _startedToConnect;
		TextButton *connectButton;
		TextInput *input;
		int waitTime;

		vector <string> connectContent;

		string status;
		string connectIP;

		string myName, opponentName;
		int gotName, gotOpponentName;

		int nameInputFilled;

		pair<float,float> infoPositionA; /// info message and icon places
		pair<float,float> infoPositionB;
		Widget* infoObjectA;
		Widget* infoObjectB;
		string mode;

		int localStart;		

		bool InfoMessageAdded, InfoIconAdded , cancelButtonAdded;
	public:
		ConnectMenu(Sysgame *sys);
		void onCreate();
		void onNetPack(string &package, map<string, string> &data);  // handle NETWORK actions
		void onNetEvent(NETWORK_EVENT *ev);
		void startToConnect(); // comenzar a conectarse (cuando el jugador hace click en el boton de conectar)
		int startedToConnect(); // checkear si nos empeazamos a conectar)
		void setConnectionFailed(); // setear la iterfaz grafica cuando fallo la coneion
		void createConnectButton(); // crear el boton para conectarse (agregar y configurar su widget)
		void generateNameInput(); // crear el widget que tiene el textInput del nombre del jugador
		void setNotConnecting(); // Configurar que no nos pudimos conectar
		void setConnectionWaitTimeout(); // Comenzar la espera para volver intentar a conectarse
		void setConnectionSuccess(); // Actualizar la interfaz cuando se logro establecer la conexion
		void eraseConnectContent(); /// Para borrar: no se usa mas
		void setInfoObjects(Widget* A,Widget* B); // Para borrar: no se usa mas
		void eraseInfoObjects(); // Para borrar: no se usa mas
		void waitForConnection(); // Setear la interfaz grafica cuando estamos en el modo en el que esperamos un cliente
		void goToGame(); // Moverse al controller del juego
		Animation* generateAnimationWidget(string name); // comenzar a mostrar el widget de animacion
		screenText* generateScreenText(string msg,string font,string name); // comenxar a mostrar el texto de informaicion
		string getConnectIP(); // conseguir la IP del text input
		vector<string> &getConnectContent(); 
		void setStatus(string status);// setear el estado de la maquina de estados del connect menu
		string getStatus(); // conseguir dicho estado
		pair<float,float> getInfoPositionA(); // para borrar: no se usa mas
		void setName(string name); // setear nombre insertado en el textInput
		void setOpponentName(string name); // setear nombre recibido del network del rival
		int hasName();
		int hasOpponentName(); // checkear si ya seteamos dichos nombres
		string getName();
		string getOpponentName(); // obtener los nombres
		void setPlayerName(string name);
		void sendName(string name); /// enviar al otro jugador el nombre (via network)
		void sendAck(); // enviar via network el Ack
		void makeDraw(); // hacer el sorteo (se llamara si corresponde)
		void sendNameRequest(); // enviar request para que se envie el nombre 
		void readyToStart(int localStart); // se llama cuando ya queremos pasar al controller del juego (gameArea)

		TextButton* addCancelButtonCenter();
		TextButton* addCancelButtonLeft();
		TextButton* addCancelButton(pair <int,int> pos);  /// Funciones auxiliares para en los distintos momentos mostrar los botones para cancelar la partida
		void removeCancelButton(); // eliminarlo...

		void addInfoMessage(string msg,string color);
		void addInfoIcon(string icon);
		void addInfoAnim(); /// Agregar widgets de informacion/animacion cuando nos estamos conectando

		void removeInfoMessage();
		void removeInfoThing(); // Eliminarlos ...
		~ConnectMenu();
};

