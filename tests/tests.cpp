#include "../banking/Transaction.h"
#include "../banking/Account.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Mock_acc : public Account
{
public:
	MOCK_METHOD(int, GetBalance, (), (const, override));
	MOCK_METHOD(void, ChangeBalance, (int diff), (override));
	MOCK_METHOD(void, Lock, (), (override));
	MOCK_METHOD(void, Unlock, (), (override));
};

class Mock_trans : public Transaction
{
public:
	MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};
Mock_acc makak(38, 69);
TEST_F(Acc_test, check_GetBalance)
{
	EXPECT_CALL(makak, GetBalance());
}

int main(int argc, char** argv) 
{
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}