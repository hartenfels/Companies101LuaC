function parseCompany(data, company)
    ensureType(company,         "table",  "Company"     )

    ensureType(company["name"], "string", "Company name")
    c101_parseCompany(data, pop(company, "name"))

    if company["departments"] then
        ensureType(company["departments"], "table", "Company departments")
        departments = pop(company, "departments")
        for _, value in pairs(departments) do
            parseDepartment(data, value)
        end
    end

    warnExcessive(company, "Company")
end

function parseDepartment(data, department)
    ensureType(department,         "table",  "Department"     )

    ensureType(department["name"], "string", "Department name")
    c101_parseDepartment(data, pop(department, "name"))

    if department["employees"] then
        ensureType(department["employees"], "table", "Employees")
        employees = pop(department, "employees")
        for _, value in pairs(employees) do
            parseEmployee(data, value)
        end
    end

    if department["departments"] then
        ensureType(department["departments"], "table", "Subdepartments")
        subdepartments = pop(department, "departments")
        for _, value in pairs(subdepartments) do
            parseDepartment(data, value)
        end
    end

    warnExcessive(department, "Department")
    c101_endDepartment(data)
end

function parseEmployee(data, employee)
    ensureType(employee,            "table",  "Employee"        )
    ensureType(employee["name"   ], "string", "Employee name"   )
    ensureType(employee["address"], "string", "Employee address")
    ensureType(employee["salary" ], "number", "Employee salary" )
    c101_parseEmployee(data, pop(employee, "name"),
                             pop(employee, "address"),
                             pop(employee, "salary"))
    warnExcessive(employee, "Employee")
end

function ensureType(var, typeName, what)
    if type(var) ~= typeName then
        error(what .. " not a " .. typeName)
    end
end

function pop(table, key)
    value      = table[key]
    table[key] = nil
    return value
end

function warnExcessive(table, what)
    for key, value in pairs(table) do
        print("Warning: excessive table key \"" .. key .. "\" in " .. what)
    end
end

