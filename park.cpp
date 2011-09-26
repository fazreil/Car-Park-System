#include <stdlib.h>
#include <iostream.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <ctime>

/*
using std::cout;
using std::cin;
using std::endl;
 */

struct parkingBay {
    char plateNumber[7];
    time_t inTime;
    bool vip;
    bool authenticated_vip;
    bool occupied;
    int intTime;
};

struct VipClubMember {
    char plateNumber[7];
    char name[10];
};

struct duration {
    int hour;
    int minute;
    int seconds;
};

//function prototype
void initParking();
void initVipCardmember();
void selamatDatang();
int showAvailableParking();
bool parking(bool vip);
void vipParking(char plate[]);
bool fullParking(int bay);
void amParking(char plate[]);
bool limit10MinitReached(time_t);
float payParkingVIP(double i);
float payParkingAM(double i);
float voidPark();
void maintenanceMode();
void printPlateNumber(char plate[]);
void printName(char name[]);
void listParkingSpace();
void paymentMode();
char emptyVip();
duration calculateDuration(double);
bool moreThan10Minute(double);
void displayParkingDuration(duration durr);

//variables
int visitorType;
int const VIP_VISITORTYPE = 1;
int const AM_VISITORTYPE = 2;
int const PAYMENT_MODE = 3;
int const MAINTENANCE = 0;
time_t inTime;
time_t theTime;
char empty_name[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
char empty_plate[7] = {'_', ' ', ' ', ' ', ' ', ' ', ' '};
char currentCarPlateNumber[7];
bool authenticated_guest;
bool vipCarOwner;
VipClubMember memberList[100];
parkingBay bay1[20];
parkingBay bay2[20];
parkingBay bay3[20];
parkingBay bay4[20];
parkingBay bay5[20];
bool run;

void initParking() {

    for (int i = 0; i < 20; i++) {
        bay1[i].occupied = false;
        strcpy(bay1[i].plateNumber, empty_plate);
        bay2[i].occupied = false;
        strcpy(bay2[i].plateNumber, empty_plate);
        bay3[i].occupied = false;
        strcpy(bay3[i].plateNumber, empty_plate);
        bay4[i].occupied = false;
        strcpy(bay4[i].plateNumber, empty_plate);
        bay5[i].occupied = false;
        strcpy(bay5[i].plateNumber, empty_plate);
    }
}

void initVipCardmember() {
    char _name[10] = {' ', 'R', 'A', 'H', 'M', 'A', 'N', ' ', ' ', ' '};
    char _plate[7] = {'P', 'G', 'W', '8', '2', '3', '6'};
    char _name2[10] = {' ', 'Y', 'U', 'S', 'M', 'A', 'N', ' ', ' ', ' '};
    char _plate2[7] = {'P', 'G', 'Y', '9', '9', '9', '9'};

    strcpy(memberList[0].name, _name);
    strcpy(memberList[0].plateNumber, _plate);
    
    strcpy(memberList[1].name, _name2);
    strcpy(memberList[1].plateNumber, _plate2);

    for (int i = 2; i < 100; i++) {
        strcpy(memberList[i].name, empty_name);
        strcpy(memberList[i].plateNumber, empty_plate);
    }


}

int main(int argc, char** argv) {

    initVipCardmember();
    initParking();
    run = true;

    while (run) {
        selamatDatang();
        cin >> visitorType;
        if (visitorType == VIP_VISITORTYPE) {
            if (fullParking(1)) {
                cout << "Maaf, tiada tempat letak kereta";
            } else {
                parking(true);
                if (vipCarOwner) {
                    vipParking(currentCarPlateNumber);
                    cout << "Sila letak kereta di basement 1" << endl;
                }
            }
        } else if (visitorType == AM_VISITORTYPE) {
            parking(false);
            amParking(currentCarPlateNumber);
            cout << "Sila letak kereta di basement 2, 3, 4 atau 5" << endl;
        } else if (visitorType == PAYMENT_MODE) {
            cout << "mod bayaran" << endl;
            paymentMode();
        } else if (visitorType == MAINTENANCE) {
            maintenanceMode();
        }
        cout << "#######TERIMA KASIH#######" << endl << endl;
    }
    return (EXIT_SUCCESS);
}

void selamatDatang() {
    time(&theTime);
    cout << "Selamat Datang " << endl << ctime(&theTime) << endl;
    cout << "Masih terdapat " << showAvailableParking() << " petak kosong" << endl;
    cout << "Pilihan tempat letak kereta anda:" << endl;
    cout << "1: VIP" << endl;
    cout << "2: AM" << endl;
    cout << "3: MOD BAYARAN" << endl;
}

int showAvailableParking() {
    int emptySpaces = 0;
    for (int i = 0; i < 20; i++) {
        if (bay1[i].occupied == false) emptySpaces = emptySpaces + 1;
        if (bay2[i].occupied == false) emptySpaces = emptySpaces + 1;
        if (bay3[i].occupied == false) emptySpaces = emptySpaces + 1;
        if (bay4[i].occupied == false) emptySpaces = emptySpaces + 1;
        if (bay5[i].occupied == false) emptySpaces = emptySpaces + 1;
    }
    return emptySpaces;
}

void vipParking(char plate[]) {
    time_t currTime;
    //look for empty bay
    for (int i = 0; i < 20; i++) {
        if (bay1[i].occupied == false) {
            bay1[i].authenticated_vip = authenticated_guest;
            bay1[i].inTime = time(&currTime);
            bay1[i].occupied = true;
            strcpy(bay1[i].plateNumber, plate);
            bay1[i].vip = true;

            cout << "intime ";
            time(&bay1[i].inTime);
            cout << ctime(&bay1[i].inTime);
            i = 20;
        }
    }
}

void amParking(char plate[]) {
    //LOOK FOR EMPTY SPACE IN BAY 2,3,4,5
    bool parked = false;
    if (parked == false) {
        for (int i = 0; i < 20; i++) {
            if (bay2[i].occupied == false) {
                bay2[i].authenticated_vip = authenticated_guest;
                bay2[i].inTime = time(&theTime);
                bay2[i].occupied = true;
                strcpy(bay2[i].plateNumber, plate);
                bay2[i].vip = true;

                cout << "intime" << endl;
                cout << ctime(&bay2[i].inTime);
                i = 20;
                parked = true;
            }
        }
    }
    if (parked == false) {
        for (int j = 0; j < 20; j++) {
            if (bay3[j].occupied == false) {
                bay3[j].authenticated_vip = authenticated_guest;
                bay3[j].inTime = time(&theTime);
                bay3[j].occupied = true;
                strcpy(bay3[j].plateNumber, plate);
                bay3[j].vip = true;

                cout << "intime" << endl;
                cout << ctime(&bay3[j].inTime);
                j = 20;
                parked = true;
            }
        }
    }
    if (parked == false) {
        for (int k = 0; k < 20; k++) {
            if (bay4[k].occupied == false) {
                bay4[k].authenticated_vip = authenticated_guest;
                bay4[k].inTime = time(&theTime);
                bay4[k].occupied = true;
                strcpy(bay4[k].plateNumber, plate);
                bay4[k].vip = true;

                cout << "intime" << endl;
                cout << ctime(&bay4[k].inTime);
                k = 20;
                parked = true;
            }
        }
    }
    if (parked == false) {
        for (int l = 0; l < 20; l++) {
            if (bay5[l].occupied == false) {
                bay5[l].authenticated_vip = authenticated_guest;
                bay5[l].inTime = time(&theTime);
                bay5[l].occupied = true;
                strcpy(bay5[l].plateNumber, plate);
                bay5[l].vip = true;

                cout << "intime" << endl;
                cout << ctime(&bay5[l].inTime);
                l = 20;
                parked = true;
            }
        }
    }
}

bool parking(bool vip) {
    char car_plateNumber[7];
    char input;
    int cmpResult = -1;
    bool authenticatedVip = false;
    vipCarOwner = vip;
    cout << "Sila masukkan plat kereta anda" << endl;
    for (int i = 0; i < 7; i++) {
        cin >> input;
        car_plateNumber[i] = input;
    }
    strcpy(currentCarPlateNumber, car_plateNumber);
    if (vip) {
        for (int j = 0; j < 100; j++) {
            if (memberList[j].plateNumber[0] != '_') {
                cmpResult = strcmp(car_plateNumber, memberList[j].plateNumber);
                if (cmpResult == 0) {
                    cout << "Selamat datang: ";
                    printName(memberList[j].name);
                    cout << endl;
                    authenticatedVip = true;
                }
            }
        }
    }
    if (vipCarOwner) {
        if (authenticatedVip == true) {
            return true;
        } else {
            cout << "ANDA TIDAK DIBENARKAN PARKING DISINI HANYA VIP SAHAJA" << endl;
            vipCarOwner = false;
            return false;
        }
    }
}

void maintenanceMode() {
    char shutdown;
    int confirm = 0;
    while (confirm == 0) {
        cout << "Nyah aktif sistem letak kereta? (y/t)";
        cin >> shutdown;
        if (shutdown == 'y') {
            run = false;
        } else if (shutdown == 't') {
            run = true;
        } else if (shutdown == '?') {
            listParkingSpace();
        }
        confirm = (shutdown == 'y')+(shutdown == 't');
    }
}

void printPlateNumber(char plate[]) {
    for (int i = 0; i < 7; i++) {
        cout << plate[i];
    }
}

void printName(char name[]) {
    for (int i = 0; i < 10; i++) {
        cout << name[i];
    }
    cout << endl;
}

bool fullParking(int bayNumber) {
    int emptyParking = 0;
    if (bayNumber == 1) {
        for (int i = 0; i < 20; i++) {
            if (bay1[i].occupied == true) {
                emptyParking = emptyParking + 1;
            }
        }
        if (emptyParking == 20) {
            return true;
        } else return false;
    }
}

void listParkingSpace() {
    for (int i = 0; i < 20; i++) {
        cout << "bay 1 - " << i << ": ";
        printPlateNumber(bay1[i].plateNumber);
        cout << "\t " << ctime(&bay1[i].inTime);
        cout << endl;
    }
    for (int j = 0; j < 20; j++) {
        cout << "bay 2 - " << j << ": ";
        printPlateNumber(bay2[j].plateNumber);
        cout << "\t " << ctime(&bay2[j].inTime);
        cout << endl;
    }
    for (int k = 0; k < 20; k++) {
        cout << "bay 3 - " << k << ": ";
        printPlateNumber(bay3[k].plateNumber);
        cout << "\t " << ctime(&bay3[k].inTime);
        cout << endl;
    }
    for (int l = 0; l < 20; l++) {
        cout << "bay 4 - " << l << ": ";
        printPlateNumber(bay4[l].plateNumber);
        cout << "\t " << ctime(&bay4[l].inTime);
        cout << endl;
    }
    for (int m = 0; m < 20; m++) {
        cout << "bay 5 - " << m << ": ";
        printPlateNumber(bay5[m].plateNumber);
        cout << "\t " << ctime(&bay5[m].inTime);
        cout << endl;
    }
}

void paymentMode() {
    char car_plateNumber[7];
    char input;
    int samePlateNumber;
    time_t currentTime;
    float charge;
    cout << "Sila masukkan plat kereta anda untuk bayaran" << endl;
    for (int i = 0; i < 7; i++) {
        cin >> input;
        car_plateNumber[i] = input;
    }

    cout << "%%%%%%%%Sila bayar%%%%%%%%%%%" << endl;
    //search car in bay1
    for (int j = 0; j < 20; j++) {
        samePlateNumber = strcmp(car_plateNumber, bay1[j].plateNumber);
        //cout << "strcmp(car_plateNumber, bay1[i].plateNumber);\t" << samePlateNumber << endl;
        if (samePlateNumber == 0) {
            cout << "%%%%%%%%VIP PARKING%%%%%%%%" << endl;
            charge = payParkingVIP(difftime(time(&currentTime), bay1[j].inTime));

            bay1[j].occupied = false;
            strcpy(bay1[j].plateNumber, empty_plate);
            j = 20;
        }
    }

    if (samePlateNumber != 0) {
        for (int k = 0; k < 20; k++) {
            samePlateNumber = strcmp(car_plateNumber, bay2[k].plateNumber);
            //cout << "strcmp(car_plateNumber, bay2[i].plateNumber);\t" << samePlateNumber << endl;
            if (samePlateNumber == 0) {
                cout << "%%%%%%%%AM  PARKING%%%%%%%%" << endl;
                charge = payParkingAM(difftime(time(&currentTime), bay2[k].inTime));

                bay2[k].occupied = false;
                strcpy(bay2[k].plateNumber, empty_plate);
                k = 20;
            }
        }
    }
    if (samePlateNumber != 0) {
        for (int l = 0; l < 20; l++) {
            samePlateNumber = strcmp(car_plateNumber, bay3[l].plateNumber);
            //cout << "strcmp(car_plateNumber, bay3[i].plateNumber);\t" << samePlateNumber << endl;
            if (samePlateNumber == 0) {
                cout << "%%%%%%%%AM  PARKING%%%%%%%%" << endl;
                charge = payParkingAM(difftime(time(&currentTime), bay3[l].inTime));

                bay3[l].occupied = false;
                strcpy(bay3[l].plateNumber, empty_plate);
                l = 20;
            }
        }
    }
    if (samePlateNumber != 0) {
        for (int m = 0; m < 20; m++) {
            samePlateNumber = strcmp(car_plateNumber, bay4[m].plateNumber);
            //cout << "strcmp(car_plateNumber, bay4[i].plateNumber);\t" << samePlateNumber << endl;
            if (samePlateNumber == 0) {
                cout << "%%%%%%%%AM  PARKING%%%%%%%%" << endl;
                charge = payParkingAM(difftime(time(&currentTime), bay4[m].inTime));

                bay4[m].occupied = false;
                strcpy(bay4[m].plateNumber, empty_plate);
                m = 20;
            }
        }
    }
    if (samePlateNumber != 0) {
        for (int n = 0; n < 20; n++) {
            samePlateNumber = strcmp(car_plateNumber, bay5[n].plateNumber);
            //cout << "strcmp(car_plateNumber, bay5[i].plateNumber);\t" << samePlateNumber << endl;
            if (samePlateNumber == 0) {
                cout << "%%%%%%%%AM  PARKING%%%%%%%%" << endl;
                charge = payParkingAM(difftime(time(&currentTime), bay5[n].inTime));

                bay5[n].occupied = false;
                strcpy(bay5[n].plateNumber, empty_plate);
                n = 20;
            }
        }
    }


    cout << "bayaran: " << charge << endl;
}

float payParkingVIP(double i) {
    float firstHour = 8;
    float subHour = 4;

    if (moreThan10Minute(i)) {
        return 0;
    }
    duration tempohLetakKenderaan = calculateDuration(i);
    displayParkingDuration(tempohLetakKenderaan);
    float bayaran = firstHour;
    tempohLetakKenderaan.hour = tempohLetakKenderaan.hour - 1;
    if (tempohLetakKenderaan.hour > 0) {
        bayaran = bayaran + (tempohLetakKenderaan.hour * subHour);
    }
    if (tempohLetakKenderaan.minute + tempohLetakKenderaan.seconds > 0) {
        bayaran = bayaran + subHour;
    }
    cout << "total: " << bayaran << endl;
    return bayaran;
}

float payParkingAM(double i) {
    float firstHour = 4;
    float subHour = 2;

    if (moreThan10Minute(i)) {
        return 0;
    }
    duration tempohLetakKenderaan = calculateDuration(i);
    displayParkingDuration(tempohLetakKenderaan);
    float bayaran = firstHour;
    tempohLetakKenderaan.hour = tempohLetakKenderaan.hour - 1;
    if (tempohLetakKenderaan.hour > 0) {
        bayaran = bayaran + (tempohLetakKenderaan.hour * subHour);
    }
    if (tempohLetakKenderaan.minute + tempohLetakKenderaan.seconds > 0) {
        bayaran = bayaran + subHour;
    }
    cout << "total:" << bayaran << endl;
    return bayaran;
}

char emptyVip() {
    for (int i = 0; i < 20; i++) {
        if (bay1[i].occupied == false)
            return 'A' + i - 1;
    }
}

duration calculateDuration(double totalSecs) {
    duration theDuration;
    theDuration.hour = theDuration.minute = theDuration.seconds = 0;
    cout << "total secs " << totalSecs << endl;
    if (totalSecs > 3600) {
        theDuration.hour = totalSecs / 3600;
        totalSecs = totalSecs - (theDuration.hour * 3600);
    }
    if (totalSecs > 60) {
        theDuration.minute = totalSecs / 60;
        totalSecs = totalSecs - (theDuration.minute * 60);
    }
    theDuration.seconds = totalSecs;
    return theDuration;
}

bool moreThan10Minute(double i) {
    if (i <= 600) {
        cout << "Masa yg digunakan kurang dari 10 minit, tiada bayaran dikenakan" << endl;
        return true;
    } else
        return false;
}

void displayParkingDuration(duration durr) {
    cout << "%%%%%%%%%%tempoh letak kenderaan:" << endl;
    cout << durr.hour << " jam" << endl;
    cout << durr.minute << " minit" << endl;
    cout << durr.seconds << " saat" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
}


