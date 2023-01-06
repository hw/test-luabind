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
