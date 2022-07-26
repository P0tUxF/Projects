// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <852021>
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include "wallet.h"

//  Writes a Wallet constructor that takes no parameters and constructs an
//  empty wallet.
//
// Example:
//  Wallet wObj{};

Wallet::Wallet(): categories(){}

//  Writes a function, size, that takes no parameters and returns an unsigned
//  int of the number of categories in the Wallet contains.
//
// Example:
//  Wallet wObj{};
//  auto size = wObj.size();

const unsigned int Wallet::size()const {
    return categories.size();
}

//  Writes a function, empty, that takes no parameters and returns true
//  if the number of categories in the Wallet is zero, false otherwise.
//
// Example:
//  Wallet wwObj{};
//  auto isEmpty = wObj.empty();

const bool Wallet::empty()const {
    if (categories.size()== 0) {
        return true;
    } else {
        return false;
    }
    return 0;
}


//  Writes a function, newCategory, that takes one parameter, a category
//  identifier, and returns the Category object as a reference. If an object
//  with the same identifier already exists, then the existing object should be
//  returned. Throw a std::runtime_error if the Category object cannot be
//  inserted into the container.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");#

Category& Wallet::newCategory(const std::string ident){
    auto it = categories.find(ident);
    if (it != categories.end()) {
        return categories.at(ident);
    } else if (categories.find(ident) == categories.end()) {
        return categories.at(ident);
    }
    throw std::runtime_error("Category Object cannot be inserted. ");
}

//  Writes a function, addCategory, that takes one parameter, a Category
//  object, and returns true if the object was successfully inserted. If an
//  object with the same identifier already exists, then the contents should be
//  merged and then return false. Throw a std::runtime_error if the Category
//  object cannot be inserted into the container for whatever reason.
//
// Example:
//  Wallet wObj{};
//  Category cObj{"categoryIdent"};
//  wObj.addCategory(cObj);

const bool Wallet::addCategory(const Category x) {
    auto it = categories.find(x.getIdent());
    if (it != categories.end()) {
        it->second = x;
        return false;
    } else if (it == categories.end()){
        categories.insert(std::pair<std::string, Category>(x.getIdent(),x));
        return true;
    } else throw std::runtime_error("Category Object can't be inserted");
}
//  Writes a function, getCategory, that takes one parameter, a Category
//  identifier and returns the Category. If no Category exists, throw an
//  appropriate exception.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
//  auto cObj = wObj.getCategory("categoryIdent");

Category Wallet::getCategory(const std::string ident) {
    if (categories.find(ident) != categories.end()) {
        return categories.at(ident);
    } else {
        throw std::out_of_range("No category exists. ");
    }
}

//  Writes a function, deleteCategory, that takes one parameter, a Category
//  identifier, and deletes it from the container, and returns true if the
//  Category was deleted. If no Category exists, throw an appropriate exception.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
//  wObj.deleteCategory("categoryIdent");

const bool Wallet::deleteCategory(const std::string ident){
   if (categories.find(ident) != categories.end()) {
       categories.erase(ident);
       return true;
    } else {
        throw std::out_of_range("No category exists. ");
    }
}

//  write a function, load, that takes one parameter, a std::string,
//  containing the filename for the database. Open the file, read the contents,
//  and populates the container for this Wallet. If the file does open throw an
//  appropriate exception (either std::runtime_error or a derived class).
//
// A note on clashes:
//  If you encounter two categories with the same key, the categories should be
//  merged (not replaced!). If you encounter two items with the same key in the
//  same category, the items should be merged (not replaced!). If you encounter
//  two entries with the same key in the same item, the entries should be merged
//  (undefined as to which value is picked). Two items in different categories
//  can have the same key, as can two entries in different items.
//
// JSON formatting:
//  The JSON file has the following format (see the sample database.json file
//  also provided with the coursework framework):
//    {
//      "Category 1" : {
//        "Item 1":  {
//          "detail 1 key": "detail 1 value",
//          "detail 2 key": "detail 2 value",
//          ...
//        },
//        "Item 2":  {
//          "detail 1 key": "detail 1 value",
//          "detail 2 key": "detail 2 value"
//        },
//        ...
//      },
//      "Category 2": {
//        "Item 1": {
//          "detail 1 key": "detail 1 value"
//        }
//        ...
//      }
//    }
//
// More help:
//  To help you with this function, I've selected the nlohmann::json
//  library that you must use for your coursework. Read up on how to use it
//  here: https://github.com/nlohmann/json. You may not use any other external
//  library other than the one I have provided. You may choose to process the
//  JSON yourself without the help of the library but I guarantee this will be
//  more work.
//
//  Understanding how to use external libraries is part of this coursework! You
//  will need to use this file to deserialize the JSON from string
//  to the JSON object provided by this library. Don't just look at the code
//  provided below, or in the README on the GitHub and despair. Google search,
//  look around, try code out in a separate file to all figure out how to use
//  this library.
//
//  Once you have deserialized the JSON string into an object, you will need to
//  loop through this object, constructing Category and Item objects according
//  to the JSON data in the file.   
//
// Example:
//  Wallet wObj{};
//  wObj.load("database.json");

void Wallet::load(const std::string filename) { 
    std::fstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("File is not opened. ");
    }
    //loops through json getting appropiate data.
    nlohmann::json j = nlohmann::json::parse(file);
    for (auto it = j.begin(); it != j.end(); it++) {
        std::string category = it.key();
        auto j2 = it.value();
        Category x{category};
        for (auto it2 = j2.begin(); it2 != j2.end(); it2++) {
            std::string item = it2.key();
            auto j3 = it2.value();
            Item y{item};
            for (auto it3 = j3.begin(); it3 != j3.end(); it3++) {
                std::string entry = it3.key();
                auto j4 = it3.value();
                y.addEntry(entry, j4);
            }   
            x.addItem(y);
        }
        addCategory(x);
    }
    file.close();
}


//  write a function ,save, that takes one parameter, the path of the file
//  to write the database to. The function should serialise the Wallet object
//  as JSON.
//
// Example:
//  Wallet wObj{};
//  wObj.load("database.json");
//  ...
//  wObj.save("database.json");

void Wallet::save(const std::string filename) {
    std::ofstream out(filename);
    out << str();
    out.close(); 
}
//  write an == operator overload for the Wallet class, such that two
//  Wallet objects are equal only if they have the exact same data.
//
// Example:
//  Wallet wObj1{};
//  Wallet wObj2{};
//  if(wObj1 == wObj2) {
//    ...
//  }

bool operator==(const Wallet &x, const Wallet &y) {
    return(x.categories == y.categories);
}

//  write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Wallet.
//
// Hint:
//  See the coursework specification for how this JSON should look.
//
// Example:
//  Wallet wObj{};
//  std::string s = wObj.str();
const std::string Wallet::str()const {
     std::stringstream walletStream;
     walletStream << "{";
     unsigned int counter = 0;
     for (auto it = categories.begin() ; it != categories.end(); it++) {
         walletStream << "\""<< it->first << "\":" << it->second.str();
         if (categories.size() - 1 > counter) {
            walletStream << ",";
            counter++;
         } 
     }
     walletStream << "}";
    return walletStream.str();
}
