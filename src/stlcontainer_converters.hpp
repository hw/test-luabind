#pragma once

namespace luabind {
    template <class T>
    struct default_converter<std::vector<T>> : native_converter_base<std::vector<T>>
    {
        static int compute_score(lua_State* L, int index) {
            return (lua_type(L, index) == LUA_TTABLE )? 0 : -1;
        }

        std::vector<T>  from(lua_State* L, int index) {
            std::vector<T> container; 
            luabind::object tbl(from_stack(L, index)); 
            
            for (luabind::iterator itr(tbl), end; itr != end; ++itr) { 
               boost::optional<T> v = object_cast_nothrow<T>(*itr); 
               if (v) container.push_back(*v); 
            } 

            return container; 
        }

        void to(lua_State* L, std::vector<T>  const& container)
        {
            lua_createtable(L, container.size(), 0); 
            luabind::object tbl(from_stack(L, -1)); 
            int n = 0;
            for (auto itr = container.begin(); itr != container.end(); ++itr) { 
               tbl[++n] = *itr; 
            }
        }
    };

    template <class T> struct default_converter<std::vector<T>  const&> : default_converter<std::vector<T> > {};

    template <class T>
    struct default_converter<std::set<T>> : native_converter_base<std::set<T>>
    {
        static int compute_score(lua_State* L, int index) {
            return (lua_type(L, index) == LUA_TTABLE )? 0 : -1;
        }

        std::set<T>  from(lua_State* L, int index) {
            std::set<T> container; 
            luabind::object tbl(from_stack(L, index)); 
            
            for (luabind::iterator itr(tbl), end; itr != end; ++itr) { 
               boost::optional<T> v = object_cast_nothrow<T>(*itr); 
               if (v) container.push_back(*v); 
            } 

            return container; 
        }

        void to(lua_State* L, std::set<T>  const& container)
        {
            lua_createtable(L, container.size(), 0); 
            luabind::object tbl(from_stack(L, -1)); 
            int n = 0;
            for (auto itr = container.begin(); itr != container.end(); ++itr) { 
               tbl[++n] = *itr; 
            }
        }
    };

    template <class T> struct default_converter<std::set<T>  const&> : default_converter<std::set<T> > {};

    template <class K, class V>
    struct default_converter<std::map<K,V>> : native_converter_base<std::map<K,V>>
    {
        static int compute_score(lua_State* L, int index) {
            return (lua_type(L, index) == LUA_TTABLE )? 0 : -1;
        }

        std::map<K,V>  from(lua_State* L, int index) {
            std::map<K, V> container; 
            luabind::object tbl(from_stack(L, index)); 
            
            for (luabind::iterator itr(tbl), end; itr != end; ++itr) { 
               boost::optional<K> k = object_cast_nothrow<K>(itr.key());
               boost::optional<V> v = object_cast_nothrow<V>(*itr); 
               if (k && v) container.insert_or_assign(k, v); 
            } 

            return container; 
        }

        void to(lua_State* L, std::map<K, V>  const& container)
        {
            lua_createtable(L, container.size(), 0); 
            luabind::object tbl(from_stack(L, -1)); 
            for (auto itr = container.begin(); itr != container.end(); ++itr) { 
               tbl[itr->first] = itr->second; 
            }
        }
    };

    template <class K, class V> struct default_converter<std::map<K, V>  const&> : default_converter<std::map<K, V> > {};
};
