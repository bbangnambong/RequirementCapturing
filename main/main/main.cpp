// 헤더 선언
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// 상수 선언
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

using namespace std;

// 함수 선언
void doTask();
void join();
void program_exit();

// 변수 선언
ifstream in_fp;
ofstream out_fp;
MemberInfo *currentMember;
string clothingName;

// 의류 클래스
class Clothing{
private:
  string name;
  string manufacturer;
  int price;
  int sellerID;
  float avgRate;
public :
  Clothing(string name_, string manufacturer_, int price_, int quantity_){
    name = name_;
    manufacturer = manufacturer_;
    price = price_;
    quantity_ = quantity_;
    sellerID = currentMember->getID();
    avgRate = 0.0;
  }
  string getClothingDetails();
};
// 멤버 클래스
class MemberInfo{
private:
  string name;
  string securityNumber;
  string id;
  string password;
  vector<Clothing> sellingClothings;
  vector<Clothing> soldoutClothings;
  vector<Clothing> purchasedClothings;
  vector<Clothing> soldClothings;
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
  void addNewClothing(string clothingName, string manufacturer, int price, int quantity){
    Clothing clothingTemp = *new Clothing(clothingName, manufacturer, price, quantity);
    sellingClothings.push_back(clothingTemp);
  };
  void listSellingClothings();
  void listSoldoutClothings();
  void listPurchasedClothings();
  void listSoldClothings();

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

// 4.1. 상품 정보 검색, 4.2. 상품 구매
// 의류 검색하는 boundary class
class SearchClothingUI{
public:
    // static string clothingName;
    static void searchClothing(){
        in_fp >> clothingName;
    }
};
// 의류 검색하는 control class
class SearchClothing{
public:
    void showClothing(){
        out_fp <<"4.1. 상품 정보 검색";
    }
};

// 4.3. 상품 구매 내역 조회, 상품 구매만족도 평가
class ShowPurchaseHistroyUI{
    
};
class ShowPurchaseHistroy{
    
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
              // createNewClothing();
            break;
          }
          case 2:
          {
            
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
                    SearchClothingUI::searchClothing();
                    
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

void createNewClothing(){
  string name, manufacturer;
  int price, quantity;
  // 입력
  in_fp >> name >> manufacturer >> price >> quantity;
  // 현재 멤버의 selling list에 의류 등록
  currentMember->addNewClothing(name, manufacturer, price, quantity);
  // 출력
  out_fp << "3.1. 판매 의류 등록\n" << name << " " << manufacturer << " " << price << " " << quantity << "\n";
}

void program_exit(){
    
}
