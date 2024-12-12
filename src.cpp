#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Room {
public:
    int room_number;
    string room_type;
    double price_per_night;
    bool is_occupied;

    Room(int room_number, string room_type, double price_per_night) {
        this->room_number = room_number;
        this->room_type = room_type;
        this->price_per_night = price_per_night;
        this->is_occupied = false;
    }
};

class Guest {
public:
    string name;
    string address;
    string contact_number;
    int room_number;

    Guest(string name, string address, string contact_number, int room_number) {
        this->name = name;
        this->address = address;
        this->contact_number = contact_number;
        this->room_number = room_number;
    }
};

class HotelManagementSystem {
private:
    vector<Room> rooms;
    vector<Guest> guests;

public:
void addRoom() {
    int roomNumber;
    string roomType;
    double pricePerNight;

    cout << "Enter room number: ";
    cin >> roomNumber;

    cout << "Enter room type (e.g., Deluxe, Standard): ";
    cin >> roomType;

    cout << "Enter price per night: ";
    cin >> pricePerNight;

    // Check for duplicate room numbers
    for (Room room : rooms) {
        if (room.room_number == roomNumber) {
            cout << "Room number already exists.\n";
            return;
        }
    }

    // Create a new Room object and add it to the vector
    Room newRoom(roomNumber, roomType, pricePerNight);
    rooms.push_back(newRoom);

    cout << "Room added successfully!\n";
}

void addGuest() {
    string name, address, contactNumber;
    int roomNumber;

    cout << "Enter guest name: ";
    cin.ignore(); // Ignore the newline character in the input buffer
    getline(cin, name);

    cout << "Enter guest address: ";
    getline(cin, address);

    cout << "Enter guest contact number: ";
    cin >> contactNumber;

    cout << "Enter room number to be assigned: ";
    cin >> roomNumber;

    // Check if room is available
    bool roomAvailable = false;
    for (Room& room : rooms) {
        if (room.room_number == roomNumber && !room.is_occupied) {
            roomAvailable = true;
            break;
        }
    }

    if (roomAvailable) {
        // Create a new Guest object and add it to the vector
        Guest newGuest(name, address, contactNumber, roomNumber);
        guests.push_back(newGuest);

        // Update room occupancy
        for (Room& room : rooms) {
            if (room.room_number == roomNumber) {
                room.is_occupied = true;
                break;
            }
        }

        cout << "Guest added successfully!\n";
    } else {
        cout << "Room not available.\n";
    }
}
void displayAvailableRooms() {
    cout << "\nAvailable Rooms:\n";
    cout << "--------------------\n";

    for (Room room : rooms) {
        if (!room.is_occupied) {
            cout << "Room Number: " << room.room_number << endl;
            cout << "Room Type: " << room.room_type << endl;
            cout << "Price per Night: " << room.price_per_night << endl;
            cout << "--------------------\n";
        }
    }
}
void bookRoom() {
    int roomNumber;
    string guestName;

    cout << "Enter room number: ";
    cin >> roomNumber;

    cout << "Enter guest name: ";
    cin >> guestName;

    for (Room& room : rooms) {
        if (room.room_number == roomNumber && !room.is_occupied) {
            // Find a suitable guest and assign the room
            for (Guest& guest : guests) {
                if (guest.name == guestName) {
                    room.is_occupied = true;
                    guest.room_number = roomNumber;
                    cout << "Room booked successfully!\n";
                    return;
                }
            }
            cout << "Guest not found.\n";
            return;
        }
    }
    cout << "Room not available.\n";
}
void generateBill() {
    string guestName;
    int roomNumber, daysStayed;
    double totalBill = 0;

    cout << "Enter guest name: ";
    cin.ignore(); // Ignore the newline character in the input buffer
    getline(cin, guestName);

    cout << "Enter room number: ";
    cin >> roomNumber;

    cout << "Enter number of days stayed: ";
    cin >> daysStayed;

    // Find the guest and room details
    for (Guest guest : guests) {
        if (guest.name == guestName && guest.room_number == roomNumber) {
            for (Room room : rooms) {
                if (room.room_number == roomNumber) {
                    totalBill = daysStayed * room.price_per_night;
                    break;
                }
            }
            break;
        }
    }

    // Print the bill
    cout << "\nGuest Name: " << guestName << endl;
    cout << "Room Number: " << roomNumber << endl;
    cout << "Days Stayed: " << daysStayed << endl;
    cout << "Total Bill: Rs. " << totalBill << endl;
}

void checkInOutGuest() {
    string guestName;
    int roomNumber;
    char action; // 'I' for check-in, 'O' for check-out

    cout << "Enter guest name: ";
    getline(cin, guestName);

    cout << "Enter room number: ";
    cin >> roomNumber;

    cout << "Enter action (I for check-in, O for check-out): ";
    cin >> action;

    // Find the guest and room
    for (Guest& guest : guests) {
        if (guest.name == guestName && guest.room_number == roomNumber) {
            for (Room& room : rooms) {
                if (room.room_number == roomNumber) {
                    if (action == 'I') {
                        // Check-in
                        room.is_occupied = true;
                        cout << "Guest checked in successfully!\n";
                    } else if (action == 'O') {
                        // Check-out
                        room.is_occupied = false;
                        guest.room_number = 0; // Clear room assignment
                        cout << "Guest checked out successfully!\n";
                    } else {
                        cout << "Invalid action. Please enter 'I' or 'O'.\n";
                    }
                    return;
                }
            }
        }
    }

    cout << "Guest not found or room not assigned.\n";
}


public:
void displayMenu() {
    cout << "\n=======================================\n";
    cout << "   Hotel Management System\n";
    cout << "=======================================\n";
    cout << "1. Add Room\n";
    cout << "2. Add Guest\n";
    cout << "3. Display Available Rooms\n";
    cout << "4. Book a Room\n";
    cout << "5. Check In/Out Guest\n";
    cout << "6. Generate Bill\n";
    cout << "7. Exit\n";
    cout << "=======================================\n";
    cout << "Enter your choice: ";
}

    void run() {
        int choice;
        do {
            displayMenu();
            cin >> choice;

            switch (choice) {
                case 1:
                    // Add room
                    addRoom();
                    break;
                case 2:
                    // Add guest
                    addGuest();
                    break;
                case 3:
                    //Display available rooms
                    displayAvailableRooms();
                    break;
                case 4:
                    bookRoom();
                    break;
                case 5:
                    // Check in/out guest
                    checkInOutGuest();
                    break;
                case 6:
                    // Generate bill
                    generateBill();
                    break;
                case 7:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 7);
    }
};

int main() {
    HotelManagementSystem hotel;
    hotel.run();
    return 0;
}