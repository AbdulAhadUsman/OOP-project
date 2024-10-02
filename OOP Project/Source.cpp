//#include<iostream>
//#include<fstream>
//#include<string>
//
//using namespace std;
//
//class Helper
//{
//public:
//
//	static int StringLength(char* str)
//	{
//
//		int i = 0;
//		for (; str[i] != '\0'; i++)
//		{
//
//		}
//		return i;
//
//	}
//
//	static void StringCopy(char*& dest, char*& src) {
//
//
//		int i = 0;
//		for (; src[i] != '\0'; i++)
//		{
//			dest[i] = src[i];
//		}
//		dest[i] = '\0';
//
//
//
//	}
//
//	static char* GetStringFromBuffer(char* str)
//	{
//
//		int strLen = StringLength(str);
//		char* dest = 0;
//
//		if (strLen > 0)
//		{
//			dest = new char[strLen + 1];
//			char* tempDest = dest;
//			StringCopy(dest, str);
//
//		}
//		return dest;
//	}
//
//	static int CompareString(char* str1, char* str2)
//	{
//
//		int length = StringLength(str1);
//
//		for (int i = 0; i < length; i++)
//		{
//
//			if (str1[i] == str2[i])
//			{
//				continue;
//			}
//			else if (str1[i] > str2[i])
//			{
//				return 1;
//			}
//			else
//			{
//				return -1;
//			}
//
//		}
//
//		return 0;
//	}
//	static int CompareString(char* str1, const char* str2)
//	{
//
//		int length = StringLength(str1);
//
//		for (int i = 0; i < length; i++)
//		{
//
//			if (str1[i] == str2[i])
//			{
//				continue;
//			}
//			else if (str1[i] > str2[i])
//			{
//				return 1;
//			}
//			else
//			{
//				return -1;
//			}
//
//		}
//
//		return 0;
//	}
//};
//
////-------------------------------------------------------------------------------------------------------------------------
////-------------------------------------------------------------------------------------------------------------------------
//
//class Page
//{
//private:
//
//	char* pageID;
//	char* pageTitle;
//
//public:
//
//	Page();
//	void ReadPagesFromFile(ifstream&);
//	char* GetPageID();
//	void PrintListView();
//
//};
//
//Page::Page()
//{
//	cout << "pages yahi\n";
//	pageID = 0;
//	pageTitle = 0;
//}
//
//void Page::ReadPagesFromFile(ifstream& fin)
//{
//	char temp[50];
//
//	fin >> temp;
//	pageID = Helper::GetStringFromBuffer(temp);
//
//	fin.getline(temp, 50);
//	pageTitle = Helper::GetStringFromBuffer(temp);
//
//}
//
//char* Page::GetPageID()
//{
//	return pageID;
//}
//
//void Page::PrintListView()
//{
//	cout << pageID << " - " << pageTitle << endl;
//
//}
//
////---------------------------------------------------------------------------------------------------------------------------
////---------------------------------------------------------------------------------------------------------------------------
//
//class User
//{
//private:
//
//	char* userID;
//	char* firstName;
//	char* lastName;
//	Page** likedPages;
//	User** friendList;
//	int likedpages;
//	int friendCount;
//
//public:
//
//	User();
//	void ReadUsersFromFile(ifstream&);
//	void LikePage(Page*);
//	char* GetUserID();
//	void AddFriend(User*);
//	void PrintListView();
//	void ViewFriendList();
//	void ViewLikedPages();
//};
//
//User::User()
//{
//	cout << "yahi user\n";
//	userID = 0;
//	firstName = 0;
//	lastName = 0;
//	likedPages = new Page*[10];
//	friendList = new User*[10];
//	likedpages = 0;
//	friendCount = 0;
//}
//
//void User::ReadUsersFromFile(ifstream& fin)
//{
//	char temp[20];
//
//	fin >> temp;
//	userID = Helper::GetStringFromBuffer(temp);
//
//	fin >> temp;
//	firstName = Helper::GetStringFromBuffer(temp);
//
//	fin >> temp;
//	lastName = Helper::GetStringFromBuffer(temp);
//
//}
//
//void User::LikePage(Page* page)
//{
//	likedPages[likedpages] = page;
//	likedpages++;
//}
//
//void User::AddFriend(User* u)
//{
//	friendList[friendCount] = u;
//	friendCount++;
//}
//
//char* User::GetUserID()
//{
//	return userID;
//}
//
//void User::PrintListView()
//{
//	cout  << userID <<" - ";
//	cout << firstName << " " << lastName << endl;;
//}
//
//void User::ViewFriendList()
//{
//	cout << firstName << " " << lastName << " - Friend List" << endl;
//
//	for (int i = 0; i < friendCount; i++)
//	{
//		friendList[i]->PrintListView();
//	}
//
//}
//
//void User::ViewLikedPages()
//{
//	cout << firstName << " " << lastName << " - Liked Pages" << endl;
//
//	for (int i = 0; i < likedpages-1; i++)
//	{
//		likedPages[i]->PrintListView();
//
//	}
//}
//
////----------------------------------------------------------------------------------------------------------------------
////----------------------------------------------------------------------------------------------------------------------
//
//class SocialNetworkingApp
//{
//private:
//
//	Page** pages;
//	User** users;
//	int totalUsers;
//	int totalPages;
//
//public:
//	SocialNetworkingApp();
//	void Load();
//	void LoadPagesFromFile();
//	void LoadUsersFromFile();
//	Page* SearchPageByID(char*);
//	User* SearchUserByID(const char*);
//
//};
//
//SocialNetworkingApp::SocialNetworkingApp()
//{
//	cout << "yahi\n";
//	pages = 0;
//	users = 0;
//}
//
//void SocialNetworkingApp::Load()
//{
//	LoadPagesFromFile();
//	LoadUsersFromFile();
//}
//
//void SocialNetworkingApp::LoadPagesFromFile()
//{
//	//int total = 0;
//	ifstream file("pages.txt");
//
//	file >> totalPages;
//	pages = new Page * [totalPages];
//
//	for (int i = 0; i < totalPages; i++)
//	{
//		pages[i] = new Page;
//		pages[i]->ReadPagesFromFile(file);
//	}
//}
//
//void SocialNetworkingApp::LoadUsersFromFile()
//{
//	ifstream file("users.txt");
//
//	file >> totalUsers;
//	users = new User * [totalUsers];
//
//	char*** tempFriends = new char** [totalUsers];
//	char temp[20];
//
//	for (int i = 0, j = 0; i < totalUsers; i++)
//	{
//		j = 0;
//		users[i] = new User;
//		users[i]->ReadUsersFromFile(file);
//
//		tempFriends[i] = new char* [10];
//
//		while (*temp != '-')
//		{
//			file >> temp;
//			tempFriends[i][j] = Helper::GetStringFromBuffer(temp);
//			j++;
//		}
//		temp[0] = { '\0' };
//
//		while (*temp != '-')
//		{
//			file >> temp;
//			Page* ptr;
//			ptr = SearchPageByID(temp);
//			users[i]->LikePage(ptr);
//
//		}
//		temp[0] = { '\0' };
//
//	}
//	file.close();
//
//	for (int i = 0, j = 0, k = 0; i < totalUsers; i++)
//	{
//		j = 0;
//		while (tempFriends[i][j][k] != '-')
//		{
//			User* ptr;
//			ptr = SearchUserByID(tempFriends[i][j]);
//			users[i]->AddFriend(ptr);
//			j++;
//		}
//	}
//
//	for (int i = 0,j=0,k=0; i < totalUsers; i++)
//	{
//		j = 0;
//		while (tempFriends[i][j][k] != '-')
//		{
//			delete[]tempFriends[i][j];
//			j++;
//		}
//		delete[]tempFriends[i];
//	}
//	delete[]tempFriends;
//	tempFriends = 0;
//
//}
//
//Page* SocialNetworkingApp::SearchPageByID(char* ID)
//{
//	for (int i = 0; i < totalPages; i++)
//	{
//		if (Helper::CompareString(pages[i]->GetPageID(), ID) == 0)
//		{
//			return pages[i];
//		}
//
//	}
//}
//
//User* SocialNetworkingApp::SearchUserByID(const char* ID)
//{
//	for (int i = 0; i < totalUsers; i++)
//	{
//
//		if (Helper::CompareString(users[i]->GetUserID(), ID) == 0)
//		{
//			return users[i];
//		}
//
//	}
//}
//
////--------------------------------------------------------------------------------------------------------------------------
////--------------------------------------------------------------------------------------------------------------------------
//
//int  main()
//{
//	SocialNetworkingApp fb;
//	fb.Load();
//
//	User* currentUser = fb.SearchUserByID("u7");
//	currentUser->ViewFriendList();
//	currentUser->ViewLikedPages();
//}