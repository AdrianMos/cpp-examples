/*
An Observer Pattern example using the push mechanism:
  A news agency (the subject) sends news to all subscribed
  observers (mobile phones / smart watches).

Copyright (C) 2016, Adrian Raul Mos

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.*/


#include "stdafx.h"
#include <list>
#include <iostream>
#include <string>
using namespace std;

class ObserverInterface {
public:
	// Every observer must implement the update() function
	// This function is called by the subject for sending 
	// updates to the observers
	virtual void Update(string headline, string story) = 0;
};

class SubjectInterface {
public:
	// Every subject must allow observers to subscribe and
	// unsubscribe
	virtual void SubscribeObserver(ObserverInterface* observer) = 0;
	virtual void UnsubscribeObserver(ObserverInterface* observer) = 0;

	// Every subject must implement the notifyObservers function
	// This function is used for notifying all observers about
	// updates in the subject. The notification is done by calling
	// the update() function of every observer.
	virtual void NotifyObservers() = 0;
};

// A news agency is a good example for a Subject
// Observers subscribe to the agency for receiving news
class NewsAgency : public SubjectInterface {
private:
	list<ObserverInterface* > observersList_;
	string headline_ = "";
	string story_ = "";

public:
	void SubscribeObserver(ObserverInterface* observer) {
		observersList_.push_back(observer);
	}

	void UnsubscribeObserver(ObserverInterface* observer) {
		observersList_.remove(observer);
	}

	void PublishNews(string headline, string story) {
		headline_ = headline;
		story_ = story;
		PrintNews(headline, story);
		NotifyObservers();
	}

protected:
	// Sends the news to all subscribed observers
	// by calling their Update() function
	void NotifyObservers() {
		list<ObserverInterface*>::iterator i = observersList_.begin();
		while (i != observersList_.end()) {
			((ObserverInterface*)(*i))->Update(headline_, story_);
			++i;
		}
	}

	void PrintNews(string headline, string story) {
		cout << endl << endl;
		cout << "News agency is having ";
		cout << std::to_string(observersList_.size());
		cout << " observers" << endl;
		cout << "   publishing: \"";
		cout << headline << ": " << story << "\"" << endl;
		cout << "---------------------------------------------------" << endl;
	}
};

// A mobile phone implements the ObserverInterface interface
// in order to receive news
class MobilePhone : public ObserverInterface
{
private:
	string phone_name_ = "";
	string headline_ = "";
	string story_ = "";
	
public:
	MobilePhone(string phone_name) : phone_name_(phone_name) {
	}
	
	void DisplayNews() {
		cout << "Mobile phone \"" << phone_name_ << "\" ";
		cout << "received news: \"" << headline_ << ": ";
		cout << story_ << "\"" << endl;
	}

	void Update(string headline, string story) {
		headline_ = headline;
		story_ = story;
		DisplayNews();
	}
};

// A smart watch implements the ObserverInterface interface
// in order to receive news
class SmartWatch : public ObserverInterface
{
private:
	string smartwatch_name_ = "";
	string headline_ = "";

public:
	SmartWatch(string smartwatch_name) : smartwatch_name_(smartwatch_name) {
	}

	// A smart watch is able to dipslay only headlines
	void DisplayHeadline() {
		cout << "Smart watch \"" << smartwatch_name_ << "\" ";
		cout << "received news: \"" << headline_ << "\"" << endl;
	}

	void Update(string headline, string story) {
		headline_ = headline;
		DisplayHeadline();
	}
};

void main(int argc, char *argv[]) {

	NewsAgency * news_agency = new NewsAgency;
	
	SmartWatch* smart_watch1 = new SmartWatch("Alex's watch");
	MobilePhone* mobile_phone1 = new MobilePhone("Leo's phone");
	MobilePhone* mobile_phone2 = new MobilePhone("Alex's phone");

	news_agency->PublishNews("Headline #0", "Story0");

	// Subscribe first observer
	news_agency->SubscribeObserver(smart_watch1);
	news_agency->PublishNews("Headline #1", "Story1");
	
	// Subscribe two more observers
	news_agency->SubscribeObserver(mobile_phone1);
	news_agency->SubscribeObserver(mobile_phone2);

	news_agency->PublishNews("Headline #2", "Story2");
	news_agency->PublishNews("Headline #3", "Story3");

	// Unsubscribe the smartwatch
	news_agency->UnsubscribeObserver(smart_watch1);
	news_agency->PublishNews("Headline4", "Story4");

	delete smart_watch1;
	delete mobile_phone1;
	delete news_agency;

	cout << endl << "Press any key to exit";
	std::cin.ignore();
};