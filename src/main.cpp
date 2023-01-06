#include <iostream>
#include <set>

extern "C" {
   #include <lua.h>
   #include <lualib.h>
   #include <lauxlib.h>
}

#include <luabind/luabind.hpp>
#include "stlcontainer_converters.hpp"

lua_State* L; 

class Test {
public:
   Test() : flag(0) { }

   void hello(const std::string& name) {
      std::cout << "Hello " << name << "!" << std::endl;
   }

   void luabindClass() {
      luabind::module(L) [
         luabind::class_<Test>("Test")
         .def("hello", &Test::hello)
         .def_readwrite("flag", &Test::flag)
      ];
      luabind::globals(L)["test"] = this;
   }

public:
   int flag;
};

void doFile(const std::string& path) {
   auto ret = luaL_dofile(L, path.c_str());
   if (ret != LUA_OK) {
      std::cerr << lua_tostring( L, lua_gettop( L ) ) << std::endl;
      lua_pop( L, 1 );
   }
}

int main(int argc, char* argv[]) {
   L = luaL_newstate();
   luaL_openlibs(L);
   luabind::open(L);

   try {
      boost::scoped_ptr<Test> test(new Test());
      test->luabindClass();

      doFile("test.lua");
      std::cout << "test->flag is now: " << test->flag << std::endl;

      std::string name("c++");
      std::map<std::string, std::string> attr = { {"first", "1st"}, {"second", "2nd"}, {"third", "3rd"} };

      int ret = luabind::call_function<int>(L, "handler", name, attr, 12345);
      std::cout << "handler() returns: " << ret << std::endl;
      std::cout << "test->flag is now: " << test->flag << std::endl;
   }

   catch(const std::exception& e) {
      std::cerr << "Exception: " << e.what() << std::endl;
   }
   
   lua_close(L);
   return 0;   
}

/*

test:hello("Lua")

handler = function(name, attr, flag) 
    local result = test.flag + 1

    print("Called by ", name, "with: ")
    for k,v in pairs(attr) do 
        print (k, " = ", v)
    end

    test.flag = flag;
    return result;
end

print("test.flag = ", test.flag)
if (test.flag == 0) then
    test.flag = 1
end

*/
