#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
	Human(const string& name, const string& status) :Name(name), Status(status) {}
	string GetName() const {return Name;}
	string GetStatus() const {return Status;}
	virtual void Walk(const string& destination)const = 0;
protected:
	const string Name, Status;
};

class Student : public Human{
public:

	Student(const string& name, const string& favouriteSong) :
		Human(name, "Student"), FavouriteSong(favouriteSong){}

	void Learn() {
		cout << "Student: " << Name << " learns" << endl;
	}

	void Walk(const string& destination) const override {
		cout << "Student: " << Name << " walks to: " << destination << endl;
		SingSong();
	}

	void SingSong() const {
		cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
	}

private:
	const string FavouriteSong;
};


class Teacher: public Human {
public:

	Teacher(const string& name, string subject) :Human(name, "Teacher"), Subject(subject){}

	void Teach() {
		cout << "Teacher: " << Name << " teaches: " << Subject << endl;
	}

	void Walk(const string& destination) const override {
		cout << "Teacher: " << Name << " walks to: " << destination << endl;
	}

private:
	const string Subject;
};


class Policeman : Human {
public:
	Policeman(const string& name) :Human(name,"Policeman"){}

	void Check(Human& h) {
		cout << "Policeman: " << Name << " checks Teacher. Teacher's name is: " << h.GetName() << endl;
	}

	void Walk(const string& destination) const override{
		cout << "Policeman: " << Name << " walks to: " << destination << endl;
	}
};

void VisitPlaces(Human& human, vector<string> places) {
	for (const auto& p : places) 
		human.Walk(p);
}


int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });
	system("pause");
	return 0;
}