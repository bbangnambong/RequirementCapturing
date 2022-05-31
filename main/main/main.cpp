// 헤더 선언
#include <iostream>
#include <fstream>
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

// 의류 클래스
class Clothing{
private:
  string name;
  string manufacturer;
  int price;
  string sellerID;
  float avgRate;
  int stock;
  int soldNum;
public :
  string getClothingDetails();
  string clothingDetailsToUser();
  string getSellerID(){
    return sellerID;
    }
  string getName(){
    return name;
  };
  string getManufacturer(){
    return manufacturer;
  };
  int getPrice(){
    return price;
  };
  string getSellerID(){
    return sellerID;
  };
  float getAvgRate(){
    return avgRate;
  };
  int getStock(){
    return stock;
  }
  int getSoldNum(){
    return soldNum;
  }
}clothingList[MAX_CLOTHING];

int clothingNum = 0;

// 판매중 의류 클래스
class SellingClothing : public Clothing{
private:
public:
  SellingClothing(string name_, string manufacturer_, int price_, int stock_){
    name = name_;
    manufacturer = manufacturer_;
    price = price_;
    sellerID = currentMember->getID();
    avgRate = 0.0;
    stock = stock_;
    soldNum = 0;
  }
  string getClothingDetails(){
    string listString = name + " " + manufacturer + " " + to_string(price) + " " + to_string(stock);
    return listString;
  };
    string clothingDetailsToUser(){ // 4.1.을 위한 함수
        string listString = getSellerID() +" "+getName() + " " + getManufacturer() + " " + getPrice() + " " + getStock()+" "+getAvgRate();
        return listString;
    }
};

//판매완료 의류 클래스
class SoldoutClothing : public Clothing{
private:
public:
  SoldoutClothing(SellingClothing *sc){//판매할 때 stock이 0이 되면 이런식으로 생성해고 원래 있던 selling은 소멸
    name = sc->getName();
    manufacturer = sc->getManufacturer();
    price = sc->getPrice();;
    sellerID = sc->getSellerID();
    avgRate = sc->getAvgRate();
  }
  string getClothingDetails(){
    string listString = name + " " + manufacturer + " " + to_string(price) + " " + to_string(stock) + " " + to_string(avgRate);
    return listString;
  };
};

// 멤버 클래스
class MemberInfo{
private:
  string name;
  string securityNumber;
  string id;
  string password;
  vector<int> sellingClothings;
  vector<int> soldoutClothings;
  vector<int> purchasedClothings;
public:
  string getName(){
    return name;
  };
  string getSecurityNumber(){
    return securityNumber;
  };
  string getID(){
    return id;
  };
  string getPassword(){
    return password;
  };
  void addNewClothing(string clothingName, string manufacturer, int price, int stock){
    clothingList[clothingNum] = SellingClothing(clothingName, manufacturer, price, stock);
    sellingClothings.push_back(clothingNum++);
  };
  vector<SellingClothing> listSellingClothings(){
    return sellingClothings;
  };
  vector<SoldoutClothing> listSoldoutClothings(){
    return soldoutClothings;
  };
  void listPurchasedClothings();
  void listAllClothings(){
    vector<int> allList = sellingClothings;
    allList.insert(allList.end(), soldoutClothings.begin(), soldoutClothings.end());
    return allList;
  };

  void setUserInfo(string n, string s, string i, string p) {
      name = n; securityNumber = s; id = i; password = p;
  };

  bool checkID(string i, string p) {
      if (i == id && p == password)
          return true;
      else
          return false;
  }
};

// 변수 선언
ifstream in_fp;
ofstream out_fp;
MemberInfo members[MAX_MEMBER];
int memberNum = 0;
MemberInfo *currentMember;
string clothingName;
int search_index; // 검색 결과 인덱스 저장
//3.1. 의류 등록 UI와 Controller
class AddClothingUI{
public:
  static void createNewClothing(string clothingName, string manufacturer, int price, int stock){
    AddClothing::addNewClothing(name, manufacturer, price, stock);
  }
};
class AddClothing{
public:
  static void addNewClothing(string clothingName, string manufacturer, int price, int stock){
   currentMember->addNewClothing(name, manufacturer, price, stock);
  }
};

//3.2. 판매중 의류 조회 UI와 Controller
class ShowSellingsUI{
public:
  static void startInterface();
};
class ShowSellings{
  static void showSellings(){
    vector<int> sellingsList = currentMember->listSellingClothings();
    string listString = "";
    for(int i = 0; i < sellingsList.size(); i++){
      listString += clothingList[sellingsList[i]].getClothingDetails() + "\n";
    }
    ShowSellingsUI::startInterface();
    return listString;
  }
};

//3.3. 판매 완료 의류 조회 UI와 Controller
class ShowSoldoutsUI{
public:
  static void startInterface();
};
class ShowSoldouts{
  static void showSellings(){
    vector<int> soldoutsList = currentMember->listSoldoutClothings();
    string listString = "";
    for(int i = 0; i < soldoutsList.size(); i++){
      listString += clothingList[soldoutsList[i]].getClothingDetails() + "\n";
    }
    ShowSoldoutsUI::startInterface();
    return listString;
  }
};

// 4.1. 상품 정보 검색, 4.2. 상품 구매
// 의류 검색하는 control class
class SearchAndPurchaseClothing{
public:
    static void searchClothing(){
        out_fp <<"4.1. 상품 정보 검색";
        int size=sizeof(clothingList)/sizeof(Clothing);
        for(int i=0;i<size;i++){
            if(in_fp==clothingList[i].getName()){
                out_fp<<clothingList[i].clothingDetailsToUser();
                search_index=i;
            }
        }
    }
    static void purchaseClothing(){
        out_fp<<clothingList[search_index].getSellerID()<<" "<<clothingList[search_index].getName();
        currentMember->purchasedClothings.push_back(clothingList[search_index]);
    }
};
// 의류 검색하는 boundary class
class SearchClothingUI{
public:
    static void startInterface(){
        SearchAndPurchaseClothing::searchClothing();
    }
};


// 4.3. 상품 구매 내역 조회, 상품 구매만족도 평가
class ShowPurchaseHistroyUI{
    
};
class ShowPurchaseHistroy{
    
};

//5.1. 판매 상품 통계 조회 UI와 Controller
class ShowSellingSumUI{
public:
  static void startInterface();
};
class ShowSellingSum{
  static void showSellingSum(){
    vector<int> sellingSumList = currentMember->listSoldoutClothings();
    string listString = "";
    for(int i = 0; i < sellingSumList.size(); i++){
      string name = clothingList[sellingSumList[i]].getName();
      int price = clothingList[sellingSumList[i]].getPrice() * clothingList[sellingSumList[i]].getSoldNum;
      float avgRate = clothingList[sellingSumList[i]].getAvgRate();
      listString += name + " " + to_string(price) + " " + to_string(avgRate) + "\n";
    }
    ShowSellingSumUI::startInterface();
    return listString;
  }
};
// main
int main(){
  // 파일 입출력을 위한 초기화
  in_fp.open(INPUT_FILE_NAME);
  out_fp.open(OUTPUT_FILE_NAME);

  doTask();
  return 0;
}

void doTask(){
  // 메뉴 파싱을 위한 level 구분을 위한 변수
  int menu_level_1 = 0, menu_level_2 = 0;
  int is_program_exit = 0;
    
  while(!is_program_exit){
    // 입력파일에서 메뉴 숫자 2개를 읽기
      in_fp >> menu_level_1 >> menu_level_2;
    // 메뉴 구분 및 해당 연산 수행
    switch(menu_level_1)
    {
      case 1:
      {
        switch(menu_level_2)
        {
          case 1:   // "1.1. 회원가입“ 메뉴 부분
          {
          // join() 함수에서 해당 기능 수행 
            join();
       
            break;
          }
          case 2:
          {
             // deleteID();
            break;
          }
        }
      }
      case 2:
      {
          switch (menu_level_2)
          {
            case 1:   
            {
              break;
            }
            case 2:
            {
              break;
            }
          }
      }

      case 3:
      {
        switch(menu_level_2)
        {
          case 1:   // "3.1. 판매 의류 등록“ 메뉴 부분
          {
            createNewClothingHelper();
            break;
          }
          case 2:
          {
            showSellingsHelper();
            break;
          }
          case 3:
          {
            
            break;
          }
        }
      }
      case 4:
      {
          switch(menu_level_2){
              case 1:
              {
                  SearchClothingUI::startInterface();
                  break;
              }
              case 2:{
                  SearchAndPurchaseClothing::purchaseClothing();
              }
          }
      }
      case 5:
      {
          switch(menu_level_2){
              case 1:
              {
                showSellingSumHelper();
                 break; 
              }
          }
      }
      case 6:
      {
        switch(menu_level_2){
          case 1:   // "6.1. 종료“ 메뉴 부분
          {
    
            program_exit();
            is_program_exit = 1;
            break;
          }
        }
      }
    }
  }
  return;
}


//1.1 회원가입
void join(){
  char user_type[MAX_STRING], name[MAX_STRING], SSN[MAX_STRING],
    address[MAX_STRING], ID[MAX_STRING], password[MAX_STRING];

   // 입력 형식 : 이름, 주민번호, ID, Password를 파일로부터 읽음
  fscanf(in_fp, "%s %s %s %s", name, SSN, ID, password);

   // 해당 기능 수행
  currentMember->setUserInfo(name, SSN, ID, password);

   // 출력 형식
  fprintf(out_fp, "1.1. 회원가입\n");
  fprintf(out_fp, "%s %s %s %s\n", name, SSN, ID, password);
}


//1.2 회원탈퇴
void deleteID() {
    delete currentMember;
}

//2.1 로그인
void login() {
    char ID[MAX_STRING], password[MAX_STRING];
    fscanf(in_fp, "%s %s",ID, password);

    if (currentMember->checkID(ID, password)) {

    }

}

//3.1. 의류 등록
void createNewClothingHelper(){
    string name, manufacturer;
    int price, stock;
    // 입력
    in_fp >> name >> manufacturer >> price >> stock;
    // 현재 멤버의 selling list에 의류 등록
    AddClothingUI::createNewClothing(name, manufacturer, price, stock);
    // 출력
    out_fp << "3.1. 판매 의류 등록\n" << name << " " << manufacturer << " " << price << " " << stock << "\n";
}

//3.2. 판매중 의류 조회
void showSellingsHelper(){
    string sellingList = ShowSellings::showSellings();
    out_fp << "3.2. 등록 상품 조회\n" << sellingList;
}

//3.3. 판매완료 의류 조회
void soldoutSellingsHelper(){
    string soldoutList = ShowSoldouts::showSellings();
    out_fp << "3.3. 판매 완료 상품 조회\n" << soldoutList;
}
//4.1. 상품 정보 검색
void searchClotingHelper(){
    string name;
    in_fp >> name;
    SearchClothingUI::startInterface()
}
//5.1. 판매 상품 통계
void showSellingSumHelper(){
    string sumList = ShowSellings::showSellings();
    out_fp << "5.1. 판매 완료 상품 조회\n" << sumList;
}
void program_exit(){
    
}
