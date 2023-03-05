local Account = {}

function Account.withdraw(v)
    Account.cnt = (Account.cnt  or 0) + v
    print("Account.cnt = ", Account.cnt )
end

Account.withdraw(3)
local a,Account = Account, nil
a.withdraw(2)