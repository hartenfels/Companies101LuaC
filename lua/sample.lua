return {
    name        = "Acme Corporation",
    departments = {
        {
            name        = "Research",
            employees   = {
                {name = "Craig", address = "Redmond", salary = 123456},
                {name = "Erik",  address = "Utrecht", salary = 12345 },
                {name = "Ralf",  address = "Koblenz", salary = 1234  },
            },
		},
		{
			name        = "Development",
			employees   = {
				{name = "Ray", address = "Redmond", salary = 234567},
			},
			departments = {
				{
					name        = "Dev1",
					employees   = {
						{name = "Klaus", address = "Boston", salary = 23456},
					},
					departments = {
						{
							name      = "Dev1.1",
							employees = {
								{name = "Karl", address = "Riga",      salary = 2345},
								{name = "Joe",  address = "Wifi City", salary = 2344},
							},
						},
					},
				},
			},
		},
    },
}

