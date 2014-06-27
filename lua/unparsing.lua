require "dumper"
json = require "dkjson"

function unparseCompany(n)
    company = {
        name        = n,
        departments = {},
    }
    return company
end

function unparseDepartment(current, n)
    department = {
        name        = n,
        employees   = {},
        departments = {},
    }
    table.insert(current["departments"], department)
    return current, department
end

function unparseEmployee(current, n, a, s)
    employee = {
        name    = n,
        address = a,
        salary  = s,
    }
    table.insert(current["employees"], employee)
    return current
end

function dumpLua(current)
    return current, DataDumper(current) .. "\n\n"
end

function dumpJson(current)
    return current, json.encode(current, { indent = true }) .. "\n\n"
end

