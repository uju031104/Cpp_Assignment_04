#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe
{
public:
    std::string potionName;
    std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경

    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const std::string &name, const std::vector<std::string> &ingredients)
        : potionName(name), ingredients(ingredients) {}
};

// RecipeManager 클래스: 레시피 목록을 관리
class RecipeManager
{
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string &name, const std::vector<std::string> &ingredients)
    {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    // 레시피 반환
    const std::vector<PotionRecipe> &getAllRecipes() const
    {
        return recipes;
    }

    // 물약 이름으로 검색하는 기능
    std::vector<PotionRecipe> searchRecipeByName(std::string name)
    {
        std::vector<PotionRecipe> result;
        for (auto &rec : recipes)
        {
            if (rec.potionName == name)
            {
                result.push_back(rec);
                return result;
            }
        }
        return result;
    }

    // 특정 재료가 들어간 물약을 검색하는 기능
    std::vector<PotionRecipe> searchRecipeByIngredient(std::string ingredient)
    {
        std::vector<PotionRecipe> result;
        for (auto &rec : recipes)
        {
            for (auto &ing : rec.ingredients)
            {
                if (ing == ingredient)
                {
                    result.push_back(rec);
                    break;
                }
            }
        }
        return result;
    }
};

// StockManager 클래스 : 재고 관리
class StockManager
{
private:
    std::map<std::string, int> PotionStock;
    const int MAX_STOCK = 3;

public:
    void initializeStock(std::string potionName)
    {
        this->PotionStock[potionName] = MAX_STOCK;
    }

    int dispensePotion(std::string potionName)
    {
        auto it = PotionStock.find(potionName);
        if (it != PotionStock.end())
        {
            if (PotionStock[potionName] == 0)
            {
                return -1;
            }
            else
            {
                return --PotionStock[potionName];
            }
        }
        else
        {
            return -2;
        }
    }

    int returnPotion(std::string potionName)
    {
        auto it = PotionStock.find(potionName);
        if (it != PotionStock.end())
        {
            if (PotionStock[potionName] == MAX_STOCK)
            {
                return 0;
            }
            else
            {
                return ++PotionStock[potionName];
            }
        }
        else
        {
            return -1;
        }
    }

    int getStock(std::string potionName)
    {
        return PotionStock[potionName];
    }
};

/************************************************************/
/**************** 레시피를 검색하고 출력하는 함수 ****************/
/************************************************************/
void const print_recipes(RecipeManager &myWorkshop_ref)
{
    if (myWorkshop_ref.getAllRecipes().empty())
    {
        std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
        return;
    }
    int choice;
    std::string str;
    std::vector<PotionRecipe> print_recipe;

    while (true)
    {
        std::cout << "1. 모든 레시피 출력" << std::endl;
        std::cout << "2. 이름으로 검색" << std::endl;
        std::cout << "3. 재료로 검색" << std::endl;
        std::cout << "4. 뒤로가기" << std::endl;
        std::cout << "선택: ";
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1)
        {
            print_recipe = myWorkshop_ref.getAllRecipes();
        }
        else if (choice == 2)
        {
            std::cout << "물약 이름을 입력하세요: " << std::endl;
            std::cin >> str;
            print_recipe = myWorkshop_ref.searchRecipeByName(str);
            if (print_recipe.size() == 0)
            {
                std::cout << str << "이(가) 없습니다." << std::endl;
            }
        }
        else if (choice == 3)
        {
            std::cout << "재료 이름을 입력하세요: " << std::endl;
            std::cin >> str;
            print_recipe = myWorkshop_ref.searchRecipeByIngredient(str);
            if (print_recipe.size() == 0)
            {
                std::cout << str << "이(가) 들어간 물약이 없습니다." << std::endl;
            }
        }
        else if (choice == 4)
        {
            return;
        }
        else
        {
            std::cout << "잘못 입력하셨습니다. 처음 메뉴로 돌아갑니다." << std::endl;
            return;
        }
        std::cout << "\n--- [ 레시피 목록 ] ---" << std::endl;
        for (size_t i = 0; i < print_recipe.size(); ++i)
        {
            std::cout << "- 물약 이름: " << print_recipe[i].potionName << std::endl;
            std::cout << "  > 필요 재료: ";

            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < print_recipe[i].ingredients.size(); ++j)
            {
                std::cout << print_recipe[i].ingredients[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < print_recipe[i].ingredients.size() - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
    }
}

int main()
{
    RecipeManager myWorkshop;
    StockManager myStock;

    while (true)
    {
        std::cout << "⚗️ 연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 레시피 검색" << std::endl;
        std::cout << "3. 물약 주기" << std::endl;
        std::cout << "4. 물약 돌려받기" << std::endl;
        std::cout << "5. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1)
        {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            // 여러 재료를 입력받기 위한 로직
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            myStock.initializeStock(name);

            while (true)
            {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "끝")
                {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty())
            {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else
            {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }
        }
        else if (choice == 2)
        {
            print_recipes(myWorkshop);
        }
        else if (choice == 3)
        {
            std::string name;
            std::cout << "지급할 물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            int num = myStock.dispensePotion(name);

            if (num == -1)
            {
                std::cout << name << "의 재고가 없습니다." << std::endl;
            }
            else if (num == -2)
            {
                std::cout << name << "은(는) 레시피에 없습니다." << std::endl;
            }
            else
            {
                std::cout << name << "이(가) 모험가에게 지급됐습니다." << std::endl;
                std::cout << name << "의 남은 재고: " << num << std::endl;
            }
        }
        else if (choice == 4)
        {
            std::string name;
            std::cout << "반환받을 물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            int num = myStock.returnPotion(name);

            if (num == 0)
            {
                std::cout << name << "이(가) 이미 최대치 입니다." << std::endl;
            }
            else if (num == -1)
            {
                std::cout << name << "은(는) 레시피에 없습니다." << std::endl;
            }
            else
            {
                std::cout << name << "을(를) 모험가로부터 반환 받았습니다." << std::endl;
                std::cout << name << "의 남은 재고: " << num << std::endl;
            }
        }
        else if (choice == 5)
        {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;
        }
        else
        {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}