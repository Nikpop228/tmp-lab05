#include "Transaction.h"
#include "Account.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

 class Mock_acc : public Account
 {
 public:
 	Mock_acc(int a, int b) : Account(a, b) {}
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

TEST(Acc_test, check_GetBalance)
{
    Account makak(38, 59);
    int balance = makak.GetBalance();
    EXPECT_EQ(balance, 59);
}

TEST(Acc_test, check_ChangeBalance)
{
    Account makak(38, 59);
    ASSERT_THROW(makak.ChangeBalance(98), std::runtime_error); // проверка на исключение при попытке добавить баланс (должно выдать)
    makak.Lock(); // снимаем ограничение
 	makak.ChangeBalance(98); // изменяем баланс
    int balance = makak.GetBalance(); 
    EXPECT_EQ(balance, 98 + 59); // проверяем, изменился ли баланс
}

TEST(Acc_test, check_Lock)
{
    Account makak(38, 59);
    ASSERT_NO_THROW(makak.Lock()); // проверка на исключение после создания аккаунта (не должно выдать)
}

TEST(Acc_test, check_Unlock)
{
    Account makak(38, 59);
    makak.Lock(); // разблокируем аккаунт
    ASSERT_NO_THROW(makak.ChangeBalance(98)); // исключения быть не должно
    makak.Unlock(); // заблокируем
    ASSERT_THROW(makak.ChangeBalance(99), std::runtime_error); // попробуем изменить баланс, должно выдать исключение
}

using ::testing::_;

TEST(Transaction, Mock) 
{
    Mock_trans trans;
    Account ac1(1, 50);
    Account ac2(2, 500);
    EXPECT_CALL(trans, SaveToDataBase(_, _, 51));
    trans.SaveToDataBase(ac1, ac2, 51);
    EXPECT_EQ(ac2.GetBalance(), 500);

}

int main(int argc, char** argv) 
{
	::testing::InitGoogleMock(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}