// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "LinkedListPatientQueue.h"

LinkedListPatientQueue::LinkedListPatientQueue() {
    // TODO: write this constructor
    pn = new PatientNode("null", 0);
}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    // TODO: write this destructor
    clear();
    delete pn;

}

void LinkedListPatientQueue::clear() {
    // TODO: write this function
    while(pn->next != nullptr) {
        PatientNode *trash = pn->next;
        pn->next = pn->next->next;
        delete trash;
    }
}

string LinkedListPatientQueue::frontName() {

    string name;
    if(pn->next != nullptr) {
        name = pn->next->name;
    } else {
        throw "there is NO front patient!!!";
    }
    return name;   // this is only here so it will compile
}

int LinkedListPatientQueue::frontPriority() {
    int priority;
    if(pn->next != nullptr) {
        priority = pn->next->priority;
    } else {
        throw "there is NO front patient!!!";
    }
    return priority;
}

bool LinkedListPatientQueue::isEmpty() {
    // TODO: write this function
    if(pn->next != nullptr) {
        return false;
    } else {
    return true;
    }
       // this is only here so it will compile
}

void LinkedListPatientQueue::newPatient(string name, int priority) {
    PatientNode *middle = pn;
    while((middle->next != nullptr) && (middle->next->priority <= priority)) {
        middle = middle->next;
    }
    PatientNode* n = new PatientNode(name, priority, middle->next);
    middle->next = n;
}

string LinkedListPatientQueue::processPatient() { 
    PatientNode* middle = pn;
    string name;
    if(middle->next != nullptr) {
         name = pn->next->name;
        PatientNode *trash = pn->next;
        pn->next = pn->next->next;
        delete trash;
    } else {
        throw "there is NO patient!!!";
    }

    return name;
}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {

    PatientNode* middle = pn;
    int mark = 1;
    while(middle->next != nullptr) {
        if(middle->next->name == name && middle->next->priority > newPriority) {
            mark = 0;
            PatientNode *trash = middle->next;
            middle->next = middle->next->next;
            delete trash;
            newPatient(name, newPriority);
            break;
        }
        middle = middle->next;
    }
    if(mark) {
      throw "there is NO this patient or already has a more urgent priority than the given new priority!!!";
    }
}

string LinkedListPatientQueue::toString() {
    // TODO: write this function
    string output = "{";
    PatientNode* middle = pn;

    while(middle->next != nullptr) {
        output += ", ";
        output += to_string(middle->next->priority);
        output += ":";
        output += middle->next->name;
        middle = middle->next;

    }
    if(middle->priority != 0 && middle->name != "null") {
        output.erase(1, 2);
    }
    output += "}";


    return output;
}
