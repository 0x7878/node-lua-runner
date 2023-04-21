-- package.cpath = package.cpath .. ";V:\\Development\\github.com\\node-lua-runner\\build\\Release\\?.dll"
local lfs = require"lfs"

local counter = 0

function attrdir (path)
    for file in lfs.dir(path) do
        if counter > 9 then
            break
        end
        if file ~= "." and file ~= ".." then
            counter = counter + 1
            local f = path..'/'..file
            print ("\t "..f)
            local attr = lfs.attributes (f)
            assert (type(attr) == "table")
            if attr.mode == "directory" then
                attrdir (f)
            else
                for name, value in pairs(attr) do
                    print (name, value)
                end
            end
        end
    end
end

attrdir (".")