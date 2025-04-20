#include"social_network_app.h"
#include<iostream>
#include<fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
using namespace sf;
using namespace std;

//Helper Fuctions
Font fun_font;
Text text("", fun_font);

//Helper functions for comparing length and copy character array also read the data

int helper::strlength(char*array) {
	int i = 0;
	for (; array[i] != '\0'; i++);
	return i;
}

int helper::strlength(const char* array) {
	int i = 0;
	for (; array[i] != '\0'; i++);
	return i;
}

void helper::strcopy(char*array1,char*array2) {
	int size = strlength(array1),i=0;
	for ( i = 0; i < size; i++) {
		array2[i] = array1[i];
	}
	array2[i] = '\0';
}

void helper::strcopy(const char* array1, char* array2) {
	int size = strlength(array1), i = 0;
	for (i = 0; i < size; i++) {
		array2[i] = array1[i];
	}
	array2[i] = '\0';
}

char* helper::strcopy(const char* array1,char c1,char c2, char* array2) {
	int size = helper::strlength(array1),i;
	for ( i = 0; i < size; i++) {
		array2[i] = array1[i];
	}
	array2[i++] = c1;
	array2[i++] = c2;
	array2[i] = '\0';
	return array2;
}

bool helper::strCompare(const char* array1,const char* array2) {
	int i;
	for ( i = 0; array1[i] != '\0' && array2[i] != '\0'; i++) {
		if (array1[i] != array2[i]) {
			return false;
		}
	}
	if (array1[i] == '\0' && array2[i] == '\0')
		return true;
	else
		return false;
}

//Page data read function
void helper::dataReaderPage(pageClass** p, ifstream& file, int total_pages,userClass** u,int total_users) {
	char* id = new char[4];
	char* title = new char[100];
	char* owner = new char[5];
	for (int i = 0; i < total_pages; i++) {
		file >> id;
		file >> owner;
		int index = 0;
		for (int x = 0; x < total_users; x++) {

			if (helper::strCompare(owner, u[x]->getId())) {
				index = x;
				break;
			}
		}
		file.getline(title, 100);
		p[i]->pageSetter(id, title,u[index]);
	}
	if (id != 0) {
	delete[] id;
	id = 0;

	}
	if (title != 0) {
	delete[] title;
	title = 0;

	}
	if (owner != 0) {
	delete[] owner;
	owner = 0;

	}
	file.close();
}

//Users liked pages data reader
void helper::dataReaderUser_PAGE(userClass** u, ifstream& file, int total_user, pageClass** p,int total_pages){
	char* id = new char[4];
	int  temp_p = 0, index = 0;
	pageClass** tempp;
	char p_ID[20][5] = { 0 };
	for (int i = 0; i < total_user; i++) {

		file >> id;
		temp_p = 0;
		for (int l = 0; id[0] != '-'; l++) {

			temp_p++;
			int m = 0;
			for (; id[m] != '\0'; m++) {

				p_ID[l][m] = id[m];
			}
			p_ID[l][m] = '\0';
			file >> id;

		}
		tempp = new pageClass * [temp_p];
		for (int i = 0; i < temp_p; i++) {
			tempp[i] = new pageClass[temp_p];
		}
		for (int l = 0; l < temp_p; l++) {
			tempp[l]->setId(p_ID[l]);
			index = 0;
			for (int x = 0; x < total_pages; x++) {

				if (helper::strCompare(p_ID[l], p[x]->getId())) {
					index = x;
					break;
				}
			}

			tempp[l]->setTitle(p[index]->getTitle());
		}
		u[i]->USER_PAGELIKER_SETTER(tempp, temp_p);
		if (tempp != 0) {
			delete[]tempp;
			tempp = 0;

		}

	}
	if (id != 0) {
	delete[]id;
	id = 0;

	}
	file.close();
}

//Users data reader
void helper::dataReaderUser(userClass**u, ifstream& file, int total_user,pageClass**p) {

	char* id=new char[4];
	char* f_name=new char[50];
	char* l_name=new char[50];
	int temp_f=0, temp_p=0,index=0;
	userClass** tempf;
	char f_ID[20][5] = {0};
	char p_ID[20][5] = {0};
	for (int i = 0; i < total_user; i++) {
		
		file >> id;
		file >> f_name;
		file >> l_name;
		u[i]->USERDATASETTER(id, f_name, l_name);
	}
	for (int i = 0; i < total_user; i++) {
		file >> id;
		temp_f = 0;
		for (int l = 0; id[0]!='-'; l++) {
			
			temp_f++; 
			int m = 0;
			for (; id[m] != '\0'; m++) {

				f_ID[l][m] = id[m];
			}
			f_ID[l][m] = '\0';
			file >>id;
			
		}
		tempf = new userClass*[temp_f];
		for (int i = 0; i < temp_f; i++) {
			tempf[i] = new userClass();
		}
		
		for (int l = 0; l < temp_f; l++) {
			tempf[l]->setId(f_ID[l]);
			index = 0;
			for (int x = 0; x < total_user; x++) {
				
				if (helper::strCompare(f_ID[l], u[x]->getId())) {
					index = x;
					break;
				}
			}
			f_name = u[index]->getFirstname();
			l_name = u[index]->getLastname();
			tempf[l]->setName(f_name, l_name);
		}

		u[i]->USER_FRIEND_SETTER(tempf, temp_f);
		if (tempf != 0) {
		delete[] tempf;
		tempf = 0;

		}
		
	}
	f_name = 0;
	l_name = 0;
	if (id != 0) {
		delete[]id;
		id = 0;

	}
	if (f_name != 0) {
	delete[]f_name;
	f_name = 0;

	}
	if (l_name != 0) {
	delete[]l_name;
	l_name = 0;

	}
}

//Posts Readr
void helper::dataReaderPosts_Comments(postClass** po, ifstream& file, int total_posts, pageClass** p, userClass** u,int total_users,int total_pages) {
	
	int activity_checker, day, month, year, activity_type, likers;
	char* id = new char[15],*text=new char[1000],*a_text = new char[100],*owner=new char[5],*friendID=new char[5];
	userClass** tempf;
	pageClass** tempp;
	for (int i = 0; i < total_posts; i++) {

		file >> activity_checker;
		file >> id;
		file >> day;
		file >> month;
		file >> year;
		file >> text;
		if (activity_checker == 2) {
			file >> activity_type;
			file>>a_text;
		}
		else {
			activity_type = 0;
			helper::strcopy("\0", a_text);
		}
		file >> owner;
		file >> likers;
		tempf = new userClass*[likers];
		for (int i = 0; i < likers; i++) {
			tempf[i] = new userClass();
		}
		tempp = new pageClass * [likers];
		for (int i = 0; i < likers; i++) {
			tempp[i] = new pageClass();
		}
		for (int i = 0; i < likers; i++) {
			file >> friendID;
			if (friendID[0] == 'u') {
				int index = 0;
				for (int x = 0; x < total_users; x++) {

					if (helper::strCompare(friendID, u[x]->getId())) {
						index = x;
						break;
					}
				}
				tempf[i]=u[index];
				tempp[i] = nullptr;
			}
			else {
				int index = 0;
				for (int x = 0; x < total_pages; x++) {

					if (helper::strCompare(friendID, p[x]->getId())) {
						index = x;
						break;
					}
				}
				tempp[i]=p[index];
				tempf[i] = nullptr;
			}
		}
		if (owner[0] == 'u') {

			int index = 0;
			for (int x = 0; x < total_users; x++) {

				if (helper::strCompare(owner, u[x]->getId())) {
					index = x;
					break;
				}
			}
			po[i]->setPostData(id, day, month, year, text,activity_type, a_text, u[index], nullptr,tempf,tempp,likers);
		}
		else {
			int index = 0;
			for (int x = 0; x < total_pages; x++) {

				if (helper::strCompare(owner, p[x]->getId())) {
					index = x;
					break;
				}
			}
			po[i]->setPostData(id, day, month, year, text, activity_type, a_text, nullptr, p[index], tempf, tempp,likers);
		}
		if (tempf != 0) {
			
			delete[] tempf;
			tempf = 0;
		}
		if (tempp != 0) {
			
			delete[] tempp;
			tempp = 0;
		}
	}
	if (a_text != 0)
	{

		delete[]a_text;
		a_text = 0;
	}
	if (friendID != 0) {

		delete[]friendID;
		friendID = 0;
	}
	file.close();


	int total_comments;
	char *postID=new char[10];
	commentClass** tempC = new commentClass*[13];
	
	for (int i = 0; i < 13; i++) {
		tempC[i] = new commentClass();
	}

	ifstream cFile("Comments.txt");
	if (!cFile) {
		cerr << "Comment file not found" << endl;
	}
	cFile >> total_comments;
	for (int i = 0; i < total_comments; i++) {
		
		cFile >> id;
		cFile >> postID;
		cFile >> owner;
		cFile >> text;
		
		int index = 0;
		if (owner[0] == 'u') {
			for (int x = 0; x < total_users; x++) {
				if (helper::strCompare(owner, u[x]->getId())) {
					index = x;
					break;
				}
			}
			tempC[i]->COMMENTSETTER(u[index], text, id, nullptr);
		}
		else {
			for (int x = 0; x < total_pages; x++) {
				if (helper::strCompare(owner, p[x]->getId())) {
					index = x;
					break;
				}
			}
			tempC[i]->COMMENTSETTER(nullptr, text, id, p[index]);
		}
		for (int x = 0; x < total_posts; x++) {
			if (helper::strCompare(postID, po[x]->getId())) {
				index = x;
				break;
			}
		}
		po[index]->commentSetterPost(tempC,i);
		
	}


	if (tempC != 0) {

		delete[]tempC;
		tempC = 0;
	}
	if (id != 0) {

	delete[]id;
	id = 0;
	}
	if (text != 0) {

		delete[]text;
	}
	if (owner != 0) {

	delete[]owner;
	owner = 0;
	}
	if (postID != 0) {

	delete[]postID;
	postID = 0;
	}
	cFile.close();
}

memoryClass** helper::sizeIncreser(memoryClass** m, int totalMemories) {
	memoryClass** temp = new memoryClass * [totalMemories + 1];
	for (int i = 0; i < totalMemories; i++) {
		temp[i] = m[i];
	}
	delete[] m;
	m = new memoryClass * [totalMemories + 1];
	for (int i = 0; i < totalMemories; i++) {
		m[i] = temp[i];
	}
	m[totalMemories] = new memoryClass();
	delete[] temp;
	return m;
}

void helper::strcopy(char* array1, const char* array2) {
	int size = strlength(array2), i = 0;
	array1 = new char[size + 1];
	for (int i = 0; i < size; i++) {
		array1[i] = array2[i];
	}
	array1[i] = '\0';
}

//---------------------------------------------

//user functions

userClass::userClass(){
	 userID=nullptr;
	 first_name= nullptr;
	 last_name= nullptr;
	 friends= nullptr;
	 likedPages= nullptr;
	 friends_num= 0;
	 pages_num=0;
	 numberOfPosts=0;
	 listOfPosts= new postClass*[10];
	 user_memories = new memoryClass*[15];
	 total_user_memories = 0;
	 for (int i = 0; i < 15; i++) {
		 user_memories[i] = 0;
	 }
	 for (int i = 0; i < 10; i++) {
		 listOfPosts[i] = 0;
	 }
}

userClass::~userClass() {
	if (userID != 0) {

		delete[] userID;
		userID = 0;
	}
	if (first_name != 0) {

		delete[] first_name;
		first_name = 0;
	}
	if (last_name != 0) {

		delete[] last_name;
		last_name = 0;
	}
	if (friends != 0) {

		delete[] friends;
		friends = 0;
	}
	if (likedPages != 0) {

		delete[] likedPages;
		likedPages = 0;
	
	}
	if (user_memories != 0) {
		for (int i = 0; i < total_user_memories; i++) {
			delete user_memories[i];
			user_memories[i] = 0;
		}
		delete[] user_memories;
		user_memories = nullptr;
	}
	if (listOfPosts != 0) {

		for (int i = 0; i < numberOfPosts; i++) {
			delete listOfPosts[i];
			listOfPosts[i] = 0;
		}
		delete[]listOfPosts;
		listOfPosts = 0;
	}
}

//add memory function from user side
void userClass::addUserMemory(postClass* obj, char* t, postClass** p, int total_posts, memoryClass**& m, int& totalMemories) {
	m = helper::sizeIncreser(m, totalMemories);

	user_memories[total_user_memories] = new memoryClass();
	user_memories[total_user_memories]->addMemory(obj, t, p, total_posts, num_memory_getter() + 1, this);

	m[totalMemories] = user_memories[total_user_memories];

	total_user_memories++;
	totalMemories++;
}

char* userClass::getId() {
	return this->userID;
}

char* userClass::getFirstname() {
	return this->first_name;
}

char* userClass::getLastname() {
	return this->last_name;
}

void userClass::setId(char*id) {
	userID = new char[helper::strlength(id)+1];
	helper::strcopy(id, userID);
}

void userClass::setName(char* f, char* l) {
	this->first_name = new char[50];
	this->last_name = new char[50];

	helper::strcopy(f, this->first_name);
	helper::strcopy(l, this->last_name);
	
}

//function print friend list of user
void userClass::viewFriendList(RenderWindow* window) {
	int count = window->getSize().y/2-150;
	text.setPosition(window->getSize().x / 2 - 200, count);
	

	String firstName(this->first_name);
	String lastName(this->last_name);
	text.setString(firstName + " " + lastName + "-- friend list\n\n");
	text.setCharacterSize(35);
	text.setFillColor(sf::Color(162, 59, 138, 200));
	window->draw(text);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	count += 20;
	for (int i = 0; i < this->friends_num; i++) {
		count += 30;
		string uid(this->friends[i]->userID);
		string fn(this->friends[i]->first_name);
		string ln(this->friends[i]->last_name);
		text.setString(uid + "\t" + fn + " " + ln + "\n");
		text.setPosition(window->getSize().x / 2 - 100, count);
		window->draw(text);
	}
	this->viewLikedPages(window,count);
}

//function print liked page list of user
void userClass::viewLikedPages(RenderWindow* window,int &count) {

	count += 30;
	String firstName(this->first_name);
	String lastName(this->last_name);
	text.setCharacterSize(35);
	text.setFillColor(sf::Color(162, 59, 138, 200));
	text.setString(firstName + " " + lastName + "-- page list\n\n");;
	text.setPosition(window->getSize().x / 2 - 200, count);
	window->draw(text);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	count += 20;

	for (int i = 0; i < this->pages_num; i++) {
		count += 30;
		this->likedPages[i]->getterForUser(window,count);
	}
}

void userClass::newFriend(userClass&obj) {
	if (friends_num>=0&&friends_num <= 10) {
		friends_num++;
		friends[friends_num]->userID = obj.userID;
		friends[friends_num]->first_name = obj. first_name;
		friends[friends_num]->last_name = obj.last_name;

		cout << "Friend stored sucessfully " << endl;

	}
	else {
		cout << "You have already maximum number of freinds" << endl;
	}
}

void userClass::newLikedPage(pageClass& obj) {
	if (friends_num >= 0 && friends_num <= 10) {
		pages_num++;
		likedPages[pages_num]->setterForUser(obj);
	}
}

//this function will print the profile page of user
void userClass::viewProfilePage(RenderWindow* window) {

	int size = 24;
	if (numberOfPosts + total_user_memories >= 5) {
		size = 12;
	}
	text.setPosition(window->getSize().x / 2 - 150, 0);
	text.setCharacterSize(size);
	text.setFillColor(sf::Color::White);
	int count = 5;

	String firstName(this->first_name);
	String lastName(this->last_name);
	text.setString(firstName + " " + lastName + "-- PROFILE PAGE\n\n");
	window->draw(text);
	for (int i = 0; i < numberOfPosts; i++) {
		listOfPosts[i]->viewPost( window, count);
	}
	for (int i = 0; i < total_user_memories; i++) {
		user_memories[i]->viewPost(window,count);
	}

}

void userClass::ownerNameGetter(RenderWindow* window , int &count) {
	text.setFillColor(Color(162, 59, 138, 200));
	String firstName(this->first_name);
	String lastName(this->last_name);
	text.setString(firstName + " " + lastName + " ");
	text.setPosition(window->getSize().x / 2 - 350, count);
	window->draw(text);
}

void userClass::postLike(postClass* obj) {
	obj->setterForUserLike(this);
}

//This function add comment from user side
void userClass::addComment(postClass*obj,char*comment) {
	obj->postComment(this,comment);
}

void userClass::USERDATASETTER(char*ID, char*f_name, char*l_name) {
	userID = new char[helper::strlength(ID)+1];
	first_name = new char[helper::strlength(f_name)+1];
	last_name = new char[helper::strlength(l_name) + 1];

	helper::strcopy(ID, userID);
	helper::strcopy(f_name, first_name);
	helper::strcopy(l_name, last_name);
}

void userClass::USER_PAGELIKER_SETTER(pageClass** p, int page) {
	this->pages_num = page;
	this->likedPages = new pageClass * [page];

	for (int i = 0; i < page; i++) {
		this->likedPages[i] = p[i];
	}
}

void userClass::SETTER(char* id, char* f_name, char*l_name,  userClass**u, pageClass**p, int u_num, int p_num, postClass**pos, int pos_num) {
	
	this->userID = new char[helper::strlength(id) + 1];
	this->first_name = new char[helper::strlength(f_name) + 1];
	this->last_name = new char[helper::strlength(l_name) + 1];

	this->friends_num = u_num;
	this->pages_num = p_num;
	this->numberOfPosts = pos_num;
	helper::strcopy(id, this->userID);
	helper::strcopy(f_name, this->first_name);
	helper::strcopy(l_name, this->last_name);
	for (int i = 0; i < u_num; i++) {
		friends[i] = u[i];
	}
	for (int i = 0; i < p_num; i++) {
		likedPages[i] = p[i];
	}
	for (int i = 0; i < pos_num; i++) {
		listOfPosts[i] = pos[i];
	}
}

void userClass::USER_FRIEND_SETTER(userClass** u,int friends) {
	this->friends_num = friends;

	this->friends = new userClass*[friends];
	


	for (int i = 0; i < friends; i++) {
		this->friends[i] = new userClass();
		this->friends[i]->SETTER(u[i]->userID, u[i]->first_name, u[i]->last_name,u[i]->friends,u[i]->likedPages,u[i]->friends_num,u[i]->pages_num,u[i]->listOfPosts,u[i]->numberOfPosts);
	}
	
}

//This function display the home page of user in terms of date
void userClass::viewHome(userClass**u,pageClass**p,int total_users,int total_pages,dateClass D, RenderWindow* window)
{
	int count = 5;

	int size = 20;
	if (numberOfPosts + total_user_memories >= 4) {
		size = 14;
		count = 0;
	}
	text.setPosition(window->getSize().x / 2-150, 0);
	text.setCharacterSize(size);
	text.setFillColor(Color	(162, 59, 138, 200));
	

	String firstName(this->first_name);
	String lastName(this->last_name);
	text.setString(firstName + " " + lastName + "-- HOME PAGE\n\n");

	window->draw(text);
	text.setFillColor(Color::White);

	for (int i = 0; i < numberOfPosts; i++) {
		if ((D.yearGetter() == listOfPosts[i]->postYEARGetter()) && (D.monthGetter() == listOfPosts[i]->postMONTHGetter()) && (D.dayGetter() == listOfPosts[i]->postDAYGetter() || (D.dayGetter() == listOfPosts[i]->postDAYGetter() + 1)))
			this->listOfPosts[i]->viewPost(window,count,size);
	}
	for (int j = 0; j < total_user_memories; j++) {

		if ((D.yearGetter() == user_memories[j]->postYEARGetter()) && (D.monthGetter() == user_memories[j]->postMONTHGetter()) && (D.dayGetter() == user_memories[j]->postDAYGetter() || (D.dayGetter() == user_memories[j]->postDAYGetter() + 1)))
			user_memories[j]->viewPost(window, count,size);
	}

	for (int i = 0; i < friends_num; i++) {
		int index = 0;
		for (int k = 0; k < total_users; k++) {
			if (helper::strCompare(this->friends[i]->getId(), u[k]->getId())) {
				index = k;
				break;
			}
		}
		for (int j = 0; j<u[index]->numberOfPosts; j++) {

		if ((D.yearGetter() == u[index]->listOfPosts[j]->postYEARGetter()) && (D.monthGetter() == u[index]->listOfPosts[j]->postMONTHGetter()) && (D.dayGetter() == u[index]->listOfPosts[j]->postDAYGetter() || (D.dayGetter() == u[index]->listOfPosts[j]->postDAYGetter() + 1)))
			u[index]->listOfPosts[j]->viewPost(window, count,size);
		}
		for (int j = 0; j < u[index]->total_user_memories; j++) {

			if ((D.yearGetter() == u[index]->user_memories[j]->postYEARGetter()) && (D.monthGetter() == u[index]->user_memories[j]->postMONTHGetter()) && (D.dayGetter() == u[index]->user_memories[j]->postDAYGetter() || (D.dayGetter() == u[index]->user_memories[j]->postDAYGetter() + 1)))
				u[index]->user_memories[j]->viewPost(window, count,size);
		}
	}
	for (int i = 0; i < pages_num; i++) {
		int index = 0;
		for (int k = 0; k < total_pages; k++) {
			if (helper::strCompare(this->likedPages[i]->getId(), p[k]->getId())) {
				index = k;
				break;
			}
		}

		for (int j = 0;j<p[index]->numOfPostGetter(); j++) {

			if ((D.yearGetter() == p[index]->pagePostGetter(j)->postYEARGetter()) && (D.monthGetter() == p[index]->pagePostGetter(j)->postMONTHGetter()) && (D.dayGetter() == p[index]->pagePostGetter(j)->postDAYGetter() || (D.dayGetter() == p[index]->pagePostGetter(j)->postDAYGetter() + 1)))
			p[index]->pagePostGetter(j)->viewPost(window, count,size);
		}
	}
}

//This functions set list of posts which the user owned
void userClass::listOfPostsSetter(postClass* post) {
	listOfPosts[numberOfPosts] = new postClass();
	listOfPosts[numberOfPosts] = post;
	this->numberOfPosts++;
}

//This function print the ids of those posts which the user owned
void userClass::viewListOfPosts(RenderWindow *window) {
	text.setPosition(window->getSize().x / 2 - 150, 0);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color(162, 59, 138, 200));
	text.setString("YOUR POSTS ARE");
	window->draw(text);
	int count = 20;
	text.setFillColor(Color::White);
	for (int i = 0; i < this->numberOfPosts; i++) {
		String id(this->listOfPosts[i]->getId());
		text.setString(id);
		text.setPosition(window->getSize().x / 2 - 50, count+(i*30));
		window->draw(text);
	}
	count += numberOfPosts * 30;
	for (int i = 0; i < total_user_memories; i++) {
		String id(this->user_memories[i]->getId());
		text.setString(id);
		text.setPosition(window->getSize().x / 2 - 50,count+ (i * 30));
		window->draw(text);
	}
}

//checks the posts which userasked to mae the memory belongs to him or not
bool userClass::memoryChecker(char* id) {
	for (int i = 0; i < numberOfPosts; i++) {
		if (helper::strCompare(listOfPosts[i]->getId(), id)) {
			return true;
		}
	}
	return false;
}

int userClass::num_memory_getter() {
	return total_user_memories;
}

//---------------------------------------------

//Page functions

pageClass::pageClass() {
	pageID = nullptr;
	pgtitle = nullptr;
	owner = nullptr;
	numberOfPosts = 0;
	listOfPosts = new postClass*[10];
	for (int i = 0; i < 10; i++) {
		listOfPosts[i] = 0;
	}
}

pageClass::~pageClass() {
	if (pageID != 0) {
		delete[] pageID;
		pageID = 0;
	}
	if (pgtitle != 0) {

		delete[] pgtitle;
		pgtitle = 0;
	}
	if (owner != 0) {
		owner = 0;
	}
	if (listOfPosts != 0) {
		for (int i = 0; i < numberOfPosts; i++) {
			delete listOfPosts[i];
		}
		delete[] listOfPosts;
		listOfPosts = 0;
	}
}

//This function set the pages data which will extract from file
void pageClass::pageSetter(char*id,char*t,userClass *ow) {

	this->pageID = new char[helper::strlength(id) + 1];
	this->pgtitle = new char[helper::strlength(t) + 1];
	this->owner = new userClass();

	helper::strcopy(id, pageID);
	helper::strcopy(t, pgtitle);
	owner = ow;
}

int pageClass::numOfPostGetter() {
	return this->numberOfPosts;
}

postClass* pageClass::pagePostGetter(int index) {
	return listOfPosts[index];
}

void pageClass::getterForUser(RenderWindow* window,int &count) {
	string id(pageID);
	string ti(pgtitle);
	text.setString(id + "-- " + ti + "\n");
	text.setPosition(window->getSize().x / 2 - 100, count);
	window->draw(text);
}

void pageClass::setterForUser(pageClass&obj) {
	this->pageID = obj.pageID;
	this->pgtitle = obj.pgtitle;
}

//This function displays the all page data
void pageClass::viewPage(RenderWindow* window) {
	int count=5;
	
	string id(pageID);
	string ti(pgtitle);
	text.setString(id + "-- " + ti + "\n");
	text.setPosition(window->getSize().x / 2 - 100, count);
	text.setFillColor(Color(162, 59, 138, 200));
	window->draw(text);
	text.setFillColor(Color::White);
	count += 30;
	for (int i = 0; i < this->numberOfPosts; i++) {
		listOfPosts[i]->viewPost(window,count);
	}
}

void pageClass::setId(char* id) {
	pageID = new char[helper::strlength(id) + 1];
	helper::strcopy(id, pageID);
}

char* pageClass::getId() {
	return pageID;
}

void pageClass::setTitle(char*t) {
	pgtitle = new char[helper::strlength(t) + 1];
	helper::strcopy(t, pgtitle);
}

char* pageClass::getTitle() {
	return pgtitle;
}

void pageClass::pageTitleGetter(RenderWindow*window,int &count) {
	text.setFillColor(Color(162, 59, 138, 200));
	string title(pgtitle);
	text.setString(title + " ");
	text.setPosition(window->getSize().x / 2 - 350, count);
	window->draw(text);
}

void pageClass::addNewComment(postClass&obj,char*comment) {
	obj.postComment(this,comment);
}

void pageClass::listOfPostSetter(postClass* post) {
	listOfPosts[numberOfPosts] = new postClass();
	listOfPosts[numberOfPosts] = post;
	this->numberOfPosts++;
}

//---------------------------------------------

//post class

postClass::postClass() {
	postID=nullptr;
	post_discription= nullptr;
	num_of_likes=0;
	num_of_comments=0;
	postOfPage= nullptr;
	listOfLikesUsers = nullptr;
	listOfLikesPages = nullptr;
	postOfUser = nullptr;
	num_of_comments = 0;
	commentOnPost = new commentClass * [10];
	for (int i = 0; i < 10; i++) {
		commentOnPost[i] = new commentClass();
	}
	post_activity = nullptr;
}

postClass::~postClass() {
	if (postID != nullptr) {
		delete[] postID;
		postID = nullptr;
	}
	if (post_discription != nullptr) {
		delete[] post_discription;
		post_discription = nullptr;
	}
	if (listOfLikesPages != nullptr) {
		delete listOfLikesPages;
		listOfLikesPages = nullptr;
	}
	if (listOfLikesUsers != nullptr) {
		listOfLikesUsers = nullptr;
	}
	if (commentOnPost != nullptr) {
		for (int i = 0; i < num_of_comments; i++) {
			delete commentOnPost[i];
			commentOnPost[i] = nullptr;
		}
		delete[] commentOnPost;
		commentOnPost = nullptr;
	}
	if (post_activity != 0) {
		delete post_activity;
		post_activity = nullptr;
	}
}

//This function set the posts data which will extract from file
void postClass::setPostData(char* id, int d, int m, int y, char* text, int aV, char* aT, userClass* owner,pageClass* powner,userClass**userliker,pageClass**pageLiker,int totalLiker){
	postID = new char[helper::strlength(id) + 1];
	post_discription = new char[helper::strlength(text) + 1];
	postOfUser = new userClass();
	postOfPage = new pageClass();
	listOfLikesPages = new pageClass * [totalLiker];
	for (int i = 0; i < totalLiker; i++) {
		listOfLikesPages[i] = new pageClass();
	listOfLikesPages[i] = pageLiker[i];
	}
	listOfLikesUsers = new userClass * [totalLiker];
	for (int i = 0; i < totalLiker; i++) {
		listOfLikesUsers[i] = new userClass();
	listOfLikesUsers[i] = userliker[i];
	}



	helper::strcopy(id,postID);
	this->post_date.dateSetter(d, m, y);
	helper::strcopy(text, post_discription);
	postOfUser = owner;
	postOfPage = powner;
	num_of_likes = totalLiker;
	post_activity = new activityClass();
	this->post_activity->setterForPost(aV, aT);
	if (owner) {
		owner->listOfPostsSetter(this);
	}
	if (powner) {
		powner->listOfPostSetter(this);
	}

}

char* postClass::getId() {
	return postID;
}

//This function display the specific post to user
void postClass::viewPost(RenderWindow* window, int& count,int size) {
	int product;
	if (size <= 20) {
		product = 6;
	}
	else {
		product = 7;
	}
	count +=(3*product);
	text.setCharacterSize(size);

	string post("POST ID");
	string post2(this->postID);
	text.setString(post +"--- "+ post2+ "\t\t");
	text.setPosition(window->getSize().x / 2 - 550, count);
	window->draw(text);
	if (postOfUser!=0) {
		postOfUser->ownerNameGetter(window,count);
	}
	else {
		postOfPage->pageTitleGetter(window, count);
	}
	text.setFillColor(Color::White);
	post_activity->getterForViewPost(window, count);
	post_date.viewDate(window, count);
			count += (4*product);
	
	text.setString(post_discription);
	text.setPosition(window->getSize().x / 2 - 350, count);
	window->draw(text);
	for (int i = 0; i < num_of_comments; i++) {
		count +=(4*product);
		commentOnPost[i]->getterForPost(window,count);
		
	}
	count += (3*product);

}

//This function add users like into the post
void postClass::setterForUserLike(userClass*ptr) {
		listOfLikesUsers[num_of_likes] = new userClass();
		listOfLikesUsers[num_of_likes] = ptr;
		num_of_likes++;
}

//This function add users comment into the post
void postClass::postComment(userClass* ptr,char* comment) {
		commentOnPost[num_of_comments]->commentSetterUser(ptr,comment);
		++num_of_comments;

}

void postClass::postComment(pageClass* ptr,char*comment) {
	
		commentOnPost[num_of_comments]->commentSetterPage(ptr,comment);
		num_of_comments++;
}

//Display the list of likes on specific post
void postClass::viewlistoflikes(RenderWindow* window) {
	text.setPosition(window->getSize().x / 2 - 150, window->getSize().y / 2 - 235);
	text.setFillColor(sf::Color(162, 59, 138, 250));
	text.setCharacterSize(40);
	int count = 30;

	String id(this->postID);
	text.setString(id + "--liked list\n\n");
	window->draw(text);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	for (int i = 0; i < num_of_likes; i++) {
		count += 30;
		if (listOfLikesUsers[i] != 0)
		{
			String ID(listOfLikesUsers[i]->getId());
			String fname(listOfLikesUsers[i]->getFirstname());
			String lname(listOfLikesUsers[i]->getLastname());
			text.setString(ID + " " + fname + " " + lname+"\n");
			text.setPosition(window->getSize().x / 2 - 100, window->getSize().y / 2 -235+count - 15);
			window->draw(text);
		}
		else
		{
			String pID(listOfLikesPages[i]->getId());
			String t(listOfLikesPages[i]->getTitle());
			text.setString(pID + " " + t+ "\n");
			text.setPosition(window->getSize().x / 2 - 100, window->getSize().y / 2-235 + count - 15);
			window->draw(text);
		}
	}
}

//This function sets the comment on the post
void postClass::commentSetterPost(commentClass** tempC, int i) {
	
	commentOnPost[num_of_comments]->COMMENTSETTER(tempC[i]->commentOwnerGetter(),tempC[i]->commentTextGetter(), tempC[i]->commentIDGetter(), tempC[i]->commentOwnerGetterpg());
	this->num_of_comments++;

}

int postClass::postDAYGetter() {
	return this->post_date.dayGetter();
}

int postClass::postMONTHGetter() {
	return this->post_date.monthGetter();
}

int postClass::postYEARGetter() {
	return this->post_date.yearGetter();
}

int postClass::numOfCommentGetter() {
	return num_of_comments;
}

int postClass::num_like_getter() {
	return this->num_of_likes;
}

//---------------------------------------------

//Activity function

activityClass::activityClass() {
	activity_type = 0;
	activity_text = nullptr;
	activity_Value = nullptr;
}

activityClass::~activityClass() {
	if (activity_Value != 0) {
		delete activity_Value;
		activity_Value = 0;
	}
	if (activity_text != 0) {
		delete activity_text;
		activity_text = 0;
	}
}

//sets the activity of post
void activityClass::setterForPost(int aV, char* aT) {
	
	if (aV != 0) {
		activity_text = new char[helper::strlength(aT) + 1];
		activity_Value = new char[50];
	 
		helper::strcopy(aT, activity_text);
		activity_type = aV;
		if (activity_type == 1) {
			helper::strcopy("is feeling ", activity_Value);

		}
		else if (activity_type == 2) {
			helper::strcopy("is thinking about ", activity_Value);
		}
		else if (activity_type == 3) {
			helper::strcopy("is making ", activity_Value);
		}
		else {
			helper::strcopy("is celebrating ", activity_Value);
		}
		
	

	}
}

//Shows the activity of post
void activityClass::getterForViewPost(RenderWindow* window, int& count) {
	if (activity_type != 0) {
		string value(this->activity_Value);
		string atext(this->activity_text);
		text.setString(value + " " + atext + "\n\n");
		text.setPosition(window->getSize().x / 2-150 , count);
		window->draw(text);
	}
}

//---------------------------------------------

//Date Functions

dateClass::dateClass() {
	this->day = 15;
	this->month = 11;
	this->year = 2017;
 }

void dateClass::viewDate(RenderWindow*window, int& count) {
	text.setString("(" + to_string(day) + "/" + to_string(month) + "/" + to_string(year) + ")");
	text.setPosition(window->getSize().x / 2+400, count);
	window->draw(text);
}

void dateClass::dateSetter(int d, int m, int y) {
	day = d;
	month = m;
	year = y;
}

int dateClass::dayGetter() {
	return day;
}

int dateClass::monthGetter() {
	return month;
}

int dateClass::yearGetter() {
	return year;
}

//---------------------------------------------

//Comment Functions
commentClass::commentClass() {
	commentID = nullptr;
	comment_text = nullptr;
	comment_owner = nullptr;
	commentOwnerPG = nullptr;
}

commentClass::~commentClass() {

	if (comment_text != nullptr && commentID != nullptr) {
		delete[] comment_text;
		comment_text = nullptr;
	}
	if (commentID != nullptr) {
		delete[]commentID;
		commentID = nullptr;
	}
	if (comment_owner != nullptr) {
		comment_owner = nullptr;
	}
	if (commentOwnerPG != nullptr) {
		commentOwnerPG = nullptr;
	}
}

//Display the comments of posts
void commentClass::getterForPost(RenderWindow* window,int& count) {
	if (comment_owner)
	{
		this->comment_owner->ownerNameGetter(window,count);
	}
	else {
		this->commentOwnerPG->pageTitleGetter(window,count);
	}
	text.setFillColor(Color::White);

	string d("commented: ");
	string t(comment_text);
	text.setString(d + t);
	text.setPosition(window->getSize().x / 2 - 150, count);
	window->draw(text);
}

//Sets the new comment
void commentClass::commentSetterUser(userClass* ptr,char* comment) {

	comment_owner = new userClass();
	this->comment_owner = ptr;
	comment_text = new char[1000];
	comment_text=comment;
}

void commentClass::commentSetterPage(pageClass* ptr,char* comment) {
	commentOwnerPG = new pageClass();
	this->commentOwnerPG = ptr;
	comment_text = new char[1000];
		comment_text = comment;

}

//Sets the existed comments 
void commentClass::COMMENTSETTER(userClass* u, char* text, char* ID, pageClass*p) {
	this->comment_owner = new userClass();
	this->commentOwnerPG = new pageClass();
	this->comment_text = new char[helper::strlength(text) + 1];
	this->commentID = new char[helper::strlength(ID) + 1];

	helper::strcopy(ID, commentID);
	helper::strcopy(text, comment_text);
	comment_owner = u;
	commentOwnerPG = p;
}

userClass* commentClass::commentOwnerGetter() {
	return this->comment_owner;
}

pageClass* commentClass::commentOwnerGetterpg() {
	return this->commentOwnerPG;
}

char* commentClass::commentIDGetter() {
	return commentID;
}

char* commentClass::commentTextGetter() {
	return comment_text;
}

//---------------------------------------------

//Memories

memoryClass::memoryClass() {
	this->listOfLikesUsers = new userClass*[10];
	for (int i = 0; i < 10; i++) {
		listOfLikesUsers[i] = nullptr;
	}
	this->postMeomery = nullptr;
}

memoryClass::~memoryClass() {
	if (postMeomery != nullptr) {
		postMeomery = nullptr;
	}
}

//Add the new memory
void memoryClass::addMemory(postClass*obj,char*t,postClass**p,int total_posts, int memory_num,userClass* owner) {
	int firstI = (total_posts + memory_num) / 10;
	int firstII = (total_posts + memory_num) % 10;

	char id1 = static_cast<char>(firstI)+'0';
	char id2= static_cast<char>(firstII)+'0';
	postID = new char[8];
	this->postID=helper::strcopy("post",id1,id2, postID);
	this->postOfUser = new userClass();
	postOfUser = owner;
	this->post_discription = new char[1000];
	helper::strcopy(t, post_discription);
	this->post_date;

	postMeomery = obj;
	
}

//overriding
//Display the posted memory
void memoryClass::viewPost(RenderWindow* window,int&count,int size) {

	text.setPosition(window->getSize().x / 2 - 620, count);
	text.setCharacterSize(size);
	text.setFillColor(Color::White);
	String id("POST ID-- ");
	string ID(postID);
	text.setString(id+ID);
	window->draw(text);
	string fname(postOfUser->getFirstname());
	string lname(postOfUser->getLastname());
	text.setString(fname + " " + lname);
	text.setPosition(window->getSize().x / 2 - 350, count);
	window->draw(text);
	count += 18;
	text.setString(this->post_discription);
	text.setPosition(window->getSize().x / 2 - 400, count);

	window->draw(text);
	this->post_date.viewDate(window, count);


	count +=10;
	this->postMeomery->viewPost(window, count,size);
	for (int i = 0; i < num_of_comments; i++) {
		count += 18;
		this->commentOnPost[i]->getterForPost(window, count);
	}
	count += 18;
}

//---------------------------------------------


//Social Network App functions

socialNetworkApp::socialNetworkApp() {
	users = nullptr;
	pages = nullptr;
	posts = nullptr;
	memories = nullptr;
	total_pages = 0;
	total_posts = 0;
	total_users = 0;
	total_memories = 0;
}

socialNetworkApp::~socialNetworkApp() {
	if (users != 0) {
		for (int i = 0; i < total_users; i++) {
			delete users[i];
			users[i] = 0;
		}
		
		delete[]users;
		users = 0;
	}
	if (pages != 0) {
		for (int i = 0; i < total_pages; i++) {
			delete pages[i];
			pages[i] = 0;
		}
		delete[]pages;
		pages = 0;
	}
	if (posts != 0) {
		delete[]posts;
		posts = 0;
	}
	if (memories!=0) {
		delete[]memories;
		memories = 0;
	}
}

//All the main functionality belonngs to this func
void socialNetworkApp::run() {

	//Data Loading
	//--------------------------------------------------------
	//Page
	ifstream pageFile("Pages.txt");
	if (!pageFile) {
		cerr << "PAGE File not found" << endl;
	}
	pageFile >> total_pages;
	pages = new pageClass * [total_pages];
	for (int i = 0; i < total_pages; i++) {
		pages[i] = new pageClass();
	}

	//USER
	ifstream userfile("Users.txt");
	if (!userfile) {
		cerr << "USER File not found" << endl;
	}
	userfile >> total_users;
	users = new userClass * [total_users];

	for (int i = 0; i < total_users; i++) {
		users[i] = new userClass();
	}

	helper::dataReaderUser(users, userfile, total_users, pages);

	helper::dataReaderPage(pages, pageFile, total_pages, users, total_users);

	helper::dataReaderUser_PAGE(users, userfile, total_users, pages, total_pages);

	//POSTS
	ifstream postfile("Posts.txt");
	if (!postfile) {
		cerr << "POST File not found" << endl;
	}

	postfile >> total_posts;
	posts = new postClass * [total_posts];
	for (int i = 0; i < total_posts; i++) {
		posts[i] = new postClass();
	}
	helper::dataReaderPosts_Comments(posts, postfile, total_posts, pages, users, total_users, total_pages);
	dateClass currentDate;

	//-------------------------------------------------------------
	
	//SFML

	//Background image loading
	Texture texture;
	if (!texture.loadFromFile("background11.jpg")) {
		cerr << "Failed to load background image." << std::endl;
	}

	Texture texture2;
	if (!texture2.loadFromFile("background12.jpg")) {
		cerr << "Failed to load background image." << std::endl;
	}

	Texture texture3;
	if (!texture3.loadFromFile("background13.jpg")) {
		cerr << "Failed to load background image." << std::endl;
	}

	//Creat window
	RenderWindow window(VideoMode(texture.getSize().x, texture.getSize().y), "SOCIAL NETWORK APP");

	//Background structure 
	RectangleShape square;
	square.setSize(Vector2f(texture.getSize().x, texture.getSize().y));
	square.setOrigin(0.0f, 0.0f);
	square.setPosition(Vector2f(0.0f,0.0f));
	square.setTexture(&texture);

	//Dispaly Font
	Font font;
	if (!font.loadFromFile("times.ttf")) {
		std::cerr << "Failed to load font." << std::endl;
	}

	if (!fun_font.loadFromFile("times.ttf")) {
		std::cerr << "Failed to load font." << std::endl;
		return;
	}

	//For output text
	Text outputText("", font);
	outputText.setCharacterSize(58);
	outputText.setFillColor(Color(162,59,138, 200));
	outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);

	//For display id after logon
	Text idText("", font);
	idText.setCharacterSize(58);
	idText.setFillColor(Color(162, 59, 138, 200));

	//For input text
	Text inputText("", font);
	inputText.setCharacterSize(24);
	inputText.setFillColor(Color::White);
	inputText.setPosition(window.getSize().x / 2 - inputText.getLocalBounds().width / 2 -15, window.getSize().y / 2 - inputText.getLocalBounds().height / 2 + 50);

	
	Text postInputText("", font);
	postInputText.setCharacterSize(24);
	postInputText.setFillColor(sf::Color::White);
	postInputText.setPosition(window.getSize().x / 2 - inputText.getLocalBounds().width / 2, window.getSize().y / 2 - inputText.getLocalBounds().height / 2 + 50);

	Text heading("", font);
	Text subheading("", font);
	Text menuText[11];

	//For menu dispaly
	RectangleShape menu[11];
	for (int i = 0; i < 11; i++) {
		menu[i].setSize(Vector2f(320.0f, 35.0f));
		menu[i].setOrigin(menu[i].getSize().x / 2, menu[i].getSize().y / 2);
		menu[i].setPosition(Vector2f(window.getSize().x / 2, 30 + (i * 55)));
		menu[i].setFillColor(Color::Transparent);
		menu[i].setOutlineColor(Color::White);
		menu[i].setOutlineThickness(1);
		menuText[i].setFont(font);
		menuText[i].setCharacterSize(24);
		menuText[i].setFillColor(sf::Color::White);

	
		if (i == 0) {
			menuText[i].setString("LogOut");
		}
		else if (i == 1) {
			menuText[i].setString("Home Page");
		}
		else if (i == 2) {
			menuText[i].setString("Like a Post");
		}
		else if (i == 3) {
			menuText[i].setString("Liked list");
		}
		else if (i == 4) {
			menuText[i].setString("Add Comment");
		}
		else if (i == 5) {
			menuText[i].setString("View Post");
		}
		else if (i == 6) {
			menuText[i].setString("Share Memory");
		}
		else if (i == 7) {
			menuText[i].setString("Personal Page");
		}
		else if (i == 8) {
			menuText[i].setString("Friend List");
		}
		else if (i == 9) {
			menuText[i].setString("View Page");
		}
		else if (i == 10) {
			menuText[i].setString("Exit");
		}
		float textPosX = menu[i].getPosition().x;
		float textPosY = menu[i].getPosition().y - menu[i].getSize().y / 2 + menuText[i].getCharacterSize() / 2;
		menuText[i].setPosition(textPosX, textPosY);
		menuText[i].setOrigin(menuText[i].getLocalBounds().width / 2, menuText[i].getLocalBounds().height / 2);
	}

	char userInput[100];
	int userInputIndex = 0;
	int postInputIndex = 0, pageInputIndex = 0,postindex=0;
	char pinput[50];
	char comment[100],mem_text[1000];

	bool menu4 = false, menu5 = false, menu2 = false, menu3 = false, menu6 = false, menu8 = false, menu9 = false;
	bool menu7 = false, menu1 = false, menu10 = false;
	bool comment_checker = false, comment_done = false;
	bool memory_checker = false;
	bool viewPost = false;
	bool likedList_checker=false;
	bool postTab = false, pagetab = false;
	bool enterChecker = false;
	bool addlike_checker = false;
	bool loggedIn = false;
	bool inputMode = false;
	bool error = false;
	bool menu_checker = false;
	bool memory_done= false, loop = false, escape_checker = false,loop_checker=false;
	int menu_index, userIndex;
	int checker = -1;
	int stoper = 0;
	int memoryIndex = 0;
	bool postIDChecker = false;
	bool backChecker = false;

	// For Sounds 
	string successMsg;
	SoundBuffer like;
	if (!like.loadFromFile("like.mp3")) {
		cerr << "Like sound not found" << endl;
	}
	SoundBuffer click;
	if (!click.loadFromFile("click.mp3")) {
		cerr << "Like sound not found" << endl;
	}
	SoundBuffer menuSound;
	if (!menuSound.loadFromFile("menu.mp3")) {
		cerr << "Like sound not found" << endl;
	}
	SoundBuffer memorySound;
	if (!memorySound.loadFromFile("memory.mp3")) {
		cerr << "Like sound not found" << endl;
	}
	SoundBuffer commentSound;
	if (!commentSound.loadFromFile("comment.mp3")) {
		cerr << "Like sound not found" << endl;
	}
	Sound sound;

	//Main loop
	while (window.isOpen()) {
		Event EVENT;
		//Event manipulating loop
		while (window.pollEvent(EVENT)) {
			if ((postTab || pagetab) && loop_checker) {
				outputText.setString("Kindly Press Enter");
				outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
				loop_checker = false;
			}
				window.clear(Color::White);
				window.draw(square);
			

			if (EVENT.type == Event::Closed) {
				memory_checker = false;
				window.close();
			}
			else if (EVENT.type == Event::KeyPressed) {
				if (!loggedIn) {
					if (!inputMode) {
						if (EVENT.key.code == Keyboard::Enter) {
							sound.setBuffer(click);
							sound.play();
							if (!postTab&& !pagetab)
							{
									outputText.setString("USER ID");
								outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
								inputMode = true;
								square.setTexture(&texture2);
							}
							else if (pagetab) {
								outputText.setString("PAGE ID");
								outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
								inputMode = true;
							}
							else {
								
								outputText.setString("POST ID");
								outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
								inputMode = true;

							}
						}
					}
					else {
						if (EVENT.key.code == Keyboard::Enter) {
							sound.setBuffer(click);
							sound.play();
							if (comment_checker) {
								helper::strcopy(userInput, comment);
								comment_checker = false;
								comment_done = true;
								loggedIn = true;
								userInput[userInputIndex] = '\0';
								inputMode = false;
								enterChecker = true;
								postTab = false;
							}
							else if (memory_checker) {
								helper::strcopy(userInput, mem_text);
								memory_checker = false;
								memory_done = true;
								loggedIn = true;
								userInput[userInputIndex] = '\0';
								inputMode = false;
								enterChecker = true;
								postTab = false;
							}
							else
							{
								bool id_checker = false;
			//For User		
								if (!postTab && !pagetab) {

									for (int i = 0; i < total_users;) {
										if (helper::strCompare(userInput, users[i]->getId()))
										{
											userIndex = i;
											id_checker = true;
											break;
										}
										i++;
									}
									if (id_checker)
									{
										loggedIn = true;
										userInput[userInputIndex] = '\0';
										string successMsg = string(userInput) + " logged on\n---------------\n Press Enter";
										outputText.setString(successMsg);
										outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
										inputMode = false;
										enterChecker = true;
									}
									else {
										outputText.setString("USER NOT FOUND");
										outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
										error = true;
									}
								}
			//For Page
								else if (pagetab) {
									for (int i = 0; i < total_pages;) {
										if (helper::strCompare(userInput, pages[i]->getId()))
										{
											pageInputIndex = i;
											id_checker = true;
											break;
										}
										i++;
									}
									if (id_checker)
									{

										userInput[userInputIndex] = '\0';
										inputMode = false;
										enterChecker = true;
										pagetab = false;
										menu9 = true;
									}
									else {
										outputText.setString("PAGE NOT FOUND");
										outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
										error = true;
									}
								}
			//For Post
								else if(postTab) {
									for (int i = 0; i < total_posts;) {
										if (helper::strCompare(userInput, posts[i]->getId()))
										{
											if (menu6) {

												if (users[userIndex]->memoryChecker(userInput))
												{
													postindex = i;
													id_checker = true;
													postIDChecker = false;
													break;
												}
											}
											else {
												postindex = i;
												id_checker = true;
												postIDChecker = false;
												break;
											}
										}
										else {
											postIDChecker = true;
										}
										i++;

									}
									if (postIDChecker) {

										for (int i = 0; i < total_memories; i++) {
			
											if (helper::strCompare(userInput, memories[i]->getId()))
											{
													memoryIndex = i;
													id_checker = true;
													break;
											
											}
										}
									
									}
			//id Checher
									if (id_checker)
									{
										if (menu2)
											addlike_checker = true;
										if (menu3)
											likedList_checker = true;
										if (menu5)
											viewPost = true;

										if (menu6)
										{
											outputText.setString("Enter TEXT");
											outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
											memory_checker = true;
											menu6 = false;
										}

			//Comment Input
										else if (menu4) {
											if(posts[postInputIndex]->numOfCommentGetter()<10)
												{
													outputText.setString("Enter Comment");
													outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
													comment_checker = true;
													menu4 = false;
												}
												else {
													outputText.setString("SORRY ALREADY 10 COMMENTS AVALIBLE");
													outputText.setPosition(window.getSize().x / 2-100 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
													menu4 = false;
												}
										}
										else {
											loggedIn = true;
											userInput[userInputIndex] = '\0';
											inputMode = false;
											enterChecker = true;
											postTab = false;

										}

									}
									else {
										outputText.setString("POST NOT FOUND");
										outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
										error = true;
									}
								}
							}
						}
		//Backspace
						else if (EVENT.key.code == Keyboard::Backspace) {
							if (userInputIndex > 0) {
								userInputIndex--;
								userInput[userInputIndex] = '\0';
								inputText.setString(userInput);
							}
							if (error && (!postTab) && (!pagetab)) {
								outputText.setString("USER ID");
								outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
								error = false;
							}
							else if (error && (postTab) && (!pagetab)&&(!comment_checker)&&(!memory_checker)) {

								outputText.setString("POST ID");
								outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
								error = false;
							}
							else if (error && (!postTab) && (pagetab)) {
								outputText.setString("PAGE ID");
								outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
								error = false;

							}
							else if(comment_checker){
								outputText.setString("Enter Comment");
								outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
								error = false;
							}
							else if(memory_checker){
								outputText.setString("Enter TEXT");
								outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
								error = false;

							}
						}
						else {
							
		//Input System
							if ((EVENT.key.code >= Keyboard::A && EVENT.key.code <= Keyboard::Z) ||
								(EVENT.key.code >= Keyboard::Num0 && EVENT.key.code <= Keyboard::Num9) ||
								EVENT.key.code == Keyboard::Period ||
								EVENT.key.code == Keyboard::Space) {
								if (EVENT.key.code >= Keyboard::A && EVENT.key.code <= Keyboard::Z) {
									userInput[userInputIndex] = EVENT.key.code + 'a';
								}
								else if (EVENT.key.code == Keyboard::Space) {
									userInput[userInputIndex] = static_cast<char>(EVENT.key.code-25);

								}
								else {
									userInput[userInputIndex] = static_cast<char>(EVENT.key.code + '0' - 26);
								}
								userInputIndex++;
								userInput[userInputIndex] = '\0';
								inputText.setString(userInput);
							}
						}
						

					}
				}
				else if (EVENT.key.code == Keyboard::Enter && enterChecker) {
					sound.setBuffer(click);
					sound.play();
					outputText.setCharacterSize(0);
					int index = 0;
					for (int i = 0; i < total_users; i++) {
						if (helper::strCompare(userInput, users[i]->getId()))
						{
							index = i;
							break;
						}

					}
					idText.setString(users[userIndex]->getId());
					idText.setPosition(0, 0);
					idText.setCharacterSize(50);
					outputText.setCharacterSize(50);
					menu_checker = true;
					square.setTexture(&texture3);
					backChecker = true;

					enterChecker = false;
				}
			}
	
	//For Menu
			else if (menu_checker) {
				

				if (EVENT.key.code == sf::Keyboard::Down) {
					sound.setBuffer(menuSound);
					sound.play();
					if (checker != -1) {

						menu[checker].setOutlineThickness(1);
						menu[checker].setOutlineColor(Color::White);
					}
					checker = (checker + 1) % 11; 
					menu[checker].setOutlineThickness(5);
					menu[checker].setOutlineColor(Color(162, 59, 138, 200));
					loop = true;
				}
				else if (EVENT.key.code == sf::Keyboard::Up) {
					sound.setBuffer(menuSound);
					sound.play();
					if (checker != -1) {
						menu[checker].setOutlineThickness(1);
						menu[checker].setOutlineColor(Color::White);
					}
					checker = (checker == -1) ? 10 : (checker == 0) ? 10 : checker - 1;
					menu[checker].setOutlineThickness(5);
					menu[checker].setOutlineColor(Color(162, 59, 138, 200));
					loop = true;
				}
				
//Menu options
				else if (EVENT.key.code == Keyboard::Enter && loop) {
					sound.setBuffer(click);
					sound.play();
					escape_checker = true;
					menu_checker = false;
					loop = false;
					if (checker == 0) {
						string successMsg = string(users[userIndex]->getId()) + " is successfully logged out\n\t\t\t Press Enter";
						outputText.setString(successMsg);
						outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
						inputMode = false;
						window.draw(outputText);

						backChecker = false;
						loggedIn = false;
						inputMode = false;
						escape_checker = false;
						menu2 = false;
						menu3 = false;
						menu5 = false;
						menu6 = false;
						menu9 = false;
						menu4 = false;
						comment_done = false;

					}
					else if (checker == 1) {
						menu1 = true;
					}
					else if (checker == 2) {
						pagetab = false;
						addlike_checker = false;
						postTab = true;
						loggedIn = false;
						inputMode = false;
						loop_checker = true;
						menu2 = true;
						menu3 = false;
						menu5 = false;
						menu6 = false;
						menu9 = false;
						menu4 = false;
						comment_done = false;
						memory_checker = false;
						memory_done = false;
						stoper = 0;

					}
					else if (checker == 3) {
						pagetab = false;
						postTab = true;
						loggedIn = false;
						inputMode = false;
						loop_checker = true;
						menu3 = true;
						menu2 = false;
						menu5 = false;
						menu6 = false;
						menu9 = false;
						menu4 = false;
						comment_done = false;
						memory_checker = false;
						memory_done = false;

					}
					else if (checker == 4) {
						pagetab = false;
						postTab = true;
						loggedIn = false;
						inputMode = false;
						loop_checker = true;
						menu5 = false;
						menu2 = false;
						menu3 = false;
						menu6 = false;
						menu9 = false;
						menu4 = true;
						stoper = 0;
						comment_done = false;
						memory_checker = false;
						memory_done = false;
						
					}
					else if (checker == 5) {
						pagetab = false;
						postTab = true;
						loggedIn = false;
						inputMode = false;
						loop_checker = true;
						menu5 = true;
						menu2 = false;
						menu3 = false;
						menu6 = false;
						menu9 = false;
						menu4 = false;
						comment_done = false;
						memory_checker = false;
						memory_done = false;
					}
					else if (checker == 6) {
						postTab = true;
						pagetab = false;
						loggedIn = false;
						inputMode = false;
						loop_checker = true;
						menu6 = true;
						menu2 = false;
						menu3 = false;
						menu5 = false;
						stoper = 0;
						menu9 = false;
						comment_done = false;
						menu4 = false;
						memory_checker = false;
						memory_done = false;
					}
					else if (checker == 7) {
						menu7 = true;
					}
					else if (checker == 8) {
						menu8 = true;
					}
					else if (checker == 9) {
						pagetab = true;
						postTab = false;
						loggedIn = false;
						inputMode = false;
						loop_checker = true;
						menu3 = false;
						menu2 = false;
						menu5 = false;
						menu6 = false;
						menu4 = false;
						comment_done = false;
						memory_checker = false;
						memory_done = false;

					}
					else if (checker == 10) {
						menu10 = true;
						window.close();
						break;
					}
					menu[checker].setOutlineColor(Color::White);
					menu[checker].setOutlineThickness(1);
					checker = -1;

				}

			}

	//Escape 
			else if (EVENT.key.code == Keyboard::Escape && escape_checker) {
				sound.setBuffer(click);
				sound.play();
				if (!menu_checker) {
					outputText.setString("");
					inputText.setString("");
					inputMode = false;
					menu_checker = true;
					addlike_checker = false;
					memory_checker = false;
					menu1 = false;
					menu2 = false;
					menu3 = false;
					menu4 = false;
					menu5 = false;
					menu6 = false;
					menu7 = false;
					menu8 = false;
					menu9 = false;
					menu10 = false;
					memory_checker=false;
					likedList_checker = false;
					viewPost = false;
					menu4 = false;
					comment_done = false;
					memory_done = false;
					postIDChecker = false;
				}

			}
	//Displays all things which have true checkers
			if (backChecker) {
				square.setTexture(&texture3);
			}
			if (menu_checker) {
				outputText.setString("");
				inputText.setString("");

				for (int i = 0; i < 11; i++) {

					window.draw(menu[i]);
					window.draw(menuText[i]);
				
				}
			}
			if (inputMode) {
				if (menu6) {
					users[userIndex]->viewListOfPosts(&window);
				}
				window.draw(inputText);
			}
			if (postTab) {
				window.draw(postInputText);
			}
			if (addlike_checker) {
				
				if (stoper == 0) {
					stoper++;
					if (postIDChecker) {
						if (memories[memoryIndex]->num_like_getter() < 10) {
							sound.setBuffer(like);
							sound.play();
							outputText.setString("like added");
							users[userIndex]->postLike(memories[memoryIndex]);

						}
						else {
							outputText.setString("likes are out of limit");
						}
						outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
					}
					else {
						if (posts[postindex]->num_like_getter() <= 10) {
							
							sound.setBuffer(like);
							sound.play();
							outputText.setString("like added");
							users[userIndex]->postLike(posts[postindex]);
						}
						else {
							string successMsg = string(userInput) + " likes are out of limit\n";
							outputText.setString("likes are out of limit");

						}
						outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
					}
				}
				outputText.setCharacterSize(54);
				outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
				window.draw(outputText);
				postIDChecker = false;
			}
			if (likedList_checker) {
				outputText.setString("");
				if (postIDChecker) {
					memories[memoryIndex]->viewlistoflikes(&window);
				}
				else {
					posts[postindex]->viewlistoflikes(&window);

				}
			}
			if(comment_done) {
				if (stoper == 0) {
					if (postIDChecker) {
						users[userIndex]->addComment(memories[memoryIndex], comment);
					}
					else {

					users[userIndex]->addComment(posts[postindex], comment);
					}
					stoper++;

					sound.setBuffer(commentSound);
					sound.play();
				}
				outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
				outputText.setString("Comment added sucessfully");
			}
			if (menu8) {
				users[userIndex]->viewFriendList(&window);
			}
			if (viewPost) {
				outputText.setString("");
				int c = window.getSize().y / 2-100;
				if (postIDChecker) {
					memories[memoryIndex]->viewPost(&window,c);
				}
				else {

					posts[postindex]->viewPost(&window, c);
				}
			}
			if (menu7) {
				users[userIndex]->viewProfilePage(&window);

			}
			if (menu1) {
				users[userIndex]->viewHome(users, pages, total_users, total_pages, currentDate, &window);
			}
			if (memory_done) {
				if (stoper == 0) {
					stoper++;
					users[userIndex]->addUserMemory(posts[postindex], mem_text,posts,total_posts,memories,total_memories);
					sound.setBuffer(memorySound);
					sound.play();
				}
				outputText.setPosition(window.getSize().x / 2 - outputText.getLocalBounds().width / 2, window.getSize().y / 2 - outputText.getLocalBounds().height / 2);
				outputText.setString("MEMORY ADDED");
			}
			if (menu9) {
				outputText.setString("");
				pages[pageInputIndex]->viewPage(&window);
			}
			window.draw(idText);
			window.draw(outputText);
			window.display();	
		}
	if (menu10) {
		break;
	}
	}

}

//For ending the fun
bool socialNetworkApp::end() {
	return 0;
}