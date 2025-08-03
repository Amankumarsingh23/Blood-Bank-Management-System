#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

const string DATA_FILE = "bloodbank_data.txt";

//--------------------------------------------------------------------------------
// HOSPITAL CLASS
//--------------------------------------------------------------------------------
class Hospital {
public:
    int hospitalID;
    string contactno;

    void registerHospital(int id) {
        this->hospitalID = id;
        cout << "\n Enter Contact no :";
        cin >> this->contactno;
        cout << " Your Hospital ID is : " << this->hospitalID << endl;
    }

    void paymentCheck() {
        char ch;
        cout << " Has payment been made? (y/n) " << endl;
        cin >> ch;
        if (ch == 'y' || ch == 'Y') {
            cout << " Transaction complete" << endl;
        } else {
            cout << " Transaction incomplete" << endl;
        }
    }
};

//--------------------------------------------------------------------------------
// DONOR CLASS
//--------------------------------------------------------------------------------
class Donor {
public:
    int fitness;
    string name;
    string contact;
    int donorID;
    string bloodgroup;
    char rhesius;

    void registerDonor(int id) {
        this->donorID = id;
        
        cout << "\n Enter Name : ";
        cin.ignore(10000, '\n'); 
        getline(cin, this->name);
        
        cout << "\n Enter Contact no : ";
        cin >> this->contact;
        
        cout << "\n Enter Fitness state (1-fit, 0-unfit) : ";
        while (!(cin >> this->fitness) || (this->fitness != 0 && this->fitness != 1)) {
            cout << "Invalid fitness state! Please enter 1 or 0: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        while (true) {
            cout << "\n Enter Blood type (A, B, AB, O) : ";
            cin >> this->bloodgroup;
            if (this->bloodgroup == "AB" || this->bloodgroup == "ab") {
                this->bloodgroup = "AB";
                break;
            } else if (this->bloodgroup == "A" || this->bloodgroup == "B" || this->bloodgroup == "O" ||
                       this->bloodgroup == "a" || this->bloodgroup == "b" || this->bloodgroup == "o") {
                this->bloodgroup[0] = toupper(this->bloodgroup[0]);
                break;
            } else {
                cout << "\n Invalid Blood type";
            }
        }
        
        while (true) {
            cout << "\n Enter your rhesius status (+ or -) : ";
            cin >> this->rhesius;
            if (this->rhesius == '+' || this->rhesius == '-') {
                break;
            } else {
                cout << "\n Invalid rhesius status";
            }
        }

        cout << "\n Your Donor ID is : " << this->donorID << endl;
    }

    void updateDonor() {
        int choice;
        cout << "\n Enter choice : \n 1. Update fitness state \n 2. Update contact number " << endl;
        while (!(cin >> choice) || (choice != 1 && choice != 2)) {
            cout << "Invalid choice! Please enter 1 or 2: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (choice) {
            case 1:
                cout << "\n Enter new fitness state (1-fit, 0-unfit) :";
                while (!(cin >> this->fitness) || (this->fitness != 0 && this->fitness != 1)) {
                    cout << "Invalid fitness state! Please enter 1 or 0: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                break;
            case 2:
                cout << "\n Enter new contact number :";
                cin >> this->contact;
                break;
            default:
                cout << "\n Invalid choice! " << endl;
        }
    }
};

//--------------------------------------------------------------------------------
// BLOOD PACKET CLASS
//--------------------------------------------------------------------------------
class BloodPacket {
public:
    string bloodtype;
    char rhesius;
    int expiryYear;
    bool isAvailable = false; 

    string getFullBloodType() const {
        return bloodtype + rhesius;
    }
};

//--------------------------------------------------------------------------------
// BLOOD BANK CLASS
//--------------------------------------------------------------------------------
class BloodBank {
private:
    int username;
    int password;

    vector<Donor> donors;
    vector<Hospital> hospitals;
    vector<BloodPacket> bloodInventory;

    int nextDonorID = 1;
    int nextHospitalID = 1;

public:
    BloodBank(int a, int b) {
        username = a;
        password = b;
    }

    bool authenticate() {
        int y, z;
        cout << "Enter your username: ";
        cin >> y;
        cout << "Enter your password: ";
        cin >> z;
        if (y == username && z == password) {
            return true;
        } else {
            return false;
        }
    }
    
    int getBloodPacketCost(const string& type, char rhesius) const {
        if (type == "A") return (rhesius == '+') ? 300 : 1000;
        if (type == "B") return (rhesius == '+') ? 400 : 800;
        if (type == "O") return (rhesius == '+') ? 300 : 2000;
        if (type == "AB") return (rhesius == '+') ? 500 : 1000;
        return 0;
    }

    int findAvailablePacket(const string& type, char rhesius) {
        for (size_t i = 0; i < bloodInventory.size(); ++i) {
            if (bloodInventory[i].isAvailable && 
                bloodInventory[i].bloodtype == type && 
                bloodInventory[i].rhesius == rhesius &&
                bloodInventory[i].expiryYear > 2025) { 
                return i;
            }
        }
        return -1;
    }

    void registerDonor() {
        Donor newDonor;
        newDonor.registerDonor(nextDonorID);
        donors.push_back(newDonor);
        nextDonorID++;
    }

    void updateDonor() {
        int id;
        cout << "Enter Donor ID to update: ";
        while (!(cin >> id) || id < 1 || id >= nextDonorID) {
            cout << "Invalid Donor ID. Please enter a valid ID: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        donors[id - 1].updateDonor();
    }

    void registerHospital() {
        Hospital newHospital;
        newHospital.registerHospital(nextHospitalID);
        hospitals.push_back(newHospital);
        nextHospitalID++;
    }

    void donateBlood() {
        int donorID;
        cout << "Enter Donor ID: ";
        while (!(cin >> donorID) || donorID < 1 || donorID >= nextDonorID) {
            cout << "Invalid Donor ID. Please enter a valid ID: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        Donor& d = donors[donorID - 1];

        if (d.fitness == 0) {
            cout << "Donor is not fit to donate." << endl;
            return;
        }

        BloodPacket newPacket;
        newPacket.bloodtype = d.bloodgroup;
        newPacket.rhesius = d.rhesius;
        newPacket.isAvailable = true;
        
        cout << "Enter expiry year: ";
        while (!(cin >> newPacket.expiryYear) || newPacket.expiryYear <= 2025) { 
            cout << "Invalid expiry year. Please enter a year greater than 2025: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        bloodInventory.push_back(newPacket);
        cout << "Blood packet successfully added to inventory." << endl;
    }

    void requestBlood() {
        int hid;
        cout << "Enter Hospital ID: ";
        while (!(cin >> hid) || hid < 1 || hid >= nextHospitalID) {
            cout << "Invalid Hospital ID. Please enter a valid ID: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        string req_t;
        char req_r;
        cout << "Enter required blood type (A, B, AB, O): ";
        cin >> req_t;
        cout << "Enter required rhesius type (+/-): ";
        cin >> req_r;

        int packetIndex = findAvailablePacket(req_t, req_r);

        if (packetIndex != -1) {
            int cost = getBloodPacketCost(req_t, req_r);
            cout << "Cost of the required Blood packet is: " << cost << endl;
            
            hospitals[hid - 1].paymentCheck();

            bloodInventory[packetIndex].isAvailable = false;
        } else {
            cout << "Blood packet is not available." << endl;
        }
    }

    void showDetails() {
        cout << "\nBlood Bank Details" << endl;
        cout << "------------------" << endl;
        
        map<string, int> counts;
        for (const auto& packet : bloodInventory) {
            if (packet.isAvailable) {
                counts[packet.getFullBloodType()]++;
            }
        }
        
        int total = 0;
        for (const auto& pair : counts) {
            cout << " " << pair.first << " : " << pair.second << endl;
            total += pair.second;
        }
        
        cout << "Total available blood packets: " << total << endl;
    }
    
    // --- FINAL FIX: SAVE DATA FUNCTION ---
    void saveData() {
        ofstream outFile(DATA_FILE);
        if (!outFile) {
            cerr << "Error: Could not open file " << DATA_FILE << " for writing." << endl;
            return;
        }
        
        // Save donors
        outFile << "--- DONORS ---" << endl;
        outFile << donors.size() << endl;
        outFile << "DonorID Contact Fitness BloodGroup Rhesus Name" << endl;
        for (const auto& d : donors) {
            outFile << d.donorID << " " << d.contact << " " << d.fitness << " " << d.bloodgroup << " " << d.rhesius << " " << d.name << endl;
        }
        
        // Save hospitals
        outFile << "--- HOSPITALS ---" << endl;
        outFile << hospitals.size() << endl;
        outFile << "HospitalID Contact" << endl;
        for (const auto& h : hospitals) {
            outFile << h.hospitalID << " " << h.contactno << endl;
        }
        
        // Save blood packets
        outFile << "--- BLOOD INVENTORY ---" << endl;
        outFile << bloodInventory.size() << endl;
        outFile << "BloodType Rhesus ExpiryYear Available" << endl;
        for (const auto& b : bloodInventory) {
            outFile << b.bloodtype << " " << b.rhesius << " " << b.expiryYear << " " << b.isAvailable << endl;
        }
        
        // --- FIXED: Persist the ID counters ---
        outFile << "--- IDS ---" << endl;
        outFile << nextDonorID << " " << nextHospitalID << endl;
        
        cout << "Data saved successfully to " << DATA_FILE << "!" << endl;
    }
    
    // --- FINAL FIX: LOAD DATA FUNCTION ---
    void loadData() {
        ifstream inFile(DATA_FILE);
        if (!inFile) {
            cout << "No saved data found. Starting with empty records." << endl;
            return;
        }
        
        donors.clear();
        hospitals.clear();
        bloodInventory.clear();
        
        string line;
        size_t size;
        
        // Load donors
        getline(inFile, line);
        if (!(inFile >> size)) { goto cleanup; }
        inFile.ignore(1000, '\n');
        
        for (size_t i = 0; i < size; ++i) {
            Donor d;
            
            if (!(inFile >> d.donorID >> d.contact >> d.fitness >> d.bloodgroup >> d.rhesius)) {
                cerr << "Error: Corrupted donor data. Stopping load." << endl;
                break;
            }
            getline(inFile, d.name);
            d.name.erase(0, d.name.find_first_not_of(" \t\r\n"));
            
            if (!d.name.empty()) {
                donors.push_back(d);
            } else {
                cerr << "Error: Blank donor name found. Skipping record." << endl;
            }
        }
        
        // Load hospitals
        getline(inFile, line); 
        if (!(inFile >> size)) { goto cleanup; }
        inFile.ignore(1000, '\n');
        
        for (size_t i = 0; i < size; ++i) {
            Hospital h;
            if (!(inFile >> h.hospitalID >> h.contactno)) {
                cerr << "Error: Corrupted hospital data. Stopping load." << endl;
                break;
            }
            hospitals.push_back(h);
        }
        
        // Load blood packets
        getline(inFile, line);
        if (!(inFile >> size)) { goto cleanup; }
        inFile.ignore(1000, '\n');
        
        for (size_t i = 0; i < size; ++i) {
            BloodPacket b;
            if (!(inFile >> b.bloodtype >> b.rhesius >> b.expiryYear >> b.isAvailable)) {
                cerr << "Error: Corrupted blood packet data. Stopping load." << endl;
                break;
            }
            bloodInventory.push_back(b);
        }
        
        cleanup:
        inFile.clear();
        inFile.ignore(10000, '\n');

        while (getline(inFile, line)) {
            if (line == "--- IDS ---") {
                if (inFile >> nextDonorID >> nextHospitalID) {
                    cout << "ID counters restored. Next DonorID: " << nextDonorID << ", Next HospitalID: " << nextHospitalID << endl;
                } else {
                    cout << "Failed to load ID counters. Using default values." << endl;
                    nextDonorID = 1;
                    nextHospitalID = 1;
                }
                break;
            }
        }
        
        cout << "Data loaded successfully from " << DATA_FILE << "!" << endl;
    }
};

//--------------------------------------------------------------------------------
// MAIN FUNCTION
//--------------------------------------------------------------------------------
int main() {
    cout << "Blood Bank Management System" << endl;
    cout << "----------------------------" << endl;

    BloodBank b(123, 123);
    b.loadData();

    int count = 0;
    while (count < 3) {
        if (b.authenticate()) {
            cout << "\nAuthentication successful!" << endl;
            break;
        } else {
            cout << "Authentication failed. Attempts remaining: " << 2 - count << endl;
            count++;
        }
    }

    if (count == 3) {
        cout << "Invalid access attempted beyond 3 times, exiting the system." << endl;
        return 1;
    }

    int ch;
    while (true) {
        cout << "\nWelcome to Blood Bank Management System" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "\n Enter choice : \n 1) Add donor \n 2) Update donor \n 3) Add hospital \n 4) Donate blood \n 5) Request blood \n 6) Show blood bank details \n 7) Exit\n" << endl;
        cout << "Your choice: ";
        
        if (!(cin >> ch)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (ch) {
            case 1:
                b.registerDonor();
                b.saveData(); 
                break;
            case 2:
                b.updateDonor();
                b.saveData();
                break;
            case 3:
                b.registerHospital();
                b.saveData();
                break;
            case 4:
                b.donateBlood();
                b.saveData(); 
                break;
            case 5:
                b.requestBlood();
                b.saveData(); 
                break;
            case 6:
                b.showDetails();
                break;
            case 7:
                b.saveData();
                exit(0);
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }
    return 0;
}