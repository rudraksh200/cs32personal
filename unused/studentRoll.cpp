#include <string>
#include "studentRoll.h"

StudentRoll::StudentRoll() {
  head = tail = NULL;
}

void StudentRoll::insertAtTail(const Student &s) {
  Node* p = new Node;
  p->next = NULL;
  p->s = new Student(s);

  if(head == NULL){
    head = p;
    tail = p;
  }
  else{
    tail->next = p;
    tail = p;
  }
}

std::string StudentRoll::toString() const {
  std::string str = "[";
  Node* temp = head;
  while(temp != NULL){
    str += temp->s->toString() + ",";
    temp = temp->next;
  }
  if(head != NULL){
    str[str.length()-1] = ']';
  }
  else{
    str += "]";
  }
  return str;
}

StudentRoll::StudentRoll(const StudentRoll &orig) {
  if(orig.head == NULL){
    head = NULL;
    tail = NULL;
    return;
  }
  head = tail = NULL;
  Node* temp = orig.head;
  Node* curr = head;
  Node* prev = NULL;
  while(temp != NULL){
    curr = new Node;
    if(head == NULL){
      head = curr;
    }
    curr->s = new Student(*(temp->s));
    temp = temp->next;
    if(prev != NULL){
      prev->next = curr;
    }
    prev = curr;
    curr->next = nullptr;
  }

  tail = curr;

}

StudentRoll::~StudentRoll() {
  if(head == NULL){
    return;
  }
  Node* temp = head;
  Node* prev = NULL;
  while(temp != NULL){
    delete temp->s;
    prev = temp;
    temp = temp->next;
    delete prev;
  }

  head = NULL;
  tail = NULL;
}

StudentRoll & StudentRoll::operator =(const StudentRoll &right ) {
  // The next two lines are standard, and you should keep them.
  // They avoid problems with self-assignment where you might free up 
  // memory before you copy from it.  (e.g. x = x)

  if (&right == this) 
    return (*this);

  // TODO... Here is where there is code missing that you need to 
  // fill in...
  
  if(head != NULL){
    Node* temp = head;
    Node* prev = NULL;
    while(temp != NULL){
      delete temp->s;
      prev = temp;
      temp = temp->next;
      delete prev;
    }

    head = NULL;
    tail = NULL;
  }

  if(right.head == NULL){
    head = NULL;
    tail = NULL;
  }
  else{
    head = tail = NULL;
    Node* temp = right.head;
    Node* curr = head;
    Node* prev = NULL;
    while(temp != NULL){
      curr = new Node;
      if(head == NULL){
        head = curr;
      }
      curr->s = new Student(*(temp->s));
      temp = temp->next;
      if(prev != NULL){
        prev->next = curr;
      }
      prev = curr;
      curr->next = nullptr;
    }
    
    tail = curr;
  
  }


  // KEEP THE CODE BELOW THIS LINE
  // Overloaded = should end with this line, despite what the textbook says.
  return (*this); 
  
}





