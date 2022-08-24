//
//  main.cpp
//  European Roulette
//
//  Created by Evgeniy Raetsky on 23.08.2022.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <random>
using namespace std;

//roulette wheel
vector<pair<int, string>> field = {
    {0, "green"},
    {32, "red"},
    {15, "black"},
    {19, "red"},
    {4, "black"},
    {21, "red"},
    {2, "black"},
    {25, "red"},
    {17, "black"},
    {34, "red"},
    {6, "black"},
    {27, "red"},
    {13, "black"},
    {36, "red"},
    {11, "black"},
    {30, "red"},
    {8, "black"},
    {23, "red"},
    {10, "black"},
    {5, "red"},
    {24, "black"},
    {16, "red"},
    {33, "black"},
    {1, "red"},
    {20, "black"},
    {14, "red"},
    {31, "black"},
    {9, "red"},
    {22, "black"},
    {18, "red"},
    {29, "black"},
    {7, "red"},
    {28, "black"},
    {12, "red"},
    {35, "black"},
    {3, "red"},
    {26, "black"}
};
//check if chosen number is on the roulette wheel
bool correct_number(string s)
{
    int result = 0;
    for (int i = s.length() - 1; i >= 0; --i)
        result += (s[i] - '0') * pow(10, s.length() - 1 - i);
    if (result >= 0 && result <= 36)
        return true;
    return false;
}
//convert string to lower case
void string_tolower(string &s)
{
    string res = "";
    for (int i = 0; i < s.length(); ++i)
    {
        if (s[i] != ' ')
            res += tolower(s[i]);
    }
    s = res;
}

//check if players chose is correct
void check_choice(string &chose)
{
    while (chose != "black" && chose != "red" && chose != "even" && chose != "odd" && !correct_number(chose))
    {
        cout << "You enter incorrect value. Please chose black, red, even, odd, or enter a number between 0 and 36.\n";
        cin >> chose;
    }

}
//finds the colour of chosen number
string bin_search(vector<pair<int, string>> v, int value)
{
    int i = 0, j = 37;
    int m = (i + j) / 2;
    bool founded = false;
    string result = "";
    while (!founded)
    {
        if (value > v[m].first)
        {
            i = m;
            m = (i + j) / 2;
        }
        else if (value < v[m].first)
        {
            j = m;
            m = (i + j) / 2;
        }
        else
        {
            founded = true;
            result = v[m].second;
        }
    }
    return result;
}

int main() {
    random_device random_device;
    mt19937 generator(random_device());
    uniform_int_distribution<> distribution(0, 36);
    
    sort(field.begin(), field.end());

    int balance = 1000, init_balance = 1000;
    int sec = 1000000;
    int number, bet, chosen_number;
    double k_colour = 0.1, k_mod2 = 0.1, k_number = 1.1;
    char c;
    string colour;
    string chose;
    bool is_even;
    
    
    cout << "Welcome to European Roulette!\n";
    usleep(sec);
    cout << "Your current balance is $1000. To start the game, you can choose black or red, odd or even, or pick a number.\n";
    usleep(1.5*sec);
    cout << "Your chose is: ";
    cin >> chose;
    string_tolower(chose);
    check_choice(chose);
    while (balance > 0)
    {
        number = distribution(generator);
        //first mode - colour
        if (chose == "black" || chose == "red")
        {
            bet = int(balance * k_colour);
            cout << "You chose " << chose << '.' << " The bet is $" << bet << '.' << '\n';
            usleep(1.5*sec);
            cout << "Roulette is spinning...\n";
            usleep(2*sec);
            cout << number << '!' << '\n';
            colour = bin_search(field, number);
            cout << "The colour of " << number << " is " << colour << '.' << '\n';
            usleep(1.5*sec);
            if (colour == chose)
            {
                balance += bet;
                cout << "You win $" << bet << '!' << '\n' << "Your balance is $" << balance << '.' << '\n';
            }
            else
            {
                balance -= bet;
                cout <<"You lose $" << bet << '!' << '\n' << "Your balance is $" << balance << '.' << '\n';
            }
        }
        //second mode - mod2
        else if (chose == "even" || chose == "odd")
        {
            bet = int(balance * k_mod2);
            cout << "You chose " << chose << '.' << " The bet is $" << bet << '.' << '\n';
            usleep(1.5*sec);
            cout << "Roulette is spinning...\n";
            usleep(2*sec);
            cout << number << '!' << '\n';
            !(number % 2) ? is_even = true : is_even = false;
            if (is_even)
                cout << number << " is even.\n";
            else cout << number << " is odd.\n";
            usleep(1.5*sec);
            if ((chose == "even" && is_even) || (chose == "odd" && !is_even))
            {
                balance += bet;
                cout << "You win $" << bet << '!' << '\n' << "Your balance is $" << balance << '.' << '\n';
            }
            else
            {
                balance -= bet;
                cout <<"You lose $" << bet << '!' << '\n' << "Your balance is $" << balance << '.' << '\n';
            }
        }
        //third mode - a number
        else
        {
            bet = int(balance * k_number);
            chosen_number = stoi(chose);
            cout << "You chose " << chose << '.' << " The bet is $" << bet << '.' << '\n';
            cout << "Big bet! Try your luck!\n";
            usleep(1.5*sec);
            cout << "Roulette is spinning...\n";
            usleep(2*sec);
            cout << number << '!' << '\n';
            if (number == chosen_number)
            {
                balance += bet;
                cout << "You win $" << bet << '!' << '\n' << "Your balance is $" << balance << '.' << '\n';
            }
            else
            {
                balance -= bet;
                cout <<"You lose $" << bet << '!' << '\n' << "Your balance is $" << balance << '.' << '\n';
            }
        }
        //if balance allow to continue the game
        if (balance > 0)
        {
            //quit opportunity
            cout << "If you want to quit, enter 'q', or enter any other sign to continue. ";
            cin >> c;
            if (c == 'q')
            {
                cout << "Thank you for the game!\n";
                if (init_balance < balance)
                    cout << "You won $" << balance - init_balance << '!' << '\n';
                else if (init_balance > balance)
                    cout << "You lose $" << init_balance - balance << '!' << '\n';
                return 0;
            }
            
            //continue game, bet again
            cout << "Your current balance is $" << balance << ". Now you can choose black or red, odd or even, or pick a number.\n";
            usleep(1.5*sec);
            cout << "Your chose is: ";
            cin >> chose;
            string_tolower(chose);
            check_choice(chose);
        }
    }
    //balance doesn't allow to continue
    cout << "You run out of money!\n";
    cout << "Thank you for the game!\n";
    return 0;
}
