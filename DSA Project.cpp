//DSA Project of 84259, 83694, 86158, 84258
//Ikigai Customer Support System
#include <iostream>
#include <string>
#include <windows.h>
#include<ctime>

using namespace std;

struct Node {
    int ticketID;
    string customerName;
    string contactInfo;
    string issueType;
    string description;
    string timestamp;
    string status;
    string updates;
    Node *next;
    bool resolved;
};

class Service {
private:
    Node *front;
    Node *rear;
    int ticketCounter;

public:
    // constructor
    Service() {
        front = NULL;
        rear = NULL;
        ticketCounter = 1;
    }
    void listTicket(int unresolved);
    void addTicket(int ticketID, string customerName, string contactInfo, string issueType, string description, string timestamp, string status);
    void deleteTicket(int ticketID);
    void updateTicket(int ticketID, string customerName, string contactInfo, string issueType, string description, string timestamp, string status);
	void searchTicketID(int ticketID);
    void searchName(string customerName);
    void searchIssue(string issueType);
    void viewAll();
    void viewNextTicket();
    void viewresolved_and_unresolved_Ticket(string status);
    void bubbleSort(Node *arr, int size);
    void generateSummaryReport();
};

//List ticket
void Service::listTicket(int unresolved) {
    Node *current = front;
	int total;
		
	    if (current == NULL) {
	        cout << "No ticket found in the list!" << endl;
	    }else{
	    	while (current != NULL){
	    		if (current->status == "Unresolved"){
	    			unresolved++;
				}
				current = current->next;
				total = unresolved;
			}
			cout << "Total number of Unresolved Issues: " << total << endl;
		}
}

//Add ticket
void Service::addTicket(int ticketID, string customerName, string contactInfo, string issueType, string description, string timestamp, string status) {
    Node *newTicket = new Node;   //allocate new memory 
    newTicket->ticketID = ticketCounter++;   //increase total number of tickets
    newTicket->customerName = customerName;
    newTicket->contactInfo = contactInfo;
    newTicket->issueType = issueType;
    newTicket->description = description;
    newTicket->timestamp = timestamp;
    newTicket->status = status;
    newTicket->next = NULL;  //set to NULL if new ticket is last

    if (front == NULL) {    //check if empty
        front = newTicket;
        rear = newTicket;
    } else {                //if not empty
        rear->next = newTicket;
        rear = newTicket;
    }
}

//Delete ticket
void Service::deleteTicket(int ticketID)
{
	 if (front == NULL) {    //if empty list
        cout << "No ticket found." << endl;
        return;
    }
    
    Node* current = front;
    Node* previous = NULL;

    // Check if the first ticket matches the given ticketID
    if (current->ticketID == ticketID) {
        front = current->next;
        delete current;
        cout << "Ticket deleted successfully." << endl;
        return;
    }

    // Search for the ticket in the queue
    while (current != NULL && current->ticketID != ticketID) {
        previous = current;
        current = current->next;
    }

    // If ticket not found
    if (current == NULL) {
        cout << "No ticket found with ID " << ticketID << endl;
        return;
    }

    // Update the links to skip the ticket to be deleted
    previous->next = current->next;

    // If the last ticket is being deleted, update the rear pointer
    if (current == rear)
        rear = previous;

    delete current;
    cout << "Ticket deleted successfully." << endl;
}

//Update Ticket
void Service::updateTicket(int ticketID, string customerName, string contactInfo, string issueType, string description, string timestamp, string status){

	Node *current = front;
	bool found = false;
    
	while (current !=NULL){     //when list is not empty
		if (current->ticketID == ticketID) {     //ticket ID found
            found = true;
		    cout << "Ticket ID: " << current->ticketID << " has found" << endl;
		    cout << "Enter Customer Name: ";
            getline(cin, current->customerName);
            cout << "Enter Contact Information: ";
            getline(cin, current->contactInfo);
            cout << "Enter Issue Type (Inquiry, Complaint, Request): ";
            getline(cin, current->issueType);
            cout << "Enter Description: ";
            getline(cin, current->description);
            cout << "Enter Status (Resolved or Unresolved) for your ticket: ";
            getline(cin, current->status);
            cout << "Your ticket is updated" << endl;
            break;
        }
        
        current = current->next;
    }
    
    if (!found) {  //Ticket ID not found
        cout << "No ticket found with ID " << ticketID << endl;
	}
}

// Search through ticket ID
void Service::searchTicketID(int ticketID) {
    if (front == NULL) {
        system("cls");
        cout << "The list is empty." << endl;
        return;
    }

    // Count the number of nodes in the linked list
    int countNodes = 0;
    Node *current = front;
    
    while (current != NULL) {
        countNodes++;
        current = current->next;
    }

    // Create an array to store the ticket IDs
    int *ticketIDs = new int[countNodes];
    current = front;
    for (int i = 0; i < countNodes; i++) {
        ticketIDs[i] = current->ticketID;
        current = current->next;
    }

    // Perform binary search
    int left = 0;
    int right = countNodes - 1;
    bool found = false;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (ticketIDs[mid] == ticketID) {
            found = true;
            current = front;
            while (current != NULL) {
                if (current->ticketID == ticketID) {
                    system("cls");
                    cout << "Ticket ID found." << endl;
                    cout << endl;
                    cout << "Ticket ID: " << current->ticketID << endl;
                    cout << "Customer Name: " << current->customerName << endl;
                    cout << "Contact Information: " << current->contactInfo << endl;
                    cout << "Issue Type: " << current->issueType << endl;
                    cout << "Description: " << current->description << endl;
                    cout << "Status: " << current->status << endl;
                    break;
                }
                current = current->next;
            }
            break;
        }
        else if (ticketIDs[mid] < ticketID) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    
    delete[] ticketIDs;

    if (!found) {
        system("cls");
        cout << "Ticket ID has not been found." << endl;
    }
}

// Search through Name
void Service::searchName(string customerName) {
    Node *current = front;
    bool found = false;

    if (front == NULL) {
        system("cls");
        cout << "The list is empty." << endl;
    }
    else {
        while (current != NULL) {
            if (current->customerName == customerName) {
            	if (!found) {
					system("cls");
					cout << "The customer has found." << endl;
					found = true;
				}
                cout << "Ticket ID:" << current->ticketID << endl;
                cout << "Customer Name: " << current->customerName << endl;
                cout << "Contact Information: " << current->contactInfo << endl;
                cout << "Issue Type: " << current->issueType << endl;
                cout << "Description: " << current->description << endl;
                cout << "Date: " << current->timestamp << endl;
                cout << "Status: " << current->status << endl;
                cout << endl;
            }
            current = current->next;
        }
    }
    if (!found) {
        system("cls");
        cout << "This customer name has not found." << endl;
    }
}

// Search through issue type
void Service::searchIssue(string issueType) {
    Node *current = front;
    bool found = false;

    if (front == NULL) {
        system("cls");
        cout << "The list is empty." << endl;
    }
    else {
        while (current != NULL) {
            if (current->issueType == issueType) {
                if (!found) {
                    system("cls");
                    cout << "The issue type has found." << endl;
                    found = true;
                }
                cout << endl;
                cout << "Ticket ID:" << current->ticketID << endl;
                cout << "Customer Name: " << current->customerName << endl;
                cout << "Contact Information: " << current->contactInfo << endl;
                cout << "Issue Type: " << current->issueType << endl;
                cout << "Description: " << current->description << endl;
                cout << "Date: " << current->timestamp << endl;
                cout << "Status: " << current->status << endl; // display
            }
            current = current->next;
        }
    }

    if (!found) {
        system("cls");
        cout << "This issue type has not found." << endl;
    }
}

//View all ticket
void Service::viewAll() {
    Node *current = front;

    if (current == NULL) {
        cout << "No ticket found." << endl;
        return;
    }

    while (current != NULL) {
        cout << "Ticket ID: " << current->ticketID << endl;
        cout << "Customer Name: " << current->customerName << endl;
        cout << "Contact Information: " << current->contactInfo << endl;
        cout << "Issue Type: " << current->issueType << endl;
        cout << "Description: " << current->description << endl;
        cout << "Date: " << current->timestamp << endl;
        cout << "Status: " << current->status << endl;
        cout << "----------------------------------------" << endl;

        current = current->next;
    }
}

//View next ticket
void Service::viewNextTicket() {

//Static retains its value across multiple function calls. Static variable current is used to keep track of the current ticket being processed.
    static Node* current = front;
	if(current != NULL){
		cout << "Ticket ID: " << current->ticketID << endl;
	    cout << "Customer Name: " << current->customerName << endl;
	    cout << "Contact Information: " << current->contactInfo << endl;
	    cout << "Issue Type: " << current->issueType << endl;
	    cout << "Description: " << current->description << endl;
	    cout << "Date: " << current->timestamp << endl;
	    cout << "Status (Solved or Unresolved): " << current->status << endl;
	    cout << "----------------------------------------" << endl;
	    current = current->next;
	}
    else {
        cout << "No ticket found." << endl;
        return;
	}
}

//View resolved or unresolved ticket
void Service::viewresolved_and_unresolved_Ticket(string status) {
	
    Node* current = front;
    bool found = false;
     
	if (front == NULL) {
	        system("cls");
	        cout << "No ticket found in the list." << endl;
	    }
	    else {
	        while (current != NULL) {
	            if (current->status == status) {
	                if (!found) {
	                    found = true;
	                }
	                cout << endl;
	                cout << "Ticket ID:" << current->ticketID << endl;
	                cout << "Customer Name: " << current->customerName << endl;
	                cout << "Contact Information: " << current->contactInfo << endl;
	                cout << "Issue Type: " << current->issueType << endl;
	                cout << "Description: " << current->description << endl;
	                cout << "Date: " << current->timestamp << endl;
	                cout << "Status: " << current->status << endl; 
	            }
	            current = current->next;
	        }
		}
}

//Perform bubble sort
void Service::bubbleSort(Node* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].status > arr[j + 1].status) {
                // Swap elements
                Node temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

//Generate summary report
void Service::generateSummaryReport() {
    int resolved = 0;
    int unresolved = 0;
    int totalTickets = 0;

    Node* current = front;

    while (current != NULL) {
        totalTickets++;
        if (current->status == "Resolved") {
            resolved++;
        } else if (current->status == "Unresolved") {
            unresolved++;
        }
        current = current->next;
    }

    // Create an array to store the tickets
    Node* tickets = new Node[totalTickets];

    // Populate the array with ticket data
    current = front;
    int index = 0;
    while (current != NULL) {
        tickets[index++] = *current;
        current = current->next;
    }

    // Sort the array by status
    bubbleSort(tickets, totalTickets);

    double resolvedPercentage = (double)resolved / totalTickets * 100;
    double unresolvedPercentage = (double)unresolved / totalTickets * 100;

    cout << "Summary Report:" << endl;
    cout << "Total Tickets: " << totalTickets << endl;
    cout << "Resolved Tickets: " << resolved << " (" << resolvedPercentage << "%)" << endl;
    cout << "Unresolved Tickets: " << unresolved << " (" << unresolvedPercentage << "%)" << endl;

    // Cleanup: deallocate the dynamic array
    delete[] tickets;
}

int main(){
	const int size = 100;
	Node tickets[size];
	int unresolved = 0; 

	int ticketID;
    string customerName;
    string contactInfo;
    string issueType;
    string description;
    string timestamp;
    string status;
    string updates;
	
    Service service;
    service.addTicket(1, "John", "john@gmail.com", "Inquiry", "Discrepancy in the amount charged", "2/6/2023", "Unresolved");
    service.addTicket(2, "James", "james05@gmail.com", "Inquiry", "Questions about my invoice", "3/6/22023", "Resolved");
    service.addTicket(3, "Bob", "bob@gmail.com", "Complaint", "Error message display on the screen", "4/6/2023", "Unresolved");
    service.addTicket(4, "Alice", "alice98@gmail.com", "Complaint", "Data loss after update", "5/6/2023", "Resolved");
    service.addTicket(5, "Jane Smith", "jane543@gmail.com", "Request", "Refund request for a cancelled service", "6/6/2023", "Unresolved");
	
    while (true) {
        cout << "======================================================" << endl;
        cout << "            Ikigai Customer Support System            " << endl;
        cout << "======================================================" << endl;
        int option;
        cout << "1. List of Issues" << endl;
        cout << "2. Manage Issues" << endl;
        cout << "3. Searching" << endl;
        cout << "4. View Issues" << endl;
        cout << "5. Summary Report" << endl;
        cout << "6. Exit." << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "Option:";
        cin >> option;

        switch (option) {
            case 1:
                system("cls");
                cout << "Main Issues: " << endl << endl;
                cout << "Inuqiries" << endl;
                cout << "Complaints" << endl;
                cout << "Requests" << endl << endl;
                service.listTicket(unresolved);
                break;
            case 2:
            	int choice;
            	cout << "Manage Issues" << endl;
			    cout << "1. Add ticket" << endl;
                cout << "2. Delete ticket" << endl;
                cout << "3. Update ticket" << endl;
                cout << "4. Return main screen" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                if (choice == 1) {
                    time_t currentTime = time(0);
                    char* timestamp = ctime(&currentTime);
                    cout << "Enter Customer Name: ";
                    cin.ignore(); 
                    getline(cin, customerName);
                    cout << "Enter Contact Information: ";                
                    getline(cin, contactInfo);
                    cout << "Enter Issue Type (Inquiry, Complaint, Request): ";  
                    getline(cin, issueType);
                    cout << "Enter Description: ";
                    getline(cin, description);
                    cout << "Enter Status (Resolved or Unresolved) for your ticket: ";
                    getline(cin, status);
                    service.addTicket(ticketID, customerName, contactInfo, issueType, description, timestamp, status);
                    cout << "The ticket was added successfully!" << endl;
                    break;
                    }
                else if (choice == 2) {
                    cout << "Enter the ticket ID to delete: ";
                    cin >> ticketID;
                    service.deleteTicket(ticketID);
                    break;
                    }
                else if (choice == 3) {
                	time_t currentTime = time(0);
					char* timestamp = ctime(&currentTime);
                    cout << "Please update your information" << endl;
                    cout << "Enter ticket ID: ";
                    cin >> ticketID;
                    cin.ignore(); 
                    service.updateTicket(ticketID, customerName, contactInfo, issueType, description, timestamp, status);
                    break;
                    }
                else if (choice == 4) {
                	system("cls");
                    break;  
                    }
				else{
					system("cls");
	                cout << "Invalid input. Please try again." << endl;
                	}
                	break;
                
            case 3:
                system("cls");
                cout << "Searching List:" << endl;
                cout << "1. Ticket ID" << endl;
                cout << "2. Customer Name" << endl;
                cout << "3. Issue Type" << endl;
                cout << "4. Return main screen" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1) {
                    system("cls");
                    cout << "Enter Ticket ID: ";
                    cin >> ticketID;
                    service.searchTicketID(ticketID);
                    break;
                } else if (choice == 2) {
                    system("cls");
                    cout << "Enter customer's name: ";
                    cin.ignore();
                    getline(cin, customerName);
                    service.searchName(customerName);
                    break;
                } else if (choice == 3) {
                    system("cls");
                    cout << "Enter issue type (Inquiry, Complaint, Request): ";
                    cin.ignore();
                    getline(cin, issueType);
                    service.searchIssue(issueType);
                    break;
                } else if (choice == 4) {
                    system("cls");
                    break;
                } else {
                    system("cls");
                    cout << "Invalid input. Please try again." << endl;
                }
                break;
                
            case 4:
                system("cls");
                int viewChoice;
                cout << "1. View All Tickets" << endl;
                cout << "2. View Next Ticket" << endl;
                cout << "3. View Resolved or Unresolved Tickets" << endl;
                cout << "4. Return main screen" << endl;
                cout << "Enter your choice: " << endl;
                cin >> viewChoice;

                if (viewChoice == 1) {
                    service.viewAll();
                    break;
                } else if (viewChoice == 2) {
                    service.viewNextTicket();
                    break;
                } else if (viewChoice == 3) {
                    cout << "Enter Status (Resolved or Unresolved) to check the tickets: ";
                    cin >> status;
                    service.viewresolved_and_unresolved_Ticket(status);
                    break;
                }
                else if (viewChoice == 4) {
                    system("cls");
                    break;
                } else {
                    system("cls");
                    cout << "Invalid input. Please try again." << endl;
                }
                break;
                
            case 5:
                system("cls");
                service.generateSummaryReport();
  				break;
                
            case 6:
                exit(0);
                
            default:
                system("cls");
                cout << "Invalid option. Please try again." << endl;
        }
        cout << endl;
        system("pause");
        system("cls");
	}
    return 0;
}
