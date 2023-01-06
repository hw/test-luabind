Test Project for luabind.
=========================

- CMakeFile with find\_package(LuaBind) - defined in FindLuaBind.cmake
- Allows Lua to access C++ class methods.
- Allows C++ to call lua functions with STL container types (vector, set and map). 

To pass stl containers into Lua codes, convertors for stl containers need to be defined.
See stlcontainer\_convertor.hpp

