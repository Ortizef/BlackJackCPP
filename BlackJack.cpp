#include <iostream>
#include <vector>
#include <ctime>

class Game
{
    std::vector<char> cards = {};

public:
    Game()
    {
        char cardSymbols[] = {'A',
                              'K',
                              'Q',
                              'J',
                              'T',
                              '9',
                              '8',
                              '7',
                              '6',
                              '5',
                              '4',
                              '3',
                              '2'};
        for (int i = 0; i < (sizeof(cardSymbols) / sizeof(char)); i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cards.push_back(cardSymbols[i]);
            }
        }
    };

    int askMoney()
    {
        int userTotalMoney;
        std::cout << "How much money are you willing to gamble today?\n";
        std::cin >> userTotalMoney;
        std::cout << "Nice you are willing to gamble $" << userTotalMoney << "\n";
        return userTotalMoney;
    }

    int askBet(int money)
    {
        int userBet;
        std::cout << "How much money are you betting on this hand?\n";
        std::cin >> userBet;
        while (userBet > money)
        {
            std::cout << "Buddy you don't have enough to bet that amount. Re-enter an amount less than your total of $" << money << "\n";
            std::cin >> userBet;
        }
        std::cout << "Good luck with your $" << userBet << " bet.\n";
        return userBet;
    }

    int startGame(int userBet, int userTotalMoney)
    {
        int cardIndex;
        char card1;
        char card2;
        char newCard;
        int playerCardValue;
        int dealerCardValue;

        cardIndex = dealCard();
        card1 = cards[cardIndex];
        cards.erase(cards.begin() + cardIndex);
        cardIndex = dealCard();
        card2 = cards[cardIndex];
        cards.erase(cards.begin() + cardIndex);
        std::cout << "Dealt player cards: " << card1 << " " << card2 << "\n";
        playerCardValue = cardTotal(card1, card2);
        std::cout << "Values of player cards is: " << playerCardValue << "\n";

        cardIndex = dealCard();
        card1 = cards[cardIndex];
        cards.erase(cards.begin() + cardIndex);
        cardIndex = dealCard();
        card2 = cards[cardIndex];
        cards.erase(cards.begin() + cardIndex);
        std::cout << "Dealt dealer cards: " << card1 << " " << card2 << "\n";
        dealerCardValue = cardTotal(card1, card2);
        std::cout << "Values of dealer cards: " << dealerCardValue << "\n";

        playerCardValue = askPlayerHit(playerCardValue);
        if (checkBust(playerCardValue))
        {
            std::cout << "Ouch. Sorry Player you went over 21! You lose! \n";
            return (userTotalMoney - userBet);
        }
        else if (checkBlackJack(playerCardValue))
        {
            std::cout << "Nice you got 21! You win! \n";
            return (userTotalMoney + userBet);
        }

        dealerCardValue = dealerPlay(dealerCardValue);

        if (checkBust(dealerCardValue))
        {
            std::cout << "Player you won! Dealer went over 21! \n";
            return (userTotalMoney + userBet);
        }
        else if (checkBlackJack(dealerCardValue))
        {
            std::cout << "Ouch you lose buddy, dealer got 21.\n";
            return (userTotalMoney - userBet);
        }
        else
        {
            int winner;
            winner = checkWinner(playerCardValue, dealerCardValue);
            if (winner == 0)
            {
                return (userTotalMoney + userBet);
            }
            else if (winner == 1)
            {
                return (userTotalMoney - userBet);
            }
            return userTotalMoney; //case if draw.
        }
    }

    int checkWinner(int playerTotal, int dealerTotal) //gonna return 0 for player win, 1 for dealer win and 2 for draw.
    {
        if (playerTotal > dealerTotal)
        {
            std::cout << "Nice player you won!\n";
            return 0;
        }
        else if (playerTotal < dealerTotal)
        {
            std::cout << "Player you lose. Dealer has better hand.\n";
            return 1;
        }
        else if (playerTotal == dealerTotal)
        {
            std::cout << "Game ended in a draw.\n";
            return 2;
        }
        return 2;
    }

    int dealerPlay(int total)
    {
        int cardIndex;
        int cardValue;

        while (checkBust(total) != true && checkBlackJack(total) != true && dealerHit(total) != false)
        {
            cardIndex = dealCard();
            cardValue = convertToNum(cards[cardIndex]);
            total += cardValue;
            std::cout << "Dealer drew a " << cards[cardIndex] << ". Dealer now has " << total << "\n";
            cards.erase(cards.begin() + cardIndex);
        }
        return total;
    }

    int askPlayerHit(int total)
    {
        char hs;
        int cardIndex;
        int cardValue;

        while (checkBust(total) != true && checkBlackJack(total) != true)
        {
            std::cout << "Would the player like to hit or stay? (H/S)\n";
            std::cin >> hs;
            if (hs == 'H')
            {
                cardIndex = dealCard();
                cardValue = convertToNum(cards[cardIndex]);
                total += cardValue;
                std::cout << "Player you drew a " << cards[cardIndex] << ". Your hand is now " << total << "\n";
                cards.erase(cards.begin() + cardIndex);
            }
            if (hs == 'S')
            {
                return total;
            }
        }
        return total;
    }

    bool checkBlackJack(int total)
    {
        if (total == 21)
        {
            return true;
        }
        return false;
    }

    bool checkBust(int total)
    {
        if (total > 21)
        {
            return true;
        }
        return false;
    }

    bool dealerHit(int total)
    {
        if (total < 18)
        {
            return true;
        }
        return false;
    }

    int dealCard()
    {
        return rand() % cards.size();
    }

    int cardTotal(char card1, char card2)
    {
        int total = 0;
        total += convertToNum(card1);
        total += convertToNum(card2);
        return total;
    }

    int convertToNum(char card)
    {
        switch (card)
        {
        case 'A':
            return 11;
        case 'K':
        case 'Q':
        case 'J':
        case 'T':
            return 10;
        case '9':
            return 9;
        case '8':
            return 8;
        case '7':
            return 7;
        case '6':
            return 6;
        case '5':
            return 5;
        case '4':
            return 4;
        case '3':
            return 3;
        case '2':
            return 2;
        default:
            return 0;
        }
    }

    bool moneyLeftOver(int moneyLeft)
    {
        if (moneyLeft == 0)
        {
            return false;
        }
        return true;
    }

    bool askPlayAgain()
    {
        char playAgain;
        std::cout << "Would you like to play another game of Black Jack? (Y/N)\n";
        std::cin >> playAgain;

        if (playAgain == 'Y')
        {
            return true;
        }
        return false;
    }

    void printMoneyLeft(int userTotalMoney)
    {
        std::cout << "You have $" << userTotalMoney << " to bet with.\n";
    }
};

int main()
{
    int userTotalMoney;
    int userBet;
    srand(time(NULL));

    Game mainGame;
    userTotalMoney = mainGame.askMoney();
    userBet = mainGame.askBet(userTotalMoney);
    userTotalMoney = mainGame.startGame(userBet, userTotalMoney);
    mainGame.printMoneyLeft(userTotalMoney);

    while (mainGame.moneyLeftOver(userTotalMoney))
    {
        if (mainGame.askPlayAgain())
        {
            userBet = mainGame.askBet(userTotalMoney);
            userTotalMoney = mainGame.startGame(userBet, userTotalMoney);
            mainGame.printMoneyLeft(userTotalMoney);
        }
    }

    std::cout << "You lost all your money! Better luck next time.\n";
}
