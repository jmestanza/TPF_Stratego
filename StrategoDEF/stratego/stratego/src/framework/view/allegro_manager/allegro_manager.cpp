#define _WIN32_WINNT 0x0501


#include "allegro_manager.h"
#include "allegro5\allegro5.h"
#include "allegro5\allegro_acodec.h"
#include "allegro5\allegro_audio.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_ttf.h"
#include <framework\utils\getXMLFile.h>

#include <map>
#include <iostream>
using namespace std;
using boost::property_tree::ptree;



AllegroHandlerException::AllegroHandlerException(string _err) : err("AllegroHandlerException: "+_err) {

}
const char * AllegroHandlerException::what() const throw() {
	//string ans =  + err;
	return err.c_str();
}

void allegro_init(void) {
	if (!al_init())	throw AllegroHandlerException("could not start allegro");
	if (!al_install_keyboard()) throw AllegroHandlerException("could not start allegro keyboard");
	if (!al_init_image_addon()) throw AllegroHandlerException("could not start allegro image");
	if (!al_install_audio()) throw AllegroHandlerException("could not start allegro audio");
	if (!al_init_acodec_addon()) throw AllegroHandlerException("could not start allegro acodec addon");
	if (!al_reserve_samples(2)) throw AllegroHandlerException("could not start allegro reserve samples");
	if (!al_install_mouse()) throw AllegroHandlerException("could not install mosue");
	if (!al_init_primitives_addon()) throw AllegroHandlerException("could not start primitives addon");
	if (!al_init_font_addon()) throw AllegroHandlerException("could not start font addon");
	if (!al_init_ttf_addon()) throw AllegroHandlerException("could not start ttf addon");
}
Viewer::Viewer() {
	_debug = 0;
	TimerFreq = 40;
	 // defaults
	screenSize.first = 800;
	screenSize.second = 600;
}
void Viewer::setDebugFlag() {
	_debug = 1;
}
pair <float, float> Viewer::getScreenSize() {
	return screenSize;
}
void Viewer::setScreenSize(pair<float,float> _size) {
	screenSize = _size;
}
void Viewer::start(){
	// enable anti alias
	//al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	//al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

	allegro_init();
	
	q = al_create_event_queue();
	if (!q) throw AllegroHandlerException("could not create event queue");

	display = al_create_display(screenSize.first, screenSize.second);
	if (!display) throw AllegroHandlerException("could not create display ");
	timer = al_create_timer(1.0 / TimerFreq);
	if (!timer) throw AllegroHandlerException("could not create timer");

	al_register_event_source(q, al_get_display_event_source(display));
	al_register_event_source(q, al_get_keyboard_event_source());
	al_register_event_source(q, al_get_mouse_event_source());
	al_register_event_source(q, al_get_timer_event_source(timer));

	al_start_timer(timer);
	if (!_debug) cout << "info: allegro started\n";
}
void Viewer::loadConfFile(string xmlFile) {
	ptree pt;
	getXMLFile(pt,xmlFile);
	if (pt.count("config") != 1) throw AllegroHandlerException("wrong xml file (config tag invalid)");
	ptree content = pt.get_child("config");

	if (content.count("screen_size") > 1) throw AllegroHandlerException("wrong xml file (screen tag is invalid)");
	if (content.count("screen_size") == 1) {
		ptree screen_sz = content.get_child("screen_size").get_child("<xmlattr>");
		if (screen_sz.count("width") != 1) {
			throw AllegroHandlerException("wrong xml file (screen size invalid)");
		}
		if (screen_sz.count("height") != 1) {
			throw AllegroHandlerException("wrong xml file (screen size invalid)");
		}
		string screen_width  = screen_sz.get<string>("width");
		string screen_height = screen_sz.get<string>("height");
		try {
			screenSize.first = stoi(screen_width);
			screenSize.second = stoi(screen_height);
		}catch (invalid_argument &e) {
			screenSize.first = 800;
			screenSize.second = 600;
			throw AllegroHandlerException("wrong xml file (screen size values invalid)");
		}
	}
	if (content.count("debug") >= 1) setDebugFlag();
}
bool Viewer::hasLoadedImg(string name) {
	return loaded.find(name) != loaded.end();
}
void Viewer::loadImgFile(string xmlFile) {
	ptree pt;
	getXMLFile(pt,xmlFile);
	if (pt.count("images") != 1) {
		throw AllegroHandlerException("Error in xml file, wrong amount of images tag in '"+xmlFile+"'");
	}
	ptree content = pt.get_child("images");
	for (auto it = content.begin(); it != content.end(); ++it) {
		if (it->first == "image") {
			if (it->second.get_child("<xmlattr>").count("name") != 1) {
				throw AllegroHandlerException("Invalid protocol xml file, invalid count 'name'");
			} else if (it->second.get_child("<xmlattr>").count("dir") != 1) {
				throw AllegroHandlerException("Invalid protocol xml file, invalid count 'dir'");
			}
			string name = it->second.get<string>("<xmlattr>.name");
			string dir = it->second.get<string>("<xmlattr>.dir");

			this->load("resource/images/"+dir,name);
		}
	}
}
void Viewer::loadAudioFile(string xmlFile) {
	cout << xmlFile << endl;
	ptree pt;
	getXMLFile(pt,xmlFile);
	cout << pt.count("audios") << endl;
	if (pt.count("audios") != 1) {
		throw AllegroHandlerException("Error in xml file, wrong amount of audio tag in '" + xmlFile + "'");
	}
	ptree content = pt.get_child("audios");
	for (auto it = content.begin(); it != content.end(); ++it) {
		if (it->first == "audio") {
			if (it->second.get_child("<xmlattr>").count("name") != 1) {
				throw AllegroHandlerException("Invalid protocol xml file, invalid count 'name'");
			} else if (it->second.get_child("<xmlattr>").count("dir") != 1) {
				throw AllegroHandlerException("Invalid protocol xml file, invalid count 'dir'");
			}
			string name = it->second.get<string>("<xmlattr>.name");
			string dir = it->second.get<string>("<xmlattr>.dir");

			this->loadAudio("resource/audio/" + dir,name);
			
		}
	}

}
void Viewer::loadFontFile(string xmlFile) {
	ptree pt;
	getXMLFile(pt,xmlFile);
	if (pt.count("fonts") != 1) {
		throw AllegroHandlerException("Error in xml file, wrong amount of fonts tag in '"+xmlFile+"'");
	}
	ptree content = pt.get_child("fonts");
	for (auto it = content.begin();it != content.end(); ++it) {
		if (it->first == "font") {
			bool err1 = it->second.get_child("<xmlattr>").count("name") != 1;
			bool err2 = it->second.get_child("<xmlattr>").count("size") != 1;
			bool err3 = it->second.get_child("<xmlattr>").count("dir") != 1;
			if (err1 || err2 || err3) {
				throw AllegroHandlerException("Invalid font xml file, invalid name-size-dir count");
			}
			string name = it->second.get<string>("<xmlattr>.name");
			string dir = it->second.get<string>("<xmlattr>.dir");
			string sSize = it->second.get<string>("<xmlattr>.size");
			int size;
			try {
				size = stoi(sSize);
			} catch (invalid_argument &e) {
				throw AllegroHandlerException("Invalid font size\n");
			}
			this->loadFont("resource/fonts/"+dir,name,size);
		}
	}
		
}
void Viewer::loadColorsFile(string xmlFile) {
	ptree pt;
	getXMLFile(pt, xmlFile);
	if (pt.count("colors") != 1) {
		throw AllegroHandlerException("Error in xml file, wrong amount of colors tag in '" + xmlFile + "'");
	}
	ptree content = pt.get_child("colors");
	for (auto it = content.begin(); it != content.end(); ++it) {
		if (it->first == "color") {
			bool err1 = it->second.get_child("<xmlattr>").count("code") != 1;
			bool err2 = it->second.get_child("<xmlattr>").count("name") != 1;
			if (err1 || err2) {
				throw AllegroHandlerException("Error in xml, code or name attr are in wrong amount in '" + xmlFile + "'");
			}
			string code = it->second.get<string>("<xmlattr>.code");
			string name = it->second.get<string>("<xmlattr>.name");

			this->loadColor(code, name);
		}
	}
}
void Viewer::loadAudio(string dir,string name){
	ALLEGRO_SAMPLE* sample = al_load_sample(dir.c_str());
	if (!sample) throw AllegroHandlerException("unable to load audio '" + dir + "'");
	loadedAudio[name] = sample;
	ALLEGRO_SAMPLE_INSTANCE *instance = al_create_sample_instance(sample);
	if(!instance) throw AllegroHandlerException("unable to create sample instance");
	AudioInstances[name] = instance;
	al_attach_sample_instance_to_mixer(AudioInstances[name],al_get_default_mixer());
}
void Viewer::load(string dir, string name) {
	ALLEGRO_BITMAP* image = al_load_bitmap(dir.c_str());
	if (!image) throw AllegroHandlerException("unable to load image '"+dir+"'");
	loaded[name] = image;
}
void Viewer::loadFromBitmap(ALLEGRO_BITMAP *b,string name) {
	if (loaded.find(name) != loaded.end()) {
		throw AllegroHandlerException("tring to load image with repeated name! , '"+name+"'");
	}
	loaded[name] = b;
}
void Viewer::loadFont(string dir, string name,int size) {
	if (fonts.find(name) != fonts.end()) {
		throw AllegroHandlerException("font name '"+name+"' repeated");
	}
	ALLEGRO_FONT* font_test = al_load_ttf_font(dir.c_str(),size,0);
	if (!font_test) throw AllegroHandlerException("could not load font '"+dir+"'");
	fonts[name] = font_test;
}
void Viewer::loadColor(string code,string name) {
	if (colors.find(name) != colors.end()) {
		throw AllegroHandlerException("trying to add two colors with the same name '" + name + "'");
	}
	if (code.size() == 0) throw AllegroHandlerException("invalid color code (err 1)");
	ALLEGRO_COLOR color;
	if (code[0] == '#') {
		if (code.size() != 7) throw AllegroHandlerException("invalid color code (err 2)");
		string colorCode = code.substr(1, 6);
		unsigned int value;
		stringstream ss;
		ss << std::hex << colorCode;
		ss >> value;
		unsigned char r = (value >> 16) & 0xFF;
		unsigned char g  = (value >> 8) & 0xFF;
		unsigned char b = (value) & 0xFF;
		color = al_map_rgb(r, g, b);
	}else{
		int pnt = 0;
		vector <string> colorsList;
		string current = "";
		while (pnt < code.size()) {
			if (code[pnt] == '(' || code[pnt] == ')') {
				
			}else if (code[pnt] != ',') {
				current += code[pnt];
			}else {
				colorsList.push_back(current);
				current = "";
			}
			pnt++;
		}
		colorsList.push_back(current);
		
		if (colorsList.size() != 3) throw AllegroHandlerException("invalid color code (err 3)");
		vector <unsigned char> ans;
		for (int i = 0; i < colorsList.size(); i++) {
			if (colorsList[i] == "") throw AllegroHandlerException("invalid color code (err 4)");
			try {
				ans.push_back(stoi(colorsList[i]));
			}catch (invalid_argument &e) {
				throw AllegroHandlerException("invalid color code (parse number failed) ");
			}
		}
		color = al_map_rgb(ans[0], ans[1], ans[2]);
	}
	/// now add to list
	//cout << "colors[" << name << "] = " << color.r << ',' << color.g << ',' << color.b << '\n';
	colors[name] = color;
}
ALLEGRO_COLOR Viewer::getColor(string code) {
	if (colors.find(code) == colors.end()) {
		throw AllegroHandlerException("Unable to find color '" + code + "'");
	}
	return colors[code];
}
ALLEGRO_FONT* Viewer::getFont(string name) {
	/*for (auto it = fonts.begin();it != fonts.end();it++) {
		cout << "font = " << it->first << '\n';
	}*/
	if (fonts.find(name) == fonts.end()) {
		throw AllegroHandlerException("font name '"+name+"' not found'");
	}
	return fonts[name];
}
ALLEGRO_BITMAP * Viewer::getImg(string loadedName) {
	if (loaded.find(loadedName) == loaded.end()) {
		throw AllegroHandlerException("Trying to get image that was not loaded '"+loadedName+"'");
	}
	return loaded[loadedName];
}
void Viewer::eraseLoaded(string loadedName) {
	if (loaded.find(loadedName) == loaded.end()) {
		return; // esta situacion puede suceder y es normal. A veces el recolector de basura elimina el objeto antes de tiempo
	}
	loaded.erase(loadedName);
}
void Viewer::stopShow(string destroyName) {
	if (frontShow.find(destroyName) == frontShow.end()) {
		throw AllegroHandlerException("trying to stop showing image that is not being shown");
	}
	frontShow.erase(destroyName);
}
void Viewer::draw() {

	vector <int> eraseList;
	for (int i = 0; i < drawOrder.size(); i++) {
		// si se da esta condiccion la imagen fue eliminada, lo agregamos a la lista para la eliminacion definitiva
		if (frontShow.find(drawOrder[i]) == frontShow.end()) {
			eraseList.push_back(i);
		}else {
			frontShow[drawOrder[i]]->draw();
		}
	}
	for (int i = eraseList.size() - 1; i >= 0; i--) drawOrder.erase(drawOrder.begin() + eraseList[i]);
	al_flip_display();
}

void Viewer::show(string imageName, string showName, float x, float y) {

	if ((loaded.find(imageName) == loaded.end())) throw AllegroHandlerException("Trying to show something that is not in memory");
	
	ShowImage *nueva = new ShowImage(this);
	nueva->setPosition(pair<float, float>(x, y), 0);
	nueva->setImage(loaded[imageName]);
	frontShow[showName] = (ShowObject*)nueva;

	drawOrder.push_back(showName);
}
void Viewer::showRectangle(string showName, unsigned char r, unsigned char g, unsigned char b, pair<float, float> pos, pair<float, float> size,bool centered) {
	
	ShowRectangle *nuevo = new ShowRectangle(this);
	nuevo->setPosition(pos,centered);
	nuevo->setColor(r,g,b);
	nuevo->setSize(size);
	frontShow[showName] = (ShowObject*)nuevo;
	drawOrder.push_back(showName);
}
void Viewer::playloop(string song) {	
	if ((AudioInstances.find(song) == AudioInstances.end())) throw AllegroHandlerException("Trying to play something that is not in memory");
	al_set_sample_instance_playmode(AudioInstances[song],ALLEGRO_PLAYMODE_LOOP);
	al_play_sample_instance(AudioInstances[song]);
}

void Viewer::playonce(string song) {
	if ((AudioInstances.find(song) == AudioInstances.end())) throw AllegroHandlerException("Trying to play something that is not in memory");
	al_set_sample_instance_playmode(AudioInstances[song],ALLEGRO_PLAYMODE_ONCE);
	al_play_sample_instance(AudioInstances[song]);
}


void Viewer::changeShowImg(string showName, string newImageName) {
	if (loaded.find(newImageName) == loaded.end()) throw AllegroHandlerException("invalid usage of Viwer::ChangeShowImg() (err 1)");
	if (frontShow.find(showName) == frontShow.end()) {
		throw AllegroHandlerException("invalid usage of Viwer::ChangeShowImg() (err 2: changing image that don't exist)");
	}else{
		try {
			ShowImage *img = dynamic_cast<ShowImage*>(frontShow[showName]);
			img->setImage(loaded[newImageName]);
		} catch (bad_cast &e) {
			throw AllegroHandlerException("invalid usage of Viwer::ChangeShowImg() (bad cast)");
		}
	}
	//float x = frontShow[showName].pos.first, y = frontShow[showName].pos.second;
	//frontShow[showName] = ShowObject(loaded[newImageName], x, y);
}
void Viewer::destroyAll() {
	for (auto it = frontShow.begin(); it != frontShow.end(); it++) delete it->second;
	frontShow.clear();
}
bool Viewer::getNextEvent(ALLEGRO_EVENT *ev) {	
	return al_get_next_event(q,ev);
}
ALLEGRO_DISPLAY *Viewer::getScreen() {
	return display;
}
Viewer::~Viewer() {
	
	for (auto it = loaded.begin(); it != loaded.end(); ++it) al_destroy_bitmap(it->second);
	for (auto it = frontShow.begin();it != frontShow.end();++it) delete it->second;

	al_destroy_display(display);
	al_destroy_event_queue(q);
	al_destroy_timer(timer);
}
