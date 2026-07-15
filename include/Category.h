#ifndef CATEGORY_H
#define CATEGORY_H
#include <string>
#include <vector>
#include <utility>
using namespace std;
struct CategoryCardData {
    string name;
    double amount;
    string formattedAmount;
    string color;
    double percentage;
};
double getTotalExpenses();

// Add these to Category.h so other files know these functions exist
std::vector<std::pair<std::string, double>> getCategoryTotals();
std::vector<CategoryCardData> getCategoryCardData();
double getCategoryAmount(const std::string& category);
std::string getFormattedCategoryAmount(const std::string& category);
bool hasCategoryExpenses(const std::string& category);
std::vector<std::string> getUniqueCategories();
int getCategoryCount();
double getCategoryPercentage(const std::string& category);
std::string getCategoryColor(const std::string& category);
std::string getTopCategory();
std::string getBottomCategory();

// QML Functions
const char* getFormattedCategoryAmountQml(const char* category);
const char* getTopCategoryQml();
const char* getBottomCategoryQml();
#endif // CATEGORY_H
