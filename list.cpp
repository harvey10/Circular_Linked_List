#include "list.h"
#include <iostream>
#include <iomanip>

using namespace std;

void CList::disp() {
  cout << left << setw(5) << "ID" << setw(10) << "ADDRESS" << setw(20)
       << "INFO" << endl;
  for (int i = 0; i < count; i++) {
    cout << setw(5) << current->id << setw(10) << current << setw(20)
	 << current->info << endl;
    current = current->next;
  }
  cout << setfill('-') << setw(35) << "-" << endl;
  cout << setfill(' ');
}

void CList::shiftRight() {
  current = current->next;
}

void CList::shiftLeft() {
  current = current->back;
}

void CList::addElement(const string data, const int nextID) {
  CElem *newNode;
  CElem *beforeCurrent;

  newNode = new CElem;
  newNode->info = data;
  newNode->id = nextID;

  if (isEmpty()) {
    newNode->next = newNode;
    newNode->back = newNode;
    current = newNode;
  }
  else {
    beforeCurrent = current->back;
    newNode->next = current;
    newNode->back = beforeCurrent;
    current->back = newNode;
    beforeCurrent->next = newNode;
  }
  count++;
}

void CList::removeElement(int searchID) {
  CElem *trailCurrent;
  int searchCount = 0;
  bool found = false;
  try {
    if (isEmpty())
      cout << "List is empty. Nothing to delete." << endl;
    else {
      while (searchCount <= count && !found) {
	if (current->id == searchID)
	  found = true;
	else {
	  current = current->next;
	  searchCount++;
	}
      }
      if (current->id != searchID)
	throw searchID;
      else if (current->id == searchID) {
	trailCurrent = current->back;
	trailCurrent->next = current->next;
	current->next->back = trailCurrent;
	count--;
	delete current;
	current = trailCurrent->next;
      }
      else {
	throw searchID;
      }
    }
  }
  catch (int searchID) {
    cout << searchID << " is not in the list." << endl;
  }
}

bool CList::isEmpty() const {
  return (count == 0);
}

int CList::length() const {
  return count;
}

CList::CList() {
  count = 0;
  current = NULL;
}

CList::~CList() {
  CElem *trailCurrent;
  if (!isEmpty()) {
    for (int i = 0; i < count; i++) {
      trailCurrent = current;
      current = current->next;
      delete trailCurrent;
    }
  }
}
