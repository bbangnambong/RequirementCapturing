// 헤더 선언
#include <fstream>
#include <iostream>
#include <string>
#include <vector>



// 상수 선언
#define MAX_STRING 32
#define MAX_MEMBER 10
#define MAX_CLOTHING 100
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

using namespace std;

// 함수 선언
void doTask();
void join();
void createNewClothingHelper();
void showSellingsHelper();
void showSoldoutsHelper();
void program_exit();
void showSellingSumHelper();
void soldoutSellingsHelper();
void deleteID();
void login();
void logout();

int clothingNum = 0;

// 멤버 클래스
class MemberInfo {
   private:
    string name;
    string securityNumber;
    string id;
    string password;
    vector<int> sellingClothings;
    vector<int> soldoutClothings;
    vector<int> purchasedClothings;

   public:
    MemberInfo(string name_, string ssn, string id_, string password_) {
        name = name_;
        securityNumber = ssn;
        id = id_;
        password = password_;
    }
    string getName() {
        return name;
    }
    string getSecurityNumber() {
        return securityNumber;
    }
    string getID() {
        return id;
    }
    string getPassword() {
        return password;
    }
    void addNewClothing(string clothingName, string manufacturer, int price, int stock);
    void addPurchasedClothing(int index) {
        purchasedClothings.push_back(index);  // 구매한 의류 인덱스 저장
    }
    vector<int> listSellingClothings() {
        return sellingClothings;
    }
    vector<int> listSoldoutClothings() {
        return soldoutClothings;
    }
    vector<int> listPurchasedClothings() {
        return purchasedClothings;
    }
    vector<int> listAllClothings() {
        vector<int> allList;
        allList = sellingClothings;
        copy(soldoutClothings.begin(), soldoutClothings.end(), back_inserter(allList));
        return allList;
    };

    // void setUserInfo(string n, string s, string i, string p) {
    //     name = n;
    //     securityNumber = s;
    //     id = i;
    //     password = p;
    // };

    bool checkID(string i, string p) {
        if (i == id && p == password)
            return true;
        else
            return false;
    }
    void disable() {
        password = "----";
        id = "----";
    }
    void soldoutClothing(int index) {
        soldoutClothings.push_back(index);
        for (int i = 0; i < sellingClothings.size(); i++) {
            if (index == sellingClothings[i]) {
                sellingClothings.erase(sellingClothings.begin() + i);
                break;
            }
        }
    }
};

MemberInfo *currentMember = NULL;

// 의류 클래스
class Clothing {
   protected:
    string name;
    string manufacturer;
    int price;
    string sellerID;
    int stock;
    int soldNum;
    int sumOfRating;  // 구매 만족도의 합
    float avgRate;
    int numOfRating; // 상품 평가 횟수

   public:
    Clothing() {
        name = "----";
        manufacturer = "----";
        price = -1;
        sellerID = "----";
        avgRate = 0.0;
        stock = -1;
        soldNum = 0;
        sumOfRating = 0;
        numOfRating = 0;
    };
    Clothing(string name_, string manufacturer_, int price_, int stock_) {
        name = name_;
        manufacturer = manufacturer_;
        price = price_;
        sellerID = currentMember->getID();
        avgRate = 0.0;
        stock = stock_;
        soldNum = 0;
        sumOfRating = 0;
        numOfRating = 0;
    }
    
    string getClothingDetails() {
        return name + " " + manufacturer + " " + to_string(price) + " " + to_string(stock);
    };
    string clothingDetailsToUser() {  // 4.1, 4.3을 위한 함수
        return getSellerID() + " " + getName() + " " + getManufacturer() + " " + to_string(getPrice()) + " " + to_string(getStock()) + " " + to_string(getAvgRate()).substr(0, 3) + '\n';
    }

    void setSumOfRating(int rating) {
        sumOfRating += rating;
        numOfRating++;
        avgRate = sumOfRating / numOfRating;
    }
    string getSellerID() {
        return sellerID;
    }
    string getName() {
        return name;
    };
    string getManufacturer() {
        return manufacturer;
    };
    int getPrice() {
        return price;
    };
    float getAvgRate() {
        return avgRate;
    };
    int getStock() {
        return stock;
    }
    int getSoldNum() {
        return soldNum;
    }
    void sold() {
        stock--;
        soldNum++;
    }
    string getSoldoutDetails() {
        return name + " " + manufacturer + " " + to_string(price) + " " + to_string(soldNum) + " " + to_string(avgRate).substr(0, 3);
    }
} clothingList[MAX_CLOTHING];

// 판매중 의류 클래스
// class SellingClothing : public Clothing {
//    private:
//    public:
//     SellingClothing(string name_, string manufacturer_, int price_, int stock_) {
//         name = name_;
//         manufacturer = manufacturer_;
//         price = price_;
//         sellerID = currentMember->getID();
//         avgRate = 0.0;
//         stock = stock_;
//         soldNum = 0;
//         sumOfRating = 0;
//         numOfRating = 0;
//     }
//     string getClothingDetails() {
//         string listString = name + " " + manufacturer + " " + to_string(price) + " " + to_string(stock);
//         return listString;
//     };

//     void clothingDetailsToUser() {  // 4.1, 4.3을 위한 함수
//         cout << getSellerID() << " " << getName() << " " << getManufacturer() << " " << getPrice() << " " << getStock() << " " << getAvgRate() << '\n';
//     }
// };

// //판매완료 의류 클래스
// class SoldoutClothing : public Clothing {
//    private:
//    public:
//     SoldoutClothing(SellingClothing *sc) {  //판매할 때 stock이 0이 되면 이런식으로 생성해고 원래 있던 selling은 소멸
//         name = sc->getName();
//         manufacturer = sc->getManufacturer();
//         price = sc->getPrice();
//         sellerID = sc->getSellerID();
//         avgRate = sc->getAvgRate();
//     }
//     string getClothingDetails() {
//         string listString = name + " " + manufacturer + " " + to_string(price) + " " + to_string(stock) + " " + to_string(avgRate);
//         return listString;
//     };
// };

void MemberInfo::addNewClothing(string clothingName, string manufacturer, int price, int stock) {
    clothingList[clothingNum] = Clothing(clothingName, manufacturer, price, stock);
    sellingClothings.push_back(clothingNum++);
}

// 구매한 의류 클래스
// class PurchasedClothing:public Clothing{
//     int sumOfRating=0; // 구매 만족도의 합
// public:
//     PurchasedClothing(int index){
//         Clothing purchasedclothing[index]=clothingList[i];
//     }
//     void showClothing(){

//     }
//     void satisfactionAssessment(int rate){
//         sumOfRating++;
//         avgRate=sumOfRating/numOfSelling;
//     }
// }

// 변수 선언
ifstream in_fp;
ofstream out_fp;
vector<MemberInfo> memberList;
int memberCount = 0;
string goodsName = "";

int memberNum = 0;
string clothingName;
int search_index = 0;  // 검색 결과 인덱스 저장

// 1.1. 회원가입
class SignUp {
   public:
    static void signUp(string name, string SSN, string ID, string password) {
        MemberInfo tempMember = MemberInfo(name, SSN, ID, password);
        memberList.push_back(tempMember);
        memberCount++;
    }
};

// 1.2. 회원탈퇴
class DeleteID {
   public:
    static void deleteId() {
        currentMember->disable();
        currentMember = NULL;
        memberCount--;
    }
};

// 2.1. 로그인
class LogIn {
   public:
    static void logIn(string ID, string password) {
        int i = 0;
        while (true) {
            if (i == memberList.size()) {
                out_fp << "2.1 로그인\n";
                out_fp << "로그인 실패\n";
                break;
            }
            if (memberList[i].checkID(ID, password)) {
                out_fp << "2.1. 로그인\n";
                out_fp << memberList[i].getID() << " " << memberList[i].getPassword() << "\n";
                currentMember = &memberList[i];
                break;
            }
            i++;
        }
    }
};

// 2.2. 로그아웃
class LogOut {
   public:
    static void logOut() {
        currentMember = NULL;
    }
};

// 3.1. 의류 등록 UI와 Controller
class AddClothing {
   public:
    static void addNewClothing(string name, string manufacturer, int price, int stock) {
        currentMember->addNewClothing(name, manufacturer, price, stock);
    }
};
class AddClothingUI {
   public:
    static void createNewClothing(string name, string manufacturer, int price, int stock) {
        AddClothing::addNewClothing(name, manufacturer, price, stock);
    }
};

// 3.2. 판매중 의류 조회 UI와 Controller
// class ShowSellingsUI {
//    public:
//     static void startInterface();//오류로 인한 주석처리
// };
class ShowSellings {
   public:
    static string showSellings() {
        vector<int> sellingsList = currentMember->listSellingClothings();
        string listString = "";
        for (int i = 0; i < sellingsList.size(); i++) {
            listString += clothingList[sellingsList[i]].getClothingDetails() + "\n";
        }
        // ShowSellingsUI::startInterface();//오류로 인한 주석처리
        return listString;
    }
};

// 3.3. 판매 완료 의류 조회 UI와 Controller
// class ShowSoldoutsUI {
//    public:
//     static void startInterface();//오류로 인한 주석처리
// };
class ShowSoldouts {
   public:
    static string showSoldouts() {
        vector<int> soldoutsList = currentMember->listSoldoutClothings();
        string listString = "";
        for (int i = 0; i < soldoutsList.size(); i++) {
            listString += clothingList[soldoutsList[i]].getSoldoutDetails() + "\n";
        }
        // ShowSoldoutsUI::startInterface();
        return listString;
    }
};

// 4.1. 상품 정보 검색, 4.2. 상품 구매
// 의류를 검색하고 구매할 수 있는 클래스

class SearchAndPurchaseClothingUI {
   public:
    static string startInterface() {
        in_fp >> goodsName;
        return goodsName;
    };
};
class SearchAndPurchaseClothing {
   public:
    // static void requestInterface() {
    //     string name;
    //     name = SearchAndPurchaseClothingUI::startInterface();//오류로 인한 주석처리
    // }
    static void searchClothing() {  // 검색을 하면 그 인덱스를 저장하여 구매할때 사용
        out_fp << "4.1. 상품 정보 검색\n";
        string name;
        name = SearchAndPurchaseClothingUI::startInterface();
        int size = clothingNum;
        for (int i = 0; i < size; i++) {
            if (name == clothingList[i].getName()) {
                out_fp << clothingList[i].clothingDetailsToUser();
                search_index = i;
            }
        }
    }
    static void purchaseClothing() {
        string sellerID = clothingList[search_index].getSellerID();
        out_fp << "4.2. 상품 구매" << '\n';
        out_fp << sellerID << " " << clothingList[search_index].getName() << "\n";
        currentMember->addPurchasedClothing(search_index);
        clothingList[search_index].sold();
        if (clothingList[search_index].getStock() == 0) {
            for (int i = 0; i < memberList.size(); i++) {
                if (memberList[i].getID() == sellerID) {
                    memberList[i].soldoutClothing(search_index);
                    break;
                }
            }
        }
    }
};

// 4.3. 상품 구매 내역 조회, 4.4. 상품 구매만족도 평가
class ShowPurchaseHistroyUI {
   public:
    static string name, rating;
    // static void startInterface() {//오류로 인한 주석처리
    // }
    static string getGoodsName() {
        string name;
        in_fp >> name;
        return name;
    }
    static string getRating() {
        string rating;
        in_fp >> rating;
        return rating;
    }
};
class ShowPurchaseHistroy {
   public:
    static void showPurchasedClothings() {
        out_fp << "4.3. 상품 구매 내역 조회" << '\n';
        vector<int> purchasedClothingsList = currentMember->listPurchasedClothings();
        // cout << purchasedClothingsList.size() << endl;
        for (int i = 0; i < purchasedClothingsList.size(); i++) {
            int idx = purchasedClothingsList[i];                  // 구매한 의류의 인덱스를 가져와서
            out_fp << clothingList[idx].clothingDetailsToUser();  // 출력한다.
            break;
        }
    }
    static void satisfactionAssessment() {
        string goodsName, goodsRating;
        out_fp << "4.4. 상품 구매만족도 평가" << '\n';
        goodsName = ShowPurchaseHistroyUI::getGoodsName();
        goodsRating = ShowPurchaseHistroyUI::getRating();
        int size = clothingNum;  // 상품 찾기
        for (int i = 0; i < size; i++) {
            if (goodsName == clothingList[i].getName()) {
                clothingList[i].setSumOfRating(stoi(goodsRating));  // 구매만족도 더함, 평균 변경함
                out_fp << clothingList[i].getSellerID() << " " << goodsName << " " << to_string(clothingList[i].getAvgRate()).substr(0, 3) << '\n';
                break;
            }
        }
    }
};
// 5.1. 판매 상품 통계 조회 UI와 Controller
// class ShowSellingSumUI {
//    public:
//     static void startInterface();//오류로 인한 주석처리
// };
class ShowSellingSum {
   public:
    static string showSellingSum() {
        vector<int> sellingSumList = currentMember->listAllClothings();
        string listString = "";
        for (int i = 0; i < sellingSumList.size(); i++) {
            if (clothingList[sellingSumList[i]].getSoldNum() == 0) continue;
            string name = clothingList[sellingSumList[i]].getName();
            int price = clothingList[sellingSumList[i]].getPrice() * clothingList[sellingSumList[i]].getSoldNum();
            float avgRate = clothingList[sellingSumList[i]].getAvgRate();
            listString += name + " " + to_string(price) + " " + to_string(avgRate).substr(0, 3) + "\n";
        }
        // ShowSellingSumUI::startInterface();
        return listString;
    }
};
// main
int main() {
    // 파일 입출력을 위한 초기화
    in_fp.open(INPUT_FILE_NAME);
    out_fp.open(OUTPUT_FILE_NAME);
    doTask();
    return 0;
}

void doTask() {
    // 메뉴 파싱을 위한 level 구분을 위한 변수
    int menu_level_1 = 0, menu_level_2 = 0;
    int is_program_exit = 0;

    while (!is_program_exit) {
        // 입력파일에서 메뉴 숫자 2개를 읽기
        in_fp >> menu_level_1 >> menu_level_2;
        // 메뉴 구분 및 해당 연산 수행
        switch (menu_level_1) {
            case 1: {
                switch (menu_level_2) {
                    case 1:  // "1.1. 회원가입“ 메뉴 부분
                    {
                        // join() 함수에서 해당 기능 수행
                        join();

                        break;
                    }
                    case 2: {
                        deleteID();
                        break;
                    }
                }
                break;
            }
            case 2: {
                switch (menu_level_2) {
                    case 1: {
                        login();
                        break;
                    }
                    case 2: {
                        logout();
                        break;
                    }
                }
                break;
            }

            case 3: {
                switch (menu_level_2) {
                    case 1:  // "3.1. 판매 의류 등록“ 메뉴 부분
                    {
                        createNewClothingHelper();
                        break;
                    }
                    case 2: {
                        showSellingsHelper();
                        break;
                    }
                    case 3: {
                        soldoutSellingsHelper();
                        break;
                    }
                }
                break;
            }
            case 4: {
                switch (menu_level_2) {
                    case 1: {
                        SearchAndPurchaseClothing::searchClothing();
                        break;
                    }
                    case 2: {
                        SearchAndPurchaseClothing::purchaseClothing();
                        break;
                    }
                    case 3: {
                        ShowPurchaseHistroy::showPurchasedClothings();
                        break;
                    }
                    case 4: {
                        ShowPurchaseHistroy::satisfactionAssessment();
                        break;
                    }
                }
                break;
            }
            case 5: {
                switch (menu_level_2) {
                    case 1: {
                        showSellingSumHelper();
                        break;
                    }
                }
            }
            case 6: {
                switch (menu_level_2) {
                    case 1:  // "6.1. 종료“ 메뉴 부분
                    {
                        program_exit();
                        is_program_exit = 1;
                        break;
                    }
                }
                break;
            }
        }
    }
    return;
}

// 1.1 회원가입
void join() {
    string name, SSN, ID, password;

    // 입력 형식 : 이름, 주민번호, ID, Password를 파일로부터 읽음
    in_fp >> name >> SSN >> ID >> password;

    // 해당 기능 수행
    if (memberCount < MAX_MEMBER) {
        // currentMember->setUserInfo(name, SSN, ID, password);
        SignUp::signUp(name, SSN, ID, password);
        out_fp << "1.1. 회원가입\n";
        out_fp << name << " " << SSN << " " << ID << " " << password << "\n";
    } else {
        out_fp << "1.1. 회원가입\n";
        out_fp << "회원가입불가\n";
    }
}

// 1.2 회원탈퇴
void deleteID() {
    DeleteID::deleteId();
    out_fp << "1.2 회원탈퇴\n";
    out_fp << currentMember->getID() << "\n", currentMember->getID();
}

// 2.1 로그인
void login() {
    string ID, password;
    in_fp >> ID >> password;
    // vector<MemberInfo>::iterator iter = memberList.begin();
    LogIn::logIn(ID, password);
}
// 2.2 로그아웃
void logout() {
    out_fp << "2.2 로그아웃\n";
    out_fp << currentMember->getID() << "\n";
    LogOut::logOut();
}

// 3.1. 의류 등록
void createNewClothingHelper() {
    string name, manufacturer;
    int price, stock;
    // 입력
    in_fp >> name >> manufacturer >> price >> stock;
    // 현재 멤버의 selling list에 의류 등록
    AddClothingUI::createNewClothing(name, manufacturer, price, stock);
    // 출력
    out_fp << "3.1. 판매 의류 등록\n"
           << name << " " << manufacturer << " " << price << " " << stock << "\n";
}

// 3.2. 판매중 의류 조회
void showSellingsHelper() {
    string sellingList = ShowSellings::showSellings();
    out_fp << "3.2. 등록 상품 조회\n"
           << sellingList;
}

// 3.3. 판매완료 의류 조회
void soldoutSellingsHelper() {
    string soldoutList = ShowSoldouts::showSoldouts();
    out_fp << "3.3. 판매 완료 상품 조회\n"
           << soldoutList;
}
// 4.1. 상품 정보 검색
// void searchClotingHelper() {
//     // string goodsname;
//     // in_fp >> goodsname;
//     SearchAndPurchaseClothingUI::startInterface();
// }
// 5.1. 판매 상품 통계
void showSellingSumHelper() {
    string sumList = ShowSellingSum::showSellingSum();
    out_fp << "5.1. 판매 상품 통계\n"
           << sumList;
}
void program_exit() {
}