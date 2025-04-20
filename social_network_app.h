#pragma once
#include<fstream>
#include <SFML/Graphics.hpp>
class pageClass;
class postClass;
class pageClass;
class dateClass;
class memoryClass;
using namespace sf;

class userClass {
private:
	char* userID;
	char* first_name;
	char* last_name;
	userClass** friends;		
	pageClass** likedPages;
	int friends_num;		
	int pages_num;
	postClass** listOfPosts;
	int numberOfPosts;
	memoryClass** user_memories;
	int total_user_memories;
public:
	userClass();
	~userClass();
	void  SETTER(char*,char*,char*, userClass**, pageClass**,int,int,postClass**,int);
	void viewFriendList(RenderWindow*);
	void viewLikedPages(RenderWindow*,int &);
	void newFriend(userClass&);
	void newLikedPage(pageClass&);
	void postLike(postClass*); 
	void viewHome(userClass**,pageClass**,int,int,dateClass,RenderWindow*);
	void ownerNameGetter(RenderWindow*,int&);
	void viewProfilePage(RenderWindow*);
	void addComment(postClass*,char*);
	void USERDATASETTER(char*,char*,char*);
	void USER_FRIEND_SETTER(userClass**,int);
	void USER_PAGELIKER_SETTER( pageClass**, int);
	char* getId();
	char* getFirstname();
	char* getLastname();
	void setId(char*);
	void setName(char*, char*);
	void listOfPostsSetter(postClass*);
	void viewListOfPosts(RenderWindow *);
	bool memoryChecker(char*);
	void addUserMemory(postClass*,char*,postClass**,int,memoryClass**&,int&);
	int num_memory_getter();
};

class dateClass {
	int day;
	int month;
	int year;
public:
	dateClass();
	void viewDate(RenderWindow*,int&);
	void dateSetter(int,int,int);
	int dayGetter();
	int monthGetter();
	int yearGetter();
};

class activityClass {
private:
	int activity_type;
	char* activity_text;
	char* activity_Value;
public:


	void setterForPost(int ,char*);
	void getterForViewPost(RenderWindow*,int&);
	activityClass();
	~activityClass();
};

class commentClass {
private:
	char* commentID;
	char* comment_text;
	userClass* comment_owner;
	pageClass* commentOwnerPG;
public:
	void getterForPost(RenderWindow*,int&);
	void commentSetterUser(userClass*,char*);
	void commentSetterPage(pageClass*,char*);
	void COMMENTSETTER(userClass*, char*, char*, pageClass*);
	commentClass();
	~commentClass();
	userClass* commentOwnerGetter();
	pageClass* commentOwnerGetterpg();
	char* commentIDGetter();
	char* commentTextGetter();	
};

class pageClass {

private:
	char* pageID;
	char* pgtitle;
	int numberOfPosts;
	userClass* owner;
	postClass** listOfPosts;
public:
	int numOfPostGetter();
	postClass* pagePostGetter(int);
	void setId(char*);
	char* getId();
	void setTitle(char*);
	char* getTitle();
	void pageSetter(char*,char*,userClass*);
	void getterForUser(RenderWindow*, int&);
	void setterForUser(pageClass&);
	void pageTitleGetter(RenderWindow*,int&);
	void viewPage(RenderWindow*);
	void addNewComment(postClass&,char*);
	pageClass();
	~pageClass();
	void listOfPostSetter(postClass*);
};

class postClass {
protected:
	char* postID;
	char* post_discription;
	int num_of_likes;
	int num_of_comments;
	commentClass** commentOnPost; 
	pageClass* postOfPage;
	userClass** listOfLikesUsers;
	pageClass** listOfLikesPages;
	userClass* postOfUser;
	dateClass post_date;
	activityClass* post_activity;
public:
	char* getId();
	virtual void viewPost(sf::RenderWindow*,int&,int size=21);
	int numOfCommentGetter();
	void postComment(userClass*,char*);
	void postComment(pageClass*, char*);
	void setPostData(char* , int , int , int , char*, int , char* , userClass* , pageClass*, userClass**, pageClass**,int);
	void setterForUserLike(userClass*);
	void viewlistoflikes(RenderWindow*);
	void commentSetterPost(commentClass**, int);
	postClass();
	virtual ~postClass();
	int postDAYGetter();
	int postMONTHGetter();
	int postYEARGetter();
	int num_like_getter();
};

class memoryClass:public postClass  {
private:
	postClass* postMeomery;
public:
	void addMemory(postClass*,char*,postClass**,int,int,userClass*);
	memoryClass();
	~memoryClass();
	void viewPost(RenderWindow*,int&,int size=21);
};

class socialNetworkApp {
private:
	userClass** users;
	int total_users;
	pageClass** pages;
	int total_pages;
	postClass** posts;
	int total_posts;
	memoryClass** memories;
	int total_memories = 0;
public:
	socialNetworkApp();
	~socialNetworkApp();
	void run();
	bool end();
};

class helper {
public:
	static void strcopy(char*,char*);
	static void strcopy(char*,const char*);
	static void strcopy(const char*, char*);
	static char* strcopy(const char*,char ,char, char*);
	static int strlength(char*);
	static int strlength(const char*);
	static void dataReaderUser(userClass**, std::ifstream&, int,pageClass**);
	static void dataReaderUser_PAGE(userClass**, std::ifstream&, int, pageClass**,int);
	static void dataReaderPage(pageClass**, std::ifstream&, int,userClass**,int);
	static void dataReaderPosts_Comments(postClass**, std::ifstream&, int, pageClass**, userClass**,int,int);
	static bool strCompare(const char*,const char*);
	static memoryClass** sizeIncreser(memoryClass**, int);
	
};