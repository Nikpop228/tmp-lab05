#include "Transaction.h"
#include "Account.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;

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
    Mock_trans() : Transaction() {};
	MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

//========================================================================================
//                                    Обычные тесты
//========================================================================================

TEST(Account, GetBalance)
{
    Account makak(38, 59);
    int balance = makak.GetBalance();
    EXPECT_EQ(balance, 59);
}

TEST(Account,ChangeBalance)
{
    Account makak(38, 59);
    ASSERT_THROW(makak.ChangeBalance(98), std::runtime_error); // проверка на исключение при попытке добавить баланс (должно выдать)
    makak.Lock(); // снимаем ограничение
 	makak.ChangeBalance(98); // изменяем баланс
    int balance = makak.GetBalance(); 
    EXPECT_EQ(balance, 98 + 59); // проверяем, изменился ли баланс
}

TEST(Account, Lock)
{
    Account makak(38, 59);
    ASSERT_NO_THROW(makak.Lock()); // проверка на исключение после создания аккаунта (не должно выдать)
}

TEST(Account, Unlock)
{
    Account makak(38, 59);
    makak.Lock(); // разблокируем аккаунт
    ASSERT_NO_THROW(makak.ChangeBalance(98)); // исключения быть не должно
    makak.Unlock(); // заблокируем
    ASSERT_THROW(makak.ChangeBalance(99), std::runtime_error); // попробуем изменить баланс, должно выдать исключение
}

TEST(Transaction, Make)
{
    Account from(8, 264);
    Account to(97, 156);
    Transaction trans;
    trans.set_fee(2);
    bool suc = trans.Make(from, to, 200);
    EXPECT_TRUE(suc);
}

TEST(Transaction, SaveToDataBase)
{
    Transaction trans;
    Account ac1(1, 200);
    Account ac2(2, 500);
    bool suc = trans.Make(ac1, ac2, 150);
    EXPECT_TRUE(suc);
}

//========================================================================================//
//                                    Мок тесты                                           //
//========================================================================================//

TEST(Mock_account, Lock)
{
    Mock_acc from(8, 264);
    Mock_acc to(97, 156);
    Transaction trans;

    EXPECT_CALL(from, Lock()).Times(::testing::AtLeast(1));

    bool suc = trans.Make(from, to, 200);
}

TEST(Mock_account, Unlock)
{
    Mock_acc from(8, 264);
    Mock_acc to(97, 156);
    Transaction trans;

    EXPECT_CALL(from, Unlock()).Times(::testing::AtLeast(1));

    bool suc = trans.Make(from, to, 200);
}

TEST(Mock_account, GetBalance)
{
    Mock_acc from(8, 264);
    Mock_acc to(97, 156);
    Transaction trans;

    EXPECT_CALL(from, GetBalance()).Times(::testing::AtLeast(1));

    bool suc = trans.Make(from, to, 200);
}

TEST(Mock_account, ChangeBalance)
{
    Mock_acc from(8, 264);
    Mock_acc to(97, 156);
    Transaction trans;

    ON_CALL(to, GetBalance()).WillByDefault(::testing::Return(156));
    ON_CALL(from, GetBalance()).WillByDefault(::testing::Return(264));
    EXPECT_CALL(from, ChangeBalance(_)).Times(::testing::AtLeast(1));

    bool suc = trans.Make(from, to, 200);
}

int main(int argc, char** argv) 
{
    ::testing::FLAGS_gmock_verbose = "error";
	::testing::InitGoogleMock(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}