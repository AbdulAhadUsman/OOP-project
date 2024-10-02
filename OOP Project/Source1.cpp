?#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class Helper;
class Date;
class State;
class User;
class Upload;
class Memory;
class Control;
class Comments;
class SocialNetworkingApp;


//-------------------------------------------------------------------------------------------------------------------------
// HELPER CLASS
//-------------------------------------------------------------------------------------------------------------------------

class Helper
{
public:

	static int StringLength(const char* str)
	{

		int i = 0;
		for (; str[i] != '\0'; i++)
		{

		}
		return i;

	}

	static void StringCopy(char*& dest, const char* src) {


		int i = 0;
		for (; src[i] != '\0'; i++)
		{
			dest[i] = src[i];
		}
		dest[i] = '\0';



	}

	static char* GetStringFromBuffer(char* str)
	{

		int strLen = StringLength(str);
		char* dest = 0;

		if (strLen > 0)
		{
			dest = new char[strLen + 1];
			char* tempDest = dest;
			StringCopy(dest, str);

		}
		return dest;
	}

	static int CompareString(char* str1, char* str2)
	{

		int length1 = StringLength(str1);
		int length2 = StringLength(str2);
		int max_length;

		if (length1 > length2)
		{
			max_length = length1;
		}
		else
		{
			max_length = length2;
		}

		for (int i = 0; i < max_length; i++)
		{

			if (str1[i] == str2[i])
			{
				continue;
			}
			else if (str1[i] > str2[i])
			{
				return 1;
			}
			else
			{
				return -1;
			}

		}

		return 0;
	}
	static int CompareString(char* str1, const char* str2)
	{



		int length1 = StringLength(str1);
		int length2 = StringLength(str2);
		int max_length;

		if (length1 > length2)
		{
			max_length = length1;
		}
		else
		{
			max_length = length2;
		}

		for (int i = 0; i < max_length; i++)
		{

			if (str1[i] == str2[i])
			{
				continue;
			}
			else if (str1[i] > str2[i])
			{
				return 1;
			}
			else
			{
				return -1;
			}

		}

		return 0;
	}
};

//-------------------------------------------------------------------------------------------------------------------------
// DATE CLASS
//-------------------------------------------------------------------------------------------------------------------------

class Date
{
private:

	int day;
	int month;
	int year;

public:
	static Date currentDate;

public:
	Date(int d = 0, int m = 0, int y = 0)
	{
		day = d, month = m, year = y;
	}
	void ReadDataFromFile(ifstream& fin)
	{
		fin >> day;
		fin >> month;
		fin >> year;
	}
	void Print()
	{
		cout << "(" << day << "/" << month << "/" << year << ")";
	}
	static void SetCurrentDate(int x, int y, int z)
	{
		currentDate.day = x;
		currentDate.month = y;
		currentDate.year = z;
	}

	static bool EligibleForHomePage(Date& d1, Date& d2)
	{

		if (d1.month == d2.month && d1.year == d2.year)
		{
			int x;

			x = d1.day - d2.day;

			if (x < 0)
			{
				x *= -1;
			}

			if (x == 0 || x == 1)
			{
				return true;
			}
		}
		return false;
	}

	static bool CheckForMemory(Date& d1, Date& d2)
	{
		if (d1.month == d2.month && d1.day == d2.day && d1.year != d2.year)
		{
			return true;
		}
		return false;
	}

	static void CalculateYearDiff(Date& d1, Date& d2)
	{
		int max = 0;

		if (d1.year > d2.year)
		{
			max = d1.year;
		}
		else {
			max = d2.year;
		}
		cout << max << " years ago\n";
	}

	void SetEqualToCurentDate()
	{
		day = currentDate.day;
		month = currentDate.month;
		year = currentDate.year;
	}
};
Date Date::currentDate(0, 0, 0);

//-------------------------------------------------------------------------------------------------------------------------
// STATE CLASS (ACTIVITY)
//-------------------------------------------------------------------------------------------------------------------------

class State
{
private:
	int type;
	char* detail;

public:
	State()
	{
		detail = 0;
	}
	void ReadDataFromFile(ifstream& fin)
	{
		char temp[50];
		fin >> type;
		fin.getline(temp, 50);
		detail = Helper::GetStringFromBuffer(temp);
	}

	void Print()
	{
		switch (type)
		{
		case 1:
			cout << "is feeling ";
		case 2:
			cout << "is thinking about ";
		case 3:
			cout << "is making ";
		case 4:
			cout << "is celebrating ";
		}

		cout << detail << endl;
	}

	~State()
	{
		if (detail)delete[]detail;
	}

};

//-------------------------------------------------------------------------------------------------------------------------
// CONTROL CLASS (OBJECT)
//-------------------------------------------------------------------------------------------------------------------------
class Control
{
protected:
	char* ID;

public:

	Control()
	{
		ID = 0;
	}

	virtual void Print()
	{
		cout << ID;
	}

	virtual void AddToTimeline(Upload*& ptr) = 0;

	virtual void PrintName() = 0;

	virtual ~Control()
	{
		if (ID)delete[]ID;
	}

};

//-------------------------------------------------------------------------------------------------------------------------
// COMMENTS CLASS
//-------------------------------------------------------------------------------------------------------------------------

class Comments
{
private:
	char* id;
	char* comment;
	Control* comment_by;

public:
	Comments();
	void SetValues(const char*, const char*, Control*&);
	void Print();
	~Comments();
};

Comments::Comments()
{
	id = 0;
	comment = 0;
	comment_by = 0;
}

Comments::~Comments()
{
	if (id)delete[]id;
	if (comment)delete[]comment;
}

void Comments::SetValues(const char* ID, const char* text, Control*& commentby)
{
	char* temp = new char[100];

	Helper::StringCopy(temp, ID);
	id = Helper::GetStringFromBuffer(temp);

	Helper::StringCopy(temp, text);
	comment = Helper::GetStringFromBuffer(temp);

	comment_by = commentby;

	delete[]temp;
	temp = 0;
}

void Comments::Print()
{
	comment_by->PrintName();
	cout << " wrote : " << comment << endl;
}

//-------------------------------------------------------------------------------------------------------------------------
// UPLOAD CLASS (POST)
//-------------------------------------------------------------------------------------------------------------------------

class Upload
{
protected:
	char* id;
	char* caption;
	Date sharingDate;
	State* activity;
	Control* shared_by;
	Control** liked_by;
	Comments** comments;
	int totalLikes;
	int totalComments;

public:
	Upload();
	void ReadPostsFromFile(ifstream&);
	void SetSharedBy(Control*&);
	void SetLikedBy(Control*&);
	char* GetPostID();

	void AddComment(Comments*& ptr)
	{
		if (totalComments < 10)
		{
			comments[totalComments] = ptr;
			totalComments++;
		}
	}

	virtual void Print(bool);
	void ViewLikedList();
	void ViewForHomePage();
	void PrintForMemory();
	~Upload();
};

Upload::Upload()
{
	id = 0;
	caption = 0;

	activity = 0;
	shared_by = 0;

	liked_by = new Control * [10];
	totalLikes = 0;

	comments = new Comments * [10];
	totalComments = 0;
}

Upload::~Upload()
{
	if (id)delete[]id;
	if (caption)delete[]caption;
	if (activity)delete activity;
	if (shared_by)delete[]shared_by;
	if (liked_by)delete[]liked_by;

	if (comments)
	{
		for (int i = 0; i < totalComments; i++)
		{
			if (comments[i])delete comments[i];
		}
		delete[]comments;
	}
}

void Upload::ReadPostsFromFile(ifstream& fin)
{
	char temp[100];
	int check;


	fin >> check;

	fin >> temp;
	id = Helper::GetStringFromBuffer(temp);

	sharingDate.ReadDataFromFile(fin);

	fin.ignore(1000, '\n');
	fin.getline(temp, 100);
	caption = Helper::GetStringFromBuffer(temp);

	if (check == 2)
	{
		activity = new State;
		activity->ReadDataFromFile(fin);
	}
}

void Upload::SetSharedBy(Control*& ptr)
{

	shared_by = ptr;

}

void Upload::SetLikedBy(Control*& ptr)
{
	if (totalLikes < 10)
	{

		liked_by[totalLikes] = ptr;
		totalLikes++;
	}
}

char* Upload::GetPostID()
{
	return id;
}

void Upload::Print(bool checkForDate)
{
	if (activity)
	{
		shared_by->PrintName();
		cout << " ";
		activity->Print();
	}
	else {
		shared_by->PrintName();
		cout << " shared" << endl;
	}

	cout << "'" << caption << "' .... ";
	if (checkForDate)
	{
		sharingDate.Print();
	}
	cout << endl;

	if (comments)
	{
		for (int i = 0; i < totalComments; i++)
		{
			comments[i]->Print();
		}
	}
}

void Upload::ViewLikedList()
{
	cout << "Post Liked by : " << endl;
	for (int i = 0; i < totalLikes; i++)
	{
		liked_by[i]->Print();
		cout << endl;
	}
}

void Upload::ViewForHomePage()
{
	if (Date::EligibleForHomePage(this->sharingDate, Date::currentDate))
	{
		Print(false);
	}
}

void Upload::PrintForMemory()
{
	if (Date::CheckForMemory(sharingDate, Date::currentDate))
	{
		cout << "On this day" << endl;
		Date::CalculateYearDiff(sharingDate, Date::currentDate);
		Print(true);
	}
}

//-----------------------------------------------------------------------------------------------------------------
// MEMORY CLASS
//-----------------------------------------------------------------------------------------------------------------

class Memory : public Upload
{
private:

	Upload* originalPost;
public:

	Memory()
	{
		originalPost = 0;
	}

	Memory(const char* xyz, Upload*& ptr, Control*& user)
	{
		char* temp = new char[100];
		Helper::StringCopy(temp, xyz);
		caption = Helper::GetStringFromBuffer(temp);

		shared_by = user;

		sharingDate.SetEqualToCurentDate();

		originalPost = ptr;
	}

	void Print()
	{
		shared_by->PrintName();
		cout << "shared a memory....";
		sharingDate.Print();
		cout << "\n" << caption;
		cout << endl;
		originalPost->Print(true);
	}

};

//-----------------------------------------------------------------------------------------------------------------
// PAGE CLASS
//-----------------------------------------------------------------------------------------------------------------
class Page :public Control
{
private:

	char* pageTitle;
	Upload** timeline;
	int totalPosts;

public:

	Page();
	void ReadPagesFromFile(ifstream&);
	char* GetPageID();
	void Print();

	void AddToTimeline(Upload*& ptr)
	{
		timeline[totalPosts] = ptr;
		totalPosts++;
	}

	void PrintName();
	void ViewTimeline();
	void PrintLatest();
	void PrintForMemory();

	~Page();
};

Page::Page()
{
	pageTitle = 0;
	timeline = new Upload * [10];
	totalPosts = 0;
}

Page::~Page()
{
	if (pageTitle)delete[]pageTitle;
}

void Page::ReadPagesFromFile(ifstream& fin)
{
	char temp[50];

	fin >> temp;
	ID = Helper::GetStringFromBuffer(temp);

	fin.getline(temp, 50);
	pageTitle = Helper::GetStringFromBuffer(temp);

}

char* Page::GetPageID()
{
	return ID;
}

void Page::Print()
{
	this->Control::Print();
	cout << " - " << pageTitle << endl;

}

void Page::PrintName()
{
	cout << pageTitle;
}

void Page::ViewTimeline()
{
	for (int i = 0; i < totalPosts; i++)
	{
		cout << pageTitle;
		timeline[i]->Print(true);
		cout << endl;
	}
}

void Page::PrintLatest()
{
	for (int i = 0; i < totalPosts; i++)
	{
		if (timeline)
		{

			timeline[i]->ViewForHomePage();
			cout << endl;
		}
		else
		{
			break;
		}
	}
}


//-------------------------------------------------------------------------------------------------------------------------
// USER CLASS
//-------------------------------------------------------------------------------------------------------------------------

class User :public Control
{
private:

	char* firstName;
	char* lastName;
	Page** likedPages;
	User** friendList;
	Upload** timeline;
	int totalPosts;
	int likedpages;
	int friendCount;

public:

	User();
	void ReadUsersFromFile(ifstream&);
	void LikePage(Page*);
	char* GetUserID();
	void AddFriend(User*);
	void Print();
	void ViewFriendList();
	void ViewLikedPages();

	void AddToTimeline(Upload*& ptr)
	{
		timeline[totalPosts] = ptr;
		totalPosts++;
	}

	void ViewTimeline();
	void PrintName();
	void ViewHomePage();
	void PrintLatest();
	void SeeYourMemory();
	bool SearchPost(Upload*& ptr);
	void AddMemory(Memory*&);

	~User();
};

User::User()
{
	firstName = 0;
	lastName = 0;
	likedPages = new Page * [10];
	friendList = new User * [10];
	timeline = new Upload * [10];
	likedpages = 0;
	friendCount = 0;
	totalPosts = 0;
}

void User::ReadUsersFromFile(ifstream& fin)
{
	char temp[20];

	fin >> temp;
	ID = Helper::GetStringFromBuffer(temp);

	fin >> temp;
	firstName = Helper::GetStringFromBuffer(temp);

	fin >> temp;
	lastName = Helper::GetStringFromBuffer(temp);

}

void User::LikePage(Page* page)
{
	likedPages[likedpages] = page;
	likedpages++;
}

void User::AddFriend(User* u)
{
	friendList[friendCount] = u;
	friendCount++;
}

char* User::GetUserID()
{
	return ID;
}

void User::PrintName()
{
	cout << firstName << " " << lastName;
}

void User::Print()
{
	this->Control::Print();
	cout << " - ";
	cout << firstName << " " << lastName << endl;;
}

void User::ViewFriendList()
{
	cout << firstName << " " << lastName << " - Friend List" << endl;

	for (int i = 0; i < friendCount; i++)
	{
		friendList[i]->Print();
	}

}

void User::ViewLikedPages()
{
	cout << firstName << " " << lastName << " - Liked Pages" << endl;

	for (int i = 0; i < likedpages - 1; i++)
	{
		likedPages[i]->Print();
	}
}

void User::ViewTimeline()
{
	for (int i = 0; i < totalPosts; i++)
	{
		timeline[i]->Print(true);
		cout << endl;
	}
}

void User::PrintLatest()
{
	for (int i = 0; i < totalPosts; i++)
	{


		timeline[i]->ViewForHomePage();
		cout << endl;
	}
}

void User::ViewHomePage()
{
	for (int i = 0; i < friendCount; i++)
	{

		friendList[i]->PrintLatest();
	}

	for (int i = 0; i < likedpages - 1; i++)
	{
		if (likedPages[i])
			likedPages[i]->PrintLatest();
	}
}

void User::SeeYourMemory()
{
	for (int i = 0; i < totalPosts; i++)
	{
		timeline[i]->PrintForMemory();
	}
}

bool User::SearchPost(Upload*& ptr)
{
	for (int i = 0; i < totalPosts; i++)
	{
		if (timeline[i] == ptr)
		{
			return true;
		}
	}
	return false;
}

void User::AddMemory(Memory*& memory)
{
	timeline[totalPosts] = memory;
	totalPosts++;
}

User::~User()
{
	if (firstName)delete[]firstName;
	if (lastName)delete[]lastName;
}

//-------------------------------------------------------------------------------------------------------------------------
// SOCIAL NETWORKING APP CLASS
//-------------------------------------------------------------------------------------------------------------------------

class SocialNetworkingApp
{
private:

	Page** pages;
	User** users;
	Upload** uploads;

	int totalUsers;
	int totalPages;
	int totalPosts;
	int totalComments;

public:
	SocialNetworkingApp();
	void Load();
	void Run();
	void LoadPagesFromFile();
	void LoadUsersFromFile();
	void LoadUploadsFromFile();
	void LoadCommentsFromFile();
	Page* SearchPageByID(const char*);
	User* SearchUserByID(const char*);
	Control* SearchObjectByID(char*);
	Upload* SearchPostByID(const char*);
	void LikePost(Upload*& ptr, User*& user);
	void PostComment(Upload*& ptr, const char* text, User*& user);
	void ShareMemory(const char* postid, const char* text, User*& user);
	void AddPost(Memory*& x);
	~SocialNetworkingApp();
};

SocialNetworkingApp::SocialNetworkingApp()
{
	pages = 0;
	users = 0;
	uploads = 0;
}

SocialNetworkingApp::~SocialNetworkingApp()
{
	if (pages)
	{

		for (int i = 0; i < totalPages; i++)
		{
			if (pages[i])delete pages[i];
		}
		delete[]pages;
	}

	if (users)
	{

		for (int i = 0; i < totalUsers; i++)
		{
			if (users[i])delete users[i];
		}
		delete[]users;
	}

	if (uploads)
	{
		delete[]uploads;
	}
}

void SocialNetworkingApp::Load()
{
	LoadPagesFromFile();
	LoadUsersFromFile();
	LoadUploadsFromFile();
	LoadCommentsFromFile();
}

void SocialNetworkingApp::LoadCommentsFromFile()
{
	ifstream file("comments.txt");
	char temp[100];
	char* comment_id;
	char* text;
	Upload* postptr;
	Control* comment_by;


	if (file.is_open())
	{
		file >> totalComments;


		for (int i = 0; i <= totalComments; i++)
		{
			Comments* comment = new Comments;

			file >> temp;
			comment_id = Helper::GetStringFromBuffer(temp);

			file >> temp;
			postptr = SearchPostByID(temp);

			file >> temp;
			comment_by = SearchObjectByID(temp);

			file.getline(temp, 100);
			text = Helper::GetStringFromBuffer(temp);

			comment->SetValues(comment_id, text, comment_by);
			postptr->AddComment(comment);

		}
	}
}

void SocialNetworkingApp::LoadUploadsFromFile()
{
	ifstream file("posts.txt");
	char temp[20];
	char temp2[20];
	Control* sharedby_temp;
	Control* likedby_temp;

	if (file.is_open())
	{
		file >> totalPosts;

		uploads = new Upload * [totalPosts + 5];

		for (int i = 0; i <= totalPosts; i++)
		{
			uploads[i] = new Upload;
			uploads[i]->ReadPostsFromFile(file);

			file >> temp;
			sharedby_temp = SearchObjectByID(temp);
			uploads[i]->SetSharedBy(sharedby_temp);

			while (true)
			{
				file >> temp;

				if (*temp == '-')break;

				likedby_temp = SearchObjectByID(temp);
				uploads[i]->SetLikedBy(likedby_temp);


			}
			sharedby_temp->AddToTimeline(uploads[i]);

		}
	}

}

void SocialNetworkingApp::LoadPagesFromFile()
{

	ifstream file("pages.txt");

	file >> totalPages;
	pages = new Page * [totalPages];

	for (int i = 0; i < totalPages; i++)
	{
		pages[i] = new Page;
		pages[i]->ReadPagesFromFile(file);
	}
}

void SocialNetworkingApp::LoadUsersFromFile()
{
	ifstream file("users.txt");

	file >> totalUsers;
	users = new User * [totalUsers];

	char*** tempFriends = new char** [totalUsers];
	char temp[20];

	for (int i = 0, j = 0; i < totalUsers; i++)
	{
		j = 0;
		users[i] = new User;
		users[i]->ReadUsersFromFile(file);

		tempFriends[i] = new char* [10];

		while (*temp != '-')
		{
			file >> temp;
			tempFriends[i][j] = Helper::GetStringFromBuffer(temp);
			j++;
		}
		temp[0] = { '\0' };

		while (*temp != '-')
		{
			file >> temp;
			Page* ptr;
			ptr = SearchPageByID(temp);
			users[i]->LikePage(ptr);

		}
		temp[0] = { '\0' };

	}
	file.close();

	for (int i = 0, j = 0, k = 0; i < totalUsers; i++)
	{
		j = 0;
		while (tempFriends[i][j][k] != '-')
		{
			User* ptr;
			ptr = SearchUserByID(tempFriends[i][j]);
			users[i]->AddFriend(ptr);
			delete[]tempFriends[i][j];
			j++;
		}
		delete[]tempFriends[i];
	}
	delete[]tempFriends;
	tempFriends = 0;

}

Page* SocialNetworkingApp::SearchPageByID(const char* ID)
{
	if (pages)
	{
		for (int i = 0; i < totalPages; i++)
		{
			if (Helper::CompareString(pages[i]->GetPageID(), ID) == 0)
			{
				return pages[i];
			}

		}
	}
}

User* SocialNetworkingApp::SearchUserByID(const char* ID)
{
	if (users)
	{

		for (int i = 0; i < totalUsers; i++)
		{
			if (Helper::CompareString(users[i]->GetUserID(), ID) == 0)
			{
				return users[i];
			}
		}
	}
}

Upload* SocialNetworkingApp::SearchPostByID(const char* ID)
{
	if (uploads)
	{
		for (int i = 0; i < totalPosts; i++)
		{
			if (Helper::CompareString(uploads[i]->GetPostID(), ID) == 0)
			{
				return uploads[i];
			}
		}
	}
}

Control* SocialNetworkingApp::SearchObjectByID(char* ID)
{
	for (int i = 0; i < totalPages || i < totalUsers; i++)
	{
		if ((i < totalPages) && (Helper::CompareString(pages[i]->GetPageID(), ID) == 0))
		{
			return pages[i];
		}

		if ((i < totalUsers) && (Helper::CompareString(users[i]->GetUserID(), ID) == 0))
		{
			return users[i];
		}
	}

}

void SocialNetworkingApp::LikePost(Upload*& ptr, User*& user)
{
	Control* temp2 = user;
	ptr->SetLikedBy(temp2);
}

void SocialNetworkingApp::PostComment(Upload*& ptr, const char* text, User*& user)
{
	Comments* temp = new Comments;
	Control* temp2 = user;

	temp->SetValues("c14", text, temp2);

	ptr->AddComment(temp);

}

void SocialNetworkingApp::ShareMemory(const char* postid, const char* text, User*& user)
{
	Upload* ptr;
	ptr = SearchPostByID(postid);

	Control* tempcontrol = user;

	if (user->SearchPost(ptr))
	{
		Memory* temp = new Memory(text, ptr, tempcontrol);

		user->AddMemory(temp);
	}
}

void SocialNetworkingApp::AddPost(Memory*& x)
{
	if (totalPosts < 10)
	{

		uploads[totalPosts] = x;
		totalPosts++;
	}
}

void SocialNetworkingApp::Run()
{

	cout << "Command:Set current System Date 15 11 2017" << endl;
	Date::SetCurrentDate(15, 11, 2017);

	cout << "Command: Set current user u7" << endl;
	User* currentUser = SearchUserByID("u7");

	cout << "Command: View Friend List" << endl << endl;
	currentUser->ViewFriendList();
	cout << "\n------------------------------------------------------------------------------------------------------\n";

	cout << "\nCommand: View liked pages : " << endl;
	currentUser->ViewLikedPages();
	cout << "\n------------------------------------------------------------------------------------------------------\n";

	cout << "Command: View Home Page" << endl << endl;
	currentUser->ViewHomePage();
	cout << "\n------------------------------------------------------------------------------------------------------\n";

	cout << "Command: View Timeline" << endl << endl;
	currentUser->ViewTimeline();
	cout << "\n------------------------------------------------------------------------------------------------------\n";


	cout << "Command: View liked list(post5)" << endl << endl;
	Upload* currentPost = SearchPostByID("post5");
	currentPost->ViewLikedList();
	cout << "\n------------------------------------------------------------------------------------------------------\n";


	cout << "Command: like post(post5)" << endl;
	cout << "Command: View liked list(post)" << endl << endl;
	LikePost(currentPost, currentUser);
	currentPost->ViewLikedList();
	cout << "\n------------------------------------------------------------------------------------------------------\n";

	cout << "Command: Post comment(post4,Good luck for your result)" << endl;
	Upload* secondPost = SearchPostByID("post4");
	PostComment(secondPost, "Good luck for your result", currentUser);
	secondPost->Print(true);
	cout << "\n------------------------------------------------------------------------------------------------------\n";

	cout << "Command: Post comment(post8,Thanks for the wishes)" << endl;
	Upload* thirdPost = SearchPostByID("post8");
	PostComment(thirdPost, "Thanks for the wishes", currentUser);
	thirdPost->Print(true);
	cout << "\n------------------------------------------------------------------------------------------------------\n";

	cout << "Command: See your Memory" << endl << endl;
	currentUser->SeeYourMemory();
	cout << "\n------------------------------------------------------------------------------------------------------\n";

	cout << "Command: Share Memory(post10, Never thought I will be specialist in this field?)" << endl;
	cout << "Command: View Timeline" << endl << endl;
	ShareMemory("post10", "Never thought I will be specialist in this field?", currentUser);
	currentUser->ViewTimeline();
	cout << "\n------------------------------------------------------------------------------------------------------\n";

	cout << "\nCommand: View Page(p1)" << endl << endl;
	Page* currentPage = SearchPageByID("p1");
	currentPage->ViewTimeline();
	cout << endl;
}

//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------

int  main()
{

	SocialNetworkingApp fb;
	fb.Load();
	fb.Run();

	system("pause");
	return 0;
}